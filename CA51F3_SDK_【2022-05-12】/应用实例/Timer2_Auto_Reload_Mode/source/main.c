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


#define INT_TIME			10000			//��ʱʱ�䣬��λΪus

#define	TH_VAL				(unsigned char)((0x10000 - (INT_TIME*(FOSC/1000))/1000)>>8)
#define	TL_VAL				(unsigned char)(0x10000 - (INT_TIME*(FOSC/1000))/1000)
/*********************************************************************************************************************/
void TIMER2_ISR (void) interrupt 5 
{
	if(T2MOD & TF2)		  //��ʱ��2����ж�,��ǰ����Ϊ10ms����
	{
		T2MOD = (T2MOD&0x1F) | TF2;
		
		
	}
	if(T2MOD & RF2)		  //��ʱ��2�����ж�
	{
		T2MOD = (T2MOD&0x1F) | RF2;
		
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
	uart_printf("Timer2 Auto Reload Mode Demo Code\n");
#endif
	   
	T2CON = TR2(0) | T2R(2) | T2IE(1) | UCKS(0) | T2P(0); 			//���ö�ʱ��Ϊ����ģʽ0																	                                                     
	T2MOD = CCFG(0) | T2M(0);				//����Ϊ��ʱ����ģʽ
	T2CH = TH_VAL;							//����T2����ֵ
	T2CL = TL_VAL;
	TH2 = TH_VAL;							//���ü�����ֵ
	TL2 = TL_VAL;
	T2CON |= TR2(1);   						//��ʱ��2ʹ��
	ET2 = 1;    							//��ʱ��2�ж�ʹ��
	
	while(1)
	{
	}
}
#endif


