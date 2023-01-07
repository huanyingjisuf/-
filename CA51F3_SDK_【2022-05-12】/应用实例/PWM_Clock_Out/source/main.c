
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/pwm.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************
	����������PWM0ֱ������ڲ�ʱ��
*********************************************************************************************************************/
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

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("PWM Clock Out Demo Code\n");
#endif

	
	CKCON |= IHCKE;					//��IRCHʱ��
// 	CKCON |= ILCKE;				//��IRCLʱ��
// 	CKCON |= TFCKE;				//��TFRCʱ��

// 	GPIO_Init(P32F,P32_XOSC_IN_SETTING);
// 	GPIO_Init(P33F,P33_XOSC_OUT_SETTING);
// 	CKCON |= XLCKE;
// 	while(!(CKCON & XLSTA));
// 	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;		//��XSOCLʱ��


// 	PLLCON = PLLON(1) | MULFT(7);
// 	while(!(PLLCON & PLSTA));
// 	CKSEL = (CKSEL&0xF8) | CKSEL_PLL;			//��PLLʱ��

	
	P15F = P15_PWM0_SETTING;								//����P15ΪPWM���Ź���

	INDEX = PWM_CH0;												//����INDEXֵ��ӦPWM0
	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IH ;		  //����PWMʱ��ԴΪIRCH  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_IL ;		  //����PWMʱ��ԴΪIRCL
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_XL ;		  //����PWMʱ��ԴΪXOSCL  
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_TF ;		  //����PWMʱ��ԴΪTFRC 
// 	PWMCON = TIE(0) | ZIE(0) | PIE(0) | NIE(0) | MS(0) | CKS_PLL ;		//����PWMʱ��ԴΪPLL  
	PWMCFG = TOG(0) | 0;																								
	
	//PWMDIV��PWMDUT������Ϊ0��ֱ�����ʱ��
	PWMDIVH	= 0;			
	PWMDIVL	= 0;
	PWMDUTH	= 0;
	PWMDUTL	= 0;

 	PWMUPD = (1<<PWM_CH0);									//PWMDIV��PWMDUT����ʹ��
	while(PWMUPD);													//�ȴ��������
 	PWMEN = (1<<PWM_CH0);										//PWM0ʹ��
	
	while(1)
	{
	}
}
#endif
