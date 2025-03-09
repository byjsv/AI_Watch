#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�ַ�������*/
/*���������궨��ֻ�ɽ������һ����ע��*/
//#define OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
#define OLED_CHARSET_GB2312		//�����ַ���ΪGB2312

/*��ģ������Ԫ*/
typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
	char Index[5];					//�����������ռ�Ϊ5�ֽ�
#endif
	
#ifdef OLED_CHARSET_GB2312			//�����ַ���ΪGB2312
	char Index[3];					//�����������ռ�Ϊ3�ֽ�
#endif
	
	uint8_t Data[32];				//��ģ����
} ChineseCell_t;

typedef struct 
{
	
#ifdef OLED_CHARSET_UTF8			//�����ַ���ΪUTF8
	char Index[5];					//�����������ռ�Ϊ5�ֽ�
#endif
	
#ifdef OLED_CHARSET_GB2312			//�����ַ���ΪGB2312
	char Index[3];					//�����������ռ�Ϊ3�ֽ�
#endif
	
	uint8_t Data[24];				//��ģ����
} Small_ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];
extern const Small_ChineseCell_t  OLED_CF12x12[];

/*ͼ����������*/
extern const uint8_t Diode[];
extern const uint8_t Num0[];
extern const uint8_t Num1[];
extern const uint8_t Num2[];
extern const uint8_t Num3[];
extern const uint8_t Num4[];
extern const uint8_t Num5[];
extern const uint8_t Num6[];
extern const uint8_t Num7[];
extern const uint8_t Num8[];
extern const uint8_t Num9[];
extern const uint8_t spit[];
extern const uint8_t No_Signer[];
extern const uint8_t Setting[];
extern const uint8_t HRate[];
extern const uint8_t OxRate[];
extern const uint8_t fire[];
extern const uint8_t step[];
extern const uint8_t barbell[];
/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
//...

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
