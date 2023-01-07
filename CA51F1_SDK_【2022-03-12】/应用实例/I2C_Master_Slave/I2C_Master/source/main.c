#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"
#include "include/i2c.h"
#include "include/uart.h"
#include "include/delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
//  本例程为I2C主机从机通信的主机程序，主机读取20字节数据。  
//   ____________            _____________ 
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |  CA51F1(M) |          | CA51F1(S)   |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
/*********************************************************************************************************************/
#define I2C_ADDR		0xCA		//定义I2C从机地址
/*********************************************************************************************************************/
unsigned char idata ReadBuffer[20];
void main(void)
{	
	unsigned char i;

#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//设置LVD复位电压为2.7V
#endif

#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//初始化UART
#endif
	
	EA = 1;							//开全局中断

#ifdef PRINT_EN
	uart_printf("I2C Master Demo Code\n");
#endif

/**********I2C端口初始化************************************************************/
 	P30F = P30_I2C_SDA_SETTING | PU_EN;		 //设置P30作为I2C_SDA,并打开上位
 	P31F = P31_I2C_SCL_SETTING | PU_EN;		 //设置P31作为I2C_SCL,并打开上位

/***************************************************************************************/

	I2CCON = I2CE(1) | I2CIE(0) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(1);		
	I2CADR = GCE(0);		
	I2CCR = 0x69;					//设置I2C时钟
	
	while(1)
	{
		I2CCON |= STA(1);			//I2C主机发送START信号
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		
		if(I2CSTA != 0x08)				
		{
			I2CFLG |= I2CF;
			goto SEND_STOP;
		}
		I2CDAT = I2C_ADDR;			//主机发送从机地址+写位
		I2CFLG |= I2CF;				//清除中断标志
		
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x18)
		{
			I2CFLG |= I2CF;
			goto SEND_STOP;
		}		
		
		I2CDAT = 0;					//主机发送数据寄存器地址
		I2CFLG |= I2CF;				//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x28)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CCON |= STA(1);			//I2C主机发送START信号
		I2CFLG  |= I2CF;			//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x08)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CDAT = I2C_ADDR+1;		//主机发送从机地址+读位
		I2CFLG  |= I2CF;			//清除中断标志
		while(!(I2CFLG & I2CF));	//等待中断标志产生
		if(I2CSTA != 0x40)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		I2CCON |= AAK(1);			//设置应答位
			
		for(i = 0; i < 20; i++)		
		{
			I2CFLG  |= I2CF;		//清除中断标志
			while(!(I2CFLG & I2CF));//等待中断标志产生	
			if((I2CSTA != 0x28)&&(I2CSTA != 0x30))
			{
				I2CFLG  |= I2CF;
				goto SEND_STOP;
			}
			ReadBuffer[i] = I2CDAT;	//读取数据到数据寄存器

			if(i == 18)
			{
				I2CCON &= ~AAK(1);	
			}
			else
			{
				I2CCON |= AAK(1);	
			}			
		}
SEND_STOP:
		I2CCON |= STP(1);			//发送STOP信号
		I2CFLG  |= I2CF;
		
		
		Delay_ms(100);
	}
}
#endif
