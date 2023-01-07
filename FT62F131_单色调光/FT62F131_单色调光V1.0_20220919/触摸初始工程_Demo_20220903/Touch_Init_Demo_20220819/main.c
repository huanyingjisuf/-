//Project: Touch_Init_Demo_20220819.prj
// Device: FT62F13X
// Memory: Flash 3KX14b, EEPROM 128X8b, SRAM 256X8b
// Author: 
//Company: 
//Version:
//   Date: 
//===========================================================
//===========================================================
#include	"SYSCFG.h";
#include "touch.h"
//===========================================================
//Variable definition   定义变量
//===========================================================

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long




void DelayUs(unsigned int Time)
{    
	unsigned int a;
	for(a=0;a<Time;a++)  
	{
		NOP();
	}
}

void delay_ms(unsigned int Time)
{
		
        unsigned int i;
        
        for(i =0;i<Time;i++)
			{
				DelayUs(50);
                if((i!=0)&&(i%50==0))   //防止看门狗溢出 定时喂狗
					CLRWDT();
            }
    
}


//===========================================================
//Funtion name：interrupt ISR
//parameters：无
//returned value：无
//===========================================================


uint Tim2_T =0;
uint P1ADTHL =0;
uint p1adt;
bit LED_F =0;

uchar Tk_Push;
uint Tk_Push_T;
uchar TK_Push_T1;

bit ADC_OK =0;
bit ADC_Start =0;			// ADC启动标志  定时器中断周期性启动
uchar ADC_T=0;
uchar TK_Run_F =0;     // 无极调光模式下 TK 扫描触发位
uchar TK_Run_T =0;		//无极调光定时 
uchar Run_Mode;   //外部开关断开 三档模式，外部开关闭合 无极调光模式
#define ADC_Time		1    //几次定时器周期进入一次ADC扫描
#define TK_ADJ_T	2

uchar LED_ADJ_Push_T;     // LED  ADJ 模式下  按下的时间

//#define TK_Run_Time    1   //无极调光扫描间隔
void interrupt ISR(void)
{
	if(TMR2IE && TMR2IF)			//50us中断一次 
		{
			TMR2IF = 0;
			
            if(Tk_Push==1)   //tk_push =1 表示触发计时 tk_push =2 表示计时溢出  tk_push =0 表示停止计时 tk_push清零需要由键盘扫描程序完成
            {
				Tk_Push_T++;
                if(Tk_Push_T>=15000)   //累计0.5 s
                {
					Tk_Push_T =0;
					Tk_Push =2;
					//TK_Push_T1++;
					// if(TK_Push_T1>=2)
					// 	{
					// 		TK_Push_T1 =0;
					// 		Tk_Push =2;
					// 	}
                }
               
            }
            else
            {
				Tk_Push_T =0;
				
            }
            
            if((ADC_T<ADC_Time)&&(ADC_Start==0))
            {
				ADC_T++;
            }
            else if(ADC_Start==0)
            {
				ADC_T =0;
                ADC_Start=1;
            }
            else
            ADC_T =0;

			
			// if(Run_Mode==1)		//无极调光模式下
			// {
			// 	TK_Run_T++;
			// 	if(TK_Run_T>=TK_Run_Time)
			// 	{
			// 		TK_Run_T =0;
			// 		TK_Run_F =1;     //允许触发一次扫描
			// 	}
			// }
			// else
			// {
			// 	TK_Run_F =0;
			// 	TK_Run_T =0;
			// }
            
		}
        
        
     if(ADCIE&&ADCIF)
     {
		ADCIF =0;
        ADC_OK =1;
     }
}

/******************************************************************************
  * @brief  SYS_INITIAL	program
  * @Description  系统时钟、IO初始化
  * @param  None
  * @note   
  * @retval  None
  *****************************************************************************
*/

void SYS_INITIAL (void) 
{
	OSCCON = SYS_OSCCON;   //0B01110001 ；//WDT 32KHZ IRCF=110=16MHZ/4=4MHZ,0.25US/T
							//Bit0=1,系统时钟为内部振荡器
							//Bit0=0,时钟源由FOSC<2：0>决定即编译选项时选择
                            
	OPTION = 0B00001000;	//Bit3 PSA   预分频器分配位 0= 预分频器分配给Timer0模块 1：分配给WDT 
							//Bit2：0：预分频比选择位 000: 1:2 
									   
	INTCON = 0;  			//暂禁止所有中断
		
	PORTA = 0B00010000;
	PORTC = 0B00000001;
	PORTB = 0B00000000;
		
	TRISA = 0B00000101;		// 0-输出 1-输入   PA2(TKCAP) set input PA4 ADCINPUT
	TRISB = 0B00000000;		// B2-B7  TK7-TK2
	TRISC = 0B00000001;     // C0-C1  TK1-TK0   //PC0设置为输入 模式判断
		
	WPUA = 0B00000000;     	//PA端口上拉控制 1-开上拉 0-关上拉
	WPUB = 0B00000000;
	WPUC = 0B00000001;		//开启 PC0 弱上拉
	
	ANSEL0 = 0B00000101;      // TKCAP （A2）设为模拟输入脚	
  //  ODCONA =0X01;
   // ANSEL0|=0X08;   //设置 AN3为模拟输入端口

    
 //   WPUA &=0XEF;
//    WPDA &=0XEF;
//    
    
	
//===========================================================
//除TSSOP/SOP20封装外，PA3、PA5必须配置成输出低,程序中请勿修改
	TRISA3 = 0;			 
	TRISA5 = 0;		
    
  //  ODCONA|=0X01;   //设置PA0为开漏输出
    
    //PA0 =1;			//设置 PA0为开漏	
    
	PA3 = 0;			 
	PA5 = 0;		
      
}


