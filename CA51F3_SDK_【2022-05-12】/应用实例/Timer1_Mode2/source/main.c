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
#define INT_TIME			100			//定时时间，单位为us

#define	T_VAL				(unsigned char)(0x100 - (INT_TIME*(FOSC/1000))/12000)

void TIMER1_ISR (void) interrupt 3 		//每100us中断一次
{
	
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
	uart_printf("Timer1 Mode2 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xCF)|0x20;//模式选择: 定时器1，模式2。
	TH1 = T_VAL;    		//装载重载值
	TL1 = T_VAL;    		//装载计数初值
	TR1 = 1;       			//定时器1使能  
	ET1 = 1;       			//定时器1中断使能
//	PT1 = 1;       			//设置定时器1中断优先级为高优先级
	
	while(1)
	{

	}
}



#endif
