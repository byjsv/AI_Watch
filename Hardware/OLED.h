#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>
#include "OLED_Data.h"

/*参数宏定义*********************/

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled参数数值*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*Direct参数数值*/
#define OLED_Left				0
#define OLED_Right				1

/*********************参数宏定义*/

extern uint8_t OLED_DisplayBuf[8][128];

extern uint8_t OLED_Bright;


/*函数声明*********************/

/*工具函数*/
uint32_t OLED_Pow(uint32_t X, uint32_t Y);

/*初始化函数*/
void OLED_Init(void);

/*更新函数*/
void OLED_Update(void);
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显存控制函数*/
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*显示函数*/
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/*自定义重写显示函数*/
uint8_t OLED_ShowString_Length(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowString_Line(int16_t X, int16_t Y, char *String);
void OLED_String_W25Q(int8_t X, int8_t Y, char *String);	//中英文打印;
void OLED_DisplayBuffMove(uint8_t Direct);
void OLED_DisplayBuffMoveArea(uint8_t PosX, uint8_t PosY, uint8_t EndX, uint8_t EndY, uint8_t Direct);
void OLED_Rotation_C_P(int8_t CX, int8_t CY, float *PX, float *PY, int16_t Angle);
void OLED_Rotation_Block(int8_t X, int8_t Y, int8_t Width, int16_t Angle);
void OLED_ShowString_12X12(int16_t X, int16_t Y, char *String);
void OLED_ShowNum_Left(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);

void OLED_SetContrast(uint8_t contrast);
void OLED_SetBrightness(uint8_t level);


/*绘图函数*/
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

/*********************函数声明*/

#endif


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
