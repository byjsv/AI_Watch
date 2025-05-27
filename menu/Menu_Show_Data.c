#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"
#include "Dial_Date.h"
#include "Dial_HData.h"
#include "sport_mode.h"

void FunctionMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"健康状态查询"},
		{"今天吃什么",whatEat},
		{"热量驱散",LostWeight},
		{"减肥鸡汤"},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void HealthMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"心率",Dial_HData_Line_HRate},
		{"血氧饱和度",Dial_HData_Line_OxRate},
		{"温度",Dial_HData_Line_Temp},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void TimeMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"设置年份",set_year},
		{"设置月份",set_month},
		{"设置日",set_day},
		{"设置小时",set_hour},
		{"设置分钟",set_min},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void BodyMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"设置身高",body_set_high},
		{"设置体重",body_set_wight},
		{"模式选择",body_set_mode},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void SetShowMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"亮度设置",set_Bright},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void SettingMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"时间设置",TimeMenu},
		{"语言设置"},
		{"显示设置",SetShowMenu},
		{"个人数据设置",BodyMenu},
		{"信息"},
		{"清空数据",Clear_Data},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}
