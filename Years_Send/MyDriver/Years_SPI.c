/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * ����		 ��Years
 * �ļ���  ��Years_Schedule.c
 * ����    ����ʱ��������
 * ����    ��791276337@qq.com
 * ��ע    ����
 * ����    ��2015.8.23
*****************************************************************************/
#include "Years_SPI.h"
#include "board.h"

void Years_SPI_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_GPIO_SPI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_GPIO_CE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE); 
	
	/*���� SPI_NRF_SPI�� SCK,MISO,MOSI���� */ 
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_SCK| SPI_Pin_MISO| SPI_Pin_MOSI; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù��� 
	GPIO_Init(Years_GPIO_SPI, &GPIO_InitStructure);
	/*����SPI_NRF_SPI��CE���ţ���SPI_NRF_SPI�� CSN ����:*/
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_CE; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(Years_GPIO_CE, &GPIO_InitStructure);           //AAAAAA
	
	GPIO_InitStructure.GPIO_Pin = SPI_Pin_CSN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(Years_GPIO_SPI, &GPIO_InitStructure);	
	
	GPIO_SetBits(Years_GPIO_SPI, SPI_Pin_CSN);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��ȫ˫�� 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //��ģʽ 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //���ݴ�С8λ 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //ʱ�Ӽ��ԣ�����ʱΪ�� 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //��1��������Ч��������Ϊ����ʱ�� 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS�ź���������� 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //4��Ƶ��9MHz 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //��λ��ǰ 
	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	SPI_Init(SPI3, &SPI_InitStructure); 
	/* Enable SPI2 */ 
	SPI_Cmd(SPI3, ENABLE);
	
}

u8 Years_SPI_RW(u8 dat) 
{ 
	/* �� SPI���ͻ������ǿ�ʱ�ȴ� */ 
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET); 
	/* ͨ�� SPI2����һ�ֽ����� */ 
	SPI_I2S_SendData(SPI3, dat); 
	/* ��SPI���ջ�����Ϊ��ʱ�ȴ� */ 
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET); 
	/* Return the byte read from the SPI bus */ 
	return SPI_I2S_ReceiveData(SPI3); 
}

void Years_SPI_CE_H(void)
{
	GPIO_SetBits(Years_GPIO_CE, SPI_Pin_CE);
}

void Years_SPI_CE_L(void)
{
	GPIO_ResetBits(Years_GPIO_CE, SPI_Pin_CE);
}

void Years_SPI_CSN_H(void)
{
	GPIO_SetBits(Years_GPIO_SPI, SPI_Pin_CSN);
}

void Years_SPI_CSN_L(void)
{
	GPIO_ResetBits(Years_GPIO_SPI, SPI_Pin_CSN);
}






















