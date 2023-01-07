
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
#include <intrins.h>
/*********************************************************************************************************************/
/*********************************************************************************************************************
	IDLE模式例程，并简单演示:通过INT2中断来唤醒IDLE									
**********************************************************************************************************************/

/******************************************************************************************************/
void INT2_init(void)
{
	P10F = 1;				//设置P10为输入引脚
	INDEX = 0;				//INDEX为带索引的寄存器，设置INDEX=0对应INT2
	EPCON = (1<<7) | 8;		//设置P10为INT2外部中断引脚，下降沿触发
	INT2EN = 1; 			//外部中断2中断使能
	EPIE |= 0x01;			//INT2中断使能
	EA = 1;					//总中断使能
}
void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)			//判断外部中断2中断标志
	{
		EPIF = 0x01;		//中断标志写1清0
	}
}
/******************************************************************************************************/
void Idle(void)
{
	/*
	备注：在应用时还要把IO设置为省电状态，未使用到的IO尽量不要为悬浮状态。
	*/
	Sys_Clk_Set_IRCL();		//由于进入IDLE模式不会关闭主时钟，所以进入IDLE前把主时钟设为低速时钟可显著降低功耗
// 	Sys_Clk_Set_XOSCL();	//两个低速时钟二选一
#if (SYSCLK_SRC == PLL)		//如主时钟为PLL时钟，把主时钟设为低速时钟后关闭PLL时钟
	PLLCON = 0;
#endif		
	I2CCON = 0;				//关闭I2C，否则无法关闭主时钟
	CKCON = 0;				//所有时钟关闭
	PWCON &= ~0x08;			//设置LDO进入低功率模式
	MECON |= (1<<6);		//设置 FLASH 进入深度睡眠状态
	while(IDLSTH|IDLSTL); 	//如果有中断未响应,等待中断被响应	
	PCON = (PCON&0x84) | 0x01;//进入IDLE模式
	_nop_();
	_nop_();	
	PWCON |= 0x08;			//退出IDLE模式后，把LDO设回高功率模式
		
	//系统时钟设置回高速时钟
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//系统时钟切换回PLL
#else
	Sys_Clk_Set_IRCH();							
#endif
}
/******************************************************************************************************/
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
	
	EA = 1;	

	INT2_init();
	
	while(1)
	{
	#ifdef PRINT_EN
		uart_printf("idle\n");
		Delay_ms(1);
	#endif		
		Idle();
	#ifdef PRINT_EN
		uart_printf("exit\n");
	#endif
		Delay_ms(1000);
	}
}
#endif
