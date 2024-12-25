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
*		V1.0    2019-08-02 waroyal  ��ʽ����
*
*	Copyright (C), 2014-2019, �����׵���
*
*********************************************************************************************************
*/

#include "bsp.h"


void bsp_InitLed(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	/*��GOIOʱ��*/
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;/*����*/
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}
void bsp_InitBeep(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	/*��GPIOʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	/*���÷�����GPIOΪ�������ģʽ
   ���ڽ�GPIO����Ϊ���ʱ��GPIO����Ĵ�����ֵȱʡ��0��������������������	
	*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
	
	
}

void bsp_LedOn(uint8_t _no)
{
	if(_no == 1)
	{
		LED0 = 0;
	}
	else if(_no == 2)
	{
		LED1 = 0;
	}
}
	
void bsp_LedOff(uint8_t _no)
{
	if(_no == 1)
	{
		LED0 = 1;
	}
	else if(_no == 2)
	{
		LED1 = 1;
	}
}

void bsp_BeepOn(void)
{
	BEEP = 0;
}

void bsp_BeepOff(void)
{
	BEEP = 1;
}

void bsp_BeepToggle(void)//��ת������
{
	BEEP_GPIO_PORT->ODR ^= BEEP_GPIO_PIN;
}

uint8_t bsp_IsBeepOn(void)
{
	if((BEEP_GPIO_PORT->ODR&BEEP_GPIO_PIN) == BEEP_GPIO_PIN)
	{
		return 1;
	}
	return 0;
}

/***************************** �����׵��� DeZLinc (END OF FILE) *********************************/
