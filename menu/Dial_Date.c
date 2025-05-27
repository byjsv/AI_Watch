#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Dial.h"
#include "Delay.h"
#include "Key.h"
#include "MyRTC.h"

#include "Menu_Show.h"
#include "OLED.h"
#include "string.h"

#include "Dial.h"
#include "Key.h"

void Dial_ShowSigner(uint8_t x,uint8_t y)
{
	//OLED_ShowString(x,y,"4G",OLED_6X8);
	OLED_ShowImage(x,y,12,8,No_Signer);
}

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

uint8_t getDaysInMonth(uint16_t year, uint8_t month) {
    // 判断月份并返回天数
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // 判断闰年
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                return 29; // 闰年2月有29天
            } else {
                return 28; // 平年2月有28天
            }
    }
	return 31;
}

void Dial_ShowDate(uint8_t PosX,uint8_t PosY,uint16_t year,uint8_t month,uint8_t day,uint8_t FontSize)
{
	uint8_t space = 3;
	
	uint8_t length = 0;
	
	OLED_ShowNum_Left(PosX,PosY,year,get_Num_Len(year),FontSize);
	length += get_Num_Len(year)*FontSize + space;
	OLED_ShowNum_Left(PosX + length,PosY,month,get_Num_Len(month),FontSize);
	length += get_Num_Len(month)*FontSize + space;
	if(day!=0)
	{
		OLED_ShowNum_Left(PosX + length,PosY,day,get_Num_Len(day),FontSize);
	}
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
	OLED_ShowNum_Left(PosX+length,PosY+28-16,sec,2,OLED_8X16);
	
}

void Time_Plate(void)
{
	MyRTC_ReadTime();
	
	Dial_ShowDate(0,47+8,MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2],OLED_6X8);
	Dial_ShowTime_FULL((127-96)/2,16+2,MyRTC_Time[3],MyRTC_Time[4],MyRTC_Time[5]);
	
	Dial_ShowSigner(127-OLED_6X8*5,0);
}

void set_year(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				MyRTC_Time[0]++;
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				MyRTC_Time[0]--;
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				MyRTC_SetTime();
				break;
			}
		}
		//OLED_ShowNum_Left(48,24,MyRTC_Time[0],2,OLED_8X16);
		OLED_ShowNum_Left(48,24,MyRTC_Time[0],4,OLED_8X16);
		OLED_ShowString_12X12(80,26,"年");
		Dial_ShowDate(0,47+8,MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2],OLED_6X8);
		OLED_Update();
	}
}

void set_month(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				if(MyRTC_Time[1]<12)
				{
					MyRTC_Time[1]++;
				}else
				{
					MyRTC_Time[1]=1;
				}
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				if(MyRTC_Time[1]>1)
				{
					MyRTC_Time[1]--;
				}else
				{
					MyRTC_Time[1]=12;
				}
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	 
				if(MyRTC_Time[2]>getDaysInMonth(MyRTC_Time[0],MyRTC_Time[1]))
				{
					MyRTC_Time[2]=getDaysInMonth(MyRTC_Time[0],MyRTC_Time[1]); //  修改后月份天数大于现在天数，回正
				}
				MyRTC_SetTime();
				break;
			}
		}
		OLED_ShowNum_Left(48,24,MyRTC_Time[1],2,OLED_8X16);
		OLED_ShowString_12X12(80-2*8,26,"月");
		Dial_ShowDate(0,47+8,MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2],OLED_6X8);
		OLED_Update();
	}

}

void set_day(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				MyRTC_Time[2]++;
				if(MyRTC_Time[2]>getDaysInMonth(MyRTC_Time[0],MyRTC_Time[1]))
				{
					MyRTC_Time[2] = 1;
				}
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				MyRTC_Time[2]--;
				if(MyRTC_Time[2]<1)
				{
					MyRTC_Time[2] = getDaysInMonth(MyRTC_Time[0],MyRTC_Time[1]);
				}
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				MyRTC_SetTime();
				break;
			}
		}
		OLED_ShowNum_Left(48,24,MyRTC_Time[2],2,OLED_8X16);
		OLED_ShowString_12X12(80-2*8,26,"日");
		Dial_ShowDate(0,47+8,MyRTC_Time[0],MyRTC_Time[1],MyRTC_Time[2],OLED_6X8);
		OLED_Update();
	}
}

void set_hour(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				if(MyRTC_Time[3]==23)
				{
					MyRTC_Time[3]=0;
				}
				else MyRTC_Time[3]++;
				
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				if(MyRTC_Time[3]==0)
				{
					MyRTC_Time[3]=23;
				}
				else MyRTC_Time[3]--;
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				MyRTC_SetTime();
				break;
			}
		}
		OLED_ShowNum_Left(48,24,MyRTC_Time[3],2,OLED_8X16);
		OLED_ShowString_12X12(80-2*8,26,"时");
		Dial_ShowDate(0,47+8,MyRTC_Time[3],MyRTC_Time[4],0,OLED_6X8);
		OLED_Update();
	}
}

void set_min(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				if(MyRTC_Time[4]==59)
				{
					MyRTC_Time[4]=0;
				}
				else MyRTC_Time[4]++;
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				if(MyRTC_Time[4]==0)
				{
					MyRTC_Time[4]=59;
				}
				else MyRTC_Time[4]--;
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				MyRTC_SetTime();
				break;
			}
		}
		OLED_ShowNum_Left(48,24,MyRTC_Time[4],2,OLED_8X16);
		OLED_ShowString_12X12(80-2*8,26,"分");
		Dial_ShowDate(0,47+8,MyRTC_Time[3],MyRTC_Time[4],0,OLED_6X8);
		OLED_Update();
	}
}


void Time_Plate_Exit(void)
{
	//uint8_t i;
	//if(buttom.roll>0)
	//{
	//	for(i=0;i<128;i++)
	//	{
	//		OLED_DisplayBuffMove(OLED_Left);
	//		OLED_Update();   
	//	}
	//}
	//else if(buttom.roll<0)
	//{
	//	for(i=0;i<128;i++)
	//	{
	//		OLED_DisplayBuffMove(OLED_Right);
	//		OLED_Update();
	//	}
	//}
}