/******************************************************************************
  * @brief  WDT_INITIAL	program
  * @Description  初始化设置看门狗为16位计数器，用于SLEEP模式的128ms唤醒
  * @param  None
  * @note   
  * @retval  None
  *****************************************************************************
*/

void WDT_INITIAL (void) 
{
	CLRWDT();              //清看门狗
	WDTCON = 0B00001101;   //bit[6:5]WCKSRC=00=LIRC(32K) 
						   //bit[4:1]WDTPS=0110=1:2048,预分频1:1 定时时间=(4096*1)/32000=128ms
                           ////已改为 8192 分频 周期256ms     
						   //bit[0]SWDTEN= 1 开启                      	                  
}


//引入PWM程序 利用LED演示PWM是否实现

////PWM @ 50k@20us
//#define PWM1_ADTHL_Value   0x140		//50%
//#define PWM1_PR2HL_Value   0x280
//#define PWM1_PR2H_Value    0x02
//#define PWM1_PR2L_Value		0x80

//PWM @ 20k@50us
#define PWM1_ADTHL_Value   200		//50%
#define PWM1_PR2HL_Value   0x640    //1600 
#define PWM1_PR2H_Value    0x06
#define PWM1_PR2L_Value		0x40

////PWM @ 10k@50us
//#define PWM1_ADTHL_Value   1600		//50%
//#define PWM1_PR2HL_Value   3200
//#define PWM1_PR2H_Value    0x0C
//#define PWM1_PR2L_Value		0x80




void PWM_Init()
{
    T2CON0=0X00;               //Bit[6:3]=TOUTPS  后分频比	0000=1:1~1111=1:16
                            //Bit2=TMR2ON	   1=TIMER2打开	0=关闭
                            //Bit[1:0]=T2CKPS  预分频比 00=1:1 01=1:4 1x=1:16
                            //设置预分频比和后分频比都为1:1
                            
    T2CON1 = 0X02;			//时钟源为2xHIRC，
							//PWM1设置为连续模式
							//关闭蜂鸣器模式
    

   PR2H =PWM1_PR2H_Value;
   PR2L =PWM1_PR2L_Value;    //20k@50us

	
    
    
    TMR2H =0;
    TMR2L =0;
    
    P1OE2 =0;
    
    P1OE = 0X10;    //使能 PA1输出PWM波形  
    
    P1CON = 0X00;  //设置死区为0
    
    P1POL = 0X00;		//P1A2反向输出(LED低电平有效)

	P1ADTH =0;//PWM1_ADTHL_Value>>8;			//P1A占空比为5/65535
	P1ADTL = 0;//PWM1_ADTHL_Value&0xff;

    
    T2CON0 = T2CON0|0X04;  //开启Timer2使能
    
    TMR2IE =1;		//开启定时器2中断
    
    GIE =1;
	
}


/*********************************************************

ADC初始化程序

**********************************************************/

void ADC_DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
		NOP();
	}
}


uint adcData;
uint VDD_Voltage;

void ADC_Init(void)
{
	ADCON1 = 0B10100101; 	//右对齐，转换时钟SysClk/32，负参考电压GND，正参考电压VDD
  	//Bit7:ADFM A/D转换结果格式 
	//1 = 右对齐。 
	//0 = 左对齐。
  
  	//Bit6~Bit4:ADCS ADC转换时钟源
    //TSEL=2T
	//000 = SysClk/2
	//001 = SysClk/8
	//010 = SysClk/32
	//011 = SysClk
	//100 = SysClk/4
	//101 = SysClk/16
	//110 = SysClk/64
	//111 = LIRC
	
	//Bit3~Bit2:ADNREF ADC负参考电压
	//00 = Int Vref（内部参考电压）
	//01 = GND
	//10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
	//11 = Ext Vref（外部参考电压）

  	//Bit1~Bit0:ADPREF ADC正参考电压
	//00 = Int Vref（内部参考电压）
	//01 = VDD
	//10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
	//11 = Ext Vref（外部参考电压）
    
	ADCON0 = 0B00000000; 	
  	//Bit6~Bit3:CHS ADC模拟通道选择位
	//0000 = AN0
	//0001 = AN1
	//0010 = AN2
	//0011 = AN3
	//0100 = AN4
	//0101 = AN5
	//0110 = AN6
	//0111 = AN7
	//1xxx = Int Vref（内部参考电压）

    //Bit2:ADEX	 ADC触发条件
	//0 = 由置位指令GO/DONE（软件触发）
	//1 = 由PA4或PWM置位G0/DONE（硬件触发）
		
    //Bit1:G0/DONE ADC转换启动和状态位
    //0 = A/D转换完成/未进行转换
	//1 = A/D转换正在进行或硬件触发延时正在计数

    //Bit0:ADON 使能ADC  
    //0 = ADC被禁止且不消耗工作电流
	//1 = ADC被使能
              

	ADC_DelayUs(200);	
    ADC_DelayUs(250);           //必须要延时450us
    			   			 			
    ADCON2 = 0B00000000; 	//选择内部正参考电压0.5V，无外部触发源
    //Bit7~Bit6:ADINTREF ADC内部参考电压
	//00 = 0.5V
	//01 = 2.0V
	//10 = 3.0V
	//11 = 未连接
		
	//Bit5~Bit4:ETGTYP 外部触发沿（当ADEX=1时适用）
	//00 = PWM 或 ADC_ETR脚的下降沿
	//01 = PWM 或 ADC_ETR脚的上升沿
		
	//Bit3:ADDLY.8/LEBPR9 ADC外部触发延时计数器或LEB计数器的第8位
		
	//Bit2~Bit0:ETGSEL 外部触发源（当ADEX=1时适用）
	//选择PWM源时需要配置TIMER为PWM输出模式并使能输出。
	//000 = P1A0
	//001 = P1A0N
	//010 = P1B
	//011 = P1C
	//100 = P1D
	//101 = ADC_ETR
	//11x = 无


    ADCON3 = 0B00000000; 
    //Bit7:ADFBEN ADC比较结果响应故障刹车使能
	//0 = 禁止
	//1 = 使能
		
	//Bit6:ADCMPOP ADC比较器输出极性
	//0 = ADC结果的高八位大于或等于ADCMPH[7:0]
	//1 = ADC结果的高八位小于ADCMPH[7:0]

	//Bit5:ADCMPEN ADC结果比较使能位
	//0 = 关闭
	//1 = 使能
		
	//Bit3:LEBADT 前沿消隐周期结束后，ADC触发使能
	//1 = 触发ADC转换
	//0 = 不触发ADC转换

    ADCMPH = 0B00000000;	//ADC比较阈值,仅8位，用于ADC结果高8位比较

   // ADON=1;                 //使能ADC	
    
}

