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
#ifndef BREAK_POINTS_H
#define BREAK_POINTS_H

#include "sdbg.h"

#define SERDBG_MAX_BKPT 8

typedef enum{
    BKPT_None = 0,       //没有设置过断点或已恢复原样
    BKPT_Ignore = 1,     //忽略断点，但不擦除
    BKPT_BinCmd = 2,     //进入二进制交互模式，需要配合上位机程序使用
    BKPT_RptNum = 3,     //报告断点编号
    BKPT_RptReg = 4,     //报告寄存器(r0-r31, epsr, epc)
}BKPT_Mode;

typedef struct{
    uint32_t p;     //指针
    uint16_t old;   //原有代码
    BKPT_Mode mode; //断点的模式
}BreakPoint;

#ifdef __cplusplus
extern "C"{
#endif
int New_BreakPoint(uint32_t p, BKPT_Mode mode);
SerDbg_Stat Erase_BreakPoint(int index);
int find_bkpt_num(uint32_t p);
#ifdef __cplusplus
}
#endif


#endif
