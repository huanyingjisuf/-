
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
	STOPģʽ���̣�������ʾ:ͨ��INT2�ж�������STOP								
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
void Stop(void)
{
	bit IE_EA;
	/*
	��ע������STOPģʽǰӦ�ر���Ӧ�������·����δʹ�õ���IO������ҪΪ����״̬(������Ϊ����̬+����)�����£�
	*/
#if 1
	GPIO_Init(P00F,HIGH_Z|PU_EN);
	GPIO_Init(P01F,HIGH_Z|PU_EN);
	GPIO_Init(P02F,HIGH_Z|PU_EN);
	GPIO_Init(P03F,HIGH_Z|PU_EN);
	GPIO_Init(P04F,HIGH_Z|PU_EN);
	GPIO_Init(P05F,HIGH_Z|PU_EN);
	GPIO_Init(P06F,HIGH_Z|PU_EN);
	GPIO_Init(P07F,HIGH_Z|PU_EN);

//	GPIO_Init(P10F,HIGH_Z|PU_EN);
	GPIO_Init(P11F,HIGH_Z|PU_EN);
	GPIO_Init(P12F,HIGH_Z|PU_EN);
	GPIO_Init(P13F,HIGH_Z|PU_EN);
	GPIO_Init(P14F,HIGH_Z|PU_EN);
	GPIO_Init(P15F,HIGH_Z|PU_EN);
	GPIO_Init(P16F,HIGH_Z|PU_EN);
	GPIO_Init(P17F,HIGH_Z|PU_EN);

	GPIO_Init(P20F,HIGH_Z|PU_EN);
	GPIO_Init(P21F,HIGH_Z|PU_EN);

	GPIO_Init(P30F,HIGH_Z|PU_EN);
	GPIO_Init(P31F,HIGH_Z|PU_EN);
	GPIO_Init(P32F,HIGH_Z|PU_EN);
	GPIO_Init(P33F,HIGH_Z|PU_EN);
	GPIO_Init(P34F,HIGH_Z|PU_EN);
	GPIO_Init(P35F,HIGH_Z|PU_EN);
	GPIO_Init(P36F,HIGH_Z|PU_EN);
	GPIO_Init(P37F,HIGH_Z|PU_EN);
#endif

#if (SYSCLK_SRC == PLL)	
	Sys_Clk_Set_IRCH();		//���ϵͳʱ��ΪPLL���ڽ���STOP֮ǰҪ��ϵͳʱ���л���IRCH
	PLLCON = 0;				//�ر�PLL
#endif
	I2CCON = 0;				//�ر�I2C�������޷��ر���ʱ��
	CKCON = 0;				//����ʱ�ӹر�
	PWCON &= ~0x08;			//����LDO����͹���ģʽ	
	MECON |= (1<<6); 		//����FLASH�������˯��״̬
	while(STPSTH|STPSTL);	//������ж�δ��Ӧ,�ȴ��жϱ���Ӧ
	IE_EA = EA; 			//����ȫ���ж�ʹ��λ״̬
	EA = 0;
	PCON = (PCON&0x84) | 0x02;//����STOPģʽ
	_nop_();
	_nop_();
	_nop_();
	EA = IE_EA; 			//�ָ�ԭȫ���жϿ���״̬	
	PWCON |= 0x08;			//�˳�STOPģʽ�󣬰�LDO��ظ߹���ģʽ
	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//ϵͳʱ���л���PLL
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

#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);	//��ʼ��UART2
#endif
	
	EA = 1;	

	INT2_init();
	
	while(1)
	{
	#ifdef PRINT_EN
		uart_printf("stop\n");
		Delay_ms(1);
	#endif		
		Stop();
	#ifdef PRINT_EN
		uart_printf("exit\n");
	#endif
		Delay_ms(1000);
	}
}
/**********************************************************************************************************************/
#endif

