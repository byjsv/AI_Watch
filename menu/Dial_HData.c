#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "ds18b20.h"
#include "max30102.h"
#include "Dial_HData.h"
#include "freeRTOS.h"
#include "task.h"
#include "Delay.h"
#include "Key.h"
#include "sport_mode.h"

#include "Serial.h"

#include "queue.h"

#define tempX 0
#define tempY 0

#define HRateX 0
#define HRateY 16

#define OxRateX 0
#define OxRateY 32

#define DStepX 0
#define DStepY 48




healthData HData = {0,0,0,0};

void Dial_HData_Init(void)
{
	xTaskCreate(vUpdateData, "UpdateData", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
}

void Dial_ShowData_Line(uint16_t num,uint16_t MIN,uint16_t MAX)
{	
	
	
	//OLED_ShowNum(0,16,CursorPosX,3,OLED_8X16);
}

void Dial_HData_Line_Temp(void)
{
	uint8_t Line_PosX=0;
	uint16_t MIN=200;
	uint16_t MAX=500;
	uint16_t num=0;
	OLED_Clear();
	while(1)
	{
		num = HData.temperature;
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		
		OLED_DrawPoint(Line_PosX,64-(num-MIN)*64/(MAX-MIN));
		if((Line_PosX)<(128*3/4))
		{
			(Line_PosX)++;
		}else
		{
			OLED_DisplayBuffMove(OLED_Left);
		}
		
		OLED_ShowString_12X12(0,2,"温度:");
		OLED_ShowNum(30,0,num,3,OLED_8X16);
		
		OLED_Update();
		vTaskDelay(pdMS_TO_TICKS(100));
		
	}
}

void Dial_HData_Line_HRate(void)
{
	uint8_t Line_PosX=0;
	uint16_t MIN=20;
	uint16_t MAX=200;
	uint16_t num=0;
	OLED_Clear();
	while(1)
	{
		num = HData.HRate;
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		
		OLED_DrawPoint(Line_PosX,64-(num-MIN)*64/(MAX-MIN));
		if((Line_PosX)<(128*3/4))
		{
			(Line_PosX)++;
		}else
		{
			OLED_DisplayBuffMove(OLED_Left);
		}
		
		OLED_ShowString_12X12(0,2,"心率:");
		OLED_ShowNum(30,0,num,3,OLED_8X16);
		
		OLED_Update();
		vTaskDelay(pdMS_TO_TICKS(100));
		
	}
}

void Dial_HData_Line_OxRate(void)
{
	uint8_t Line_PosX=0;
	uint16_t MIN=70;
	uint16_t MAX=120;
	uint16_t num=0;
	OLED_Clear();
	while(1)
	{
		num = HData.OxRate;
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		
		OLED_DrawPoint(Line_PosX,64-(num-MIN)*64/(MAX-MIN));
		if((Line_PosX)<(128*3/4))
		{
			(Line_PosX)++;
		}else
		{
			OLED_DisplayBuffMove(OLED_Left);
		}
		
		OLED_ShowString_12X12(0,2,"血氧:");
		OLED_ShowNum(30,0,num,3,OLED_8X16);
		
		OLED_Update();
		vTaskDelay(pdMS_TO_TICKS(100));
		
	}
}


/****************控件布局***********************/

void Health_Plate(void)
{ 				

	OLED_ShowNum_Left(tempX,tempY,HData.temperature/10,2,OLED_8X16);
	OLED_ShowNum_Left(tempX+8*2+8,tempY,HData.temperature%10,1,OLED_8X16);
	OLED_ShowChar(tempX+8*2,tempY,'.',OLED_8X16);
	OLED_ShowString(tempX+24+8,tempY,"℃",OLED_8X16);
	OLED_ShowString_12X12(tempX+12+5*8,   tempY+(16-12)/2,"体表温度");
	
	OLED_ShowImage(HRateX,   HRateY+(16-12)/2,12,12,HRate);
	OLED_ShowNum_Left(HRateX+12,HRateY, HData.HRate,3,OLED_8X16);
	OLED_ShowString_12X12(HRateX+12+4*8,  HRateY+(16-12)/2,"心率");
	
	OLED_ShowImage(OxRateX,   OxRateY+(16-12)/2,12,12,OxRate);
	OLED_ShowNum_Left(OxRateX+12,OxRateY, HData.OxRate,3,OLED_8X16);
	OLED_ShowChar(OxRateX+12+3*8,OxRateY+8,'%',OLED_6X8);
	OLED_ShowString_12X12(OxRateX+12+4*8,   OxRateY+(16-12)/2,"血氧饱和度");
	
	OLED_ShowImage(DStepX,   DStepY+(16-12)/2,12,12,step);
	OLED_ShowNum_Left(DStepX+12,DStepY, HData.DailyStep,3,OLED_8X16);
	OLED_ShowString_12X12(OxRateX+12+4*8,   OxRateY+(16-12)/2,"");
	
	//OLED_ShowString();
}

//int main(void) 
//{
//    System_Init();
//    Sensor_Init();
//    Collect_Initial_Samples();
//    
//    while(1) {
//        Process_Sensor_Data();
//		//display_hr-20;
//		//display_spO2;
//        delay_ms(10); // 适当延时
//    }
//}

void vUpdateData(void *pvParameters)
{

	Sport_MODE_Init();
	System_Init();
	Sensor_Init();
	Collect_Initial_Samples();
	
	while(1)
	{
		Sport_getData();
		Process_Sensor_Data();
		
		
		HData.temperature = DS18B20_Get_Temp();
		HData.HRate = display_hr;
		HData.OxRate = display_spO2;
		HData.DailyStep = Watch_Posture.step;
		
		vTaskDelay(pdMS_TO_TICKS(30));
		
	}
}


