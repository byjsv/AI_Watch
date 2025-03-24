#include "stm32f10x.h"                  // Device header"
#include "OLED.h"
#include "Delay.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "sport_mode.h"


struct posture Watch_Posture = {0,0,0,0};


void Sport_MODE_Init(void)
{
	delay_init();
	OLED_Init();
	MPU6050_DMP_Init();
	dmp_set_pedometer_step_count(0);
}

void Sport_getData(void)
{

	MPU6050_DMP_Get_Data(&Watch_Posture.Pitch,&Watch_Posture.Roll,&Watch_Posture.Yaw);
	dmp_get_pedometer_step_count(&Watch_Posture.step);
	
	
	//OLED_ShowSignedNum(0,0,Watch_Posture.Pitch,3,OLED_8X16);
	//OLED_ShowSignedNum(0,16,Watch_Posture.Roll,3,OLED_8X16);
	//OLED_ShowSignedNum(0,32,Watch_Posture.Yaw,3,OLED_8X16);
	//OLED_ShowNum(0,48,Watch_Posture.step,3,OLED_8X16);
	//OLED_Update();
	
}
