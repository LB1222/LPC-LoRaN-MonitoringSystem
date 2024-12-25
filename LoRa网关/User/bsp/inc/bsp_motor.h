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

#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "sys.h"


#ifdef WSNEP_V01
//RH+

#define MOTOR1_GPIO_PIN			GPIO_Pin_11					//BEEP引脚号
#define MOTOR1_PIN_ID				11									//BEEP引脚序号
#define MOTOR1_GPIO_PORT		GPIOA								//BEEP端口号
#define MOTOR1_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define MOTOR1_FUN_OUT			PAout								//BEEP输出端口配置函数

/////////////////////////////////////////////////////////////////////////////////////////////////

//RH-
#define MOTOR2_GPIO_PIN			GPIO_Pin_7					//BEEP引脚号
#define MOTOR2_PIN_ID				7									//BEEP引脚序号
#define MOTOR2_GPIO_PORT		GPIOB								//BEEP端口号
#define MOTOR2_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEP时钟
#define MOTOR2_FUN_OUT			PBout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//RQ+
#define MOTOR3_GPIO_PIN			GPIO_Pin_6					//BEEP引脚号
#define MOTOR3_PIN_ID				6									//BEEP引脚序号
#define MOTOR3_GPIO_PORT		GPIOB								//BEEP端口号
#define MOTOR3_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEP时钟
#define MOTOR3_FUN_OUT			PBout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//RQ-
#define MOTOR4_GPIO_PIN			GPIO_Pin_14					//BEEP引脚号
#define MOTOR4_PIN_ID				14									//BEEP引脚序号
#define MOTOR4_GPIO_PORT		GPIOB								//BEEP端口号
#define MOTOR4_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEP时钟
#define MOTOR4_FUN_OUT			PBout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//LQ+
#define MOTOR5_GPIO_PIN			GPIO_Pin_0					//BEEP引脚号
#define MOTOR5_PIN_ID				0									//BEEP引脚序号
#define MOTOR5_GPIO_PORT		GPIOA								//BEEP端口号
#define MOTOR5_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define MOTOR5_FUN_OUT			PAout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//LQ-
#define MOTOR6_GPIO_PIN			GPIO_Pin_1					//BEEP引脚号
#define MOTOR6_PIN_ID				1									//BEEP引脚序号
#define MOTOR6_GPIO_PORT		GPIOA								//BEEP端口号
#define MOTOR6_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define MOTOR6_FUN_OUT			PAout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//LH+
#define MOTOR7_GPIO_PIN			GPIO_Pin_2					//BEEP引脚号
#define MOTOR7_PIN_ID				2									//BEEP引脚序号
#define MOTOR7_GPIO_PORT		GPIOA								//BEEP端口号
#define MOTOR7_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define MOTOR7_FUN_OUT			PAout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//LH-
#define MOTOR8_GPIO_PIN			GPIO_Pin_3					//BEEP引脚号
#define MOTOR8_PIN_ID				3									//BEEP引脚序号
#define MOTOR8_GPIO_PORT		GPIOA								//BEEP端口号
#define MOTOR8_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEP时钟
#define MOTOR8_FUN_OUT			PAout								//BEEP输出端口配置函数
/////////////////////////////////////////////////////////////////////////////////////////////////

//IO操作函数	 
#define MOTOR1    MOTOR1_FUN_OUT(MOTOR1_PIN_ID) //MOTOR1
#define MOTOR2    MOTOR2_FUN_OUT(MOTOR2_PIN_ID) //MOTOR2
#define MOTOR3    MOTOR3_FUN_OUT(MOTOR3_PIN_ID) //MOTOR3
#define MOTOR4    MOTOR4_FUN_OUT(MOTOR4_PIN_ID) //MOTOR4
#define MOTOR5    MOTOR5_FUN_OUT(MOTOR5_PIN_ID) //MOTOR5
#define MOTOR6    MOTOR6_FUN_OUT(MOTOR6_PIN_ID) //MOTOR6
#define MOTOR7    MOTOR7_FUN_OUT(MOTOR7_PIN_ID) //MOTOR7
#define MOTOR8    MOTOR8_FUN_OUT(MOTOR8_PIN_ID) //MOTOR8

#endif

/* 供外部调用的函数声明 */
void bsp_InitMotor(void);

void bsp_MotorFront(void);

void bsp_MotorFront(void);
//后退
void bsp_Motorback(void);

//右转
void bsp_Motorright(void);

//左转
void bsp_Motorleft(void);

//刹车
void bsp_Motorstop(void);


#endif


