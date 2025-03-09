#include "stm32f10x.h"                  // Device header

#ifndef __DS18B20_H
#define __DS18B20_H 
//#include "sys.h"   


//DS18B20���ź궨��						

#define DS18B20_GPIO_PORT		GPIOA
#define DS18B20_GPIO_PIN		GPIO_Pin_3
#define DS18B20_GPIO_CLK   	RCC_APB2Periph_GPIOA

//���״̬����
#define OUT 1
#define IN  0

//����DS18B20��������ߵ͵�ƽ
#define DS18B20_Low  GPIO_ResetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)
#define DS18B20_High GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)		
		
uint8_t DS18B20_Init(void);//��ʼ��DS18B20
short DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��
void DS18B20_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_Read_Byte(void);//����һ���ֽ�
uint8_t DS18B20_Read_Bit(void);//����һ��λ
void DS18B20_Mode(uint8_t mode);//DS18B20�������ģʽ����
uint8_t DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20   

#endif


