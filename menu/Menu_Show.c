#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"
#include "OLED.h"
#include "string.h"

#include "Dial.h"
#include "Key.h"

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
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	从消息队列获取一次按键事件
            
			// 按下上键
			if(xKeyEvent.Up_Pressed) {	
				
				select--;		// 选项上移
				select = (select < 0) ? (length - 1) : (select % length);	//到边界循环
			}
			// 	按下下键
			if(xKeyEvent.Down_Pressed) {	
				
				select++;		// 选项下移
				select = (select < 0) ? (length - 1) : (select % length);	//到边界循环
			}
			// 按下中间键
			if(xKeyEvent.Enter_Pressed) {	
				if(select==0)break;
				if(Option_Class_List[select].func != NULL)
				{
					Option_Class_List[select].func();
				}
			}
			
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
