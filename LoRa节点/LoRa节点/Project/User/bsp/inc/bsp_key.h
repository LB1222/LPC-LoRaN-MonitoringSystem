/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_key.h
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ�ƣ�����½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023.8.21  ����    keytest
*
*	
*
*********************************************************************************************************
*/
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include"sys.h"



#define RCC_ALL_KEY ( WKUP_GPIO_CLK|KEY0_GPIO_CLK)


#define WKUP_GPIO_PIN      GPIO_Pin_1       //WKUP���źţ�С�˿ںţ�
#define WKUP_PIN_ID         1               //WKUP�������
#define WKUP_GPIO_PORT     GPIOA            //WKUP�˿ںţ���˿ںţ�
#define WKUP_GPIO_CLK      RCC_APB2Periph_GPIOA    //WKUPʱ��
//#define WKUP_FUN_OUT       PAout             //WKUP����˿����ú���
#define WKUP_FUN_IN        PAin            //WKUP����˿����ú���
#define WKUP_GPIO_MODE     GPIO_Mode_IPU    //WKUP�˿�����ģʽ
#define WKUP_ACTIVE_LEVEL   1               //WKUP������Ч��ƽΪ�ߵ�ƽ


#define KEY0_GPIO_PIN      GPIO_Pin_4          //KEY0 ���ź�
#define KEY0_PIN_ID        4                   //KEY0 �������
#define KEY0_GPIO_PORT     GPIOA               //KEY0 �˿ں�
#define KEY0_GPIO_CLK      RCC_APB2Periph_GPIOA          //KEY0 ʱ��
//#define KEY0_FUN_OUT       PEout               //KEY0 ����˿����ú���
#define KEY0_FUN_IN        PAin                //KEY0 ����˿����ú���
#define KEY0_GPIO_MODE     GPIO_Mode_IPU       //KEY0 �˿�����ģʽ
#define KEY0_ACTIVE_LEVEL  1                   //KEY0 ������Ч��ƽΪ�͵�ƽ
        //KEY0 ������Ч��ƽΪ�͵�ƽ


//IO��������
#define WKUP  WKUP_FUN_IN(WKUP_PIN_ID)//WKUP
#define KEY0  KEY0_FUN_IN(KEY0_PIN_ID)//KEY0


/*���ⲿ���õĺ������� */
void bsp_InitKey(void);
void EXTIx_Init(void);
void EXTI4_IRQHandler(void);






#endif

