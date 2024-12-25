/*
*********************************************************************************************************
*	函 数 名: bsp_InitKey
*	功能说明: 初始化按键。该函数被 bsp_Init()调用
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
#include "bsp.h"

void bsp_InitKey(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	//第一步：打开GPIO时钟*
	RCC_APB2PeriphClockCmd(RCC_ALL_KEY,ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);/*关闭jtag,使能SWD,可以用SWD模式调试*/
	/*第二步：配置所有的按键GPIO*/
	GPIO_InitStructure.GPIO_Pin =KEY0_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =KEY0_GPIO_MODE ;
	GPIO_Init(KEY0_GPIO_PORT,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin =WKUP_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode =WKUP_GPIO_MODE ;
	GPIO_Init(WKUP_GPIO_PORT,&GPIO_InitStructure);
	
	
	 

    // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 配置PB4引脚为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 最大输出速度50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 初始化GPIOB

    // 将PB4引脚输出低电平
    GPIO_ResetBits(GPIOB, GPIO_Pin_4);

}


/*
按键KEY_UP上拉，KEY0,KEY1下拉
KEY_UP  PA0
KEY0    PE4
KEY1    PE3
*/


void EXTIx_Init(void)
{
	//开启复用IO口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//初始化io输入函数，这里我们可以用按键作为输入
  bsp_InitKey();   //调用已经配制好的按键函数
	
	//设置IO口与中断线的映射
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
	
	//初始化线上中断，设置触发条件
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 ;  //PE4选择线4
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断还是事件触发模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//选择下降沿
	EXTI_Init(&EXTI_InitStructure);
	
	//配置中断函分组（NVIC），并使能
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //因为选择中断优先级为2，所以只能选0-3；
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
}
	

void EXTI4_IRQHandler(void)
{
	
		//编写中断服务函数
	delay_ms(10);     //延时，防抖动
	if(KEY0 == 0)   //判断是否按下
	{
		LED0 = !LED0;
			bsp_BeepOn();
					bsp_LedToggle(1);
	}
	
	//清除终端标志位
	EXTI_ClearFlag(EXTI_Line1);
	
}


