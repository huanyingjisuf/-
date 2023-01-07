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

#define INT_TIME			100			//��ʱʱ�䣬��λΪus

#define	T_VAL				(unsigned char)(0x100 - (INT_TIME*(FOSC/1000))/12000)

void TIMER0_ISR (void) interrupt 1 		//ÿ100us�ж�һ��
{
	
}
void main(void)
{	
#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//��ʼ��UART
#endif
	
	EA = 1;							//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("Timer0 Mode2 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xFC)|0x02; 		//ģʽѡ��: ��ʱ��0��ģʽ2��
	TH0 = T_VAL;    				//װ������ֵ
	TL0 = T_VAL;    				//װ�ؼ�����ֵ
	
	TR0 = 1;       					//��ʱ��0ʹ��  
	ET0 = 1;       					//��ʱ��0�ж�ʹ��

	while(1)
	{
	}
}
#endif
