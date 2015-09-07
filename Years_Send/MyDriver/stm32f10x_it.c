#include "stm32f10x_it.h"
#include "board.h"
#include "usb_istr.h"


void USART1_IRQHandler(void)  //串口中断函数
{
	Uart1_IRQ();
}

void TIM3_IRQHandler(void)		//0.5ms中断一次
{	

}

void NMI_Handler(void)
{
}


void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	SysTick_IRQ();
}
void USB_HP_CAN1_TX_IRQHandler(void)//USB_HP_CAN1_TX_IRQHandler
{
}
void USB_LP_CAN1_RX0_IRQHandler(void)//USB_LP_CAN1_RX0_IRQHandler 在这吃大亏啦，启动代码里面带1，这个不带，
{
    USB_Istr();
}

