
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
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	

	Uart1_Initial(115200);	//��ʼ��UART1

	EA = 1;													//��ȫ���ж�

	uart_printf("Uart1 Demo Code\n");

	while(1)
	{
		/*
			����uart1_rx_bufΪUART1����buffer, uart1_rev.head��uart1_rev.tailΪbuffer��ͷβָ�룬��ͷβָ�벻���ʱ����ʾ
			buffer�н��յ����ݡ�������ʵ�ְ�UART1 RX���յ�������ͨ��UART1 TX���ͳ�ȥ��
		*/
		if(uart1_rev.tail != uart1_rev.head)		//��ʾ�����ݴ�ȡ
		{
			uart1_rev.tail++;
			uart1_rev.tail %= UART1_RX_BUF_SIZE;				
			data_temp=uart1_rx_buf[uart1_rev.tail];			//��uart1_rx_bufȡ������
			
			Uart1_PutChar(data_temp);										//�ѽ��յ������ݷ��ͳ�ȥ
		}		
	}
}
#endif
