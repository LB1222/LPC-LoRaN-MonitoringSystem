/*
*********************************************************************************************************
*
*	ģ������ : LoRa���ؽ������ݲ�����
*	�ļ����� : bsp_date.c
*	��    �� : V1.0
*	˵    �� : LoRa���ؽ������ݲ�����������½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-08-02   ����   ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"


///////////
char testBuf[10] = {0XEE,0XEE,0XEE,0XEE,0XEE,0XEE};
//char testBuf[10] = {0XEE,0XEE,0XEE,0XEE,0XEE,0XEE};
char test1Buf[20] = {"basisdate error"};
char test2Buf[15] = {"alldate error"};
/////////
/////////
char rxdatabufer;
u16 point1 = 0;
volatile uint8_t Lora_rxd_flag =0;   //��־λ
_SaveData Save_Data;
_sensorData sensorDate;


volatile char USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

///////////////////
char buffer_basisdate[80]; // ���ڴ洢��ʽ�����temp�ַ���
char buffer_alldate[80]; // ���ڴ洢��ʽ�����hum�ַ���
char buffer_dc[30]; // ���ڴ洢��ʽ�����dc�ַ���
char buffer_lt[30]; // ���ڴ洢��ʽ�����lt�ַ���
////////////////////
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART3_RX_STA=0;       //����״̬���	
/////////////////
/////////////////////////////////////

float Temp_value;
float Hum_value;
float CO2_value;
float LT_value;
float DC_value;
float TIME_value;
float latitude_value;
float longitude_value;
float altitude_value;
/////////////////////////////////////
//////////////////////
volatile uint8_t rxBuffer1[MAX_DATA_LENGTH1];
volatile uint8_t rxBuffer2[MAX_DATA_LENGTH2];

volatile ReceiveState currentState = IDLE_STATE;

volatile uint8_t dataIndex1 = 0;
volatile uint8_t dataIndex2 = 0;
volatile uint8_t *currentBuffer = NULL;
char *nonVolatileBuffer1 = (char *)rxBuffer1;
char *nonVolatileBuffer2 = (char *)rxBuffer2;

///////////////////////

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
	 if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        uint8_t receivedByte = USART_ReceiveData(USART3);
       //lora_send_Byte(receivedByte);
        switch (currentState) {
            case IDLE_STATE:
                   // ��IDLE_STATE�µȴ�֡ͷ
          
                if (receivedByte == FRAME_HEADER1) {
                    currentState = HEADER1_STATE;
                    dataIndex1 = 0; // ������������
                    currentBuffer = rxBuffer1;
									rxBuffer1[dataIndex1++] = receivedByte;
                } else if (receivedByte == FRAME_HEADER_ALT1) {
                    currentState = HEADER_ALT1_STATE;
                    dataIndex2 = 0; // ������������
                    currentBuffer = rxBuffer2;
									rxBuffer2[dataIndex2++] = receivedByte;
                }
                break;

            case HEADER1_STATE:
                if (receivedByte == FRAME_HEADER2) {
                    currentState = HEADER2_STATE;
                    rxBuffer1[dataIndex1++] = receivedByte;
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            case HEADER2_STATE:
                if (receivedByte == FRAME_HEADER3) {
                    currentState = HEADER3_STATE;
                    rxBuffer1[dataIndex1++] = receivedByte;
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            case HEADER3_STATE:
                currentState = DATA_STATE;
                //rxBuffer1[dataIndex1++] = receivedByte;
                break;
            
						case HEADER_ALT1_STATE:
                if (receivedByte == FRAME_HEADER_ALT2) {
                    currentState = HEADER_ALT2_STATE;
									  rxBuffer2[dataIndex2++] = receivedByte;
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            case HEADER_ALT2_STATE:
                if (receivedByte == FRAME_HEADER_ALT3) {
                    currentState = HEADER_ALT3_STATE;
									  rxBuffer2[dataIndex2++] = receivedByte;
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            case HEADER_ALT3_STATE:
							 
                    currentState = DATA_STATE;

                break;
               
                
								
            case DATA_STATE:

                if (currentBuffer == rxBuffer1 && dataIndex1 < MAX_DATA_LENGTH1-8) {
                    currentBuffer[dataIndex1++] = receivedByte;
								//	lora_send_Byte(receivedByte);
									    if (receivedByte == FRAME_TAIL1) 
												{
														currentState = TAIL1_STATE;
													  rxBuffer1[dataIndex1++] = receivedByte;
													
                        }
                } else if (currentBuffer == rxBuffer2 && dataIndex2 < MAX_DATA_LENGTH2-8) {
                    currentBuffer[dataIndex2++] = receivedByte;
									     //   lora_send_Byte(receivedByte);
									        if (receivedByte == FRAME_TAIL1) 
														{
																currentState = TAIL1_STATE;
																rxBuffer2[dataIndex2++] = receivedByte;
															
														}
                } else {
                    // ��ǰ��������������Ҫ����������
                   currentState = IDLE_STATE;
                }
               
               
                break;

            case TAIL1_STATE:
                if (receivedByte == FRAME_TAIL2) {
                    currentState = TAIL2_STATE;
									 // ���ݵ�ǰ�Ļ�����ѡ��洢����
                if (currentBuffer == rxBuffer1) {
                    rxBuffer1[dataIndex1++] = receivedByte;
                } else if (currentBuffer == rxBuffer2) {
                    rxBuffer2[dataIndex2++] = receivedByte;
                }
									
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            case TAIL2_STATE:
							
						
                if (receivedByte == FRAME_TAIL3) {
                    
                   if (currentBuffer == rxBuffer1) {
//                      lora_send_buf(nonVolatileBuffer1,50);
									
											memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //���
											memcpy(Save_Data.LORA1_BasisBuffer, nonVolatileBuffer1, dataIndex1); 	//��������
										  Lora_rxd_flag=1;
                } else if (currentBuffer == rxBuffer2) {
//                    lora_send_buf(nonVolatileBuffer2,55);
									
											memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //���
											memcpy(Save_Data.LORA1_AllBuffer, nonVolatileBuffer2, dataIndex2); 	//��������
									    Lora_rxd_flag=2;
                }
                    currentState = IDLE_STATE;
                } else {
                    currentState = IDLE_STATE;
                }
                break;

            default:
                currentState = IDLE_STATE;
                break;
        }
    }
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);


	   
}



void BasisDate_Analysis(void)
{
	
	    uint8_t i;
	   // Read_AHT10();
						 // ʹ��ѭ�����Ƶ�10��13���ֽڵ�������----TEMP
				for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_BasisBuffer[10 + i];
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       Temp_value =  sensorDate.f;
					printf("Temp_value:%0.2f\r\n",Temp_value);
		      
					
								 // ʹ��ѭ�����Ƶ�18��22���ֽڵ�������----HUM
				for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_BasisBuffer[18 + i];
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       Hum_value =  sensorDate.f;
					printf("Hum_value:%f\r\n",Hum_value);
					// sprintf(buffer_hum,"{\"Temp\":%0.2f}",Hum_value);
					        
					      // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----LT
						for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_BasisBuffer[26 + i];
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       LT_value =  sensorDate.f;
					printf("LT_value:%f\r\n",LT_value);
										      // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----LT
						for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_BasisBuffer[34 + i];
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
		
	       CO2_value =  sensorDate.f;
					printf("CO2_value:%f\r\n",CO2_value);
					// sprintf(buffer_lt,"{\"Temp\":%0.2f}",LT_value);
					
					
//					       // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----DC
//								for (i = 0; i < 4; i++) 
//					{
//					 sensorDate.x[3-i] = Save_Data.LORA1_BasisBuffer[34 + i];
//					}
//			//��ֵ��ע��Թ�����ĵĸ�������ֵ
//	       DC_value =  sensorDate.f;
//					printf("DC_value: %f\r\n",DC_value);
					 //sprintf(buffer_dc,"{\"Temp\":%0.2f}",DC_value);
					
					 sprintf(buffer_basisdate,"{\"Temp\":%0.2f,\"Hum\":%0.2f,\"LT\":%0.2f,\"CO2\":%0.2f}",
					Temp_value,Hum_value,LT_value,CO2_value);
//					
				
								
   
}



void AllDate_Analysis(void)
{
	   uint8_t i;
//	  uint16_t   hours=0, minutes=0, seconds=0;
//	   Read_AHT10();
		
						
					       // ʹ��ѭ�����Ƶ�10��13���ֽڵ�������----DC
								for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_AllBuffer[10 + i];//------1
					}
			       //��ֵ��ע��Թ�����ĵĸ�������ֵ
	       DC_value =  sensorDate.f;
					printf("DC_value: %f\r\n",DC_value);
	
//					       // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----TIME
//								for (i = 0; i < 4; i++) 
//					{
//					 sensorDate.x[3-i] = Save_Data.LORA1_AllBuffer[18 + i];//-----6
//					}
//			//��ֵ��ע��Թ�����ĵĸ�������ֵ
//	       TIME_value =  sensorDate.f;


//  
//		// ��ȡСʱ����
//     hours = TIME_value / 10000;

//    // ��ȡ���Ӳ���
//    minutes = (TIME_value / 100) - (hours * 100);

//    // ��ȡ�벿��
//    seconds = TIME_value - (hours * 10000) - (minutes * 100);

//    // ������
//    printf("Hours: %d\n", hours);
//    printf("Minutes: %d\n", minutes);
//    printf("Seconds: %d\n", seconds);
////					printf("TIME_value:%f\r\n",TIME_value);
					        
					            // ʹ��ѭ�����Ƶ�18��23���ֽڵ�������----latitude
								for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_AllBuffer[18 + i];//------2
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       latitude_value =  sensorDate.f;
					printf("latitude_value: %0.9f\r\n",latitude_value);
					
								       // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----longitude
								for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_AllBuffer[26 + i];//------3
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       longitude_value =  sensorDate.f;
					printf("longitude_value: %0.9f\r\n",longitude_value);
					
								       // ʹ��ѭ�����Ƶ�19��22���ֽڵ�������----altitude
								for (i = 0; i < 4; i++) 
					{
					 sensorDate.x[3-i] = Save_Data.LORA1_AllBuffer[34 + i];//------4
					}
			//��ֵ��ע��Թ�����ĵĸ�������ֵ
	       altitude_value =  sensorDate.f;
					printf("altitude_value:%f\r\n",altitude_value);
					
//					sprintf(buffer_alldate,"{\"Temp\":%0.2f,\"Hum\":%0.2f,\"LT\":%0.2f,\"DC\":%0.2f,\"CHINATIME\":%02d:%02d:%02d,\"latitude\":%0.9f,\"longitude\":%0.9f,\"altitude\":%0.2f}",
//					Temp_value,Hum_value,LT_value,DC_value, hours, minutes, seconds,latitude_value,longitude_value,altitude_value);
				sprintf(buffer_alldate,"{\"DC\":%0.2f,\"latitude\":%0.9f,\"longitude\":%0.9f,\"altitude\":%0.2f}",
					DC_value ,latitude_value,longitude_value,altitude_value);
}

void clrStruct(void)
{

	memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //���
	memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //���
//	memset(rxBuffer1, 0, USART3_REC_LEN);      //���		
	memset(Save_Data.buffer_temp, 0, temp_Length);
	memset(Save_Data.buffer_hum, 0, hum_Length);
	memset(Save_Data.buffer_hum, 0, CO2_Length);
	memset(Save_Data.buffer_dc, 0, dc_Length);
	memset(Save_Data.buffer_lt, 0, lt_Length);
	memset(Save_Data.ChinaTime, 0, ChinaTime_Length);
	memset(Save_Data.latitude, 0, latitude_Length);
  memset(Save_Data.longitude, 0, longitude_Length);
	memset(Save_Data.altitude, 0, altitude_Length);
}


void DateuploadEMQX(void)
{
//	if(Lora_rxd_flag==1)
//	{
//		BasisDate_Analysis();
//		 OneNet_Publish(devPubTopic, buffer_temp);
//	}
//	else if(Lora_rxd_flag==2)
//	{
//		AllDate_Analysis();
//		 OneNet_Publish(devPubTopic, buffer_temp);
//	}
	
	
}

