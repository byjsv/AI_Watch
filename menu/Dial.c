#include "stm32f10x.h"                  // Device header

#include "freeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Dial.h"

#include "Menu_Show.h"
#include "OLED.h"
#include "ds18b20.h"
#include "Key.h"
#include "MyRTC.h"
#include "Delay.h"

#include "Serial.h"

#include "string.h"


/****************工具函数**************/




/****************控件函数********************/

void Dial_ShowText(int16_t X, int16_t Y,int16_t MaxX, int16_t MaxY, char *String, uint8_t FontSize)		//字符集为GB2312
{
	uint16_t i = 0;
	char SingleChar[5];
	uint8_t CharLength = 0;
	uint16_t XOffset = 0;
	uint16_t pIndex;
	
	while (String[i] != '\0')	//遍历字符串
	{		

		/*此段代码的目的是，提取GB2312字符串中的一个字符，转存到SingleChar子字符串中*/
		/*判断GB2312字节的最高位标志位*/
		if ((String[i] & 0x80) == 0x00)			//最高位为0
		{
			CharLength = 1;						//字符为1字节
			SingleChar[0] = String[i ++];		//将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
			SingleChar[1] = '\0';				//为SingleChar添加字符串结束标志位
		}
		else									//最高位为1
		{
			CharLength = 2;						//字符为2字节
			SingleChar[0] = String[i ++];		//将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
			if (String[i] == '\0') {break;}		//意外情况，跳出循环，结束显示
			SingleChar[1] = String[i ++];		//将第二个字节写入SingleChar第1个位置，随后i指向下一个字节
			SingleChar[2] = '\0';				//为SingleChar添加字符串结束标志位
		}
		if(XOffset+FontSize > MaxX && !(CharLength == 1 && SingleChar[0]=='\n'))         //    缺字显示
		{
			XOffset = 0;
			Y += (FontSize==OLED_6X8)?8:16;
			if(Y>MaxY)return;
		}
		
		/*显示上述代码提取到的SingleChar*/
		if (CharLength == 1)	//如果是单字节字符
		{
			if(SingleChar[0]=='\n')         //   解析到\n换行操作
			{
				XOffset = 0;
				Y += (FontSize==OLED_6X8)?8:16;
				if(Y>MaxY)return;
			}
			else
			{
				/*使用OLED_ShowChar显示此字符*/
				OLED_ShowChar(X + XOffset, Y, SingleChar[0], FontSize);
				XOffset += FontSize;
			}
		}
		else					//否则，即多字节字符
		{
			/*遍历整个字模库，从字模库中寻找此字符的数据*/
			/*如果找到最后一个字符（定义为空字符串），则表示字符未在字模库定义，停止寻找*/
			for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
			{
				/*找到匹配的字符*/
				if (strcmp(OLED_CF16x16[pIndex].Index, SingleChar) == 0)
				{
					break;		//跳出循环，此时pIndex的值为指定字符的索引
				}
			}
			if (FontSize == OLED_8X16)		//给定字体为8*16点阵
			{
				/*将字模库OLED_CF16x16的指定数据以16*16的图像格式显示*/
				OLED_ShowImage(X + XOffset, Y, 16, 16, OLED_CF16x16[pIndex].Data);
				XOffset += 16;
			}
			else if (FontSize == OLED_6X8)	//给定字体为6*8点阵
			{
				/*空间不足，此位置显示'?'*/
				OLED_ShowChar(X + XOffset, Y, '?', OLED_6X8);
				XOffset += OLED_6X8;
			}
		}
	}
}

//void Dial_ShowText_contral()
//{
//	uint8_t Roll_Event;
//	
//	while(1)
//	{
//		Roll_Event = Dial_RollEvent();
//		if(Roll_Event)
//		{
//			Roll_Event = Dial_RollEvent();
//		
//		}
//		if(Roll_Event)
//		{
//			
//			
//			//select += Roll_Event;
//			
//			
//			OLED_Clear();
//		}
//		else
//		{
//			
//		}
//	}
//}


			/***********设置选项***********/