/*-------------------------------------------------
 *  函数名: GET_ADC_DATA
 *	功能：  读取通道ADC值
 *  输入：  adcChannel 通道序号
 *  输出：  INT类型AD值(单次采样无滤波)
 --------------------------------------------------*/

uint GET_ADC_DATA (uchar adcChannel)
{
	uint ADC_Dat;


//    ADC_OK =0;		//使用中断标志位
    ADON =1;
	ADCON0 &= 0B00000011;        				   
    ADCON0 |= adcChannel>>1; 				//重新加载通道值
	ADC_DelayUs(80);                        	//廷时等待电压稳定 Tst >10us
    
//    ADON =1;		//开启 ADC  等待PWM触发
//	ADCIE =1;
//    
	ADCON0 = ADCON0|0x02;             		//启动ADC 
    NOP();
    NOP();
    
	while(ADCON0&0x02);    					//等待ADC转换完成
//	while(ADC_OK==0);
  //  ADCIE =0;
//    ADC_OK =0;

	ADC_Dat=ADRESH;
	ADC_Dat<<=8;
    ADC_Dat+=ADRESL;
    ADON =0;
    return  ADC_Dat;      //整合12位AD值
} 

/**************************************************

初始化外部测量ADC
使用内部2V参考点

***************************************************/

void ADC_AN3_Init()
{

	ADCON1 = 0B11100100; 	//右对齐，转换时钟SysClk/32，负参考电压GND，正参考电压VDD，使用内部参考电压
	ADCON0 = 0B00000000; 	//使用外部触发
	
	ADC_DelayUs(200);	
    ADC_DelayUs(250);           //必须要延时450us
    			   			 			
    ADCON2 = 0B01000000; 	//选择内部正参考电压0.5V，无外部触发源     
    ADCON3 = 0B00000000; 
    ADCMPH = 0B00000000;	//ADC比较阈值,仅8位，用于ADC结果高8位比较
    
    
 
   // ADON=1;                 //使能ADC	
    
}




ulong ADC_Test_VDD()
{
		adcData = GET_ADC_DATA(0X80);		//VDD做基准测量内部参考通道的AD值
		//adcData>>=4;						//AD值缩小16倍
        
        VDD_Voltage = (ulong)((204800/adcData));
        
        NOP();
        NOP();
        
        return VDD_Voltage;
    
}

/*************************************

字符串排序 对采样数据做中位数过滤

输入： *s 字符串  l 字符串长度   l仅能输入10
输出：中位数平均值

*************************************/
uint String_Sort_Tab[10];
uchar String_Sort_Warning;
uint String_Sort(uint *s,uchar l)
{

	uint Dat;//,Dat1;   //Dat 和 Dat所取的数据
    
    String_Sort_Warning =0;
    for(uchar i =0;i<10;i++)
		String_Sort_Tab[i] =0;
    for(uchar i =0;i<l;i++)
    {
		String_Sort_Tab[i] =*s;
        s++;
    }
    
    for(uchar i =0;i<l;i++)			//对字符串进行冒泡
    {
		Dat =String_Sort_Tab[i];
        
        for(uchar is =i;is<l;is++)
        {
			if(Dat>=String_Sort_Tab[is]);
            else
            {
				String_Sort_Tab[i] =String_Sort_Tab[is];			//将较大数字放在首位
                String_Sort_Tab[is]=Dat;    //将较小数字放在比较位
                Dat = String_Sort_Tab[i];  //获取较大值继续比较
            }
        }
        //完成循环后 Dat值已经是范围内最大的数据    
	}
    Dat =0;
	for(uchar i =0;i<l;i++)
		Dat+=String_Sort_Tab[i];
	
    Dat/=l;      //计算平均数
    
    if(String_Sort_Tab[0]>150)    //当数据不均匀时计算中位数
    {
		if((String_Sort_Tab[0]-String_Sort_Tab[9])>(String_Sort_Tab[0]/5))
		{
			Dat =0;
		//	String_Sort_Warning =1;    //差值太大异常位置1
        Dat+=String_Sort_Tab[l/2];
        Dat+=String_Sort_Tab[l/2+1];
        Dat+=String_Sort_Tab[l/2+2];
        
        Dat/=3;
            
		}
    }	
    return Dat;
}

