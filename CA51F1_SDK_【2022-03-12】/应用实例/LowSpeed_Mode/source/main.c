#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"

#include "include/system_clock.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************
	低速运行模式例程
*********************************************************************************************************************/
#define IHCKE 		(1<<7) 
#define ILCKE 		(1<<6) 
#define CKSEL_IRCH 		0 
#define CKSEL_IRCL 		1

void main(void)
{	
#ifdef SYSCLK_16MHZ			//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

	I2CCON = 0; 			//关闭I2C模块，因为I2C默认是使能的，如果I2C不关闭将无法关闭IRCH时钟
	Sys_Clk_Set_IRCL();		//切换系统时钟为IRCL 
	CKCON &= ~IHCKE; 		//关闭IRCH时钟 

	while(1)
	{
	}
}
#endif
