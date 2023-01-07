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

#define INT_TIME			10000	//��ʱʱ�䣬��λΪus

#define	TH_VAL				(unsigned char)((0x2000 - (INT_TIME*(FOSC/1000))/12000)>>5)
#define	TL_VAL				(unsigned char)(0x2000 - (INT_TIME*(FOSC/1000))/12000)&0x1F

void TIMER1_ISR (void) interrupt 3 	//ÿ10ms�ж�һ��
{
	TH1 = TH_VAL;
	TL1 = TL_VAL;
	
}
void main(void)
{	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE1;					//����LVD��λ��ѹΪ2V
#endif
	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;							//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("Timer1 Mode0 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xCF)|0x00; 		//ģʽѡ��: ��ʱ��1��ģʽ1��
	TH1 = TH_VAL;    				//��8λװ��ֵ
	TL1 = TL_VAL;    				//��8λװ��ֵ
	
	TR1 = 1;       					//��ʱ��1ʹ��  
	ET1 = 1;       					//��ʱ��1�ж�ʹ��
//	PT1 = 1;       					//���ö�ʱ��1�ж����ȼ�Ϊ�����ȼ�
		
	while(1)
	{

	}
}
#endif


