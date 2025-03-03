#ifndef __W25Q64_H
#define __W25Q64_H

void W25Q64_Init(void);     //  ��ʼ��
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);		//  ��ID
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t count);		//		ҳ��д
void W25Q64_SectorErase(uint32_t Address);		//  ҳ����
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t count);		//  ������


#endif
