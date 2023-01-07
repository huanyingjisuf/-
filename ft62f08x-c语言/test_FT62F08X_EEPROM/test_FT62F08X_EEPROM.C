//********************************************************* 
/* 文件名：TEST_62F08x_EEPROM.c
* 功能：   FT62F08x-EEPROM功能演示
* IC:      FT62F088 LQFP32
* 内部：   16M
* empno:   500                                  
* 说明：   此演示程序为62F08x_EEPROM的演示程序.
*		   把0x55写入地址0x13,再读出该值
*
*		
*	参考原理图 TEST_62F08x_sch.pdf
*/  
//*********************************************************
#include "SYSCFG.h"
//************************宏定义***************************
#define	 unchar	 unsigned char 

volatile	unchar	EEReadData; 
/*-------------------------------------------------
 *  函数名： interrupt ISR
 *	功能：  中断处理，包括定时器0中断和外部中断
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void interrupt ISR(void)            	
{ 

}
/*-------------------------------------------------
 *  函数名：POWER_INITIAL
 *	功能：  上电系统初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{ 
	OSCCON = 0B01110001;	//IRCF=111=16MHz/2
	INTCON = 0;  			//暂禁止所有中断
    
	PORTA = 0B00000000;		
	TRISA = 0B00000000;		//PA输入输出 0-输出 1-输入
	PORTB = 0B00000000;		
	TRISB = 0B00000000;		//PB输入输出 0-输出 1-输入							
	PORTC = 0B00000000; 	
	TRISC = 0B00000000;		//PC输入输出 0-输出 1-输入  	
    PORTD = 0B00000000;		
	TRISD = 0B00000000;		//PD输入输出 0-输出 1-输入
	
	WPUA = 0B00000000;     	//PA端口上拉控制 1-开上拉 0-关上拉
	WPUB = 0B00000000;     	//PB端口上拉控制 1-开上拉 0-关上拉
	WPUC = 0B00000000;     	//PC端口上拉控制 1-开上拉 0-关上拉
	WPUD = 0B00000000;     	//PD端口上拉控制 1-开上拉 0-关上拉
    
    WPDA = 0B00000000;     	//PA端口上拉控制 1-开下拉 0-关下拉
	WPDB = 0B00000000;     	//PB端口上拉控制 1-开下拉 0-关下拉
	WPDC = 0B00000000;     	//PC端口上拉控制 1-开下拉 0-关下拉
	WPDD = 0B00000000;     	//PD端口上拉控制 1-开下拉 0-关下拉
    
    PSRC0 = 0B11111111;  	//PORTA,PORTB源电流设置最大
    PSRC1 = 0B11111111;		//PORTC,PORTD源电流设置最大    
    
    PSINK0 = 0B11111111;  	//PORTA灌电流设置最大 0:最小，1:最大
    PSINK1 = 0B11111111; 	//PORTB灌电流设置最大 0:最小，1:最大
    PSINK2 = 0B11111111;	//PORTC灌电流设置最大 0:最小，1:最大
    PSINK3 = 0B11111111;	//PORTD灌电流设置最大 0:最小，1:最大
	
    ANSELA = 0B00000000;    //全为数字管脚
}
/*----------------------------------------------------
 *	函数名：EEPROMread
 *	功能：  读EEPROM数据
 *	输入：  EEAddr 需读取数据的地址
 *  返回；  ReEEPROMread 对应地址读出的数据
 ----------------------------------------------------*/
unchar EEPROMread(unchar EEAddr)
{
	unchar ReEEPROMread;
	while(GIE)	           //等待GIE为0
	{
          GIE = 0;         //读数据必须关闭中断
          NOP();               
          NOP();            
	}				
    DRDEN=1;    
    NOP();
    NOP();      
   	EEADRL = EEAddr;
   
    CFGS = 0;
    EEPGD = 0; 
   	RD = 1;
    
	ReEEPROMread = EEDATL; 
    DRDEN=0;    	
	return ReEEPROMread;
}
/*-------------------------------------------------
 *  函数名：Unlock_Flash
 *	功能：  进行FLASH/EEDATA操作时，解锁FLASH/EEDATA的时序不能被打断。
 *			程序中要将此段用汇编指令处理防止被优化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void Unlock_Flash()
{
#asm
    MOVLW    0x03
    MOVWF    _BSREG
    MOVLW    0x55
    MOVWF    _EECON2 & 0x7F
    MOVLW    0xAA
    MOVWF    _EECON2 & 0x7F
    BSF		_EECON1 & 0x7F,1  		//WR=1;
    NOP
    NOP
#endasm
}
/*---------------------------------------------------- 
 *	函数名：EEPROMwrite
 *	功能：  写数据到EEPROM
 *	输入：  EEAddr 需要写入数据的地址
 *	        Data 需要写入的数据
 *	返回：  无
 ----------------------------------------------------*/
void EEPROMwrite(unchar EEAddr,unchar Data)
{
	while(GIE)	           			//等待GIE为0
	{
		GIE = 0;            		//写数据必须关闭中断
		NOP();               
		NOP();            
	}				
	EEADRL = EEAddr; 	 			//EEPROM的地址
	EEDATL = Data;		 			//EEPROM的写数据  
      
    CFGS =0;                        //访问EEPROM存储器
    EEPGD=0;                        //
    WREN=1;                         //写使能
    EEIF = 0;
    
    Unlock_Flash();        			//Flash 解锁时序不能修改       
    NOP();
    NOP();
    NOP();
    NOP();
    
   	while(WR);      				//等待EE写入完成
    WREN=0;
	GIE = 1;
}

/*-------------------------------------------------
 *  函数名：main
 *	功能：  主函数
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void main(void)
{
	POWER_INITIAL();				//系统初始化
    
	EEPROMwrite(0x13,0x55); 		//0x55写入地址0x13
	EEReadData = EEPROMread(0x13); 	//读取0x13地址EEPROM值 
    
   	while(1) 
	{
		NOP();
	}
}