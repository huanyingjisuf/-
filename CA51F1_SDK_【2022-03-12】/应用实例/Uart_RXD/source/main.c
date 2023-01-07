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
	串口接收数据的控制例程
**********************************************************************************************************************/
void main(void)
{	
	unsigned char rxd_dat;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//设置LVD复位电压为2.7V
#endif

#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//初始化UART
#endif
	
	EA = 1;							//开全局中断

	while(1)
	{
#ifdef UART_EN
		if(uart_rev.head!=uart_rev.tail)
		{
			if(uart_rev.tail==UART_RX_BUF_SIZE-1)
			{
				uart_rev.tail=0;
			}
			else
			{
				uart_rev.tail++;
			}		
			rxd_dat = uart_rx_buf[uart_rev.tail];
						
			Uart_PutChar(rxd_dat);
		}
#endif				
	}
}
#endif
