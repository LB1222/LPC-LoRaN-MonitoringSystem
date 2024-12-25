/*
*********************************************************************************************************
*
*	ģ������ : GPS����ģ��
*	�ļ����� : bsp_Gps.c
*	��    �� : V1.0
*	˵    �� : ��λģ���ʼ�����򣬲��ô���3��������
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-04-19  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"

char rxdatabufer;
u16 point1 = 0;

_SaveData Save_Data;
char USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	


char GPS_BUF[100];
////////////////////////////////////////////ת��buf



char Time_BUF[10];
char latitude_BUF[11];
char longitude_BUF[11];
char altitude_BUF[11];
float Time_value ;
//float latitude_value  ;
//float longitude_value ;
//float altitude_value ;
float latitude_value=116.151809  ;
float longitude_value=40.218612 ;
float altitude_value = 56.0;
//			  latitude_value =116.151809  ;
//        longitude_value =40.218612;
//         altitude_value  = 56.0 ;

//////////////////////////////////////////

/*
************************************************************
*	�������ƣ�	USART3_IRQHandler
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART3_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		Res =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
	
	if(Res == '$')
	{
		point1 = 0;	
	}
		

	  USART3_RX_BUF[point1++] = Res;

	if(USART3_RX_BUF[0] == '$' && USART3_RX_BUF[4] == 'G' && USART3_RX_BUF[5] == 'A')			//ȷ���Ƿ��յ�"GPRMC/GNRMC"��һ֡����
	{
		if(Res == '\n')									   
		{
			memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
			memcpy(Save_Data.GPS_Buffer, USART3_RX_BUF, point1); 	//��������
			Save_Data.isGetData = true;
			point1 = 0;
			memset(USART3_RX_BUF, 0, USART3_REC_LEN);      //���				
		}	
				
	}
	
	if(point1 >= USART3_REC_LEN)
	{
		point1 = USART3_REC_LEN;
	}	
		
} 
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
}



u8 Hand(char *a)                   // ��������ʶ����
{ 
    if(strstr(USART3_RX_BUF,a)!=NULL)
	    return 1;
	else
		return 0;
}

void CLR_Buf(void)                           // ���ڻ�������
{
	memset(USART3_RX_BUF, 0, USART3_REC_LEN);      //���
  point1 = 0;                    
}

void clrStruct(void)
{
	Save_Data.isGetData = false;
	Save_Data.isParseData = false;
	Save_Data.isUsefull = false;
	memset(Save_Data.GPS_Buffer, 0, GPS_Buffer_Length);      //���
	memset(Save_Data.UTCTime, 0, UTCTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
	memset(Save_Data.N_S, 0, N_S_Length);
	memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.E_W, 0, E_W_Length);
//	memset(buffer_hum, 0, 30);
//	memset(buffer_temp, 0, 30);
	memset(Time_BUF, 0, 30);
	memset(GPS_BUF, 0, 100);
	memset(DC_Buf, 0, 30);
	memset(LT_Buf, 0, 30);
	
}



void errorLog(int num)
{
	
	while (1)
	{
	  	printf("ERROR%d\r\n",num);
	}
}

void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		printf(" Information Error!");
		//printf("%s\r\n ",Save_Data.GPS_Buffer);

		
		for (i = 0 ; i <= 10 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1);	//��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					
					switch(i)
					{
						case 1:memcpy(Save_Data.UTCTime, subString, subStringNext - subString);break;	//��ȡUTCʱ��
						case 2:memcpy(Save_Data.latitude, subString, subStringNext - subString);break;	//��ȡγ����Ϣ
						case 3:memcpy(Save_Data.N_S, subString, subStringNext - subString);break;	//��ȡN/S
						case 4:memcpy(Save_Data.longitude, subString, subStringNext - subString);break;	//��ȡ������Ϣ
						case 5:memcpy(Save_Data.E_W, subString, subStringNext - subString);break;	//��ȡE/W
						case 6:memcpy(Save_Data.UseDW, subString, subStringNext - subString);break;	//��ȡE/W
						case 7:memcpy(Save_Data.Usesatellite, subString, subStringNext - subString);break;	//��ȡE/W
						case 8:memcpy(Save_Data.wuxiao, subString, subStringNext - subString);break;	//��ȡE/W
						case 9:memcpy(Save_Data.altitude, subString, subStringNext - subString);break;	//��ȡE/W
						case 10:memcpy(Save_Data.alt, subString, subStringNext - subString);break;	//��ȡE/W

						default:break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
			    
					if(Save_Data.UseDW[0] == '1')
						Save_Data.isUsefull = true;
					else if(Save_Data.UseDW[0] == '0')
						Save_Data.isUsefull = false;

				}
				else
				{
					errorLog(2);	//��������
				}
			}


		}
	}
}



void printGpsBuffer()
{
	parseGpsBuffer();
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;
		
	//�й�+8 132356.000

     // ������յ���ʱ���ַ���

    

    struct tm received_time = {0}; // ��ʼ��Ϊ0�������ڲ�����Ϊ1970-01-01

    // ����ʱ���ַ���             //�й�+8 Sava_Date.UTCTime 132356.000
    sscanf(Save_Data.UTCTime, "%2d%2d%2d", &received_time.tm_hour, &received_time.tm_min, &received_time.tm_sec);

    // ��ʱ������Ϊ����������8Сʱ��
    received_time.tm_hour += 8;

    // ����Сʱ��������
    if (received_time.tm_hour >= 24) {
        received_time.tm_hour -= 24;
    }

    // ����������ʱ��
    printf("\r\n China time:%02d:%02d:%02d\r\n\r\n", received_time.tm_hour, received_time.tm_min, received_time.tm_sec);
     // sprintf(Time_BUF," {\"China time\":%02d:%02d:%02d}", received_time.tm_hour, received_time.tm_min, received_time.tm_sec);
    sprintf(Time_BUF," %02d%02d%02d", received_time.tm_hour, received_time.tm_min, received_time.tm_sec);    
		// lora_send_buf(Time_BUF,30);
    Time_value = atof(Time_BUF);
   // sensor_TIME_Upload();
 
//        //printf("%02d\n",ChHour1);
//				ChMin1 = Save_Data.UTCTime[2];
//				ChMin2 = Save_Data.UTCTime[3];
//		    ChSe1 = Save_Data.UTCTime[4];
//		    ChSe2 = Save_Data.UTCTime[5];
		       
//		    printf("%c%c:%c%c",ChMin1,ChMin2,ChSe1,ChSe2);
//		    printf("\r\n");
//		printf("UTCTime = ");
//		printf(Save_Data.UTCTime);
//		printf("\r\n");

		if(Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
			float firstFloat1, secondFloat1,firstFloat2, secondFloat2;
			
					  // ���ַ������е�ǰ�����ַ�����Ϊ����������ֵ��firstFloat
    sscanf(Save_Data.latitude, "%2f", &firstFloat1);

    // ���ַ������еĺ���9���ַ�����Ϊ����������ֵ��secondFloat
    sscanf(Save_Data.latitude + 2, "%8f", &secondFloat1);
    
    latitude_value =  firstFloat1+(secondFloat1/60.0);
					
	//latitudeС������λ		
//					for (J = 4; J >= 2; J--)
//					{
//						Save_Data.latitude[J] = Save_Data.latitude[J - 1];
//					}
//					Save_Data.latitude[2] = temp1;
				
			printf("original :latitude = ");
			printf("%s",Save_Data.latitude);
			//	printf("Save_Data.N_S = ");
			printf("%s",Save_Data.N_S);
			printf("\r\n");
			//printf("\r\n");

//longitudeС������λ
//					for (W = 5; W >= 3; W--)
//					{
//						Save_Data.longitude[W] = Save_Data.longitude[W - 1];
//					}
//					Save_Data.longitude[3] = temp2;
									  // ���ַ������е�ǰ�����ַ�����Ϊ����������ֵ��firstFloat
    sscanf(Save_Data.longitude, "%3f", &firstFloat2);

    // ���ַ������еĺ���9���ַ�����Ϊ����������ֵ��secondFloat
    sscanf(Save_Data.longitude + 2, "%8f", &secondFloat2);
    
    longitude_value =  firstFloat2+(secondFloat2/60.0);
		

			printf("original :longitude = ");
			printf("%s",Save_Data.longitude);
			//printf("Save_Data.E_W = ");
			printf("%s",Save_Data.E_W);
			printf("\r\n");
		
//0��Ч 1��Ч					
			printf("UseDW = ");
			printf("%s",Save_Data.UseDW);
			printf("\r\n");
			
//			printf("Save_Data.Usesatellite = ");
//			printf(Save_Data.Usesatellite);
//			printf("\r\n");
	//���θ߶�	
			printf("original :altitude = ");
			printf("%s",Save_Data.altitude);
			//printf("Save_Data.alt = ");
			printf("%s",Save_Data.alt);
			printf("\r\n");
			
//				sprintf(latitude_BUF,"%s",\"N_S\":%s ,\"longitude\":%s,\"E_W\":%s,\"UseDW\":%s,\"altitude\":%s,\"alt\":%s}",
//			Save_Data.latitude,Save_Data.N_S,Save_Data.longitude,Save_Data.E_W,Save_Data.UseDW,Save_Data.altitude,Save_Data.alt);
			
		//	lora_send_buf(GPS_BUF,200);
		//�ַ�����ת������
//			sprintf(latitude_BUF,"%s",Save_Data.latitude);
//			 latitude_value = atof(latitude_BUF);
//			sprintf(longitude_BUF,"%s",Save_Data.longitude);
//			 longitude_value = atof(longitude_BUF);
			sprintf(altitude_BUF,"%s",Save_Data.altitude);
			 altitude_value = atof(altitude_BUF);
//			 sensor_latitude_Upload();
//			 sensor_longitude_Upload();
//			 sensor_altitude_Upload();
//  			bsp_BeepOff();
//				delay_ms(1000);
//				bsp_BeepOn();
		}
		else
		{
			  latitude_value =116.151809  ;
        longitude_value =40.218612;
         altitude_value  = 56.0 ;
			printf("GPS DATA is not usefull!USE Reserve date!\r\n");
		}
		
	}
}
