
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
	INT2~INT9控制例程
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
//EPCON寄存器定义
#define EPPL(N)	(N<<7)

bit int2_flag,int3_flag,int4_flag,int5_flag,int6_flag,int7_flag,int8_flag,int9_flag;

/*外部中断2控制例程****************************************************************************************************/
void INT2_Init(void)
{
	P10F = INPUT;							//P10设置为输入模式
	INDEX = 0;								//EPCON为带索引的寄存器，设置INDEX=0 对应INT2
	EPCON = EPPL(1) | P10_INDEX;			//设置P10为INT2中断引脚，下降沿触发
	INT2EN = 1; 							//外部中断2中断使能
	EPIE |= 0x01;							//INT2中断使能
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

/*外部中断3控制例程****************************************************************************************************/
void INT3_Init(void)
{
	P11F = INPUT;							//P11设置为输入模式	
	INDEX = 1;								//INDEX为带索引的寄存器，设置INDEX=1 对应INT3
	EPCON = EPPL(1) | P11_INDEX;			//设置P11为INT3中断引脚，下降沿触发		
	INT3EN = 1; 							//外部中断3中断使能 
	EPIE |= 0x02;							//INT3中断使能
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

/*外部中断4控制例程****************************************************************************************************/
void INT4_Init(void)
{
	P12F = INPUT;							//P12设置为输入模式		
	INDEX = 2;								//INDEX为带索引的寄存器，设置INDEX=2 对应INT4
	EPCON = EPPL(1) | P12_INDEX;			//设置P12为INT4中断引脚，下降沿触发				
	INT4EN = 1;  							//外部中断4中断使能
	EPIE |= 0x04;							//INT4中断使能
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

/*外部中断5控制例程****************************************************************************************************/
void INT5_Init(void)
{
	P13F = INPUT;							//P13设置为输入模式		
	INDEX = 3;								//INDEX为带索引的寄存器，设置INDEX=3 对应INT5
	EPCON = EPPL(1) | P13_INDEX;			//设置P13为INT5中断引脚，下降沿触发		
	INT5EN = 1; 							//外部中断5中断使能 
	EPIE |= 0x08;							//INT5中断使能
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

/*外部中断6控制例程****************************************************************************************************/
void INT6_Init(void)
{
	P14F = INPUT;							//P14设置为输入模式			
	INDEX = 4;								//INDEX为带索引的寄存器，设置INDEX=4 对应INT6
	EPCON = EPPL(1) | P14_INDEX;			//设置P14为INT6中断引脚，下降沿触发		
	INT6EN = 1;  							//外部中断6中断使能
	EPIE |= 0x10;							//INT6中断使能
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

/*外部中断7控制例程****************************************************************************************************/
void INT7_Init(void)
{
	P15F = INPUT;							//P15设置为输入模式		
	INDEX = 5;								//INDEX为带索引的寄存器，设置INDEX=5 对应INT7
	EPCON = EPPL(1) | P15_INDEX;			//设置P15为INT7中断引脚，下降沿触发		
	INT7EN = 1;  							//外部中断7中断使能
	EPIE |= 0x20;							//INT7中断使能
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

/*外部中断8控制例程****************************************************************************************************/
void INT8_Init(void)
{
	P16F = INPUT;							//P16设置为输入模式			
	INDEX = 6;								//INDEX为带索引的寄存器，设置INDEX=6 对应INT8
	EPCON = EPPL(1) | P16_INDEX;			//设置P16为INT8中断引脚，下降沿触发		
	INT8EN = 1;  							//外部中断8中断使能
	EPIE |= 0x40;							//INT8中断使能
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

/*外部中断9控制例程****************************************************************************************************/
void INT9_Init(void)
{
	P17F = INPUT;							//P17设置为输入模式		
	INDEX = 7;								//INDEX为带索引的寄存器，设置INDEX=7 对应INT9
	EPCON = EPPL(1) | P17_INDEX;			//设置P17为INT9中断引脚，下降沿触发	
	INT9EN = 1;  							//外部中断9中断使能
	EPIE |= 0x80;							//INT9中断使能
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
	LVDCON = 0xE1;					//设置LVD复位电压为2V
#endif

#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

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
