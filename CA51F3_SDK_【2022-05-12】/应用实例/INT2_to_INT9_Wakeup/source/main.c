
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
#include <intrins.h>
/*********************************************************************************************************************/

/*********************************************************************************************************************
	INT2~INT9��������
*********************************************************************************************************************/
enum 
{
	P00_INDEX = 0,
	P01_INDEX = 1,
	P02_INDEX = 2,
	P03_INDEX = 3,
	P04_INDEX = 4,
	P05_INDEX = 5,
	P06_INDEX = 6,
	P07_INDEX = 7,

	P10_INDEX = 8,
	P11_INDEX = 9,
	P12_INDEX = 10,
	P13_INDEX = 11,
	P14_INDEX = 12,
	P15_INDEX = 13,
	P16_INDEX = 14,
	P17_INDEX = 15,

	P20_INDEX = 16,
	P21_INDEX = 17,

	P30_INDEX = 24,
	P31_INDEX = 25,
	P32_INDEX = 26,
	P33_INDEX = 27,
	P34_INDEX = 28,
	P35_INDEX = 29,
	P36_INDEX = 30,
	P37_INDEX = 31,
};
//EPCON�Ĵ�������
#define EPPL(N)	(N<<7)

bit int2_flag,int3_flag,int4_flag,int5_flag,int6_flag,int7_flag,int8_flag,int9_flag;

