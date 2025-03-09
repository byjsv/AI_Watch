#include "OLED.h"
#include "math.h"
#include "string.h"

/**
 * 函    数：旋转点
 * 参    数：CX 指定旋转原点的横坐标，范围：0~127
 * 参    数：CY 指定旋转原点的纵坐标，范围：0~63
 * 参    数：PX 指定旋转点的横坐标，范围：0~127
 * 参    数：PY 指定旋转点的纵坐标，范围：0~63
 * 参    数：Angle 指定旋转角度，范围：-360~360
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Rotation_C_P(int8_t CX, int8_t CY, float *PX, float *PY, int16_t Angle) // 旋转点
{
	float Theta = (3.14 / 180) * Angle;
	float Xd = *PX - CX;
	float Yd = *PY - CY;

	*PX = (Xd)*cos(Theta) - (Yd)*sin(Theta) + CX; // + 0.5;
	*PY = (Xd)*sin(Theta) + (Yd)*cos(Theta) + CY; // + 0.5;
}
/**
 * 函    数：将OLED显存数组部分旋转
 * 参    数：X 指定旋转原点的横坐标，范围：0~127
 * 参    数：Y 指定旋转原点的纵坐标，范围：0~63
 * 参    数：Width 指定旋转区域半径，范围：0~63
 * 参    数：Angle 指定旋转角度，范围：-360~360
 * 返 回 值：无
 * 说    明：调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Rotation_Block(int8_t X, int8_t Y, int8_t Width, int16_t Angle) // 旋转区块
{
	uint8_t OLED_DpB1[8][128];
	memcpy(OLED_DpB1, OLED_DisplayBuf, 1024);

	// OLED_Clear();
	OLED_ClearArea(X - Width, Y - Width, Width * 2, Width * 2);
	float Theta = (3.14 / 180) * Angle;

	uint8_t x, y;
	for (y = Y - Width; y < Y + Width; y++) // 遍历指定页
	{
		for (x = X - Width; x < X + Width; x++) // 遍历指定列
		{
			//			if(x > 127) break;
			//			if(y > 63) break;
			//			if(x < 0) break;
			//			if(y < 0) break;
			x %= 128;
			y %= 64;

			if (OLED_DpB1[y / 8][x] & 0x01 << (y % 8)) // 效果同if(OLED_GetPoint(x, y))
			{
				OLED_DrawPoint(
					(float)(x - X) * cos(Theta) - (float)(y - Y) * sin(Theta) + X, //+ 0.5,
					(float)(x - X) * sin(Theta) + (float)(y - Y) * cos(Theta) + Y  // + 0.5
				);
			}
		}
	}
}

void OLED_ShowString_12X12(int16_t X, int16_t Y, char *String)
{
	uint16_t i = 0;
	char SingleChar[5];
	uint8_t CharLength = 0;
	uint16_t XOffset = 0;
	uint16_t pIndex;
	
	while (String[i] != '\0')	//遍历字符串
	{
		
		
		OLED_CHARSET_GB2312						//定义字符集为GB2312
		/*此段代码的目的是，提取GB2312字符串中的一个字符，转存到SingleChar子字符串中*/
		/*判断GB2312字节的最高位标志位*/
		if ((String[i] & 0x80) == 0x00)			//最高位为0
		{
			CharLength = 1;						//字符为1字节
			SingleChar[0] = String[i ++];		//将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
			SingleChar[1] = '\0';				//为SingleChar添加字符串结束标志位
		}
		else									//最高位为1
		{
			CharLength = 2;						//字符为2字节
			SingleChar[0] = String[i ++];		//将第一个字节写入SingleChar第0个位置，随后i指向下一个字节
			if (String[i] == '\0') {break;}		//意外情况，跳出循环，结束显示
			SingleChar[1] = String[i ++];		//将第二个字节写入SingleChar第1个位置，随后i指向下一个字节
			SingleChar[2] = '\0';				//为SingleChar添加字符串结束标志位
		}
		
		/*显示上述代码提取到的SingleChar*/
		if (CharLength == 1)	//如果是单字节字符
		{
			/*使用OLED_ShowChar显示此字符*/
			OLED_ShowChar(X + XOffset, Y, SingleChar[0], OLED_6X8);
			XOffset += 6;
		}
		else					//否则，即多字节字符
		{
			/*遍历整个字模库，从字模库中寻找此字符的数据*/
			/*如果找到最后一个字符（定义为空字符串），则表示字符未在字模库定义，停止寻找*/
			for (pIndex = 0; strcmp(OLED_CF12x12[pIndex].Index, "") != 0; pIndex ++)
			{
				/*找到匹配的字符*/
				if (strcmp(OLED_CF12x12[pIndex].Index, SingleChar) == 0)
				{
					break;		//跳出循环，此时pIndex的值为指定字符的索引
				}
			}
			/*将字模库OLED_CF16x16的指定数据以16*16的图像格式显示*/
			OLED_ShowImage(X + XOffset, Y, 12, 12, OLED_CF12x12[pIndex].Data);
			XOffset += 12;
			
		}
	}
}

