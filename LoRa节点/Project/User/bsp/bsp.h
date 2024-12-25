/*
*********************************************************************************************************
*
*	模块名称 : BSP模块
*	文件名称 : bsp.h
*	说    明 : 这是底层驱动模块所有的h文件的汇总文件。 应用程序只需 #include bsp.h 即可，
*			  不需要#include 每个模块的 h 文件
*
*	
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

#include "stm32f10x.h"
#include "sys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "time.h"


#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/* 按需增加头文件区域 START OF AREA*/

#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "bsp_timer.h"
#include "OLED.h"
#include "bsp_adc.h"
#include "bsp_i2c.h"
#include "bsp_Gps.h"
#include "bsp_Co2.h"
#include "usart.h"
#include "bsp_dateanalysis.h"
#include "bsp_dateupload.h"
#include "bsp_powermanage.h"
#include "bsp_Modifyregister.h"


/* 按需增加头文件区域 END OF AREA */


/* 提供给其他C文件调用的函数 */
void bsp_Init(void);
void bsp_Idle(void);

void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);

#endif

/***************************** 德致伦电子 DeZLinc (END OF FILE) *********************************/
