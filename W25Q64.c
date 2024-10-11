#include "stm32f10x.h"
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}

void W25Q64_ReadID(uint8_t *MID, uint16_t* DID) // Manufacure & Device ID
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	MySPI_Start();
}

void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

void W25Q64_WaitBusy(void)
{
	uint32_t Timeout=10000; // 暫時先這樣設
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1); // 這裡是SCK上升沿，所以選register 1
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01) // 超時退出機制
	{
		Timeout--;
		if(Timeout==0)
			break;
	}
	MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count) // 最多可以寫256個，0xXXXX00~0xXXXXFF
{
	W25Q64_WriteEnable();
	
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address>>16); // 高位捨棄
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	for(i=0;i<Count;i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy(); // 等他寫完
}

void W25Q64_SectorErase(uint32_t Address) // 0xXXX000~0xXXXFFF
{
	W25Q64_WriteEnable();
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
	
	W25Q64_WaitBusy();
}

void W25Q64_ReadData(uint32_t Address,uint8_t *DataArray,uint16_t Count) // 讀取模式就沒有頁的數量限制了
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address>>16);
	MySPI_SwapByte(Address>>8); // 高位會被捨棄
	MySPI_SwapByte(Address);
	for(i=0;i<Count;i++)
	{
		DataArray[i]=MySPI_SwapByte(W25Q64_DUMMY_BYTE); // 在每次調換交換讀取之後，存儲器內部地址指標都會自動自增
	}
	MySPI_Stop();
}