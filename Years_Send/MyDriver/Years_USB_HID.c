/******************** (C) COPYRIGHT 2014 ANO Tech ***************************
 * ����		 ��Years
 * �ļ���  ��Years_USB_HID.c
 * ����    ��USBͨ��
 * ����    ��791276337@qq.com
 * ��ע    ����
 * ����    ��2015.8.23
*****************************************************************************/
#include "Years_USB_HID.h"
#include "board.h"

u8 Hid_RxData[63];

void USB_HID_Init(void)
{
	USB_GPIO_Configuration();
	USB_Interrupts_Config();
	Set_USBClock();    
	USB_Init();
	USB_ReceiveFlg = FALSE;
	USB_Connect(FALSE);//�������Ӳ������usb
	Delay(100);
	USB_Connect(TRUE);
}

void USB_SendString(u8 *str)
{
     u8 ii=0;   
     while(*str)
     {
         Transi_Buffer[ii++]=*(str++);
         if (ii == SendLength) break;
     }
     UserToPMABufferCopy(Transi_Buffer, ENDP2_TXADDR, SendLength);
     SetEPTxValid(ENDP2);
}

