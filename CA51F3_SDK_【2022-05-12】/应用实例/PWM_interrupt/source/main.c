
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/pwm.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************
	本例程设置PWM0输出频率为30KHZ、占空比50%的PWM信号, 并产生PWM上升沿中断

	备注：
	1、PWM有多种时钟源可以选择，时钟源是以两路PWM为单位进行设置的，
	分别是：PWM0 和 PWM1、PWM2 和 PWM3、PWM4 和 PWM5，也就是说，每
	组PWM的时钟源是共同设置的，时钟源通过 PWM0、PWM2、PWM4对应的控
	制寄存器 PWMCON 的PWMCKS来选择。

	2、PWMCON、PWMCFG、PWMDIVH、PWMDIVL、PWMDUTH、PWMDUTL、PWMCMAX等
	寄存器是带索引的寄存器，设置带索引的寄存器前先设置INDEX寄存器，
	具体操作请参考下面的例子
*********************************************************************************************************************/
#define PWMDIV_V				(3686400/30000)		//当PWM时钟为其他时钟频率时，需相应修改参数
#define PWMDUT_V				(PWMDIV_V/2)			//占空比为50%

/*******************************************************************************************************************/

void INT9_ISR(void) interrupt 14  using 1
{					  
	if(PWMAIF & PIF0)		//PWM上升沿中断
	{	
		PWMAIF = PIF0;		//清除中断标志
		
	}
}
void main(void)
{
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
	uart_printf("PWM interrupt Demo Code\n");
#endif

//---------------------------------------------------------------------------------------------	
	CKCON |= IHCKE;					//打开IRCH时钟
// 	CKCON |= ILCKE;				//打开IRCL时钟
// 	CKCON |= TFCKE;				//打开TFRC时钟

// 	GPIO_Init(P32F,P32_XOSC_IN_SETTING);
// 	GPIO_Init(P33F,P33_XOSC_OUT_SETTING);
// 	CKCON |= XLCKE;
// 	while(!(CKCON & XLSTA));
// 	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;		//打开XSOCL时钟


// 	PLLCON = PLLON(1) | MULFT(7);
// 	while(!(PLLCON & PLSTA));
// 	CKSEL = (CKSEL&0xF8) | CKSEL_PLL;			//打开PLL时钟

	
	P15F = P15_PWM0_SETTING;								//设置P15为PWM引脚功能

	INDEX = PWM_CH0;												//设置INDEX值对应PWM0
	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IH ;		  //设置PWM时钟源为IRCH  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //设置PWM时钟源为IRCL
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XL ;		  //设置PWM时钟源为XOSCL  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_TF ;		  //设置PWM时钟源为TFRC 
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_PLL ;		//设置PWM时钟源为PLL  
	PWMCFG = TOG(0) | 0;																								
	
	//设置PWMDIV、PWMDUT
	PWMDIVH	= (unsigned char)(PWMDIV_V>>8);			
	PWMDIVL	= (unsigned char)(PWMDIV_V);			
	PWMDUTH	=	(unsigned char)(PWMDUT_V>>8);		
	PWMDUTL	= (unsigned char)(PWMDUT_V);	

 	PWMUPD = (1<<PWM_CH0);									//PWMDIV、PWMDUT更新使能
	while(PWMUPD);													//等待更新完成
 	PWMEN = (1<<PWM_CH0);										//PWM0使能

	
	INDEX = PWM_CH0;														//设置INDEX值对应PWM0
	PWMCON |=TIE(0) | ZIE(0) | PIE(1) | NIE(0);	//使能上升沿中断
	PWMCMAX = 0;																//设置每个上升沿都触发
	INT9EN = 1;																	//使能INT9中断

	while(1)
	{
	}
}
#endif
