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
	LVD中断例程

	说明：当LVD中断产生后，如果VDD持续低于所设定的电压，LVD中断也会重复地产生。
*********************************************************************************************************************/
#define LVDE(N)			(N<<7)	  	//N=0~1
#define LVDS_reset		(1<<6)
#define LVDS_int		(0<<6)
#define LVDF			(1<<5)

#define LVDTH_2p2V		0
#define LVDTH_2p7V		1
#define LVDTH_3p7V		2
#define LVDTH_4p2V		3

void LVD_ISR(void) interrupt 6		//LVD中断服务程序
{
	if(LVDCON & LVDF)
	{
		LVDCON |= LVDF;			    //清除LVD中断标志

	}		
}
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
	uart_printf("LVD Interrupt Demo Code\n");
#endif
	
	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_2p2V;	//设置LVD使能,设置LVD为中断模式,检测电压为2.2V
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_2p7V;	//设置LVD使能,设置LVD为中断模式,检测电压为2.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_3p7V;	//设置LVD使能,设置LVD为中断模式,检测电压为3.7V	
//	LVDCON = LVDE(1) | LVDF | LVDS_int | LVDTH_4p2V;	//设置LVD使能,设置LVD为中断模式,检测电压为4.2V

	INT4EN = 1; 					//INT4 中断使能

	while(1)
	{
	}
}
#endif
