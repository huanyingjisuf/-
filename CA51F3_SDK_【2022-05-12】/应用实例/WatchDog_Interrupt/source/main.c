
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/wdt.h"
#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
bit WdtIntEvFlag;
void WDT_ISR (void) interrupt 12 
{
	if(WDFLG & WDIF)
	{
		WDFLG = 0xA5;;
		WdtIntEvFlag = 1;
	}	
}
void main(void)
{	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("Watch dog interrpt mode Demo code!\n");
#endif

/***************************���Ź���ֵ���ü��㹫ʽ����****************************
���Ź�����ʱ�� = (WDVTH * 800H+7FFH) * clock cycle
�����Ź�ʱ��Ϊ3.6864Mʱ,ʱ�串�Ƿ�ΧΪ0.56ms--36s
*********************************************************************************/

//���Ź�ʱ��ԴΪIRCH(�ڲ�����ʱ��)	
	WDCON  = WDTS(WDTS_IRCH) | WDRE(WDRE_int);   	//���ÿ��Ź�ʱ��ԴΪIRCH��ģʽΪ�ж�ģʽ
	WDVTHH = 0x07;									//���Ź��ж���ֵ�߰�λ���� ��ǰֵΪ1s
	WDVTHL = 0x08;									//���Ź��ж���ֵ�Ͱ�λ����

//���Ź�ʱ��ԴΪXOSCL
// 	P32F = P32_XOSC_IN_SETTING;						//����P32Ϊ��������
// 	P33F = P33_XOSC_OUT_SETTING;					//����P33Ϊ��������
// 	CKCON |= XLCKE;									//ʹ��XSOCL
// 	while(!(CKCON & XLSTA));						//�ȴ�XSOCL�ȶ�
//	WDCON  = WDTS(WDTS_XOSCL) | WDRE(WDRE_int); 	//���ÿ��Ź�ʱ��ԴΪXOSCL��ģʽΪ�ж�ģʽ
//	WDVTHH = 0;										//���Ź��ж���ֵ�߰�λ���� ��ǰֵΪ1s
//	WDVTHL = 0x0f;									//���Ź��ж���ֵ�Ͱ�λ����


//���Ź�ʱ��ԴΪIRCL
//	CKCON |= ILCKE;									//ʹ��IRCL
//	WDCON  = WDTS(WDTS_IRCL) | WDRE(WDRE_int);   	//���ÿ��Ź�ʱ��ԴΪILCKE��ģʽΪ�ж�ģʽ
//	WDVTHH = 0;										//���Ź��ж���ֵ�߰�λ���� ��ǰֵΪ1s	
//	WDVTHL = 0x0f;									//���Ź��ж���ֵ�Ͱ�λ����

	
	INT7EN = 1; 									//�������Ź��ж�
	WDFLG = 0xA5;									//ι��
	while(1)
	{
		if(WdtIntEvFlag)							//���Ź��жϷ���
		{
			WdtIntEvFlag = 0;
#ifdef PRINT_EN
			uart_printf("Watch dog interrupt event happen!\n");	
#endif
		}		
	}
}
#endif
