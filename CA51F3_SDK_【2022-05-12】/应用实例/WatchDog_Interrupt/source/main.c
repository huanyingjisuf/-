
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/wdt.h"
#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
bit WdtIntEvFlag;
void WDT_ISR (void) interrupt 12 
{
	if(WDFLG & WDIF)
	{
		WDFLG = 0xA5;;
		WdtIntEvFlag = 1;
	}	
}
void main(void)
{	
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
	uart_printf("Watch dog interrpt mode Demo code!\n");
#endif

/***************************看门狗阈值设置计算公式如下****************************
看门狗触发时间 = (WDVTH * 800H+7FFH) * clock cycle
当看门狗时钟为3.6864M时,时间覆盖范围为0.56ms--36s
*********************************************************************************/

//看门狗时钟源为IRCH(内部高速时钟)	
	WDCON  = WDTS(WDTS_IRCH) | WDRE(WDRE_int);   	//设置看门狗时钟源为IRCH，模式为中断模式
	WDVTHH = 0x07;									//看门狗中断阈值高八位设置 当前值为1s
	WDVTHL = 0x08;									//看门狗中断阈值低八位设置

//看门狗时钟源为XOSCL
// 	P32F = P32_XOSC_IN_SETTING;						//设置P32为晶振引脚
// 	P33F = P33_XOSC_OUT_SETTING;					//设置P33为晶振引脚
// 	CKCON |= XLCKE;									//使能XSOCL
// 	while(!(CKCON & XLSTA));						//等待XSOCL稳定
//	WDCON  = WDTS(WDTS_XOSCL) | WDRE(WDRE_int); 	//设置看门狗时钟源为XOSCL，模式为中断模式
//	WDVTHH = 0;										//看门狗中断阈值高八位设置 当前值为1s
//	WDVTHL = 0x0f;									//看门狗中断阈值低八位设置


//看门狗时钟源为IRCL
//	CKCON |= ILCKE;									//使能IRCL
//	WDCON  = WDTS(WDTS_IRCL) | WDRE(WDRE_int);   	//设置看门狗时钟源为ILCKE，模式为中断模式
//	WDVTHH = 0;										//看门狗中断阈值高八位设置 当前值为1s	
//	WDVTHL = 0x0f;									//看门狗中断阈值低八位设置

	
	INT7EN = 1; 									//开启看门狗中断
	WDFLG = 0xA5;									//喂狗
	while(1)
	{
		if(WdtIntEvFlag)							//看门狗中断发生
		{
			WdtIntEvFlag = 0;
#ifdef PRINT_EN
			uart_printf("Watch dog interrupt event happen!\n");	
#endif
		}		
	}
}
#endif
