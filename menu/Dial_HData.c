#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "ds18b20.h"

#define tempX 0
#define tempY 0

#define HRateX 0
#define HRateY 16

#define OxRateX 0
#define OxRateY 32

#define DStepX 0
#define DStepY 48

typedef struct {
	short temperature;
	uint8_t HRate;
	uint8_t OxRate;
	uint32_t DailyStep;
}healthData;

healthData  hData = {0,10,100,10000};

uint8_t Line_PosX=0;

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


//short temperature = 0;
void Health_Plate()
{ 				//温度值
    
	hData.temperature=DS18B20_Get_Temp();	//读取温度
	OLED_ShowNum(tempX,tempY,hData.temperature/10,2,OLED_8X16);
	OLED_ShowNum(tempX+8*2+8,tempY,hData.temperature%10,1,OLED_8X16);
	OLED_ShowChar(tempX+8*2,tempY,'.',OLED_8X16);
	OLED_ShowString(tempX+24+8,tempY,"℃",OLED_8X16);
	OLED_ShowString_12X12(tempX+12+5*8,   tempY+(16-12)/2,"体表温度");
	
	OLED_ShowImage(HRateX,   HRateY+(16-12)/2,12,12,HRate);
	OLED_ShowNum  (HRateX+12,HRateY, hData.HRate,3,OLED_8X16);
	OLED_ShowString_12X12(HRateX+12+4*8,  HRateY+(16-12)/2,"心率");
	
	OLED_ShowImage(OxRateX,   OxRateY+(16-12)/2,12,12,OxRate);
	OLED_ShowNum  (OxRateX+12,OxRateY, hData.OxRate,3,OLED_8X16);
	OLED_ShowChar(OxRateX+12+3*8,OxRateY+8,'%',OLED_6X8);
	OLED_ShowString_12X12(OxRateX+12+4*8,   OxRateY+(16-12)/2,"血氧饱和度");
	
	OLED_ShowImage(DStepX,   DStepY+(16-12)/2,12,12,step);
	OLED_ShowNum  (DStepX+12,DStepY, hData.DailyStep,3,OLED_8X16);
	OLED_ShowString_12X12(OxRateX+12+4*8,   OxRateY+(16-12)/2,"");
	
	//OLED_ShowString();
}

