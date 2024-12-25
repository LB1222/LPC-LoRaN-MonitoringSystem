
/*
*********************************************************************************************************
*
*	模块名称 : 数据本地化处理模块
*	文件名称 : bsp_dateupload.c
*	版    本 : V1.0
*	说    明 : 驱动LED指示灯，配合新建工程使用，非完整文件
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2023-10-4  刘斌  正式发布
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"

/************************************************************************************************
 * 函 数 名: Date_deal
 * 函数功能: 数据本地处理
 * 函数参数: 无
 * 返 回 值: 无
 ***********************************************************************************************/
 
 void Date_deal(void)
 {
	 if(Temp_value>35||Hum_value>90)
	 {
		      CO2_SensorCS(); //使能CO2模块引脚，饱和三极管，给模块供电，高功耗
		      ADC_DC_EN_SensorEN(); //使能ADC电压检测引脚，饱和三极管，给模块供电，高功耗
		      GPS_EN_SensorEN();//使能GPS模块检测引脚，饱和三极管，给模块供电，高功耗
		      printf("DC Capacity!\r\n");
		    	Get_battery_volt();
				  delay_ms(50);
				 // Get_Light_value();
			  //  delay_ms(50);
		      LowPower_Calculate_Co2Value();
//					delay_ms(50);
//          printf("start AHT10!\r\n");
	        Read_AHT10();
		 	    printf("start GPS!\r\n");
					printGpsBuffer();
					delay_ms(50);
		 
		 lora_send_Byte(0X22);
		 lora_send_Byte(0X25);
		 lora_send_Byte(0X22);
		 sensor_AllDate_Upload(); //所有数据上传
		   	bsp_BeepOff();
		    delay_ms(100);
		    bsp_BeepOn();
		      delay_ms(200);
	 }

	 else
	 {
          ADC_DC_EN_SensorCS(); 
		      GPS_EN_SensorCS();
		      CO2_SensorEN(); //使能CO2模块引脚，饱和三极管，给模块供电，高功耗
		 	    printf("start CO2!\r\n");
		 		  LowPower_Calculate_Co2Value();
					delay_ms(50);	
				  Get_Light_value();
			    delay_ms(50);
          printf("start AHT10!\r\n");
	        Read_AHT10();
		 		 	
          lora_send_Byte(0X22);
		      lora_send_Byte(0X25);
		      lora_send_Byte(0X22);
			    sensor_BasisDate_Upload();//基础数据上传
	 }
}
 
