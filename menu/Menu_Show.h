#ifndef __MENU_Show_H
#define __MENU_Show_H

struct Option_Class
{
	char *String;		// ѡ������
	void (*func)(void); // ����ָ��
	float *Variable;	// ��ѡ����
	uint8_t StrLen;		// ��������ռ�����ֽ�,��strlen�������ֳ��Ȳ���׼ȷ,������ⴢ�����ֳ���
};

uint8_t Menu_GetOptionStrLen(char *String);
void Run_List_Menu(struct Option_Class *Option_Class_List);
void SettingMenu(void);
void HealthMenu(void);

#endif
