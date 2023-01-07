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
void Uart1_Initial(unsigned long int baudrate)
{
	unsigned int value_temp;

	uart1_send.head=0;
	uart1_send.tail=0;
	uart1_rev.head=0;
	uart1_rev.tail=0;
	uart1_tx_flag=0;

	value_temp = 0x400 - FOSC/(baudrate*32);


	P12F = P12_UART1_RX_SETTING;
	P11F = P11_UART1_TX_SETTING;


	S1RELH = (unsigned char)(value_temp>>8);
	S1RELL = (unsigned char)(value_temp);
	
	S1CON = 0xD0;
	ES1 =	1;	
}
void Uart1_PutChar(unsigned char bdat)
{
	unsigned char free_space;
	unsigned char tail_tmp;
	while(1)
	{		
		tail_tmp = uart1_send.tail;
		if(uart1_send.head < tail_tmp)
		{
			free_space = tail_tmp - uart1_send.head;
		}
		else
		{
			free_space = UART1_TX_BUF_SIZE + tail_tmp - uart1_send.head;
		}		
		if(free_space > 1)
		{
			ES1 = 0; 
			uart1_send.head++;
			uart1_send.head %= UART1_TX_BUF_SIZE;
			uart1_tx_buf[uart1_send.head] = bdat;
			if(!uart1_tx_flag)
			{
				ES1 = 1;
				uart1_send.tail++;
				uart1_send.tail %= UART1_TX_BUF_SIZE;		
				S1BUF = uart1_tx_buf[uart1_send.tail];				
				uart1_tx_flag = 1;		
			}
			else
			{
				ES1 = 1;	
			}			
			break;
		}
	}
}
void UART1_ISR (void) interrupt 6	
{
	if(S1CON & 0x01)
	{
		S1CON = (S1CON&0xFC)|0x01;			 
		uart1_rev.head++;
	   	uart1_rev.head %= UART1_RX_BUF_SIZE;
		uart1_rx_buf[uart1_rev.head]=S1BUF;
	}
	if(S1CON & 0x02)
	{
		S1CON = (S1CON&0xFC)|0x02;	
		if(uart1_send.head!=uart1_send.tail)
		{
			uart1_send.tail++;
			uart1_send.tail %= UART1_TX_BUF_SIZE;
			S1BUF=uart1_tx_buf[uart1_send.tail];				
		}
		else
		{
			uart1_tx_flag=0;
		}		
	}
}

void UartPutStr(char *str)
{
	while(*str)
	{	
 		Uart1_PutChar(*str++);
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