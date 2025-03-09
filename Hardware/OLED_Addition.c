#include "OLED.h"
#include "math.h"
#include "string.h"

/**
 * ��    ������ת��
 * ��    ����CX ָ����תԭ��ĺ����꣬��Χ��0~127
 * ��    ����CY ָ����תԭ��������꣬��Χ��0~63
 * ��    ����PX ָ����ת��ĺ����꣬��Χ��0~127
 * ��    ����PY ָ����ת��������꣬��Χ��0~63
 * ��    ����Angle ָ����ת�Ƕȣ���Χ��-360~360
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Rotation_C_P(int8_t CX, int8_t CY, float *PX, float *PY, int16_t Angle) // ��ת��
{
	float Theta = (3.14 / 180) * Angle;
	float Xd = *PX - CX;
	float Yd = *PY - CY;

	*PX = (Xd)*cos(Theta) - (Yd)*sin(Theta) + CX; // + 0.5;
	*PY = (Xd)*sin(Theta) + (Yd)*cos(Theta) + CY; // + 0.5;
}
/**
 * ��    ������OLED�Դ����鲿����ת
 * ��    ����X ָ����תԭ��ĺ����꣬��Χ��0~127
 * ��    ����Y ָ����תԭ��������꣬��Χ��0~63
 * ��    ����Width ָ����ת����뾶����Χ��0~63
 * ��    ����Angle ָ����ת�Ƕȣ���Χ��-360~360
 * �� �� ֵ����
 * ˵    �������ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Rotation_Block(int8_t X, int8_t Y, int8_t Width, int16_t Angle) // ��ת����
{
	uint8_t OLED_DpB1[8][128];
	memcpy(OLED_DpB1, OLED_DisplayBuf, 1024);

	// OLED_Clear();
	OLED_ClearArea(X - Width, Y - Width, Width * 2, Width * 2);
	float Theta = (3.14 / 180) * Angle;

	uint8_t x, y;
	for (y = Y - Width; y < Y + Width; y++) // ����ָ��ҳ
	{
		for (x = X - Width; x < X + Width; x++) // ����ָ����
		{
			//			if(x > 127) break;
			//			if(y > 63) break;
			//			if(x < 0) break;
			//			if(y < 0) break;
			x %= 128;
			y %= 64;

			if (OLED_DpB1[y / 8][x] & 0x01 << (y % 8)) // Ч��ͬif(OLED_GetPoint(x, y))
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
	
	while (String[i] != '\0')	//�����ַ���
	{
		
		
		OLED_CHARSET_GB2312						//�����ַ���ΪGB2312
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
		
		/*��ʾ����������ȡ����SingleChar*/
		if (CharLength == 1)	//����ǵ��ֽ��ַ�
		{
			/*ʹ��OLED_ShowChar��ʾ���ַ�*/
			OLED_ShowChar(X + XOffset, Y, SingleChar[0], OLED_6X8);
			XOffset += 6;
		}
		else					//���򣬼����ֽ��ַ�
		{
			/*����������ģ�⣬����ģ����Ѱ�Ҵ��ַ�������*/
			/*����ҵ����һ���ַ�������Ϊ���ַ����������ʾ�ַ�δ����ģ�ⶨ�壬ֹͣѰ��*/
			for (pIndex = 0; strcmp(OLED_CF12x12[pIndex].Index, "") != 0; pIndex ++)
			{
				/*�ҵ�ƥ����ַ�*/
				if (strcmp(OLED_CF12x12[pIndex].Index, SingleChar) == 0)
				{
					break;		//����ѭ������ʱpIndex��ֵΪָ���ַ�������
				}
			}
			/*����ģ��OLED_CF16x16��ָ��������16*16��ͼ���ʽ��ʾ*/
			OLED_ShowImage(X + XOffset, Y, 12, 12, OLED_CF12x12[pIndex].Data);
			XOffset += 12;
			
		}
	}
}

