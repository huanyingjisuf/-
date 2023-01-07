/* 文件名：TEST_61F02x_EE.C
* 功能：   FT61F02x-内部EE功能演示
* IC:      FT61F023 SOP16
* 晶振：   16M /2T                    
* 说明：   此演示程序为61F02x EERROM的演示程序.
*		   该程序读取0x12地址的值,取反后存入0x13地址.
*
*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|---------NC
*  NC----------|5(PC3)  (PA3)12|---------NC
*  NC----------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  NC----------|8(PC5)  (PC4)09|---------NC
*			    ---------------
*/
//*********************************************************
#include "SYSCFG.h"
//***********************宏定义****************************
#define 	unchar     	unsigned char

unchar 		EEReadData; 
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
	TRISA = 0B00000000;		//PA全部为输出
	PORTC = 0B00000000; 	
	TRISC = 0B00000000;		//PC全部为输出
	WPUA = 0;          		//禁止所有PA口上拉
	WPUC = 0;       		//禁止所有PC口上拉
    
	OPTION = 0B00001000;	//Bit3=1 WDT MODE,PS=000=1:1 WDT RATE
	MSCKCON = 0B00000000;
    //Bit6->0,禁止PA4，PC5稳压输出
	//Bit5->0,TIMER2时钟为Fosc
	//Bit4->0,禁止LVR       
	CMCON0 = 0B00000111; 	//关闭比较器，CxIN为数字IO口
} 
/*----------------------------------------------------
* 函数名：EEPROMread
* 功能：  读EEPROM数据
* 输入：  EEAddr 需读取数据的地址
* 输出：  ReEEPROMread 对应地址读出的数据
 ----------------------------------------------------*/
unchar EEPROMread(unchar EEAddr)
{
	unchar ReEEPROMread;

	EEADR = EEAddr;    
	RD = 1;
	ReEEPROMread = EEDAT;     //EEPROM的读数据 ReEEPROMread = EEDATA;
	return ReEEPROMread;
}

/*---------------------------------------------------- 
* 函数名：EEPROMwrite
* 功能：  写数据到EEPROM
* 输入：  EEAddr 需要写入数据的地址
*         Data 需要写入的数据
* 输出：  无
 ----------------------------------------------------*/
void EEPROMwrite(unchar EEAddr,unchar Data)
{
	GIE = 0;				//写数据必须关闭中断
	while(GIE); 			//等待GIE为0
	EEADR = EEAddr; 	 	//EEPROM的地址
	EEDAT = Data;		 	//EEPROM的写数据  EEDATA = Data;
	EEIF = 0;
	EECON1 = 0x34;			//置位WREN1,WREN2,WREN3三个变量.
	WR = 1;					//置位WR启动编程
	while(WR);      		//等待EE写入完成
	GIE = 1;
}
/*-------------------------------------------------
* 函数名：main
* 功能：  主函数
* 输入：  无
* 输出：  无
 --------------------------------------------------*/
void main()
{
	POWER_INITIAL();				//系统初始化
	EEPROMwrite(0xff,0xaa);	
	EEPROMwrite(0xff,0xaa);			//在未使用到的随意一个地址写两次0xAA
 
	EEReadData = EEPROMread(0x12); 	//读取0x12地址EEPROM值 
	EEPROMwrite(0x13,~EEReadData); 	//取反写入地址0x13
	while(1)
	{
		NOP();
	}
}