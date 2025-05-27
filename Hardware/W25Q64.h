#ifndef __W25Q64_H
#define __W25Q64_H

#define Font_Index_Address 0x000000
#define Font_Address 0x001C00

void W25Q64_Init(void);     //  ��ʼ��
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);		//  ��ID
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t count);		//		ҳ��д
void W25Q64_PageErase(uint32_t Address);		//  ҳ����
void W25Q64_SectorErase(uint32_t Address);		//  ��������
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t count);		//  ������


void Font_Clear();
void write_Font(const uint8_t *Array,uint16_t cursor, uint32_t length);		//  д��ģ���ݣ���ʼ��ַ����28ҳ
void write_index(char *string);
uint16_t W25Q64_Chinese_ReadIndex(char *string);					//������(GB2312)
void W25Q64_Chinese_ReadFont(uint16_t index, uint8_t *Array);		//����ģ(GB2312)


#endif
