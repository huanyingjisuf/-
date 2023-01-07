#ifndef _SYSTEM_CLOCK_C_
#define _SYSTEM_CLOCK_C_
/*********************************************************************************************************************/
#include "ca51f1_config.h"
#include "includes\ca51f1sfr.h"
#include "includes\ca51f1xsfr.h"
#include "includes\gpiodef_f1.h"

#include "includes\system.h"
#include "Library\includes\system_clock.h"
#include <intrins.h>
/*********************************************************************************************************************/
void Sys_Clk_Set_IRCH(void)
{
	CKCON |= IHCKE;						//IRCH时钟使能
	CKCON = (CKCON&0xFE) | CKSEL_IRCH;	//系统时钟切换到IRCH		
}
void Sys_Clk_Set_IRCL(void)
{
	CKCON |= ILCKE;						//IRCL时钟使能
	CKCON = (CKCON&0xFE) | CKSEL_IRCL;	//系统时钟切换到IRCH	
}
/*********************************************************************************************************************/
#endif
