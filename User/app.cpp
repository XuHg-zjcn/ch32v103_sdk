/********************************************************************************
 * C++程序入口文件
 * Copyright (C) 2021-2022  Xu Ruijun
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *******************************************************************************/
#include "app.h"
#include "c_pin.hpp"
#include "delay.hpp"
#include "break_points.h"


void Led2(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	XDelayMs(100);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	XDelayMs(100);
}

int app(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	C_Pin led = C_Pin(2, 13);
	led.loadXCfg(GPIO_GP_PP0);
	int index = New_BreakPoint((uint32_t)&Led2, BKPT_Ignore);
	if(index >= 0){
		//Erase_BreakPoint(index);
	}
	while(1){
		Led2();
	}
	return 0;
}
