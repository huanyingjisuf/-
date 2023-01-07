
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
	LVDCON = 0xE1;					//设置LVD复位电压为2V
#endif
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("ADC Simple Demo Code\n");
#endif

	

/**********设置ADC引脚功能*************************************************************/
	P10F = P10_ADC0_SETTING;	//设置P10为ADC引脚功能
// 	P11F = P11_ADC1_SETTING;	//设置P11为ADC引脚功能
// 	P12F = P12_ADC2_SETTING;	//设置P12为ADC引脚功能
// 	P13F = P13_ADC3_SETTING;	//设置P13为ADC引脚功能
// 	P14F = P14_ADC4_SETTING;	//设置P14为ADC引脚功能
// 	P15F = P15_ADC5_SETTING;	//设置P15为ADC引脚功能
// 	P16F = P16_ADC6_SETTING;	//设置P16为ADC引脚功能
// 	P17F = P17_ADC7_SETTING;	//设置P17为ADC引脚功能
	
// 		P10F = P10_ADC_VREF_SETTING;	//如果ADC参考电压选择为外部参考电压，需要设置P10为外部参考电压引脚，并且ADC0通道不能使用。
/***************************************************************************************/
	

/**********初始化ADC寄存器（设置ADC时钟、选择ADC参考电压、设置ADC运放、加载内部1.5V校准值）***********/
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//设置ADC参考电压为内部1.5V
	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);			//设置ADC参考电压为VDD
// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_Outer);		//设置ADC参考电压为外部参考电压
	
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());				//加载内部1.5V校准值
/**************************************************************************************************/


/**********设置ADC通道和时钟分频*********************************************************************/
	ADCFGL = ACKD(7) | ADCHS(ADC_CH0);	//选择ADC0通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH1);	//选择ADC1通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH2);	//选择ADC2通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH3);	//选择ADC3通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH4);	//选择ADC4通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH5);	//选择ADC5通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH6);	//选择ADC6通道
// 	ADCFGL = ACKD(7) | ADCHS(ADC_CH7);	//选择ADC7通道
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
