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

/*********************************************************************************************************************
	LVD�ж�����

	˵������LVD�жϲ��������VDD�����������趨�ĵ�ѹ��LVD�ж�Ҳ���ظ��ز�����
*********************************************************************************************************************/
#define LVDE(N)			(N<<7)	  	//N=0~1
#define LVDS_reset		(1<<6)
#define LVDS_int		(0<<6)
#define LVDF			(1<<5)

#define LVDTH_2p2V		0
#define LVDTH_2p7V		1
#define LVDTH_3p7V		2
#define LVDTH_4p2V		3

void LVD_ISR(void) interrupt 6		//LVD�жϷ������
{
	if(LVDCON & LVDF)
	{
		LVDCON |= LVDF;			    //���LVD�жϱ�־

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
	uart_printf("LVD Interrupt Demo Code\n");
#endif
	
	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_2p2V;	//����LVDʹ��,����LVDΪ�ж�ģʽ,����ѹΪ2.2V
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_2p7V;	//����LVDʹ��,����LVDΪ�ж�ģʽ,����ѹΪ2.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_3p7V;	//����LVDʹ��,����LVDΪ�ж�ģʽ,����ѹΪ3.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_4p2V;	//����LVDʹ��,����LVDΪ�ж�ģʽ,����ѹΪ4.2V

	INT4EN = 1; 					//INT4 �ж�ʹ��

	while(1)
	{
	}
}
#endif
