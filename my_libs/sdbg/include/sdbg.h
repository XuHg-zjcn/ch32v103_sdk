/***********************************************************************
 * serial debug for CH32V10x
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
#ifndef SDBG_H
#define SDBG_H

#include <stdint.h>
#include "ch32v10x.h"

typedef enum{
    SDB_OK = 0,
    SDB_INVAILD_PTR,
    SDB_INVAILD_BKPT,
    SDB_BKPT_FULL,
    SDB_FLASH_OP_ERR,
    SDB_CRC_ERR
}SerDbg_Stat;

typedef enum{           // Param,                       | ret
    SDB_Read_Reg   = 0, // rx-ry(2B)                    | data(4nB)
    SDB_Write_Reg  = 1, // rx-ry(2B), data(4nB)         | stat(1B)
    SDB_Read_Mem   = 2, // addr(4B), len(2B)            | data(len), stat(1B)
    SDB_Write_Mem  = 3, // addr(4B), len(2B), data(lenB)| stat(1B)
    SDB_Read_Flash = 4, //
    SDB_Write_Flash= 5, //
    SDB_New_BKPT   = 6, // addr(4B)                     | index(1B)
    SDB_Mode_BKPT  = 7, // index(1B), set(1B)           | stat(1B)
    SDB_Get_BKPT   = 8, // index(1B)                    | [n(1B)], set(nB)
    SDB_Pause      = 9, //                              |
    SDB_Resume     = 10,//                              |
    SDB_Step       = 11,//                              |
    SDB_About      = 12,//                              | str
}SerDbg_Cmd;

#endif
