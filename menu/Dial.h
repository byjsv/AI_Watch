#ifndef __DIAL_H
#define __DIAL_H

#define NULL_Func 0

void Dial_ShowDate(uint8_t PosX,uint8_t PosY,uint16_t year,uint8_t month,uint8_t day,uint8_t FontSize);
void Dial_ShowTime_FULL(uint8_t PosX,uint8_t PosY,uint8_t hour,uint8_t min,uint8_t sec);
void Dial_ShowData(uint8_t temp,uint8_t HRate, uint8_t Oxygen);
void Dial_ShowData_Line(uint16_t num,uint16_t MIN,uint16_t MAX);
void Dial_RunPlate(void);

#endif
