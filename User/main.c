#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "OLED.h"
#include "ds18b20.h"	
#include "W25Q64.h"
#include "Dial.h"
#include "MyRTC.h"
#include "Encoder.h"
#include "Key.h"
#include "AIR780E.h"
#include "Serial.h"

							//����Ҫ��ȡ���ݵĲ�������

void test_W25Q64()
{
	uint8_t MID;							//�������ڴ��MID�ŵı���
	uint16_t DID;							//�������ڴ��DID�ŵı���

	uint8_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x04};	//����Ҫд�����ݵĲ�������
	uint8_t ArrayRead[4];	
	/*��ʾ��̬�ַ���*/
	OLED_ShowString(0, 0, "MID:   DID:", OLED_8X16);
	OLED_ShowString(1, 16, "W:", OLED_8X16);
	OLED_ShowString(1, 32, "R:", OLED_8X16);
	
	/*��ʾID��*/
	W25Q64_ReadID(&MID, &DID);			//��ȡW25Q64��ID��
	OLED_ShowHexNum(4*8, 0, MID, 2, OLED_8X16);		//��ʾMID
	OLED_ShowHexNum(11*8, 0, DID, 4, OLED_8X16);		//��ʾDID
	
	/*W25Q64���ܺ�������*/
	W25Q64_SectorErase(0x000000);					//��������
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);	//��д�����ݵĲ�������д�뵽W25Q64��
	
	W25Q64_ReadData(0x000000, ArrayRead, 4);		//��ȡ��д��Ĳ������ݵ���ȡ���ݵĲ���������
	
	/*��ʾ����*/
	OLED_ShowHexNum(2*8, 1*16, ArrayWrite[0], 2, OLED_8X16);		//��ʾд�����ݵĲ�������
	OLED_ShowHexNum(5*8, 1*16 , ArrayWrite[1], 2, OLED_8X16);
	OLED_ShowHexNum(8*8, 1*16, ArrayWrite[2], 2, OLED_8X16);
	OLED_ShowHexNum(11*8,1*16, ArrayWrite[3], 2, OLED_8X16);
	
	OLED_ShowHexNum(2 *8 ,2*16 , ArrayRead[0], 2, OLED_8X16);			//��ʾ��ȡ���ݵĲ�������
	OLED_ShowHexNum(5 *8 ,2*16 , ArrayRead[1], 2, OLED_8X16);
	OLED_ShowHexNum(8 *8 ,2*16 , ArrayRead[2], 2, OLED_8X16);
	OLED_ShowHexNum(11*8,2*16 , ArrayRead[3], 2, OLED_8X16);
}

void testTemprature(void)
{	
	
	delay_init(72);	  
	OLED_Init();					//OLED��ʼ��
	
	
	
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		
	}
	//delay_ms(1000);
	
	
	
 	while(1)
	{	
		short temperature = 0; 				//�¶�ֵ
		
		temperature=DS18B20_Get_Temp();	//��ȡ�¶�
		
		Dial_ShowData_Line(temperature/10,10,40);
		OLED_ShowNum(0,0,temperature,3,OLED_8X16);
		OLED_ShowString(24,0,"��",OLED_8X16);
		
		OLED_Update();
		
		delay_ms(100);
	}	
}

void test_Dial_RunPlate()
{
	OLED_Init();					//OLED��ʼ��
	delay_init(72);
	MyRTC_Init();
	Encoder_Init();
	Key_Init();
	
	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		OLED_ShowString(0,0,"ds18b20 Error!",OLED_8X16);
		
		OLED_Update();
	}
	
	
	Dial_RunPlate();
}

void test_AIR780E()
{
	OLED_Init();
	delay_init(72);
	Serial_Init();
	
	uint8_t i=0;
	
	OLED_Update();
	
	while(1)
	{
		if(AT_SendCommand("AT\r\n","OK\r\n",100,1))
		{
			OLED_ShowString_Line(0,0,Serial_RxPacket,OLED_6X8);
		}
		OLED_ShowNum(0,47,i,3,OLED_8X16);
		i++;
		delay_ms(1000);
		OLED_Update();
	}
	
}


void test_OLED(void)
{
	/*ģ���ʼ��*/
	OLED_Init();						//OLED��ʼ��
	W25Q64_Init();						//W25Q64��ʼ��
	delay_init(72);
	//DS18B20_Init();

	delay_ms(100);
	
	//OLED_ShowNum(0,16,OLED_ShowString_Length(0,0,"���",OLED_8X16),5,OLED_8X16);
	//OLED_String_W25Q(0,32,"�¶�");
	//OLED_ShowSignedNum(0,32,-10,2,OLED_8X16);
	
	//Dial_ShowDate(0,47+8,2025,2,28,OLED_6X8);
	//Dial_ShowTime_FULL(0,16,1,20,50);
                       
	OLED_ShowString(32,32,"���",OLED_8X16);
	OLED_DrawLine(64,0,64,64);
	OLED_DrawLine(0,32,127,32);
	
	OLED_Update();
	
	while (1)
	{
		//OLED_DisplayBuffMove(OLED_Left);
		OLED_DisplayBuffMoveArea(32,16,96,48,OLED_Left);
		delay_ms(100);
		OLED_Update();
	}
}

void usart()
{
	
}

int main()
{
	//test_AIR780E();
	OLED_Init();
	
	//Dial_ShowText(16,0,64,32,"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",OLED_8X16);
	//OLED_ShowString_Line(16,16,"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",OLED_8X16);
	test_AIR780E();
	OLED_Update();
}



