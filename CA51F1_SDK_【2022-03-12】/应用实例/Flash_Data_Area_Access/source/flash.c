#ifndef _FLASH_C_
#define _FLASH_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"
#include "include/flash.h"
#include <intrins.h>
/*********************************************************************************************************************/

/***********************************************************************************
函 数 名：Data_Area_Erase_Page										 	
功能描述：擦除数据区空间的一个页					
函数说明：								
输    入：unsigned char PageNumber	页号，范围 0-255										
返    回：无																	
***********************************************************************************/
void Data_Area_Erase_Page(unsigned char PageNumber)
{
	unsigned int Address;
	FSCMD =	0;
	Address = 0x40*PageNumber;
	LOCK = CMD_DATA_AREA_UNLOCK;					//数据区解锁
	PTSH = (unsigned char)(Address>>8);				//填写页地址
	PTSL = (unsigned char)(Address);				//填写页地址	
	FSCMD = CMD_DATA_AREA_ERASE_PAGE;				//执行擦除页操作
	LOCK = CMD_FLASH_LOCK;						    //对FLASH加锁
} 

/***********************************************************************************
函 数 名：Data_Area_Write_Page										 	
功能描述：向FLASH数据区批量写入一个页													
输    入：			unsigned char PageNumber	页号，范围 0-255											
					unsigned char *pData		数据指针，指向写入数据缓存数组
返    回：无																	
***********************************************************************************/
void Data_Area_Write_Page(unsigned char PageNumber,unsigned char *pData)
{
	unsigned int i;
	unsigned int Address;
	FSCMD = 0;
	Address = 0x40*PageNumber;
	LOCK = CMD_DATA_AREA_UNLOCK;					//数据区解锁
	PTSH = 0;
	PTSL = 0;
	FSCMD = CLRPL;
	for(i = 0; i < 64; i++)
	{
		FSDAT = *pData++;							//装载数据	
	}
	PTSH = (unsigned char)(Address>>8);				//填写高位地址
	PTSL = (unsigned char)Address;        			//填写低位地址
	FSCMD = CMD_DATA_AREA_WIRTE_PAGE;				//执行写操作
	LOCK = CMD_FLASH_LOCK;						    //对FLASH加锁
} 

/***********************************************************************************
函 数 名：Data_Area_Mass_Read										 	
功能描述：从FLASH数据区批量读出数据																	
输    入：unsigned int Address	  数据区空间读起始地址											
					unsigned char *pData		数据指针，指向读出数据缓存数组
					unsigned char Length		读数据长度												
返    回：无																	
***********************************************************************************/
void Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length)
{
	unsigned int i;
	FSCMD =	0;
	LOCK = CMD_DATA_AREA_UNLOCK;					//数据区解锁
	PTSH = (unsigned char)(Address>>8);				//填写高位地址
	PTSL = (unsigned char)Address;        			//填写低位地址
	FSCMD = CMD_DATA_AREA_READ;						//执行读操作
	for(i = 0; i < Length; i++)
	{												
		*pData++ = FSDAT;
	}
	FSCMD = 0;
	LOCK = CMD_FLASH_LOCK;						    //对FLASH加锁
} 
#endif 