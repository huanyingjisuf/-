
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
#include <intrins.h>
/*********************************************************************************************************************/
unsigned long int Read_32bit_UID(void)				
{
	unsigned long int ID;
	LOCK  = 0x2B;	
	FSCMD = 0x80;	
	PTSH = 0x01;				
	PTSL = 0x00;        			
	FSCMD = 0x81;						
	ID = FSDAT;
	ID *= 256;
	ID |= FSDAT;
	ID *= 256;
	ID |= FSDAT;
	ID *= 256;
	ID |= FSDAT;
	FSCMD = 0;
	LOCK = 0xAA;
	return ID;
}
void main(void)
{
	unsigned long int UID;
	
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
	uart_printf("Read 32bits UID Demo Code\n");
#endif

	UID = Read_32bit_UID();
#ifdef PRINT_EN
	uart_printf ("UID = %ld\n",UID);		//打印UID值
#endif
	while(1)
	{
	}
}
#endif
