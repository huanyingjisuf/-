
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/flash.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/

/******************************************************************************************************************
	本例程划分256字节为数据空间，实现10个字节数据掉电存储功能，初次上电分别设置初值为0~9，后面每次上电数据累加。
	为了防止在擦除或写入FLASH阶段发生芯片掉电或复位，从而导致出现数据丢失的情况，本例程采用双扇区存储的模式，可保证数据存储的安全性。

	备注：由于仿真模式下，FLASH 的部分资源会被占用。在测试FLASH存储功能时，只能通过串口助手工具来打印调试。
	本例程默认打开UART0用于调试。
*******************************************************************************************************************/
unsigned char UserDataBuff[10];
unsigned char BuffTemp[13];
void main(void)
{	
	unsigned char i;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE1;					//设置LVD复位电压为2V
#endif
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("Flash Data Area Access Demo Code\n");
#endif

	PADRD	= FLASH_SIZE*4 - 1;		//划分FLASH最后256字节为数据空间，注意：不同型号芯片FLASH容量不同，定义的FLASH_SIZE也不同，应用时要根据实际FLASH容量定义
	
	Data_Area_Mass_Read(0,BuffTemp,2);					//读扇区0 16位ID，16位ID用以识别是否初次上电
	if(BuffTemp[0] != 0xAA || BuffTemp[1] != 0x55)		//若ID不相符，
	{
		Data_Area_Mass_Read(128,BuffTemp,2);			//读取16位ID，16位ID用以识别是否初次上电
		if(BuffTemp[0] == 0xAA && BuffTemp[1] == 0x55)	//若扇区0 ID不相符，则判断扇区1 ID
		{
			goto READ_SECOND_SECTOR_PARA;				//若相符，跳转读取扇区1数据
		}
		
		//若扇区0、1 ID都不相符， 表示是初次上电
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
		
		//在擦除扇区或写入数据时，如果出现芯片掉电或复位，会导致用户数据丢失，以下采用双扇区存储的方式，可避免数据丢失。
		Data_Area_Sector_Erase(0);						//擦除数据扇区
		Data_Area_Mass_Write(0,BuffTemp,13);			//用户数据、ID、校验码写入数据空间
		
		Data_Area_Sector_Erase(1);						//擦除数据扇区
		Data_Area_Mass_Write(128,BuffTemp,13);			//用户数据、ID、校验码写入数据空间
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
			//如果校验码不相符，则读取第二扇区数据。
			Data_Area_Mass_Read(128,BuffTemp,13);		//读取用户数据、ID、校验码
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
		
		Data_Area_Sector_Erase(0);						//擦除数据扇区
		Data_Area_Mass_Write(0,BuffTemp,13);			//用户数据、ID、校验码写入数据空间
		
		Data_Area_Sector_Erase(1);						//擦除数据扇区
		Data_Area_Mass_Write(128,BuffTemp,13);			//用户数据、ID、校验码写入数据空间
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
