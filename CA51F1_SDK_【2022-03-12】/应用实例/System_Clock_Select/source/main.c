#ifndef _MAIN_C_
#define _MAIN_C_
/********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"

#include "include/system_clock.h"
/********************************************************************************************************************/

void main(void)
{	
#if (SYSCLK_SRC == IRCH)
	Sys_Clk_Set_IRCH();							//设置系统时钟为IRCH
	#ifdef SYSCLK_16MHZ							//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
	#endif
#elif (SYSCLK_SRC == IRCL)
	Sys_Clk_Set_IRCL();							//设置系统时钟为IRCL
#endif
	while(1)
	{
	}
}
#endif
