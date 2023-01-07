
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
	������ʵ��4com*9seg��1/3bias LCD��ʾ���ܣ�LCDʱ������ΪXOSCL��IRCL��ʵ��LCD��С����ģʽ��
	
	��Ҫ��ʾ��
	�ڹر�LCD����ǰ���������õ�COM�ź�SEG������Ϊ���ģʽ������͵�ƽ�����Ա���ر�LCD����ʱLCD��������Ӱ����
*********************************************************************************************************************/			
void LCD_Off(void)
{
	//�ڹر�LCD����ǰ���������õ�COM�ź�SEG������Ϊ���ģʽ������͵�ƽ�����Ա���ر�LCD����ʱLCD��������Ӱ����
	P00 = 0;
	P01 = 0;
	P02 = 0;
	P03 = 0;	 
       
	P17 = 0;
	P37 = 0; 
	P36 = 0; 
	P35 = 0;
	P34 = 0;
	P07 = 0;
	P06 = 0;
	P05 = 0;
	P04 = 0;
	
	P00F = OUTPUT;
	P01F = OUTPUT;
	P02F = OUTPUT;
	P03F = OUTPUT;	 
       
	P17F = OUTPUT;
	P37F = OUTPUT; 
	P36F = OUTPUT;  
	P35F = OUTPUT; 
	P34F = OUTPUT;
	P07F = OUTPUT;
	P06F = OUTPUT; 
	P05F = OUTPUT;
	P04F = OUTPUT;
	
	LXCON = 0;						//�ر�LCD����
}

void main(void)
{	
	unsigned char i;
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
	uart_printf("LCD Power Saving Mode Demo Code\n");
#endif
		
	//��ʼ��LCD��������
	P00F = P00_COM0_SETTING;
	P01F = P01_COM1_SETTING;
	P02F = P02_COM2_SETTING;
	P03F = P03_COM3_SETTING;	 
       
	P17F = P17_SEG0_SETTING;
	P37F = P37_SEG1_SETTING; 
	P36F = P36_SEG2_SETTING;  
	P35F = P35_SEG3_SETTING; 
	P34F = P34_SEG4_SETTING;
	P07F = P07_SEG5_SETTING;
	P06F = P06_SEG6_SETTING; 
	P05F = P05_SEG7_SETTING;
	P04F = P04_SEG8_SETTING;	
	
	
	//LCD RAM����
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0;
	}
	
	P32F = P32_XOSC_IN_SETTING;			//����P32Ϊ��������
	P33F = P33_XOSC_OUT_SETTING;		//����P33Ϊ��������
	CKCON |= XLCKE;									//ʹ��XSOCL
	while(!(CKCON & XLSTA));				//�ȴ�XSOCL�ȶ�
	
// 	CKCON |= ILCKE;									//ʹ��IRCL

	LXDIVH = 0;				//����LCDʱ�ӷ�Ƶ��Ŀ��֡Ƶ��Ϊ64HZ
	LXDIVL = 0;	
	LXCAD = 0;
	LXCFG =	 DMOD(DMOD_5ua) | BIAS(BIAS_1_3) | LDRV(LDRV_7);			//����LCD����������ƫѹ(bias)���Զ�
	LXCON =  LEN(LEN_XOSCL) | LMOD(LMOD_lcd);	 										//����LCDʱ��ԴΪXOSCL��ѡ��LCDģʽ
// 	LXCON =  LEN(LEN_IRCL) | LMOD(LMOD_lcd);	 									//����LCDʱ��ԴΪIRCL��ѡ��LCDģʽ
	
	//����LCDȫ��
	for(i = 0; i < 9; i++)
	{
		INDEX = i;
		LXDAT = 0xFF;
	}

//	LCD_Off();
	
	I2CCON = 0;						//�ر�I2C������ϵͳʱ���޷��ر�
	CKCON = XLCKE;					//�رճ�LCDʱ���������ʱ��
// 	CKCON = ILCKE;	
	PWCON &= ~0x08;					//LDO����͹���ģʽ
	
	PCON = (PCON&0x84) | 0x02;      //����STOPģʽ
	_nop_();
	_nop_();
	_nop_();
	while(1)
	{
	}
}
#endif
