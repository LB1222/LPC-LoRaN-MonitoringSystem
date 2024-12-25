#include "usart3.h"
#include "misc.h"
#include "stdio.h"
#include "ALL_DEFINE.h"


uint8_t rxd_buf[20];
uint8_t rxd_index = 0;
uint8_t rxd_flag = 0;
uint8_t mode_flag = 0;

/*
 * 函数名：USART1_Config
 * 描述  ：USART1 GPIO 配置,工作模式配置。
 * 输入  ：无
 * 输出  : 无
 * 调用  ：外部调用
 */

void USART3_Config(u32 br_num) 
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //开启USART3时钟
	RCC_APB2PeriphClockCmd(RCC_UART3,ENABLE);	

	/*串口GPIO端口配置*/
  /* 配置串口1 （USART3 Tx (PA.10)）*/
	GPIO_InitStructure.GPIO_Pin = UART3_Pin_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_UART3, &GPIO_InitStructure);
  
	/* 配置串口1 USART3 Rx (PA.11)*/
  GPIO_InitStructure.GPIO_Pin = UART3_Pin_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_UART3, &GPIO_InitStructure);
	
	
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate =br_num;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	
		//配置USART3时钟
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //时钟低电平活动
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK引脚上时钟输出->低电平
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //
	
	
	USART_Init(USART3, &USART_InitStructure);
	USART_ClockInit(USART3, &USART_ClockInitStruct);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	
	USART_Cmd(USART3, ENABLE); //使能串口 
	
		/* 使能串口1中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	//USART3  串口1全局中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //子优先级
	/*IRQ通道使能*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART3*/
	NVIC_Init(&NVIC_InitStructure);
	
	
	
}

//////////////////////////////////////////


//串口3中断程序在  ANO_DT.C 程序里面


//////////////////////////////////////////

void ANO_UART3_DeInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USART_DeInit(USART3);
	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
}



void USART3_SendByte(const int8_t *Data,uint8_t len)
{ 
	uint8_t i;
	
	for(i=0;i<len;i++)
	{
		while (!(USART3->SR & USART_FLAG_TXE));	 // while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		USART_SendData(USART3,*(Data+i));	 
	}
}

//void USART3_Send1(const int8_t Data)  
//{ 

//		while (!(USART3->SR & USART_FLAG_TXE));	 // while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
//		USART_SendData(USART3,(Data));	 
//	
//}


//int8_t CheckSend[7]={0xAA,0XAA,0xEF,2,0,0,0};

//void USART1_setBaudRate(uint32_t baudRate)
//{
//	USART_InitTypeDef USART_InitStructure;
//	USART_InitStructure.USART_BaudRate =  baudRate;
//	USART_Init(USART1, &USART_InitStructure);
//}

//#include "sys.h"
//#include "usart.h"
//// 	 
////如果使用ucos,则包括下面的头文件即可.
//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos 使用	  
//#endif

//
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((USART3->SR&0X40)==0)
//		;//循环发送,直到发送完毕   
//    USART3->DR = (u8) ch;
//	return ch;
//}
//#endif 

//#if EN_USART3_RX   //如果使能了接收
////串口1中断服务程序
////注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
////接收状态
////bit15，	接收完成标志
////bit14，	接收到0x0d
////bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	  

//void uart1_init(u32 bound){
//  //GPIO端口设置
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
//   
//  //USART1_RX	  GPIOA.10初始化
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

//  //Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//  
//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//串口波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//  USART_Cmd(USART1, ENABLE);                    //使能串口1 

//}
//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	u8 Res;
////	static u8 i =0;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		 Res =USART_ReceiveData(USART1);	//读取接收到的数据
////	   USART_SendData(USART1,Res);			
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
//} 
//#endif


void Send_Byte(uint8_t byte)
{
	USART_SendData(USART3,byte);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
}


/*
*********************************************************************************************************
*	函 数 名: Send_String
	*	功能说明: 发送字符串/定义一个BUF在里面增加字符串即可  ：uint8_t buf[] = {"ninhao"};
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Send_String(uint8_t *str)
{
	
	while(*str != '\0')
	{
		Send_Byte(*str++);
	}
}


/*
*********************************************************************************************************
*	函 数 名: Send_Buf
*	功能说明: 发送Buf
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Send_Buf(uint8_t *buf,uint16_t len)
{
	uint16_t i;
	for(i=0;i<len;i++)
	{
		Send_Byte(buf[i]);
	}
}



/*
*********************************************************************************************************
*	函 数 名: Send_Pack
	*	功能说明: 发送带帧头、帧尾的协议包
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void Send_Pack(void)
{

		Send_Byte(0xFE);
		Send_Buf(rxd_buf,6);
		Send_Byte(0xEF);
		if(mode_flag == 0)
		{
			Send_Byte(0x58);
			Send_Byte(0x48);
		}
		else if(mode_flag == 0x01||mode_flag == 0x02||mode_flag == 0x03)
		{
			Send_Byte(0x44);
			Send_Byte(0x44);
			Send_Byte(mode_flag);
			Send_Byte(ON_flag);
		}
	
	
}


	/*
*********************************************************************************************************
*	函 数 名: USARTI_IRQHandler(void)
*	功能说明: USART3中断，主要是接收1个字节
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void USART3_IRQHandler(void)                   //串口3中断服务程序
  {
	uint8_t Res;
	static uint8_t  Res_state = 0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  //接收中断（接收到一个字节数据）
	{
		Res = USART_ReceiveData(USART3);     //把接收到的字节保存
	  switch(Res_state)
		{
			case 0:    //'A' 为文本模式发送/或者ASCII码
				if(Res==0xEF)  //判断帧头
				{
					Res_state=1;  //切换为下一个状态
					rxd_index=0;  //将索引归0，方便下次接着接收
				}
				else{
					Res_state=0;  //帧头不对，死循环
				}
			 
			break;
			case 1:
				rxd_buf[rxd_index] = Res;  //将接下来的数据存入BUF
		  	rxd_index++;    //一个个存
			if(rxd_buf[3]==0x58 && rxd_buf[4]==0x48)
			{
				mode_flag = 0;
				ON_flag = 0;
			}
			else if(rxd_buf[3]==0x44 && rxd_buf[4]==0x44)
			{
				//mode_flag = rxd_buf[5];
				mode_flag = 1;
				ON_flag = 0;
			}
			if(rxd_index >= 6)  //固定包长4个
			{
				Res_state=2;   //进入下一个状态
			}
			  
			 break; 
			case 2:
				if(Res==0xFE)
				{
					rxd_flag=1;      //切换标志位，代表数据接收完成
					Res_state=0;     //清除状态，方便下次接收
				} 
		}
		
	}
     USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	   //USART_ClearITPendingBit(USART1,USART_IT_IDLE);
  }
	




