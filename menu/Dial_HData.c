#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "ds18b20.h"
#include "Dial_HData.h"
#include "freeRTOS.h"
#include "task.h"
#include "Delay.h"
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


uint8_t Line_PosX=0;

healthData HData = {0,0,0,0};

void Dial_HData_Init(void)
{
	xTaskCreate(vUpdateData, "UpdateData", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
}

void Dial_ShowData_Line(uint16_t num,uint16_t MIN,uint16_t MAX)
{	
	
	OLED_DrawPoint(Line_PosX,64-(num-MIN)*64/(MAX-MIN));
	if((Line_PosX)<(128*3/4))
	{
		(Line_PosX)++;
	}else
	{
		OLED_DisplayBuffMove(OLED_Left);
	}
	//OLED_ShowNum(0,16,CursorPosX,3,OLED_8X16);
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

void vUpdateData(void *pvParameters)
{

	while(1)
	{
		Sport_getData();
		
		
		HData.temperature = DS18B20_Get_Temp();
		HData.HRate = 80;
		HData.OxRate = 100;
		HData.DailyStep = Watch_Posture.step;
		
		TaskDelay_ms(30);
		
	}
}


