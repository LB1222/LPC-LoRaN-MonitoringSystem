//========================================================================
//	爱好者电子工作室-淘宝 https://devotee.taobao.com/
//	STM32四轴爱好者QQ群: 799870988
//	作者：小刘
//	电话:13728698082
//	邮箱:1042763631@qq.com
//	日期：2020.05.17
//	版本：V1.0
//========================================================================
//套件购买地址：https://devotee.taobao.com/
//套件购买地址：https://devotee.taobao.com/
//                 爱好者电子工作室
//特此声明：
//
//         此程序只能用作学习，如用商业用途。必追究责任！
//          
//
//
#include "ALL_DEFINE.h"
#include "scheduler.h"
#include "spl06.h"
#include "ANO_Data_Transfer.h"
#include "WIFI_UFO.h"
#include "flow.h"
#include "ADC.h"

loop_t loop; 
u32 time[10],time_sum;
 
void Loop_check()
{
	loop.cnt_2ms++;
	loop.cnt_4ms++;
	loop.cnt_6ms++;
	loop.cnt_10ms++;
	loop.cnt_20ms++;
	loop.cnt_50ms++;
	loop.cnt_1000ms++;

	if( loop.check_flag >= 1)
	{
		loop.err_flag ++;// 2ms 
	}
	else
	{
		loop.check_flag += 1;   //该标志位在循环后面清0
	}
}
void main_loop()
{
	if( loop.check_flag >= 1 )
	{
		
		if( loop.cnt_2ms >= 1 )
		{
			loop.cnt_2ms = 0;
			
			Duty_2ms();	 					//周期2ms的任务
		}
		if( loop.cnt_4ms >= 2 )
		{
			loop.cnt_4ms = 0;
			Duty_4ms();						//周期4ms的任务
		}
		if( loop.cnt_6ms >= 3 )
		{
			loop.cnt_6ms = 0;
			Duty_6ms();						//周期6ms的任务
		}
		if( loop.cnt_10ms >= 5 )
		{
			loop.cnt_10ms = 0;
			Duty_10ms();					//周期10ms的任务
		} 
		if( loop.cnt_20ms >= 10 )
		{
			loop.cnt_20ms = 0;
			Duty_20ms();					//周期20ms的任务
		}
		if( loop.cnt_50ms >= 25 )
		{
			loop.cnt_50ms = 0;
			Duty_50ms();					//周期50ms的任务
		}
		if( loop.cnt_1000ms >= 500)
		{
			loop.cnt_1000ms = 0;
			Duty_1000ms();				//周期1s的任务
		}
		loop.check_flag = 0;		//循环运行完毕标志
	}
}
/////////////////////////////////////////////////////////
void Duty_2ms()
{
	time[0] = GetSysTime_us();
	
	MpuGetData();				          //读取陀螺仪数据
	FlightPidControl(0.002f);     /// 姿态控制
	MotorControl();               //电机控制
	
	time[0] = GetSysTime_us() - time[0];
}
//////////////////////////////////////////////////////////
void Duty_4ms()
{
	time[1] = GetSysTime_us();
	
	ANO_NRF_Check_Event();    //扫描接收2.4G信号
	ANO_DT_Data_Exchange();		//返回飞机数据到遥控器
	Rc_Connect();  						//解析遥控器数据
	Mode_Controler(0.004f); 	//模式输入选择控制
	time[1] = GetSysTime_us() - time[1];
}
//////////////////////////////////////////////////////////
void Duty_6ms()
{
	time[2] = GetSysTime_us();
	
	GetAngle(&MPU6050,&Angle,0.006f);   //更新姿态数据
	
	time[2] = GetSysTime_us() - time[2];
}
/////////////////////////////////////////////////////////
void Duty_10ms()
{
	time[3] = GetSysTime_us();

	
	RC_Analy();	     					//遥控器控制指令处理
	Pixel_Flow_Fix(0.006f);  			//mini光流数据融合	
	Flow_Pos_Controler(0.006f);		//光流定点控制	
	Att_Err_Check(0.01f);     //姿态异常检测
	Height_Get(0.01f);			//获取高度数据	
	High_Data_Calc(10);			//高度数据融合		
	
	HeightPidControl(0.006f); 		//气压高度控制
	
	time[3] = GetSysTime_us() - time[3];
}
/////////////////////////////////////////////////////////
void Duty_20ms()
{
	time[4] = GetSysTime_us();

	ANTO_polling(); 	//串口3在飞机 输出数据到 匿名上位机
		 

				 
	time[4] = GetSysTime_us() - time[4];
}
//////////////////////////////////////////////////////////
void Duty_50ms()
{
	time[5] = GetSysTime_us();
	
	PilotLED(); 						//LED刷新
	
	Flag_Check();   			 //传感器状态标志
	
	Voltage_Check();			//飞控电压检测
	
	time[5] = GetSysTime_us() - time[5];
}
/////////////////////////////////////////////////////////////
void Duty_1000ms()
{
	u8 i;
  NRF_SSI = NRF_SSI_CNT;  //NRF信号强度
	NRF_SSI_CNT = 0;
	
	WIFI_SSI = WIFI_SSI_CNT;//WiFi信号强度
	WIFI_SSI_CNT = 0;
	
	Locat_SSI = Locat_SSI_CNT;//视觉位置数据频率
	Locat_SSI_CNT = 0;
	
	Flow_SSI = Flow_SSI_CNT;  //光流数据频率
	Flow_SSI_CNT = 0;
	
		//检测视觉定位模块是否插入
	if(Locat_SSI>10)  Locat_Err = 0;
	else Locat_Mode=0,Locat_Err = 1;
	
	  //检测光流模块是否插入
	if(Flow_SSI>10)  Flow_Err = 0;
	else 						 Flow_Err = 1;
	
	
		if(ON_flag==1)
		{
			move_Controler();
		}
	
	
	
	
	
	time_sum = 0;
	for(i=0;i<6;i++)	time_sum += time[i];
	
}



//////////////////////////end///////////////////////////////////////////