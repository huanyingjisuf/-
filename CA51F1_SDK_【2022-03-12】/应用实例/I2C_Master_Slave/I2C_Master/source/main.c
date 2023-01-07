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
//  ������ΪI2C�����ӻ�ͨ�ŵ���������������ȡ20�ֽ����ݡ�  
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
#define I2C_ADDR		0xCA		//����I2C�ӻ���ַ
/*********************************************************************************************************************/
unsigned char idata ReadBuffer[20];
void main(void)
{	
	unsigned char i;

#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//����LVD��λ��ѹΪ2.7V
#endif

#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);	//��ʼ��UART
#endif
	
	EA = 1;							//��ȫ���ж�

#ifdef PRINT_EN
	uart_printf("I2C Master Demo Code\n");
#endif

/**********I2C�˿ڳ�ʼ��************************************************************/
 	P30F = P30_I2C_SDA_SETTING | PU_EN;		 //����P30��ΪI2C_SDA,������λ
 	P31F = P31_I2C_SCL_SETTING | PU_EN;		 //����P31��ΪI2C_SCL,������λ

/***************************************************************************************/

	I2CCON = I2CE(1) | I2CIE(0) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(1);		
	I2CADR = GCE(0);		
	I2CCR = 0x69;					//����I2Cʱ��
	
	while(1)
	{
		I2CCON |= STA(1);			//I2C��������START�ź�
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		
		if(I2CSTA != 0x08)				
		{
			I2CFLG |= I2CF;
			goto SEND_STOP;
		}
		I2CDAT = I2C_ADDR;			//�������ʹӻ���ַ+дλ
		I2CFLG |= I2CF;				//����жϱ�־
		
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x18)
		{
			I2CFLG |= I2CF;
			goto SEND_STOP;
		}		
		
		I2CDAT = 0;					//�����������ݼĴ�����ַ
		I2CFLG |= I2CF;				//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x28)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CCON |= STA(1);			//I2C��������START�ź�
		I2CFLG  |= I2CF;			//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x08)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		
		I2CDAT = I2C_ADDR+1;		//�������ʹӻ���ַ+��λ
		I2CFLG  |= I2CF;			//����жϱ�־
		while(!(I2CFLG & I2CF));	//�ȴ��жϱ�־����
		if(I2CSTA != 0x40)
		{
			I2CFLG  |= I2CF;
			goto SEND_STOP;
		}
		I2CCON |= AAK(1);			//����Ӧ��λ
			
		for(i = 0; i < 20; i++)		
		{
			I2CFLG  |= I2CF;		//����жϱ�־
			while(!(I2CFLG & I2CF));//�ȴ��жϱ�־����	
			if((I2CSTA != 0x28)&&(I2CSTA != 0x30))
			{
				I2CFLG  |= I2CF;
				goto SEND_STOP;
			}
			ReadBuffer[i] = I2CDAT;	//��ȡ���ݵ����ݼĴ���

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
		I2CCON |= STP(1);			//����STOP�ź�
		I2CFLG  |= I2CF;
		
		
		Delay_ms(100);
	}
}
#endif
