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

#ifndef __GPS_H
#define __GPS_H


#include "sys.h"



#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern char  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         		//接收状态标记	


#define false 0
#define true 1

//定义数组长度
#define GPS_Buffer_Length 200
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 
#define Useful_Nb 2 
#define Usesatellite_NB 1 
#define altitude_Nb 6 
#define altitude_M 2 
#define wx 4 

typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	char isGetData;		//是否获取到GPS数据
	char isParseData;	//是否解析完成
	char UTCTime[UTCTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//经度
	char E_W[E_W_Length];		//E/W
	char UseDW[Useful_Nb];		//定位状态是否有效  0未定位 1 无差分定位sps模式 2  带差分 sps模式 3pps定位有效
	char Usesatellite[Usesatellite_NB]; //使用卫星数量
	char altitude[altitude_Nb]; //海拔高度
	char alt[altitude_M];//单位M
	char wuxiao[wx];//无效信息
	char isUsefull;		//定位信息是否有效
} _SaveData;


extern char rxdatabufer;
extern u16 point1;
extern _SaveData Save_Data;

extern char GPS_BUF[100];
////////////////////////////////////////////转发buf

extern char Time_BUF[10];
extern char latitude_BUF[11];
extern char longitude_BUF[11];
extern char altitude_BUF[11];
extern float Time_value ;
extern float latitude_value ;
extern float longitude_value ;
extern float altitude_value ;

//////////////////////////////////////////


void CLR_Buf(void);
u8 Hand(char *a);
void clrStruct(void);
void errorLog(int num);
void parseGpsBuffer(void);
void printGpsBuffer(void);


#endif
