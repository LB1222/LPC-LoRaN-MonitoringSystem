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
*		V1.0    2023-08-21  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"


/*
*********************************************************************************************************
*	函 数 名: bsp_InitLed
*	功能说明: 配置LED指示灯相关的GPIO,  该函数被 bsp_Init() 调用。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 打开GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_ALL_LED, ENABLE);
	

	
	//GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* 推挽输出模式 */
	
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_PIN;
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);
	
}



/*
*********************************************************************************************************
*	函 数 名: bsp_LedToggle
*	功能说明: 翻转指定的LED指示灯。
*	形    参:  _no : 指示灯序号，范围 1 - 2
*	返 回 值: 无
*********************************************************************************************************
*/
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
void bsp_LedToggle(uint8_t _no)
{
	if (_no == 1)
	{
		LED0_GPIO_PORT->ODR ^= LED0_GPIO_PIN;
	}
	else if(_no == 2)
	{
		LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN;
	}
}

uint8_t bsp_IsLedOn(uint8_t _no)
{
	if(_no == 1)
	{
		if((LED0_GPIO_PORT->ODR & LED0_GPIO_PIN) == LED0_GPIO_PIN)
		{
			return 1;
		}
		return 0;
	}
	else if (_no == 2)
	{
		if((LED1_GPIO_PORT->ODR & LED1_GPIO_PIN)== LED1_GPIO_PIN)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}



/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
