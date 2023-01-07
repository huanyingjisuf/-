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
�� �� ����Data_Area_Erase_Page										 	
���������������������ռ��һ��ҳ					
����˵����								
��    �룺unsigned char PageNumber	ҳ�ţ���Χ 0-255										
��    �أ���																	
***********************************************************************************/
void Data_Area_Erase_Page(unsigned char PageNumber)
{
	unsigned int Address;
	FSCMD =	0;
	Address = 0x40*PageNumber;
	LOCK = CMD_DATA_AREA_UNLOCK;					//����������
	PTSH = (unsigned char)(Address>>8);				//��дҳ��ַ
	PTSL = (unsigned char)(Address);				//��дҳ��ַ	
	FSCMD = CMD_DATA_AREA_ERASE_PAGE;				//ִ�в���ҳ����
	LOCK = CMD_FLASH_LOCK;						    //��FLASH����
} 

/***********************************************************************************
�� �� ����Data_Area_Write_Page										 	
������������FLASH����������д��һ��ҳ													
��    �룺			unsigned char PageNumber	ҳ�ţ���Χ 0-255											
					unsigned char *pData		����ָ�룬ָ��д�����ݻ�������
��    �أ���																	
***********************************************************************************/
void Data_Area_Write_Page(unsigned char PageNumber,unsigned char *pData)
{
	unsigned int i;
	unsigned int Address;
	FSCMD = 0;
	Address = 0x40*PageNumber;
	LOCK = CMD_DATA_AREA_UNLOCK;					//����������
	PTSH = 0;
	PTSL = 0;
	FSCMD = CLRPL;
	for(i = 0; i < 64; i++)
	{
		FSDAT = *pData++;							//װ������	
	}
	PTSH = (unsigned char)(Address>>8);				//��д��λ��ַ
	PTSL = (unsigned char)Address;        			//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_WIRTE_PAGE;				//ִ��д����
	LOCK = CMD_FLASH_LOCK;						    //��FLASH����
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
	FSCMD =	0;
	LOCK = CMD_DATA_AREA_UNLOCK;					//����������
	PTSH = (unsigned char)(Address>>8);				//��д��λ��ַ
	PTSL = (unsigned char)Address;        			//��д��λ��ַ
	FSCMD = CMD_DATA_AREA_READ;						//ִ�ж�����
	for(i = 0; i < Length; i++)
	{												
		*pData++ = FSDAT;
	}
	FSCMD = 0;
	LOCK = CMD_FLASH_LOCK;						    //��FLASH����
} 
#endif 