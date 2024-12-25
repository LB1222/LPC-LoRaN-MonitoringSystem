/*
*********************************************************************************************************
*
*	模块名称 : ATH10驱动模块
*	文件名称 : bsp_i2c.h
*	版    本 : V1.0
*	说    明 : ATH10驱动
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-08-19  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/



#ifndef __BSP_I2C2_H
#define __BSP_I2C2_H

#include "sys.h"


////////////////////////////
//extern char buffer_temp[30]; // 用于存储格式化后的temp字符串
//extern char buffer_hum[30]; // 用于存储格式化后的hum字符串
//extern float Temp_value;
//extern float Hum_value;
/////////////////////////
//  PB6,PB7
 
//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<24;}
//#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<24;}
// 
////IO操作函数	 
//#define IIC_SCL    PBout(7) //SCL
//#define IIC_SDA    PBout(6) //SDA	 
//#define READ_SDA   PBin(6)  //输入SDA 


//IIC所有操作函数
u8 JH_Init(void);
uint8_t JH_Read_Cal_Enable(void) ;
void JH_Read_CTdata(uint32_t *ct) ;
void Read_AHT10(void);
#endif
