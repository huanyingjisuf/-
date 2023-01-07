//********************************************************* 
/* 文件名：TEST_60F01x_IR_Send.c
* 功能：   FT60F01x-红外发射 功能演示
*  IC:     FT60F011A SOP8
* 晶振：   16M/4T                  
* 说明：   演示程序中,IR红外是采用6122协议，起始信号是9ms低电平，到4.5ms高电平，再到低
*          8位用户识别码，到高8位的用户识别码，8位数据码，8位数据码的反码。SendIO（PA4）
*          定时（5秒钟）发送一次，接收端收到遥控器发过来的数据后，校验数据互为补码，LED会开关。
*		   
*                    FT60F011A  SOP8 
*                   ----------------
*  VDD-------------|1(VDD)    (GND)8|------------GND     
*  NC--------------|2(PA2)    (PA4)7|---------SendIO 
*  NC--------------|3(PA1)    (PA5)6|-------------NC
*  NC--------------|4(PA3)    (PA0)5|-------------NC
*			        ----------------
*/
//*********************************************************
#include	"SYSCFG.h";
#include 	"FT60F01X.h";
//*******************宏定义********************************
#define uchar			unsigned char 
#define uint			unsigned int
#define IRSendIO		PA4  				//串口的发送脚

#define IRSend_HIGH_1   1  					//560uS
#define IRSend_LOW_1    3 					//1680uS

#define IRSend_HIGH_0   1  					//560uS
#define IRSend_LOW_0    1  					//560uS

#define IRSend_PIN_1    T0IE = 1  			//发送数据 开启定时器0
#define IRSend_PIN_0    T0IE = 0 			//关闭定时器0

#define Status_NOSend	0			        //不发送的状态
#define Status_Head		1			        //发送引导码的状态
#define Status_Data		2			        //发送数据的状态

uchar  IRSendStatus;						//发送状态，是发送引导码还是数据
uchar  IRSendData;							//发送的数据中转变量
uchar  TxBit=0,TxTime=0; 
uchar  Sendbit = 0;
uchar  level0,level1;						//一位数据里发送与关闭的时间值
bit    SendLastBit = 0;
uchar  SaveLastBit = 0;
uint   SYSTime5S = 0;						//系统时间，5S发送一次

uchar  IRData[4] = {0x00,0xff,0x40,0xBf};	//需要发送的4个数据
/*-------------------------------------------------
 *  函数名：POWER_INITIAL
 *	功能：  系统初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void POWER_INITIAL(void)
{
	OSCCON = 0B01110000;				//IRCF=111=16MHz/4T=4MHz,0.25us                           
	INTCON = 0;  						//暂禁止所有中断
	OPTION = 0B00001000;				//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1

	PORTA = 0B00000000;					
	TRISA = 0B00000000;				    //PA输入输出 0-输出 1-输入
                                        //PA4-输出
	WPUA = 0B00000000;     			    //PA端口上拉控制 1-开上拉 0-关上拉						
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
    //Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后)
}
/*----------------------------------------------------
 *	函数名：TIMER0_INITIAL
 *	功能：  初始化设置定时器0
 *  说明：  38KHz发生器，1000000/38000=26.3uS .由于定时太短，频繁进定时器，时间有一定的
 *          误差，239并不是直接算出来的，是用示波器看的。
 *	设置TMR0定时时长=1/系统时钟频率*4*预分频值*26
                    =(1/16000000)*4*2*26=13us 	                      
 ----------------------------------------------------*/
void TIMER0_INITIAL (void)  
{
	OPTION = 0B00000000;    //时钟源为指令时钟，预分频比为1:2
	//Bit5:     T0CS Timer0时钟源选择 
	//          1-外部引脚电平变化T0CKI 0-内部时钟(FOSC/4)
	//Bit4:     T0SE T0CKI引脚触发方式 1-下降沿 0-上升沿
	//Bit3:     PSA 预分频器分配位 0-Timer0 1-WDT 
	//Bit[2:0]: PS 8位预分频比 000 - 1:2
	TMR0 = 239; 
    T0IF = 0;				//清空T0软件中断
}
/*-------------------------------------------------
 * 函数名称：TIMER2_INITIAL
 * 功能：初始化设置定时器1 
 * 设置TMR2定时时长=1/系统时钟频率*4*预分频值*后分频值*PR2
                   =(1/16000000)*4*4*4*140=560us 
 -------------------------------------------------*/
void TIMER2_INITIAL (void) 
{
	T2CON = 0B00011001;     	
    //Bit[6:3]: 定时器2后分频比  0011-1:4
    //Bit2:     定时器2使能位    0-关闭 1-使能
	//Bit[1:0]: 定时器2预分频比  01-1:4 
	TMR2 = 0;  				//TMR2赋初值
	PR2 = 140;
	
	TMR2IF = 0;				//清TMER2中断标志
	TMR2IE = 1;				//使能TMER2的中断
	TMR2ON = 1;				//使能TMER2启动
	PEIE=1;    				//使能外设中断
}
/*-------------------------------------------------
 *  函数名：SendCtrl
 *	功能：  发送数据函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void SendCtrl(void)
{

	if (IRSendStatus == Status_NOSend)			//不发送的状态
	{        
		IRSend_PIN_0;
        Sendbit = 0;
		TxTime = 0;   
	}	 
	else if (IRSendStatus == Status_Head)		//发送引导码
	{
    	TxTime++;
		if (TxTime < 17)   						//发送9mS信号
		{
			IRSend_PIN_1;
		}
        else if (TxTime < 24)   				//4.5mS不发送
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
	else if(IRSendStatus == Status_Data)		 //发送数据
	{
		if (IRSendData & TxBit)  				 //1，是1:3的时间
		{
			level1 = IRSend_HIGH_1;
			level0 = IRSend_LOW_1;
            
		}
		else									 //0，是1:1的时间
		{
			level1 = IRSend_HIGH_0;
			level0 = IRSend_LOW_0;
		}
		TxTime++;
		if (TxTime <= level1)  					 //发送信号
		{
			IRSend_PIN_1;
		}
		else if (TxTime <= (level0+level1)) 	//不发送信号
		{
			IRSend_PIN_0;
		}
		else if (Sendbit < 4)					 //发送4位数据未完成
		{
			TxTime = 1;
            IRSend_PIN_1;
            SaveLastBit = IRSendData & TxBit;
			TxBit <<= 1;
			if (TxBit == 0x00)  				 //发送完一个字节
			{
				TxBit = 0x01;
                Sendbit++;
                IRSendData = IRData[Sendbit];
				if (Sendbit > 3)   				 //最后一位要注意，因为发送完了还要有一个脉冲
				{
                    SendLastBit = 1;
				}
			}
		}
        else									 //数据完成了，要补脉冲
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
	//定时器0的中断处理
	if(T0IE && T0IF)				//13us
	{
		TMR0 = 239;					//注意:对TMR0重新赋值TMR0在两个周期内不变化	 
		T0IF = 0;    
		IRSendIO = ~IRSendIO; 		//翻转电平产生38KHz信号
	} 
    
    //定时器2的中断处理
	if(TMR2IE && TMR2IF)			//560us中断一次 红外每一位都是560us的倍数
	{
		TMR2IF = 0;
        SendCtrl();
        SYSTime5S++;
        IRSendIO = 0;
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
    TIMER2_INITIAL();
    GIE = 1; 							//开中断
    while(1)
    {
		if(SYSTime5S >10000)			//定时5S
        {
        	SYSTime5S = 0;
            IRSendStatus = Status_Head;
        }

    }
}