/***********************************************************
 * 
 *触摸调光
 * 开关灯过程  
 * 配置三档亮度
 * 配置三档基础PWM和三档稳定电流
 * 
 * *********************************************************/

/* 
uchar Tk_PushNum;

void TK_Run(void)
{

	TSC_Start(); 

	if(TSC_DataProcessing()==1)    //返回1 表示所有按键处理完成
	{
		strongest = TSC_GetStrongest(); 
		
        Tk_PushNum = TSC_GetSingle();   //获取按下的按键号
        
		if(strongest!=Sav_strongest)
		{
        
 */



#define LED_Lv1_Cur 		100   /// LED 1级电流
#define LED_Lv2_Cur 		300   /// LED 2级电流
#define LED_Lv3_Cur 		500   /// LED 3级电流

#define LED_LV1_Cur_Off		5		//LED 1级电流 偏差电流
#define LED_LV2_Cur_Off		5		//LED 2级电流 偏差电流
#define LED_LV3_Cur_Off		5		//LED 3级电流 偏差电流

#define LED_LV1_Dyty	20			//LED 1级占空比%
#define LED_LV2_Dyty	30			//LED 1级占空比%
#define LED_LV3_Dyty	40			//LED 1级占空比%

#define PWM1_LED_PWM_H_Max_Value  1600		//设定 LED_PWM_H 最大值
#define LED_Max_Cur_Dat  500		//通过 LED 最大电流（无极模式有效）

uchar Tk_PushNum;
// uchar Tk_Push =0;   //触摸持续触发标志 
// uint Tk_Push_T;

uchar LED_Cur_LV_Num =0;
uint LED_Cur_LV_Dat =0;
uchar LED_Cur_off_Dat =0;

uchar LED_Dyty_LV_Num =0;
uchar LED_Dyty_LV_Dat =0;

unsigned char strongest = 0; //demo_test   新获取到的触摸结果
unsigned char Sav_strongest = 0; //demo_test   //保存在本地的触摸结果用于比对

 
uint LED_PWM_H =0;		//占空比 1-100;
uint LED_PWN_N =0;

uint LED_PWM_H_Max;			//占空比上限

uint LED_PWM_H_SV =0;		//备份 LED_PWM_H 数值

uchar LED_Cur_OK =0;			// LED 亮度调节完成

uchar LED_ADJ_Stop =0;			//LED_ADJ_Stop  长按一次只允许一次开启循环，关闭后需要松开再按

uint LED_adj_SV_dat=0;			//保存上次的关闭亮度

uint LED_ADJ_P1ADTH=0;		//保持上次占空比
uint LED_ADJ_P1ADTL=0;
uint LED_Cur;				//LED 实时电流
//uint LED_ADJ_Set_Cur;			// LED 调光设置电流 同时由LED_Cur_LV_Dat 完成


uchar LED_ADJ_Dir=0;			//调光方向
uchar LED_TH1_OP_Flag =0;			//通过短按不松手触发开灯标志

uchar LED_ADJ_OP; 			// LED 无极调光 开关  0 关 1 开
#define LED_ADJ_Div			15		// LED 无级调光分度值
#define LED_ADJ_Min_Cur		50		//LED无级调光 最小电流（由于ADC调光设定最低50最高LED_Max_Cur_Dat）

#define LED_PWM_H_ADJ_Min 50     //无极调光最小值


