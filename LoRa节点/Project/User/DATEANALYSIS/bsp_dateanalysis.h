/*
*********************************************************************************************************
*
*	ģ������ : �ֽ�ͨ��Э��
*	�ļ����� : bsp_dataanalisis.h
*	��    �� : V1.0
*	˵    �� : ������������֡ͷ֡β�궨��
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-04-19  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#ifndef __DATEANALYSIS_H
#define __DATEANALYSIS_H


#include "sys.h"



//////////////////////
extern uint8_t SENSOR_DATA_BYTE[248];
////////////////////////

/************�궨��************/

//��ȫ֡ͷ�궨��
#define FRAME_HEADER_BYTE_1st   0x4c    //'L'
#define FRAME_HEADER_BYTE_2nd   0x30    //'0'
#define FRAME_HEADER_BYTE_3rd   0x31    //'1'

//����֡ͷ�궨��
#define FRAME_SHEADER_BYTE_1st   0x53    //'S'
#define FRAME_SHEADER_BYTE_2nd   0x30    //'0'
#define FRAME_SHEADER_BYTE_3rd   0x31    //'1'

#define FUN_CODE_DATA 0x03    //�����ϴ��Ĺ�����(�̶�)

#define SENSOR_SINGLE_DATA_LEN 8   //���������������ݳ���
#define DATA_LEN_OFFSET 3          //���ݳ���ƫ�Ƶ�ַ
#define FRAME_TYPE_OFFSET 4        //֡����ƫ�Ƶ�ַ
#define DATA_TYPE_OFFSET 5         //����֡����������ƫ�Ƶ�ַ
#define SENSOR_DATA_LEN_OFFSET 6   //���������ݳ��� ƫ�Ƶ�ַ
#define SENSOR_DATA_START_OFFSET 7 //��һ�������������׵�ַ ƫ�Ƶ�ַ


#define SENSOR_TEMP_CODE 0x01                 //�¶ȴ�����
#define SENSOR_HUMI_CODE 0x02                 //ʪ�ȴ�����
#define SENSOR_LM_CODE 0x04                   //���մ�����
#define SENSOR_DC_CODE 0x05                   //��ص�ѹ���
#define SENSOR_CO2_CODE 0x06                  //����ʱ���ϱ�
#define SENSOR_latitude_CODE 0x07              //γ���ϱ�
#define SENSOR_longitude_CODE 0x08             //�����ϱ�
#define SENSOR_altitude_CODE 0x09              //���θ߶��ϱ�
#define SENSOR_TIME_CODE 0x0a                   //Co2�����ϱ�


#define ENVIRONMENT_SENSOR_TYPE_CODE_MSB 0x22 //��������������֡��֡ͷ
#define ENVIRONMENT_SENSOR_TYPE_CODE_LSB 0x00 //��������������֡��֡ͷ

#define SENSOR_STATUS_PRE 0x00                //������Ԥ��
#define SENSOR_STATUS_NG 0x01                 //��������ֵ�쳣
#define SENSOR_STATUS_RUN 0x02                //��������������
#define DATA_TYPE_SENSOR 0x01                 //����������

#define ENVIRONMENT_SENSOR_START1 0xFF //��������������֡��֡ͷ
#define ENVIRONMENT_SENSOR_START2 0x22 //��������������֡��֡ͷ
#define ENVIRONMENT_SENSOR_END 0x11 //��������������֡��֡ͷ

typedef union
{
    float f;
    uint8_t x[4];
} _sensorData; //���������� float �� 4 �ֽ� �໥�任 ʹ��������




uint8_t CheckSum(uint8_t *buf, uint8_t len);
void sensor_BasisDate_Upload(void);
void sensor_AllDate_Upload(void);
//void sensor_Humi_Upload(void);
void sensor_Luminance_Upload(float LT);
void sensor_DC_Upload(float DC);
void sensor_TIME_Upload(void);
//void sensor_CO2_Upload(float CO2);
void sensor_latitude_Upload(void);
void sensor_longitude_Upload(void);
void sensor_altitude_Upload(void);

#endif

