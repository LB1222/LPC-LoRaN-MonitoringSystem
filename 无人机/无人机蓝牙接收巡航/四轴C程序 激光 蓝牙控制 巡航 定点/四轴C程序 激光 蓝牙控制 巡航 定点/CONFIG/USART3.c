#include "usart3.h"
#include "misc.h"
#include "stdio.h"
#include "ALL_DEFINE.h"


uint8_t rxd_buf[20];
uint8_t rxd_index = 0;
uint8_t rxd_flag = 0;
uint8_t mode_flag = 0;

/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ���á�
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */

void USART3_Config(u32 br_num) 
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStruct;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //����USART3ʱ��
	RCC_APB2PeriphClockCmd(RCC_UART3,ENABLE);	

	/*����GPIO�˿�����*/
  /* ���ô���1 ��USART3 Tx (PA.10)��*/
	GPIO_InitStructure.GPIO_Pin = UART3_Pin_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_UART3, &GPIO_InitStructure);
  
	/* ���ô���1 USART3 Rx (PA.11)*/
  GPIO_InitStructure.GPIO_Pin = UART3_Pin_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_UART3, &GPIO_InitStructure);
	
	
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate =br_num;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	
		//����USART3ʱ��
	USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;  //ʱ�ӵ͵�ƽ�
	USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;  //SLCK������ʱ�����->�͵�ƽ
	USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;  //
	USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //
	
	
	USART_Init(USART3, &USART_InitStructure);
	USART_ClockInit(USART3, &USART_ClockInitStruct);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	
	USART_Cmd(USART3, ENABLE); //ʹ�ܴ��� 
	
		/* ʹ�ܴ���1�ж� */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	//USART3  ����1ȫ���ж� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ�
	/*IRQͨ��ʹ��*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/*����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART3*/
	NVIC_Init(&NVIC_InitStructure);
	
	
	
}

//////////////////////////////////////////


//����3�жϳ�����  ANO_DT.C ��������


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
////���ʹ��ucos,����������ͷ�ļ�����.
//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos ʹ��	  
//#endif

//
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
//#if 1
//#pragma import(__use_no_semihosting)             
////��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART3->SR&0X40)==0)
//		;//ѭ������,ֱ���������   
//    USART3->DR = (u8) ch;
//	return ch;
//}
//#endif 

//#if EN_USART3_RX   //���ʹ���˽���
////����1�жϷ������
////ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
////����״̬
////bit15��	������ɱ�־
////bit14��	���յ�0x0d
////bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	  

//void uart1_init(u32 bound){
//  //GPIO�˿�����
//  GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
//  
//	//USART1_TX   GPIOA.9
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
//   
//  //USART1_RX	  GPIOA.10��ʼ��
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

//  //Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//  
//   //USART ��ʼ������

//	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
//  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

//}
//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;
////	static u8 i =0;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//		 Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
////	   USART_SendData(USART1,Res);			
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
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
*	�� �� ��: Send_String
	*	����˵��: �����ַ���/����һ��BUF�����������ַ�������  ��uint8_t buf[] = {"ninhao"};
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: Send_Buf
*	����˵��: ����Buf
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: Send_Pack
	*	����˵��: ���ʹ�֡ͷ��֡β��Э���
*	��    �Σ���
*	�� �� ֵ: ��
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
*	�� �� ��: USARTI_IRQHandler(void)
*	����˵��: USART3�жϣ���Ҫ�ǽ���1���ֽ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void USART3_IRQHandler(void)                   //����3�жϷ������
  {
	uint8_t Res;
	static uint8_t  Res_state = 0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  //�����жϣ����յ�һ���ֽ����ݣ�
	{
		Res = USART_ReceiveData(USART3);     //�ѽ��յ����ֽڱ���
	  switch(Res_state)
		{
			case 0:    //'A' Ϊ�ı�ģʽ����/����ASCII��
				if(Res==0xEF)  //�ж�֡ͷ
				{
					Res_state=1;  //�л�Ϊ��һ��״̬
					rxd_index=0;  //��������0�������´ν��Ž���
				}
				else{
					Res_state=0;  //֡ͷ���ԣ���ѭ��
				}
			 
			break;
			case 1:
				rxd_buf[rxd_index] = Res;  //�������������ݴ���BUF
		  	rxd_index++;    //һ������
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
			if(rxd_index >= 6)  //�̶�����4��
			{
				Res_state=2;   //������һ��״̬
			}
			  
			 break; 
			case 2:
				if(Res==0xFE)
				{
					rxd_flag=1;      //�л���־λ���������ݽ������
					Res_state=0;     //���״̬�������´ν���
				} 
		}
		
	}
     USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	   //USART_ClearITPendingBit(USART1,USART_IT_IDLE);
  }
	