void TK_TG_Run()
{
	TSC_Start(); 					//开始触摸扫描
	if(TSC_DataProcessing()==1)   //返回1 表示所有按键处理完成
	{
		strongest = TSC_GetStrongest();
		Tk_PushNum = TSC_GetSingle();

		if(Run_Mode==0)
		{
		
			if(strongest!=Sav_strongest)
			{
				switch (strongest)
				{
				case 1: 		//当触摸按下时   

					if(LED_Cur_LV_Num<3)		//增量循环触摸
					{
                    
						LED_Cur_LV_Num++;
//                        switch(LED_Cur_LV_Num)
//                        {
//							case 1:
//                            LED_PWM_H =200;		//抬高到近似PWM
//                            break;
//                            
//                            
//                            case 2: 
//                            LED_PWM_H =900;
//                            break;
//                            
//                            case 3:
//                            LED_PWM_H =1400;
//                            break;
//							
//                        }			
					}
					else
					{
						LED_Cur_LV_Num =0;
						P1ADTH =0;
						P1ADTL =0;

						LED_PWM_H =0;
						LED_PWN_N =0;		//清空占空比值
					}

					break;

				default:
					break;
				}

				switch (LED_Cur_LV_Num)    //电流等级匹配
				{
					case 0:
					LED_Cur_LV_Dat =0;
					LED_Cur_off_Dat =0;			
						break;
					case 1:
					// if(Run_Mode==0)
					// {
						LED_Cur_LV_Dat =LED_Lv1_Cur;
						LED_Cur_off_Dat =LED_LV1_Cur_Off;
						LED_PWM_H =200;		//抬高到近似PWM
					// }
					// else
					// {
					// 	LED_Cur_LV_Dat =200;
					// 	LED_Cur_off_Dat =5;
					// }
						break;
					case 2:
					LED_Cur_LV_Dat =LED_Lv2_Cur;
					LED_Cur_off_Dat =LED_LV2_Cur_Off;
                    LED_PWM_H =900;
						break;
					case 3:
					LED_Cur_LV_Dat =LED_Lv3_Cur;
					LED_Cur_off_Dat =LED_LV3_Cur_Off;
                    LED_PWM_H =1400;
						break;
					
					default:
						break;
				}

				Sav_strongest = strongest;
			}
		}
		else if(Run_Mode==1)
		{

			switch (strongest)
			{
				case 0:

				if((Tk_Push==1)&&(strongest!=Sav_strongest))		//表示在短时间内完成按键触发，执行开关
                {
					Tk_Push=0;		//清空触发位
					if((LED_ADJ_OP==1)&&(LED_TH1_OP_Flag==0))		//关灯
					{
							LED_ADJ_OP =0;
							LED_Cur_LV_Num =0;

                            LED_ADJ_P1ADTH = P1ADTH;	//备份占空比高位                            
							P1ADTH =0;					//清空低位占空比

							LED_ADJ_P1ADTL = P1ADTL;	//备份占空比低位
							P1ADTL =0;					//清空低位占空比
                            
							LED_PWM_H_SV = LED_PWM_H;		//备份 PWM_PWM_H
							LED_PWM_H =0;
							LED_PWN_N =0;		//清空占空比值
                            LED_adj_SV_dat=LED_Cur_LV_Dat;
							LED_Cur_LV_Dat =0;
							LED_ADJ_Dir =0;				//关灯复位调光方向
							PA4 =0;

                    }
                    else
                    if((LED_ADJ_OP==0)&&(LED_TH1_OP_Flag==0))		//开灯
                    {

								LED_ADJ_OP =1;
								LED_Cur_LV_Dat = LED_adj_SV_dat;		//使用备份数据
								if(LED_Cur_LV_Dat<LED_ADJ_Min_Cur)
									LED_Cur_LV_Dat =LED_ADJ_Min_Cur;						//给予50 保底数
								P1ADTH = LED_ADJ_P1ADTH;				//  使用备份的数据给予PWM寄存器
								P1ADTL = LED_ADJ_P1ADTL;
								LED_PWM_H = LED_PWM_H_SV;				//调用备份数据
								PA4 =1;										//关闭指示灯
								LED_Cur_off_Dat =LED_LV1_Cur_Off;

                    }
                }
                
                if((Tk_Push==2)&&(strongest!=Sav_strongest))		//表示调光之后
				{
					Tk_Push=0;
                    if(LED_ADJ_Dir==0)			//调光方向
						LED_ADJ_Dir =1;	//取反
                     else
						LED_ADJ_Dir =0;

					
                }               
				break;

				case 1:
					

					if(Sav_strongest != strongest)		//key值变化，记录按下时间
                    {
						Tk_Push =1;
						if(LED_ADJ_OP==0)		//如果没开灯 先开灯
						{

								LED_TH1_OP_Flag =1;
								LED_ADJ_OP =1;
								LED_Cur_LV_Dat = LED_adj_SV_dat;		//使用备份数据
								if(LED_Cur_LV_Dat<LED_ADJ_Min_Cur)
									LED_Cur_LV_Dat =LED_ADJ_Min_Cur;						//给予50 保底数
								P1ADTH = LED_ADJ_P1ADTH;				//  使用备份的数据给予PWM寄存器
								P1ADTL = LED_ADJ_P1ADTL;
								LED_PWM_H = LED_PWM_H_SV;				//调用备份数据
								PA4 =1;										//关闭指示灯
								LED_Cur_off_Dat =LED_LV1_Cur_Off;
						}
						else
						LED_TH1_OP_Flag =0;
                    }

					if((Tk_Push==2)&&(LED_ADJ_OP==1))		//按下一段时间后
					{

						
						if((LED_ADJ_Dir==0)&&(LED_Cur_OK==1))  //向上调光
						{
							LED_Cur_OK =0;

						if(LED_Cur<LED_Max_Cur_Dat)
							LED_PWM_H +=20;

							if(LED_PWM_H>=PWM1_LED_PWM_H_Max_Value)
								LED_PWM_H = PWM1_LED_PWM_H_Max_Value;
							
							LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
							
							P1ADTH = LED_PWN_N>>8;
							P1ADTL =LED_PWN_N&0XFF;
							if(LED_Cur<LED_Max_Cur_Dat)
								LED_Cur_LV_Dat =LED_Cur;			//将采样电流设定为当前电流
							else
								LED_Cur_LV_Dat =LED_Max_Cur_Dat;
						}

						if((LED_ADJ_Dir==1)&&(LED_Cur_OK==1))   //向下调光
						{
							LED_Cur_OK =0;
							if(LED_Cur>(LED_ADJ_Min_Cur+50))
								LED_PWM_H-=20;
							else if(LED_Cur>LED_ADJ_Min_Cur)
								LED_PWM_H-=4;
							
							if(LED_PWM_H<=LED_PWM_H_ADJ_Min)
								LED_PWM_H = LED_PWM_H_ADJ_Min;
							
							LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
							P1ADTH = LED_PWN_N>>8;
							P1ADTL =LED_PWN_N&0XFF;
							
							if(LED_Cur>LED_ADJ_Min_Cur)
								LED_Cur_LV_Dat =LED_Cur;			//将采样电流设定为当前电流
							else
								LED_Cur_LV_Dat =LED_ADJ_Min_Cur;

						}
						
					}

					break;
				
				default:
					break;
			}

			Sav_strongest = strongest;
		}
	}

}




