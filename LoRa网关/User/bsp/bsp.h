/*
*********************************************************************************************************
*
*	模块名称 : BSP模块
*	文件名称 : bsp.h
*	说    明 : 这是底层驱动模块所有的h文件的汇总文件。 应用程序只需 #include bsp.h 即可，
*			  不需要#include 每个模块的 h 文件
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#ifndef _BSP_H_
#define _BSP_H_


/* 定义 BSP 版本号 */
#define __STM32F1_BSP_VERSION		"1.1"

/* CPU空闲时执行的函数 */
//#define CPU_IDLE()		bsp_Idle()

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/* 这个宏仅用于调试阶段排错 */
//#define BSP_Printf		printf
#define BSP_Printf(...)

//#include "stm32f10x.h"
#include "sys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* 按需增加头文件区域 START OF AREA*/

#include "bsp_led.h"
#include "bsp_timer.h"
//#include "bsp_uart.h"
#include "bsp_date.h"
#include "MqttKit.h"
#include "onenet.h"
#include "Common.h"
#include "usart.h"
#include "esp8266.h"
#include "cJSON.h"
#include "OLED.h"
#include "bsp_i2c.h"

/* 按需增加头文件区域 END OF AREA */
#define 	BEEP		BEEP_FUN_OUT(BEEP_PIN_ID)//BEEP

/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void bsp_Idle(void);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);





#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
