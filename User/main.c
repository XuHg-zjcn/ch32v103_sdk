/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2020/04/30
* Description        : Main program body.
*******************************************************************************/

#include "debug.h"


#define LED_PORT GPIOC
#define LED_PIN  GPIO_Pin_13

/* Global typedef */

/* Global define */

/* Global Variable */

void My_GPIO_Init()
{
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef gpio_init;
	gpio_init.GPIO_Pin = LED_PIN;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_PORT, &gpio_init);
}

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	My_GPIO_Init();
	//printf("SystemClk:%d\r\n",SystemCoreClock);

	//printf("This is printf example\r\n");

	while(1)
	{
		GPIO_SetBits(LED_PORT, LED_PIN);
		Delay_Ms(100);
		GPIO_ResetBits(LED_PORT, LED_PIN);
		Delay_Ms(100);
	}
}

