#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"
#include "include/system_clock.h"
#include "include/uart.h"
#include "include/delay.h"
#include "include/flash.h"
#include "include/adc.h"
#include <intrins.h>
/********************************************************************************************************************/

/******************************************************************************************************************
	Flash存储器组织结构:
	(1)Flash 由若干个页组成，页是进行擦除和写操作的最小单位，每个页为64字节。
	(2)Flash 写操作以页为单位进行，必须一次性写入64字节，不支持单字节写入。
	(2)Flash 可以按功能划分为程序区和数据区，划分单位为128字节，程序区用于存储用户的程序，数据区是用于存储一些掉电需要保存的数据。

	本例程划分128字节为数据空间，实现10个字节数据掉电存储功能，初次上电分别设置初值为0~9，后面每次上电数据累加。
	为了防止在擦除或写入FLASH阶段发生芯片掉电或复位，从而导致出现数据丢失的情况，本例程采用双页存储的模式，可保证数据存储的安全性。


	说明：
	在调试FLASH过程中只能通过串口助手工具来打印数据，不能使用仿真功能，因为在进行仿真时，FLASH的资源会被占用。
	#define PRINT_EN			//使用uart_printf函数打印使能
******************************************************************************************************************/
unsigned char idata UserDataBuff[10];
unsigned char idata BuffTemp[64];

void main(void)
{	
	unsigned char i;

#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//设置LVD复位电压为2.2V
#endif

#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);						//初始化UART
#endif
	
	EA = 1;												//开全局中断


	PADRD = 128-1;										//划分FLASH最后128字节为数据空间
	
	Data_Area_Mass_Read(0,BuffTemp,2);					//读页0 16位ID，16位ID用以识别是否初次上电
	if(BuffTemp[0] != 0xAA || BuffTemp[1] != 0x55)		//若ID不相符，
	{
		Data_Area_Mass_Read(64,BuffTemp,2);				//读取16位ID，16位ID用以识别是否初次上电
		if(BuffTemp[0] == 0xAA && BuffTemp[1] == 0x55)	//若页0 ID不相符，则判断页1 ID
		{
			goto READ_SECOND_SECTOR_PARA;				//若相符，跳转读取页1数据
		}
		
		//若页0、1 ID都不相符， 表示是初次上电
FIRST_POWER_ON:
		//初次上电，初始化用户数据为 0 ~ 9
		UserDataBuff[0] = 0x00;			
		UserDataBuff[1] = 0x01;
		UserDataBuff[2] = 0x02;
		UserDataBuff[3] = 0x03;
		UserDataBuff[4] = 0x04;
		UserDataBuff[5] = 0x05;
		UserDataBuff[6] = 0x06;
		UserDataBuff[7] = 0x07;
		UserDataBuff[8] = 0x08;
		UserDataBuff[9] = 0x09;		
		
		BuffTemp[0] = 0xAA;								//设置ID为0xAA55
		BuffTemp[1] = 0x55;
		BuffTemp[12] = 0;
		
		for(i = 0; i < 10; i++)
		{
			BuffTemp[i+2] = UserDataBuff[i];
			BuffTemp[12] += UserDataBuff[i];			//计算校验码
		}
		
		//在擦除页或写入数据时，如果出现芯片掉电或复位，会导致用户数据丢失，以下采用双页存储的方式，可避免数据丢失。
		Data_Area_Erase_Page(0);						//擦除数据页0
		Data_Area_Write_Page(0,BuffTemp);				//用户数据、ID、校验码写入数据空间,注：写操作以页为单位进行，必须一次性写入64字节，不支持单字节写入
	
		Data_Area_Erase_Page(1);						//擦除数据页1
		Data_Area_Write_Page(1,BuffTemp);				//用户数据、ID、校验码写入数据空间,注：写操作以页为单位进行，必须一次性写入64字节，不支持单字节写入
	}
	else
	{
		unsigned char CheckSum;
		Data_Area_Mass_Read(0,BuffTemp,13);				//读取用户数据、ID、校验码
		CheckSum = 0;
		for(i = 0; i < 10; i++)
		{
			CheckSum += BuffTemp[2+i];					//计算校验码
		}
		if(CheckSum != BuffTemp[12])					//判断检验码是否相符
		{	
READ_SECOND_SECTOR_PARA:
			//如果校验码不相符，则读取第二页数据。
			Data_Area_Mass_Read(64,BuffTemp,13);		//读取用户数据、ID、校验码
			CheckSum = 0;
			for(i = 0; i < 10; i++)
			{
				CheckSum += BuffTemp[2+i];				//计算校验码
			}
			if(CheckSum != BuffTemp[12])				//判断检验码是否相符
			{
				goto FIRST_POWER_ON;
			}
		}
		
		for(i = 0; i < 10; i++)
		{
			UserDataBuff[i] = BuffTemp[i+2];			//读出的数据装载到用户数据数组
		}
		
		for(i = 0; i < 10; i++)
		{
			UserDataBuff[i]++;							//用户数据累加
		}
		
		BuffTemp[0] = 0xAA;									
		BuffTemp[1] = 0x55;
		BuffTemp[12] = 0;
		for(i = 0; i < 10; i++)
		{
			BuffTemp[i+2] = UserDataBuff[i];
			BuffTemp[12] += UserDataBuff[i];
		}

		Data_Area_Erase_Page(0);						//擦除数据页0
		Data_Area_Write_Page(0,BuffTemp);				//用户数据、ID、校验码写入数据空间,注：写操作以页为单位进行，必须一次性写入64字节，不支持单字节写入

		Data_Area_Erase_Page(1);						//擦除数据页1
		Data_Area_Write_Page(1,BuffTemp);				//用户数据、ID、校验码写入数据空间,注：写操作以页为单位进行，必须一次性写入64字节，不支持单字节写入
	}
	//用户数据打印，每次上电或复位，用户数据加1
#ifdef PRINT_EN
	uart_printf("UserDataBuff[0] = 0x%x\n", (unsigned int)(UserDataBuff[0]));
	uart_printf("UserDataBuff[1] = 0x%x\n", (unsigned int)(UserDataBuff[1]));
	uart_printf("UserDataBuff[2] = 0x%x\n", (unsigned int)(UserDataBuff[2]));
	uart_printf("UserDataBuff[3] = 0x%x\n", (unsigned int)(UserDataBuff[3]));
	uart_printf("UserDataBuff[4] = 0x%x\n", (unsigned int)(UserDataBuff[4]));
	uart_printf("UserDataBuff[5] = 0x%x\n", (unsigned int)(UserDataBuff[5]));
	uart_printf("UserDataBuff[6] = 0x%x\n", (unsigned int)(UserDataBuff[6]));
	uart_printf("UserDataBuff[7] = 0x%x\n", (unsigned int)(UserDataBuff[7]));
	uart_printf("UserDataBuff[8] = 0x%x\n", (unsigned int)(UserDataBuff[8]));
	uart_printf("UserDataBuff[9] = 0x%x\n", (unsigned int)(UserDataBuff[9]));
#endif
	while(1)
	{
	}
}
#endif
