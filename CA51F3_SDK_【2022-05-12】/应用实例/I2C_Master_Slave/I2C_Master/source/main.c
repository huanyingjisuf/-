
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
//  本例程为I2C主机从机通信的主机程序，主机读取20字节数据。  
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
#define DATA_LEN		20
unsigned char xdata ReadBuffer[DATA_LEN];

void main(void)
{
	unsigned char i=0;
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
	uart_printf("I2C Master Demo Code\n");
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


	I2CCON = I2CE(1) | I2CIE(0) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(1);		
	I2CADR = GCE(0);		
	I2CCCR = 0x29;							//设置I2C时钟
	
	while(1)
	{
// 		Uart0_PutChar(0xaa);
		I2CCON |= STA(1);					//I2C主机发送START信号
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		
		if(I2CSTA != 0x08)				
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		I2CDAT = I2C_ADDR;				//主机发送从机地址+写位
		I2CFLG  |= I2CF;					//清除中断标志
		
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x18)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}		
		
		I2CDAT = 0;								//主机发送数据寄存器地址
		I2CFLG  |= I2CF;					//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x28)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CCON |= STA(1);					//I2C主机发送START信号
		I2CFLG  |= I2CF;					//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x08)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CDAT = I2C_ADDR+1;			//主机发送从机地址+读位
		I2CFLG  |= I2CF;					//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x40)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
#if (DATA_LEN == 1)		//读取单字节
		I2CCON &= ~AAK(1);
		I2CFLG  |= I2CF;					//清除中断标志
		while(!(I2CFLG & I2CF));			//等待中断标志产生	
		ReadBuffer[0] = I2CDAT;				//读取数据到数据寄存器
//		Uart0_PutChar(ReadBuffer[0]);		
#else					//连续读取多字节
		I2CCON |= AAK(1);					//设置应答位
		for(i = 0; i < DATA_LEN; i++)		
		{
			I2CFLG  |= I2CF;				//清除中断标志
			while(!(I2CFLG & I2CF));//等待中断标志产生	
			if((I2CSTA != 0x28)&&(I2CSTA != 0x30))
			{
				I2CFLG  |= I2CF;
				goto SEND_STOP;
			}
			ReadBuffer[i] = I2CDAT;			//读取数据到数据寄存器
// 			Uart0_PutChar(ReadBuffer[i]);
			if(i == (DATA_LEN - 2))
			{									
				I2CCON &= ~AAK(1);			//读最后一字节，不发送ACK
			}	
			else
			{					
				I2CCON |= AAK(1);			//如果不是最后一字节，预设ACK状态	
			}	
		}
#endif
SEND_STOP:
		I2CCON |= STP(1);				//发送STOP信号
		I2CFLG  |= I2CF;
		
		
		Delay_ms(100);
	}
}
#endif
