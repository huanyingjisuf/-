//********************************************************* 
/* 文件名：TEST_60F01x_IIC.c
* 功能：   FT60F01x IIC功能演示
* IC:      FT60F011A SOP8 
* 晶振：   16M/4T                    
* 说明：   此演示程序为60F01x_IIC的演示程序.
*		   该程序读取(24C02)0x12地址的值,取反后存入0x13地址 
*
*                  FT60F011A  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  IIC_SDA-------|2(PA2)    (PA4)7|--------IIC_SCL 
*  NC------------|3(PA1)    (PA5)6|-------------NC
*  NC------------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
//***********************宏定义*****************************
#define  unchar     unsigned char 

#define  IIC_SCL	PA4   
#define  IIC_SDA	PA2

#define  SDA_OUT    TRISA2 =0
#define  SDA_IN	    TRISA2 =1

unchar IICReadData;

 /*-------------------------------------------------
 * 函数名： POWER_INITIAL
 * 功能：  上电系统初始化
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{
    OSCCON = 0B01110000;				//IRCF=111=16MHz/4T=4MHz,0.25us
                                 
	INTCON = 0;  						//暂禁止所有中断
	OPTION = 0B00001000;				//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1

	PORTA = 0B00000000;					
	TRISA = 0B00000000;					//PA输入输出 0-输出 1-输入
                                        //PA4-输出
	WPUA = 0B00000000;     				//PA端口上拉控制 1-开上拉 0-关上拉								
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
    //Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后)  
}
/*-------------------------------------------------
 * 函数名：DelayUs
 * 功能：  短延时函数 --16M-4T--大概快1%左右.
 * 输入：  Time 延时时间长度 延时时长Time*2 Us
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
 * 函数名：IIC_Start
 * 功能：  产生IIC起始信号
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT;          //SDA线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	DelayUs(10);      
 	IIC_SDA=0;        //start:当CLK为高时，DATA由高变低 
	DelayUs(10);
	IIC_SCL=0;        //钳住I2C总线，准备发送或接收数据 
    DelayUs(10);
}	  
/*-------------------------------------------------
 * 函数名：IIC_Stop
 * 功能：  产生IIC停止信号
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
 void IIC_Stop(void)
{
	SDA_OUT;          //SDA线输出
	IIC_SCL=0;
	IIC_SDA=0;        //stop:当CLK为高时，DATA由低变高
 	DelayUs(10);
	IIC_SCL=1; 
    DelayUs(10);
	IIC_SDA=1;        //发送I2C总线结束信号
	DelayUs(10);							   	
}
/*-------------------------------------------------
 * 函数名：IIC_Wait_Ack
 * 功能：  等待应答信号到来
 * 输入：  无
 * 输出：  返回值：1，接收应答失败
 *                 0，接收应答成功
 --------------------------------------------------*/
unsigned char IIC_Wait_Ack(void)
{
	unsigned char ucErrTime=0;      
	SDA_IN;               //SDA设置为输入  
	IIC_SDA=1;
	DelayUs(5);	   
	IIC_SCL=1;
	DelayUs(5);	 
	while(IIC_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250) //等待超时
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;            //时钟输出0 	   
	return 0;  
} 
/*-------------------------------------------------
 * 函数名：IIC_Ack
 * 功能：  产生ACK应答
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT;              //SDA线输出
	IIC_SDA=0;
	DelayUs(5);	
	IIC_SCL=1;
	DelayUs(5);	
	IIC_SCL=0;
}
/*-------------------------------------------------
 * 函数名：IIC_NAck
 * 功能：  不产生ACK应答
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/	    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT;              //SDA线输出
	IIC_SDA=1;
	DelayUs(5);	
	IIC_SCL=1;
	DelayUs(5);	
	IIC_SCL=0;
}					 				     
/*-------------------------------------------------
 * 函数名：IIC_Send_Byte
 * 功能：  IIC发送一个字节
 * 输入：  写入要发送的一个人字节数据txd
 * 输出：  无
 --------------------------------------------------*/		  
void IIC_Send_Byte(unsigned char txd)
{                        
    unsigned char t;   
	SDA_OUT;	          //SDA线输出   
    IIC_SCL=0;            //拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		DelayUs(5);				  
		IIC_SCL=1;
		DelayUs(5);	
		IIC_SCL=0;	
		DelayUs(5);
    }	 
} 	    
/*-------------------------------------------------
 * 函数名：IIC_Read_Byte
 * 功能：  IIC读一个字节
 * 输入：  无
 * 输出：  读出存储器里面的数据并返回receive
 --------------------------------------------------*/
 unsigned char IIC_Read_Byte(void)
{
	unsigned char i,receive=0;
	SDA_IN;               //SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        DelayUs(5);	
     	IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;   
		DelayUs(5);	
    }					 
    IIC_NAck();           //发送nACK
  
    return receive;
}
/*-------------------------------------------------
 * 函数名：IIC_READ
 * 功能：  IIC读出制定位置的数据
 * 输入：  address
 * 输出：  读出address存储器里面的数据iicdata
 --------------------------------------------------*/
 unsigned char IIC_READ(unsigned char address)
{
	unsigned char iicdata = 0;
	IIC_READ_Begin:
		IIC_Start();
		IIC_Send_Byte(0xa0);
		if(IIC_Wait_Ack())goto IIC_READ_Begin;
		IIC_Send_Byte(address);				    //填要读的数据地址
		if(IIC_Wait_Ack())goto IIC_READ_Begin; 
		IIC_Start();
		IIC_Send_Byte(0xa1);
		if(IIC_Wait_Ack())goto IIC_READ_Begin;
		iicdata=IIC_Read_Byte();
		IIC_Stop();		
		return iicdata;
}
 /*-------------------------------------------------
 * 函数名：IIC_WRITE
 * 功能：  IIC把数据data写入制定的位置address
 * 输入：  address，data
 * 输出：  无
 --------------------------------------------------*/
void IIC_WRITE(unsigned char address,unsigned char data)
	{
	IIC_WRITE_Begin:
		IIC_Start();
		IIC_Send_Byte(0xa0);
		if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

		IIC_Send_Byte(address);
		if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

		IIC_Send_Byte(data);
		if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

		IIC_Stop();	
	}

/*-------------------------------------------------
 * 函数名:  main 
 * 功能：  主函数
 * 输入：  无
 * 输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();				    //系统初始化

	IICReadData = IIC_READ(0x12); 		//读取0x12地址EEPROM值 
	IIC_WRITE(0x13,~IICReadData); 		//取反写入地址0x13
	while(1)
	{
    	NOP();
	}
}
	
