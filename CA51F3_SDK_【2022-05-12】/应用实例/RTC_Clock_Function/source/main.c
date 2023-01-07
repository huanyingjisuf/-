
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
#include "include/rtc.h"
#include <intrins.h>
/*********************************************************************************************************************/

/*********************************************************************************************************************
	RTC��������
*********************************************************************************************************************/
bit HalfSecFlag;
bit AlarmEvFlag;
void RTC_ISR (void) interrupt 13 	 
{
	if(RTCIF & RTC_MF)			//�����ж�
	{
		RTCIF = RTC_MF;			
	}
	if(RTCIF & RTC_HF)			//�����ж�
	{
		RTCIF = RTC_HF;
		HalfSecFlag = 1;
	}	
	if(RTCIF & RTC_AF)			//�����ж�
	{
		RTCIF = RTC_AF;	
		AlarmEvFlag = 1;
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
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("RTC Demo Code\n");
#endif

	P32F = P32_XOSC_IN_SETTING;			//����P32Ϊ��������
	P33F = P33_XOSC_OUT_SETTING;		//����P33Ϊ��������
	CKCON |= XLCKE;									//ʹ��XSOCL
	while(!(CKCON & XLSTA));				//�ȴ�XSOCL�ȶ�
	
	RTCON = RTCE(1) | MSE(1) | HSE(1) | SCE(1) | MCE(1) | HCE(1);	//ʹ��RTC���ܣ����ð��롢�����жϿ��������幦�ܿ���(ʱ���֡���ƥ��ʹ��)
	
	Delay_50us(6);		//RTCʹ�ܺ������ʱ300us��д��ʱ�䣬 ����д��ʱ�������Ч��
	
	//���õ�ǰʱ��Ϊ12:00:00
	RTC_WriteHour(12);			
	RTC_WriteMinute(0);		
	RTC_WriteSecond(0);			


	//��������ʱ��Ϊ12:01:00
	RTAH	=	12;			
	RTAM	=	1;
	RTAS	=	0;
	
	RTMSS = 0;			//���ú����ж�ʱ����
	INT8EN = 1;			//RTC�ж�ʹ��
	
	HalfSecFlag = 0;
	AlarmEvFlag = 0;
	
	while(1)
	{
		if(HalfSecFlag)	//�����ӡ��ǰʱ��
		{
			HalfSecFlag = 0;
#ifdef PRINT_EN
			uart_printf("Hour = %d,Minute = %d,Second = %d\n",(unsigned int)(RTCH&0x1F),(unsigned int)RTCM,(unsigned int)RTCS);	
#endif		
		}
		if(AlarmEvFlag)	//�����жϲ���ʱ��ӡ
		{
			AlarmEvFlag = 0;
#ifdef PRINT_EN
			uart_printf("Alarm event happen!\n");	
#endif		
		}
	}
}
#endif
