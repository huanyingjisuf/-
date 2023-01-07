#ifndef _ADC_H_
#define _ADC_H_

//ADCON����
#define AST(N)		(N<<7)			//N=0-1��ADC������AST=0����
#define ADIE(N)		(N<<6)			//N=0-1���ж�ʹ��
#define ADIF		(1<<5)			//�жϱ�־
#define HTME(N) 	(N<<2)			//N=0-7������ʱ�����ã�ʱ��Ϊ2��HTME�η���ʱ������
#define VSEL(N) 	(N)				//N=0-3��ѡ��ο���ѹ 0-�ڲ� 1-VDD 2-�ⲿ

//ADCFGL����													   
#define ACKD(N)		(N<<5)  		//N=0-7��ADCʱ�ӷ�Ƶ��Ƶ����=��ACKD+1)
#define ADCALE(N)		(N<<4) 	
#define ADCHS(N)	(N) 			//N=0-11��ADCͨ��ѡ��1-10��Ӧͨ��0-9

enum 
{
	ADC_REF_INNER  	= 0,
	ADC_REF_VDD  	= 1,
};

enum 
{
	ADC_CH0  	= 1,
	ADC_CH1  	= 2,
	ADC_CH2  	= 3,
	ADC_CH3  	= 4,
	ADC_CH4  	= 5,
	ADC_CH5  	= 6,
	ADC_VDD  	= 7,
};

#endif