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
//�Ĵ���T2CON����
#define TR2(N)   (N<<6)
#define T2R(N)   (N<<4)   	//N=0~3
#define T2IE(N)  (N<<3)
#define UCKS(N)  (N<<2)
#define T2P(N)   (N)	    //N=0~3

//�Ĵ���T2MOD����
#define TF2		 (1<<7)
#define CF2		 (1<<6)
#define RF2		 (1<<5)
#define CCFG(N)	 (N<<3)	  	//N=0~3
#define T2M(N)	 (N)		//N=0~3

/*********************************************************************************************************************/
void TIMER2_ISR (void) interrupt 5 
{
	unsigned int T2CapValue;
	if(T2MOD & TF2)		  //��ʱ��2����ж�
	{
		T2MOD = (T2MOD&0x1F) | TF2;
	}
	if(T2MOD & CF2)		  //��ʱ��2ץȡ�ж�
	{
		T2MOD = (T2MOD&0x1F) | CF2;
		T2CapValue = T2CH*256 + T2CL;		//��ȡ��ʱ��ץȡֵ

	}
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
	Uart0_Initial_Timer1(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;							//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("Timer2 Capture Mode Demo Code\n");
#endif
	   
	P36F = P36_T2CP_SETTING;	 
	T2CON = TR2(0) | T2R(0) | T2IE(1) | UCKS(0) | T2P(0); 																				                                                     
	T2MOD = CCFG(1) | T2M(2);				//����Ϊץȡģʽ���½�����Ч
	T2CON |= TR2(1);   						//��ʱ��2ʹ��
	ET2 = 1;    							//��ʱ��2�ж�ʹ��
		
	while(1)
	{
	}
}
#endif


