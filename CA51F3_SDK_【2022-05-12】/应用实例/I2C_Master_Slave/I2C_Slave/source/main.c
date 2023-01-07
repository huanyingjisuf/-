
#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f_config.h"		
#include "include/ca51f3sfr.h"
#include "include/ca51f3xsfr.h"
#include "include/gpiodef_f3.h"
#include "include/system_clock.h"

#include "include/uart.h"
#include "include/i2c.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/

//  本例程为I2C主机从机通信的从机程序。
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |  CA51F3(M) |          | CA51F3(S)   |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
/*********************************************************************************************************************/
#define I2C_ADDR		0xCA		//定义I2C从机地址
/*********************************************************************************************************************/
unsigned char I2CDataIndex;
unsigned char regAddr;
bit iicReadMode;
unsigned char xdata Buffer[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};//设置数据寄存器初值为0~19
void INT6_ISR(void) interrupt 11 
{
	unsigned char Sta_Temp;

	if(I2CFLG & I2CF)					 			//IIC  interrupt
	{						
		Sta_Temp = I2CSTA;			
		if(Sta_Temp == 0x60)			    //接收到从机地址+写位
		{			
			I2CDataIndex = 0xFF;				//设置为0xFF表示后面接收到的第一个字节为地址
			iicReadMode = 0;						//设置为从机接收状态
			I2CCON |= AAK(1);			
		}
		else if(Sta_Temp == 0x80)			//发送或接收一字节数据，已检测到应答信号
		{					
			if(iicReadMode)	 						//发送一字节数据
			{
				I2CDataIndex++;
				I2CDAT = Buffer[I2CDataIndex + regAddr];			//把数据装载到发送寄存器，等待主机读取
			}
			else												//接收到一字节数据
			{				
				if(I2CDataIndex == 0xFF) 	//地址
				{
					regAddr = I2CDAT;	 																//接收到的第一个字节认为是地址
			   		I2CDataIndex = 0;																	//设置索引值为0
					I2CCON |= AAK(1);
				}
				else				   						//数据
				{
					Buffer[I2CDataIndex + regAddr] = I2CDAT;		//接收到的数据装载到数据寄存器	
					I2CDataIndex++;																		//索引值累加
					I2CCON |= AAK(1);		
				}
			}	
		}
		else if(Sta_Temp==0xA8)				//接收到从机地址+读位，发送ACK信号
		{								
			I2CDAT = Buffer[I2CDataIndex + regAddr];		//把数据装载到发送寄存器，等待主机读取
			iicReadMode = 1;						//设置为从机发送状态
		}
		else if(Sta_Temp == 0x88)			//发送或接收一字节数据，已检测到应答信号
		{
		}
		I2CFLG  |= I2CF;					//清除中断标志
	}	
}				
void main(void)
{
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//设置系统时钟为PLL，PLL_Multiple为倍频倍数
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//初始化UART1
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("I2C Slave Demo Code\n");
#endif

	

/**********选择I2C端口************************************************************/
// 	I2CIOS = 0;
// 	P30F = P30_I2C_SDA_SETTING | PU_EN;
// 	P31F = P31_I2C_SCL_SETTING | PU_EN;		

	I2CIOS = 1;
	P11F = P11_I2C_SDA_SETTING | PU_EN;
	P12F = P12_I2C_SCL_SETTING | PU_EN;		
//以上两组端口二选一
/***************************************************************************************/


	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(0);		
	I2CADR = GCE(0)|(I2C_ADDR>>1);		//设置I2C从机地址
	I2CCCR = 0x20;										//设置I2C时钟采样时钟
	INT6EN = 1;	 											//I2C中断开启

	while(1)
	{

	}
}
#endif
