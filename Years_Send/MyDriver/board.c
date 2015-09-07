/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * ����		 ��Years
 * �ļ���  ��board.c
 * ����    ��LED
 * ����    ��791276337@qq.com
 * ��ע    ���δ�ʱ��
 * ����    ��2015.8.23
*****************************************************************************/
#include "board.h"

static volatile uint32_t usTicks = 0;
// �δ�ʱ���������� ,49������
static volatile uint32_t sysTickUptime = 0;

void cycleCounterInit(void)
{
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    usTicks = clocks.SYSCLK_Frequency / 1000000;
}

void Delay(vu32 nCount)
{
  for(; nCount!= 0;nCount--);
}

void SysTick_IRQ(void)
{
	sysTickUptime++;
	S_cnt_1ms++;
	S_cnt_2ms++;
	S_cnt_5ms++;
	S_cnt_10ms++;
	S_cnt_20ms++;
}

