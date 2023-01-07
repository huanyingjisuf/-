#ifndef _FLASH_H_
#define _FLASH_H_

enum
{
	CMD_DATA_AREA_READ 				= 1,	
	CMD_DATA_AREA_WIRTE_PAGE 		= 2,	
	CMD_DATA_AREA_ERASE_PAGE 		= 3,
	CMD_FLASH_ERASE_SECTOR 			= 4,
};
enum
{
	CMD_FLASH_UNLOCK 				= 0x28,
	CMD_CODE_AREA_UNLOCK 			= 0x29,
	CMD_DATA_AREA_UNLOCK 			= 0x2A,
	CMD_FLASH_LOCK 					= 0xAA,
};

 //¼Ä´æÆ÷FSCMDÎ»¶¨Òå
#define IFEN		(1<<7)
#define CLRPL		(1<<3)

void Data_Area_Erase_Page(unsigned char PageNumber);
void Data_Area_Write_Page(unsigned char PageNumber,unsigned char *pData);
void Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length);

#endif