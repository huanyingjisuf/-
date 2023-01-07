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
	ADC0~ADC5��������
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


//	P31F = P31_ADC0_SETTING;
 	P35F = P35_ADC1_SETTING;
//	P32F = P32_ADC2_SETTING;
//	P34F = P34_ADC3_SETTING;
//	P01F = P01_ADC4_SETTING;
//	P30F = P30_ADC5_SETTING;

/**********��ʼ��ADC�Ĵ���������ADCʱ�ӡ�ѡ��ADC�ο���ѹ��*****************************************/
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//����ADC�ο���ѹΪ�ڲ�1.5V
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//����ADC�ο���ѹΪVDD
/**************************************************************************************************/


/**********����ADCͨ����У׼ʹ�ܡ�ADCͨ��*******************************************************************/								
//	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH0);	//ѡ��ADC0ͨ��
 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH1);	//ѡ��ADC1ͨ��
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH2);	//ѡ��ADC2ͨ��
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH2);	//ѡ��ADC3ͨ��
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH4);	//ѡ��ADC4ͨ��
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH5);	//ѡ��ADC5ͨ��
/**************************************************************************************************/


	while(1)
	{
		unsigned int AD_Value;
		ADCON |= AST(1);									//����ADCת��
		while(!(ADCON & ADIF));								//�ȴ�ADCת�����
		ADCON |= ADIF;										//���ADC�жϱ�־
		AD_Value = ADCDH*256 + ADCDL;						//��ȡADֵ
		AD_Value >>= 4;		
	#ifdef PRINT_EN
		uart_printf ("ADC Value = 0x%x\n",AD_Value);		//��ӡADֵ
	#endif
		Delay_ms(100);
	}
}
#endif
