#include "ds18b20.h"
#include "delay.h"	

/*****************���絥Ƭ�����******************
											STM32
 * �ļ�			:	DS18B20�����¶ȴ�����c�ļ�                   
 * �汾			: V1.0
 * ����			: 2024.8.13
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	��DS18B20.h�ļ�							
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/			

void DS18B20_Rst(void)	   
{                 
		DS18B20_Mode(OUT); 	//SET OUTPUT
    DS18B20_Low; 				//����DQ
    Delay_us(750);    	//����750us
    DS18B20_High; 			//DQ=1 
		Delay_us(15);     	//15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_Mode(IN);	//SET  INPUT	 
    while (GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<200)
	{
		retry++;
		Delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN)&&retry<240)
	{
		retry++;
		Delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
u8 DS18B20_Read_Bit(void) 	 
{
    uint8_t data;
	DS18B20_Mode(OUT);	//SET OUTPUT
    DS18B20_Low; 
	Delay_us(2);
    DS18B20_High; 
	DS18B20_Mode(IN);	//SET INPUT
	Delay_us(12);
	if(GPIO_ReadInputDataBit(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN))data=1;
    else data=0;	 
    Delay_us(50);           
    return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
uint8_t DS18B20_Read_Byte(void)     
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
	DS18B20_Mode(OUT);	//SET OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_Low;	// Write 1
            Delay_us(2);                            
            DS18B20_High;
            Delay_us(60);             
        }
        else 
        {
            DS18B20_Low;	// Write 0
            Delay_us(60);             
            DS18B20_High;
            Delay_us(2);                          
        }
    }
}
//��ʼ�¶�ת��
void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
} 

//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
u8 DS18B20_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //ʹ��PORTA��ʱ�� 
	
 	GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;				//PORTA.6 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);

 	GPIO_SetBits(DS18B20_GPIO_PORT,DS18B20_GPIO_PIN);    //���1

	DS18B20_Rst();

	return DS18B20_Check();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
{
    uint8_t temp;
    uint8_t TL,TH;
	short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert	    
    TL=DS18B20_Read_Byte(); 	// LSB   
    TH=DS18B20_Read_Byte(); 	// MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					//�¶�Ϊ��  
    }else temp=1;				//�¶�Ϊ��	  	  
    tem=TH; 					//��ø߰�λ
    tem<<=8;    
    tem+=TL;					//��õװ�λ
    tem=(float)tem*0.625;		//ת��     
	if(temp)return tem; 		//�����¶�ֵ
	else return -tem;    
}

void DS18B20_Mode(uint8_t mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_GPIO_CLK, ENABLE);	 //ʹ��PORTA��ʱ��
	
	if(mode)
	{
		GPIO_InitStructure.GPIO_Pin = DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Pin =  DS18B20_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	GPIO_Init(DS18B20_GPIO_PORT, &GPIO_InitStructure);
}



 
