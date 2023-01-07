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

void TIMER1_ISR (void) interrupt 3 		 //ÿ1ms�ж�һ��
{
	TH1 = TH_VAL;
	TL1 = TL_VAL;

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
	uart_printf("Timer1 Mode0 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xCF)|0x00; 		//ģʽѡ��: ��ʱ��1��ģʽ0
	TH1 = TH_VAL;    				//��8λװ��ֵ
	TL1 = TL_VAL;    				//��8λװ��ֵ
	
	TR1 = 1;       					//��ʱ��1ʹ��  
	ET1 = 1;       					//��ʱ��1�ж�ʹ��
	
	while(1)
	{
	}
}
#endif
