
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/delay.h"
#include "include/lcd_led.h"
#include <intrins.h>
/*********************************************************************************************************************			
	������ʵ��4com*9seg LED��ʾ���ܡ�
*********************************************************************************************************************/			

void main(void)
{	
	unsigned char i;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE1;					//����LVD��λ��ѹΪ2V
#endif

#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("LED Demo Code\n");
#endif

	
	
	//��ʼ��LED��������
	P00F = P00_COM0_SETTING;			//����P00ΪCOM0
	P00C |= 0x80;									//����P00Ϊ�߹����ģʽ
	
	P01F = P01_COM1_SETTING;			//����P01ΪCOM1
	P01C |= 0x80;									//����P01Ϊ�߹����ģʽ
	
	P02F = P02_COM2_SETTING;			//����P02ΪCOM2
	P02C |= 0x80;									//����P02Ϊ�߹����ģʽ
	
	P03F = P03_COM3_SETTING;	 		//����P03ΪCOM3
	P03C |= 0x80;									//����P03Ϊ�߹����ģʽ
       
			 
	//��������ΪSEG����
	P17F = P17_SEG0_SETTING;
	P37F = P37_SEG1_SETTING; 
	P36F = P36_SEG2_SETTING;  
	P35F = P35_SEG3_SETTING; 
	P34F = P34_SEG4_SETTING;
	P07F = P07_SEG5_SETTING;
	P06F = P06_SEG6_SETTING; 
	P05F = P05_SEG7_SETTING;
	P04F = P04_SEG8_SETTING;	
	
	//LED RAM����
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}

	LXDIVH = 0;						//����LEDʱ�ӷ�Ƶ
	LXDIVL = 112;	
	LXCFG =	 COMHV(COM_L) | SEGHV(SEG_H) | BLNK(0) | LDRV(LDRV_7);		//����LED COM��SEG��Ч��ƽ�����ȼ���
	LXCON =  LEN(LEN_IRCH) | LMOD(LMOD_led);	 												//����LEDʱ��Դ��ѡ��LEDģʽ
	
	//����LCDȫ��
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0xFF;
	}
	while(1)
	{
	}
}
#endif
