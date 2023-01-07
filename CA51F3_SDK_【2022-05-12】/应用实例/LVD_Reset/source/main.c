
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

#define LVDE(N)		(N<<7)
#define LVDS_reset	(1<<6)
#define LVDS_int	(0<<6)
#define LVDF		(1<<5)

#define LVDTH_1p8V		0
#define LVDTH_2p0V		1
#define LVDTH_2p2V		2
#define LVDTH_2p4V		3
#define LVDTH_2p6V		4
#define LVDTH_2p8V		5
#define LVDTH_3p0V		6
#define LVDTH_3p2V		7
#define LVDTH_3p4V		8
#define LVDTH_3p6V		9
#define LVDTH_3p8V		10
#define LVDTH_4p0V		11
#define LVDTH_4p2V		12
#define LVDTH_4p4V		13
#define LVDTH_4p6V		14
#define LVDTH_4p8V		15

void main(void)
{	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;							//开全局中断

#ifdef PRINT_EN
	uart_printf("LVD Reset Demo Code\n");
#endif

//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_1p8V;	//设置LVD使能,设置LVD为复位模式,检测电压为1.8V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p0V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.0V
	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p2V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.2V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p4V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.4V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p6V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.6V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p8V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.8V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p0V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.0V	
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p2V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.2V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p4V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.4V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p6V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.6V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p8V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.8V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_4p0V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.0V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_4p2V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.2V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_4p4V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.4V
//	LVDCON = LVDE(1) | LVDS_reset | LVDTH_4p8V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.8V

	while(1)
	{
	}
}
#endif
