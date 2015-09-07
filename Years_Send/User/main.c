/*
██╗   ██╗███████╗ █████╗ ██████╗ ███████╗
╚██╗ ██╔╝██╔════╝██╔══██╗██╔══██╗██╔════╝
 ╚████╔╝ █████╗  ███████║██████╔╝███████╗
  ╚██╔╝  ██╔══╝  ██╔══██║██╔══██╗╚════██║
   ██║   ███████╗██║  ██║██║  ██║███████║
   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝                                        
*/
/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * 作者		 ：Years
 * 文件名  ：msin.c
 * 描述    ：main
 * 邮箱    ：791276337@qq.com
 * 备注    ：主程序
 * 日期    ：2015.8.23
*****************************************************************************/
																											 
#include "config.h"
uint8_t NRF_ENABLE=0;
uint8_t UART1_ENABLE=0;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);    //中断优先级
	Years_LED_Init();
	Years_LEDA_Twinkle();
	Years_KEY_Init();
	USB_HID_Init();
	Uart1_Init(500000);
	UART1_ENABLE = 1;
	//滴答定时器初始化
	cycleCounterInit();
	SysTick_Config(SystemCoreClock / 1000);
	
	Years_SPI_Init();
	NRF_ENABLE=Years_NRF_Check();
	if(NRF_ENABLE)
		Years_NRF_Init(MODEL_TX2,80);
		
	while(1)
	{
		Years_Loop();
	}
}
