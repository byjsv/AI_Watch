#include "stm32f10x.h"                  // Device header

typedef struct{
	char location[10];
	uint8_t wend;
	uint16_t weat;
	uint16_t temprature;
	
}weather;

void UpdateWealth()
{

}

void Dial_ShowWealth(void)
{
	UpdateWealth();
	
}
