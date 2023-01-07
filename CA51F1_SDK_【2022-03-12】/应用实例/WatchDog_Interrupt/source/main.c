#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"
#include "include/system_clock.h"
#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/

//WDFLG����
#define WDIF			(1<<1)
#define WDRF			(1<<0)

#define WDTS_DISABLE	(0<<6)
#define WDTS_IRCH		(1<<6)
#define WDTS_IRCL		(2<<6)

#define WDRE_reset		(1<<0)
#define WDRE_int		(0<<0)

bit WdtIntEvFlag;
void WDT_ISR (void) interrupt 6 
{
	if(WDFLG & WDIF)
	{
		WDFLG = 0xA5;
		WdtIntEvFlag = 1;
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
	uart_printf("Watch dog interrupt demo\n");
#endif
	

	/***************************���Ź���ֵ���ü��㹫ʽ����****************************
���Ź�����ʱ�� = (WDVTH * 800H+7FFH) * clock cycle
*********************************************************************************/

//���Ź�ʱ��ԴΪIRCH(�ڲ�����ʱ��)	
	WDCON = WDTS_IRCH | WDRE_int;   	//���ÿ��Ź�ʱ��ԴΪIRCH��ģʽΪ�ж�ģʽ
	WDVTHH = 0x1e;						//���Ź��ж���ֵ�߰�λ���� ��ǰֵΪ1s
	WDVTHL = 0x84;						//���Ź��ж���ֵ�Ͱ�λ����


//���Ź�ʱ��ԴΪIRCL
// 	CKCON |= ILCKE;						//ʹ��IRCL
// 	WDCON = WDTS_IRCL | WDRE_int;   	//���ÿ��Ź�ʱ��ԴΪILCKE��ģʽΪ�ж�ģʽ
// 	WDVTHH = 0;							//���Ź��ж���ֵ�߰�λ���� ��ǰֵΪ1s	
// 	WDVTHL = 0x0f;						//���Ź��ж���ֵ�Ͱ�λ����
	
	INT4EN = 1; 						//�������Ź��ж�
	WDFLG = 0xA5;						//ι��
	while(1)
	{
		if(WdtIntEvFlag)				//���Ź��жϷ���
		{
			WdtIntEvFlag = 0;
		#ifdef PRINT_EN
			uart_printf("Watch dog interrupt happen\n");	
		#endif
		}		
	}
}
#endif
