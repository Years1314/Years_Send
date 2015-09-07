/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * 作者		 ：Years
 * 文件名  ：Years_LED.c
 * 描述    ：LED
 * 邮箱    ：791276337@qq.com
 * 备注    ：无
 * 日期    ：2015.8.23
*****************************************************************************/
#include "Years_LED.h"
#include "board.h"

void Years_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LED_A|LED_B;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO, &GPIO_InitStructure);
	Years_LEDA_ON();
	Years_LEDB_ON();
	}

void Years_LEDA_ON(void)
{
	GPIO_ResetBits(LED_GPIO, LED_A);
}

void Years_LEDA_OFF(void)
{
	GPIO_SetBits(LED_GPIO, LED_A);
}

void Years_LEDB_ON(void)
{
	GPIO_ResetBits(LED_GPIO, LED_B);
}

void Years_LEDB_OFF(void)
{
	GPIO_SetBits(LED_GPIO, LED_B);
}

void Years_LEDA_Twinkle(void)
{
	Years_LEDA_ON();
	Delay(2000000);
	Years_LEDA_OFF();
	Delay(2000000);
	Years_LEDA_ON();
	Delay(2000000);
	Years_LEDA_OFF();
	Delay(2000000);
	Years_LEDA_ON();
	Delay(2000000);
	Years_LEDA_OFF();
	Delay(2000000);
}

void Years_LEDB_Twinkle(void)
{
	Years_LEDB_ON();
	Delay(2000000);
	Years_LEDB_OFF();
	Delay(2000000);
	Years_LEDB_ON();
	Delay(2000000);
	Years_LEDB_OFF();
	Delay(2000000);
	Years_LEDB_ON();
	Delay(2000000);
	Years_LEDB_OFF();
	Delay(2000000);
}



