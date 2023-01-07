#ifndef _WDT_C_
#define _WDT_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/wdt.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
/*****************************************************************************
��������WDT_init
������������ʼ�����Ź�
���������wdts		���Ź�ʱ��Դ����
					wdre		���Ź�ģʽ����
					wdtch		���Ź�ʱ������
����ֵ�� ��
******************************************************************************/
void WDT_init(WDTS_TypeDef wdts,WDRE_TypeDef wdre,unsigned int wdtvh)
{
	WDCON = WDTS(wdts) | WDRE(wdre);
	WDVTHH = (unsigned char)(wdtvh>>8);
	WDVTHL = (unsigned char)(wdtvh);	
}

/*****************************************************************************
��������WDT_FeedDog
����������ˢ�¿��Ź�
�����������
����ֵ�� ��
******************************************************************************/
void WDT_FeedDog(void)
{
	WDFLG = 0xA5;
}
/*********************************************************************************************************************/
#endif