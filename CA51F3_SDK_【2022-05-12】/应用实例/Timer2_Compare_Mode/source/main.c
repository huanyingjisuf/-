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
//寄存器T2CON定义
#define TR2(N)   (N<<6)
#define T2R(N)   (N<<4)   	//N=0~3
#define T2IE(N)  (N<<3)
#define UCKS(N)  (N<<2)
#define T2P(N)   (N)	    //N=0~3

//寄存器T2MOD定义
#define TF2		 (1<<7)
#define CF2		 (1<<6)
#define RF2		 (1<<5)
#define CCFG(N)	 (N<<3)	  	//N=0~3
#define T2M(N)	 (N)		//N=0~3

/*********************************************************************************************************************/
void main(void)
{	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE1;					//设置LVD复位电压为2V
#endif
	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial_Timer1(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("Timer2 Compare Mode Demo Code\n");
#endif
	   
	P36F = P36_T2CP_SETTING;	  	//比较输出引脚初始化
	T2CON = TR2(0) | T2R(0) | T2IE(0) | UCKS(0) | T2P(0); 																			                                                        
	T2MOD = CCFG(2) | T2M(1);		//设置为比较模式
	 
	T2CH = 0x80;     				//T2C值越小，T2CP输出占空比越大。
	T2CL = 0x00;
	TH2=0;        					//计数初值
	TL2=0;			  
	T2CON |= TR2(1);  				//定时器2启动

	while(1)
	{
	}
}


#endif


