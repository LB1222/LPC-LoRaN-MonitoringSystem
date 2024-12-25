/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_beep.c
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯，配合新建工程使用，非完整文件
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-04-19  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/

#ifndef __ADC_H
#define __ADC_H


#include "sys.h"

/////////////////////////////////////转发得BUF
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
// ADC 编号选择
// 可以是 ADC1/2，如果使用ADC3，中断相关的要改成ADC3的
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADCx                          ADC1
#define    ADC_CLK                       RCC_APB2Periph_ADC1

// ADC GPIO宏定义
// 注意：用作ADC采集的IO必须没有复用，否则采集电压会有影响
#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA
#define    ADC_PIN                       GPIO_Pin_5
// ADC 通道宏定义
#define    ADC_CHANNEL                   ADC_Channel_5

// ADC 中断相关宏定义
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
