
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
/*********************************************************************************************************************
	IDLEģʽ���̣�������ʾ:ͨ��INT2�ж�������IDLE									
**********************************************************************************************************************/

/******************************************************************************************************/
void INT2_init(void)
{
	P10F = 1;				//����P10Ϊ��������
	INDEX = 0;				//INDEXΪ�������ļĴ���������INDEX=0��ӦINT2
	EPCON = (1<<7) | 8;		//����P10ΪINT2�ⲿ�ж����ţ��½��ش���
	INT2EN = 1; 			//�ⲿ�ж�2�ж�ʹ��
	EPIE |= 0x01;			//INT2�ж�ʹ��
	EA = 1;					//���ж�ʹ��
}
void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)			//�ж��ⲿ�ж�2�жϱ�־
	{
		EPIF = 0x01;		//�жϱ�־д1��0
	}
}
/******************************************************************************************************/
void Idle(void)
{
	/*
	��ע����Ӧ��ʱ��Ҫ��IO����Ϊʡ��״̬��δʹ�õ���IO������ҪΪ����״̬��
	*/
	Sys_Clk_Set_IRCL();		//���ڽ���IDLEģʽ����ر���ʱ�ӣ����Խ���IDLEǰ����ʱ����Ϊ����ʱ�ӿ��������͹���
// 	Sys_Clk_Set_XOSCL();	//��������ʱ�Ӷ�ѡһ
#if (SYSCLK_SRC == PLL)		//����ʱ��ΪPLLʱ�ӣ�����ʱ����Ϊ����ʱ�Ӻ�ر�PLLʱ��
	PLLCON = 0;
#endif		
	I2CCON = 0;				//�ر�I2C�������޷��ر���ʱ��
	CKCON = 0;				//����ʱ�ӹر�
	PWCON &= ~0x08;			//����LDO����͹���ģʽ
	MECON |= (1<<6);		//���� FLASH �������˯��״̬
	while(IDLSTH|IDLSTL); 	//������ж�δ��Ӧ,�ȴ��жϱ���Ӧ	
	PCON = (PCON&0x84) | 0x01;//����IDLEģʽ
	_nop_();
	_nop_();	
	PWCON |= 0x08;			//�˳�IDLEģʽ�󣬰�LDO��ظ߹���ģʽ
		
	//ϵͳʱ�����ûظ���ʱ��
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//ϵͳʱ���л���PLL
#else
	Sys_Clk_Set_IRCH();							
#endif
}
/******************************************************************************************************/
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
	
	EA = 1;	

	INT2_init();
	
	while(1)
	{
	#ifdef PRINT_EN
		uart_printf("idle\n");
		Delay_ms(1);
	#endif		
		Idle();
	#ifdef PRINT_EN
		uart_printf("exit\n");
	#endif
		Delay_ms(1000);
	}
}
#endif
