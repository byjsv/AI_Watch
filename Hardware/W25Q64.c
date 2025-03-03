#include "stm32f10x.h"      // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

//************≥ı ºªØ*****************
void W25Q64_Init(void)
{
	MySPI_Init();
}

//************∂¡ID*****************
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

//************–¥ πƒ‹*****************
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

//************√¶µ»¥˝*****************
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

//************“≥±‡–¥*****************
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t count)
{
	
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
}

//************“≥≤¡≥˝*****************
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

//************∂¡ ˝æ›*****************
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t count)
{
	W25Q64_WaitBusy();
	
	uint16_t i;
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16);
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for(i=0;i<count ;i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}