/*�ⲿ�ж�2��������****************************************************************************************************/
void INT2_Init(void)
{
	P10F = INPUT;							//P10����Ϊ����ģʽ
	INDEX = 0;								//EPCONΪ�������ļĴ���������INDEX=0 ��ӦINT2
	EPCON = EPPL(1) | P10_INDEX;			//����P10ΪINT2�ж����ţ��½��ش���
	INT2EN = 1; 							//�ⲿ�ж�2�ж�ʹ��
	EPIE |= 0x01;							//INT2�ж�ʹ��
	int2_flag = 0;		
}
void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)
	{
		EPIF = 0x01;
		int2_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�3��������****************************************************************************************************/
void INT3_Init(void)
{
	P11F = INPUT;							//P11����Ϊ����ģʽ	
	INDEX = 1;								//INDEXΪ�������ļĴ���������INDEX=1 ��ӦINT3
	EPCON = EPPL(1) | P11_INDEX;			//����P11ΪINT3�ж����ţ��½��ش���		
	INT3EN = 1; 							//�ⲿ�ж�3�ж�ʹ�� 
	EPIE |= 0x02;							//INT3�ж�ʹ��
	int3_flag = 0;
}
void INT3_ISR (void) interrupt 8
{
	if(EPIF & 0x02)
	{
		EPIF = 0x02;	
		int3_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�4��������****************************************************************************************************/
void INT4_Init(void)
{
	P12F = INPUT;							//P12����Ϊ����ģʽ		
	INDEX = 2;								//INDEXΪ�������ļĴ���������INDEX=2 ��ӦINT4
	EPCON = EPPL(1) | P12_INDEX;			//����P12ΪINT4�ж����ţ��½��ش���				
	INT4EN = 1;  							//�ⲿ�ж�4�ж�ʹ��
	EPIE |= 0x04;							//INT4�ж�ʹ��
	int4_flag = 0;
}
void INT4_ISR (void) interrupt 9
{
	if(EPIF & 0x04)
	{
		EPIF = 0x04;
		int4_flag = 1;	
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�5��������****************************************************************************************************/
void INT5_Init(void)
{
	P13F = INPUT;							//P13����Ϊ����ģʽ		
	INDEX = 3;								//INDEXΪ�������ļĴ���������INDEX=3 ��ӦINT5
	EPCON = EPPL(1) | P13_INDEX;			//����P13ΪINT5�ж����ţ��½��ش���		
	INT5EN = 1; 							//�ⲿ�ж�5�ж�ʹ�� 
	EPIE |= 0x08;							//INT5�ж�ʹ��
	int5_flag = 0;
}
void INT5_ISR (void) interrupt 10
{
	if(EPIF & 0x08)
	{
		EPIF = 0x08;	
		int5_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�6��������****************************************************************************************************/
void INT6_Init(void)
{
	P14F = INPUT;							//P14����Ϊ����ģʽ			
	INDEX = 4;								//INDEXΪ�������ļĴ���������INDEX=4 ��ӦINT6
	EPCON = EPPL(1) | P14_INDEX;			//����P14ΪINT6�ж����ţ��½��ش���		
	INT6EN = 1;  							//�ⲿ�ж�6�ж�ʹ��
	EPIE |= 0x10;							//INT6�ж�ʹ��
	int6_flag = 0;
}
void INT6_ISR (void) interrupt 11
{
	if(EPIF & 0x10)
	{
		EPIF = 0x10;	
		int6_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�7��������****************************************************************************************************/
void INT7_Init(void)
{
	P15F = INPUT;							//P15����Ϊ����ģʽ		
	INDEX = 5;								//INDEXΪ�������ļĴ���������INDEX=5 ��ӦINT7
	EPCON = EPPL(1) | P15_INDEX;			//����P15ΪINT7�ж����ţ��½��ش���		
	INT7EN = 1;  							//�ⲿ�ж�7�ж�ʹ��
	EPIE |= 0x20;							//INT7�ж�ʹ��
	int7_flag = 0;
}
void INT7_ISR (void) interrupt 12
{
	if(EPIF & 0x20)
	{
		EPIF = 0x20;	
	  int7_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�8��������****************************************************************************************************/
void INT8_Init(void)
{
	P16F = INPUT;							//P16����Ϊ����ģʽ			
	INDEX = 6;								//INDEXΪ�������ļĴ���������INDEX=6 ��ӦINT8
	EPCON = EPPL(1) | P16_INDEX;			//����P16ΪINT8�ж����ţ��½��ش���		
	INT8EN = 1;  							//�ⲿ�ж�8�ж�ʹ��
	EPIE |= 0x40;							//INT8�ж�ʹ��
	int8_flag = 0;
}
void INT8_ISR (void) interrupt 13
{
	if(EPIF & 0x40)
	{
		EPIF = 0x40;	
		int8_flag = 1;
	}
}
/*********************************************************************************************************************/

/*�ⲿ�ж�9��������****************************************************************************************************/
void INT9_Init(void)
{
	P17F = INPUT;							//P17����Ϊ����ģʽ		
	INDEX = 7;								//INDEXΪ�������ļĴ���������INDEX=7 ��ӦINT9
	EPCON = EPPL(1) | P17_INDEX;			//����P17ΪINT9�ж����ţ��½��ش���	
	INT9EN = 1;  							//�ⲿ�ж�9�ж�ʹ��
	EPIE |= 0x80;							//INT9�ж�ʹ��
	int9_flag = 0;
}
void INT9_ISR (void) interrupt 14
{
	if(EPIF & 0x80)
	{
		EPIF = 0x80;	
		int9_flag = 1;
	}
}
/*********************************************************************************************************************/

void main(void)
{
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
	uart_printf("INT2 to INT9 Demo Code\n");
#endif
	
	INT2_Init(); 
//	INT3_Init();
//	INT4_Init();
//	INT5_Init();
//	INT6_Init();
//	INT7_Init();
//	INT8_Init();
//	INT9_Init();

//	P00F = OUTPUT;	
	while(1)
	{
		if(int2_flag)					
		{
			int2_flag = 0;
//		#ifdef PRINT_EN
//			uart_printf("INT2\n");
//		#endif
//			P00 = ~P00;
		}
		if(int3_flag)				
		{
			int3_flag = 0;
		}
		if(int4_flag)					
		{
			int4_flag = 0;
		}
		if(int5_flag)				
		{
			int5_flag = 0;
		}
		if(int6_flag)				
		{
			int6_flag = 0;
		}
		if(int7_flag)				
		{
			int7_flag = 0;
		}
		if(int8_flag)				
		{
			int8_flag = 0;
		}
		if(int9_flag)				
		{
			int9_flag = 0;
		}
	}
}
#endif
