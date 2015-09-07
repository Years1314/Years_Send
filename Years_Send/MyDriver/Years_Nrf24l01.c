/******************** (C) COPYRIGHT 2014 Years Tech ***************************
 * ����		 ��Years
 * �ļ���  ��Years_Nrf24l01.c
 * ����    ������ģ��
 * ����    ��791276337@qq.com
 * ��ע    ����
 * ����    ��2015.8.23
*****************************************************************************/
#include "Years_Nrf24l01.h"

//***************************************NRF24L01�Ĵ���ָ��*******************************************************
#define NRF_READ_REG        0x00  	// ���Ĵ���ָ��
#define NRF_WRITE_REG       0x20 	// д�Ĵ���ָ��
#define R_RX_PL_WID   	0x60
#define RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0  	// д��������ָ��
#define FLUSH_TX        0xE1 	// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NOP             0xFF  	// ����
//*************************************SPI(nRF24L01)�Ĵ�����ַ****************************************************
#define CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RXADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ�������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define NRFRegSTATUS    0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��1�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��2�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��3�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��4�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��5�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������
//**************************************************************************************
//*********************************************NRF24L01*************************************
#define RX_DR				6		//�жϱ�־
#define TX_DS				5
#define MAX_RT			4

u8	TX_ADDRESS[TX_ADR_WIDTH] = {0xAA,0xBB,0xCC,0x00,0x01};	//���ص�ַ
u8	RX_ADDRESS[RX_ADR_WIDTH] = {0xAA,0xBB,0xCC,0x00,0x01};	//���յ�ַ	
	
uint8_t NRF24L01_2_RXDATA[RX_PLOAD_WIDTH];//nrf24l01���յ�������
uint8_t NRF24L01_2_TXDATA[RX_PLOAD_WIDTH];//nrf24l01��Ҫ���͵�����
/*
*****************************************************************
* д�Ĵ���
*****************************************************************
*/
uint8_t Years_NRF_Write_Reg(uint8_t reg, uint8_t value)
{
	uint8_t status;
	Years_SPI_CSN_L();					  /* ѡͨ���� */
	status = Years_SPI_RW(reg);  /* д�Ĵ�����ַ */
	Years_SPI_RW(value);		  /* д���� */
	Years_SPI_CSN_H();					  /* ��ֹ������ */
  return 	status;
}
/*
*****************************************************************
* ���Ĵ���
*****************************************************************
*/
uint8_t Years_NRF_Read_Reg(uint8_t reg)
{
	uint8_t reg_val;
	Years_SPI_CSN_L();					  /* ѡͨ���� */
	Years_SPI_RW(reg);			  /* д�Ĵ�����ַ */
	reg_val = Years_SPI_RW(0);	  /* ��ȡ�üĴ����������� */
	Years_SPI_CSN_H();					  /* ��ֹ������ */
   return 	reg_val;
}
	
/*
*****************************************************************
*
* д������
*
*****************************************************************
*/
uint8_t Years_NRF_Write_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars)
{
	uint8_t i;
	uint8_t status;
	Years_SPI_CSN_L();				        /* ѡͨ���� */
	status = Years_SPI_RW(reg);	/* д�Ĵ�����ַ */
	for(i=0; i<uchars; i++)
	{
		Years_SPI_RW(pBuf[i]);		/* д���� */
	}
	Years_SPI_CSN_H();						/* ��ֹ������ */
    return 	status;	
}
/*
*****************************************************************
* ��������
*****************************************************************
*/
uint8_t Years_NRF_Read_Buf(uint8_t reg, uint8_t *pBuf, uint8_t uchars)
{
	uint8_t i;
	uint8_t status;
	Years_SPI_CSN_L();						/* ѡͨ���� */
	status = Years_SPI_RW(reg);	/* д�Ĵ�����ַ */
	for(i=0; i<uchars; i++)
	{
		pBuf[i] = Years_SPI_RW(0); /* ��ȡ�������� */ 	
	}
	Years_SPI_CSN_H();						/* ��ֹ������ */
    return 	status;
}


void Years_NRF_TxPacket(uint8_t * tx_buf, uint8_t len)
{	
	Years_SPI_CE_L();		 //StandBy Iģʽ	
	Years_NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // װ�ؽ��ն˵�ַ
	Years_NRF_Write_Buf(WR_TX_PLOAD, tx_buf, len); 			 // װ������	
	Years_SPI_CE_H();		 //�ø�CE���������ݷ���
}

void Years_NRF_TxPacket_AP(uint8_t * tx_buf, uint8_t len)
{	
	Years_SPI_CE_L();		 //StandBy Iģʽ	
	Years_NRF_Write_Buf(0xa8, tx_buf, len); 			 // װ������
	Years_SPI_CE_H();		 //�ø�CE
}



