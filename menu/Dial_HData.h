#ifndef __DIAL_HDATA_H
#define __DIAL_HDATA_H

typedef struct {
	short temperature;
	uint8_t HRate;
	uint8_t OxRate;
	uint32_t DailyStep;
}healthData;

void Dial_HData_Init(void);

void Health_Plate(void);

void vUpdateData(void *pvParameters);

#endif
