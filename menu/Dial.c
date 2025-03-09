#include "stm32f10x.h"                  // Device header

#include "freeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Dial.h"

#include "Menu_Show.h"
#include "OLED.h"
#include "ds18b20.h"
#include "Key.h"
#include "MyRTC.h"
#include "Encoder.h"

#include "string.h"



int8_t Dial_RollEvent(void) // �˵�����
{
	if (Key_Up_Get()) // �����Ͻӵ�PB15;
	{
		return 1;
	}
	if (Key_Down_Get()) // �����½ӵ�PB13;
	{
		return -1;
	}
	return Encoder_Get_Div4(); // ��ť������PA8,PA9;
}
int8_t Dial_EnterEvent(void) // �˵�ȷ��
{
	return Key_Enter_Get(); // ȷ�ϼ��ӵ�PB14;
}
int8_t Menu_BackEvent(void) // �˵�����
{
	return Key_Back_Get(); // ���ؼ��ӵ�PB12;
}

/****************���ߺ���**************/




/****************�ؼ�����********************/

void Dial_ShowText(int16_t X, int16_t Y,int16_t MaxX, int16_t MaxY, char *String, uint8_t FontSize)		//�ַ���ΪGB2312
{
	uint16_t i = 0;
	char SingleChar[5];
	uint8_t CharLength = 0;
	uint16_t XOffset = 0;
	uint16_t pIndex;
	
	while (String[i] != '\0')	//�����ַ���
	{		

		/*�˶δ����Ŀ���ǣ���ȡGB2312�ַ����е�һ���ַ���ת�浽SingleChar���ַ�����*/
		/*�ж�GB2312�ֽڵ����λ��־λ*/
		if ((String[i] & 0x80) == 0x00)			//���λΪ0
		{
			CharLength = 1;						//�ַ�Ϊ1�ֽ�
			SingleChar[0] = String[i ++];		//����һ���ֽ�д��SingleChar��0��λ�ã����iָ����һ���ֽ�
			SingleChar[1] = '\0';				//ΪSingleChar����ַ���������־λ
		}
		else									//���λΪ1
		{
			CharLength = 2;						//�ַ�Ϊ2�ֽ�
			SingleChar[0] = String[i ++];		//����һ���ֽ�д��SingleChar��0��λ�ã����iָ����һ���ֽ�
			if (String[i] == '\0') {break;}		//�������������ѭ����������ʾ
			SingleChar[1] = String[i ++];		//���ڶ����ֽ�д��SingleChar��1��λ�ã����iָ����һ���ֽ�
			SingleChar[2] = '\0';				//ΪSingleChar����ַ���������־λ
		}
		if(XOffset+FontSize > MaxX && !(CharLength == 1 && SingleChar[0]=='\n'))         //    ȱ����ʾ
		{
			XOffset = 0;
			Y += (FontSize==OLED_6X8)?8:16;
			if(Y>MaxY)return;
		}
		
		/*��ʾ����������ȡ����SingleChar*/
		if (CharLength == 1)	//����ǵ��ֽ��ַ�
		{
			if(SingleChar[0]=='\n')         //   ������\n���в���
			{
				XOffset = 0;
				Y += (FontSize==OLED_6X8)?8:16;
				if(Y>MaxY)return;
			}
			else
			{
				/*ʹ��OLED_ShowChar��ʾ���ַ�*/
				OLED_ShowChar(X + XOffset, Y, SingleChar[0], FontSize);
				XOffset += FontSize;
			}
		}
		else					//���򣬼����ֽ��ַ�
		{
			/*����������ģ�⣬����ģ����Ѱ�Ҵ��ַ�������*/
			/*����ҵ����һ���ַ�������Ϊ���ַ����������ʾ�ַ�δ����ģ�ⶨ�壬ֹͣѰ��*/
			for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
			{
				/*�ҵ�ƥ����ַ�*/
				if (strcmp(OLED_CF16x16[pIndex].Index, SingleChar) == 0)
				{
					break;		//����ѭ������ʱpIndex��ֵΪָ���ַ�������
				}
			}
			if (FontSize == OLED_8X16)		//��������Ϊ8*16����
			{
				/*����ģ��OLED_CF16x16��ָ��������16*16��ͼ���ʽ��ʾ*/
				OLED_ShowImage(X + XOffset, Y, 16, 16, OLED_CF16x16[pIndex].Data);
				XOffset += 16;
			}
			else if (FontSize == OLED_6X8)	//��������Ϊ6*8����
			{
				/*�ռ䲻�㣬��λ����ʾ'?'*/
				OLED_ShowChar(X + XOffset, Y, '?', OLED_6X8);
				XOffset += OLED_6X8;
			}
		}
	}
}

