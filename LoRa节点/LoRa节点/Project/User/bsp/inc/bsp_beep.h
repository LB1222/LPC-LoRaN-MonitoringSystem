/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_beep.h
*	版    本 : V1.0
*	说    明 : 头文件，配合新建工程使用，非完整文件
*
*	
*
*********************************************************************************************************
*/


#ifndef __BSP_BEEP_H
#define __BSP_BEEP_H

#include "sys.h"

#define RCC_ALL_BEEP (BEEP_GPIO_CLK)

#define BEEP_GPIO_PIN  GPIO_Pin_8  //BEEP引脚号
#define BEEP_PIN_ID    8           //BEEP引脚序号
#define BEEP_GPIO_PORT  GPIOA       //BEEP端口号
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOA  //BEEP时钟
#define BEEP_FUN_OUT PAout          //BEEP输出端口配置函数
//#define BEEP_FUN_IN  PGin            //BEEP输入端口配置函数

//IO 操作函数
#define BEEP  BEEP_FUN_OUT(BEEP_PIN_ID)//BEEP

/*供外部调用的函数声明 */
void bsp_InitBeep(void);
void bsp_BeepOn(void );
void bsp_BeepOff(void);
void bsp_BeepToggle(void);
uint8_t bsp_IsBeepOn(void);



#endif

