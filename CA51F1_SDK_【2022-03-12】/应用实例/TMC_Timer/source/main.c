#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"

#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************
	TMC定时器的时钟源为IRCL，中断的最小单位为512个IRCL时钟周期，可配置中断时间为1~256个最小单位时间。
	在STOP/IDLE模式下，TMC中断可唤醒CPU
*********************************************************************************************************************/
#define TME(N) 		(N<<7) //N=0-1 
#define TMF 		(1<<0) 
#define IHCKE 		(1<<7) 
#define ILCKE 		(1<<6) 
void INT3_ISR (void) interrupt 5 
{ 
	if(TMCON & TMF) 	//判断TMC中断标志 
	{ 
		TMCON |= TMF; 	//清除TMC中断标志 
		
	} 
}
void main(void)
{	
#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//初始化UART
#endif
	
	EA = 1;							//开全局中断

#ifdef PRINT_EN
	uart_printf("TMC Timer Demo Code\n");
#endif
	
	CKCON |= ILCKE; 	//打开IRCL时钟 
	TMCON = TME(1); 	//TMC使能 
	TMSNU = 0; 			//设置1个最小单位时间（即512个IRCL时钟周期）产生中断 
	INT3EN =1; 			//开启TMC中断
	
	while(1)
	{
	}
}
#endif
