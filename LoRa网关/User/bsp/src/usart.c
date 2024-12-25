/**
	*	�ļ����� 	usart.c
	*
	*	���ߣ� 		����
	*
	*	���ڣ� 		2023-11-23
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		��Ƭ�����������ʼ������ʽ����ӡ
	*
	*	�޸ļ�¼��	
**/

//Ӳ������

#include "bsp.h"

//C��
#include <stdarg.h>




uint16_t rxd_cnt = 0;//���ռ�������

//usart2 USART2_IRQHandler ���ݰ�
uint8_t txd_buf[4] ={1,2,3,4};
uint8_t rxd_buf[100];   //�̶�����
uint8_t rxd_flag =0;   //��־λ
uint8_t rxd_index = 0;  //����




#if 1

/*
*********************************************************************************************************
*	�� �� ��: fputc
*	����˵��: ���¶���put��������������ʹ��printf�����Ӵ���1��ӡ���
*******************************************************************8
	��仰��ʹ��C/C++��������е� `sprintf` ��������ʽ���ַ�����һ���֡�
		����������һ�����ĺ��壺
1. `sprintf`: ����һ�����ڸ�ʽ���ַ����ĺ�����
		�����Խ����ݰ���ָ���ĸ�ʽ���뵽�ַ����С�
2. `String`: ����һ�����ڴ洢���ո�ʽ��������ַ�������ַ���������
3. `" %.2f%%"`: ���Ǹ�ʽ���ַ����ĸ�ʽ���Ʋ��֡������������������
	 - `" "`: ���ʾ�ڲ�������֮ǰ����һ���ո����ǿ�ѡ�ģ�
		����������ǰ���һ���ո�
	 - `%.2f`: ����һ����ʽ˵���������ڲ��븡������
		���У�`%` ��ʾ��ʽ˵�����Ŀ�ʼ��`.2` ��ʾ������λС������ `f` ��ʾ��������
	 - `%%`: ������������ٷֺŵ�ת�����С���Ϊ `%` �ڸ�ʽ���ַ�������һ�������ַ���
		����Ϊ�˲���ʵ�ʵ� `%` ���ţ���Ҫʹ�� `%%`��
4. `Hum`: ����һ����������ʾҪ���뵽��ʽ���ַ����еľ��帡����ֵ��
�ۺ���������仰����˼�ǽ����� `Hum` ��ֵ���մ�����λС���ĸ�������ʽ��
���뵽�ַ����У����һ�����ֵǰ���һ���ո񣬲�������ֵ�����һ���ٷֺš�
���磬��� `Hum` ��ֵ�� 75.25����ô��ʽ����Ľ�������� `" 75.25%"`��
AHT10ReadData(float *temperature,u8 *humidity);
sprintf(String, "+%.2fC", temperature);//��ʽ���ַ���������ַ�������

*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
  #pragma import(__use_no_semihosting) /*��׼����Ҫ��֧�ֺ���*/
  struct __FILE
  {
	  int handle;

  };

   FILE __stdout;
  /*����_sys_exit()�Ա���ʹ�ð�����ģʽ*/
 void _sys_exit(int x)
  {
	x=x; 

  }
	
	/***************************���������������*****************************/
//__use_no_semihosting was requested, but _ttywrch was 
void _ttywrch(int ch)
{
    ch = ch;
}
/***************************���������������*****************************/

 int fputc(int ch,FILE*f)
  {
	while((USART1->SR&0X40)==0){};  //ѭ������ֱ���������
    USART1->DR=(u8)ch;
	return ch;
  }
	


#endif
  
	
/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 3;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}

/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&nvicInitStruct);

}




/*
************************************************************
*	�������ƣ�	Usart3_Init
*
*	�������ܣ�	����3��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PB10		RX-PB11
************************************************************
*/
void Usart3_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//Pb10	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitStruct);
	
	//Pb11	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_11;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART3, &usartInitStruct);
	
	USART_Cmd(USART3, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}

/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}

/*
************************************************************
*	�������ƣ�	UsartPrintf
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
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}


/*
************************************************************
*	�������ƣ�	lora_send_Byte
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				�����ֽ�
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/

void lora_send_Byte(char Byte)
{
	USART_SendData(USART1,Byte);
	/*�ȴ��������DR�Ĵ���Ϊ��*/
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		//�ȴ��������
}

void lora_send_buf(char *buf, uint16_t len)
{
	uint16_t i;
	for(i= 0;i<len;i++)
	{
		lora_send_Byte(buf[i]);
	}
}

/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	����1�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}

}


/*
************************************************************
*	�������ƣ�	USART2_IRQHandler
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
//void USART3_IRQHandler(void)                   //����1�жϷ������
//  {
//	uint8_t Res;
//	static uint8_t  Res_state = 0;
//	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)  //�����жϣ����յ�һ���ֽ����ݣ�
//	{
//		Res = USART_ReceiveData(USART3);     //�ѽ��յ����ֽڱ���
//	  switch(Res_state)
//		{
//			case 0:    //'A' Ϊ�ı�ģʽ����/����ASCII��
//				if((Res=='A')&& !rxd_flag)  //�ж�֡ͷ && ��ֹ����
//				{
//					Res_state=1;  //�л�Ϊ��һ��״̬
//					rxd_index=0;  //��������0�������´ν��Ž���
//				}
//				else{
//					Res_state=0;  //֡ͷ���ԣ���ѭ��
//				}
//			  LED0 = 1;   
//			break;
//			case 1:
//				if(Res=='\r')
//				{
//					Res_state=2;   //������һ��״̬
//				}
//				else
//				{
//					rxd_buf[rxd_index] = Res;  //�������������ݴ���BUF
//		  	  rxd_index++;    //һ������
//				}
//				LED0 = 0;  
//			 break; 
//			case 2:
//				if(Res=='\n')
//				{
//					rxd_flag=1;      //�л���־λ���������ݽ������
//					Res_state=0;     //���״̬�������´ν���
//				} 
//				break;
//		}
//		
//	}
//     USART_ClearITPendingBit(USART3,USART_IT_RXNE);
//	   //USART_ClearITPendingBit(USART1,USART_IT_IDLE);
//  }

	


