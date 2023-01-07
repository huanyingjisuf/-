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
	ADC0~ADC5控制例程
*********************************************************************************************************************/
void main(void)
{	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//设置LVD复位电压为2.2V
#endif

#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//初始化UART
#endif
	
	EA = 1;							//开全局中断


//	P31F = P31_ADC0_SETTING;
 	P35F = P35_ADC1_SETTING;
//	P32F = P32_ADC2_SETTING;
//	P34F = P34_ADC3_SETTING;
//	P01F = P01_ADC4_SETTING;
//	P30F = P30_ADC5_SETTING;

/**********初始化ADC寄存器（设置ADC时钟、选择ADC参考电压）*****************************************/
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//设置ADC参考电压为内部1.5V
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//设置ADC参考电压为VDD
/**************************************************************************************************/


/**********设置ADC通道、校准使能、ADC通道*******************************************************************/								
//	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH0);	//选择ADC0通道
 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH1);	//选择ADC1通道
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH2);	//选择ADC2通道
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH2);	//选择ADC3通道
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH4);	//选择ADC4通道
// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH5);	//选择ADC5通道
/**************************************************************************************************/


	while(1)
	{
		unsigned int AD_Value;
		ADCON |= AST(1);									//启动ADC转换
		while(!(ADCON & ADIF));								//等待ADC转换完成
		ADCON |= ADIF;										//清除ADC中断标志
		AD_Value = ADCDH*256 + ADCDL;						//读取AD值
		AD_Value >>= 4;		
	#ifdef PRINT_EN
		uart_printf ("ADC Value = 0x%x\n",AD_Value);		//打印AD值
	#endif
		Delay_ms(100);
	}
}
#endif
