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
//Variable definition   �������
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
                if((i!=0)&&(i%50==0))   //��ֹ���Ź���� ��ʱι��
					CLRWDT();
            }
    
}


//===========================================================
//Funtion name��interrupt ISR
//parameters����
//returned value����
//===========================================================


uint Tim2_T =0;
uint P1ADTHL =0;
uint p1adt;
bit LED_F =0;

uchar Tk_Push;
uint Tk_Push_T;
uchar TK_Push_T1;

bit ADC_OK =0;
bit ADC_Start =0;			// ADC������־  ��ʱ���ж�����������
uchar ADC_T=0;
uchar TK_Run_F =0;     // �޼�����ģʽ�� TK ɨ�败��λ
uchar TK_Run_T =0;		//�޼����ⶨʱ 
uchar Run_Mode;   //�ⲿ���ضϿ� ����ģʽ���ⲿ���رպ� �޼�����ģʽ
#define ADC_Time		1    //���ζ�ʱ�����ڽ���һ��ADCɨ��
#define TK_ADJ_T	2

uchar LED_ADJ_Push_T;     // LED  ADJ ģʽ��  ���µ�ʱ��

//#define TK_Run_Time    1   //�޼�����ɨ����
void interrupt ISR(void)
{
	if(TMR2IE && TMR2IF)			//50us�ж�һ�� 
		{
			TMR2IF = 0;
			
            if(Tk_Push==1)   //tk_push =1 ��ʾ������ʱ tk_push =2 ��ʾ��ʱ���  tk_push =0 ��ʾֹͣ��ʱ tk_push������Ҫ�ɼ���ɨ��������
            {
				Tk_Push_T++;
                if(Tk_Push_T>=15000)   //�ۼ�0.5 s
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

			
			// if(Run_Mode==1)		//�޼�����ģʽ��
			// {
			// 	TK_Run_T++;
			// 	if(TK_Run_T>=TK_Run_Time)
			// 	{
			// 		TK_Run_T =0;
			// 		TK_Run_F =1;     //������һ��ɨ��
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
  * @Description  ϵͳʱ�ӡ�IO��ʼ��
  * @param  None
  * @note   
  * @retval  None
  *****************************************************************************
*/

void SYS_INITIAL (void) 
{
	OSCCON = SYS_OSCCON;   //0B01110001 ��//WDT 32KHZ IRCF=110=16MHZ/4=4MHZ,0.25US/T
							//Bit0=1,ϵͳʱ��Ϊ�ڲ�����
							//Bit0=0,ʱ��Դ��FOSC<2��0>����������ѡ��ʱѡ��
                            
	OPTION = 0B00001000;	//Bit3 PSA   Ԥ��Ƶ������λ 0= Ԥ��Ƶ�������Timer0ģ�� 1�������WDT 
							//Bit2��0��Ԥ��Ƶ��ѡ��λ 000: 1:2 
									   
	INTCON = 0;  			//�ݽ�ֹ�����ж�
		
	PORTA = 0B00010000;
	PORTC = 0B00000001;
	PORTB = 0B00000000;
		
	TRISA = 0B00000101;		// 0-��� 1-����   PA2(TKCAP) set input PA4 ADCINPUT
	TRISB = 0B00000000;		// B2-B7  TK7-TK2
	TRISC = 0B00000001;     // C0-C1  TK1-TK0   //PC0����Ϊ���� ģʽ�ж�
		
	WPUA = 0B00000000;     	//PA�˿��������� 1-������ 0-������
	WPUB = 0B00000000;
	WPUC = 0B00000001;		//���� PC0 ������
	
	ANSEL0 = 0B00000101;      // TKCAP ��A2����Ϊģ�������	
  //  ODCONA =0X01;
   // ANSEL0|=0X08;   //���� AN3Ϊģ������˿�

    
 //   WPUA &=0XEF;
//    WPDA &=0XEF;
//    
    
	
//===========================================================
//��TSSOP/SOP20��װ�⣬PA3��PA5�������ó������,�����������޸�
	TRISA3 = 0;			 
	TRISA5 = 0;		
    
  //  ODCONA|=0X01;   //����PA0Ϊ��©���
    
    //PA0 =1;			//���� PA0Ϊ��©	
    
	PA3 = 0;			 
	PA5 = 0;		
      
}


/******************************************************************************
  * @brief  WDT_INITIAL	program
  * @Description  ��ʼ�����ÿ��Ź�Ϊ16λ������������SLEEPģʽ��128ms����
  * @param  None
  * @note   
  * @retval  None
  *****************************************************************************
*/

void WDT_INITIAL (void) 
{
	CLRWDT();              //�忴�Ź�
	WDTCON = 0B00001101;   //bit[6:5]WCKSRC=00=LIRC(32K) 
						   //bit[4:1]WDTPS=0110=1:2048,Ԥ��Ƶ1:1 ��ʱʱ��=(4096*1)/32000=128ms
                           ////�Ѹ�Ϊ 8192 ��Ƶ ����256ms     
						   //bit[0]SWDTEN= 1 ����                      	                  
}


//����PWM���� ����LED��ʾPWM�Ƿ�ʵ��

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
    T2CON0=0X00;               //Bit[6:3]=TOUTPS  ���Ƶ��	0000=1:1~1111=1:16
                            //Bit2=TMR2ON	   1=TIMER2��	0=�ر�
                            //Bit[1:0]=T2CKPS  Ԥ��Ƶ�� 00=1:1 01=1:4 1x=1:16
                            //����Ԥ��Ƶ�Ⱥͺ��Ƶ�ȶ�Ϊ1:1
                            
    T2CON1 = 0X02;			//ʱ��ԴΪ2xHIRC��
							//PWM1����Ϊ����ģʽ
							//�رշ�����ģʽ
    

   PR2H =PWM1_PR2H_Value;
   PR2L =PWM1_PR2L_Value;    //20k@50us

	
    
    
    TMR2H =0;
    TMR2L =0;
    
    P1OE2 =0;
    
    P1OE = 0X10;    //ʹ�� PA1���PWM����  
    
    P1CON = 0X00;  //��������Ϊ0
    
    P1POL = 0X00;		//P1A2�������(LED�͵�ƽ��Ч)

	P1ADTH =0;//PWM1_ADTHL_Value>>8;			//P1Aռ�ձ�Ϊ5/65535
	P1ADTL = 0;//PWM1_ADTHL_Value&0xff;

    
    T2CON0 = T2CON0|0X04;  //����Timer2ʹ��
    
    TMR2IE =1;		//������ʱ��2�ж�
    
    GIE =1;
	
}


/*********************************************************

ADC��ʼ������

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
	ADCON1 = 0B10100101; 	//�Ҷ��룬ת��ʱ��SysClk/32�����ο���ѹGND�����ο���ѹVDD
  	//Bit7:ADFM A/Dת�������ʽ 
	//1 = �Ҷ��롣 
	//0 = ����롣
  
  	//Bit6~Bit4:ADCS ADCת��ʱ��Դ
    //TSEL=2T
	//000 = SysClk/2
	//001 = SysClk/8
	//010 = SysClk/32
	//011 = SysClk
	//100 = SysClk/4
	//101 = SysClk/16
	//110 = SysClk/64
	//111 = LIRC
	
	//Bit3~Bit2:ADNREF ADC���ο���ѹ
	//00 = Int Vref���ڲ��ο���ѹ��
	//01 = GND
	//10 = Int Vref + Ext Cap���ڲ��ο���ѹ + �ⲿ���ݣ�
	//11 = Ext Vref���ⲿ�ο���ѹ��

  	//Bit1~Bit0:ADPREF ADC���ο���ѹ
	//00 = Int Vref���ڲ��ο���ѹ��
	//01 = VDD
	//10 = Int Vref + Ext Cap���ڲ��ο���ѹ + �ⲿ���ݣ�
	//11 = Ext Vref���ⲿ�ο���ѹ��
    
	ADCON0 = 0B00000000; 	
  	//Bit6~Bit3:CHS ADCģ��ͨ��ѡ��λ
	//0000 = AN0
	//0001 = AN1
	//0010 = AN2
	//0011 = AN3
	//0100 = AN4
	//0101 = AN5
	//0110 = AN6
	//0111 = AN7
	//1xxx = Int Vref���ڲ��ο���ѹ��

    //Bit2:ADEX	 ADC��������
	//0 = ����λָ��GO/DONE�����������
	//1 = ��PA4��PWM��λG0/DONE��Ӳ��������
		
    //Bit1:G0/DONE ADCת��������״̬λ
    //0 = A/Dת�����/δ����ת��
	//1 = A/Dת�����ڽ��л�Ӳ��������ʱ���ڼ���

    //Bit0:ADON ʹ��ADC  
    //0 = ADC����ֹ�Ҳ����Ĺ�������
	//1 = ADC��ʹ��
              

	ADC_DelayUs(200);	
    ADC_DelayUs(250);           //����Ҫ��ʱ450us
    			   			 			
    ADCON2 = 0B00000000; 	//ѡ���ڲ����ο���ѹ0.5V�����ⲿ����Դ
    //Bit7~Bit6:ADINTREF ADC�ڲ��ο���ѹ
	//00 = 0.5V
	//01 = 2.0V
	//10 = 3.0V
	//11 = δ����
		
	//Bit5~Bit4:ETGTYP �ⲿ�����أ���ADEX=1ʱ���ã�
	//00 = PWM �� ADC_ETR�ŵ��½���
	//01 = PWM �� ADC_ETR�ŵ�������
		
	//Bit3:ADDLY.8/LEBPR9 ADC�ⲿ������ʱ��������LEB�������ĵ�8λ
		
	//Bit2~Bit0:ETGSEL �ⲿ����Դ����ADEX=1ʱ���ã�
	//ѡ��PWMԴʱ��Ҫ����TIMERΪPWM���ģʽ��ʹ�������
	//000 = P1A0
	//001 = P1A0N
	//010 = P1B
	//011 = P1C
	//100 = P1D
	//101 = ADC_ETR
	//11x = ��


    ADCON3 = 0B00000000; 
    //Bit7:ADFBEN ADC�ȽϽ����Ӧ����ɲ��ʹ��
	//0 = ��ֹ
	//1 = ʹ��
		
	//Bit6:ADCMPOP ADC�Ƚ����������
	//0 = ADC����ĸ߰�λ���ڻ����ADCMPH[7:0]
	//1 = ADC����ĸ߰�λС��ADCMPH[7:0]

	//Bit5:ADCMPEN ADC����Ƚ�ʹ��λ
	//0 = �ر�
	//1 = ʹ��
		
	//Bit3:LEBADT ǰ���������ڽ�����ADC����ʹ��
	//1 = ����ADCת��
	//0 = ������ADCת��

    ADCMPH = 0B00000000;	//ADC�Ƚ���ֵ,��8λ������ADC�����8λ�Ƚ�

   // ADON=1;                 //ʹ��ADC	
    
}

/*-------------------------------------------------
 *  ������: GET_ADC_DATA
 *	���ܣ�  ��ȡͨ��ADCֵ
 *  ���룺  adcChannel ͨ�����
 *  �����  INT����ADֵ(���β������˲�)
 --------------------------------------------------*/

uint GET_ADC_DATA (uchar adcChannel)
{
	uint ADC_Dat;


//    ADC_OK =0;		//ʹ���жϱ�־λ
    ADON =1;
	ADCON0 &= 0B00000011;        				   
    ADCON0 |= adcChannel>>1; 				//���¼���ͨ��ֵ
	ADC_DelayUs(80);                        	//͢ʱ�ȴ���ѹ�ȶ� Tst >10us
    
//    ADON =1;		//���� ADC  �ȴ�PWM����
//	ADCIE =1;
//    
	ADCON0 = ADCON0|0x02;             		//����ADC 
    NOP();
    NOP();
    
	while(ADCON0&0x02);    					//�ȴ�ADCת�����
//	while(ADC_OK==0);
  //  ADCIE =0;
//    ADC_OK =0;

	ADC_Dat=ADRESH;
	ADC_Dat<<=8;
    ADC_Dat+=ADRESL;
    ADON =0;
    return  ADC_Dat;      //����12λADֵ
} 

/**************************************************

��ʼ���ⲿ����ADC
ʹ���ڲ�2V�ο���

***************************************************/

void ADC_AN3_Init()
{

	ADCON1 = 0B11100100; 	//�Ҷ��룬ת��ʱ��SysClk/32�����ο���ѹGND�����ο���ѹVDD��ʹ���ڲ��ο���ѹ
	ADCON0 = 0B00000000; 	//ʹ���ⲿ����
	
	ADC_DelayUs(200);	
    ADC_DelayUs(250);           //����Ҫ��ʱ450us
    			   			 			
    ADCON2 = 0B01000000; 	//ѡ���ڲ����ο���ѹ0.5V�����ⲿ����Դ     
    ADCON3 = 0B00000000; 
    ADCMPH = 0B00000000;	//ADC�Ƚ���ֵ,��8λ������ADC�����8λ�Ƚ�
    
    
 
   // ADON=1;                 //ʹ��ADC	
    
}




ulong ADC_Test_VDD()
{
		adcData = GET_ADC_DATA(0X80);		//VDD����׼�����ڲ��ο�ͨ����ADֵ
		//adcData>>=4;						//ADֵ��С16��
        
        VDD_Voltage = (ulong)((204800/adcData));
        
        NOP();
        NOP();
        
        return VDD_Voltage;
    
}

/*************************************

�ַ������� �Բ�����������λ������

���룺 *s �ַ���  l �ַ�������   l��������10
�������λ��ƽ��ֵ

*************************************/
uint String_Sort_Tab[10];
uchar String_Sort_Warning;
uint String_Sort(uint *s,uchar l)
{

	uint Dat;//,Dat1;   //Dat �� Dat��ȡ������
    
    String_Sort_Warning =0;
    for(uchar i =0;i<10;i++)
		String_Sort_Tab[i] =0;
    for(uchar i =0;i<l;i++)
    {
		String_Sort_Tab[i] =*s;
        s++;
    }
    
    for(uchar i =0;i<l;i++)			//���ַ�������ð��
    {
		Dat =String_Sort_Tab[i];
        
        for(uchar is =i;is<l;is++)
        {
			if(Dat>=String_Sort_Tab[is]);
            else
            {
				String_Sort_Tab[i] =String_Sort_Tab[is];			//���ϴ����ַ�����λ
                String_Sort_Tab[is]=Dat;    //����С���ַ��ڱȽ�λ
                Dat = String_Sort_Tab[i];  //��ȡ�ϴ�ֵ�����Ƚ�
            }
        }
        //���ѭ���� Datֵ�Ѿ��Ƿ�Χ����������    
	}
    Dat =0;
	for(uchar i =0;i<l;i++)
		Dat+=String_Sort_Tab[i];
	
    Dat/=l;      //����ƽ����
    
    if(String_Sort_Tab[0]>150)    //�����ݲ�����ʱ������λ��
    {
		if((String_Sort_Tab[0]-String_Sort_Tab[9])>(String_Sort_Tab[0]/5))
		{
			Dat =0;
		//	String_Sort_Warning =1;    //��ֵ̫���쳣λ��1
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
 *��������
 * ���صƹ���  
 * ������������
 * ������������PWM�������ȶ�����
 * 
 * *********************************************************/

/* 
uchar Tk_PushNum;

void TK_Run(void)
{

	TSC_Start(); 

	if(TSC_DataProcessing()==1)    //����1 ��ʾ���а����������
	{
		strongest = TSC_GetStrongest(); 
		
        Tk_PushNum = TSC_GetSingle();   //��ȡ���µİ�����
        
		if(strongest!=Sav_strongest)
		{
        
 */



#define LED_Lv1_Cur 		100   /// LED 1������
#define LED_Lv2_Cur 		300   /// LED 2������
#define LED_Lv3_Cur 		500   /// LED 3������

#define LED_LV1_Cur_Off		5		//LED 1������ ƫ�����
#define LED_LV2_Cur_Off		5		//LED 2������ ƫ�����
#define LED_LV3_Cur_Off		5		//LED 3������ ƫ�����

#define LED_LV1_Dyty	20			//LED 1��ռ�ձ�%
#define LED_LV2_Dyty	30			//LED 1��ռ�ձ�%
#define LED_LV3_Dyty	40			//LED 1��ռ�ձ�%

#define PWM1_LED_PWM_H_Max_Value  1600		//�趨 LED_PWM_H ���ֵ
#define LED_Max_Cur_Dat  500		//ͨ�� LED ���������޼�ģʽ��Ч��

uchar Tk_PushNum;
// uchar Tk_Push =0;   //��������������־ 
// uint Tk_Push_T;

uchar LED_Cur_LV_Num =0;
uint LED_Cur_LV_Dat =0;
uchar LED_Cur_off_Dat =0;

uchar LED_Dyty_LV_Num =0;
uchar LED_Dyty_LV_Dat =0;

unsigned char strongest = 0; //demo_test   �»�ȡ���Ĵ������
unsigned char Sav_strongest = 0; //demo_test   //�����ڱ��صĴ���������ڱȶ�

 
uint LED_PWM_H =0;		//ռ�ձ� 1-100;
uint LED_PWN_N =0;

uint LED_PWM_H_Max;			//ռ�ձ�����

uint LED_PWM_H_SV =0;		//���� LED_PWM_H ��ֵ

uchar LED_Cur_OK =0;			// LED ���ȵ������

uchar LED_ADJ_Stop =0;			//LED_ADJ_Stop  ����һ��ֻ����һ�ο���ѭ�����رպ���Ҫ�ɿ��ٰ�

uint LED_adj_SV_dat=0;			//�����ϴεĹر�����

uint LED_ADJ_P1ADTH=0;		//�����ϴ�ռ�ձ�
uint LED_ADJ_P1ADTL=0;
uint LED_Cur;				//LED ʵʱ����
//uint LED_ADJ_Set_Cur;			// LED �������õ��� ͬʱ��LED_Cur_LV_Dat ���


uchar LED_ADJ_Dir=0;			//���ⷽ��
uchar LED_TH1_OP_Flag =0;			//ͨ���̰������ִ������Ʊ�־

uchar LED_ADJ_OP; 			// LED �޼����� ����  0 �� 1 ��
#define LED_ADJ_Div			15		// LED �޼�����ֶ�ֵ
#define LED_ADJ_Min_Cur		50		//LED�޼����� ��С����������ADC�����趨���50���LED_Max_Cur_Dat��

#define LED_PWM_H_ADJ_Min 50     //�޼�������Сֵ


void TK_TG_Run()
{
	TSC_Start(); 					//��ʼ����ɨ��
	if(TSC_DataProcessing()==1)   //����1 ��ʾ���а����������
	{
		strongest = TSC_GetStrongest();
		Tk_PushNum = TSC_GetSingle();

		if(Run_Mode==0)
		{
		
			if(strongest!=Sav_strongest)
			{
				switch (strongest)
				{
				case 1: 		//����������ʱ   

					if(LED_Cur_LV_Num<3)		//����ѭ������
					{
                    
						LED_Cur_LV_Num++;
//                        switch(LED_Cur_LV_Num)
//                        {
//							case 1:
//                            LED_PWM_H =200;		//̧�ߵ�����PWM
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
						LED_PWN_N =0;		//���ռ�ձ�ֵ
					}

					break;

				default:
					break;
				}

				switch (LED_Cur_LV_Num)    //�����ȼ�ƥ��
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
						LED_PWM_H =200;		//̧�ߵ�����PWM
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

				if((Tk_Push==1)&&(strongest!=Sav_strongest))		//��ʾ�ڶ�ʱ������ɰ���������ִ�п���
                {
					Tk_Push=0;		//��մ���λ
					if((LED_ADJ_OP==1)&&(LED_TH1_OP_Flag==0))		//�ص�
					{
							LED_ADJ_OP =0;
							LED_Cur_LV_Num =0;

                            LED_ADJ_P1ADTH = P1ADTH;	//����ռ�ձȸ�λ                            
							P1ADTH =0;					//��յ�λռ�ձ�

							LED_ADJ_P1ADTL = P1ADTL;	//����ռ�ձȵ�λ
							P1ADTL =0;					//��յ�λռ�ձ�
                            
							LED_PWM_H_SV = LED_PWM_H;		//���� PWM_PWM_H
							LED_PWM_H =0;
							LED_PWN_N =0;		//���ռ�ձ�ֵ
                            LED_adj_SV_dat=LED_Cur_LV_Dat;
							LED_Cur_LV_Dat =0;
							LED_ADJ_Dir =0;				//�صƸ�λ���ⷽ��
							PA4 =0;

                    }
                    else
                    if((LED_ADJ_OP==0)&&(LED_TH1_OP_Flag==0))		//����
                    {

								LED_ADJ_OP =1;
								LED_Cur_LV_Dat = LED_adj_SV_dat;		//ʹ�ñ�������
								if(LED_Cur_LV_Dat<LED_ADJ_Min_Cur)
									LED_Cur_LV_Dat =LED_ADJ_Min_Cur;						//����50 ������
								P1ADTH = LED_ADJ_P1ADTH;				//  ʹ�ñ��ݵ����ݸ���PWM�Ĵ���
								P1ADTL = LED_ADJ_P1ADTL;
								LED_PWM_H = LED_PWM_H_SV;				//���ñ�������
								PA4 =1;										//�ر�ָʾ��
								LED_Cur_off_Dat =LED_LV1_Cur_Off;

                    }
                }
                
                if((Tk_Push==2)&&(strongest!=Sav_strongest))		//��ʾ����֮��
				{
					Tk_Push=0;
                    if(LED_ADJ_Dir==0)			//���ⷽ��
						LED_ADJ_Dir =1;	//ȡ��
                     else
						LED_ADJ_Dir =0;

					
                }               
				break;

				case 1:
					

					if(Sav_strongest != strongest)		//keyֵ�仯����¼����ʱ��
                    {
						Tk_Push =1;
						if(LED_ADJ_OP==0)		//���û���� �ȿ���
						{

								LED_TH1_OP_Flag =1;
								LED_ADJ_OP =1;
								LED_Cur_LV_Dat = LED_adj_SV_dat;		//ʹ�ñ�������
								if(LED_Cur_LV_Dat<LED_ADJ_Min_Cur)
									LED_Cur_LV_Dat =LED_ADJ_Min_Cur;						//����50 ������
								P1ADTH = LED_ADJ_P1ADTH;				//  ʹ�ñ��ݵ����ݸ���PWM�Ĵ���
								P1ADTL = LED_ADJ_P1ADTL;
								LED_PWM_H = LED_PWM_H_SV;				//���ñ�������
								PA4 =1;										//�ر�ָʾ��
								LED_Cur_off_Dat =LED_LV1_Cur_Off;
						}
						else
						LED_TH1_OP_Flag =0;
                    }

					if((Tk_Push==2)&&(LED_ADJ_OP==1))		//����һ��ʱ���
					{

						
						if((LED_ADJ_Dir==0)&&(LED_Cur_OK==1))  //���ϵ���
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
								LED_Cur_LV_Dat =LED_Cur;			//�����������趨Ϊ��ǰ����
							else
								LED_Cur_LV_Dat =LED_Max_Cur_Dat;
						}

						if((LED_ADJ_Dir==1)&&(LED_Cur_OK==1))   //���µ���
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
								LED_Cur_LV_Dat =LED_Cur;			//�����������趨Ϊ��ǰ����
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

������ɨ�� ADC
ͨ����ʱ���ж϶�ʱ��������   �ݶ�10ms����һ��

************************************************************/


#define LED_PWM_AD_Dat_Len  10       //LED_PWM_AD_Dat  ���ݳ���
#define LED_PWM_PJ_Val_Len 	5		//LED_PWM_PJ_Val_Len  ���ݳ���
#define LED_PWM_PJ_Cur_Len  5		//LED_PWM_PJ_Cur_Len  ���ݳ���



//uint LED_ON_AD_Dat[10];
//uint LED_OFF_AD_Dat[10];
uint LED_PWM_AD_Dat[LED_PWM_AD_Dat_Len];
uchar LED_PWM_AD_Num =0;    // LED_PWM_AD_Dat ��ǰ�洢��������

uint AD_PWM_PJ_Dat;  //���� ADƽ��ֵ
//uint AD_OFF_PJ_Dat;  //���� ADƽ��ֵ
//uint AD_ON_PJ_Dat;   //���� ADƽ��ֵ

uint LED_PWM_PJ_Cur[LED_PWM_PJ_Cur_Len];
uchar LED_PWM_PJ_Cur_Num =0;    //LED_PWM_PJ_Cur    ��ǰ�洢��������

uint LED_PWM_PJ_Val[LED_PWM_PJ_Val_Len];
uchar LED_PWM_PJ_Val_Num =0;	//LED_PWM_PJ_Val  ��ǰ�洢��������





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
            
				LED_PWM_AD_Dat[LED_PWM_AD_Num++] = GET_ADC_DATA(0x00);			//����һ��ADC

                
				if(LED_PWM_AD_Num<LED_PWM_AD_Dat_Len)      //�����������㹻ʱ������һ��
					ADC_now =1;			//ADC�������ݲ����������²�
                else if(LED_PWM_AD_Num>=LED_PWM_AD_Dat_Len)
                {
					LED_PWM_AD_Num =0;
					ADC_now=2;			//ADC���������㹻�����²�ת��Ϊ��ѹ
                }
				break;
                
            case 2:

					//LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num++] =(ulong)200000/4096*(String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len))/100;//String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len)/2;

				LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num++] = (String_Sort(LED_PWM_AD_Dat,LED_PWM_AD_Dat_Len))/2;
                
                LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num]+=(LED_PWM_PJ_Val[LED_PWM_PJ_Val_Num]/50)*12/10;   //������ֵ
                
                
                if(String_Sort_Warning==1)		//������������
                {
					LED_PWM_PJ_Val_Num-=1;			//��������
                    String_Sort_Warning =0;			//��ձ�־λ
                }   
                
                if(LED_PWM_PJ_Val_Num<LED_PWM_PJ_Val_Len)   //�����������㹻ʱ������һ��
					ADC_now=1;									//�������²ɼ�һ������
					else if(LED_PWM_PJ_Val_Num>=LED_PWM_PJ_Val_Len)
                    {
						LED_PWM_PJ_Val_Num =0;	
						ADC_now=3;
                    }
				break;
			
            case 3:
				
				LED_PWM_PJ_Cur[LED_PWM_PJ_Cur_Num++] = String_Sort(LED_PWM_PJ_Val,LED_PWM_PJ_Val_Len);
                
                if(String_Sort_Warning==1)		//������������
                {
                
					LED_PWM_PJ_Val_Num-=1;			//��������
                    String_Sort_Warning =0;
                    
                }
                
                if(LED_PWM_PJ_Cur_Num<LED_PWM_PJ_Cur_Len)			//�����������㹻ʱ������һ��
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
            
            case 5:   //���ݵ���΢��ռ�ձ�  ����1��
            
			if(LED_Cur_LV_Num||((Run_Mode==1)&&(LED_ADJ_OP==1)&&(Tk_Push==0)))			//�޼�����ģʽ����һ�ο���ʱ������΢������������¶��������������� ��������ʱ��������
			{

					if(LED_Cur>LED_Cur_LV_Dat)
					{
						if((LED_Cur-LED_Cur_LV_Dat)>LED_Cur_off_Dat)  //����һ�� �½�1%
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
							if((LED_Cur_LV_Dat-LED_Cur)>LED_Cur_off_Dat)    //С��һ��  ���� 1%
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
							//��������ʱ������������ɷ���
							LED_Cur_OK =1;
						}
				// else if((Run_Mode==1)&&(First_OP_ADJ_LED==1))
				// {
				// 	if(LED_Cur>LED_ADJ_Set_Cur)
				// 	{
				// 		if((LED_Cur-LED_ADJ_Set_Cur)>LED_Cur_off_Dat)  //����һ�� �½�1%
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
				// 			if((LED_ADJ_Set_Cur-LED_Cur)>LED_Cur_off_Dat)    //С��һ��  ���� 1%
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



//void TK_Run(void);     //���д�������
//===========================================================
//Funtion name��main
//parameters����
//returned value����
//���Դ���ʱ��Ҫ�ε�FMD link ����Ҫ�����ϵ��������TH2 ��������оƬ���ڵ���ģʽ
//������Ϊ�Ǹ�λ�źŵ���оƬ��λ
//===========================================================
ulong VDD_Value;
uint VDD_V_Tab[10];

main()
{
	SYS_INITIAL(); //ϵͳʱ�ӡ�IO��ʼ��   
    T2CON0=0;		//�ر�PWM��ʱ��
	TOUCH_INITIAL();//����������ʼ��
	WDT_INITIAL(); //���Ź���ʼ��
	PEIE = 1;  //ʹ�������ж�
	GIE = 1; //ʹ��ȫ���ж�

	TRISA&=0xfD;		//����PA1Ϊ���
	TRISA&=0xEF;		//����PA4Ϊ���
	


    ADC_AN3_Init();

	PA1 =0;  //�ر�LED
     
	
    PWM_Init();		//ʹ�� PWM 
	
    delay_ms(5000);			//�ȴ��ȶ�
    
	while(1)
    {
		if(LED_Cur_LV_Num==0)
		{
			if(PC0==1)   //�ж��ⲿģʽ����
			{
				if(Run_Mode==1)
                {
					LED_Cur_LV_Num =0;
					LED_Cur_LV_Dat =0;
					P1ADTH =0;
					P1ADTL =0;
					LED_PWM_H =0;
					LED_PWN_N =0;		//���ռ�ձ�ֵ
                }
                
                Run_Mode =0;			//����޼�����ֵ
			}
			else if((PC0==0)&&(Run_Mode==0))
			{
				LED_ADJ_OP =0;  //Ĭ�Ϲص�
				PA4 =0;			//��ָʾ��
				Run_Mode =1;
			}
		}

		if((LED_Cur_LV_Num==0)&&(Run_Mode==0))   //������������ ָʾ��
		{
			PA4 =0;
		}
		else if((LED_Cur_LV_Num!=0)&&(Run_Mode==0))
		{
			PA4 =1;
		}

		//�忴�Ź�   
        ADC_Run();

		CLRWDT(); 
		//����ɨ�� 
		TK_TG_Run();
       // TK_Run();

//	   if(LED_Cur_LV_Num==0)
//	   		{
//				CLRWDT();  		//�忴�Ź�
//				NOP();
//     			SLEEP(); 
//				NOP();      
//			}
            
    }
	
}
//===========================================================




/* 
//�������г���

uchar Tk_PushNum;

void TK_Run(void)
{

	TSC_Start(); 

	if(TSC_DataProcessing()==1)    //����1 ��ʾ���а����������
	{
		strongest = TSC_GetStrongest(); 
		
        Tk_PushNum = TSC_GetSingle();   //��ȡ���µİ�����
        
		if(strongest!=Sav_strongest)
		{
			switch(strongest)       //����������Ӧ
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
		Tk_Push =1;     //��ʼ�Դ���ʱ���ʱ
        
    }
    else if(Sav_strongest==0)
		{
			Tk_Push =0;   //�޴�������ʱ��ճ�������ʱ��
        }
    
		if(Tk_Push==2)    //��ʱ���ʱ
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
        
        if(Tk_PushNum==0x03)   //��������ͬʱ���µ�ʱ�� ռ�ձȵ�Ϊ50%
        {
			P1ADTH =PWM1_ADTHL_Value>>8;			
			P1ADTL = PWM1_ADTHL_Value&0xff;
        }
        
		
	}
    
}
 */


