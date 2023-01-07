/* 文件名：TEST_61F02x_PWM.C
* 功能：   FT61F02x-增强型PWM功能演示
* IC:      FT61F023 SOP16
* 晶振：   16M/2T                    
* 说明：   芯片工作在PWM增强模式下,P1A(PC5) 
*		   引脚均输出40kHz占空比渐增渐减的波形
*		   P1B,P1C,P1D,PWM引脚为普通I/O口
*
*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|---------NC
*  P1C---------|5(PC3)  (PA3)12|---------NC
*  P1D---------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  P1A---------|8(PC5)  (PC4)09|--------P1B
*			    ---------------
*/
//**********************************************************
#include "SYSCFG.h"
//************************宏定义****************************
#define  unchar     unsigned char 
#define  unint      unsigned int
//PWM引脚功能选择P1XOE 1-PWM输出 0-普通I/O口
#define  PWM_A_OE  P1AOE 
//PWM引脚输入输出控制
#define  P1ADir	   	TRISC5

volatile   unint    pwm_d=0;      //PWM脉冲宽度值
volatile   bit      SAFlag;       
/*-------------------------------------------------
* 函数名：interrupt ISR
* 功能：  中断函数
* 设置中断定时时长=设定值*指令周期
* 				  =16000*0.125uS=2000uS
 --------------------------------------------------*/
void interrupt ISR(void)
{
	if(TMR1IF)
	{
		TMR1IF = 0;
        
        //初值=65536-16000=49536=>0XC180
		TMR1L = 0X80;  		//赋初值=>TMR1H=0XC1;TMR1L=0X80
		TMR1H = 0XC1;  		    
	}
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
	TRISA = 0B00000000;		//PA输入输出 1-输入 0-输出 
	PORTC = 0B00000000;
	TRISC = 0B11111111; 	//PC输入输出 1-输入 0-输出

	WPUA = 0;          		//禁止所有PA口上拉
	WPUC = 0   ;       		//禁止所有PC口上拉
	OPTION = 0B00001000;	//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1
    MSCKCON = 0B00000000;
    //Bit6->0,禁止PA4，PC5稳压输出
	//Bit5->0,TIMER2时钟为Fosc
	//Bit4->0,禁止LVR       
	CMCON0 = 0B00000111; 	//关闭比较器，CxIN为数字IO口
}
/*-------------------------------------------------
* 函数名：TIMER1_INITIAL
* 功能：  定时器1初始化
* 设置定时时长=(1/系统时钟周期)*指令周期*预分频值*(65536-TMR1H:TMR1L)
* 			  =(1/16000000)*2*1*(65536-16000)=2000us
 --------------------------------------------------*/
void TIMER1_INITIAL (void) 
{
	//需要在中断里重新赋初始值
	T1CON = 0B00000000;
    //Bit[5:4]:	00-T2时钟分频 1:1
    //Bit2:	    0-Timer1使用内部时钟
	//Bit1:		0-T1时钟源选择内部时钟
	TMR1L = 0X80;  			//赋初值TMR1H=0XC1;TMR1L=0X80
	TMR1H = 0XC1;  			
	TMR1IE = 1;				//使能TMER1的中断
	TMR1ON = 1;				//使能TMER1启动
	PEIE=1;    				//使能外设中断
	GIE = 1;   				//使能全局中断
}
/*-------------------------------------------------
* 函数名：pwm_duty_count
* 功能：  将十位pwm_d的值赋值给CCPR1L:CCP1CON<5:4>
* 输入：  无
* 输出：  无
 --------------------------------------------------*/	
