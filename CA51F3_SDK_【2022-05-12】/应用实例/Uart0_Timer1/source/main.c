
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
	Sys_Clk_Set_PLL(PLL_Multiple);		//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
	Uart0_Initial_Timer1(19200);		//Timer1��ΪUART0�����ʷ�������ע�⣺��ϵͳʱ��Ϊ3.6864Mʱ�����������Ϊ19200
	
	EA = 1;								//��ȫ���ж�

	uart_printf("Uart0 Demo Code!\n");

	while(1)
	{
		/*
			����uart0_rx_bufΪUART0����buffer, uart0_rev.head��uart0_rev.tailΪbuffer��ͷβָ�룬��ͷβָ�벻���ʱ����ʾ
			buffer�н��յ����ݡ�������ʵ�ְ�UART0 RX���յ�������ͨ��UART0 TX���ͳ�ȥ��
		*/
		if(uart0_rev.tail != uart0_rev.head)				//��ʾ�����ݴ�ȡ
		{
			uart0_rev.tail++;
			uart0_rev.tail %= UART0_RX_BUF_SIZE;				
			data_temp=uart0_rx_buf[uart0_rev.tail];			//��uart0_rx_bufȡ������
			
			Uart0_PutChar(data_temp);						//�ѽ��յ������ݷ��ͳ�ȥ
		}		
	}
}
#endif
