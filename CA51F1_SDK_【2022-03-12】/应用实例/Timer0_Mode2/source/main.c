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

#define INT_TIME			100			//定时时间，单位为us

#define	T_VAL				(unsigned char)(0x100 - (INT_TIME*(FOSC/1000))/12000)

void TIMER0_ISR (void) interrupt 1 		//每100us中断一次
{
	
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
	uart_printf("Timer0 Mode2 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xFC)|0x02; 		//模式选择: 定时器0，模式2。
	TH0 = T_VAL;    				//装载重载值
	TL0 = T_VAL;    				//装载计数初值
	
	TR0 = 1;       					//定时器0使能  
	ET0 = 1;       					//定时器0中断使能

	while(1)
	{
	}
}
#endif
