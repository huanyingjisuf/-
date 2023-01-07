#ifndef _ADC_H_
#define _ADC_H_

//ADCON定义
#define AST(N)		(N<<7)			//N=0-1，ADC启动，AST=0结束
#define ADIE(N)		(N<<6)			//N=0-1，中断使能
#define ADIF		(1<<5)			//中断标志
#define HTME(N) 	(N<<2)			//N=0-7，采样时间设置，时间为2的HTME次方的时钟周期
#define VSEL(N) 	(N)				//N=0-3，选择参考电压 0-内部 1-VDD 2-外部

//ADCFGL定义													   
#define ACKD(N)		(N<<5)  		//N=0-7，ADC时钟分频分频倍数=（ACKD+1)
#define ADCALE(N)		(N<<4) 	
#define ADCHS(N)	(N) 			//N=0-11，ADC通道选择，1-10对应通道0-9

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