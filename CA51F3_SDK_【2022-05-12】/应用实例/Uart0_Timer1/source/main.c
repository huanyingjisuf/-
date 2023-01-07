
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

void main(void)
{
	unsigned char data_temp;
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);		//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
	Uart0_Initial_Timer1(19200);		//Timer1作为UART0波特率发生器，注意：当系统时钟为3.6864M时，波特率最高为19200
	
	EA = 1;								//开全局中断

	uart_printf("Uart0 Demo Code!\n");

	while(1)
	{
		/*
			数组uart0_rx_buf为UART0接收buffer, uart0_rev.head和uart0_rev.tail为buffer的头尾指针，当头尾指针不相等时，表示
			buffer有接收到数据。本例程实现把UART0 RX接收到的数据通过UART0 TX发送出去。
		*/
		if(uart0_rev.tail != uart0_rev.head)				//表示有数据待取
		{
			uart0_rev.tail++;
			uart0_rev.tail %= UART0_RX_BUF_SIZE;				
			data_temp=uart0_rx_buf[uart0_rev.tail];			//从uart0_rx_buf取出数据
			
			Uart0_PutChar(data_temp);						//把接收到的数据发送出去
		}		
	}
}
#endif