void pwm_duty_count (void)  
{    
	unint  lsb22;  
	unchar lsb23;            	     	   
	lsb22 = (unchar) pwm_d & 0B00000011;
	CCP1CON =  CCP1CON & 0B11001111;
	lsb22 <<= 4;
	lsb23 = (unchar)lsb22; 
	CCP1CON =  CCP1CON | lsb23; //赋值10Bit PWM脉冲宽度的低2位LSB
	lsb22 = pwm_d >> 2; 		//赋值10Bit PWM脉冲宽度的高8位MSB
	lsb23 = (unchar)lsb22; 
	CCPR1L = lsb23;  
}
/*-------------------------------------------------
* 函数名：PWM_INITIAL
* 功能：  PWM初始化
* 设置PWM周期 = (PR2+1)*2*(1/Fosc)*T2分频比值
* 			  = (199+1)*2*(1/16000000)*1 = 25us
* 	  PWM频率=1/PWM周期=1/25us=40kHz
 --------------------------------------------------*/
void PWM_INITIAL (unchar SET_PR2) 
{
	MSCKCON = 0B00000000;
    //Bit6->0,禁止PA4，PC5稳压输出
	//Bit5->0,TIMER2时钟为Fosc ; 1为TIMER2时钟为32MHZ
	//Bit4->0,禁止LVR  
	T2CON = 0B00000000;   		//Bit[1:0]=00, T2分频比为1:1
	PR2 = SET_PR2;				//设置PWM的周期
	CCP1CON = 0B10001101;
    //Bit(7:6)=00;  P1A单输出,P1B,P1C,P1D位普通I/O口
	//Bit(5:4)=00;  10Bit PWM占空比低2位
	//Bit(3:0)=1101;PWM模式，P1A高电平有效,P1B低电平有效

	pwm_duty_count();      		//PWM占空比计算 占空比pwm_d/((PR2+1)*4)

	PWM1CON = 0B10000001;
    //Bit7=1,自动关闭时PWM自动重启
	//死区时间=Bit<6:0>*(1/Fosc)*2
	//		  =1*(1/16000000)*2=0.125ns
	ECCPAS = 0B00001111;
    //Bit[6:4]=000,禁止自动关闭
	//Bit[3:2]=11, P1A,P1C关闭时为三态
	//Bit[1:0]=11, P1B,P1D关闭时为三态
	PWM1AUX = 0B10000000;
    //Bit7=1,使能PWM辅助功能
	//Bit6=0,使能PWM连续输出
	//Bit[5:2]=0011,P1C,P1D为半桥PWM输出
	//Bit[1:0]=11,P1A,P1B,P1E,P1F引脚为IO
	TMR2IF = 0;           		//清T2中断标志位  
}
/*----------------------------------------------------
* 函数名：DelayUs
* 功能：  短延时函数 --16M-2T--大概快1%左右.
* 输入：  Time 延时时间长度 延时时长Time μs
* 输出：  无 
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
* 函数名：DelayMs
* 功能：  短延时函数
* 输入：  Time 延时时间长度 延时时长Time ms
* 输出：  无
 ----------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(197);     //快1%
		}
	}
}
/*----------------------------------------------------
* 函数名：main
* 功能：  主函数
* 输入：  无
* 输出：  无
 ----------------------------------------------------*/
void main(void)
{
	POWER_INITIAL(); 
	TIMER1_INITIAL();    
	pwm_d = 10;             
	PWM_INITIAL(99);       	//Tpwm = (99+1)*2*(1/16000000)*1 = 25us = 40kHz	 
							//PWM阶数 = 4 * (99+1) = 400
	PWM_A_OE = 1;
    
	P1ADir = 0;
    
	TMR2ON = 1;             //使能开启T2 	
	SAFlag = 1;
	while(1)
	{
		if(SAFlag == 1) 	//PWM占空比增加
		{
			pwm_d++;
			if(pwm_d > 400)
			{
				 SAFlag = 0;
			}
		}
		else				//PWM占空比减小
		{
			pwm_d--;
			if(pwm_d == 0)
			{
				SAFlag = 1;
			}
		}
		pwm_duty_count(); 	//载入PWM占空比
		DelayMs(10);   		//10ms
	}
}