/*
*********************************************************************************************************
*
*	模块名称 : LED指示灯驱动模块
*	文件名称 : bsp_key.h
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯，配合新建工程使用，非完整文件
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023.8.21  刘斌    keytest
*
*	
*
*********************************************************************************************************
*/
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include"sys.h"



#define RCC_ALL_KEY ( WKUP_GPIO_CLK|KEY0_GPIO_CLK)


#define WKUP_GPIO_PIN      GPIO_Pin_1       //WKUP引脚号（小端口号）
#define WKUP_PIN_ID         1               //WKUP引脚序号
#define WKUP_GPIO_PORT     GPIOA            //WKUP端口号（大端口号）
#define WKUP_GPIO_CLK      RCC_APB2Periph_GPIOA    //WKUP时钟
//#define WKUP_FUN_OUT       PAout             //WKUP输出端口配置函数
#define WKUP_FUN_IN        PAin            //WKUP输入端口配置函数
#define WKUP_GPIO_MODE     GPIO_Mode_IPU    //WKUP端口输入模式
#define WKUP_ACTIVE_LEVEL   1               //WKUP按键有效电平为高电平


#define KEY0_GPIO_PIN      GPIO_Pin_4          //KEY0 引脚号
#define KEY0_PIN_ID        4                   //KEY0 引脚序号
#define KEY0_GPIO_PORT     GPIOA               //KEY0 端口号
#define KEY0_GPIO_CLK      RCC_APB2Periph_GPIOA          //KEY0 时钟
//#define KEY0_FUN_OUT       PEout               //KEY0 输出端口配置函数
#define KEY0_FUN_IN        PAin                //KEY0 输入端口配置函数
#define KEY0_GPIO_MODE     GPIO_Mode_IPU       //KEY0 端口输入模式
#define KEY0_ACTIVE_LEVEL  1                   //KEY0 按键有效电平为低电平
        //KEY0 按键有效电平为低电平


//IO操作函数
#define WKUP  WKUP_FUN_IN(WKUP_PIN_ID)//WKUP
#define KEY0  KEY0_FUN_IN(KEY0_PIN_ID)//KEY0


/*供外部调用的函数声明 */
void bsp_InitKey(void);
void EXTIx_Init(void);
void EXTI4_IRQHandler(void);






#endif

