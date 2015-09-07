#ifndef __BOARD_H__
#define __BOARD_H__
#include "stm32f10x.h"
#include "Years_LED.h"
#include "Years_SPI.h"
#include "Years_Nrf24l01.h"
#include "Years_Uart.h"
#include "Years_USB_HID.h"



/*******************LED GPIO定义******************/
#define LED_RCC      RCC_APB2Periph_GPIOB
#define LED_GPIO     GPIOB
#define LED_A        GPIO_Pin_12
#define LED_B				 GPIO_Pin_13
/*************************************************/
/*******************KEY GPIO定义******************/
#define KEY_RCC      RCC_APB2Periph_GPIOC
#define KEY_GPIO     GPIOC
#define KEY_A        GPIO_Pin_0
#define KEY_B        GPIO_Pin_1
#define KEY_C        GPIO_Pin_2
#define KEY_D        GPIO_Pin_0
#define KEY_ON	0
#define KEY_OFF	1
/*************************************************/
/***************UART1 GPIO定义******************/
#define ANO_RCC_UART1			RCC_APB2Periph_GPIOB
#define ANO_GPIO_UART1		GPIOB
#define ANO_UART1_Pin_TX	GPIO_Pin_6
#define ANO_UART1_Pin_RX	GPIO_Pin_7
/*********************************************/
/********************SPI GPIO定义*****************/
#define Years_GPIO_SPI    GPIOB
#define Years_GPIO_CE     GPIOB
#define RCC_GPIO_SPI      RCC_APB2Periph_GPIOB
#define RCC_GPIO_CE       RCC_APB2Periph_GPIOA
#define SPI_Pin_CSN			  GPIO_Pin_7
#define SPI_Pin_SCK				GPIO_Pin_3
#define SPI_Pin_MISO			GPIO_Pin_4
#define SPI_Pin_MOSI			GPIO_Pin_5
#define SPI_Pin_CE				GPIO_Pin_8
/**************************************************/
/*****************硬件中断优先级*******************/
#define NVIC_UART_P	5
#define NVIC_UART_S	1
/**************************************************/
extern uint8_t 	NRF_ENABLE;
extern uint8_t 	UART1_ENABLE;


extern uint16_t S_cnt_1ms,S_cnt_2ms,S_cnt_5ms,S_cnt_10ms,S_cnt_20ms;

void Delay(vu32 nCount);
void cycleCounterInit(void);
void SysTick_IRQ(void);

#endif 
