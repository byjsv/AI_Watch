#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "freeRTOS.h"
#include "task.h"
#include "MyRTC.h"
#include "Encoder.h"
#include "Key.h"
#include "ds18b20.h"
#include "Dial.h"


void test_Dial_RunPlate()
{
	OLED_Init();					//OLED初始化

	MyRTC_Init();
	Encoder_Init();
	Key_Init();
	Delay_Init();
	
	while(DS18B20_Init())	//DS18B20初始化	
	{
		OLED_ShowString(0,0,"ds18b20 Error!",OLED_8X16);
		
		OLED_Update();
	}
	
	
	Dial_RunPlate();
}
 
TaskHandle_t myTaskHandler;
void myTask(void * arg){
	
    test_Dial_RunPlate();
	//while(1){
	//	
	//	OLED_ShowNum(0,0,1,1,OLED_8X16); 
	//	OLED_Update();
	//	vTaskDelay(500);
	//	OLED_ShowNum(0,0,0,1,OLED_8X16); 
	//	OLED_Update();
	//	vTaskDelay(500);
	//		
	//}
}
 



int main(void)
{
	OLED_Init();
	
	test_Dial_RunPlate();
	
	//xTaskCreate(myTask,"myTask",512,NULL,2,&myTaskHandler);
	//vTaskStartScheduler();
	while (1)
	{
		
	}
}

