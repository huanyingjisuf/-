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
#include "include/adc.h"
#include <intrins.h>
/*********************************************************************************************************************
	ADC���VDD����
*********************************************************************************************************************/
void main(void)
{	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//����LVD��λ��ѹΪ2.2V
#endif

#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//��ʼ��UART
#endif
	
	EA = 1;							//��ȫ���ж�


/**********��ʼ��ADC�Ĵ���������ADCʱ�ӡ�ѡ��ADC�ο���ѹ��*****************************************/
 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//����ADC�ο���ѹΪ�ڲ�1.5V
/**************************************************************************************************/


/**********����ADCͨ����У׼ʹ�ܡ�ADCͨ��*******************************************************************/								
	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_VDD);	//ѡ��ADCͨ��Ϊ1/4VDD
/**************************************************************************************************/


	while(1)
	{
		unsigned int AD_Value;
		double VDD_Voltage;
		ADCON |= AST(1);									//����ADCת��
		while(!(ADCON & ADIF));								//�ȴ�ADCת�����
		ADCON |= ADIF;										//���ADC�жϱ�־
		AD_Value = ADCDH*256 + ADCDL;						//��ȡADֵ
		AD_Value >>= 4;		
		
		VDD_Voltage = ((double)AD_Value*1.5*4)/4095;		//����ADCֵ����Ϊ��ѹֵ��ע�⣺����ADC������1/4VDD�����Ի���ΪVDD��ѹʱADCֵҪ����4
	#ifdef PRINT_EN
		uart_printf ("VDD Voltage = %e\n",VDD_Voltage);		//��ӡVDD��ѹֵ	
	#endif
		Delay_ms(100);
	}
}
#endif
