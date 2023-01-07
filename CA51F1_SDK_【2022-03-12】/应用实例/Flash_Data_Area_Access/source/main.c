#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"
#include "include/system_clock.h"
#include "include/uart.h"
#include "include/delay.h"
#include "include/flash.h"
#include "include/adc.h"
#include <intrins.h>
/********************************************************************************************************************/

/******************************************************************************************************************
	Flash�洢����֯�ṹ:
	(1)Flash �����ɸ�ҳ��ɣ�ҳ�ǽ��в�����д��������С��λ��ÿ��ҳΪ64�ֽڡ�
	(2)Flash д������ҳΪ��λ���У�����һ����д��64�ֽڣ���֧�ֵ��ֽ�д�롣
	(2)Flash ���԰����ܻ���Ϊ�������������������ֵ�λΪ128�ֽڣ����������ڴ洢�û��ĳ��������������ڴ洢һЩ������Ҫ��������ݡ�

	�����̻���128�ֽ�Ϊ���ݿռ䣬ʵ��10���ֽ����ݵ���洢���ܣ������ϵ�ֱ����ó�ֵΪ0~9������ÿ���ϵ������ۼӡ�
	Ϊ�˷�ֹ�ڲ�����д��FLASH�׶η���оƬ�����λ���Ӷ����³������ݶ�ʧ������������̲���˫ҳ�洢��ģʽ���ɱ�֤���ݴ洢�İ�ȫ�ԡ�


	˵����
	�ڵ���FLASH������ֻ��ͨ���������ֹ�������ӡ���ݣ�����ʹ�÷��湦�ܣ���Ϊ�ڽ��з���ʱ��FLASH����Դ�ᱻռ�á�
	#define PRINT_EN			//ʹ��uart_printf������ӡʹ��
******************************************************************************************************************/
unsigned char idata UserDataBuff[10];
unsigned char idata BuffTemp[64];

