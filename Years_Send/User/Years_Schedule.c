/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * 作者		 ：Years
 * 文件名  ：Years_Schedule.c
 * 描述    ：定时处理任务
 * 邮箱    ：791276337@qq.com
 * 备注    ：无
 * 日期    ：2015.8.23
*****************************************************************************/
#include "Years_Schedule.h"
#include "stm32f10x.h"
#include "config.h"
extern u8 Tx_Buffer[32];
extern u8 Rx_Buffer[32];

uint16_t S_cnt_1ms=0,S_cnt_2ms=0,S_cnt_5ms=0,S_cnt_10ms=0,S_cnt_20ms=0;

static void Years_Loop_1ms(void)
{
	Years_NRF_Check_Event();
	Tx_Buffer[1]=0x88;
  Remote_Send();
}

static void Years_Loop_2ms(void)
{
	
}

static void Years_Loop_5ms(void)
{
	
}

static void Years_Loop_10ms(void)
{
	
}

static void Years_Loop_20ms(void)
{
	Years_LEDA_ON();
	Years_LEDB_ON();
}

void Years_Loop(void)
{
	if(S_cnt_1ms>=1){
		Years_Loop_1ms();
		S_cnt_1ms=0;
	}
	if(S_cnt_2ms>=2){
		Years_Loop_2ms();
		S_cnt_2ms=0;
	}
	if(S_cnt_5ms>=5){
		Years_Loop_5ms();
		S_cnt_5ms=0;
	}
	if(S_cnt_10ms>=10){
		Years_Loop_10ms();
		S_cnt_10ms=0;
	}
	if(S_cnt_20ms>=20){
		Years_Loop_20ms();
		S_cnt_20ms=0;
	}
}





