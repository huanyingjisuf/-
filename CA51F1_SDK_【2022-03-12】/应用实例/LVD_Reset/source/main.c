#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"

#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/

/*********************************************************************************************************************
	LVD复位例程

	说明：LVD复位产生之后，LVD自身的电路并不会复位，寄存器LVDCON还会保持之前的状态，所以，
	      当LVD复位产生之后，如果VDD持续低于所设定的电压，芯片将会一直处于复位状态。
*********************************************************************************************************************/
#define LVDE(N)			(N<<7)	  	//N=0~1
#define LVDS_reset		(1<<6)
#define LVDS_int		(0<<6)
#define LVDF			(1<<5)

#define LVDTH_2p2V		0
#define LVDTH_2p7V		1
#define LVDTH_3p7V		2
#define LVDTH_4p2V		3

void main(void)
{	
#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//初始化UART
#endif
	
	EA = 1;							//开全局中断

#ifdef PRINT_EN
	uart_printf("LVD Reset Demo Code\n");
#endif

	LVDCON = LVDE(1) | LVDF | LVDS_reset | LVDTH_2p2V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.2V
//	LVDCON = LVDE(1) | LVDF | LVDS_reset | LVDTH_2p7V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_reset | LVDTH_3p7V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_reset | LVDTH_4p2V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.2V

	while(1)
	{
	}
}
#endif
