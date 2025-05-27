#ifndef __SPORT_MODE_H
#define __SPORT_MODE_H

struct posture{
	float Pitch;
	float Roll;
	float Yaw;
	unsigned long step;
};

struct body_infomation{
	uint16_t high;
	uint16_t wight;
	uint8_t mode;
};

extern struct posture Watch_Posture;
extern struct body_infomation body;

uint8_t isshake(void);

void Sport_MODE_Init(void);

void body_set_high(void);
void body_set_wight(void);
void body_set_mode(void);

void LostWeight(void);
void whatEat(void);

void Sport_getData(void);

#endif
