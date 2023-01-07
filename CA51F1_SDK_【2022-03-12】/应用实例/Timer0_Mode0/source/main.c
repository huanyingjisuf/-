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
/*********************************************************************************************************************/

#define INT_TIME			1000			//定时时间，单位为us

#define	TH_VAL				(unsigned char)((0x2000 - (INT_TIME*(FOSC/1000))/12000)>>5)
#define	TL_VAL				(unsigned char)(0x2000 - (INT_TIME*(FOSC/1000))/12000)&0x1F

void TIMER0_ISR (void) interrupt 1			//每1ms产生中断
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;
	
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
	uart_printf("Timer0 Mode0 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xFC)|0x00; 		//模式选择: 定时器0，模式0。
	TH0 = TH_VAL;    				//高8位装初值
	TL0 = TL_VAL;    				//低8位装初值
	
	TR0 = 1;       					//定时器0使能  
	ET0 = 1;       					//定时器0中断使能

	while(1)
	{
	}
}
#endif
