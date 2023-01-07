//********************************************************* 
/*  文件名：TEST_60F01x_EE.c
*	功能：  FT60F011A-EE功能演示
*   IC:     FT60F011A SOP8
*   晶振：  16M/4T                    
*   说明：  此演示程序为60F01x EERROM的演示程序.
*		    该程序读取0x12地址的值,取反后存入0x13地址.
*
*                  FT60F011A  SOP8 
*                 ----------------
*  VDD-----------|1(VDD)    (GND)8|------------GND     
*  NC------------|2(PA2)    (PA4)7|-------------NC 
*  NC------------|3(PA1)    (PA5)6|-------------NC
*  NC------------|4(PA3)    (PA0)5|-------------NC
*			      ----------------
*/	
	    
//*********************************************************
#include "SYSCFG.h"
//*********************************************************
#define unchar  unsigned char
unchar EEReadData; 
 /*-------------------------------------------------
 *  函数名：POWER_INITIAL
 *	功能：  上电系统初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{ 
    OSCCON = 0B01110000;				//IRCF=111=16MHz/4T=4MHz,0.25us
                                 
	INTCON = 0;  						//暂禁止所有中断
	OPTION = 0B00001000;				//Bit3=1,WDT MODE,PS=000=WDT RATE 1:1
	PORTA  = 0B00000000;					
	TRISA  = 0B00000000;				//PA输入输出 0-输出 1-输入
	WPUA   = 0B00000000;     			//PA端口上拉控制 1-开上拉 0-关上拉								
					 		
	MSCKCON = 0B00000000;
	//Bit4=0,禁止LVR(60F01x O版之前)       
	//Bit4=0,LVREN使能时,开启LVR(60F01x O版及O版之后)  
	//Bit4=1,LVREN使能时,工作时开启LVR,睡眠时自动关闭LVR(60F01x O版及O版后) 
}
/*-------------------------------------------------
 * 	函数名称：EEPROMread
 * 	功能：    读EEPROM数据
 * 	输入参数：EEAddr 需读取数据的地址
 * 	返回参数；ReEEPROMread 对应地址读出的数据
 -------------------------------------------------*/
unchar EEPROMread(unchar EEAddr)
{
	unchar ReEEPROMread;
	EEADR = EEAddr;    
	RD = 1;
	ReEEPROMread = EEDAT;     			//EEPROM的读数据 ReEEPROMread = EEDATA;
	return ReEEPROMread;
}
/*-------------------------------------------------
 * 	函数名称：EEPROMwrite
 * 	功能：    写数据到EEPROM
 * 	输入参数：EEAddr 需要写入数据的地址
 *            Data 需要写入的数据
 * 	返回参数：无
 -------------------------------------------------*/
void EEPROMwrite(unchar EEAddr,unchar Data)
{
	GIE = 0;							//写数据必须关闭中断
	while(GIE); 						//等待GIE为0
	EEADR = EEAddr; 	 				//EEPROM的地址
	EEDAT = Data;		 				//EEPROM的写数据  EEDATA = Data;
	EEIF = 0;
	EECON1|= 0x34;						//置位WREN1,WREN2,WREN3三个变量.
	WR = 1;								//置位WR启动编程
	while(WR);      					//等待EE写入完成
	GIE = 1;                            //开总中断
}
/*-------------------------------------------------
 *  函数名：main
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();					//系统初始化
 	EEPROMwrite(0xFF,0xAA);	
	EEPROMwrite(0xFF,0xAA);				//在未使用到的随意一个地址写两次0xAA
 
	EEReadData = EEPROMread(0x12); 		//读取0x12地址EEPROM值 
	EEPROMwrite(0x13,~EEReadData); 		//取反写入地址0x13
    
	while(1) 
	{
		NOP();
	}
}
