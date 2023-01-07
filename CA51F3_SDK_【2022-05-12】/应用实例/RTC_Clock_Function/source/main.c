
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
#include "include/rtc.h"
#include <intrins.h>
/*********************************************************************************************************************/

/*********************************************************************************************************************
	RTC控制例程
*********************************************************************************************************************/
bit HalfSecFlag;
bit AlarmEvFlag;
void RTC_ISR (void) interrupt 13 	 
{
	if(RTCIF & RTC_MF)			//毫秒中断
	{
		RTCIF = RTC_MF;			
	}
	if(RTCIF & RTC_HF)			//半秒中断
	{
		RTCIF = RTC_HF;
		HalfSecFlag = 1;
	}	
	if(RTCIF & RTC_AF)			//闹钟中断
	{
		RTCIF = RTC_AF;	
		AlarmEvFlag = 1;
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
	uart_printf("RTC Demo Code\n");
#endif

	P32F = P32_XOSC_IN_SETTING;			//设置P32为晶振引脚
	P33F = P33_XOSC_OUT_SETTING;		//设置P33为晶振引脚
	CKCON |= XLCKE;									//使能XSOCL
	while(!(CKCON & XLSTA));				//等待XSOCL稳定
	
	RTCON = RTCE(1) | MSE(1) | HSE(1) | SCE(1) | MCE(1) | HCE(1);	//使能RTC功能，设置半秒、毫秒中断开启，闹铃功能开启(时、分、秒匹配使能)
	
	Delay_50us(6);		//RTC使能后必须延时300us再写入时间， 否则写入时间可能无效。
	
	//设置当前时间为12:00:00
	RTC_WriteHour(12);			
	RTC_WriteMinute(0);		
	RTC_WriteSecond(0);			


	//设置闹钟时间为12:01:00
	RTAH	=	12;			
	RTAM	=	1;
	RTAS	=	0;
	
	RTMSS = 0;			//设置毫秒中断时间间隔
	INT8EN = 1;			//RTC中断使能
	
	HalfSecFlag = 0;
	AlarmEvFlag = 0;
	
	while(1)
	{
		if(HalfSecFlag)	//半秒打印当前时间
		{
			HalfSecFlag = 0;
#ifdef PRINT_EN
			uart_printf("Hour = %d,Minute = %d,Second = %d\n",(unsigned int)(RTCH&0x1F),(unsigned int)RTCM,(unsigned int)RTCS);	
#endif		
		}
		if(AlarmEvFlag)	//闹钟中断产生时打印
		{
			AlarmEvFlag = 0;
#ifdef PRINT_EN
			uart_printf("Alarm event happen!\n");	
#endif		
		}
	}
}
#endif
