
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
	uart_printf("ADC Detect VDD Demo Code\n");
#endif


/**********��ʼ��ADC�Ĵ���������ADCʱ�ӡ�ѡ��ADC�ο���ѹ������ADC�˷š������ڲ�1.5VУ׼ֵ��***********/
 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//����ADC�ο���ѹΪ�ڲ�1.5V
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());				//�����ڲ�1.5VУ׼ֵ
/**************************************************************************************************/


/**********����ADCͨ����ʱ�ӷ�Ƶ*********************************************************************/
	ADCFGL = ACKD(7) | ADCHS(ADC_VDD);	//ѡ��ADCͨ��Ϊ1/4VDD
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
