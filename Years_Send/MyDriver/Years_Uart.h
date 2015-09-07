#ifndef __YEARS_UART_H__
#define __YEARS_UART_H__

#include "stm32f10x.h"
#include "board.h"

void Uart1_Init(u32 br_num);
void Uart1_DeInit(void);
void Uart1_IRQ(void);
void Uart1_Put_String(unsigned char *Str);
void Uart1_Put_Buf(unsigned char *DataToSend , u8 data_num);

#endif
