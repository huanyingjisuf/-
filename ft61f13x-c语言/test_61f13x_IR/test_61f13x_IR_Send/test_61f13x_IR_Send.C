//********************************************************* 
/*  文件名：TEST_61F13x_IR_Send.c
*	功能：  FT61F13x-红外发射 功能演示
*   IC:     FT61F135 SOP20
*   晶振：  16M/4T                 
*   说明：  演示程序中,IR红外是采用6122协议，起始信号是9ms低电平，到4.5ms高电平，再到低8位
*           用户识别码，到高8位的用户识别码，8位数据码，8位数据码的反码。SendIO（PA4）定时
*          （5秒钟）发送一次，接收端收到遥控器发过来的数据后，校验数据互为补码，LED会开关。
*		    
*                  FT61F135  SOP20
*                 ----------------
*  VDD-----------|1(VDD)   (VSS)20|-----------VSS     
*  NC------------|2(PC1)   (PA0)19|------------NC 
*  NC------------|3(PC0)   (PA1)18|------------NC
*  NC------------|4(PB7)   (PA2)17|------------NC
*  NC------------|5(PB6)   (PA3)16|------------NC
*  NC------------|6(PB5)   (PA4)15|------IRSendIO
*  NC------------|7(PB4)   (PA5)14|------------NC
*  NC------------|8(PB3)   (PA6)13|------------NC
*  NC------------|9(PB2)   (PA7)12|------------NC
*  NC------------|10(PB1)  (PB0)11|------------NC
*                 ----------------   
*/
//*********************************************************
#include	"SYSCFG.h"

// 宏定义
#define  uchar     unsigned char 
#define  uint      unsigned int
#define  ulong     unsigned long

#define  IRSendIO		PA4  					// 串口的发送脚

#define IRSend_HIGH_1   1  						// 560uS
#define IRSend_LOW_1    3 						// 1680uS

#define IRSend_HIGH_0   1  						// 560uS
#define IRSend_LOW_0    1  						// 560uS

#define IRSend_PIN_1   T0IE = 1  				// 发送数据 开启定时器0
#define IRSend_PIN_0   T0IE = 0 				// 关闭定时器0

#define Status_NOSend	0			            // 不发送的状态
#define Status_Head		1			            // 发送引导码的状态
#define Status_Data	    2			            // 发送数据的状态

uchar IRSendStatus;								// 发送状态，是发送引导码还是数据
uchar IRSendData;								// 发送的数据中转变量
uchar TxBit=0,TxTime=0; 
uchar Sendbit = 0;
uchar level0,level1;							// 一位数据里发送与关闭的时间值
bit   SendLastBit = 0;
uchar SaveLastBit = 0;
uint  SYSTime5S = 0;							// 系统时间，5S发送一次

uchar IRData[4] = {0x00,0xff,0x40,0xBf};		// 需要发送的4个数据
//===========================================================
//函数名：POWER_INITIAL
//功能：  初始化单片机
//输入：  无
//输出：  无
//===========================================================
void POWER_INITIAL(void)
{
	OSCCON = 0B01110001;	       //IRCF=111=16MHz/2T=8MHz，0.125us
    OPTION = 0B00001000;           //Bit3=1 WDT，Bit[2:0]=000=WDT RATE 1:1
	INTCON = 0;  			       //暂禁止所有中断
	PORTA  = 0B00000000;		
	TRISA  = 0B00000010;	       //PA输入输出 0-输出 1-输入
							       //PA4-OUT PA1-IN		
	PORTC  = 0B00000000; 	
	TRISC  = 0B00000000;	       //PC输入输出 0-输出 1-输入  
								
	WPUA   = 0B00000010;           //PA端口上拉控制 1-开上拉 0-关上拉
							       //开PA1上拉
	WPUC   = 0B00000000;           //PC端口上拉控制 1-开上拉 0-关上拉
}
/*----------------------------------------------------
 *	函数名：TIMER0_INITIAL
 *	功能：  初始化设置定时器0
 *  说明：  38KHz发生器，1000000/38000=26.3uS .由于定时太短，频繁进定时器，时间有一定的
 *          误差，239并不是直接算出来的， 是示波器看的。
 *	设置TMR0定时时长13us=(1/16000000)*4*2*26(16M-2T-PSA 1:16- TMR0=255溢出)	                      
 ----------------------------------------------------*/
