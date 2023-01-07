
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
	本例程设置PWM0直接输出内部时钟
*********************************************************************************************************************/
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
	uart_printf("PWM Clock Out Demo Code\n");
#endif

	
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
	
	//PWMDIV、PWMDUT都设置为0可直接输出时钟
	PWMDIVH	= 0;			
	PWMDIVL	= 0;
	PWMDUTH	= 0;
	PWMDUTL	= 0;

 	PWMUPD = (1<<PWM_CH0);									//PWMDIV、PWMDUT更新使能
	while(PWMUPD);													//等待更新完成
 	PWMEN = (1<<PWM_CH0);										//PWM0使能
	
	while(1)
	{
	}
}
#endif
