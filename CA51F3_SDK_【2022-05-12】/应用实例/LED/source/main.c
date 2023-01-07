
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/delay.h"
#include "include/lcd_led.h"
#include <intrins.h>
/*********************************************************************************************************************			
	本例程实现4com*9seg LED显示功能。
*********************************************************************************************************************/			

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
	uart_printf("LED Demo Code\n");
#endif

	
	
	//初始化LED驱动引脚
	P00F = P00_COM0_SETTING;			//设置P00为COM0
	P00C |= 0x80;									//设置P00为高灌电流模式
	
	P01F = P01_COM1_SETTING;			//设置P01为COM1
	P01C |= 0x80;									//设置P01为高灌电流模式
	
	P02F = P02_COM2_SETTING;			//设置P02为COM2
	P02C |= 0x80;									//设置P02为高灌电流模式
	
	P03F = P03_COM3_SETTING;	 		//设置P03为COM3
	P03C |= 0x80;									//设置P03为高灌电流模式
       
			 
	//设置引脚为SEG功能
	P17F = P17_SEG0_SETTING;
	P37F = P37_SEG1_SETTING; 
	P36F = P36_SEG2_SETTING;  
	P35F = P35_SEG3_SETTING; 
	P34F = P34_SEG4_SETTING;
	P07F = P07_SEG5_SETTING;
	P06F = P06_SEG6_SETTING; 
	P05F = P05_SEG7_SETTING;
	P04F = P04_SEG8_SETTING;	
	
	//LED RAM清零
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}

	LXDIVH = 0;						//设置LED时钟分频
	LXDIVL = 112;	
	LXCFG =	 COMHV(COM_L) | SEGHV(SEG_H) | BLNK(0) | LDRV(LDRV_7);		//设置LED COM、SEG有效电平，亮度级别
	LXCON =  LEN(LEN_IRCH) | LMOD(LMOD_led);	 												//设置LED时钟源，选择LED模式
	
	//设置LCD全显
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0xFF;
	}
	while(1)
	{
	}
}
#endif
