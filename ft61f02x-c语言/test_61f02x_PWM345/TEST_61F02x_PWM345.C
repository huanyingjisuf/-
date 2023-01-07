/* 文件名：TEST_61F02x_PWM345.C
* 功能：   FT61F02x-增强型PWM功能演示
* IC：     FT61F023 SOP16
* 晶振：   16M/2T                    
* 说明：   此程序用来演示PWM345功能
*		   演示程序中在PWM345脚分别输出2KHz,1KHz,500Hz
*		   占空比的为50%的信号
*
*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|---------NC
*  PWM4--------|5(PC3)  (PA3)12|---------NC
*  PWM5--------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  NC----------|8(PC5)  (PC4)09|-------PWM3
*			    ---------------
*/
#include "SYSCFG.h"
//********************宏定义***************************
//PWM引脚输入输出控制
#define	PWM3Dir	TRISC4
#define	PWM4Dir	TRISC3
#define	PWM5Dir	TRISC2
/*-------------------------------------------------
* 函数名：interrupt
* 功能：  中断处理
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void interrupt ISR(void)	
{
	NOP();
}
/*-------------------------------------------------
* 函数名：POWER_INITIAL
* 功能：  上电系统初始化
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void POWER_INITIAL (void) 
{
	OSCCON = 0B01110001;	//IRCF=111=16MHz/2=8MHz,0.125us
	INTCON = 0;  			//暂禁止所有中断
	PORTA = 0B00000000; 
	TRISA = 0B00000000; 	//PA输入输出 1-输入 0-输出
	PORTC = 0B00000000; 
	TRISC = 0B00000000;		//PC输入输出 1-输入 0-输出

	WPUA = 0B00000000;    	//禁止所有PA口上拉
	WPUC = 0B00000000;    	//禁止所有PC口上拉
	OPTION = 0B00001000;	//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1
    MSCKCON = 0B00000000;
    //Bit6->0,禁止PA4，PC5稳压输出
	//Bit5->0,TIMER2时钟为Fosc
	//Bit4->0,禁止LVR       
	CMCON0 = 0B00000111; 	//关闭比较器，CxIN为数字IO口
}
/*-------------------------------------------------
* 函数名：PWM_INITIAL
* 功能：  PWM3,4,5初始化
* 设置PWM3周期=2^TMRXPS*2^PXPER*[(T3CKDIV+1)/PWM时钟源]
* 			=2^0*2^8*[(30+1)/16000000]=496us
* 	PWM4周期=2^TMRXPS*2^PXPER*[(T4CKDIV+1)/PWM时钟源]
* 			=2^0*2^8*[(62+1)/16000000]=1.008ms
* 	PWM5周期=2^TMRXPS*2^PXPER*[(T5CKDIV+1)/PWM时钟源]
* 			=2^0*2^8*[(124+1)/16000000]=2ms
 --------------------------------------------------*/
void PWM_INITIAL (void) 
{
	PWM3Dir = 1;	//PWM3输出PIN暂为输入模式
	PWM4Dir = 1;	//PWM4输出PIN暂为输入模式
	PWM5Dir = 1;	//PWM5输出PIN暂为输入模式
	//-------------PWM3---------------
	PWM3CR0 = 0B00110010;
    //Bit7: 	禁止中断
	//Bit[6:4]: 周期位选择 011-8位
	//Bit[3:1]: 时钟选择 001-内部RC快时钟/(T3CKDIV+1)
	//Bit0: 	PWM 输出							
	PWM3CR1 = 0B10000000;
	//Bit7: 	1-TMR3为PWM/BUZZER模式
	//Bit6:		0-PWM3为高电平有效
	//Bit[5:3]: 000-PWM3预分频比设置为1:1
	//Bit2: 	0-暂关TMR3
	//Bit1: 	0-禁止TMR3中断
	//Bit0: 	0-TMR3中断标志位只读	               		
	TMR3H=0;
	T3CKDIV = 30;	//赋值 T3CKDIV
	PR3L = 128;
	//-------------PWM4---------------
	PWM4CR0 = 0B00110010;
    //Bit7:     禁止中断
	//Bit[6:4]: 周期位选择 011-8位
	//Bit[3:1]: 时钟选择001-内部RC快时钟/(T4CKDIV+1)
	//Bit0:	    PWM 输出							
	PWM4CR1 = 0B10000000;
	//Bit7:     1-TMR4为PWM/BUZZER模式
	//Bit6:     0-PWM4为高电平有效
	//Bit[5:3]: 000-PWM4预分频比设置为1:1
	//Bit2:     0-暂关TMR4
	//Bit1:     0-禁止TMR4中断
	//Bit0:     0-TMR4中断标志位只读
    TMR4H=0;
	T4CKDIV = 62;	//赋值 T4CKDIV
	PR4L = 128;
	//------------PWM5--------------
	PWM5CR0 = 0B00110010; 
    //Bit7:		禁止中断
    //Bit[6:4]: 周期位选择 011-8位
    //Bit[3:1]: 时钟选择001-内部RC快时钟/(T5CKDIV+1)
    //Bit0:		PWM 输出
	PWM5CR1 = 0B10000000;
    //Bit7:     1-TMR5为PWM/BUZZER模式
    //Bit6:     0-PWM5为高电平有效
    //Bit[5:3]: 000-PWM5预分频比设置为1:1
    //Bit2:     0-暂关TMR5
    //Bit1:     0-禁止TMR5中断
    //Bit0:     0-TMR5中断标志位只读
    TMR5H=0;
	T5CKDIV = 124;	//赋值 T5CKDIV
	PR5L = 128;
}
/*-------------------------------------------------
* 函数名：main
* 功能：  主函数
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void main(void)
{	
	POWER_INITIAL(); 
	PWM_INITIAL();

	TMR3ON=1;
	TMR4ON=1;
	TMR5ON=1;
	PWM3Dir = 0;	//PWM3 PIN设为输出模式允许PWM输出
	PWM4Dir = 0;	//PWM4 PIN设为输出模式允许PWM输出
	PWM5Dir = 0;	//PWM5 PIN设为输出模式允许PWM输出
	while(1)
	{	
		NOP();
	}
}