void TIMER0_INITIAL (void)  
{
	OPTION = 0B00000000;    //Bit3=0 TMR0，Bit[2:0]=000=TMR0 RATE 1:2
	TMR0 = 239; 
    T0IF = 0;				//清空T0软件中断
}

//******************************************
//函数名：TIMER2_INITIAL
//功能：  初始化设置定时器2 配置成PWM
//输入：  无
//输出：  无
//******************************************
void Timer2Inital(void) 
{
	T2CON0  = 0B00011001; 	// TMR2预分频1:4  后分频1:4
    //Bit[6:3]=TOUTPS  后分频比	0000=1:1~1111=1:16
    //Bit2=TMR2ON	   1=TIMER2打开	0=关闭
    //Bit[1:0]=T2CKPS  预分频比 00=1:1 01=1:4 1x=1:16
    
	T2CON1  = 0B00000000;	//T2时钟来自指令时钟,PWM1连续模式
	//Bit4:     PWM模式选择 0-连续模式；1-单脉冲模式
    //Bit3:     0-PWM模式；1-蜂鸣器模式	
    //Bit[2:0]: Timer2时钟源选择：000-指令时钟；001-系统时钟；
    //          010-HIRC的2倍频；100-HIRC；101-LIRC
    						
    TMR2H  	= 0;			//定时器2计数寄存器
    TMR2L   = 141;
    
    
	PR2H    = 0; 			//周期=（PR+1）*Tt2ck*TMR2预分频
	PR2L    = 141;	  
    
    P1ADTH	= 0;			//脉宽=P1xDT*Tt2ck*TMR2预分频
    P1ADTL	= 50;
    
    P1OE=0B00000000;        // Bit7=P1C0OE	1=P1C0输出到PB2	 0=不输出
                            // Bit6=P1B0OE	1=P1B0输出到PA7	 0=不输出
                            // Bit5=P1A2NOE 1=P1A2N输出到PA0 0=不输出
                            // Bit4=P1A2OE	1=P1A2输出到PA1  0=不输出
                            // Bit3=P1A1NOE	1=P1A1N输出到PB6 0=不输出
                            // Bit2=P1A1OE	1=P1A1输出到PB5	 0=不输出
                            // Bit1=P1A0NOE	1=P1A0N输出到PB1 0=不输出
                            // Bit1=P1A0OE	1=P1A0输出到PA6	 0=不输出
                            
    P1CON=0B00000001;        //死区时间=Bit<6:0>*(1/Fosc)*2=1*(1/16000000)*2=0.125uS
    
    P1POL=0B00000000;       // Bit7=P1C0P输出极性	1=反向	 0=不反向
                            // Bit6=P1B0P输出极性	1=反向	 0=不反向
                            // Bit5=P1A2NP输出极性	1=反向	 0=不反向
                            // Bit4=P1A2P输出极性	1=反向	 0=不反向
                            // Bit3=P1A1NP输出极性	1=反向	 0=不反向
                            // Bit2=P1A1P输出极性	1=反向	 0=不反向
                            // Bit1=P1A0NP输出极性	1=反向	 0=不反向
                            // Bit1=P1A0P输出极性	1=反向	 0=不反向
     
				 			//设置TMR2输出比较值定时15us=(1/4000000)*60(PR2)
	TMR2IF  = 0;			//清TMER2中断标志
	TMR2IE  = 1;			//使能TMER2的中断（配置成timer定时器时不注释）
	TMR2ON  = 1;			//使能TMER2启动
	PEIE    = 1;    		//使能外设中断
	GIE     = 1;   			//使能全局中断
}
/*-------------------------------------------------
 *  函数名：SendCtrl
 *	功能：  发送数据函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void SendCtrl(void)
{

	if (IRSendStatus == Status_NOSend)			// 不发送的状态
	{        
		IRSend_PIN_0;
        Sendbit = 0;
		TxTime = 0;
        
	}	 
	else if (IRSendStatus == Status_Head)		// 发送引导码
	{
    	TxTime++;
		if (TxTime < 17)   						// 发送9mS信号
		{
			IRSend_PIN_1;
		}
        else if (TxTime < 24)   				// 4.5mS不发送
		{
			IRSend_PIN_0;
		}
		else
		{
			TxTime = 0;
            IRSendStatus = Status_Data;
		}
        IRSendData = IRData[0];
        TxBit = 0x01;
	}
	else if(IRSendStatus == Status_Data)		// 发送数据
	{
		if (IRSendData & TxBit)  				// 1，是1:3的时间
		{
			level1 = IRSend_HIGH_1;
			level0 = IRSend_LOW_1;
		}
		else									// 0，是1:1的时间
		{
			level1 = IRSend_HIGH_0;
			level0 = IRSend_LOW_0;
		}
		TxTime++;
		if (TxTime <= level1)  					// 发送信号
		{
			IRSend_PIN_1;
		}
		else if (TxTime <= (level0+level1)) 	// 不发送信号
		{
			IRSend_PIN_0;
		}
		else if (Sendbit < 4)					// 发送4位数据未完成
		{
			TxTime = 1;
            IRSend_PIN_1;
            SaveLastBit = IRSendData & TxBit;
			TxBit <<= 1;
			if (TxBit == 0x00)  				// 发送完一个字节
			{
				TxBit = 0x01;
                Sendbit++;
                IRSendData = IRData[Sendbit];
				if (Sendbit > 3)   				// 最后一位要注意，因为发送完了还要有一个脉冲
				{
                    SendLastBit = 1;
				}
			}
		}
        else									// 数据完成了，要补脉冲
        {
        	if(SendLastBit)
 		   	{
		    	TxTime++;
		    	if(SaveLastBit)
		        {
		        	if(TxTime < 3)
		            {
		            	IRSend_PIN_0;
		            }
		            else if(TxTime < 4)
		            {
		            	IRSend_PIN_1;
		            }
		            else
		            {
		            	IRSend_PIN_0;
						IRSendStatus = Status_NOSend;
		                IRSend_PIN_0;
		                SendLastBit = 0;
                        TxBit = 0;
                        TxTime = 0;
		            }
		        }
		        else
		        {
		        	if(TxTime < 5)
		            {
		            	IRSend_PIN_0;
		            }
		            else if(TxTime < 6)
		            {
		            	IRSend_PIN_1;
		            }
		            else
		            {
		            	IRSend_PIN_0;
						IRSendStatus = Status_NOSend;
		                IRSend_PIN_0;
		                SendLastBit = 0;
                        TxBit = 0;
                        TxTime = 0;
		            }
		        }
		    }
        }
	}
    
}
/*-------------------------------------------------
 *  函数名：interrupt ISR
 *	功能：  中断处理，包括定时器0中断和外部中断
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void interrupt ISR(void)			
{  
  //****************定时器0的中断处理**********************
	if(T0IE && T0IF)				//13us
	{
		TMR0 = 239;					//注意:对TMR0重新赋值TMR0在两个周期内不变化	 
		T0IF = 0;    
		IRSendIO = ~IRSendIO; 		//翻转电平  产生38KHz信号
       
	} 
    
    //**************定时器2的中断处理**********************
	if(TMR2IE && TMR2IF)			//560us中断一次 红外每一位都是560uS的倍数
	{
		TMR2IF = 0;
        SendCtrl();
        SYSTime5S++;
        
   	}
} 
/*-------------------------------------------------
 *  函数名：main
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main(void)
{
	POWER_INITIAL();
    TIMER0_INITIAL();
    Timer2Inital();
    GIE = 1; 							//开中断
    while(1)
    {
		if(SYSTime5S >10000)			//每隔5S发射一次
        {
        	SYSTime5S = 0;
            IRSendStatus = Status_Head;
        }
    }
}