#ifndef __SPORT_MODE_H
#define __SPORT_MODE_H

struct posture{
	float Pitch;
	float Roll;
	float Yaw;
	unsigned long step;
};

extern struct posture Watch_Posture;

uint8_t isshake(void);

void Sport_MODE_Init(void);

void Sport_getData(void);

#endif
