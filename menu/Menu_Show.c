#include "stm32f10x.h"                  // Device header
#include "Menu_Show.h"

struct Option_Class
{
	char *String;		// 选项名字
	void (*func)(void); // 函数指针
	float *Variable;	// 可选变量
	uint8_t StrLen;		// 由于中文占三个字节,用strlen计算名字长度不再准确,故需额外储存名字长度
};

struct Option_Class Option_Class_List[] = {
	{">>>"},
	{"显示"}
};

void test(){}

void Run_List_Menu(struct Option_Class *Option_Class_List)
{
	uint8_t i,len;
	len = sizeof(Option_Class_List);
	
	for(i=0;i<len;i++)          // 确定图像位置并画图
	{
		Option_Class_List[i].String;
	}

}
