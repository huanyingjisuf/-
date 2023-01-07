
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"
#include <intrins.h>
/*********************************************************************************************************************/
void main(void)
{
	//注意：上电后默认系统时钟为IRCH, 如需切换时钟，可在ca51f_config.h选择其他系统时钟定义
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#elif (SYSCLK_SRC == IRCL)
	Sys_Clk_Set_IRCL();							//设置系统时钟为IRCL
#elif (SYSCLK_SRC == XOSCL)
	Sys_Clk_Set_XOSCL();						//设置系统时钟为XOSCL
#endif
	while(1)
	{
	}
}
#endif
