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

#define INT_TIME			1000			//��ʱʱ�䣬��λΪus

#define	TH_VAL				(unsigned char)((0x2000 - (INT_TIME*(FOSC/1000))/12000)>>5)
#define	TL_VAL				(unsigned char)(0x2000 - (INT_TIME*(FOSC/1000))/12000)&0x1F

void TIMER0_ISR (void) interrupt 1			//ÿ1ms�����ж�
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;
	
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
	uart_printf("Timer0 Mode0 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xFC)|0x00; 		//ģʽѡ��: ��ʱ��0��ģʽ0��
	TH0 = TH_VAL;    				//��8λװ��ֵ
	TL0 = TL_VAL;    				//��8λװ��ֵ
	
	TR0 = 1;       					//��ʱ��0ʹ��  
	ET0 = 1;       					//��ʱ��0�ж�ʹ��

	while(1)
	{
	}
}
#endif
