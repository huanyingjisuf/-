//********************************************************* 
/* 文件名：TEST_60F01x_IO.c
* 功能：   FT60F01x IO功能演示
* IC:      FT60F011A SOP8
* 晶振：   16M/4T                    
* 说明：   当DemoPortIn悬空或者高电平时,
*		   DemoPortOut输出50Hz占空比50%的波形
*		   当DemoPortIn接地时,DemoPortOut输出高电平
*
*                  FT60F011A  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  DemoPortIn----|2(PA2)    (PA4)7|----DemoPortOut 
*  NC------------|3(PA1)    (PA5)6|-------------NC
*  NC------------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
//***********************宏定义****************************
#define  unchar     unsigned char 

#define  DemoPortOut	PA4   
#define  DemoPortIn		PA2
/*-------------------------------------------------
 *  函数名：POWER_INITIAL
 *	功能：  上电系统初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{ 
    OSCCON = 0B01110000;				//IRCF=111=16MHz/4T=4MHz,0.25us
                                 
	INTCON = 0;  						//暂禁止所有中断
	OPTION = 0B00001000;				//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1

	PORTA  = 0B00000000;					
	TRISA  = 0B00000100;				//PA输入输出 0-输出 1-输入
                                        //PA2-IN PA4-OUT
	WPUA   = 0B00000100;     			//PA端口上拉控制 1-开上拉 0-关上拉								
					 		            //开PA2上拉
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
    //Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后) 
}
/*-------------------------------------------------
 *  函数名：DelayUs
 *  功能：  短延时函数 
 *  输入：  Time延时时间长度 延时时长Time us
 * 	输出：  无 
 -------------------------------------------------*/
void DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
		NOP();
	}
}                  
/*------------------------------------------------- 
 * 	函数名：DelayMs
 * 	功能：  短延时函数--16M-4T--大概快1%左右.
 * 	输入：  Time延时时间长度 延时时长Time ms
 * 	输出：  无 
 -------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(98);                //快1%
		}
	}
}
/*-------------------------------------------------
 *  函数名:  main 
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();				  //系统初始化
	while(1)
	{
		DemoPortOut = 1; 			
		DelayMs(10);     			  //10ms
		if(DemoPortIn == 1) 		  //判断输入是否为高电平 
		{
			DemoPortOut = 0;
		}
		DelayMs(10); 
	}
}
