#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "include/ca51f1_config.h"		
#include "include/ca51f1sfr.h"
#include "include/ca51f1xsfr.h"
#include "include/gpiodef_f1.h"

#include "include/delay.h"
/*********************************************************************************************************************
	PWM例程
*********************************************************************************************************************/

#define TOG(n) 			(n<<6)
#define PWM_CKS_SYS	 	(0<<0)
#define PWM_CKS_IL	 	(1<<0)
#define PWM_CKS_IH	 	(2<<0)

#define PWMMOD(N)		(N<<3)	  //N=0-7
#define PWMPOL(N)		(N<<2)	  //N=0-1

#define PWM0DIV			100
#define PWM0DUT			50

#define PWM1DIV			1000
#define PWM1DUT			300

#define PWM2DIV			1000
#define PWM2DUT			300

#define LEBSY			(1<<2)

#define LED_DRIVE    

void main(void)
{	
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE0;					//设置LVD复位电压为2.2V
#endif

#ifdef SYSCLK_16MHZ					//系统时钟为16MHz,设置CKDIV为0
	CKDIV = 0;
#endif
	
	EA = 1;							//开全局中断

	//PWM0：160K,50%DUTY;
	PWM0CON = TOG(1)|PWM_CKS_IH;//设置PWM时钟，PWM是否反向输出
	PWM0CKD = 0;                //设置预分频系数，设置为0表示不分频
	PWM0DIVH = PWM0DIV/256;     //设置频率
	PWM0DIVL = PWM0DIV%256;
	PWM0DUTH = PWM0DUT/256;     //设置占空比
	PWM0DUTL = PWM0DUT%256;	
	P32F = P32_PWM0_SETTING;	//设置P32为PWM引脚功能 
	PWMEN |= (1<<0);	        //PWM0使能
	
	//PWM1：16K,30%DUTY;
//	PWM1CON = TOG(0)| PWMMOD(0) | PWMPOL(0) | PWM_CKS_IH;
//	PWM1CKD = 0;
//	PWM1DIVH = PWM1DIV/256;
//	PWM1DIVL = PWM1DIV%256;
//	PWM1DUTH = PWM1DUT/256;
//	PWM1DUTL = PWM1DUT%256;	
//	P34F = P34_PWM1_SETTING;
//	PWMEN |= (1<<1);	
	
	//PWM2：16K,30%DUTY;
	PWM2CON = TOG(0) | PWM_CKS_IH;
	PWM2CKD = 0;
	PWM2DIVH = PWM2DIV/256;
	PWM2DIVL = PWM2DIV%256;
	PWM2DUTH = PWM2DUT/256;
	PWM2DUTL = PWM2DUT%256;	
	P01F = P01_PWM2_SETTING;
	PWMEN |= (1<<2);	
	
#ifdef LED_DRIVE
	//单线级联LED
	PWM1CON = TOG(0)| PWMMOD(3) | PWMPOL(0) | PWM_CKS_IH; //设置 IRCH为 PWM时钟源，发送 3 个字节后插入暂停时间
	PWM1CKD = 0;     	//设置预分频系数，设置为 0 表示不分频
	PWM1DIVH= 0;		//设置位周期时间
	PWM1DIVL= 20;		
	PWM1DUTH= 0;		//设置位码 0 时间
	PWM1DUTL= 6;	
	LEDUTH	= 0;		//设置位码 1 时间
	LEDUTL	= 13;		
	LEDWTMH	= 0;   	 	//设置暂停时间
	LEDWTML	= 50;	
	P34F = P34_PWM1_SETTING;    //设置P34为PWM引脚功能 
	PWMEN |= (1<<1);	  		//PWM1 使能
#endif
	
	
	while(1)
	{
	#ifdef LED_DRIVE
		unsigned char i;
    	static unsigned char color_index = 0;
		code unsigned char LED_DAT[][3] = 
		{
			{0xff,0x00,0x00},
			{0xff,0xff,0x00},
			{0x00,0xff,0x00},
			{0x00,0xff,0xff},
			{0x00,0x00,0xff},
			{0xff,0x00,0xff},
		};
		for(i=0;i<24;i++) 
		{
			while(LEFLG & LEBSY);
			LEDAT0 = LED_DAT[color_index][i%3];
		}
		color_index++; 
		if(color_index>=6) 
		color_index=0;
		Delay_ms(500);
	#endif
	}
}
#endif
