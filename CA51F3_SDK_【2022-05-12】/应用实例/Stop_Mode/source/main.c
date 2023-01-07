
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
	STOP模式例程，并简单演示:通过INT2中断来唤醒STOP								
**********************************************************************************************************************/

/******************************************************************************************************/
void INT2_init(void)
{
	P10F = 1;				//设置P10为输入引脚
	INDEX = 0;				//INDEX为带索引的寄存器，设置INDEX=0对应INT2
	EPCON = (1<<7) | 8;		//设置P10为INT2外部中断引脚，下降沿触发
	INT2EN = 1; 			//外部中断2中断使能
	EPIE |= 0x01;			//INT2中断使能
	EA = 1;					//总中断使能
}
void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)			//判断外部中断2中断标志
	{
		EPIF = 0x01;		//中断标志写1清0
	}
}
/******************************************************************************************************/
void Stop(void)
{
	bit IE_EA;
	/*
	备注：进入STOP模式前应关闭相应的外设电路，如未使用到的IO尽量不要为悬浮状态(可设置为高阻态+上拉)，如下：
	*/
#if 1
	GPIO_Init(P00F,HIGH_Z|PU_EN);
	GPIO_Init(P01F,HIGH_Z|PU_EN);
	GPIO_Init(P02F,HIGH_Z|PU_EN);
	GPIO_Init(P03F,HIGH_Z|PU_EN);
	GPIO_Init(P04F,HIGH_Z|PU_EN);
	GPIO_Init(P05F,HIGH_Z|PU_EN);
	GPIO_Init(P06F,HIGH_Z|PU_EN);
	GPIO_Init(P07F,HIGH_Z|PU_EN);

//	GPIO_Init(P10F,HIGH_Z|PU_EN);
	GPIO_Init(P11F,HIGH_Z|PU_EN);
	GPIO_Init(P12F,HIGH_Z|PU_EN);
	GPIO_Init(P13F,HIGH_Z|PU_EN);
	GPIO_Init(P14F,HIGH_Z|PU_EN);
	GPIO_Init(P15F,HIGH_Z|PU_EN);
	GPIO_Init(P16F,HIGH_Z|PU_EN);
	GPIO_Init(P17F,HIGH_Z|PU_EN);

	GPIO_Init(P20F,HIGH_Z|PU_EN);
	GPIO_Init(P21F,HIGH_Z|PU_EN);

	GPIO_Init(P30F,HIGH_Z|PU_EN);
	GPIO_Init(P31F,HIGH_Z|PU_EN);
	GPIO_Init(P32F,HIGH_Z|PU_EN);
	GPIO_Init(P33F,HIGH_Z|PU_EN);
	GPIO_Init(P34F,HIGH_Z|PU_EN);
	GPIO_Init(P35F,HIGH_Z|PU_EN);
	GPIO_Init(P36F,HIGH_Z|PU_EN);
	GPIO_Init(P37F,HIGH_Z|PU_EN);
#endif

#if (SYSCLK_SRC == PLL)	
	Sys_Clk_Set_IRCH();		//如果系统时钟为PLL，在进入STOP之前要把系统时钟切换回IRCH
	PLLCON = 0;				//关闭PLL
#endif
	I2CCON = 0;				//关闭I2C，否则无法关闭主时钟
	CKCON = 0;				//所有时钟关闭
	PWCON &= ~0x08;			//设置LDO进入低功率模式	
	MECON |= (1<<6); 		//设置FLASH进入深度睡眠状态
	while(STPSTH|STPSTL);	//如果有中断未响应,等待中断被响应
	IE_EA = EA; 			//保存全局中断使能位状态
	EA = 0;
	PCON = (PCON&0x84) | 0x02;//进入STOP模式
	_nop_();
	_nop_();
	_nop_();
	EA = IE_EA; 			//恢复原全局中断开关状态	
	PWCON |= 0x08;			//退出STOP模式后，把LDO设回高功率模式
	
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//系统时钟切换回PLL
#endif
}
/******************************************************************************************************/
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

#ifdef UART2_EN
	Uart2_Initial(UART2_BAUTRATE);	//初始化UART2
#endif
	
	EA = 1;	

	INT2_init();
	
	while(1)
	{
	#ifdef PRINT_EN
		uart_printf("stop\n");
		Delay_ms(1);
	#endif		
		Stop();
	#ifdef PRINT_EN
		uart_printf("exit\n");
	#endif
		Delay_ms(1000);
	}
}
/**********************************************************************************************************************/
#endif

