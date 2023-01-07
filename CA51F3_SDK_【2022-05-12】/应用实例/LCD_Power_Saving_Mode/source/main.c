
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
	本例程实现4com*9seg、1/3bias LCD显示功能，LCD时钟设置为XOSCL或IRCL，实现LCD最小电流模式。
	
	重要提示：
	在关闭LCD功能前，把所设置的COM脚和SEG脚设置为输出模式并输出低电平，可以避免关闭LCD功能时LCD屏出现拖影现象。
*********************************************************************************************************************/			
void LCD_Off(void)
{
	//在关闭LCD功能前，把所设置的COM脚和SEG脚设置为输出模式并输出低电平，可以避免关闭LCD功能时LCD屏出现拖影现象。
	P00 = 0;
	P01 = 0;
	P02 = 0;
	P03 = 0;	 
       
	P17 = 0;
	P37 = 0; 
	P36 = 0; 
	P35 = 0;
	P34 = 0;
	P07 = 0;
	P06 = 0;
	P05 = 0;
	P04 = 0;
	
	P00F = OUTPUT;
	P01F = OUTPUT;
	P02F = OUTPUT;
	P03F = OUTPUT;	 
       
	P17F = OUTPUT;
	P37F = OUTPUT; 
	P36F = OUTPUT;  
	P35F = OUTPUT; 
	P34F = OUTPUT;
	P07F = OUTPUT;
	P06F = OUTPUT; 
	P05F = OUTPUT;
	P04F = OUTPUT;
	
	LXCON = 0;						//关闭LCD功能
}

void main(void)
{	
	unsigned char i;
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
	uart_printf("LCD Power Saving Mode Demo Code\n");
#endif
		
	//初始化LCD驱动引脚
	P00F = P00_COM0_SETTING;
	P01F = P01_COM1_SETTING;
	P02F = P02_COM2_SETTING;
	P03F = P03_COM3_SETTING;	 
       
	P17F = P17_SEG0_SETTING;
	P37F = P37_SEG1_SETTING; 
	P36F = P36_SEG2_SETTING;  
	P35F = P35_SEG3_SETTING; 
	P34F = P34_SEG4_SETTING;
	P07F = P07_SEG5_SETTING;
	P06F = P06_SEG6_SETTING; 
	P05F = P05_SEG7_SETTING;
	P04F = P04_SEG8_SETTING;	
	
	
	//LCD RAM清零
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}
	
	P32F = P32_XOSC_IN_SETTING;			//设置P32为晶振引脚
	P33F = P33_XOSC_OUT_SETTING;		//设置P33为晶振引脚
	CKCON |= XLCKE;									//使能XSOCL
	while(!(CKCON & XLSTA));				//等待XSOCL稳定
	
// 	CKCON |= ILCKE;									//使能IRCL

	LXDIVH = 0;				//设置LCD时钟分频，目标帧频率为64HZ
	LXDIVL = 0;	
	LXCAD = 0;
	LXCFG =	 DMOD(DMOD_5ua) | BIAS(BIAS_1_3) | LDRV(LDRV_7);			//设置LCD驱动电流、偏压(bias)、辉度
	LXCON =  LEN(LEN_XOSCL) | LMOD(LMOD_lcd);	 										//设置LCD时钟源为XOSCL，选择LCD模式
// 	LXCON =  LEN(LEN_IRCL) | LMOD(LMOD_lcd);	 									//设置LCD时钟源为IRCL，选择LCD模式
	
	//设置LCD全显
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0xFF;
	}

//	LCD_Off();
	
	I2CCON = 0;						//关闭I2C，否则系统时钟无法关闭
	CKCON = XLCKE;					//关闭除LCD时钟外的其他时钟
// 	CKCON = ILCKE;	
	PWCON &= ~0x08;					//LDO进入低功率模式
	
	PCON = (PCON&0x84) | 0x02;      //进入STOP模式
	_nop_();
	_nop_();
	_nop_();
	while(1)
	{
	}
}
#endif
