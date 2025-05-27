#ifndef __DIAL_HDATA_H
#define __DIAL_HDATA_H

typedef struct {
	short temperature;
	uint8_t HRate;
	uint8_t OxRate;
	uint32_t DailyStep;
}healthData;

void Dial_HData_Init(void);

void Dial_HData_Line_Temp(void);
void Dial_HData_Line_HRate(void);
void Dial_HData_Line_OxRate(void);

void Health_Plate(void);

void vUpdateData(void *pvParameters);

#endif
