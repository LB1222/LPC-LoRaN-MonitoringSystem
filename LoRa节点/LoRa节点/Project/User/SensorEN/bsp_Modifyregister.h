/*
*********************************************************************************************************
*
*	模块名称 : 按键驱动模+块
*	文件名称 : bsp_usart.h
*	版    本 : V1.2
*	说    明 : 头文件
     
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023.4.26  l刘斌    usarttest
*
*	Copyright (C), 2014-2019, 德致伦电子
*
*********************************************************************************************************
*/

#ifndef __BSP_MODIFY_H
#define __BSP_MODIFY_H


#include"sys.h"



//#define  Register   0x00
//#define  Wegister   0x80
//#define  Addr_Reg   0x19
//#define  Number     0x01

//#define  Addr1       0x22
//#define  Addr2       0x33



#define USART1_EX_0      GPIO_Pin_3           //串口1的（4路）多路复用控制引脚
#define USART1_EX_1      GPIO_Pin_15          //串口1的（4路）多路复用控制引脚
#define LORA_EX_EN       GPIO_Pin_4           //串口2的（2路）多路复用控制引脚
#define LORA_MD0         GPIO_Pin_4           //LORA_MD0 引脚号
#define LORA_MD1         GPIO_Pin_5           //LORA_MD1 引脚号
#define CO2_EN           GPIO_Pin_0           //二氧化碳使能引脚号
#define LANYA_EN     		 GPIO_Pin_1           //蓝牙使能引脚号
#define ADC_DC_EN        GPIO_Pin_12          //ADC电压采样使能引脚号
#define GPS_EN           GPIO_Pin_7           //GPS使能引脚号



extern char Register_Buf[3] ;
extern char Wegister_Buf1[4] ;
extern char Wegister_Buf2[4] ;
extern char Reset_Lora[3]  ;







void Config_MDPin(void);
void Config_EnSensorPin(void);
void Reset_MDPin(void);
void Set_MDPin(void);
void Work_MDPin(void);
void Modify_Register(void);
void Search_Register(void);
void Modify_Addr(void);	
void Sleeping_MDPin(void);
void CO2_SensorEN(void);
void LANYA_SensorEN(void);
void ADC_DC_EN_SensorEN(void);
void GPS_EN_SensorEN(void);
void CO2_SensorCS(void);
void LANYA_SensorCS(void);
void ADC_DC_EN_SensorCS(void);
void GPS_EN_SensorCS(void);
void USART1_Lanya(void);
void USART1_CO2(void);
void USART1_Printf(void);
void USART1_RESERVED(void);

void USART2_LORA_EX_EN(void);
	void USART2_REGLORA_TXD(void);
#endif

