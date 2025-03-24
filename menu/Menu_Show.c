#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"
#include "OLED.h"
#include "string.h"

#include "Dial.h"

#define Screen_Length_Menu 4


struct Option_Class Option_Class_List[] = {
	{">>>"},
	{"显示"},
	{".."}
};

uint8_t Menu_GetOptionStrLen(char *String)
{
	uint8_t i = 0, len = 0;
	while (String[i] != '\0') // 遍历字符串的每个字符
	{
		if (String[i] > '~') // 如果不属于英文字符长度加2
		{
			len += 2;
			i += 3;
		}
		else // 属于英文字符长度加1
		{
			len += 1;
			i += 1;
		}
	}
	return len;
}

void Run_List_Menu(struct Option_Class *Option_Class_List)
{
	uint8_t length=0;
	int8_t select = 0;
	uint8_t i=0;
	
	uint8_t startX=3;
	
	
	while(Option_Class_List[length].String[0]!='.')			//		计算有几个选项
	{
		length++;
	}
	
	while(1)
	{
		if(buttom.roll!=0)		//  触发移动
		{
			
			
			// 切换界面下标
			select += buttom.roll;
			
			buttom.roll=0;
			
			
			if(select > (length-1))select = 0;
			
			if(select < 0)select = (length-1);
		}
		
		//  触发按下事件
		if(buttom.enter == 1&&select==0)break;
		
		if(buttom.enter != 0 && Option_Class_List[select].func != NULL)
		{
			Option_Class_List[select].func();
			buttom.enter=0;
		}
		
		if(select>Screen_Length_Menu)           // 达到菜单偏移的临界值
		{
			for(i=0;i<length;i++)
			{
				OLED_ShowString_12X12(startX,0+(i-select+Screen_Length_Menu)*12,Option_Class_List[i].String);
				if(i==select)
				{
					OLED_ReverseArea(0,0+(i-select+Screen_Length_Menu)*12,Menu_GetOptionStrLen(Option_Class_List[i].String)*8+startX*2,12);
					
				}
			}
		}
		else 					//  菜单前段不偏移
		{
			for(i=0;i<length;i++)
			{
				OLED_ShowString_12X12(startX,0+i*12,Option_Class_List[i].String);
				if(i==select)
				{
					OLED_ReverseArea(0,0+i*12,Menu_GetOptionStrLen(Option_Class_List[i].String)*8+startX*2,12);
				}
			}
		}
		OLED_ShowNum(127-8,0,select,1,OLED_8X16);
		OLED_Update();
		OLED_Clear();
	}
	
}
