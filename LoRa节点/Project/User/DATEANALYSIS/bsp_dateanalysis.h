/*
*********************************************************************************************************
*
*	模块名称 : 字节通信协议
*	文件名称 : bsp_dataanalisis.h
*	版    本 : V1.0
*	说    明 : 传感器及数据帧头帧尾宏定义
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-04-19  刘斌  正式发布
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

/************宏定义************/

//安全帧头宏定义
#define FRAME_HEADER_BYTE_1st   0x4c    //'L'
#define FRAME_HEADER_BYTE_2nd   0x30    //'0'
#define FRAME_HEADER_BYTE_3rd   0x31    //'1'

//报警帧头宏定义
#define FRAME_SHEADER_BYTE_1st   0x53    //'S'
#define FRAME_SHEADER_BYTE_2nd   0x30    //'0'
#define FRAME_SHEADER_BYTE_3rd   0x31    //'1'

#define FUN_CODE_DATA 0x03    //数据上传的功能码(固定)

#define SENSOR_SINGLE_DATA_LEN 8   //单个传感器的数据长度
#define DATA_LEN_OFFSET 3          //数据长度偏移地址
#define FRAME_TYPE_OFFSET 4        //帧类型偏移地址
#define DATA_TYPE_OFFSET 5         //数据帧的数据类型偏移地址
#define SENSOR_DATA_LEN_OFFSET 6   //传感器数据长度 偏移地址
#define SENSOR_DATA_START_OFFSET 7 //第一个传感器数据首地址 偏移地址


#define SENSOR_TEMP_CODE 0x01                 //温度传感器
#define SENSOR_HUMI_CODE 0x02                 //湿度传感器
#define SENSOR_LM_CODE 0x04                   //光照传感器
#define SENSOR_DC_CODE 0x05                   //电池电压监测
#define SENSOR_CO2_CODE 0x06                  //本地时间上报
#define SENSOR_latitude_CODE 0x07              //纬度上报
#define SENSOR_longitude_CODE 0x08             //经度上报
#define SENSOR_altitude_CODE 0x09              //海拔高度上报
#define SENSOR_TIME_CODE 0x0a                   //Co2数据上报


#define ENVIRONMENT_SENSOR_TYPE_CODE_MSB 0x22 //环境传感器数据帧的帧头
#define ENVIRONMENT_SENSOR_TYPE_CODE_LSB 0x00 //环境传感器数据帧的帧头

#define SENSOR_STATUS_PRE 0x00                //传感器预热
#define SENSOR_STATUS_NG 0x01                 //传感器数值异常
#define SENSOR_STATUS_RUN 0x02                //传感器正常运行
#define DATA_TYPE_SENSOR 0x01                 //传感器数据

#define ENVIRONMENT_SENSOR_START1 0xFF //环境传感器数据帧的帧头
#define ENVIRONMENT_SENSOR_START2 0x22 //环境传感器数据帧的帧头
#define ENVIRONMENT_SENSOR_END 0x11 //环境传感器数据帧的帧头

typedef union
{
    float f;
    uint8_t x[4];
} _sensorData; //传感器数据 float 与 4 字节 相互变换 使用联合体




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

