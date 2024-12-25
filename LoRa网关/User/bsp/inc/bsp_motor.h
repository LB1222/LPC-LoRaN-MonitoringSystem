/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�������½�����ʹ�ã��������ļ�
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H

#include "sys.h"


#ifdef WSNEP_V01
//RH+

#define MOTOR1_GPIO_PIN			GPIO_Pin_11					//BEEP���ź�
#define MOTOR1_PIN_ID				11									//BEEP�������
#define MOTOR1_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define MOTOR1_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define MOTOR1_FUN_OUT			PAout								//BEEP����˿����ú���

/////////////////////////////////////////////////////////////////////////////////////////////////

//RH-
#define MOTOR2_GPIO_PIN			GPIO_Pin_7					//BEEP���ź�
#define MOTOR2_PIN_ID				7									//BEEP�������
#define MOTOR2_GPIO_PORT		GPIOB								//BEEP�˿ں�
#define MOTOR2_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEPʱ��
#define MOTOR2_FUN_OUT			PBout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//RQ+
#define MOTOR3_GPIO_PIN			GPIO_Pin_6					//BEEP���ź�
#define MOTOR3_PIN_ID				6									//BEEP�������
#define MOTOR3_GPIO_PORT		GPIOB								//BEEP�˿ں�
#define MOTOR3_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEPʱ��
#define MOTOR3_FUN_OUT			PBout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//RQ-
#define MOTOR4_GPIO_PIN			GPIO_Pin_14					//BEEP���ź�
#define MOTOR4_PIN_ID				14									//BEEP�������
#define MOTOR4_GPIO_PORT		GPIOB								//BEEP�˿ں�
#define MOTOR4_GOIP_CLK			RCC_APB2Periph_GPIOB		//BEEPʱ��
#define MOTOR4_FUN_OUT			PBout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//LQ+
#define MOTOR5_GPIO_PIN			GPIO_Pin_0					//BEEP���ź�
#define MOTOR5_PIN_ID				0									//BEEP�������
#define MOTOR5_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define MOTOR5_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define MOTOR5_FUN_OUT			PAout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//LQ-
#define MOTOR6_GPIO_PIN			GPIO_Pin_1					//BEEP���ź�
#define MOTOR6_PIN_ID				1									//BEEP�������
#define MOTOR6_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define MOTOR6_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define MOTOR6_FUN_OUT			PAout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//LH+
#define MOTOR7_GPIO_PIN			GPIO_Pin_2					//BEEP���ź�
#define MOTOR7_PIN_ID				2									//BEEP�������
#define MOTOR7_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define MOTOR7_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define MOTOR7_FUN_OUT			PAout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//LH-
#define MOTOR8_GPIO_PIN			GPIO_Pin_3					//BEEP���ź�
#define MOTOR8_PIN_ID				3									//BEEP�������
#define MOTOR8_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define MOTOR8_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define MOTOR8_FUN_OUT			PAout								//BEEP����˿����ú���
/////////////////////////////////////////////////////////////////////////////////////////////////

//IO��������	 
#define MOTOR1    MOTOR1_FUN_OUT(MOTOR1_PIN_ID) //MOTOR1
#define MOTOR2    MOTOR2_FUN_OUT(MOTOR2_PIN_ID) //MOTOR2
#define MOTOR3    MOTOR3_FUN_OUT(MOTOR3_PIN_ID) //MOTOR3
#define MOTOR4    MOTOR4_FUN_OUT(MOTOR4_PIN_ID) //MOTOR4
#define MOTOR5    MOTOR5_FUN_OUT(MOTOR5_PIN_ID) //MOTOR5
#define MOTOR6    MOTOR6_FUN_OUT(MOTOR6_PIN_ID) //MOTOR6
#define MOTOR7    MOTOR7_FUN_OUT(MOTOR7_PIN_ID) //MOTOR7
#define MOTOR8    MOTOR8_FUN_OUT(MOTOR8_PIN_ID) //MOTOR8

#endif

/* ���ⲿ���õĺ������� */
void bsp_InitMotor(void);

void bsp_MotorFront(void);

void bsp_MotorFront(void);
//����
void bsp_Motorback(void);

//��ת
void bsp_Motorright(void);

//��ת
void bsp_Motorleft(void);

//ɲ��
void bsp_Motorstop(void);


#endif


