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
#define INT_TIME			10000		//定时时间，单位为us

#define	TH_VAL				(unsigned char)((0x10000 - (INT_TIME*(FOSC/1000))/12000)>>8)
#define	TL_VAL				(unsigned char)(0x10000 - (INT_TIME*(FOSC/1000))/12000)

void TIMER0_ISR (void) interrupt 1 		//每10ms产生中断
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;
	
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

	EA = 1;							//开全局中断

#ifdef PRINT_EN
	uart_printf("Timer0 Mode1 Demo Code\n");
#endif

	TMOD = (TMOD&0xFC)|0x01; 		//模式选择: 定时器0，模式1。
	TH0 = TH_VAL;    				//高8位装初值
	TL0 = TL_VAL;    				//低8位装初值
	
	TR0 = 1;       					//定时器0使能  
	ET0 = 1;       					//定时器0中断使能
//	PT0 = 1;       					//设置定时器0中断优先级为高优先级
	
	while(1)
	{

	}
}
#endif
