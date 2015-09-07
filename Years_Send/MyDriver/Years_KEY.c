/******************** (C) COPYRIGHT 2014 Years Studio ***************************
 * 作者		 ：Years
 * 文件名  ：Years_KEY.c
 * 描述    ：KEY
 * 邮箱    ：791276337@qq.com
 * 备注    ：无
 * 日期    ：2015.9.5
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
	
	/*开启按键端口（PC）的时钟*/
	RCC_APB2PeriphClockCmd(KEY_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = KEY_A|KEY_B|KEY_C|KEY_D; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_Init(KEY_GPIO, &GPIO_InitStructure);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	{	   
		/*延时消抖*/
		//Delay(10000);		
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
		{	 
			/*等待按键释放 */
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
	if( Key_Scan(GPIOC,GPIO_Pin_0) == KEY_ON  )//  一键悬停按钮
		{
				Years_LEDB_OFF();
		}
	
		if( Key_Scan(GPIOC,GPIO_Pin_1) == KEY_ON  )//解锁按钮
		{
				Years_LEDB_ON();
		} 
		if( Key_Scan(GPIOC,GPIO_Pin_2) == KEY_ON  )//紧急刹停按钮
		{
			
		} 
		if( Key_Scan(GPIOC,GPIO_Pin_3) == KEY_ON  )//  灯光指示按钮
		{
				
		} 
	
	}



