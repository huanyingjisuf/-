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
	ADC检测VDD例程
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


/**********初始化ADC寄存器（设置ADC时钟、选择ADC参考电压）*****************************************/
 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//设置ADC参考电压为内部1.5V
/**************************************************************************************************/


/**********设置ADC通道、校准使能、ADC通道*******************************************************************/								
	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_VDD);	//选择ADC通道为1/4VDD
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
