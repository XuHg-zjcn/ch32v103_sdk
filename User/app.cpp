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


int app(void)
{
	C_Pin led = C_Pin(2, 13);
	led.loadXCfg(GPIO_GP_PP0);
	while(1){
		led.write_pin(Pin_Reset);
		XDelayMs(100);
		led.write_pin(Pin_Set);
		XDelayMs(100);
	}
	return 0;
}
