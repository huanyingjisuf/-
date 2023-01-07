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
	��������ģʽ����
*********************************************************************************************************************/
#define IHCKE 		(1<<7) 
#define ILCKE 		(1<<6) 
#define CKSEL_IRCH 		0 
#define CKSEL_IRCL 		1

void main(void)
{	
#ifdef SYSCLK_16MHZ			//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

	I2CCON = 0; 			//�ر�I2Cģ�飬��ΪI2CĬ����ʹ�ܵģ����I2C���رս��޷��ر�IRCHʱ��
	Sys_Clk_Set_IRCL();		//�л�ϵͳʱ��ΪIRCL 
	CKCON &= ~IHCKE; 		//�ر�IRCHʱ�� 

	while(1)
	{
	}
}
#endif
