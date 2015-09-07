/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V2.2.1
* Date               : 09/22/2008
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "Years_USB_HID.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u8 Transi_Buffer[SendLength];
u8 USB_ReceiveFlg = FALSE;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void EP1_OUT_Callback(void)//stm32��������ɣ��жϾͻ�������������
{
		PMAToUserBufferCopy(Hid_RxData, ENDP1_RXADDR,64);
		USB_ReceiveFlg = TRUE;
		SetEPRxStatus(ENDP1, EP_RX_VALID);
}

void EP2_IN_Callback(void)//stm32����������ɣ�Ҳ����������������жϷ�����������ֻ����ջ�����
{
     u8 ii;
     for (ii=0;ii<SendLength;ii++) Transi_Buffer[ii] = 0x00;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

