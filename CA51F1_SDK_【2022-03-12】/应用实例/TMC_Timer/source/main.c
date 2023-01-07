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
	TMC��ʱ����ʱ��ԴΪIRCL���жϵ���С��λΪ512��IRCLʱ�����ڣ��������ж�ʱ��Ϊ1~256����С��λʱ�䡣
	��STOP/IDLEģʽ�£�TMC�жϿɻ���CPU
*********************************************************************************************************************/
#define TME(N) 		(N<<7) //N=0-1 
#define TMF 		(1<<0) 
#define IHCKE 		(1<<7) 
#define ILCKE 		(1<<6) 
void INT3_ISR (void) interrupt 5 
{ 
	if(TMCON & TMF) 	//�ж�TMC�жϱ�־ 
	{ 
		TMCON |= TMF; 	//���TMC�жϱ�־ 
		
	} 
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
	uart_printf("TMC Timer Demo Code\n");
#endif
	
	CKCON |= ILCKE; 	//��IRCLʱ�� 
	TMCON = TME(1); 	//TMCʹ�� 
	TMSNU = 0; 			//����1����С��λʱ�䣨��512��IRCLʱ�����ڣ������ж� 
	INT3EN =1; 			//����TMC�ж�
	
	while(1)
	{
	}
}
#endif
