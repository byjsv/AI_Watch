#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	DS18B20�����¶ȴ�����h�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.13
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	������							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

/***************�����Լ��������****************/
//DS18B20���ź궨��						

#define DS18B20_GPIO_PORT		GPIOA
#define DS18B20_GPIO_PIN		GPIO_Pin_3
#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOA

/*********************END**********************/
//���״̬����
#define OUT 1
#define IN  0

//����DS18B20��������ߵ͵�ƽ
#define DS18B20_Low  GPIO_ResetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)
#define DS18B20_High GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)		
		
u8 DS18B20_Init(void);//��ʼ��DS18B20
short DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);//����һ���ֽ�
u8 DS18B20_Read_Bit(void);//����һ��λ
void DS18B20_Mode(u8 mode);//DS18B20�������ģʽ����
u8 DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20   

#endif


