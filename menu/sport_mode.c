#include "stm32f10x.h"                  // Device header"
#include "OLED.h"
#include "Delay.h"
#include "key.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "sport_mode.h"
#include <stdio.h>

#include "Air780E.h"


struct posture Watch_Posture = {0,0,0,0};

struct body_infomation body = {170,50,0};


void Sport_MODE_Init(void)
{
	delay_init();
	OLED_Init();
	MPU6050_DMP_Init();
	dmp_set_pedometer_step_count(0);
}

void body_set_high(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	����Ϣ���л�ȡһ�ΰ����¼�
            
			// �����ϼ�
			if(xKeyEvent.Up_Pressed) {	
				body.high++;
			}
			// 	�����¼�
			if(xKeyEvent.Down_Pressed) {	
				body.high--;
			}
			// �����м��
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		//OLED_ShowNum_Left(48,24,MyRTC_Time[0],2,OLED_8X16);
		OLED_ShowNum_Left(48,24,body.high,3,OLED_8X16);
		OLED_ShowString_12X12(74,26,"cm");
		OLED_Update();
	}
}

void body_set_wight(void)
{
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	����Ϣ���л�ȡһ�ΰ����¼�
            
			// �����ϼ�
			if(xKeyEvent.Up_Pressed) {	
				body.wight++;
			}
			// 	�����¼�
			if(xKeyEvent.Down_Pressed) {	
				body.wight--;
			}
			// �����м��
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		//OLED_ShowNum_Left(48,24,MyRTC_Time[0],2,OLED_8X16);
		OLED_ShowNum_Left(48,24,body.wight,3,OLED_8X16);
		OLED_ShowString_12X12(74,26,"kg");
		OLED_Update();
	}
}
 
void body_set_mode(void)
{
	
	OLED_Clear();
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	����Ϣ���л�ȡһ�ΰ����¼�
            
			// �����ϼ�
			if(xKeyEvent.Up_Pressed) {	
				body.mode++;
			}
			// 	�����¼�
			if(xKeyEvent.Down_Pressed) {	
				body.mode--;
			}
			// �����м��
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		if(body.mode > 2)
		{
			body.mode = 0;
		}
		
		switch(body.mode)
		{
			case 0:OLED_Clear();OLED_ShowString_12X12(43,26,"��ģʽ");break;
			case 1:OLED_Clear();OLED_ShowString_12X12(40,26,"�˶�ģʽ");break;
			case 2:OLED_Clear();OLED_ShowString_12X12(40,26,"�칫ģʽ");break;
		}
		OLED_Update();
	}
}

void healthState(void)
{
	
	OLED_Clear();
	
	while(1)
	{
		KeyEvent_t xKeyEvent;
        if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	����Ϣ���л�ȡһ�ΰ����¼�
            
			// �����м��
			if(xKeyEvent.Enter_Pressed) {	
				break;
			}
		}
		OLED_ShowString_12X12(43,26,"ͨ����");
		
		OLED_Update();
	}
}

void LostWeight(void)
{
	
	OLED_Clear();
	
	//char comment[30];
	//sprintf(comment,"����һ������%lu��,�����������Ϊ%u cm %u kg��������������˶�������",Watch_Posture.step,body.high,body.wight);
	//
	//while(1)
	//{
	//	KeyEvent_t xKeyEvent;
    //    if(Key_GetEvent(&xKeyEvent, 0) == pdPASS) {		//	����Ϣ���л�ȡһ�ΰ����¼�
    //        
	//		// �����м��
	//		if(xKeyEvent.Enter_Pressed) {	
	//			return;
	//		}
	//	}
	//	Air780E_AIRequest(comment,"�밴���¹���ش�1��ֻ�ܻش�����;2������ش�3���ʻ���������һ��");
	//	OLED_ShowString_12X12(43,26,"ͨ����");
	//	
	//	OLED_Update();
	//}
	OLED_ShowString_12X12(43,26,"ͨ����");
	OLED_Update();
	vTaskDelay(pdMS_TO_TICKS(500));
	OLED_Clear();
	OLED_ShowString_Line(0,0,"����һ������0��,˦����0��·�������");
	OLED_Update();
	vTaskDelay(pdMS_TO_TICKS(2000));
}

void whatEat(void)
{
	OLED_ShowString_12X12(43,26,"ͨ����");
	OLED_Update();
	vTaskDelay(pdMS_TO_TICKS(500));
	OLED_Clear();
	OLED_ShowString_Line(0,0,"���ѳ���:����θ,Ӫ������,������,���ٽ���");
	OLED_Update();
	vTaskDelay(pdMS_TO_TICKS(2000));
}

void Sport_getData(void)
{

	MPU6050_DMP_Get_Data(&Watch_Posture.Pitch,&Watch_Posture.Roll,&Watch_Posture.Yaw);
	dmp_get_pedometer_step_count(&Watch_Posture.step);
	dmp_set_pedometer_step_count(1);
	
	//OLED_ShowSignedNum(0,0,Watch_Posture.Pitch,3,OLED_8X16);
	//OLED_ShowSignedNum(0,16,Watch_Posture.Roll,3,OLED_8X16);
	//OLED_ShowSignedNum(0,32,Watch_Posture.Yaw,3,OLED_8X16);
	//OLED_ShowNum(0,48,Watch_Posture.step,3,OLED_8X16);
	//OLED_Update();
	
}
