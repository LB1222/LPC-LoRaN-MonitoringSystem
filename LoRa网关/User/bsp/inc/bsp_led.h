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

#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "sys.h"



///////////////////////////////////////////////////////////
//��ֲ�޸���
//����ʵ�ʶ˿��޸�
//��ǰ�汾����������ֲ(ע�⣬�˿ڽ��������ڷ�JTAG/SWD���ţ������JTAG���ţ���Ҫ��AFIOʱ�ӣ���ʧ��JTAG)



#ifdef WSNEP_V01






#define LED0_GPIO_PIN		GPIO_Pin_9				//LED0��y??o?
#define LED0_PIN_ID			9						//LED0��y??D��o?
#define LED0_GPIO_PORT		GPIOB					//LED0???��o?
#define LED0_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0����?��
#define LED0_FUN_OUT		PBout					//LED0��?3????��????o����y
//#define LED0_FUN_IN			PBin					//LED0��?��????��????o����y

#define LED1_GPIO_PIN		GPIO_Pin_12				//LED0��y??o?
#define LED1_PIN_ID			12						//LED0��y??D��o?
#define LED1_GPIO_PORT		GPIOB					//LED0???��o?
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOB	//LED0����?��
#define LED1_FUN_OUT		PBout					//LED0��?3????��????o����y
//#define LED0_FUN_IN			PBin					//LED0��?��????��????o����y


#define BEEP_GPIO_PIN			GPIO_Pin_8					//BEEP���ź�
#define BEEP_PIN_ID				8									//BEEP�������
#define BEEP_GPIO_PORT		GPIOA								//BEEP�˿ں�
#define BEEP_GOIP_CLK			RCC_APB2Periph_GPIOA		//BEEPʱ��
#define BEEP_FUN_OUT			PAout								//BEEP����˿����ú���
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////


//IO2������o����y	 
#define LED0    LED0_FUN_OUT(LED0_PIN_ID) //LED0
#define LED1    LED1_FUN_OUT(LED1_PIN_ID) //LED1
#define BEEP    BEEP_FUN_OUT(BEEP_PIN_ID) //LED1
                


/* ���ⲿ���õĺ������� */
void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);

void bsp_BeepOn(void);
void bsp_BeepOff(void);


#endif

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
