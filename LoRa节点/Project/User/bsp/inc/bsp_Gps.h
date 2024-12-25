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

#ifndef __GPS_H
#define __GPS_H


#include "sys.h"



#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern char  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���	


#define false 0
#define true 1

//�������鳤��
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
	char isGetData;		//�Ƿ��ȡ��GPS����
	char isParseData;	//�Ƿ�������
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];		//����
	char E_W[E_W_Length];		//E/W
	char UseDW[Useful_Nb];		//��λ״̬�Ƿ���Ч  0δ��λ 1 �޲�ֶ�λspsģʽ 2  ����� spsģʽ 3pps��λ��Ч
	char Usesatellite[Usesatellite_NB]; //ʹ����������
	char altitude[altitude_Nb]; //���θ߶�
	char alt[altitude_M];//��λM
	char wuxiao[wx];//��Ч��Ϣ
	char isUsefull;		//��λ��Ϣ�Ƿ���Ч
} _SaveData;


extern char rxdatabufer;
extern u16 point1;
extern _SaveData Save_Data;

extern char GPS_BUF[100];
////////////////////////////////////////////ת��buf

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
