
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
	uart_printf("ADC Detect VDD Demo Code\n");
#endif


/**********初始化ADC寄存器（设置ADC时钟、选择ADC参考电压、设置ADC运放、加载内部1.5V校准值）***********/
 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//设置ADC参考电压为内部1.5V
	ADCFGH = AOPS(NO_AMP) | VTRIM(read_inner_trim());				//加载内部1.5V校准值
/**************************************************************************************************/


/**********设置ADC通道和时钟分频*********************************************************************/
	ADCFGL = ACKD(7) | ADCHS(ADC_VDD);	//选择ADC通道为1/4VDD
/**************************************************************************************************/


	while(1)
	{
		unsigned int AD_Value;
		double VDD_Voltage;
		ADCON |= AST(1);									//启动ADC转换
		while(!(ADCON & ADIF));								//等待ADC转换完成
		ADCON |= ADIF;										//清除ADC中断标志
		AD_Value = ADCDH*256 + ADCDL;						//读取AD值
		AD_Value >>= 4;		
		
		VDD_Voltage = ((double)AD_Value*1.5*4)/4095;		//根据ADC值换算为电压值，注意：由于ADC检测的是1/4VDD，所以换算为VDD电压时ADC值要乘以4
#ifdef PRINT_EN
		uart_printf ("VDD Voltage = %e\n",VDD_Voltage);		//打印VDD电压值	
#endif		
		Delay_ms(100);
	}
}
#endif
