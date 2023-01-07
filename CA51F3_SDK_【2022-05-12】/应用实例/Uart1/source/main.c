
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
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	

	Uart1_Initial(115200);	//初始化UART1

	EA = 1;													//开全局中断

	uart_printf("Uart1 Demo Code\n");

	while(1)
	{
		/*
			数组uart1_rx_buf为UART1接收buffer, uart1_rev.head和uart1_rev.tail为buffer的头尾指针，当头尾指针不相等时，表示
			buffer有接收到数据。本例程实现把UART1 RX接收到的数据通过UART1 TX发送出去。
		*/
		if(uart1_rev.tail != uart1_rev.head)		//表示有数据待取
		{
			uart1_rev.tail++;
			uart1_rev.tail %= UART1_RX_BUF_SIZE;				
			data_temp=uart1_rx_buf[uart1_rev.tail];			//从uart1_rx_buf取出数据
			
			Uart1_PutChar(data_temp);										//把接收到的数据发送出去
		}		
	}
}
#endif
