#ifndef _UART_C_
#define _UART_C_
#include "include/ca51f_config.h"
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"

#include "include/uart.h"
#include <intrins.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>
/*********************************************************************************************************************/
/*********************************************************************************************************************/
void Uart0_Initial_Timer2(unsigned long int baudrate)
{
	unsigned int value_temp;

	P31F = P31_UART0_RX_SETTING;
	P30F = P30_UART0_TX_SETTING;
	
	uart0_send.head=0;
	uart0_send.tail=0;
	uart0_rev.head=0;
	uart0_rev.tail=0;
	uart0_tx_flag=0;

/************************************************************************************************************************/
//TIMER2作为UART0的波特率发生器
	value_temp = 0x10000 - FOSC/(baudrate*32);
	T2CON = 	0x24;
	T2CH  = 	(unsigned char)(value_temp>>8);
	T2CL  = 	(unsigned char)(value_temp);
	TH2   = 	(unsigned char)(value_temp>>8);
	TL2   = 	(unsigned char)(value_temp);;	
	TR2   = 	1;
/************************************************************************************************************************/	

	S0CON = 0x50;	 
	ES0 = 1;
}
void Uart0_PutChar(unsigned char bdat)
{
	unsigned char free_space;
	unsigned char tail_tmp;
	while(1)
	{				
		tail_tmp = uart0_send.tail;	
		if(uart0_send.head < tail_tmp)
		{
			free_space = tail_tmp - uart0_send.head;
		}
		else
		{
			free_space = UART0_TX_BUF_SIZE + tail_tmp - uart0_send.head;
		}		
		if(free_space > 1)
		{
			ES0 = 0; 
			uart0_send.head++;
			uart0_send.head %= UART0_TX_BUF_SIZE;
			uart0_tx_buf[uart0_send.head] = bdat;			
			if(!uart0_tx_flag)
			{
				ES0 = 1;				
				uart0_send.tail++;
				uart0_send.tail %= UART0_TX_BUF_SIZE;		
				S0BUF=uart0_tx_buf[uart0_send.tail];				
				uart0_tx_flag = 1;		
			}
			else
			{
				ES0 = 1;	
			}			
			break;
		}
	}
}
void UART0_ISR (void) interrupt 4
{	
	if(RI0)
	{
		RI0 = 0;
		uart0_rev.head++;
		uart0_rev.head %= UART0_RX_BUF_SIZE;
		uart0_rx_buf[uart0_rev.head]=S0BUF;
	}
	if(TI0)
	{	
		TI0 = 0;		
		if(uart0_send.head!=uart0_send.tail)
		{
			uart0_send.tail++;
			uart0_send.tail %= UART0_TX_BUF_SIZE;
			S0BUF=uart0_tx_buf[uart0_send.tail];				
		}
		else
		{
			uart0_tx_flag=0;
		}	
	}
}

void UartPutStr(char *str)
{
	while(*str)
	{	
 		Uart0_PutChar(*str++);
	}
}
void uart_printf(char *fmt,...) 
{
    va_list ap;
    char xdata string[256];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    UartPutStr(string);
    va_end(ap);
}
/*********************************************************************************************************************/
#endif