
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

/*********************************************************************************************************************
	INT1控制例程
*********************************************************************************************************************/
enum 
{
	P00_INDEX = 0,
	P01_INDEX = 1,
	P02_INDEX = 2,
	P03_INDEX = 3,
	P04_INDEX = 4,
	P05_INDEX = 5,
	P06_INDEX = 6,
	P07_INDEX = 7,

	P10_INDEX = 8,
	P11_INDEX = 9,
	P12_INDEX = 10,
	P13_INDEX = 11,
	P14_INDEX = 12,
	P15_INDEX = 13,
	P16_INDEX = 14,
	P17_INDEX = 15,

	P20_INDEX = 16,
	P21_INDEX = 17,

	P30_INDEX = 24,
	P31_INDEX = 25,
	P32_INDEX = 26,
	P33_INDEX = 27,
	P34_INDEX = 28,
	P35_INDEX = 29,
	P36_INDEX = 30,
	P37_INDEX = 31,
};
bit int1_flag;
void INT1_init(void)
{
	P10F = INPUT;					//P10设置为输入功能
	IT1CON = P10_INDEX;				//设置P10为INT1中断引脚
	EX1 = 1;						//INT1中断使能
	IE1 = 1;						//外部中断1中断使能
	IT1 = 1;						//设置INT1为下降沿触发
	PX1 = 1;						//设置INT1中断为最高优先级
	
	int1_flag = 0;
}
void INT1_ISR (void) interrupt 2
{
	int1_flag = 1;			
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
	uart_printf("INT1 Demo Code\n");
#endif


	INT1_init();
//	P00F = OUTPUT;	
	while(1)
	{
		if(int1_flag)		
		{
			int1_flag = 0;
//			P00 = ~P00;
		#ifdef PRINT_EN
			uart_printf("INT1\n");
		#endif
		}
	}
}
#endif
