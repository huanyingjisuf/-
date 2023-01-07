//********************************************************* 
/*  文件名：TEST_60F01x_UART.c
*	功能：  FT60F01x-UART 功能演示
*   IC:     FT60F011A SOP8
*   晶振：  16M/4T                    
*   说明：  演示程序中波特率为9600，RXIO（PA2）每次收到外部串口发过来的数据后，TXIO(PA4)
*		    把收到的数据再发送出去。接收起始位时是用电平变化中断识别，后面关闭电平变化中断。
*
*                    FT60F011A  SOP8 
*                   ----------------
*  VDD-------------|1(VDD)    (GND)8|------------GND     
*  RXIO------------|2(PA2)    (PA4)7|-----------TXIO 
*  NC--------------|3(PA1)    (PA5)6|-------------NC
*  NC--------------|4(PA3)    (PA0)5|-------------NC
*			        ----------------
*/
//*********************************************************
#include	"SYSCFG.h";
#include 	"FT60F01X.h";
//********************宏定义******************************
#define  uchar      unsigned char 

#define  TXIO		PA4  	//串口的发送脚
#define  RXIO		PA2  	//串口的接收脚

#define  Bord		49 		//通过定时器提供波特率
uchar    RXFLAG = 0;
uchar    ReadAPin;
/*-------------------------------------------------
 *  函数名: POWER_INITIAL
 *	功能：  MCU初始化函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void POWER_INITIAL(void)
{
	OSCCON = 0B01110000;	//IRCF=111=16MHz/4T=4MHz，0.25us
	INTCON = 0;  			//暂禁止所有中断
	PORTA = 0B00000000;		
	TRISA = 0B00000100;		//PA输入输出 0-输出 1-输入
                            //PA4-OUT	PA2-IN
	WPUA = 0B00000100;     	//PA端口上拉控制 1-开上拉 0-关上拉
                            //PA2开上拉
	OPTION = 0B00001000;	//Bit3=1，WDT MODE，PS=000=WDT RATE 1:1
	MSCKCON = 0B00000000;
	//Bit4->0,禁止LVR(60F01x O版之前)
	//Bit4->0,LVREN使能时,开启LVR(60F01x O版及O版后)  
	//Bit4->1,LVREN使能时,工作时开启LVR, 睡眠时自动关闭LVR(60F01x O版及O版之后)  
}
/*----------------------------------------------------
 *	函数名：TIMER0_INITIAL
 *	功能：  初始化设置定时器
 *	设置TMR0定时时长=1/系统时钟频率*4*预分频值*208
                    =(1/16000000)*4*2*208=104us	                      
 ----------------------------------------------------*/
void TIMER0_INITIAL (void)  
{
	OPTION = 0B00000000;    //时钟源为指令时钟，预分频比为1:256
	//Bit5:     T0CS Timer0时钟源选择 
	//          1-外部引脚电平变化T0CKI 0-内部时钟(FOSC/4)
	//Bit4:     T0SE T0CKI引脚触发方式 1-下降沿 0-上升沿
	//Bit3:     PSA 预分频器分配位 0-Timer0 1-WDT 
	//Bit[2:0]: PS 8位预分频比 000 - 1:2
	TMR0 = Bord; 
    T0IF = 0;				//清空T0软件中断
}
/*-------------------------------------------------
 *  函数名: PA2_Level_Change_INITIAL
 *	功能：  PA端口(PA2)电平变化中断初始化
 *  输入：  无
 *  输出：  无
--------------------------------------------------*/
void PA2_Level_Change_INITIAL(void)
{
	TRISA2 =1; 				//设置PA2为输入
	ReadAPin = PORTA;		//清PA电平变化中断
	PAIF =0;   				//清PA_INT中断标志位
    IOCA2 =1;  				//使能PA2电平变化中断
	PAIE =1;   				//使能PA_INT中断
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
	if(T0IE && T0IF)		//104us
	{
		TMR0 = Bord;		//注意:对TMR0重新赋值TMR0在两个周期内不变化
		T0IF = 0;
        T0IE = 0;
	} 
    
    //PA电平变化中断
	if(PAIE && PAIF)		
    {
		ReadAPin = PORTA; 	//读取PORTA数据清PAIF标志
		PAIF = 0;  			//清PAIF标志位
		if(RXIO == 0)
        {
        	PAIE = 0;  		//暂先禁止PA电平变化中断
			IOCA2 =0;  		//禁止PA2电平变化中断
            RXFLAG = 1;
        } 
    }
} 
/*-------------------------------------------------
 *  函数名： WaitTF0
 *	功能：  查询定时器溢出后，在中断里关闭定时器后，再次打开定时器
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void WaitTF0( void )
{
     while(T0IE);
     T0IE=1;
}
/*-------------------------------------------------
 *  函数名：WByte
 *	功能：  UART发送一个字节
 *  输入：  input
 *  输出：  无
 --------------------------------------------------*/

void WByte(uchar input)
{
	                        //发送起始位
	uchar i=8;
	TXIO = 1;
	TMR0 = Bord;
	T0IE = 1;  
	WaitTF0(); 
	TXIO=0;
	WaitTF0();
	                        //发送8位数据位
	while(i--)
	{
		if(input&0x01) 		//先传低位
		{
			TXIO=1;
		}
		else
		{
			TXIO = 0;
		}    
		WaitTF0();
		input=input>>1;
	}
	                        //发送校验位(无)
	                        //发送结束位
	TXIO=(bit)1;
	T0IE=0;
} 
/*-------------------------------------------------
 *  函数名：RByte
 *	功能：  UART接收一个字节
 *  输入：  无
 *  输出：  Output
 --------------------------------------------------*/
uchar RByte()
{
	uchar Output=0;
	uchar i=8;
	T0IE=1;                 //启动Timer0
	TMR0 = Bord;
	WaitTF0();
	T0IE=1;                 //启动Timer0
	TMR0 = Bord;
	WaitTF0();              //等过起始位
	                        //发送8位数据位
	while(i--)
	{
		Output >>=1;
		if(RXIO) 
        {
        	Output|=0x80;   //先收低位
        }
		WaitTF0();          //位间延时
	}
	T0IE=0;                 //停止Timer0
	return Output;
}
/*-------------------------------------------------
 *  函数名： main
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main(void)
{
	uchar rdata = 0;
	POWER_INITIAL();
    TIMER0_INITIAL();
    PA2_Level_Change_INITIAL();
    GIE = 1; 				//开中断
	T0IE = 1;				//开定时器/计数器0中断
    while(1)
    {

        if(RXFLAG)			//外部中断下降沿触发了
        {
        	rdata = RByte();
            WByte(rdata);
        
            IOCA2 =1;  		//使能PA2电平变化中断
			PAIE =1;   		//使能PA INT中断
            RXFLAG = 0;
        }
    }
}