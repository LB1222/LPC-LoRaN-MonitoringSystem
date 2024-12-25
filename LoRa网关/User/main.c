/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*     说明 ：LoRa网关主程序，上传数据至EMQX服务器
*	文件名称 : main.c
*	版    本 : V1.0
**	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2024-07-02   刘斌   正式发布
*
*********************************************************************************************************
*/

#include "bsp.h"

/* 底层硬件驱动 */


//////////////////////wifiBuf
char fenge[10] = {"_____"};

//////////////////////////


/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
int main(void)
{	
		
   
	
//	char PUB_BUF[256];//上传数据的BUF
	const char *devSubTopic[] = {"/lbsmarthome/sub"};//数据下行命令TOPIC
	const char devPubTopic[] = "/lbsmarthome/pub";//数据上传TOPIC
	
	unsigned short timeCount = 0;	//发送间隔变量
	
	unsigned char *dataPtr = NULL;
	
	bsp_Init(); 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Usart1_Init(9600);         //debug 串口
	Usart2_Init(115200);         //  ESP8266通信
	Usart3_Init(9600);      //Lora通信
	UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
  Lora_TH_Display();
	ESP8266_Init();					      //初始化ESP8266
	
		while(OneNet_DevLink())			//接入OneNET
		delay_ms(500);		
		bsp_BeepOn();             //鸣叫提示接入成功
	  delay_ms(1000);
	  bsp_BeepOff();
		
		OneNet_Subscribe(devSubTopic, 1);
		clrStruct();
    delay_ms(200);	
//	  memset(Save_Data.LORA1_Buffer, 0, LORA1_Buffer_Length); 
//    point1 = 0;
//   	memset(USART3_RX_BUF, 0, USART3_REC_LEN);      //清空		 
	while(1)
	{
		
		if(++timeCount >= 200)									//发送间隔5s
		{
//			UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
	      if(Lora_rxd_flag==1)
					{
						BasisDate_Analysis();
						OneNet_Publish(devPubTopic, buffer_basisdate);				
	//  				memset(buffer_basisdate, 0, 100);
//						memset(buffer_basisdate, 0, 100);
	//					memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //清空
             Lora_rxd_flag=0;
						
					}
					else if(Lora_rxd_flag==2)
					{
						AllDate_Analysis();
						OneNet_Publish(devPubTopic, buffer_alldate);
		//				 memset(buffer_alldate, 0, 200);
			//			 memset(buffer_alldate, 0, 200);
		//				 memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //清空
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
							
		//memset(Save_Data.LORA1_Buffer, 0, LORA1_Buffer_Length);      //清空
		//bsp_Idle();
   
//		delay_ms(2000);
//		
//										lora_send_buf(fenge,5);
//											memset(LORA1_newBuffer, 0, 100);      //清空
//											memcpy(LORA1_newBuffer, nonVolatileBuffer, dataIndex); 	//保存数据
									
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
//					 memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //清空
//				}else if(Lora_rxd_flag==2)
//				{
//					 lora_send_buf(Save_Data.LORA1_AllBuffer,LORA1_AllBuffer_Length);
//					 //memset(Save_Data.LORA1_AllBuffer, 0, LORA1_AllBuffer_Length);      //清空
//					memset(Save_Data.LORA1_BasisBuffer, 0, LORA1_BasisBuffer_Length);      //清空
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
