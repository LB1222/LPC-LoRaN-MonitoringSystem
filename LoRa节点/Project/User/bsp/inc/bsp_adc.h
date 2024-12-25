/*
*********************************************************************************************************
*
*	ģ������ : LEDָʾ������ģ��
*	�ļ����� : bsp_beep.c
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ�ƣ�����½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-04-19  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#ifndef __ADC_H
#define __ADC_H


#include "sys.h"

/////////////////////////////////////ת����BUF
extern char DC_Buf[20];
extern char LT_Buf[20];
extern float DC_value;
extern float LT_value;

//extern float DC_alarm_value;

//extern float LT_alarm_value;
///////////////////////////////////////

//extern uint16_t ADC_ConvertedValue[2];
//extern uint16_t adcValueVoltage, adcValueLight;

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
// ADC ���ѡ��
// ������ ADC1/2�����ʹ��ADC3���ж���ص�Ҫ�ĳ�ADC3��
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

// ADC GPIO�궨��
// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA
#define    ADC_PIN                       GPIO_Pin_5
// ADC ͨ���궨��
#define    ADC_CHANNEL                   ADC_Channel_5

// ADC �ж���غ궨��
#define    ADC_IRQ                       ADC1_2_IRQn
#define    ADC_IRQHandler                ADC1_2_IRQHandler

//#define    ADC_IRQ                       ADC3_IRQn
//#define    ADC_IRQHandler                ADC3_IRQHandler


//void Light_Adc_Init(void);
//void DC_Adc_Init(void);
void GPIO_Configuration(void);
void ADC_Configuration(void) ;
void ReadDCValue(void);
void ReadLTValue(void) ;
void Get_battery_volt(void);  
void Get_Light_value(void);


#endif
