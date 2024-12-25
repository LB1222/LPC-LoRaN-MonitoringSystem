/*
*********************************************************************************************************
*
*	ģ������ : ���������
*     ˵�� ��LoRa�����������ϴ�������EMQX������
*	�ļ����� : main.c
*	��    �� : V1.0
**	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2024-07-02   ����   ��ʽ����
*
*********************************************************************************************************
*/

#include "bsp.h"

/* �ײ�Ӳ������ */


//////////////////////wifiBuf
char fenge[10] = {"_____"};

//////////////////////////


/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: 
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{	
		
   
	
//	char PUB_BUF[256];//�ϴ����ݵ�BUF
	const char *devSubTopic[] = {"/lbsmarthome/sub"};//������������TOPIC
	const char devPubTopic[] = "/lbsmarthome/pub";//�����ϴ�TOPIC
	
	unsigned short timeCount = 0;	//���ͼ������
	
	unsigned char *dataPtr = NULL;
	
	bsp_Init(); 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Usart1_Init(9600);         //debug ����
	Usart2_Init(115200);         //  ESP8266ͨ��
	Usart3_Init(9600);      //Loraͨ��
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
  Lora_TH_Display();
	ESP8266_Init();					      //��ʼ��ESP8266
	
		while(OneNet_DevLink())			//����OneNET
		delay_ms(500);		
		bsp_BeepOn();             //������ʾ����ɹ�
	  delay_ms(1000);
	  bsp_BeepOff();
		
		OneNet_Subscribe(devSubTopic, 1);
		clrStruct();
    delay_ms(200);	
//	  memset(Save_Data.LORA1_Buffer, 0, LORA1_Buffer_Length); 
//    point1 = 0;
//   	memset(USART3_RX_BUF, 0, USART3_REC_LEN);      //���		 
	while(1)
	{
		
		if(++timeCount >= 200)									//���ͼ��5s
		{
//			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
	      if(Lora_rxd_flag==1)
					{
						BasisDate_Analysis();
						OneNet_Publish(devPubTopic, buffer_basisdate);				
	//  				memset(buffer_basisdate, 0, 100);
//						memset(buffer_basisdate, 0, 100);
	//					memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //���
             Lora_rxd_flag=0;
						
					}
					else if(Lora_rxd_flag==2)
					{
						AllDate_Analysis();
						OneNet_Publish(devPubTopic, buffer_alldate);
		//				 memset(buffer_alldate, 0, 200);
			//			 memset(buffer_alldate, 0, 200);
		//				 memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //���
            Lora_rxd_flag=0;
						
					}
						else
						{
			//				 lora_send_buf(fenge,9); 
						}
			
			         timeCount = 0;
			         ESP8266_Clear();
		}
		
		          dataPtr = ESP8266_GetIPD(3);
		          if(dataPtr != NULL)
			        OneNet_RevPro(dataPtr);
		          delay_ms(10);
	
	 	//////////////////////////////////////////////////////////////////////////////////////////
							
		//memset(Save_Data.LORA1_Buffer, 0, LORA1_Buffer_Length);      //���
		//bsp_Idle();
   
//		delay_ms(2000);
//		
//										lora_send_buf(fenge,5);
//											memset(LORA1_newBuffer, 0, 100);      //���
//											memcpy(LORA1_newBuffer, nonVolatileBuffer, dataIndex); 	//��������
									
//			
//////		lora_send_Byte(1);
//	  lora_send_buf(BasisDate_Analysis,50);
	//	test_Analysis();
////		 point1 = 0;
////		lora_send_buf(fenge,10);
		//lora_send_buf(USART3_RX_BUF,48);
//////////////////////////////////////////////////////////////////////////////////////////////////		
//					if(Lora_rxd_flag==1)
//				{
//					 lora_send_buf(Save_Data.LORA1_BasisBuffer,LORA1_BasisBuffer_Length);
//					 memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //���
//				}else if(Lora_rxd_flag==2)
//				{
//					 lora_send_buf(Save_Data.LORA1_AllBuffer,LORA1_AllBuffer_Length);
//					 //memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //���
//					memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //���
//				}
//				else
//				{
//					 lora_send_buf(fenge,9); 
//				}
////		
////////////////////////////////////////////////////////////////////////////////////////////////////////		
////		
	}
	 
}
