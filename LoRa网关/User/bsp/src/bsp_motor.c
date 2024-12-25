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
*		V1.0    2023-07-15   刘斌  正式发布
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#include "bsp.h"




//void bsp_InitMotor(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStruct;
//    // 使能GPIOA和GPIOB的时钟
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

//    // 设置PA0、PA1、PB14引脚为输出模式
//   
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_11;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStruct);

//	
//	
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14| GPIO_Pin_6| GPIO_Pin_7;
//		 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//}

void bsp_MotorFront(void)
{
     MOTOR1=1;
     MOTOR2=0;
     MOTOR3=1;
     MOTOR4=0;
     MOTOR5=0;
     MOTOR6=1;	
	   MOTOR7=1;
     MOTOR8=0;

}


//后退
void bsp_Motorback(void)
{
     MOTOR1=0;
     MOTOR2=1;
     MOTOR3=0;
     MOTOR4=1;
     MOTOR5=1;
     MOTOR6=0;	
	   MOTOR7=0;
     MOTOR8=1;

}


//右转
void bsp_Motorright(void)
{
     MOTOR1=0;
     MOTOR2=1;
     MOTOR3=0;
     MOTOR4=1;
     MOTOR5=0;
     MOTOR6=1;	
	   MOTOR7=1;
     MOTOR8=0;

}


//左转
void bsp_Motorleft(void)
{
     MOTOR1=1;
     MOTOR2=0;
     MOTOR3=1;
     MOTOR4=0;
     MOTOR5=1;
     MOTOR6=0;	
	   MOTOR7=0;
     MOTOR8=1;

}

//刹车
void bsp_Motorstop(void)
{
     MOTOR1=1;
     MOTOR2=1;
     MOTOR3=1;
     MOTOR4=1;
     MOTOR5=1;
     MOTOR6=1;	
	   MOTOR7=1;
     MOTOR8=1;

}



