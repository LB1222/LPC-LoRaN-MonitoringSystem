/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.c
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯，配合新建工程使用，非完整文件
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2019-08-02 waroyal  正式发布
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"


void bsp_InitLed(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	/*打开GOIO时钟*/
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*推免*/
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}
void bsp_InitBeep(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	/*打开GPIO时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*配置蜂鸣器GPIO为推挽输出模式
   由于将GPIO设置为输出时，GPIO输出寄存器的值缺省是0，不会驱动蜂鸣器鸣叫	
	*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
	
	
}

void bsp_LedOn(uint8_t _no)
{
	if(_no == 1)
	{
		LED0 = 0;
	}
	else if(_no == 2)
	{
		LED1 = 0;
	}
}
	
void bsp_LedOff(uint8_t _no)
{
	if(_no == 1)
	{
		LED0 = 1;
	}
	else if(_no == 2)
	{
		LED1 = 1;
	}
}

void bsp_BeepOn(void)
{
	BEEP = 0;
}

void bsp_BeepOff(void)
{
	BEEP = 1;
}

void bsp_BeepToggle(void)//翻转蜂鸣器
{
	BEEP_GPIO_PORT->ODR ^= BEEP_GPIO_PIN;
}

uint8_t bsp_IsBeepOn(void)
{
	if((BEEP_GPIO_PORT->ODR&BEEP_GPIO_PIN) == BEEP_GPIO_PIN)
	{
		return 1;
	}
	return 0;
}

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
