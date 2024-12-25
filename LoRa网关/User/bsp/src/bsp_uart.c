/*
*********************************************************************************************************
*
*	模块名称 : 串口驱动模块
*	文件名称 : bsp_uart.c
*	版    本 : V1.0
*	说    明 : 实现printf重定向到串口1，即支持printf信息到USART1
*

*********************************************************************************************************
*/
#include "bsp.h"

#if EN_USART1_RX	//如果使能了接收

uint8_t USART_RX_BUF[USART_REC_LEN];		//接收缓冲，最大USART_REC_LEN个字节
uint8_t ReceiveState = 0;					//接收字符数
uint16_t RxCounter = 0;						//接收状态指示（0：未接受，1：接收）

#endif

/*
*********************************************************************************************************
*	函 数 名: bsp_InitUart1
*	功能说明:初始化CPU的USART1串口硬件设备,未启用中断。
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/

void bsp_InitUart1(uint32_t baud)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	
#if EN_USART1_RX	//如果使能了接收
	
	NVIC_InitTypeDef	NVIC_InitStructure;
	
#endif
	
	//1.串口1 TX = PA9  RX = PA10
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//打开GPIO时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//打开UART时钟
	
	//配置 USART TX 为复用功能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推免输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//PA9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.9
	
	//配置 USART RX 为复用功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化GPIOA.10
	
	//2.配置串口硬件参数
	USART_InitStructure.USART_BaudRate = baud;//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_Init(USART1,&USART_InitStructure);//初始化串口1
	
#if EN_USART1_RX		//如果使能了接收
	
	//3.Usart1 NVIC配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ通道使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级3
	NVIC_Init(&NVIC_InitStructure);//根据指定的参数初始化NVIC寄存器
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启串口接收中断
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);//开启串口空闲中断
#endif
	//4.使能串口1
	USART_Cmd(USART1,ENABLE);	
}

void USART1_IRQHandler(void)//串口1中断服务函数
{
	uint8_t Res = Res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE )!= RESET)//接收中断（接收到一个字节的数据）
	{
		USART_RX_BUF[RxCounter++] = USART1->DR;//把接收到的数据保存
	}
	if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)//接收中断（接收到1帧的数据）
	{
		Res = USART1->SR;//读SR寄存器
		Res = USART1->DR;//读DR寄存器（先读SR，在读DR，就是为了清除IDLE中断）
		ReceiveState = 1;//标记接收状态置位
	}
}

//串口0状态清除函数
void Uart0_STA_Clr(void)
{
	RxCounter = 0;//串口BUF计数清零
	ReceiveState = 0;//接收状态清零
}

//加入以下代码，支持printf函数，而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义——sys——exit（）以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}

//重定义fputc函数，这样可以使用printf函数从串口1打印输出
int fputc(int ch,FILE *f)
{
	while((USART1->SR&0x40)==0){};//循环发送，直到发送完毕
	USART1->DR = (u8)ch;
	return ch;	
}
#endif

//USART1发送len个字，buf：发送区首地址 len：发送的字节数
void USART1_Send_Data(uint8_t *buf,uint8_t len)
{
	uint8_t t;
	
	for(t=0;t<len;t++)//循环发送
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)== RESET);
		USART_SendData(USART1,buf[t]);			
	}
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)== RESET);
}


/**********************************************************************************************************/
