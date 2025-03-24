#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"

void SettingMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"internet"},
		{"2"},
		{"3"},
		{"4"},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void HealthMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"心率"},
		{"血氧饱和度"},
		{"温度"},
		{"4"},
		{"5"},
		{"6"},
		{"7"},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

