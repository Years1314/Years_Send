/*
�����[   �����[���������������[ �����������[ �������������[ ���������������[
�^�����[ �����X�a�����X�T�T�T�T�a�����X�T�T�����[�����X�T�T�����[�����X�T�T�T�T�a
 �^���������X�a �����������[  ���������������U�������������X�a���������������[
  �^�����X�a  �����X�T�T�a  �����X�T�T�����U�����X�T�T�����[�^�T�T�T�T�����U
   �����U   ���������������[�����U  �����U�����U  �����U���������������U
   �^�T�a   �^�T�T�T�T�T�T�a�^�T�a  �^�T�a�^�T�a  �^�T�a�^�T�T�T�T�T�T�a                                        
*/
/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * ����		 ��Years
 * �ļ���  ��msin.c
 * ����    ��main
 * ����    ��791276337@qq.com
 * ��ע    ��������
 * ����    ��2015.8.23
*****************************************************************************/
																											 
#include "config.h"
uint8_t NRF_ENABLE=0;
uint8_t UART1_ENABLE=0;
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);    //�ж����ȼ�
	Years_LED_Init();
	Years_LEDA_Twinkle();
	Years_KEY_Init();
	USB_HID_Init();
	Uart1_Init(500000);
	UART1_ENABLE = 1;
	//�δ�ʱ����ʼ��
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
