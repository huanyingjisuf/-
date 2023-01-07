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
/*********************************************************************************************************************
	引脚控制例程
*********************************************************************************************************************/
void main(void)
{	
#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

/*
	所有时钟关闭，所有输出引脚无负载，所有数字输入引脚不浮动，所有外设
	关闭，Flash进入睡眠模式，CPU进入STOP模式。
*/
	I2CCON = 0;        //关闭I2C功能，因为I2C默认是使能的，如果I2C不关闭将无法关闭IRCH时钟 
	CKCON = 0;         //关闭所有时钟 
	MECON |= (1<<6);   //设置FLASH进入深度睡眠状态 
	PCON |= 0x02;     //进入STOP模式 
	_nop_();          //在STOP的指令后面需要紧接三条nop指令，防止程序出错。
	_nop_();
	_nop_();
	
	while(1)
	{
		
	}
	
}
#endif
