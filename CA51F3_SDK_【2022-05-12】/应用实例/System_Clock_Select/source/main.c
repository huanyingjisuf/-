
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
	//ע�⣺�ϵ��Ĭ��ϵͳʱ��ΪIRCH, �����л�ʱ�ӣ�����ca51f_config.hѡ������ϵͳʱ�Ӷ���
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#elif (SYSCLK_SRC == IRCL)
	Sys_Clk_Set_IRCL();							//����ϵͳʱ��ΪIRCL
#elif (SYSCLK_SRC == XOSCL)
	Sys_Clk_Set_XOSCL();						//����ϵͳʱ��ΪXOSCL
#endif
	while(1)
	{
	}
}
#endif
