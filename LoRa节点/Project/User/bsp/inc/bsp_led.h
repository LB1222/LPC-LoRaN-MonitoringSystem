/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件，配合新建工程使用，非完整文件
*
*	
*
*********************************************************************************************************
*/

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "sys.h"



///////////////////////////////////////////////////////////
//移植修改区
//按照实际端口修改
//较前版本更加容易移植(注意，端口仅仅适用于非JTAG/SWD引脚，如果是JTAG引脚，需要打开AFIO时钟，并失能JTAG)



#ifdef WSNEP_V01

#define RCC_ALL_LED 	( LED0_GPIO_CLK | LED1_GPIO_CLK)

#define LED0_GPIO_PIN		GPIO_Pin_13				//LED0引脚号
#define LED0_PIN_ID			13						//LED0引脚序号
#define LED0_GPIO_PORT		GPIOC					//LED0端口号
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOC	//LED0时钟
#define LED0_FUN_OUT		PCout					//LED0输出端口配置函数
//#define LED0_FUN_IN			PBin					//LED0输入端口配置函数

#define LED1_GPIO_PIN		GPIO_Pin_5				//LED0引脚号
#define LED1_PIN_ID			5						//LED0引脚序号
#define LED1_GPIO_PORT		GPIOE					//LED0端口号
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOE	//LED0时钟
#define LED1_FUN_OUT		PBout					//LED0输出端口配置函数
//#define LED0_FUN_IN			PBin					//LED0输入端口配置函数

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////


//IO操作函数	 
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0
#define LED1    LED0_FUN_OUT(LED1_PIN_ID) //LED1



/* 供外部调用的函数声明 */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);
void bsp_LedToggle(uint8_t _no);
uint8_t bsp_IsLedOn(uint8_t _no);

#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
