/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_led.c
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ�ƣ�����½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-07-15   ����  ��ʽ����
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#include "bsp.h"




//void bsp_InitMotor(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStruct;
//    // ʹ��GPIOA��GPIOB��ʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

//    // ����PA0��PA1��PB14����Ϊ���ģʽ
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


//����
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


//��ת
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


//��ת
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

//ɲ��
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