/***********************************************************

周期性扫描 ADC
通过定时器中断定时触发进入   暂定10ms进入一次

************************************************************/


#define LED_PWM_AD_Dat_Len  10       //LED_PWM_AD_Dat  数据长度
#define LED_PWM_PJ_Val_Len 	5		//LED_PWM_PJ_Val_Len  数据长度
#define LED_PWM_PJ_Cur_Len  5		//LED_PWM_PJ_Cur_Len  数据长度



//uint LED_ON_AD_Dat[10];
//uint LED_OFF_AD_Dat[10];
uint LED_PWM_AD_Dat[LED_PWM_AD_Dat_Len];
uchar LED_PWM_AD_Num =0;    // LED_PWM_AD_Dat 当前存储的数据量

uint AD_PWM_PJ_Dat;  //保存 AD平均值
//uint AD_OFF_PJ_Dat;  //保存 AD平均值
//uint AD_ON_PJ_Dat;   //保存 AD平均值

uint LED_PWM_PJ_Cur[LED_PWM_PJ_Cur_Len];
uchar LED_PWM_PJ_Cur_Num =0;    //LED_PWM_PJ_Cur    当前存储的数据量

uint LED_PWM_PJ_Val[LED_PWM_PJ_Val_Len];
uchar LED_PWM_PJ_Val_Num =0;	//LED_PWM_PJ_Val  当前存储的数据量





uchar ADC_now =0;			// ADC switch 