void Show_Setting()
{
	OLED_ShowImage((127-50)/2,(64-50)/2+10,50,50,Setting);

}

void Show_APP()
{
	uint8_t wide = 50;
	uint8_t high = 36;
	OLED_ShowImage((127-wide)/2,(64-high)/2+10,wide,high,whale);

}

void Dial_ShowData(uint8_t temp,uint8_t HRate, uint8_t Oxygen)
{

}




void Health_Plate_Exit()
{

}

void Plate_ShowName(char *Name,uint8_t Y)
{
	uint8_t length_name=0;
	
	while(Name[length_name]!='\0')
	{
		length_name++;
	}
	
	OLED_ShowString_12X12(63-length_name*6/2,Y,Name);
	//OLED_ReverseArea();
}

/*********************主界面选项**********************/
struct Plate_class{                        //  选项结构体
	char *Plate_Name;		// 选项名字
	void (*func)(void);     // 显示函数指针
	void (*func_Exit)(void);          //  退出函数
	void (*enter_func)(void);
};


TaskHandle_t buttomHandle;          // 按键消息句柄
TaskHandle_t DialShow_Handle;          // 显示消息句柄
TaskHandle_t UpdateData_Handle;          // 更新数据句柄


/**
 * @brief 菜单展示任务
 * 
 * @param *pvParameters  无关参数
 * @return 无
 * @note 特殊注意事项或限制
 * @warning 重要警告信息
 */
void vDialShow_Task(void *pvParameters)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();    //   用于绝对延时的TickType

	int8_t select=0;			//	界面下标
	uint8_t length = 0;
	
	struct Plate_class plate[] = {
		{"时间",Time_Plate,Time_Plate_Exit},
		{"",Health_Plate,Health_Plate_Exit,HealthMenu},
		{"功能",Show_APP,NULL_Func,FunctionMenu},
		{"设置",Show_Setting,NULL_Func,SettingMenu},
		{".."}
	};
	
	while(plate[length].Plate_Name[0]!='.')			//		计算有几个选项
	{
		length++;
	}
	
	while (1) {
		
		        // 1. 非阻塞检查按键
        KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {			
				 // 调用退出函数
				if (plate[select].func_Exit != NULL) {
					plate[select].func_Exit();
				}
				
                select--;
				
				//到边界循环
				select = (select < 0) ? (length - 1) : (select % length);
				
				OLED_Clear();
			}
			
			
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {		
				 // 调用退出函数
				if (plate[select].func_Exit != NULL) {
					plate[select].func_Exit();
				}
				
                select++;
				
				//到边界循环
				select = (select < 0) ? (length - 1) : (select % length);

				OLED_Clear();
            }
			
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {		
                if(plate[select].enter_func!=NULL)		//	若点击函数不为空
				{
					plate[select].enter_func();			//	执行点击函数
				}
            }
        }

        // 调用显示函数
        if (plate[select].func != NULL) {
            plate[select].func();
			Plate_ShowName(plate[select].Plate_Name,0);
        }
		

        // 更新显示
        OLED_Update();

        // 延时 30ms
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

//void vUpdateData(void *pvParameters)
//{
//	while(1)
//	{
//		hData.temperature = 1;
//		//Sport_getData();
//		//HData_SetData(DS18B20_Get_Temp(),0,0,Watch_Posture.step);
//		TaskDelay_ms(10);
//		
//	}
//}

/**
 * @brief 用于启动任务的函数
 * 
 * @param 无
 * @return 无
 */
void Dial_RunPlate()
{
	Sport_MODE_Init();
	
	
	Key_Init();		// 包括了按键任务创建
	
	Serial_Init();
	
	Dial_HData_Init();		//		包括了采集数据任务的创建
	
	
    // 创建显示任务
    xTaskCreate(vDialShow_Task, "DialShowTask", configMINIMAL_STACK_SIZE*3, NULL, 3, &DialShow_Handle);
	


    // 启动调度器
    vTaskStartScheduler();

    // 如果调度器启动失败，进入死循环
    for (;;)
	{
	}
}

