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
#define INT_TIME			100			//��ʱʱ�䣬��λΪus

#define	T_VAL				(unsigned char)(0x100 - (INT_TIME*(FOSC/1000))/12000)

void TIMER1_ISR (void) interrupt 3 		//ÿ100us�ж�һ��
{
	
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
	uart_printf("Timer1 Mode2 Demo Code\n");
#endif
	

	TMOD = (TMOD&0xCF)|0x20;//ģʽѡ��: ��ʱ��1��ģʽ2��
	TH1 = T_VAL;    		//װ������ֵ
	TL1 = T_VAL;    		//װ�ؼ�����ֵ
	TR1 = 1;       			//��ʱ��1ʹ��  
	ET1 = 1;       			//��ʱ��1�ж�ʹ��
//	PT1 = 1;       			//���ö�ʱ��1�ж����ȼ�Ϊ�����ȼ�
	
	while(1)
	{

	}
}



#endif
