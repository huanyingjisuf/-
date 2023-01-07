//********************************************************* 
/* 文件名: TEST_62F08x_USART.c
* 功能：   FT62F08x-USART功能演示
* IC:      FT62F088 LQFP32
* 内部：   16M
* empno:   500                                
* 说明：   串口上电发送10个字符，然后等待接收10个字节数据（通过串口助手发送接收）
*
*   参考原理图 TEST_62F08x_sch.pdf
*/
//*********************************************************
#include "SYSCFG.h"
//***********************宏定义****************************
#define  unchar     unsigned char 

#define  DemoPortOut	PB3   
#define  DemoPortIn		PC3

volatile  unchar 	receivedata[10] = 0;
volatile  unchar 	senddata = 0;

volatile  unchar    toSend[11]={0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x0d,0x0a};
unchar    i=0;
unchar    mmm=0;
/*-------------------------------------------------
 * 函数名：interrupt ISR
 * 功能：  中断处理
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void interrupt ISR(void)            
{ 
	if(URRXNE && RXNEF)       //接收中断         	
	{
    	receivedata[mmm++] = URDATAL; 
        
        if(mmm>=10)
        {
        	mmm=0;
        } 
        NOP();
	} 
    //----------------------------
    if(TCEN && TCF)          //发送中断
    {	
        TCF=1;       		 //写1清0
        
    	if(i<10)
        {
    		URDATAL =toSend[i++];
        }
        else
        {
          i=0;
        }
		NOP();
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
	OSCCON = 0B01110001;	//IRCF=111=16MHz
	INTCON = 0;  			//暂禁止所有中断
    
	PORTA = 0B00000000;		
	TRISA = 0B00000000;		//PA输入输出 0-输出 1-输入
	PORTB = 0B00000000;		
	TRISB = 0B00000000;		//PB输入输出 0-输出 1-输入	PB3-OUT						
	PORTC = 0B00000000; 	
	TRISC = 0B00001000;		//PC输入输出 0-输出 1-输入  PC3-IN
    PORTD = 0B00000000;		
	TRISD = 0B00000000;		//PD输入输出 0-输出 1-输入
	
	WPUA = 0B00000000;     	//PA端口上拉控制 1-开上拉 0-关上拉
	WPUB = 0B00000000;     	//PB端口上拉控制 1-开上拉 0-关上拉
	WPUC = 0B00001000;     	//PC端口上拉控制 1-开上拉 0-关上拉
	WPUD = 0B00000000;     	//PD端口上拉控制 1-开上拉 0-关上拉
    
    WPDA = 0B00000000;     	//PA端口下拉控制 1-开下拉 0-关下拉
	WPDB = 0B00000000;     	//PB端口下拉控制 1-开下拉 0-关下拉
	WPDC = 0B00000000;     	//PC端口下拉控制 1-开下拉 0-关下拉
	WPDD = 0B00000000;     	//PD端口下拉控制 1-开下拉 0-关下拉
    
    PSRC0 = 0B11111111;  	//PORTA,PORTB源电流设置最大
    PSRC1 = 0B11111111;    	//PORTC,PORTD源电流设置最大    
    
    PSINK0 = 0B11111111;  	//PORTA灌电流设置最大 0:最小，1:最大
    PSINK1 = 0B11111111; 	//PORTB灌电流设置最大 0:最小，1:最大
    PSINK2 = 0B11111111;	//PORTC灌电流设置最大 0:最小，1:最大
    PSINK3 = 0B11111111;	//PORTD灌电流设置最大 0:最小，1:最大
	
    ANSELA = 0B00000000;    //全为数字管脚
}
/*------------------------------------------------- 
 * 函数名：DelayUs
 * 功能：  短延时函数 --16M-2T--大概快1%左右.
 * 输入：  Time延时时间长度 延时时长Time Us
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
 * 函数名：DelayMs
 * 功能：  短延时函数
 * 输入：  Time延时时间长度 延时时长Time ms
 * 输出：  无 
 * 输出：  无 
 -------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(197); //快1%
		}
	}
}
/*-------------------------------------------------
 * 函数名: UART_INITIAL
 * 功能：  主函数
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void UART_INITIAL(void)
{
	PCKEN |= 0B00100000; //打开UART时钟
    
    URIER = 0B00100001;  //使能发送接收完成中断
    URLCR = 0B00000001;  //8位数据，停止位1，无奇偶校验
    URMCR = 0B00011000;
    
    URDLL = 104;         //9600波特率 = Fosc/16*[URDLH:URDLL]
    URDLH = 0;
    TCF=1;
	INTCON=0B11000000;
}
/*-------------------------------------------------
 * 函数名: main 
 * 功能：  主函数
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void main(void)
{
	POWER_INITIAL();		//系统初始化
    UART_INITIAL();
    DelayMs(100);
    
    if(TXEF)                //上电发送10+1个数据
    {
      URDATAL =0x41;        
    }

	while(1)
	{
		NOP();
   	}
}