void Dial_ShowText_contral()
{
	uint8_t Roll_Event;
	
	while(1)
	{
		Roll_Event = Dial_RollEvent();
		if(Roll_Event)
		{
			Roll_Event = Dial_RollEvent();
		
		}
		if(Roll_Event)
		{
			
			
			//select += Roll_Event;
			
			
			OLED_Clear();
		}
		else
		{
			
		}
	}
}


			/***********����ѡ��***********/
void Show_Setting()
{
	OLED_ShowImage((127-50)/2,(64-50)/2+10,50,50,Setting);

}


void Dial_ShowData(uint8_t temp,uint8_t HRate, uint8_t Oxygen)
{

}




void Health_Plate_Exit()
{

}

void Plate_ShowName(char *Name,uint8_t Y)
{
	uint8_t length_name=0;
	
	while(Name[length_name]!='\0')
	{
		length_name++;
	}
	
	OLED_ShowString_12X12(63-length_name*6/2,Y,Name);
	//OLED_ReverseArea();
}

/*********************������ѡ��**********************/
struct Plate_class{                        //  ѡ��ṹ��
	char *Plate_Name;		// ѡ������
	void (*func)(void);     // ��ʾ����ָ��
	void (*func_Exit)(void);          //  �˳�����
	void (*enter_func)(void);
};



Buttom_Message buttom = {0,0};

TaskHandle_t buttomHandle;          // ������Ϣ���
TaskHandle_t DialShow_Handle;          // ��ʾ��Ϣ���


void vButtomTask(void *pvParameters)
{

    while (1) {
        // ��ⰴ���¼�
		buttom.roll = Dial_RollEvent();
        buttom.enter = Dial_EnterEvent();
		if(buttom.roll!=0)
		{
			vTaskResume(DialShow_Handle);
		}
		else if(buttom.enter!=0)
		{
			vTaskResume(DialShow_Handle);
		}


        // ��ʱ 30ms
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}





void vDialShow_Task(void *pvParameters)
{

	int8_t select=0;			//	�����±�
	uint8_t length = 0;
	int8_t select1=0;
	
	struct Plate_class plate[] = {
		{"ʱ��",Time_Plate,Time_Plate_Exit},
		{"",Health_Plate,Health_Plate_Exit},
		{"����",Show_Setting,NULL_Func,SettingMenu},
		{".."}
	};
	
	while(plate[length].Plate_Name[0]!='.')			//		�����м���ѡ��
	{
		length++;
	}
	
	while (1) {

        if (buttom.roll!=0) {
            // ȡ������
			select1 = select;
           

            // �л������±�
			select += buttom.roll;
			
			buttom.roll=0;
			
			
			if(select > (length-1))select = 0;
			
			if(select < 0)select = (length-1);
			
			
			 // �����˳�����
            if (plate[select1].func_Exit != NULL) {
                plate[select1].func_Exit();
            }
			
			
			OLED_Clear();
        }
		
		// ��⵽�����¼������ð��º���
		if (buttom.enter!=0&&plate[select].enter_func!=NULL) {
			buttom.enter = 0;
			plate[select].enter_func();
		}

        // ������ʾ����
        if (plate[select].func != NULL) {
            plate[select].func();
			Plate_ShowName(plate[select].Plate_Name,0);
        }
		

        // ������ʾ
        OLED_Update();

        // ��ʱ 30ms
        vTaskDelay(pdMS_TO_TICKS(3));
    }
}



void Dial_RunPlate()
{


    // ������������
    xTaskCreate(vButtomTask, "ButtonTask", 128, NULL, 2, NULL);

    // ������ʾ����
    xTaskCreate(vDialShow_Task, "DialShowTask", 512, NULL, 1, NULL);

    // ����������
    vTaskStartScheduler();

    // �������������ʧ�ܣ�������ѭ��
    for (;;)
	{
	}
}

