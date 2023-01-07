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
	引脚控制例程
*********************************************************************************************************************/
void main(void)
{	
#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

/*
备注：由于进入IDLE 后，主时钟仍是打开的，如果进入IDLE前主时钟是高速时钟，进
	  入IDLE模式后功耗仍会很大，所以进入IDLE之前需要把主时钟切换到低速时钟。
*/
	Sys_Clk_Set_IRCL(); 		//系统时钟设为IRCL
	I2CCON = 0; 				//关闭I2C模块，因为I2C默认是使能的，如果I2C不关闭将无法关闭IRCH时钟 	 
	CKCON&=~IHCKE; 				//关闭IRCH时钟
	MECON |= (1<<6); 			//设置FLASH进入深度睡眠状态 
	while(IDLST&0x7F); 			//如果有中断未响应,等待中断被响应
	PCON |= 0x01; 				//进入IDLE模式 
	_nop_(); 
	_nop_(); 
	
	while(1)
	{
		
	}
	
}
#endif
