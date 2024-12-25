
/*
*********************************************************************************************************
*
*	ģ������ : ���ݱ��ػ�����ģ��
*	�ļ����� : bsp_dateupload.c
*	��    �� : V1.0
*	˵    �� : ����LEDָʾ�ƣ�����½�����ʹ�ã��������ļ�
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2023-10-4  ����  ��ʽ����
*
*	
*
*********************************************************************************************************
*/

#include "bsp.h"

/************************************************************************************************
 * �� �� ��: Date_deal
 * ��������: ���ݱ��ش���
 * ��������: ��
 * �� �� ֵ: ��
 ***********************************************************************************************/
 
 void Date_deal(void)
 {
	 if(Temp_value>35||Hum_value>90)
	 {
		      CO2_SensorCS(); //ʹ��CO2ģ�����ţ����������ܣ���ģ�鹩�磬�߹���
		      ADC_DC_EN_SensorEN(); //ʹ��ADC��ѹ������ţ����������ܣ���ģ�鹩�磬�߹���
		      GPS_EN_SensorEN();//ʹ��GPSģ�������ţ����������ܣ���ģ�鹩�磬�߹���
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
		 sensor_AllDate_Upload(); //���������ϴ�
		   	bsp_BeepOff();
		    delay_ms(100);
		    bsp_BeepOn();
		      delay_ms(200);
	 }

	 else
	 {
          ADC_DC_EN_SensorCS(); 
		      GPS_EN_SensorCS();
		      CO2_SensorEN(); //ʹ��CO2ģ�����ţ����������ܣ���ģ�鹩�磬�߹���
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
			    sensor_BasisDate_Upload();//���������ϴ�
	 }
}
 
