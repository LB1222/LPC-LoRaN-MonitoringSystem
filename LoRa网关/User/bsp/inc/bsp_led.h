/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_led.h
*	版    本 : V1.0
*	说    明 : 头文件，配合新建工程使用，非完整文件
*
*	Copyright (C), 2014-2019, 德致伦电子
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






#define LED0_GPIO_PIN		GPIO_Pin_9				//LED0òy??o?
#define LED0_PIN_ID			9						//LED0òy??Dòo?
#define LED0_GPIO_PORT		GPIOB					//LED0???úo?
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0ê±?ó
#define LED0_FUN_OUT		PBout					//LED0ê?3????ú????oˉêy
//#define LED0_FUN_IN			PBin					//LED0ê?è????ú????oˉêy

#define LED1_GPIO_PIN		GPIO_Pin_12				//LED0òy??o?
#define LED1_PIN_ID			12						//LED0òy??Dòo?
#define LED1_GPIO_PORT		GPIOB					//LED0???úo?
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0ê±?ó
#define LED1_FUN_OUT		PBout					//LED0ê?3????ú????oˉêy
//#define LED0_FUN_IN			PBin					//LED0ê?è????ú????oˉêy


#define BEEP_GPIO_PIN			GPIO_Pin_8					//BEEP引脚号
#define BEEP_PIN_ID				8									//BEEP引脚序号
#define BEEP_GPIO_PORT		GPIOA								//BEEP端口号
#define BEEP_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define BEEP_FUN_OUT			PAout								//BEEP输出端口配置函数
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////


//IO2ù×÷oˉêy	 
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0
#define LED1    LED1_FUN_OUT(LED1_PIN_ID) //LED1
#define BEEP    BEEP_FUN_OUT(BEEP_PIN_ID) //LED1
                


/* 供外部调用的函数声明 */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);

void bsp_BeepOn(void);
void bsp_BeepOff(void);


#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
