#ifndef __W25Q64_H
#define __W25Q64_H

#define Font_Index_Address 0x000000
#define Font_Address 0x001C00

void W25Q64_Init(void);     //  初始化
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);		//  读ID
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t count);		//		页编写
void W25Q64_PageErase(uint32_t Address);		//  页擦除
void W25Q64_SectorErase(uint32_t Address);		//  扇区擦除
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t count);		//  读数据


void Font_Clear();
void write_Font(const uint8_t *Array,uint16_t cursor, uint32_t length);		//  写字模数据，起始地址：第28页
void write_index(char *string);
uint16_t W25Q64_Chinese_ReadIndex(char *string);					//读索引(GB2312)
void W25Q64_Chinese_ReadFont(uint16_t index, uint8_t *Array);		//读字模(GB2312)


#endif
