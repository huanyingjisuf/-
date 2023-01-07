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
	���ڽ������ݵĿ�������
**********************************************************************************************************************/
void main(void)
{	
	unsigned char rxd_dat;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//����LVD��λ��ѹΪ2.7V
#endif

#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//��ʼ��UART
#endif
	
	EA = 1;							//��ȫ���ж�

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
