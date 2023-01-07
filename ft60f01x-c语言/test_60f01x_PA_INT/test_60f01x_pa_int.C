//********************************************************* 
/* 文件名：TEST_60F01x_PA_INT.c
* 功能：   FT60F01x-PA口电平中断功能演示
* IC:      FT60F011A SOP8
* 晶振：   16M/4T                    
* 说明：   程序中DemoPortOut(PA4)输出100帧50Hz的占空比为50%的方波后,MCU进入睡眠,等待
*          中断的发生;
*		   当每次PA2电平变化中断触发后，重复以上流程;
*
*                  FT60F011A  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  NC------------|2(PA2)    (PA4)7|----DemoPortOut 
*  NC------------|3(PA1)    (PA5)6|-------------NC
*  NC------------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
//***********************宏定义****************************
#define	unchar     unsigned char 

#define	DemoPortOut  PA4   
 
unchar	FCount;
unchar	ReadAPin;
/*-------------------------------------------------
 * 函数名：interrupt ISR
 * 功能：  中断处理函数
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void interrupt ISR(void)
{ 
	//PA电平变化中断
	 if(PAIE && PAIF)		
    {
		ReadAPin = PORTA; 	//读取PORTA数据清PAIF标志
		PAIF = 0;  			//清PAIF标志位
		PAIE = 0;  			//暂先禁止PA0中断
		IOCA2 =0;  			//禁止PA0电平变化中断
    }
} 
/*----------------------------------------------------
 * 函数名：POWER_INITIAL
 * 功能：  上电系统初始化
 * 输入：  无
 * 输出：  无
 ----------------------------------------------------*/	
void POWER_INITIAL (void) 
{ 
	OSCCON = 0B01110001;	//IRCF=111=16MHz/2=8MHz,0.125us
	INTCON = 0;  			//暂禁止所有中断
    
	PORTA = 0B00000000;		
	TRISA = 0B11101111;		//PA输入输出 0-输出 1-输入
							//PA4->输出
	WPUA = 0B00000000;     	//PA端口上拉控制 1-开上拉 0-关上拉

	OPTION = 0B00001000;	//Bit3=1 WDT MODE,PS=000=1:1 WDT RATE
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
    //Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后)  
}
/*----------------------------------------------------
 * 函数名称：DelayUs
 * 功能：    短延时函数 --16M-4T--大概快1%左右.
 * 输入参数：Time 延时时间长度 延时时长Time Us
 * 返回参数：无 
 ----------------------------------------------------*/
void DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
		NOP();
	}
}                  
/*---------------------------------------------------- 
 * 函数名称：DelayMs
 * 功能：   短延时函数
 * 输入参数：Time 延时时间长度 延时时长Time ms
 * 返回参数：无 
 ----------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(98);     //快1%
		}
	}
}
/*----------------------------------------------------
 * 函数名称：DelayS
 * 功能：    短延时函数
 * 输入参数：Time 延时时间长度 延时时长Time S
 * 返回参数：无 
 ----------------------------------------------------*/
void DelayS(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<10;b++)
		{
		 	DelayMs(100); 	
		}
	}
}
/*-------------------------------------------------
 * 函数名: PA2_Level_Change_INITIAL
 * 功能：  PA端口(PA2)电平变化中断初始化
 * 输入：  无
 * 输出：  无
--------------------------------------------------*/
void PA2_Level_Change_INITIAL(void)
{
	TRISA2 =1; 				//设置PA2输入
	ReadAPin = PORTA;		//清PA电平变化中断
	PAIF =0;   				//清PA INT中断标志位
    IOCA2 =1;  				//使能PA2电平变化中断
	PAIE =1;   				//使能PA INT中断
}
/*-------------------------------------------------
 * 函数名: main 
 * 功能：  主函数
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();					//系统初始化
	while(1)
	{
		for(FCount=0;FCount<100;FCount++)//输出100次波形	
		{
			DemoPortOut = 1; 				
			DelayMs(10);  				//10ms 
			DemoPortOut = 0;
			DelayMs(10); 
		}
		PA2_Level_Change_INITIAL();		//初始化外部中断
		GIE = 1;						//开总中断
		SLEEP(); 						//睡眠
	}
}