void ADC_Run()
{

	if(((ADC_Start==1)&&(LED_Cur_LV_Num))||((Run_Mode==1)&&(LED_ADJ_OP==1)))
    {
		ADC_Start =0;        
		switch(ADC_now)
        {
			case 0:
            
				LED_PWM_AD_Num =0;
                LED_PWM_PJ_Val_Num =0;
                LED_PWM_PJ_Cur_Num =0;

                ADC_now=1;
				break;
                
            case 1:
            
				LED_PWM_AD_Dat[LED_PWM_AD_Num++] = GET_ADC_DATA(0x00);			//采样一次ADC

                
				if(LED_PWM_AD_Num<LED_PWM_AD_Dat_Len)      //当输入数据足够时进入下一步
					ADC_now =1;			//ADC采样数据不够不进入下层
                else if(LED_PWM_AD_Num>=LED_PWM_AD_Dat_Len)
                {
					LED_PWM_AD_Num =0;
					ADC_now=2;			//ADC采样数据足够进入下层转换为电压
                }
				break;
                
            case 2:

					//LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num++] =(ulong)200000/4096*(String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len))/100;//String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len)/2;

				LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num++] = (String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len))/2;
                
                LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num]+=(LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num]/50)*12/10;   //补偿差值
                
                
                if(String_Sort_Warning==1)		//当数据落差过大
                {
					LED_PWM_PJ_Val_Num-=1;			//舍弃数据
                    String_Sort_Warning =0;			//清空标志位
                }   
                
                if(LED_PWM_PJ_Val_Num<LED_PWM_PJ_Val_Len)   //当输入数据足够时进入下一步
					ADC_now=1;									//否则重新采集一次数据
					else if(LED_PWM_PJ_Val_Num>=LED_PWM_PJ_Val_Len)
                    {
						LED_PWM_PJ_Val_Num =0;	
						ADC_now=3;
                    }
				break;
			
            case 3:
				
				LED_PWM_PJ_Cur[LED_PWM_PJ_Cur_Num++] = String_Sort(LED_PWM_PJ_Val,LED_PWM_PJ_Val_Len);
                
                if(String_Sort_Warning==1)		//当数据落差过大
                {
                
					LED_PWM_PJ_Val_Num-=1;			//舍弃数据
                    String_Sort_Warning =0;
                    
                }
                
                if(LED_PWM_PJ_Cur_Num<LED_PWM_PJ_Cur_Len)			//当输入数据足够时进入下一步
                ADC_now=1;
                else if(LED_PWM_PJ_Cur_Num>=LED_PWM_PJ_Cur_Len)
                {
					LED_PWM_PJ_Cur_Num =0;
					ADC_now=4;
                }
				break;
			
            case 4:
            
			LED_Cur = String_Sort(LED_PWM_PJ_Cur,LED_PWM_PJ_Cur_Len);
			//LED_Cur*=10;
			//LED_Cur=10;
				
			ADC_now ++;
                
			break;
            
            case 5:   //根据电流微调占空比  测试1级
            
			if(LED_Cur_LV_Num||((Run_Mode==1)&&(LED_ADJ_OP==1)&&(Tk_Push==0)))			//无极调光模式仅第一次开启时做电流微调，其余情况下对最大电流进行限制 触摸按下时不做调光
			{

					if(LED_Cur>LED_Cur_LV_Dat)
					{
						if((LED_Cur-LED_Cur_LV_Dat)>LED_Cur_off_Dat)  //大于一次 下降1%
						{
						
			//					if(((LED_Cur-LED_Lv3_Cur)>(LED_LV3_Cur_Off*10))&&(LED_PWM_H>10))
			//                    {
			//						//	if(LED_PWM_H>((LED_Cur-LED_Lv3_Cur)/LED_LV3_Cur_Off))
			//							//	LED_PWM_H-=(LED_Cur-LED_Lv3_Cur)/LED_LV3_Cur_Off;
			//                        //    else
			//								LED_PWM_H-=10;
			//                    }
			//                    else 
								LED_Cur_OK =0;
								if((LED_Cur-LED_Cur_LV_Dat)>(LED_Cur_off_Dat*5)&&(LED_PWM_H>5))
								{
									if(LED_PWM_H>5)
									LED_PWM_H-=5;
									else
									LED_PWM_H =0;
								
								}
								else
								{
									
									if(LED_PWM_H>1)
									LED_PWM_H-=1;
									else
									LED_PWM_H =0;
								}
								
								LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
								
			//					if(LED_PWN_N>1)
			//						LED_PWN_N-=1;
			//                    else
			//						LED_PWN_N =0;
							
								P1ADTH = LED_PWN_N>>8;
								P1ADTL =LED_PWN_N&0XFF;
						
						}
						else
							LED_Cur_OK =1;
						
					}
					else if(LED_Cur<LED_Cur_LV_Dat)
					{
							if((LED_Cur_LV_Dat-LED_Cur)>LED_Cur_off_Dat)    //小于一次  上升 1%
							{
							LED_Cur_OK =0;
							if(LED_PWM_H<50)
							{
								LED_PWM_H =50;
							}					
							else if (LED_PWM_H<100)
							{
								LED_PWM_H+=4;
							}
							else if(LED_PWM_H<500)
							{
								LED_PWM_H+=10;
							}
							else if(LED_PWM_H<(PWM1_LED_PWM_H_Max_Value-10))
								LED_PWM_H+=10;
								else
								LED_PWM_H =PWM1_LED_PWM_H_Max_Value;
							}
							else
							{
								LED_Cur_OK =1;
							}
								

							LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
							
							P1ADTH = LED_PWN_N>>8;
							P1ADTL =LED_PWN_N&0XFF;

					}
					else
						LED_Cur_OK =1;
				
				}
				else if(Tk_Push==2)
						{
							//长按触摸时做电流采样完成反馈
							LED_Cur_OK =1;
						}
				// else if((Run_Mode==1)&&(First_OP_ADJ_LED==1))
				// {
				// 	if(LED_Cur>LED_ADJ_Set_Cur)
				// 	{
				// 		if((LED_Cur-LED_ADJ_Set_Cur)>LED_Cur_off_Dat)  //大于一次 下降1%
				// 			{
							
				// //					if(((LED_Cur-LED_Lv3_Cur)>(LED_LV3_Cur_Off*10))&&(LED_PWM_H>10))
				// //                    {
				// //						//	if(LED_PWM_H>((LED_Cur-LED_Lv3_Cur)/LED_LV3_Cur_Off))
				// //							//	LED_PWM_H-=(LED_Cur-LED_Lv3_Cur)/LED_LV3_Cur_Off;
				// //                        //    else
				// //								LED_PWM_H-=10;
				// //                    }
				// //                    else 
				// 					LED_Cur_OK =0;
				// 					if((LED_Cur-LED_ADJ_Set_Cur)>(LED_Cur_off_Dat*5)&&(LED_PWM_H>5))
				// 					{
				// 						if(LED_PWM_H>5)
				// 						LED_PWM_H-=5;
				// 						else
				// 						LED_PWM_H =0;
									
				// 					}
				// 					else
				// 					{
										
				// 						if(LED_PWM_H>1)
				// 						LED_PWM_H-=1;
				// 						else
				// 						LED_PWM_H =0;
				// 					}
									
				// 					LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
									
				// //					if(LED_PWN_N>1)
				// //						LED_PWN_N-=1;
				// //                    else
				// //						LED_PWN_N =0;
								
				// 					P1ADTH = LED_PWN_N>>8;
				// 					P1ADTL =LED_PWN_N&0XFF;
							
				// 			}
				// 	}
				// 	else if(LED_Cur<LED_ADJ_Set_Cur)
				// 	{
				// 			if((LED_ADJ_Set_Cur-LED_Cur)>LED_Cur_off_Dat)    //小于一次  上升 1%
				// 			{
				// 				LED_Cur_OK =0;
				// 				if(LED_PWM_H<50)
				// 				{
				// 					LED_PWM_H =50;
				// 				}					
				// 				else if (LED_PWM_H<100)
				// 				{
				// 					LED_PWM_H+=4;
				// 				}
				// 				else if(LED_PWM_H<500)
				// 				{
				// 					LED_PWM_H+=10;
				// 				}
				// 				else if(LED_PWM_H<(PWM1_PR2HL_Value-10))
				// 					LED_PWM_H+=10;
				// 					else
				// 					LED_PWM_H =PWM1_PR2HL_Value;
				// 			}
				// 			else
				// 			{
				// 				LED_Cur_OK =1;
				// 			}
								

				// 			LED_PWN_N = LED_PWM_H*(PWM1_PR2HL_Value/PWM1_LED_PWM_H_Max_Value);
							
				// 			P1ADTH = LED_PWN_N>>8;
				// 			P1ADTL =LED_PWN_N&0XFF;

				// 	}

				// }


            ADC_now =0;
            break;
            
            default:

				ADC_now =0;
                
				break;
        }
        
    }

}



//void TK_Run(void);     //运行触摸按键
//===========================================================
//Funtion name：main
//parameters：无
//returned value：无
//测试触摸时需要拔掉FMD link 且需要重新上电否则触碰到TH2 程序烧完芯片处于调试模式
//会误以为是复位信号导致芯片复位
//===========================================================
ulong VDD_Value;
uint VDD_V_Tab[10];

