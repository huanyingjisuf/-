
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/adc.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
unsigned char read_inner_trim(void)				
{
	unsigned char value;
	FSCMD = 0x80;	
	PTSH  = 0x00;				
	PTSL  = 0x24;      
	FSCMD = 0x81;						
	value = FSDAT;
	FSCMD = 0;
	return (value&0x3F);
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
	uart_printf("ADC Simple Demo Code\n");
#endif

	

/**********����ADC���Ź���*************************************************************/
	P10F = P10_ADC0_SETTING;	//����P10ΪADC���Ź���
// 	P11F = P11_ADC1_SETTING;	//����P11ΪADC���Ź���
// 	P12F = P12_ADC2_SETTING;	//����P12ΪADC���Ź���
// 	P13F = P13_ADC3_SETTING;	//����P13ΪADC���Ź���
// 	P14F = P14_ADC4_SETTING;	//����P14ΪADC���Ź���
// 	P15F = P15_ADC5_SETTING;	//����P15ΪADC���Ź���
// 	P16F = P16_ADC6_SETTING;	//����P16ΪADC���Ź���
// 	P17F = P17_ADC7_SETTING;	//����P17ΪADC���Ź���
	
// 		P10F = P10_ADC_VREF_SETTING;	//���ADC�ο���ѹѡ��Ϊ�ⲿ�ο���ѹ����Ҫ����P10Ϊ�ⲿ�ο���ѹ���ţ�����ADC0ͨ������ʹ�á�
/***************************************************************************************/
	

/**********��ʼ��ADC�Ĵ���������ADCʱ�ӡ�ѡ��ADC�ο���ѹ������ADC�˷š������ڲ�1.5VУ׼ֵ��***********/
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//����ADC�ο���ѹΪ�ڲ�1.5V
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);			//����ADC�ο���ѹΪVDD
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_Outer);		//����ADC�ο���ѹΪ�ⲿ�ο���ѹ
	
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());				//�����ڲ�1.5VУ׼ֵ
/**************************************************************************************************/


/**********����ADCͨ����ʱ�ӷ�Ƶ*********************************************************************/
	ADCFGL = ACKD(7) | ADCHS(ADC_CH0);	//ѡ��ADC0ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH1);	//ѡ��ADC1ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH2);	//ѡ��ADC2ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH3);	//ѡ��ADC3ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH4);	//ѡ��ADC4ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH5);	//ѡ��ADC5ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH6);	//ѡ��ADC6ͨ��
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH7);	//ѡ��ADC7ͨ��
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
