/***********************************************************************
 * read/write reg and ram header for CH32V10x
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
#ifndef REG_RAM_H
#define REG_RAM_H

#include "sdbg.h"

typedef enum{
    SDB_NoWait = 0,
    SDB_UARTCap = 1,
    SDB_StepStop = 2
}SDB_RegSaveStat;

typedef struct{
    uint32_t x[32];
    uint32_t mepc;
    SDB_RegSaveStat stat;
}SDB_RegSave;

#endif
