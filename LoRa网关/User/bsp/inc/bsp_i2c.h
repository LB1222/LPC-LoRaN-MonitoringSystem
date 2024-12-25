/*
*********************************************************************************************************
*
*	ģ������ : ATH10����ģ��
*	�ļ����� : bsp_i2c.h
*	��    �� : V1.0
*	˵    �� : ATH10����
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-08-19  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/



#ifndef __BSP_I2C2_H
#define __BSP_I2C2_H

#include "sys.h"


////////////////////////////
//extern char buffer_temp[30]; // ���ڴ洢��ʽ�����temp�ַ���
//extern char buffer_hum[30]; // ���ڴ洢��ʽ�����hum�ַ���
//extern float Temp_value;
//extern float Hum_value;
/////////////////////////
//  PB6,PB7
 
//#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<24;}
//#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<24;}
// 
////IO��������	 
//#define IIC_SCL    PBout(7) //SCL
//#define IIC_SDA    PBout(6) //SDA	 
//#define READ_SDA   PBin(6)  //����SDA 


//IIC���в�������
u8 JH_Init(void);
uint8_t JH_Read_Cal_Enable(void) ;
void JH_Read_CTdata(uint32_t *ct) ;
void Read_AHT10(void);
#endif
