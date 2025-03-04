#include "stm32f10x.h"                  // Device header
#include "Dial.h"

#include "OLED.h"
#include "ds18b20.h"
#include "Key.h"
#include "MyRTC.h"
#include "Encoder.h"

#include "string.h"


int8_t Dial_RollEvent()
{
	return Encoder_Get_Div4();
}

int8_t Dial_EnterEvent(void) // 菜单确认
{
	return Key_Enter_Get(); // 确认键接到PB14;
}
	

/****************工具函数**************/

uint8_t get_Num_Len(uint32_t num)
{
	uint8_t i=0;
	while(num)
	{
		num /= 10;
		i++;
	}
	return i;
}

void Show_large_num(uint8_t X,uint8_t Y,uint8_t n)
{
	switch(n)
	{
		case 0:OLED_ShowImage(X,Y,16,28,Num0);break;
		case 1:OLED_ShowImage(X,Y,16,28,Num1);break;
		case 2:OLED_ShowImage(X,Y,16,28,Num2);break;
		case 3:OLED_ShowImage(X,Y,16,28,Num3);break;
		case 4:OLED_ShowImage(X,Y,16,28,Num4);break;
		case 5:OLED_ShowImage(X,Y,16,28,Num5);break;
		case 6:OLED_ShowImage(X,Y,16,28,Num6);break;
		case 7:OLED_ShowImage(X,Y,16,28,Num7);break;
		case 8:OLED_ShowImage(X,Y,16,28,Num8);break;
		case 9:OLED_ShowImage(X,Y,16,28,Num9);break;
	}
}

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

void Dial_ShowDate(uint8_t PosX,uint8_t PosY,uint16_t year,uint8_t month,uint8_t day,uint8_t FontSize)
{
	uint8_t space = 3;
	
	uint8_t length = 0;
	
	OLED_ShowNum(PosX,PosY,year,get_Num_Len(year),FontSize);
	length += get_Num_Len(year)*FontSize + space;
	OLED_ShowNum(PosX + length,PosY,month,get_Num_Len(month),FontSize);
	length += get_Num_Len(month)*FontSize + space;
	OLED_ShowNum(PosX + length,PosY,day,get_Num_Len(day),FontSize);
}

void Dial_ShowTime_FULL(uint8_t PosX,uint8_t PosY,uint8_t hour,uint8_t min,uint8_t sec)
{
	uint8_t length = 0;
	
	Show_large_num(PosX+length,PosY,hour/10);
	length += 16;
	Show_large_num(PosX+length,PosY,hour%10);
	length += 16;
	OLED_ShowImage(PosX+length,PosY,12,28,spit);
	length += 12;
	Show_large_num(PosX+length,PosY,min/10);
	length += 16;
	Show_large_num(PosX+length,PosY,min%10);
	length += 16;
	length += 4;
	OLED_ShowNum(PosX+length,PosY+28-16,sec,2,OLED_8X16);
	
}

void Dial_ShowSigner(uint8_t x,uint8_t y)
{
	//OLED_ShowString(x,y,"4G",OLED_6X8);
	OLED_ShowImage(x,y,12,8,No_Signer);
}

void Dial_ShowData(uint8_t temp,uint8_t HRate, uint8_t Oxygen)
{

}


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

void Time_Plate()
{
	MyRTC_ReadTime();
	
	Dial_ShowDate(0,47+8,MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2],OLED_6X8);
	Dial_ShowTime_FULL((127-96)/2,16+2,MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
	
	Dial_ShowSigner(127-OLED_6X8*5,0);
}

void Time_Plate_Exit()
{
	
}

void Health_Plate()
{
	static short temperature = 0; 				//温度值
    
	temperature=DS18B20_Get_Temp();	//读取温度
	
	
	Dial_ShowData_Line(temperature/10,10,40);
	OLED_ShowNum(0,0,temperature,3,OLED_8X16);
	OLED_ShowString(24,0,"℃",OLED_8X16);
	//OLED_DrawPoint(2*8,16);
	//OLED_ShowNum(0,0,1,3,OLED_8X16);
}

void Health_Plate_Exit()
{
	Line_PosX = 0;
}


/*********************主界面选项**********************/

struct Plate_class{
	char *Plate_Name;		// 选项名字
	void (*func)(void);     // 显示函数指针
	void (*func_Exit)(void);          //  退出函数
};

void Plate_ShowName(char *Name,uint8_t Y)
{
	uint8_t length_name=0;
	
	while(Name[length_name]!='\0')
	{
		length_name++;
	}
	
	OLED_ShowString(63-length_name*OLED_8X16/2,Y,Name,OLED_8X16);
	//OLED_ReverseArea();
}


void Dial_RunPlate()
{
	
	int8_t select = 0;
	uint8_t length = 0;
	
	uint8_t Roll_Event = 0;
	
	
	struct Plate_class plate[] = {
		{"时间",Time_Plate},
		{"温度",Health_Plate,Health_Plate_Exit},
		{"应用",NULL_Func,NULL_Func},
		{".."}
	};
	while(plate[length].Plate_Name[0]!='.')
	{
		length++;
	}
	
	
	while(1)
	{
		Roll_Event = Dial_RollEvent();
		
		Plate_ShowName(plate[select].Plate_Name,0);
		
		if(Roll_Event)
		{
			if(plate[select].func_Exit)
			{
				plate[select].func_Exit();
			}
			
			
			select += Roll_Event;
			
			if(select > (length-1))select = 0;
			
			if(select < 0)select = (length-1);
			
			
			OLED_Clear();
		}
		else
		{
			if(plate[select].func)
			{
				plate[select].func();        //  运行对应项的显示函数
			}
			
		}
		

		
		OLED_Update();
	}		
}

