/***********************************************************************
 * Step run instruct in RAM for CH32V10x
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
#include "step.h"
#include "reg_ram.h"
#include <stdbool.h>

#define rd(x)        ((x)>>7&0x1f)
#define rs1(x)       ((x)>>20&0x1f)
#define rs2(x)       ((x)>>15&0x1f)

#define i_imm(x)     ((int32_t)(x)>>20)

#define b_imm(x)     (((int32_t)(x)>>31)<<12 | \
                      ((x)>>25&0x3f)<<5      | \
                      ((x)>>8&0xf)<<1        | \
                      ((x)>>7&1)<<11)

#define j_imm(x)     (((int32_t)(x)>>31)<<20 | \
                      ((x)>>21&0x3ff)<<1     | \
                      ((x)>>20&1)<<11        | \
                      ((x)>>12&0xff)<<12)

#define cj_imm(x)    ((-((x)>>12&1))<<11 | \
                      ((x)>>11&1)<<4     | \
                      ((x)>>9&3)<<8      | \
                      ((x)>>8&1)<<10     | \
                      ((x)>>7&1)<<6      | \
                      ((x)>>6&1)<<7      | \
                      ((x)>>3&7)<<1      | \
                      ((x)>>2&1)<<5)

#define cb_imm(x)    ((-((x)>>12&1))<<8 | \
                      ((x)>>11&1)<<4    | \
                      ((x)>>10&1)<<3    | \
                      ((x)>>5&3)<<6     | \
                      ((x)>>3&3)<<1     | \
                      ((x)>>3&1)<<5)

#define cj_rs1(x)    ((x>>7)&0b11111)
#define cb_rs1(x)    ((x>>7&0b111) + 8)

extern SDB_RegSave sdbg_regsave;
uint32_t RunInstRAM[2];
uint32_t RunInstRAM_epc = 0;


/*
由于把指令搬到内存中运行，可能会受到pc指针的改变影响运行结果，部分指令需要由软件模拟。

受影响指令
jal, jalr, beq, bne, bge, blt, bgeu, bltu
c.jal, c.jalr, c.j, c.jr, c.beqz, c.bnez
ecall, ebreak, mret(暂时没有模拟)
c.ebreak
*/

void RunStep_RAM(uint32_t Inst)
{
    sdbg_regsave.x[0] = 0;
    if(Inst & 0b11 == 0b11){
        uint32_t opcode = Inst & 0b1111111;
        //32位指令
        if(opcode == 0b1100111){
            //jal
            sdbg_regsave.x[rs1(Inst)] = sdbg_regsave.mepc + 4;
            sdbg_regsave.mepc += j_imm(Inst);
            return;
        }else if((opcode == 0b1100111) && ((Inst >> 12 & 0b111) == 0b000)){
            //jalr
            uint32_t t = sdbg_regsave.mepc + 4;
            sdbg_regsave.mepc = (sdbg_regsave.x[rs1(Inst)] + i_imm(Inst)) & ~1;
            sdbg_regsave.x[rd(Inst)] = t;
            return;
        }else if(opcode == 1100011){
            _Bool res;
            uint32_t data1 = sdbg_regsave.x[rs1(Inst)];
            uint32_t data2 = sdbg_regsave.x[rs2(Inst)];
            switch(Inst >> 12 & 0b111){
            case 0b000:  //beq
                res = data1 == data2;
                break;
            case 0b001:  //bne
                res = data1 != data2;
                break;
            case 0b100:  //blt
                res = (int32_t)data1 < data2;
                break;
            case 0b101:  //bge
                res = (int32_t)data1 >= data2;
                break;
            case 0b110:  //bltu
                res = (uint32_t)data1 < data2;
                break;
            case 0b111:  //bgeu
                res = (uint32_t)data1 >= data2;
                break;
            default:
                res = false;
                break;
            }
            sdbg_regsave.mepc += res?b_imm(Inst):4;
            return;
        }
    }else{
        //16位指令
        uint16_t op = Inst & 0b11;
        uint16_t funct3 = Inst >> 13;
        if(op == 0b01){
            if(funct3 == 0b001 || funct3 == 0b101){
                if(funct3 == 0b001){ //c.jal
                    sdbg_regsave.x[1] = sdbg_regsave.mepc + 2;
                }
                sdbg_regsave.mepc += cj_imm(Inst);  //c.jal or c.j
                return;
            }else if(funct3 == 0b110 || funct3 == 0b111){
                if(funct3 == 0b111 ^ sdbg_regsave.x[cb_rs1(Inst)] == 0){
                    sdbg_regsave.mepc += cb_imm(Inst);  //c.beqz, c.bnez
                }else{
                    sdbg_regsave.mepc += 2;
                }
                return;
            }
        }else if(op == 0b10){
            if(funct3 == 0b100 && (Inst>>7 & 0b11111) != 0){
                if(Inst & (1<<12)){  //c.jalr
                   uint32_t t = sdbg_regsave.mepc + 2;
                   sdbg_regsave.mepc = sdbg_regsave.x[cj_rs1(Inst)];
                   sdbg_regsave.x[1] = t;
                   return;
                }else{  //c.jr
                   sdbg_regsave.mepc = sdbg_regsave.x[cj_rs1(Inst)];
                   return;
                }
            }
        }
    }
    //没有用软件模拟，搬到RAM中执行指令
    RunInstRAM[0] = Inst;
    RunInstRAM[1] = 0;
    RunInstRAM_epc = sdbg_regsave.mepc + ((Inst & 0b11) == 0b11 ? 4 : 2);
    sdbg_regsave.mepc = (uint32_t)&RunInstRAM;
}
