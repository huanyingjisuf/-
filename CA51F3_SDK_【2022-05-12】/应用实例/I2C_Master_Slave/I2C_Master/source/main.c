
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
//  ������ΪI2C�����ӻ�ͨ�ŵ���������������ȡ20�ֽ����ݡ�  
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
#define I2C_ADDR		0xCA		//����I2C�ӻ���ַ
/*********************************************************************************************************************/
#define DATA_LEN		20
unsigned char xdata ReadBuffer[DATA_LEN];

void main(void)
{
	unsigned char i=0;
#if (SYSCLK_SRC == PLL)
	Sys_Clk_Set_PLL(PLL_Multiple);	//����ϵͳʱ��ΪPLL��PLL_MultipleΪ��Ƶ����
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//��ʼ��UART0
#endif
	
#ifdef UART1_EN
	Uart1_Initial(UART1_BAUTRATE);	//��ʼ��UART1
#endif

	EA = 1;													//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("I2C Master Demo Code\n");
#endif

	

/**********ѡ��I2C�˿�************************************************************/
// 	I2CIOS = 0;
// 	P30F = P30_I2C_SDA_SETTING | PU_EN;
// 	P31F = P31_I2C_SCL_SETTING | PU_EN;		

	I2CIOS = 1;
	P11F = P11_I2C_SDA_SETTING | PU_EN;
	P12F = P12_I2C_SCL_SETTING | PU_EN;		
//��������˿ڶ�ѡһ
/***************************************************************************************/


	I2CCON = I2CE(1) | I2CIE(0) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(1);		
	I2CADR = GCE(0);		
	I2CCCR = 0x29;							//����I2Cʱ��
	
	while(1)
	{
// 		Uart0_PutChar(0xaa);
		I2CCON |= STA(1);					//I2C��������START�ź�
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		
		if(I2CSTA != 0x08)				
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		I2CDAT = I2C_ADDR;				//�������ʹӻ���ַ+дλ
		I2CFLG  |= I2CF;					//����жϱ�־
		
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x18)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}		
		
		I2CDAT = 0;								//�����������ݼĴ�����ַ
		I2CFLG  |= I2CF;					//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x28)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CCON |= STA(1);					//I2C��������START�ź�
		I2CFLG  |= I2CF;					//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x08)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CDAT = I2C_ADDR+1;			//�������ʹӻ���ַ+��λ
		I2CFLG  |= I2CF;					//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x40)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
#if (DATA_LEN == 1)		//��ȡ���ֽ�
		I2CCON &= ~AAK(1);
		I2CFLG  |= I2CF;					//����жϱ�־
		while(!(I2CFLG & I2CF));			//�ȴ��жϱ�־����	
		ReadBuffer[0] = I2CDAT;				//��ȡ���ݵ����ݼĴ���
//		Uart0_PutChar(ReadBuffer[0]);		
#else					//������ȡ���ֽ�
		I2CCON |= AAK(1);					//����Ӧ��λ
		for(i = 0; i < DATA_LEN; i++)		
		{
			I2CFLG  |= I2CF;				//����жϱ�־
			while(!(I2CFLG & I2CF));//�ȴ��жϱ�־����	
			if((I2CSTA != 0x28)&&(I2CSTA != 0x30))
			{
				I2CFLG  |= I2CF;
				goto SEND_STOP;
			}
			ReadBuffer[i] = I2CDAT;			//��ȡ���ݵ����ݼĴ���
// 			Uart0_PutChar(ReadBuffer[i]);
			if(i == (DATA_LEN - 2))
			{									
				I2CCON &= ~AAK(1);			//�����һ�ֽڣ�������ACK
			}	
			else
			{					
				I2CCON |= AAK(1);			//����������һ�ֽڣ�Ԥ��ACK״̬	
			}	
		}
#endif
SEND_STOP:
		I2CCON |= STP(1);				//����STOP�ź�
		I2CFLG  |= I2CF;
		
		
		Delay_ms(100);
	}
}
#endif