main()
{
	SYS_INITIAL(); //系统时钟、IO初始化   
    T2CON0=0;		//关闭PWM定时器
	TOUCH_INITIAL();//触摸按键初始化
	WDT_INITIAL(); //看门狗初始化
	PEIE = 1;  //使能外设中断
	GIE = 1; //使能全局中断

	TRISA&=0xfD;		//配置PA1为输出
	TRISA&=0xEF;		//配置PA4为输出
	


    ADC_AN3_Init();

	PA1 =0;  //关闭LED
     
	
    PWM_Init();		//使能 PWM 
	
    delay_ms(5000);			//等待稳定
    
	while(1)
    {
		if(LED_Cur_LV_Num==0)
		{
			if(PC0==1)   //判断外部模式开关
			{
				if(Run_Mode==1)
                {
					LED_Cur_LV_Num =0;
					LED_Cur_LV_Dat =0;
					P1ADTH =0;
					P1ADTL =0;
					LED_PWM_H =0;
					LED_PWN_N =0;		//清空占空比值
                }
                
                Run_Mode =0;			//清空无极调光值
			}
			else if((PC0==0)&&(Run_Mode==0))
			{
				LED_ADJ_OP =0;  //默认关灯
				PA4 =0;			//亮指示灯
				Run_Mode =1;
			}
		}

		if((LED_Cur_LV_Num==0)&&(Run_Mode==0))   //控制三级亮度 指示灯
		{
			PA4 =0;
		}
		else if((LED_Cur_LV_Num!=0)&&(Run_Mode==0))
		{
			PA4 =1;
		}

		//清看门狗   
        ADC_Run();

		CLRWDT(); 
		//按键扫描 
		TK_TG_Run();
       // TK_Run();

//	   if(LED_Cur_LV_Num==0)
//	   		{
//				CLRWDT();  		//清看门狗
//				NOP();
//     			SLEEP(); 
//				NOP();      
//			}
            
    }
	
}
//===========================================================




/* 
//触摸运行程序

uchar Tk_PushNum;

void TK_Run(void)
{

	TSC_Start(); 

	if(TSC_DataProcessing()==1)    //返回1 表示所有按键处理完成
	{
		strongest = TSC_GetStrongest(); 
		
        Tk_PushNum = TSC_GetSingle();   //获取按下的按键号
        
		if(strongest!=Sav_strongest)
		{
			switch(strongest)       //触摸按键响应
			{
				case 1:
					
	//						//PA1 =0;

	//                        if(P1ADTL>10)
	//							P1ADTL-=10;
	//                         else
	//							P1ADTL =1;

				P1ADTHL = P1ADTH;
				P1ADTHL <<=8;
				P1ADTHL|=P1ADTL;
				
				if(P1ADTHL>10)
				{
					P1ADTHL-=10;
				}
				else
					P1ADTHL = 0;
				
				p1adt = P1ADTHL;
				P1ADTH = p1adt>>=8;
				
				p1adt = P1ADTHL;
				P1ADTL = p1adt&0x00FF;
				
					
					break;
				 
				case 2:
					
					//PA1 =1;
					
	//                         if(P1ADTL<(0xFF-10))

	//						P1ADTL+=10;
	//                          else
	//                          P1ADTL =0XFF;


				P1ADTHL = P1ADTH;
				P1ADTHL <<=8;
				P1ADTHL|=P1ADTL;
				
				if(P1ADTHL<(PWM1_PR2HL_Value-10))
				{
					P1ADTHL+=10;
				}
				else
					P1ADTHL = PWM1_PR2HL_Value;
				
				p1adt = P1ADTHL;
				P1ADTH = p1adt>>=8;
				
				p1adt = P1ADTHL;
				P1ADTL = p1adt&0x00FF;
				
					break;
					
					default :
					
					break;
			}		
			
			
		}
	//            else
	//             PA1 =1;
		
		Sav_strongest = strongest;
        
		
    if((Sav_strongest!=0)&&(Tk_Push==0))
    {
		Tk_Push =1;     //开始对触发时间计时
        
    }
    else if(Sav_strongest==0)
		{
			Tk_Push =0;   //无触发按键时清空持续按键时间
        }
    
		if(Tk_Push==2)    //计时溢出时
		{
				
		   switch (Sav_strongest)
		   {
				case 1:
					P1ADTHL = P1ADTH;
					P1ADTHL <<=8;
					P1ADTHL|=P1ADTL;
					
					if(P1ADTHL>10)
					{
						P1ADTHL-=10;
					}
					else
						P1ADTHL = 0;
					
					p1adt = P1ADTHL;
					P1ADTH = p1adt>>=8;
					
					p1adt = P1ADTHL;
					P1ADTL = p1adt&0x00FF;
					
					delay_ms(150);
					break;
					
				case 2:
				
					P1ADTHL = P1ADTH;
					P1ADTHL <<=8;
					P1ADTHL|=P1ADTL;
					
					if(P1ADTHL<(PWM1_PR2HL_Value-10))
					{
						P1ADTHL+=10;
					}
					else
						P1ADTHL = PWM1_PR2HL_Value;
					
					p1adt = P1ADTHL;
					P1ADTH = p1adt>>=8;
					
					p1adt = P1ADTHL;
					P1ADTL = p1adt&0x00FF;
					
					delay_ms(150);
					
					break;
				
		   }
			
		}
        
        if(Tk_PushNum==0x03)   //两个按键同时按下的时候 占空比调为50%
        {
			P1ADTH =PWM1_ADTHL_Value>>8;			
			P1ADTL = PWM1_ADTHL_Value&0xff;
        }
        
		
	}
    
}
 */


