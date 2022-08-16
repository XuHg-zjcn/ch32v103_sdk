/***********************************************************************
 * Breakpoints operators for CH32V10x
 * Copyright (C) 2022  Xu Ruijun
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ***********************************************************************/
#include "break_points.h"
#include "reg_ram.h"
#include "step.h"
#include <string.h>

extern SDB_RegSave sdbg_regsave;
extern void Error_Handler(void);
extern uint32_t RunInstRAM[2];
extern uint32_t RunInstRAM_epc;

int bkpt_last = -1;                 //最后一个设置的断点编号，-1表示没有设置过
BreakPoint bkpts[SERDBG_MAX_BKPT];  //断点数据

void write_0x0000(uint32_t p)
{
    if(p < 0x08000000){
        p += 0x08000000;
    }
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    FLASH_ProgramHalfWord(p, 0x0000);
    FLASH_Lock();
}

int find_FreeBKPT()
{
    int i;
    //尽量使用与上次设置的断点号以后的编号
    for(i=bkpt_last+1;i<SERDBG_MAX_BKPT;i++){
        if(bkpts[i].mode == BKPT_None){
            return i;
        }
    }
    //如果没有，则从头开始找
    for(i=0;i<=bkpt_last;i++){
        if(bkpts[i].mode == BKPT_None){
            return i;
        }
    }
    //找不到空闲的，返回-1
    return -1;
}

int New_BreakPoint(uint32_t p, BKPT_Mode mode)
{
    if((uint32_t)p & 0x01){
        return -SDB_INVAILD_PTR;
    }
    int index = find_FreeBKPT();
    if(index < 0){
        return -SDB_BKPT_FULL;
    }
    bkpts[index].p = p;
    bkpts[index].old = *(uint16_t*)p;
    bkpts[index].mode = mode;
    bkpt_last = index;
    write_0x0000(p);
    return index;
}

SerDbg_Stat Erase_BreakPoint(int index)
{
    if(bkpts[index].mode == BKPT_None){
        return SDB_INVAILD_BKPT;
    }
    uint32_t p = (uint32_t)bkpts[index].p;
    if(p < 0x08000000){
        p += 0x08000000;
    }
    FLASH_Unlock_Fast();
    FLASH_BufReset();
    uint32_t *pPage = (uint32_t *)(p&0xFFFFFF80);
    uint32_t tmp[32];
    for(int i=0;i<32;i++){
        tmp[i] = pPage[i];
    }
    ((uint16_t *)tmp)[(p-(uint32_t)pPage)/2] = bkpts[index].old;
    FLASH_ErasePage_Fast((uint32_t)pPage);
    FLASH_BufReset();
    for(int i=0;i<8;i++){
        FLASH_BufLoad((uint32_t)(pPage+i*4), tmp[i*4], tmp[i*4+1], tmp[i*4+2], tmp[i*4+3]);
    }
    FLASH_ProgramPage_Fast((uint32_t)pPage);
    FLASH_Lock_Fast();
    if((uint32_t)p == RunInstRAM_epc){
        //擦除的是当前断点
        memset(RunInstRAM, 0x00, 6);
    }
    bkpts[index].mode = BKPT_None;
    return SDB_OK;
}

int find_bkpt_num(uint32_t p)
{
    for(int i=0;i<SERDBG_MAX_BKPT;i++){
        if(bkpts[i].p == p){
            return i;
        }
    }
    return -1;
}

void Breakpoint_Handler_C()
{
    if(RunInstRAM[0]){
        sdbg_regsave.mepc = RunInstRAM_epc;
        RunInstRAM[0] = 0;
        return;
    }
    int index = find_bkpt_num(sdbg_regsave.mepc);
    if(index < 0){
        while(1);
    }
    uint32_t Inst = bkpts[index].old;
    if(Inst & 0b11 == 0b11){
        //是32位指令
        Inst |= (uint32_t)(*(uint16_t *)(bkpts[index].p + 2)) << 16;
    }
    RunStep_RAM(Inst);
}
