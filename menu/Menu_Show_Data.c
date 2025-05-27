#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"
#include "Dial_Date.h"
#include "Dial_HData.h"
#include "sport_mode.h"

void FunctionMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"����״̬��ѯ"},
		{"�����ʲô",whatEat},
		{"������ɢ",LostWeight},
		{"���ʼ���"},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void HealthMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"����",Dial_HData_Line_HRate},
		{"Ѫ�����Ͷ�",Dial_HData_Line_OxRate},
		{"�¶�",Dial_HData_Line_Temp},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void TimeMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"�������",set_year},
		{"�����·�",set_month},
		{"������",set_day},
		{"����Сʱ",set_hour},
		{"���÷���",set_min},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void BodyMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"�������",body_set_high},
		{"��������",body_set_wight},
		{"ģʽѡ��",body_set_mode},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void SetShowMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"��������",set_Bright},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}

void SettingMenu(void)
{
	struct Option_Class Option_Class_List[] = {
		{">>>"},
		{"ʱ������",TimeMenu},
		{"��������"},
		{"��ʾ����",SetShowMenu},
		{"������������",BodyMenu},
		{"��Ϣ"},
		{"�������",Clear_Data},
		{".."}
	};
	
	Run_List_Menu(Option_Class_List);
}
