/* 文件名：TEST_61F02x_ADC.C
* 功能：   FT61F02x-ADC功能演示
* IC:      FT61F023 SOP16
* 晶振：   16M/2T                    
* 说明：   程序根据AN2(PA2)口的电压来调节PWM3P(PC4)的占空比
*		   AN2脚电压越高(0-VDD)PWM3(PC2)占空比越大(2K,0-99%)	
*
*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|--------AN2
*  NC----------|5(PC3)  (PA3)12|---------NC
*  NC----------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  NC----------|8(PC5)  (PC4)09|-------PWM3
*			    ---------------
*/
#include "SYSCFG.h"
//*************************宏定义***************************
#define  unchar     unsigned char 
#define  unint      unsigned int

//PWM引脚输入输出控制
#define  PWM3Dir  	TRISC4

volatile unint    	TestADC;
/*-------------------------------------------------
* 函数名：POWER_INITIAL
* 功能：  上电系统初始化
* 输入：  无
* 输出：  无
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{ 
    OSCCON = 0B01110001;			//IRCF=111=16MHz/2T=8MHz,0.125us
	INTCON = 0;  					//暂禁止所有中断
    
	PORTA = 0B00000000;		
	TRISA = 0B00000100;				//PA输入输出 1-输入 0-输出
									//PA2-输入
	PORTC = 0B00000000; 	
	TRISC = 0B00000000;				//PC输入输出 1-输入 0-输出
	WPUA = 0;          				//禁止所有PA口上拉
	WPUC = 0;       				//禁止所有PC口上拉
    
	OPTION = 0B00001000;			//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1
    MSCKCON = 0B00000000;
    //Bit6:	0-禁止PA4，PC5稳压输出
	//Bit5:	0-TIMER2时钟为Fosc
	//Bit4:	0-禁止LVR       
	CMCON0 = 0B00000111; 			//关闭比较器，CxIN为数字IO口
}
/*------------------------------------------------- 
* 函数名：DelayUs
* 功能：  短延时函数 --16M-2T--大概快1%左右.
* 输入：  Time 延时时间长度 延时时长Time Us
* 输出：  无 
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
* 函数名: ADC_INITIAL
* 功能：  ADC初始化
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void ADC_INITIAL (void) 
{
	ADCON1 = 0B01100000;
    //DIVS=0,时钟选FOSC
	//ADCS[2:0]=110,分频FOSC/64
    
	ADCON0 = 0B10001001;
    //Bit7:		ADFM=1,结果右对齐                     
	//Bit[6:5]: VCFG参考电压
    //			00-参考电压VDD
	//			01-参考电压内部2V
    //			10-参考电压内部3V
	//			11-参考电压Vref
	//Bit[4:2]:	CHS=010-选择AN2通道
	//Bit1:		GO,AD转换状态位
	//Bit0:		ADON=1,ADC使能
	ANSEL = 0B00000100;   			//使能AN2为模拟输入	
}                      
/*-------------------------------------------------
* 函数名: GET_ADC_DATA
* 功能：  读取通道ADC值
* 输入：  AN_CN 通道序号
* 输出：  INT类型AD值(单次采样无滤波)
 --------------------------------------------------*/
unint GET_ADC_DATA (unchar AN_CH) 
{ 
	unchar	i;
	unchar	ADCON0Buff; 
	unint	tBuffer = 0;
	unint	ADC_DATA=0;
	 
	ADCON0Buff = ADCON0 & 0B11100011;//清空通道值

	AN_CH <<=2;              
	ADCON0Buff |=  AN_CH;   		//Bit[4:2]:CHS=010,选择AN2通道      

	ADCON0 = ADCON0Buff; 			//重新加载通道值
    DelayUs(20); 
	GO_DONE = 1;             		//启动ADC 
	while( GO_DONE==1 );    		//等待ADC转换完成

	ADC_DATA =  ADRESH;
	ADC_DATA <<=8;
	ADC_DATA |= ADRESL;      		//10Bit ADC值整合
	tBuffer =  ADC_DATA;
	return  tBuffer;
} 
/*-------------------------------------------------
* 函数名：PWM_INITIAL
* 功能：  PWM初始化
* 设置周期 = 2^TMRxPS*2^Nbit*TPxCK
*		   = 2^0*2^8*[(T3CKDIV+1)/16000000]
*		   = 1*256*[(30+1)/16000000] = 0.496ms
* 设置脉宽 = 2TMRxPS*(PRx)*TPxCK
*		   = 2^0*128*[(T3CKDIV+1)/16000000]
*		   = 1*128*[(30+1)/16000000] = 0.248ms
 --------------------------------------------------*/
void PWM_INITIAL (void) 
{
	PWM3Dir =1; 					//PWM3输出PIN暂为输入模式

	PWM3CR0 = 0B00110010;
    //Bit7:		中断选择位 0-计数器溢出时产生中断
	//Bit[6:4]:	周期位选择 011-8位
	//Bit[3:1]:	时钟选择   001-内部RC快时钟/(T3CKDIV+1)
	//Bit0:		PWM/BUZZER选择 0-PWM 输出
	PWM3CR1 = 0B10000000;
	//Bit7:		1-TMR3为PWM/BUZZER模式
	//Bit6:		0-PWM3为高电平有效
	//Bit[5:3]:	000-PWM3预分频比设置为1:1
	//Bit2:		0-暂关TMR3
	//Bit1:		0-禁止TMR3中断
	//Bit0:		0-TMR3中断标志位只读
	TMR3H=0;
	T3CKDIV = 30;
	PR3L = 128;						//占空比 50%
}
/*-------------------------------------------------
* 函数名:  main
* 功能：  主函数
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();		        //系统初始化
	ADC_INITIAL();			        //ADC初始化	
	PWM_INITIAL();					//PWM初始化
	TMR3ON = 1;				        //T3开启PWM3
	PWM3Dir = 0; 			        //PWM3 PIN设为输出模式允许PWM输出
	while(1)
	{
		TestADC = GET_ADC_DATA(2); 	//通道2AD值
		PR3L =  TestADC >> 2; 		//将AD值赋值给PWM的PR3L调节PWM3P输出的占空比
							
		NOP();
		NOP();	 
	}
}
