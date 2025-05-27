#include "stm32f10x.h"      // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"
#include "W25Q64.h"
#include "OLED.h"
#include "delay.h"

#define CHINESE_INDEX_LENGTH 3500     // 字库的中文数量

//************初始化*****************
void W25Q64_Init(void)
{
	MySPI_Init();
}

//************读ID*****************
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

//************写使能*****************
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

//************忙等待*****************
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

//************页编写*****************
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


//************扇区擦除*****************
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

//************页擦除*****************
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

//************读数据*****************
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

//*字库相关函数*****************************************	

//**********清理空间*************************

void Font_Clear()
{
	uint8_t i =0;
	for(i=0;i<30;i++)
	{
		W25Q64_SectorErase(Font_Address+i*4096);
	}
}

//**********写字模(GB2312)*******************
void write_Font(const uint8_t *Array,uint16_t cursor, uint32_t length)		//  写字模数据，起始地址：第28页+写入位置(汉字索引)
{
	
	uint32_t Address = Font_Address +cursor*32;  // 起始地址
    uint16_t i = 0;               // 页内索引
    uint32_t count = 0;           // 数组索引
    uint8_t page[256];            // 页缓冲区
	
	OLED_ShowString(0,0,"写入中...", OLED_8X16);
	OLED_Update();
	
	
	for(i=0,count = 0; count < length; i++,count++)
	{
		 // 将字符写入页缓冲区
        page[i] = Array[count];
		// 如果页缓冲区已满（256 字节），写入闪存
        if (i == 255)
        {
            W25Q64_PageErase(Address);          // 擦除页
            W25Q64_PageProgram(Address, page, 256); // 写入页
            Address += 256;                 // 地址增加 256 字节
            i = 0;                               // 重置页内索引
        }
	}
	if(i>0)
	{
		W25Q64_PageErase(Address);         // 擦除页
		W25Q64_PageProgram(Address, page, i + 1); // 写入剩余数据
	}
	
	OLED_Clear();
	OLED_ShowString(0,0,"完成", OLED_8X16);
	OLED_Update();
}

//**********写索引(GB2312)*******************
void write_index(char *string)
{
    uint32_t Address = Font_Index_Address;  // 起始地址
    uint16_t i = 0;               // 页内索引
    uint16_t count = 0;           // 字符串索引
    uint8_t page[256];            // 页缓冲区
	
	OLED_ShowString(0,0,"写入中...", OLED_8X16);
    OLED_Update();
	
    while (1)
    {
        // 将字符写入页缓冲区
        page[i] = string[count];

        // 如果页缓冲区已满（256 字节），写入闪存
        if (i == 255)
        {
            W25Q64_PageErase(Address);          // 擦除页
            W25Q64_PageProgram(Address, page, 256); // 写入页
            Address += 0x000100;                 // 地址增加 256 字节
            i = 0;                               // 重置页内索引
			
        }

        // 如果字符串结束，写入剩余数据并退出
        if (string[count] == '\0')
        {
            W25Q64_PageErase(Address);         // 擦除页
            W25Q64_PageProgram(Address, page, i + 1); // 写入剩余数据
            break;
        }

        count++;  // 字符串索引增加
        i++;     // 页内索引增加
		
    }
	OLED_Clear();
	OLED_ShowString(0,0,"完成", OLED_8X16);
	OLED_Update();
}

//**********读索引(GB2312)*******************
uint16_t W25Q64_Chinese_ReadIndex(char *string)
{
    uint16_t count = 0;
    uint16_t All_length = CHINESE_INDEX_LENGTH * 2;  // 字库索引总长度（字节）
    uint32_t Address = Font_Index_Address;  // 起始地址
    uint8_t ch[2];  // 用于存储读取的2个字节（一个中文字符）

    // 遍历字库索引
    for (count = 0; count < All_length; count += 2)
    {
        // 从字库中读取2个字节
        W25Q64_ReadData(Address, ch, 2);

        // 比较读取的字符与目标字符
        if (string[0] == ch[0] && string[1] == ch[1])
        {
            return count/2;  // 返回字符在索引中的位置
        }

        Address += 0x000002;  // 地址增加2个字节
    }

    return 0xFFFF;  // 如果没有找到匹配的字符，返回特殊值
}
//**********读字模(GB2312)*******************
void W25Q64_Chinese_ReadFont(uint16_t index, uint8_t *Array)
{
	
	uint32_t Address = Font_Address + index * 0x000020;  // 起始地址
	W25Q64_ReadData(Address, Array, 32);
}

//*******************************字库相关函数*
