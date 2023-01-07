//********************************************************* 
/* 文件名: TEST_60F01x_IR_Receive.c
* 功能：   FT60F01x 红外接收功能演示
* IC:      FT60F011A SOP8
* 晶振：   16M/4T                    
* 说明：   演示程序中,IR红外是采用6122协议，起始信号是9ms低电平，到4.5ms高电平，再到低8位
*          用户识别码，到高8位的用户识别码，8位数据码，8位数据码的反码。RXIO（PA4）每次收到
*          遥控器发过来的数据后，如果数据合法（两对补码，不对内容判断），LED(PA2)开关状态就
*		   改变一次。
*		   
*                    FT60F011A  SOP8 
*                   ----------------
*  VDD-------------|1(VDD)    (GND)8|------------GND     
*  LED-------------|2(PA2)    (PA4)7|-----------IRIO 
*  NC--------------|3(PA1)    (PA5)6|-------------NC
*  NC--------------|4(PA3)    (PA0)5|-------------NC
*			        ----------------
*/
//*********************************************************
#include	"SYSCFG.h";
#include 	"FT60F01X.h";
//*******************宏定义********************************
#define  uchar     unsigned char 

#define  IRRIO		PA4  	//IR的接收脚
#define  LED		PA2		//LED指示灯的IO

uchar IRbitNum = 0;		    //用于记录接收到第几位数据了
uchar IRbitTime = 0;		//用于计时一位的时间长短
uchar IRDataTimer[4];		//存出来的4个数据
uchar bitdata=0x01;			//用于按位或的位数据
uchar ReceiveFinish = 0;	//用于记录接收完成
uchar ReadAPin = 0;			//用于读取IO口状态，电平变化中断标志清除
/*-------------------------------------------------
 *  函数名: POWER_INITIAL 
 *	功能：  初始化设置
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void POWER_INITIAL(void)
{
	OSCCON = 0B01110000;				//IRCF=111=16MHz/4T=4MHz,0.25us                           
	INTCON = 0;  						//暂禁止所有中断
	OPTION = 0B00001000;				//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1

	PORTA = 0B00000000;					
	TRISA = 0B00010000;				    //PA输入输出 0-输出 1-输入
                                        //PA4-IN PA2-OUT
	WPUA = 0B00000000;     			    //PA端口上拉控制 1-开上拉 0-关上拉
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
    //Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后)  
}
/*----------------------------------------------------
 *	函数名：TIMER0_INITIAL
 *	功能：  初始化设置定时器
 *	设置TMR0定时时长=1/系统时钟频率*4*预分频值*140
 *                  =(1/16000000)*4*16*140=560us	                      
 ----------------------------------------------------*/
void TIMER0_INITIAL (void)  
{
	OPTION = 0B00000011;                  //时钟源为指令时钟，预分频比为1:16
	//Bit5:     T0CS Timer0时钟源选择 
	//          1-外部引脚电平变化T0CKI 0-内部时钟(FOSC/4)
	//Bit4:     T0SE T0CKI引脚触发方式 1-下降沿 0-上升沿
	//Bit3:     PSA 预分频器分配位 0-Timer0 1-WDT 
	//Bit[2:0]: PS 8位预分频比 011 - 1:16
    
	TMR0 = 118; 
	T0IF = 0;				              //清空T0软件中断标志位
}
/*-------------------------------------------------
 *  函数名: PA_Level_Change_INITIAL
 *	功能：  PA端口(PA4)电平变化中断初始化
 *  输入：  无
 *  输出：  无
--------------------------------------------------*/
void PA_Level_Change_INITIAL(void)
{
	TRISA4=1; 					 //设置PA4为输入
	ReadAPin=PORTA;				 //清PA电平变化中断
	PAIF=0;   					 //清PA_INT中断标志位
    IOCA4=1;  					 //使能PA4电平变化中断
	PAIE=1;   					 //使能PA_INT中断
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
	if(T0IE && T0IF)
	{
		TMR0 = 118;                 //注意:对TMR0重新赋值TMR0在两个周期内不变化
		 
		T0IF = 0;
        IRbitTime++;
        if(IRbitTime > 50)
        {
        	T0IE = 0;
            IRbitTime = 0;
        }
	} 
    
    //PA电平变化中断
	if(PAIE && PAIF)		
    {
		ReadAPin = PORTA; 				//读取PORTA数据清PAIF标志
		PAIF = 0; 
        if(IRRIO == 0)
        {
        	T0IE = 1;
        	if(IRbitTime > 21)
            {
            	IRDataTimer[0] = 0;
                IRDataTimer[1] = 0;
                IRDataTimer[2] = 0;
                IRDataTimer[3] = 0;
                IRbitNum = 0;
                bitdata = 0x00;
            }
            else if(IRbitTime > 3)
            {
            	IRDataTimer[IRbitNum-1] |= bitdata;
            }
            IRbitTime = 0;
            bitdata<<=1;
            if(bitdata == 0)
            {
            	bitdata = 0x01;
                IRbitNum++;
            }
            if(IRbitNum > 4)
            {
            	IRbitNum = 0;
                T0IE = 0;  
                ReceiveFinish = 1;		
            }

        }
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
	uchar rdata1,rdata2;
	POWER_INITIAL();
    TIMER0_INITIAL();
    PA_Level_Change_INITIAL();
    GIE = 1; 						//开中断
    T0IE = 1;						//开定时器/计数器0中断
    while(1)
    {
		if(ReceiveFinish)
        {
        	ReceiveFinish = 0;
            rdata1 = 0xFF - IRDataTimer[0];
            rdata2 = 0xFF - IRDataTimer[2];
            if((rdata1 == IRDataTimer[1])&&(rdata2 == IRDataTimer[3]))
            {
            	LED = ~LED; 		//翻转电平
            }
        }
    }
}