void main(void)
{	
	unsigned char i;

#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//����LVD��λ��ѹΪ2.2V
#endif

#ifdef SYSCLK_16MHZ					//ϵͳʱ��Ϊ16MHz,����CKDIVΪ0
	CKDIV = 0;
#endif

#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);						//��ʼ��UART
#endif
	
	EA = 1;												//��ȫ���ж�


	PADRD = 128-1;										//����FLASH���128�ֽ�Ϊ���ݿռ�
	
	Data_Area_Mass_Read(0,BuffTemp,2);					//��ҳ0 16λID��16λID����ʶ���Ƿ�����ϵ�
	if(BuffTemp[0] != 0xAA || BuffTemp[1] != 0x55)		//��ID�������
	{
		Data_Area_Mass_Read(64,BuffTemp,2);				//��ȡ16λID��16λID����ʶ���Ƿ�����ϵ�
		if(BuffTemp[0] == 0xAA && BuffTemp[1] == 0x55)	//��ҳ0 ID����������ж�ҳ1 ID
		{
			goto READ_SECOND_SECTOR_PARA;				//���������ת��ȡҳ1����
		}
		
		//��ҳ0��1 ID��������� ��ʾ�ǳ����ϵ�
FIRST_POWER_ON:
		//�����ϵ磬��ʼ���û�����Ϊ 0 ~ 9
		UserDataBuff[0] = 0x00;			
		UserDataBuff[1] = 0x01;
		UserDataBuff[2] = 0x02;
		UserDataBuff[3] = 0x03;
		UserDataBuff[4] = 0x04;
		UserDataBuff[5] = 0x05;
		UserDataBuff[6] = 0x06;
		UserDataBuff[7] = 0x07;
		UserDataBuff[8] = 0x08;
		UserDataBuff[9] = 0x09;		
		
		BuffTemp[0] = 0xAA;								//����IDΪ0xAA55
		BuffTemp[1] = 0x55;
		BuffTemp[12] = 0;
		
		for(i = 0; i < 10; i++)
		{
			BuffTemp[i+2] = UserDataBuff[i];
			BuffTemp[12] += UserDataBuff[i];			//����У����
		}
		
		//�ڲ���ҳ��д������ʱ���������оƬ�����λ���ᵼ���û����ݶ�ʧ�����²���˫ҳ�洢�ķ�ʽ���ɱ������ݶ�ʧ��
		Data_Area_Erase_Page(0);						//��������ҳ0
		Data_Area_Write_Page(0,BuffTemp);				//�û����ݡ�ID��У����д�����ݿռ�,ע��д������ҳΪ��λ���У�����һ����д��64�ֽڣ���֧�ֵ��ֽ�д��
	
		Data_Area_Erase_Page(1);						//��������ҳ1
		Data_Area_Write_Page(1,BuffTemp);				//�û����ݡ�ID��У����д�����ݿռ�,ע��д������ҳΪ��λ���У�����һ����д��64�ֽڣ���֧�ֵ��ֽ�д��
	}
	else
	{
		unsigned char CheckSum;
		Data_Area_Mass_Read(0,BuffTemp,13);				//��ȡ�û����ݡ�ID��У����
		CheckSum = 0;
		for(i = 0; i < 10; i++)
		{
			CheckSum += BuffTemp[2+i];					//����У����
		}
		if(CheckSum != BuffTemp[12])					//�жϼ������Ƿ����
		{	
READ_SECOND_SECTOR_PARA:
			//���У���벻��������ȡ�ڶ�ҳ���ݡ�
			Data_Area_Mass_Read(64,BuffTemp,13);		//��ȡ�û����ݡ�ID��У����
			CheckSum = 0;
			for(i = 0; i < 10; i++)
			{
				CheckSum += BuffTemp[2+i];				//����У����
			}
			if(CheckSum != BuffTemp[12])				//�жϼ������Ƿ����
			{
				goto FIRST_POWER_ON;
			}
		}
		
		for(i = 0; i < 10; i++)
		{
			UserDataBuff[i] = BuffTemp[i+2];			//����������װ�ص��û���������
		}
		
		for(i = 0; i < 10; i++)
		{
			UserDataBuff[i]++;							//�û������ۼ�
		}
		
		BuffTemp[0] = 0xAA;									
		BuffTemp[1] = 0x55;
		BuffTemp[12] = 0;
		for(i = 0; i < 10; i++)
		{
			BuffTemp[i+2] = UserDataBuff[i];
			BuffTemp[12] += UserDataBuff[i];
		}

		Data_Area_Erase_Page(0);						//��������ҳ0
		Data_Area_Write_Page(0,BuffTemp);				//�û����ݡ�ID��У����д�����ݿռ�,ע��д������ҳΪ��λ���У�����һ����д��64�ֽڣ���֧�ֵ��ֽ�д��

		Data_Area_Erase_Page(1);						//��������ҳ1
		Data_Area_Write_Page(1,BuffTemp);				//�û����ݡ�ID��У����д�����ݿռ�,ע��д������ҳΪ��λ���У�����һ����д��64�ֽڣ���֧�ֵ��ֽ�д��
	}
	//�û����ݴ�ӡ��ÿ���ϵ��λ���û����ݼ�1
#ifdef PRINT_EN
	uart_printf("UserDataBuff[0] = 0x%x\n", (unsigned int)(UserDataBuff[0]));
	uart_printf("UserDataBuff[1] = 0x%x\n", (unsigned int)(UserDataBuff[1]));
	uart_printf("UserDataBuff[2] = 0x%x\n", (unsigned int)(UserDataBuff[2]));
	uart_printf("UserDataBuff[3] = 0x%x\n", (unsigned int)(UserDataBuff[3]));
	uart_printf("UserDataBuff[4] = 0x%x\n", (unsigned int)(UserDataBuff[4]));
	uart_printf("UserDataBuff[5] = 0x%x\n", (unsigned int)(UserDataBuff[5]));
	uart_printf("UserDataBuff[6] = 0x%x\n", (unsigned int)(UserDataBuff[6]));
	uart_printf("UserDataBuff[7] = 0x%x\n", (unsigned int)(UserDataBuff[7]));
	uart_printf("UserDataBuff[8] = 0x%x\n", (unsigned int)(UserDataBuff[8]));
	uart_printf("UserDataBuff[9] = 0x%x\n", (unsigned int)(UserDataBuff[9]));
#endif
	while(1)
	{
	}
}
#endif
