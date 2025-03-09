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
#include "Encoder.h"

#include "string.h"



int8_t Dial_RollEvent(void) // 菜单滚动
{
	if (Key_Up_Get()) // 按键上接到PB15;
	{
		return 1;
	}
	if (Key_Down_Get()) // 按键下接到PB13;
	{
		return -1;
	}
	return Encoder_Get_Div4(); // 旋钮编码器PA8,PA9;
}
int8_t Dial_EnterEvent(void) // 菜单确认
{
	return Key_Enter_Get(); // 确认键接到PB14;
}
int8_t Menu_BackEvent(void) // 菜单返回
{
	return Key_Back_Get(); // 返回键接到PB12;
}

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

void Dial_ShowText_contral()
{
	uint8_t Roll_Event;
	
	while(1)
	{
		Roll_Event = Dial_RollEvent();
		if(Roll_Event)
		{
			Roll_Event = Dial_RollEvent();
		
		}
		if(Roll_Event)
		{
			
			
			//select += Roll_Event;
			
			
			OLED_Clear();
		}
		else
		{
			
		}
	}
}


			/***********设置选项***********/
void Show_Setting()
{
	OLED_ShowImage((127-50)/2,(64-50)/2+10,50,50,Setting);

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



Buttom_Message buttom = {0,0};

TaskHandle_t buttomHandle;          // 按键消息句柄
TaskHandle_t DialShow_Handle;          // 显示消息句柄


void vButtomTask(void *pvParameters)
{

    while (1) {
        // 检测按键事件
		buttom.roll = Dial_RollEvent();
        buttom.enter = Dial_EnterEvent();
		if(buttom.roll!=0)
		{
			vTaskResume(DialShow_Handle);
		}
		else if(buttom.enter!=0)
		{
			vTaskResume(DialShow_Handle);
		}


        // 延时 30ms
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}





void vDialShow_Task(void *pvParameters)
{

	int8_t select=0;			//	界面下标
	uint8_t length = 0;
	int8_t select1=0;
	
	struct Plate_class plate[] = {
		{"时间",Time_Plate,Time_Plate_Exit},
		{"",Health_Plate,Health_Plate_Exit},
		{"设置",Show_Setting,NULL_Func,SettingMenu},
		{".."}
	};
	
	while(plate[length].Plate_Name[0]!='.')			//		计算有几个选项
	{
		length++;
	}
	
	while (1) {

        if (buttom.roll!=0) {
            // 取出数据
			select1 = select;
           

            // 切换界面下标
			select += buttom.roll;
			
			buttom.roll=0;
			
			
			if(select > (length-1))select = 0;
			
			if(select < 0)select = (length-1);
			
			
			 // 调用退出函数
            if (plate[select1].func_Exit != NULL) {
                plate[select1].func_Exit();
            }
			
			
			OLED_Clear();
        }
		
		// 检测到按下事件，调用按下函数
		if (buttom.enter!=0&&plate[select].enter_func!=NULL) {
			buttom.enter = 0;
			plate[select].enter_func();
		}

        // 调用显示函数
        if (plate[select].func != NULL) {
            plate[select].func();
			Plate_ShowName(plate[select].Plate_Name,0);
        }
		

        // 更新显示
        OLED_Update();

        // 延时 30ms
        vTaskDelay(pdMS_TO_TICKS(3));
    }
}



void Dial_RunPlate()
{


    // 创建按键任务
    xTaskCreate(vButtomTask, "ButtonTask", 128, NULL, 2, NULL);

    // 创建显示任务
    xTaskCreate(vDialShow_Task, "DialShowTask", 512, NULL, 1, NULL);

    // 启动调度器
    vTaskStartScheduler();

    // 如果调度器启动失败，进入死循环
    for (;;)
	{
	}
}

