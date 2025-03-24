#ifndef __MENU_Show_H
#define __MENU_Show_H

struct Option_Class
{
	char *String;		// 选项名字
	void (*func)(void); // 函数指针
	float *Variable;	// 可选变量
	uint8_t StrLen;		// 由于中文占三个字节,用strlen计算名字长度不再准确,故需额外储存名字长度
};

uint8_t Menu_GetOptionStrLen(char *String);
void Run_List_Menu(struct Option_Class *Option_Class_List);
void SettingMenu(void);
void HealthMenu(void);

#endif
