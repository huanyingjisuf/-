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
#include <intrins.h>
/*********************************************************************************************************************/

//WDFLG定义
#define WDIF			(1<<1)
#define WDRF			(1<<0)

#define WDTS_DISABLE	(0<<6)
#define WDTS_IRCH		(1<<6)
#define WDTS_IRCL		(2<<6)

#define WDRE_reset		(1<<0)
#define WDRE_int		(0<<0)

bit WdtIntEvFlag;
void WDT_ISR (void) interrupt 6 
{
	if(WDFLG & WDIF)
	{
		WDFLG = 0xA5;
		WdtIntEvFlag = 1;
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
	uart_printf("Watch dog interrupt demo\n");
#endif
	

	/***************************看门狗阈值设置计算公式如下****************************
看门狗触发时间 = (WDVTH * 800H+7FFH) * clock cycle
*********************************************************************************/

//看门狗时钟源为IRCH(内部高速时钟)	
	WDCON = WDTS_IRCH | WDRE_int;   	//设置看门狗时钟源为IRCH，模式为中断模式
	WDVTHH = 0x1e;						//看门狗中断阈值高八位设置 当前值为1s
	WDVTHL = 0x84;						//看门狗中断阈值低八位设置


//看门狗时钟源为IRCL
// 	CKCON |= ILCKE;						//使能IRCL
// 	WDCON = WDTS_IRCL | WDRE_int;   	//设置看门狗时钟源为ILCKE，模式为中断模式
// 	WDVTHH = 0;							//看门狗中断阈值高八位设置 当前值为1s	
// 	WDVTHL = 0x0f;						//看门狗中断阈值低八位设置
	
	INT4EN = 1; 						//开启看门狗中断
	WDFLG = 0xA5;						//喂狗
	while(1)
	{
		if(WdtIntEvFlag)				//看门狗中断发生
		{
			WdtIntEvFlag = 0;
		#ifdef PRINT_EN
			uart_printf("Watch dog interrupt happen\n");	
		#endif
		}		
	}
}
#endif
