/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * ����		 ��Years
 * �ļ���  ��Years_KEY.c
 * ����    ��KEY
 * ����    ��791276337@qq.com
 * ��ע    ����
 * ����    ��2015.9.5
*****************************************************************************/
#include "Years_KEY.h"
#include "board.h"
#include "config.h"

/*static void Delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} */

void Years_KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڣ�PC����ʱ��*/
	RCC_APB2PeriphClockCmd(KEY_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY_A|KEY_B|KEY_C|KEY_D; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(KEY_GPIO, &GPIO_InitStructure);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*��ʱ����*/
		//Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*�ȴ������ͷ� */
			while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			return 	KEY_ON;	 
		}
		else
			return KEY_OFF;
	}
	else
		return KEY_OFF;
}

void Key_Event(void)
{
	if( Key_Scan(GPIOC,GPIO_Pin_0) == KEY_ON  )//  һ����ͣ��ť
		{
				Years_LEDB_OFF();
		}
	
		if( Key_Scan(GPIOC,GPIO_Pin_1) == KEY_ON  )//������ť
		{
				Years_LEDB_ON();
		} 
		if( Key_Scan(GPIOC,GPIO_Pin_2) == KEY_ON  )//����ɲͣ��ť
		{
			
		} 
		if( Key_Scan(GPIOC,GPIO_Pin_3) == KEY_ON  )//  �ƹ�ָʾ��ť
		{
				
		} 
	
	}



