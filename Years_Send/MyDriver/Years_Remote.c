/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * 作者		 ：Years
 * 文件名  ：Years_Remote.c
 * 描述    ：Remote
 * 邮箱    ：791276337@qq.com
 * 备注    ：无
 * 日期    ：2015.8.23
*****************************************************************************/
#include "Years_Remote.h"
#include "Config.h"
u8 Rx_Buffer[32];
u8 Tx_Buffer[32];

void RemotePutRxBuf(unsigned char *RxBuf,u8 data_num)
{
	for(u8 i=0;i<data_num;i++)
		Rx_Buffer[i]=*(RxBuf+i);
	}

void Remote_Send(void)
	{
		Years_LEDA_OFF();
		Years_NRF_TxPacket(Tx_Buffer,32);
		}
