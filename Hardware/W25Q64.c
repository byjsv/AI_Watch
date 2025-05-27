#include "stm32f10x.h"      // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"
#include "W25Q64.h"
#include "OLED.h"
#include "delay.h"

#define CHINESE_INDEX_LENGTH 3500     // �ֿ����������

//************��ʼ��*****************
void W25Q64_Init(void)
{
	MySPI_Init();
}

//************��ID*****************
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(0xFF);
	*DID = MySPI_SwapByte(0xFF);
	*DID <<= 8; 
	*DID |= MySPI_SwapByte(0xFF);
	MySPI_Stop();
}

//************дʹ��*****************
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

//************æ�ȴ�*****************
void W25Q64_WaitBusy(void)
{
	uint32_t timeout;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	timeout = 100000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		timeout--;
		if(timeout == 0)
		{
			break;
		}
	}
	MySPI_Stop();
}

//************ҳ��д*****************
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t count)
{
	W25Q64_WaitBusy();
	
	uint16_t i;
	
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for(i=0;i<count ;i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
	delay_ms(10);
}


//************��������*****************
void W25Q64_SectorErase(uint32_t Address)
{
	
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

//************ҳ����*****************
void W25Q64_PageErase(uint32_t Address)
{
	uint16_t i;
	
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for(i=0;i<256 ;i++)
	{
		MySPI_SwapByte(0xFF);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

//************������*****************
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for (i = 0; i < Count; i ++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}

//*�ֿ���غ���*****************************************	

//**********����ռ�*************************

void Font_Clear()
{
	uint8_t i =0;
	for(i=0;i<30;i++)
	{
		W25Q64_SectorErase(Font_Address+i*4096);
	}
}

//**********д��ģ(GB2312)*******************
void write_Font(const uint8_t *Array,uint16_t cursor, uint32_t length)		//  д��ģ���ݣ���ʼ��ַ����28ҳ+д��λ��(��������)
{
	
	uint32_t Address = Font_Address +cursor*32;  // ��ʼ��ַ
    uint16_t i = 0;               // ҳ������
    uint32_t count = 0;           // ��������
    uint8_t page[256];            // ҳ������
	
	OLED_ShowString(0,0,"д����...", OLED_8X16);
	OLED_Update();
	
	
	for(i=0,count = 0; count < length; i++,count++)
	{
		 // ���ַ�д��ҳ������
        page[i] = Array[count];
		// ���ҳ������������256 �ֽڣ���д������
        if (i == 255)
        {
            W25Q64_PageErase(Address);          // ����ҳ
            W25Q64_PageProgram(Address, page, 256); // д��ҳ
            Address += 256;                 // ��ַ���� 256 �ֽ�
            i = 0;                               // ����ҳ������
        }
	}
	if(i>0)
	{
		W25Q64_PageErase(Address);         // ����ҳ
		W25Q64_PageProgram(Address, page, i + 1); // д��ʣ������
	}
	
	OLED_Clear();
	OLED_ShowString(0,0,"���", OLED_8X16);
	OLED_Update();
}

//**********д����(GB2312)*******************
void write_index(char *string)
{
    uint32_t Address = Font_Index_Address;  // ��ʼ��ַ
    uint16_t i = 0;               // ҳ������
    uint16_t count = 0;           // �ַ�������
    uint8_t page[256];            // ҳ������
	
	OLED_ShowString(0,0,"д����...", OLED_8X16);
    OLED_Update();
	
    while (1)
    {
        // ���ַ�д��ҳ������
        page[i] = string[count];

        // ���ҳ������������256 �ֽڣ���д������
        if (i == 255)
        {
            W25Q64_PageErase(Address);          // ����ҳ
            W25Q64_PageProgram(Address, page, 256); // д��ҳ
            Address += 0x000100;                 // ��ַ���� 256 �ֽ�
            i = 0;                               // ����ҳ������
			
        }

        // ����ַ���������д��ʣ�����ݲ��˳�
        if (string[count] == '\0')
        {
            W25Q64_PageErase(Address);         // ����ҳ
            W25Q64_PageProgram(Address, page, i + 1); // д��ʣ������
            break;
        }

        count++;  // �ַ�����������
        i++;     // ҳ����������
		
    }
	OLED_Clear();
	OLED_ShowString(0,0,"���", OLED_8X16);
	OLED_Update();
}

//**********������(GB2312)*******************
uint16_t W25Q64_Chinese_ReadIndex(char *string)
{
    uint16_t count = 0;
    uint16_t All_length = CHINESE_INDEX_LENGTH * 2;  // �ֿ������ܳ��ȣ��ֽڣ�
    uint32_t Address = Font_Index_Address;  // ��ʼ��ַ
    uint8_t ch[2];  // ���ڴ洢��ȡ��2���ֽڣ�һ�������ַ���

    // �����ֿ�����
    for (count = 0; count < All_length; count += 2)
    {
        // ���ֿ��ж�ȡ2���ֽ�
        W25Q64_ReadData(Address, ch, 2);

        // �Ƚ϶�ȡ���ַ���Ŀ���ַ�
        if (string[0] == ch[0] && string[1] == ch[1])
        {
            return count/2;  // �����ַ��������е�λ��
        }

        Address += 0x000002;  // ��ַ����2���ֽ�
    }

    return 0xFFFF;  // ���û���ҵ�ƥ����ַ�����������ֵ
}
//**********����ģ(GB2312)*******************
void W25Q64_Chinese_ReadFont(uint16_t index, uint8_t *Array)
{
	
	uint32_t Address = Font_Address + index * 0x000020;  // ��ʼ��ַ
	W25Q64_ReadData(Address, Array, 32);
}

//*******************************�ֿ���غ���*
