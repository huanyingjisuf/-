#ifndef _FLASH_C_
#define _FLASH_C_
/*********************************************************************************************************************/
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/flash.h"
#include <intrins.h>
/*********************************************************************************************************************/

/***********************************************************************************
�� �� ����Data_Area_Erase_Sector										 	
���������������������ռ��һ������						
����˵����								
��    �룺unsigned char SectorNumber	�����ţ���Χ 0-31										
��    �أ���																	
***********************************************************************************/
void Data_Area_Sector_Erase(unsigned char SectorNumber)
{
	unsigned int SectorAddress;
	FSCMD 	= 	0;
	SectorAddress = 0x80*SectorNumber;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//����������
	PTSH = (unsigned char)(SectorAddress>>8);			//��д������ַ
	PTSL = (unsigned char)(SectorAddress);				//��д������ַ	
	FSCMD = CMD_DATA_AREA_ERASE_SECTOR;					//ִ�в�����������
	LOCK  = CMD_FLASH_LOCK;						    	//��FLASH����
} 


/***********************************************************************************
�� �� ����Data_Area_Write_Byte											 	
������������FLASH������д��һ���ֽ�����																	
��    �룺unsigned int Address	�������ռ�д���ַ											
					unsigned char Data		д������												
��    �أ���																	
***********************************************************************************/
void Data_Area_Write_Byte(unsigned int Address,unsigned char Data)
{
	FSCMD 	= 	0;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//����������
	PTSH = (unsigned char)(Address>>8);			//��д��λ��ַ
	PTSL = (unsigned char)Address;        	//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_WIRTE;						//ִ��д����
	FSDAT = Data;														//װ������	
	LOCK  = CMD_FLASH_LOCK;						    	//��FLASH����
} 



/***********************************************************************************
�� �� ����Data_Area_Mass_Write										 	
������������FLASH����������д������																	
��    �룺unsigned int wAddress	  �������ռ�д����ʼ��ַ											
					unsigned char *pData		����ָ�룬ָ��д�����ݻ�������
					unsigned char Length		д�����ݳ���												
��    �أ���																	
***********************************************************************************/
void Data_Area_Mass_Write(unsigned int Address,unsigned char *pData,unsigned int Length)
{
	unsigned int i;
	FSCMD 	= 	0;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//����������
	PTSH = (unsigned char)(Address>>8);			//��д��λ��ַ
	PTSL = (unsigned char)Address;        	//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_WIRTE;						//ִ��д����
	for(i = 0; i < Length; i++)
	{
		FSDAT = *pData++;											//װ������	
	}
	LOCK  = CMD_FLASH_LOCK;						    	//��FLASH����
} 



/***********************************************************************************
�� �� ����Data_Area_Read_Byte											 	
������������FLASH����������һ�ֽ�����																
��    �룺unsigned int Address	�������ռ����ַ																							
��    �أ���ȡ��һ�ֽ�����																	
***********************************************************************************/
unsigned char Data_Area_Read_Byte(unsigned int Address)
{	
	unsigned char Data_Temp;
	FSCMD 	= 	0;
	PTSH = (unsigned char)(Address>>8);				//��д��λ��ַ
	PTSL = (unsigned char)Address;        				//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_READ;							//ִ�ж�����
	Data_Temp = FSDAT;
	LOCK  = CMD_FLASH_LOCK;						    	//��FLASH����
	return Data_Temp;
} 



/***********************************************************************************
�� �� ����Data_Area_Mass_Read										 	
������������FLASH������������������																	
��    �룺unsigned int Address	  �������ռ����ʼ��ַ											
					unsigned char *pData		����ָ�룬ָ��������ݻ�������
					unsigned char Length		�����ݳ���												
��    �أ���																	
***********************************************************************************/
void Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length)
{
	unsigned int i;
	FSCMD 	= 	0;
	PTSH = (unsigned char)(Address>>8);				//��д��λ��ַ
	PTSL = (unsigned char)Address;        				//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_READ;							//ִ�ж�����
	for(i = 0; i < Length; i++)
	{												
		*pData++ = FSDAT;
	}
	LOCK  = CMD_FLASH_LOCK;						    	//��FLASH����
} 
#endif 