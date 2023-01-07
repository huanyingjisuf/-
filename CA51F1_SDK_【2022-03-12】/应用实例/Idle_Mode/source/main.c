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
	���ſ�������
*********************************************************************************************************************/
void main(void)
{	
#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

/*
��ע�����ڽ���IDLE ����ʱ�����Ǵ򿪵ģ��������IDLEǰ��ʱ���Ǹ���ʱ�ӣ���
	  ��IDLEģʽ�󹦺��Ի�ܴ����Խ���IDLE֮ǰ��Ҫ����ʱ���л�������ʱ�ӡ�
*/
	Sys_Clk_Set_IRCL(); 		//ϵͳʱ����ΪIRCL
	I2CCON = 0; 				//�ر�I2Cģ�飬��ΪI2CĬ����ʹ�ܵģ����I2C���رս��޷��ر�IRCHʱ�� 	 
	CKCON&=~IHCKE; 				//�ر�IRCHʱ��
	MECON |= (1<<6); 			//����FLASH�������˯��״̬ 
	while(IDLST&0x7F); 			//������ж�δ��Ӧ,�ȴ��жϱ���Ӧ
	PCON |= 0x01; 				//����IDLEģʽ 
	_nop_(); 
	_nop_(); 
	
	while(1)
	{
		
	}
	
}
#endif
