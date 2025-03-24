#ifndef __DIAL_HDATA_H
#define __DIAL_HDATA_H

struct healthData{
	short temperature;
	uint8_t HRate;
	uint8_t OxRate;
	uint32_t DailyStep;
};


extern struct healthData hData;
void Health_Plate(void);
void HData_SetData(short temperature,uint8_t HRate,uint8_t OxRate,uint32_t DailyStep);

#endif