void Years_NRF_Init(u8 model, u8 ch)
{

	Years_SPI_CE_L();
	Years_NRF_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);	//дRX�ڵ��ַ 
	Years_NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH); 		//дTX�ڵ��ַ  
	Years_NRF_Write_Reg(NRF_WRITE_REG+EN_AA,0x01); 													//ʹ��ͨ��0���Զ�Ӧ�� 
	Years_NRF_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);											//ʹ��ͨ��0�Ľ��յ�ַ 
	Years_NRF_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);											//�����Զ��ط����ʱ��:500us;����Զ��ط�����:10�� 2M��������
	Years_NRF_Write_Reg(NRF_WRITE_REG+RF_CH,ch);														//����RFͨ��ΪCHANAL
	Years_NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f); 												//����TX�������,0db����,2Mbps,���������濪��
	//Write_Reg(NRF_WRITE_REG+RF_SETUP,0x07); 												//����TX�������,0db����,1Mbps,���������濪��
	//Write_Reg(NRF_WRITE_REG+RF_SETUP,0x27); 												//����TX�������,0db����,250Kbps,���������濪��
/////////////////////////////////////////////////////////
	if(model==1)				//RX
	{
		Years_NRF_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//ѡ��ͨ��0����Ч���ݿ�� 
		Years_NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ�շ�����жϿ���,16λCRC,������
	}
	else if(model==2)		//TX
	{
		Years_NRF_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//ѡ��ͨ��0����Ч���ݿ�� 
		Years_NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����жϿ���,16λCRC,������
	}
	else if(model==3)		//RX2
	{
		Years_NRF_Write_Reg(FLUSH_TX,0xff);
		Years_NRF_Write_Reg(FLUSH_RX,0xff);
		Years_NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ�շ�����жϿ���,16λCRC,������
		
		Years_SPI_RW(0x50);
		Years_SPI_RW(0x73);
		Years_NRF_Write_Reg(NRF_WRITE_REG+0x1c,0x01);
		Years_NRF_Write_Reg(NRF_WRITE_REG+0x1d,0x06);
	}
	else								//TX2
	{
		Years_NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����жϿ���,16λCRC,������
		Years_NRF_Write_Reg(FLUSH_TX,0xff);
		Years_NRF_Write_Reg(FLUSH_RX,0xff);
		
		Years_SPI_RW(0x50);
		Years_SPI_RW(0x73);
		Years_NRF_Write_Reg(NRF_WRITE_REG+0x1c,0x01);
		Years_NRF_Write_Reg(NRF_WRITE_REG+0x1d,0x06);
	}
	Years_SPI_CE_H();
}

uint8_t Years_NRF_Check(void)
{ 
	u8 buf1[5]; 
	u8 i; 
	/*д��5���ֽڵĵ�ַ. */ 
	Years_NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADDRESS,5); 
	/*����д��ĵ�ַ */ 
	Years_NRF_Read_Buf(TX_ADDR,buf1,5); 
	/*�Ƚ�*/ 
	for(i=0;i<5;i++) 
	{ 
		if(buf1[i]!=TX_ADDRESS[i]) 
			break; 
	} 
	if(i==5)
		return 1; //MCU��NRF�ɹ����� 
	else
		return 0; //MCU��NRF���������� 
}

void Years_NRF_Check_Event(void)
{
	//���Ĵ���  
	u8 sta = Years_NRF_Read_Reg(NRF_READ_REG + NRFRegSTATUS);  // 0x00 ���Ĵ���    0x07״̬�Ĵ���  ��������
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<RX_DR))     //  6  �жϱ�־
	{
		u8 rx_len = Years_NRF_Read_Reg(R_RX_PL_WID);  //  0x60    ��ȡ�ֽڳ���
		if(rx_len<33)
		{
			// ��������
			Years_NRF_Read_Buf(RD_RX_PLOAD,NRF24L01_2_RXDATA,rx_len);// read receive payload from RX_FIFO buffer 0x61 ��ȡ��������ָ��
			Years_LEDB_OFF();
			//RemotePutRxBuf(unsigned char *RxBuf,u8 data_num);
			
		}
		else 
		{
			Years_NRF_Write_Reg(FLUSH_RX,0xff);//��ջ�����
		}
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<TX_DS))
	{
		
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	if(sta & (1<<MAX_RT))
	{
		if(sta & 0x01)	//TX FIFO FULL
		{
			Years_NRF_Write_Reg(FLUSH_TX,0xff);//��ջ�����
		}
	}
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	Years_NRF_Write_Reg(NRF_WRITE_REG + NRFRegSTATUS, sta);   //0x20 д�Ĵ���ָ��     0x07״̬�Ĵ���
}
































