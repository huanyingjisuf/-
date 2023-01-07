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
//  ������ΪI2C�����ӻ�ͨ�ŵĴӻ�����
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
unsigned char I2CDataIndex;
unsigned char regAddr;
bit iicReadMode;
unsigned char idata Buffer[20]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};//�������ݼĴ�����ֵΪ0~19
void I2C_ISR(void) interrupt 6 
{
	unsigned char Sta_Temp;

	if(I2CFLG & I2CF)					 			//IIC  interrupt
	{						
		Sta_Temp = I2CSTA;			
		if(Sta_Temp == 0x60)			    		//���յ��ӻ���ַ+дλ
		{			
			I2CDataIndex = 0xFF;					//����Ϊ0xFF��ʾ������յ��ĵ�һ���ֽ�Ϊ��ַ
			iicReadMode = 0;						//����Ϊ�ӻ�����״̬
			I2CCON |= AAK(1);			
		}
		else if(Sta_Temp == 0x80)					//���ͻ����һ�ֽ����ݣ��Ѽ�⵽Ӧ���ź�
		{					
			if(iicReadMode)	 						//����һ�ֽ�����
			{
				I2CDataIndex++;
				I2CDAT = Buffer[I2CDataIndex + regAddr];		//������װ�ص����ͼĴ������ȴ�������ȡ
			}
			else												//���յ�һ�ֽ�����
			{				
				if(I2CDataIndex == 0xFF) 	//��ַ
				{
					regAddr = I2CDAT;	 						//���յ��ĵ�һ���ֽ���Ϊ�ǵ�ַ
			   		I2CDataIndex = 0;							//��������ֵΪ0
					I2CCON |= AAK(1);
				}
				else				   		//����
				{
					Buffer[I2CDataIndex + regAddr] = I2CDAT;	//���յ�������װ�ص����ݼĴ���	
					I2CDataIndex++;								//����ֵ�ۼ�
					I2CCON |= AAK(1);		
				}
			}	
		}
		else if(Sta_Temp==0xA8)				//���յ��ӻ���ַ+��λ������ACK�ź�
		{								
			I2CDAT = Buffer[I2CDataIndex + regAddr];		//������װ�ص����ͼĴ������ȴ�������ȡ
			iicReadMode = 1;								//����Ϊ�ӻ�����״̬
		}
		else if(Sta_Temp == 0x88)			//���ͻ����һ�ֽ����ݣ��Ѽ�⵽Ӧ���ź�
		{
		}
		I2CFLG  |= I2CF;					//����жϱ�־
	}	
}				
void main(void)
{	
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
	uart_printf("I2C Slave Demo Code\n");
#endif

/**********ѡ��I2C�˿�************************************************************/
 	P30F = P30_I2C_SDA_SETTING | PU_EN;		 //����P30��ΪI2C_SDA,������λ
 	P31F = P31_I2C_SCL_SETTING | PU_EN;		 //����P31��ΪI2C_SCL,������λ

/***************************************************************************************/

	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(0);		
	I2CADR = GCE(0)|(I2C_ADDR>>1);		//����I2C�ӻ���ַ
//	I2CCR = 0x69;						//����I2Cʱ�Ӳ���ʱ��
	INT4EN = 1;	 						//I2C�жϿ���

	while(1)
	{
	}
}
#endif
