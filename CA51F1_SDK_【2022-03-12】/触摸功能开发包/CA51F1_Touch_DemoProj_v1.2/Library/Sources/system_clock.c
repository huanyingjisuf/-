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
	CKCON |= IHCKE;						//IRCHʱ��ʹ��
	CKCON = (CKCON&0xFE) | CKSEL_IRCH;	//ϵͳʱ���л���IRCH		
}
void Sys_Clk_Set_IRCL(void)
{
	CKCON |= ILCKE;						//IRCLʱ��ʹ��
	CKCON = (CKCON&0xFE) | CKSEL_IRCL;	//ϵͳʱ���л���IRCH	
}
/*********************************************************************************************************************/
#endif
