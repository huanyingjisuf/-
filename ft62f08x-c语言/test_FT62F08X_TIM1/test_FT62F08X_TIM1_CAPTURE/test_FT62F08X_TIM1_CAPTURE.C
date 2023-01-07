//********************************************************* 
/* ÎÄ¼þÃû: TEST_62F08x_TIM1_CAPTURE.c
* ¹¦ÄÜ£º   FT62F08x_TIM1_CAPTURE¹¦ÄÜÑÝÊ¾
* IC:      FT62F088 LQFP32
* ÄÚ²¿£º   16M
* empno:   500                                
* ËµÃ÷£º   Àý³ÌÍ¨¹ýTIM1µÄ²¶»ñÍ¨µÀ1²âÁ¿TIM4Êä³öµ½PB3µÄ²¨ÐÎµÄÖÜÆÚ£¨4K£©
*		   TIM1¼ÆÊýÆ÷²¶»ñµÄÊý¾Ý·ÅÔÚtestdataÊý×éÀï£¬Ò»¹²20¸ö¡£
*          ³ÌÐòÖ»ÓÃµ½Ò»¸öÊý¾Ý(testdata[1])À´¼ÆËãÖÜÆÚ¡£		    
*
*   ²Î¿¼Ô­ÀíÍ¼ TEST_62F08x_sch.pdf
*/
//*********************************************************
#include "SYSCFG.h"
//***********************ºê¶¨Òå****************************
#define  unchar     unsigned char 
#define  unint      unsigned int

#define  DemoPortOut	PB3   
#define  DemoPortOut1	PB4

volatile unint 	testdata[20];
volatile unchar y=0;
volatile unchar dataH;
volatile unchar dataL;
volatile unint  period=0;
/*-------------------------------------------------
 * º¯ÊýÃû£ºinterrupt ISR
 * ¹¦ÄÜ£º  ¶¨Ê±Æ÷4µÄÖÐ¶Ï´¦Àí
 * ÊäÈë£º  ÎÞ
 * Êä³ö£º  ÎÞ
 --------------------------------------------------*/
void interrupt ISR(void)            	
{ 
	if(T4UIE && T4UIF)                	
	{
		T4UIF = 1;                    	//Ð´1ÇåÁã±êÖ¾Î»             
		DemoPortOut = ~DemoPortOut; 	//·­×ªµçÆ½
	} 
    if(T1CC1IE && T1CC1IF)              //²¶»ñÖÐ¶Ï
    {
    	T1CC1IF=1;
        
        T1CC1OF=0;
        DemoPortOut1 = ~DemoPortOut1;   //²¶»ñÖÐ¶Ïµ÷ÊÔ²é¿´         
        dataH = TIM1CCR1H;
        dataL = TIM1CCR1L;
        testdata[y++] =(unint)(dataH<<8 | dataL);
        NOP();
        
        if(y>=20)
        {
        	y=0;
            
            //¼ÆËãÖÜÆÚ(us)
            period = testdata[1]/32;   //ÖÜÆÚÔ¼µÈÓÚ250us
            NOP();
            NOP();
            NOP();
        }
    }
}  
/*-------------------------------------------------
 * º¯ÊýÃû£ºPOWER_INITIAL
 * ¹¦ÄÜ£º  ÉÏµçÏµÍ³³õÊ¼»¯
 * ÊäÈë£º  ÎÞ
 * Êä³ö£º  ÎÞ
 --------------------------------------------------*/	
void POWER_INITIAL (void) 
{
	 
	OSCCON = 0B01110001;	//IRCF=111=16MHz 1:1
	INTCON = 0;  			//ÔÝ½ûÖ¹ËùÓÐÖÐ¶Ï
    
	PORTA = 0B00000000;		
	TRISA = 0B00000001;		//PAÊäÈëÊä³ö 0-Êä³ö 1-ÊäÈë  PA0-IN
	PORTB = 0B00000000;		
	TRISB = 0B00000000;		//PBÊäÈëÊä³ö 0-Êä³ö 1-ÊäÈë	PB3,PB4-OUT						
	PORTC = 0B00000000; 	
	TRISC = 0B00000000;		//PCÊäÈëÊä³ö 0-Êä³ö 1-ÊäÈë  	
    PORTD = 0B00000000;		
	TRISD = 0B00000000;		//PDÊäÈëÊä³ö 0-Êä³ö 1-ÊäÈë
	
	WPUA = 0B00000000;     	//PA¶Ë¿ÚÉÏÀ­¿ØÖÆ 1-¿ªÉÏÀ­ 0-¹ØÉÏÀ­
	WPUB = 0B00000000;     	//PB¶Ë¿ÚÉÏÀ­¿ØÖÆ 1-¿ªÉÏÀ­ 0-¹ØÉÏÀ­
	WPUC = 0B00000000;     	//PC¶Ë¿ÚÉÏÀ­¿ØÖÆ 1-¿ªÉÏÀ­ 0-¹ØÉÏÀ­
	WPUD = 0B00000000;     	//PD¶Ë¿ÚÉÏÀ­¿ØÖÆ 1-¿ªÉÏÀ­ 0-¹ØÉÏÀ­
    
    WPDA = 0B00000000;     	//PA¶Ë¿ÚÏÂÀ­¿ØÖÆ 1-¿ªÏÂÀ­ 0-¹ØÏÂÀ­
	WPDB = 0B00000000;     	//PB¶Ë¿ÚÏÂÀ­¿ØÖÆ 1-¿ªÏÂÀ­ 0-¹ØÏÂÀ­
	WPDC = 0B00000000;     	//PC¶Ë¿ÚÏÂÀ­¿ØÖÆ 1-¿ªÏÂÀ­ 0-¹ØÏÂÀ­
	WPDD = 0B00000000;     	//PD¶Ë¿ÚÏÂÀ­¿ØÖÆ 1-¿ªÏÂÀ­ 0-¹ØÏÂÀ­
    
    PSRC0  = 0B11111111;  	//PORTA,PORTBÔ´µçÁ÷ÉèÖÃ×î´ó
    PSRC1  = 0B11111111;    //PORTC,PORTDÔ´µçÁ÷ÉèÖÃ×î´ó    
    
    PSINK0 = 0B11111111;  	//PORTA¹àµçÁ÷ÉèÖÃ×î´ó 0:×îÐ¡£¬1:×î´ó
    PSINK1 = 0B11111111; 	//PORTB¹àµçÁ÷ÉèÖÃ×î´ó 0:×îÐ¡£¬1:×î´ó
    PSINK2 = 0B11111111;	//PORTC¹àµçÁ÷ÉèÖÃ×î´ó 0:×îÐ¡£¬1:×î´ó
    PSINK3 = 0B11111111;	//PORTD¹àµçÁ÷ÉèÖÃ×î´ó 0:×îÐ¡£¬1:×î´ó
	
    ANSELA = 0B00000000;    //È«ÎªÊý×Ö¹Ü½Å
}
/*-------------------------------------------------
 * º¯ÊýÃû³Æ£ºTime4Initial
 * ¹¦ÄÜ£º  
 * ÊäÈë²ÎÊý£º
 * ·µ»Ø²ÎÊý£ºÎÞ 
 -------------------------------------------------*/
void Time4Initial(void)
{
	PCKEN |=0B00001000;      	//TIME4Ä£¿éÊ±ÖÓÊ¹ÄÜ		
    
    TIM4CR1	=0B00000001;
    //Bit7: 0£ºTIM1_ARR¼Ä´æÆ÷Ã»ÓÐ»º³å£¬Ëü¿ÉÒÔ±»Ö±½ÓÐ´Èë; 1£ºTIM1_ARR¼Ä´æÆ÷ÓÉÔ¤×°ÔØ»º³åÆ÷»º³å¡£
    //Bit6: ±£Áô
    //Bit[5:4]: timer4Ê±ÖÓÑ¡ÔñÎ»¡£
	//00£ºÏµÍ³Ê±ÖÓ/Ö÷Ê±ÖÓ
	//01£ºÄÚ²¿¿ìÊ±ÖÓHIRC
	//10£ºLPÊ±ÖÓ£¬Ö»ÓÐµ±FOSCÑ¡ÔñLPÄ£Ê½Ê±²ÅÓÐÒâÒå
	//11£ºXTÊ±ÖÓ£¬Ö»ÓÐµ±FOSCÑ¡ÔñXTÄ£Ê½Ê±²ÅÓÐÒâÒå

    //Bit3:µ¥Âö³åÄ£Ê½
    //0£ºÔÚ·¢Éú¸üÐÂÊÂ¼þÊ±£¬¼ÆÊýÆ÷²»Í£Ö¹£»
	//1£ºÔÚ·¢ÉúÏÂÒ»´Î¸üÐÂÊÂ¼þ(Çå³ýCENÎ»)Ê±£¬¼ÆÊýÆ÷Í£Ö¹¡£

    //Bit2:¸üÐÂÇëÇóÔ´
   	//0£ºÈç¹ûUDISÔÊÐí²úÉú¸üÐÂÊÂ¼þ£¬ÔòÏÂÊöÈÎÒ»ÊÂ¼þ²úÉúÒ»¸ö¸üÐÂÖÐ¶Ï£º
	//¼Ä´æÆ÷±»¸üÐÂ(¼ÆÊýÆ÷ÉÏÒç/ÏÂÒç)
	//Èí¼þÉèÖÃUGÎ»
	//Ê±ÖÓ/´¥·¢¿ØÖÆÆ÷²úÉúµÄ¸üÐÂ
	//1£ºÈç¹ûUDISÔÊÐí²úÉú¸üÐÂÊÂ¼þ£¬ÔòÖ»ÓÐµ±ÏÂÁÐÊÂ¼þ·¢ÉúÊ±²Å²úÉú¸üÐÂÖÐ¶Ï£¬²¢UIFÖÃ1£º
	//¼Ä´æÆ÷±»¸üÐÂ(¼ÆÊýÆ÷ÉÏÒç/ÏÂÒç)

    //Bit1:½ûÖ¹¸üÐÂ
    //0£ºÒ»µ©ÏÂÁÐÊÂ¼þ·¢Éú£¬²úÉú¸üÐÂ(UEV)ÊÂ¼þ£º
	//¼ÆÊýÆ÷Òç³ö/ÏÂÒç
	//²úÉúÈí¼þ¸üÐÂÊÂ¼þ
	//Ê±ÖÓ/´¥·¢Ä£Ê½¿ØÖÆÆ÷²úÉúµÄÓ²¼þ¸´Î»±»»º´æµÄ¼Ä´æÆ÷±»×°ÈëËüÃÇµÄÔ¤×°ÔØÖµ¡£
	//1£º²»²úÉú¸üÐÂÊÂ¼þ£¬Ó°×Ó¼Ä´æÆ÷(ARR¡¢PSC¡¢CCRx)±£³ÖËüÃÇµÄÖµ¡£Èç¹ûÉèÖÃÁËUGÎ»»òÊ±ÖÓ/´¥·¢¿ØÖÆÆ÷·¢³öÁËÒ»¸öÓ²¼þ¸´Î»£¬Ôò¼ÆÊýÆ÷ºÍÔ¤·ÖÆµÆ÷±»ÖØÐÂ³õÊ¼»¯¡£

    //Bit0: 0£º½ûÖ¹¼ÆÊýÆ÷£»1£ºÊ¹ÄÜ¼ÆÊýÆ÷¡£

    TIM4IER	= 0B00000001;
    //Bit0:  0£º½ûÖ¹¸üÐÂÖÐ¶Ï£»1£ºÔÊÐí¸üÐÂÖÐ¶Ï¡£

    TIM4SR = 0B00000000;
    //Bit0: µ±²úÉú¸üÐÂÊÂ¼þÊ±¸ÃÎ»ÓÉÓ²¼þÖÃ1¡£ËüÓÉÈí¼þÐ´1Çå0
	//0£ºÎÞ¸üÐÂÊÂ¼þ²úÉú£»
	//1£º¸üÐÂÊÂ¼þµÈ´ýÏìÓ¦¡£µ±¼Ä´æÆ÷±»¸üÐÂÊ±¸ÃÎ»ÓÉÓ²¼þÖÃ1£º
	//ÈôTIM4_CR1¼Ä´æÆ÷µÄUDIS=0£¬µ±¼ÆÊýÆ÷ÉÏÒç»òÏÂÒçÊ±£»
	//ÈôTIM4_CR1¼Ä´æÆ÷µÄUDIS=0¡¢URS=0£¬µ±ÉèÖÃTIM4_EGR¼Ä´æÆ÷µÄUGÎ»Èí¼þ¶Ô¼ÆÊýÆ÷
	//CNTÖØÐÂ³õÊ¼»¯Ê±£»
	//ÈôTIM4_CR1¼Ä´æÆ÷µÄUDIS=0¡¢URS=0£¬µ±¼ÆÊýÆ÷CNT±»´¥·¢ÊÂ¼þÖØÐÂ³õÊ¼»¯Ê±¡£
    
    TIM4EGR = 0B00000000;
    //Bit0:¸ÃÎ»ÓÉÈí¼þÖÃ1£¬ÓÉÓ²¼þ×Ô¶¯Çå0¡£
	//0£ºÎÞ¶¯×÷£»
	//1£ºÖØÐÂ³õÊ¼»¯¼ÆÊýÆ÷£¬²¢²úÉúÒ»¸ö¸üÐÂÊÂ¼þ¡£×¢ÒâÔ¤·ÖÆµÆ÷µÄ¼ÆÊýÆ÷Ò²±»Çå0(µ«ÊÇÔ¤·ÖÆµÏµÊý²»±ä)¡£ÈôÔÚÖÐÐÄ¶Ô³ÆÄ£Ê½ÏÂ»òDIR=0(ÏòÉÏ¼ÆÊý)Ôò¼ÆÊýÆ÷±»Çå0£»ÈôDIR=1(ÏòÏÂ¼ÆÊý)Ôò¼ÆÊýÆ÷È¡TIM1_ARRµÄÖµ¡£

    TIM4CNTR=0; //TIM4 8Î»¼ÆÊýÆ÷
    
    TIM4PSCR=0B00000100;
    //Ô¤·ÖÆµÆ÷¶ÔÊäÈëµÄCK_PSCÊ±ÖÓ½øÐÐ·ÖÆµ¡£
	//¼ÆÊýÆ÷µÄÊ±ÖÓÆµÂÊfCK_CNTµÈÓÚfCK_PSC/2(PSC[2:0])¡£PSC[7:3]ÓÉÓ²¼þÇå0¡£
	//PSCR°üº¬ÁËµ±¸üÐÂÊÂ¼þ²úÉúÊ±×°Èëµ±Ç°Ô¤·ÖÆµÆ÷¼Ä´æÆ÷µÄÖµ(°üÀ¨ÓÉÓÚÇå³ýTIMx_EGR¼Ä´æÆ÷µÄUGÎ»²úÉúµÄ¼ÆÊýÆ÷Çå³ýÊÂ¼þ)£¬
    //ÕâÒâÎ¶×ÅÈçÒªÐÂµÄÔ¤·ÖÆµÖµÉúÐ§£¬±ØÐë²úÉú¸üÐÂÊÂ¼þ»òÕßCEN=0¡£
    
    TIM4ARR	=124;
    //ARR°üº¬ÁË½«Òª×°ÔØÈëÊµ¼ÊµÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷µÄÖµ¡£
	//µ±×Ô¶¯ÖØ×°ÔØµÄÖµÎª¿ÕÊ±£¬¼ÆÊýÆ÷²»¹¤×÷¡£

    INTCON |= 0B11000000;    	//¿ª×ÜÖÐ¶ÏºÍÍâÉèÖÐ¶Ï
  }
/*-------------------------------------------------
 * º¯ÊýÃû£ºTime1Initial
 * ¹¦ÄÜ£º  ³õÊ¼»¯¼ÆÊ±Æ÷1
 * ÊäÈë£º  ÎÞ
 * Êä³ö£º  ÎÞ
 --------------------------------------------------*/		
void Time1_Capture_Initial(void)
{
	PCKEN |= 0B00000010;    	//Ê¹ÄÜtimer1Ê±ÖÓÄ£¿é
    CKOCON = 0B00100000;
    TCKSRC = 0B00000011;    	//TIM1Ê±ÖÓÎªHIRCµÄ2±¶Æµ
    //Bit7µÍÆµÄÚÕñÄ£Ê½£º1=256K Õñµ´ÆµÂÊÄ£Ê½,0 = 32K Õñµ´ÆµÂÊÄ£Ê½
    
    //Bit[6:4]:TIM2Ê±ÖÓÔ´Ñ¡ÔñÎ»
	//Öµ	Ê±ÖÓÔ´
	//0		ÏµÍ³Ê±ÖÓ/Ö÷Ê±ÖÓ
	//1		HIRC
	//2		XTÊ±ÖÓ/Íâ²¿Ê±ÖÓ
	//3		HIRCµÄ2±¶Æµ
	//4		XTÊ±ÖÓ/Íâ²¿Ê±ÖÓµÄ2±¶Æµ
	//5		LIRC
	//6		LPÊ±ÖÓ/Íâ²¿Ê±ÖÓ
	//7		LPÊ±ÖÓ/Íâ²¿Ê±ÖÓµÄ2Î»Æµ
    
	//Bit3:±£ÁôÎ»
    
	//Bit[2:1]:TIM1Ê±ÖÓÔ´Ñ¡ÔñÎ»
	//Öµ	Ê±ÖÓÔ´
	//0		ÏµÍ³Ê±ÖÓ/Ö÷Ê±ÖÓ
	//1		HIRC
	//2		XTÊ±ÖÓ/Íâ²¿Ê±ÖÓ
	//3		HIRCµÄ2±¶Æµ
	//4		XTÊ±ÖÓ/Íâ²¿Ê±ÖÓµÄ2±¶Æµ
	//5		LIRC
	//6		LPÊ±ÖÓ/Íâ²¿Ê±ÖÓ
	//7		LPÊ±ÖÓ/Íâ²¿Ê±ÖÓµÄ2Î»Æµ


    TIM1CR1 = 0B00000110;  		//Ô¤ÔØÔÊÐí£¬±ßÑØ¶ÔÆëÏòÉÏ¼ÆÊýÆ÷£¬¼ÆÊýÆ÷Ê¹ÄÜ
    //Bit7:×Ô¶¯Ô¤×°ÔØÔÊÐíÎ»
	//0£ºTIM1_ARR¼Ä´æÆ÷Ã»ÓÐ»º³å£¬Ëü¿ÉÒÔ±»Ö±½ÓÐ´Èë£»
	//1£ºTIM1_ARR¼Ä´æÆ÷ÓÉÔ¤×°ÔØ»º³åÆ÷»º³å¡£
    
	//Bit[6:5]:Ñ¡Ôñ¶ÔÆëÄ£Ê½
	//00£º±ßÑØ¶ÔÆëÄ£Ê½¡£¼ÆÊýÆ÷ÒÀ¾Ý·½ÏòÎ»(DIR)ÏòÉÏ»òÏòÏÂ¼ÆÊý¡£
	//01£ºÖÐÑë¶ÔÆëÄ£Ê½1¡£¼ÆÊýÆ÷½»ÌæµØÏòÉÏºÍÏòÏÂ¼ÆÊý¡£ÅäÖÃÎªÊä³öµÄÍ¨µÀ(TIM1_CCMRx¼Ä´æÆ÷ÖÐCciS=00)µÄÊä³ö±È½ÏÖÐ¶Ï±êÖ¾Î»£¬Ö»ÔÚ¼ÆÊýÆ÷ÏòÏÂ¼ÆÊýÊ±±»ÖÃ1¡£ 
	//10: ÖÐÑë¶ÔÆëÄ£Ê½2¡£¼ÆÊýÆ÷½»ÌæµØÏòÉÏºÍÏòÏÂ¼ÆÊý¡£ÅäÖÃÎªÊä³öµÄÍ¨µÀ(TIM1_CCMRx¼Ä´æÆ÷ÖÐCciS=00)µÄÊä³ö±È½ÏÖÐ¶Ï±êÖ¾Î»£¬Ö»ÔÚ¼ÆÊýÆ÷ÏòÉÏ¼ÆÊýÊ±±»ÖÃ1¡£
	//11£ºÖÐÑë¶ÔÆëÄ£Ê½3¡£¼ÆÊýÆ÷½»ÌæµØÏòÉÏºÍÏòÏÂ¼ÆÊý¡£ÅäÖÃÎªÊä³öµÄÍ¨µÀ(TIM1_CCMRx¼Ä´æÆ÷ÖÐCciS=00)µÄÊä³ö±È½ÏÖÐ¶Ï±êÖ¾Î»£¬ÔÚ¼ÆÊýÆ÷ÏòÉÏºÍÏòÏÂ¼ÆÊýÊ±¾ù±»ÖÃ1¡£
    
	//Bit4:·½Ïò
	//0£º¼ÆÊýÆ÷ÏòÉÏ¼ÆÊý£»
	//1£º¼ÆÊýÆ÷ÏòÏÂ¼ÆÊý¡£
    
	//Bit3:µ¥Âö³åÄ£Ê½
	//0£ºÔÚ·¢Éú¸üÐÂÊÂ¼þÊ±£¬¼ÆÊýÆ÷²»Í£Ö¹£»
	//1£ºÔÚ·¢ÉúÏÂÒ»´Î¸üÐÂÊÂ¼þ(Çå³ýCENÎ»)Ê±£¬¼ÆÊýÆ÷Í£Ö¹¡£
    
	//Bit2:¸üÐÂÇëÇóÔ´
	//0£ºÈç¹ûUDISÔÊÐí²úÉú¸üÐÂÊÂ¼þ£¬ÔòÏÂÊöÈÎÒ»ÊÂ¼þ²úÉúÒ»¸ö¸üÐÂÖÐ¶Ï£º
	//¼Ä´æÆ÷±»¸üÐÂ(¼ÆÊýÆ÷ÉÏÒç/ÏÂÒç)
	//Èí¼þÉèÖÃUGÎ»
	//Ê±ÖÓ/´¥·¢¿ØÖÆÆ÷²úÉúµÄ¸üÐÂ
	//1£ºÈç¹ûUDISÔÊÐí²úÉú¸üÐÂÊÂ¼þ£¬ÔòÖ»ÓÐµ±ÏÂÁÐÊÂ¼þ·¢ÉúÊ±²Å²úÉú¸üÐÂÖÐ¶Ï£¬²¢UIFÖÃ1£º
	//¼Ä´æÆ÷±»¸üÐÂ(¼ÆÊýÆ÷ÉÏÒç/ÏÂÒç)
    
	//Bit1:	½ûÖ¹¸üÐÂ
	//0£ºÒ»µ©ÏÂÁÐÊÂ¼þ·¢Éú£¬²úÉú¸üÐÂ(UEV)ÊÂ¼þ£º
	//¼ÆÊýÆ÷Òç³ö/ÏÂÒç
	//²úÉúÈí¼þ¸üÐÂÊÂ¼þ
	//Ê±ÖÓ/´¥·¢Ä£Ê½¿ØÖÆÆ÷²úÉúµÄÓ²¼þ¸´Î»±»»º´æµÄ¼Ä´æÆ÷±»×°ÈëËüÃÇµÄÔ¤×°ÔØÖµ¡£
	//1£º²»²úÉú¸üÐÂÊÂ¼þ£¬Ó°×Ó¼Ä´æÆ÷(ARR¡¢PSC¡¢CCRx)±£³ÖËüÃÇµÄÖµ¡£Èç¹ûÉèÖÃÁËUGÎ»»òÊ±ÖÓ/´¥·¢¿ØÖÆÆ÷·¢³öÁËÒ»¸öÓ²¼þ¸´Î»£¬Ôò¼ÆÊýÆ÷ºÍÔ¤·ÖÆµÆ÷±»ÖØÐÂ³õÊ¼»¯¡£
    
	//Bit0:	ÔÊÐí¼ÆÊýÆ÷
	//0£º½ûÖ¹¼ÆÊýÆ÷£»
	//1£ºÊ¹ÄÜ¼ÆÊýÆ÷¡£
	
    TIM1SMCR = 0B01010000;
    TIM1SMCR |= 0B00000100;
	//Bit7£º±£ÁôÎ»

	//Bit[6:4]£º´¥·¢Ñ¡Ôñ,Õâ3Î»Ñ¡ÔñÓÃÓÚÑ¡ÔñÍ¬²½¼ÆÊýÆ÷µÄ´¥·¢ÊäÈë¡£
	//000£ºÄÚ²¿´¥·¢ITR0Á¬½Óµ½TIM6 TRGO (´ËÉè¼ÆÃ»ÓÐTIM6£¬ËùÒÔ¹Ì¶¨½Ó0)	
	//001£º±£Áô	
	//010£ºÄÚ²¿´¥·¢ITR2Á¬½Óµ½TIM5 TRGO(´ËÉè¼ÆÃ»ÓÐTIM5£¬ËùÒÔ¹Ì¶¨½Ó0)
	//011£º±£Áô	
	//100£ºTI1µÄ±ßÑØ¼ì²âÆ÷(TI1F_ED)
	//101£ºÂË²¨ºóµÄ¶¨Ê±Æ÷ÊäÈë1(TI1FP1)
	//110£ºÂË²¨ºóµÄ¶¨Ê±Æ÷ÊäÈë2(TI2FP2)
	//111£ºÍâ²¿´¥·¢ÊäÈë(ETRF)
	//×¢£ºÕâÐ©Î»Ö»ÄÜÔÚÎ´ÓÃµ½(ÈçSMS=000)Ê±±»¸Ä±ä£¬ÒÔ±ÜÃâÔÚ¸Ä±äÊ±²úÉú´íÎóµÄ±ßÑØ¼ì²â¡£
    
	//Bit3:±£Áô
    
	//Bit[2:0]£ºÊ±ÖÓ/´¥·¢/´ÓÄ£Ê½Ñ¡Ôñ,µ±Ñ¡ÔñÁËÍâ²¿ÐÅºÅ£¬´¥·¢ÐÅºÅ(TRGI)µÄÓÐÐ§±ßÑØÓëÑ¡ÖÐµÄÍâ²¿ÊäÈë¼«ÐÔÏà¹Ø(¼ûÊäÈë¿ØÖÆ¼Ä´æÆ÷ºÍ¿ØÖÆ¼Ä´æÆ÷µÄËµÃ÷)
	//000£ºÊ±ÖÓ/´¥·¢¿ØÖÆÆ÷½ûÖ¹ ¨C Èç¹ûCEN=1£¬ÔòÔ¤·ÖÆµÆ÷Ö±½ÓÓÉÄÚ²¿Ê±ÖÓÇý¶¯¡£
	//001£º±àÂëÆ÷Ä£Ê½1 ¨C ¸ù¾ÝTI1FP1µÄµçÆ½£¬¼ÆÊýÆ÷ÔÚTI2FP2µÄ±ßÑØÏòÉÏ/ÏÂ¼ÆÊý¡£
	//010£º±àÂëÆ÷Ä£Ê½2 ¨C ¸ù¾ÝTI2FP2µÄµçÆ½£¬¼ÆÊýÆ÷ÔÚTI1FP1µÄ±ßÑØÏòÉÏ/ÏÂ¼ÆÊý¡£
	//011£º±àÂëÆ÷Ä£Ê½3 ¨C ¸ù¾ÝÁíÒ»¸öÊäÈëµÄµçÆ½£¬¼ÆÊýÆ÷ÔÚTI1FP1ºÍTI2FP2µÄ±ßÑØÏòÉÏ/ÏÂ¼ÆÊý¡£
	//100£º¸´Î»Ä£Ê½ ¨C ÔÚÑ¡ÖÐµÄ´¥·¢ÊäÈë(TRGI)µÄÉÏÉýÑØÊ±ÖØÐÂ³õÊ¼»¯¼ÆÊýÆ÷£¬²¢ÇÒ²úÉúÒ»¸ö¸üÐÂ¼Ä´æÆ÷µÄÐÅºÅ¡£
	//101£ºÃÅ¿ØÄ£Ê½ ¨C µ±´¥·¢ÊäÈë(TRGI)Îª¸ßÊ±£¬¼ÆÊýÆ÷µÄÊ±ÖÓ¿ªÆô¡£Ò»µ©´¥·¢ÊäÈë±äÎªµÍ£¬Ôò¼ÆÊýÆ÷Í£Ö¹(µ«²»¸´Î»)¡£¼ÆÊýÆ÷µÄÆô¶¯ºÍÍ£Ö¹¶¼ÊÇÊÜ¿ØµÄ¡£
	//110£º´¥·¢Ä£Ê½ ¨C ¼ÆÊýÆ÷ÔÚ´¥·¢ÊäÈëTRGIµÄÉÏÉýÑØÆô¶¯(µ«²»¸´Î»)£¬Ö»ÓÐ¼ÆÊýÆ÷µÄÆô¶¯ÊÇÊÜ¿ØµÄ¡£
	//111£ºÍâ²¿Ê±ÖÓÄ£Ê½1 ¨C Ñ¡ÖÐµÄ´¥·¢ÊäÈë(TRGI)µÄÉÏÉýÑØÇý¶¯¼ÆÊýÆ÷¡£
	//×¢£ºÈç¹ûTI1F_ED±»Ñ¡Îª´¥·¢ÊäÈë(TS=100)Ê±£¬²»ÒªÊ¹ÓÃÃÅ¿ØÄ£Ê½¡£ÕâÊÇÒòÎªTI1F_EDÔÚÃ¿´Î
	//TI1F±ä»¯Ê±Ö»ÊÇÊä³öÒ»¸öÂö³å£¬È»¶øÃÅ¿ØÄ£Ê½ÊÇÒª¼ì²é´¥·¢ÊäÈëµÄµçÆ½¡£

    TIM1IER =0B00000010;//²¶»ñ±È½Ï1ÖÐ¶ÏÊ¹ÄÜ
    //Bit7£ºÔÊÐíÉ²³µÖÐ¶Ï
	//0£º½ûÖ¹É²³µÖÐ¶Ï£»
	//1£ºÔÊÐíÉ²³µÖÐ¶Ï¡£
    
	//Bit6£º´¥·¢ÖÐ¶ÏÊ¹ÄÜ
	//0£º½ûÖ¹´¥·¢ÖÐ¶Ï£»
	//1£ºÊ¹ÄÜ´¥·¢ÖÐ¶Ï¡£
    
	//Bit5£º±£ÁôÎ»
    
	//Bit4£ºÔÊÐí²¶»ñ/±È½Ï4ÖÐ¶Ï
	//0£º½ûÖ¹²¶»ñ/±È½Ï4ÖÐ¶Ï£»
	//1£ºÔÊÐí²¶»ñ/±È½Ï4ÖÐ¶Ï¡£
    
	//Bit3£ºÔÊÐí²¶»ñ/±È½Ï3ÖÐ¶Ï
	//0£º½ûÖ¹²¶»ñ/±È½Ï3ÖÐ¶Ï£»
	//1£ºÔÊÐí²¶»ñ/±È½Ï3ÖÐ¶Ï¡£
    
	//Bit2£ºÔÊÐí²¶»ñ/±È½Ï2ÖÐ¶Ï
	//0£º½ûÖ¹²¶»ñ/±È½Ï2ÖÐ¶Ï£»
	//1£ºÔÊÐí²¶»ñ/±È½Ï2ÖÐ¶Ï¡£
    
	//Bit1£ºÔÊÐí²¶»ñ/±È½Ï1ÖÐ¶Ï
	//0£º½ûÖ¹²¶»ñ/±È½Ï1ÖÐ¶Ï£»
	//1£ºÔÊÐí²¶»ñ/±È½Ï1ÖÐ¶Ï¡£
    
	//Bit0£ºÔÊÐí¸üÐÂÖÐ¶Ï
	//0£º½ûÖ¹¸üÐÂÖÐ¶Ï£»
	//1£ºÔÊÐí¸üÐÂÖÐ¶Ï¡£

    TIM1SR1 =0B00000000; 		//T1CC1IF
    //Bit7£ºÉ²³µÖÐ¶Ï±ê¼Ç(Ð´1Çå0£¬Ð´0ÎÞÐ§)
	//0£ºÎÞÉ²³µÊÂ¼þ²úÉú£»
	//1£ºÉ²³µÊäÈëÉÏ¼ì²âµ½ÓÐÐ§µçÆ½¡£
    
	//Bit6£º´¥·¢Æ÷ÖÐ¶Ï±ê¼Ç(Ð´1Çå0£¬Ð´0ÎÞÐ§)
	//0£ºÎÞ´¥·¢Æ÷ÊÂ¼þ²úÉú£»
	//1£º´¥·¢ÖÐ¶ÏµÈ´ýÏìÓ¦¡£
    
	//Bit5:±£ÁôÎ»
    
	//Bit4£º²¶»ñ/±È½Ï4ÖÐ¶Ï±ê¼Ç
	//²Î¿¼CC1IFÃèÊö¡£
    
	//Bit3£º²¶»ñ/±È½Ï3ÖÐ¶Ï±ê¼Ç
	//²Î¿¼CC1IFÃèÊö¡£
    
	//Bit2£º²¶»ñ/±È½Ï2ÖÐ¶Ï±ê¼Ç
	//²Î¿¼CC1IFÃèÊö¡£
    
	//Bit1£º²¶»ñ/±È½Ï1ÖÐ¶Ï±ê¼Ç  Èç¹ûÍ¨µÀCC1ÅäÖÃÎªÊä³öÄ£Ê½£º(Ð´1Çå0£¬Ð´0ÎÞÐ§)
	//0£ºÎÞÆ¥Åä·¢Éú£»
	//1£ºTIMx_CNTµÄÖµÓëTIMx_CCR1µÄÖµÆ¥Åä¡£
	//×¢£ºÔÚÖÐÐÄ¶Ô³ÆÄ£Ê½ÏÂ£¬µ±¼ÆÊýÆ÷ÖµÎª0Ê±£¬ÏòÉÏ¼ÆÊý£¬µ±¼ÆÊýÆ÷ÖµÎªARRÊ±£¬ÏòÏÂ¼ÆÊý£¨Ëü´Ó0ÏòÉÏ¼ÆÊýµ½ARR-1£¬ÔÙÓÉARRÏòÏÂ¼ÆÊýµ½1£©¡£Òò´Ë£¬¶ÔËùÓÐµÄSMSÎ»Öµ£¬ÕâÁ½¸öÖµ¶¼²»ÖÃ±ê¼Ç¡£µ«ÊÇ£¬Èç¹ûCCR1>ARR£¬Ôòµ±CNT´ïµ½ARRÖµÊ±£¬CC1IFÖÃ1¡£
	//Èç¹ûÍ¨µÀCC1ÅäÖÃÎªÊäÈëÄ£Ê½£ºµ±²¶»ñÊÂ¼þ·¢ÉúÊ±¸ÃÎ»ÓÉÓ²¼þÖÃ1£¬ËüÓÉÈí¼þÇå0»òÍ¨¹ý¶ÁTIM1_CCR1LÇå0¡£
	//0£ºÎÞÊäÈë²¶»ñ²úÉú£»
	//1£º¼ÆÊýÆ÷ÖµÒÑ±»²¶»ñ(¿½±´)ÖÁTIM1_CCR1(ÔÚIC1ÉÏ¼ì²âµ½ÓëËùÑ¡¼«ÐÔÏàÍ¬µÄ±ßÑØ)¡£
    
	//Bit0£º¸üÐÂÖÐ¶Ï±ê¼Ç,µ±²úÉú¸üÐÂÊÂ¼þÊ±¸ÃÎ»ÓÉÓ²¼þÖÃ1¡£ËüÓÉÈí¼þÇå0¡£
	//0£ºÎÞ¸üÐÂÊÂ¼þ²úÉú£»
	//1£º¸üÐÂÊÂ¼þµÈ´ýÏìÓ¦¡£µ±¼Ä´æÆ÷±»¸üÐÂÊ±¸ÃÎ»ÓÉÓ²¼þÖÃ1£º
	//ÈôTIM1_CR1¼Ä´æÆ÷µÄUDIS=0£¬µ±¼ÆÊýÆ÷ÉÏÒç»òÏÂÒçÊ±£»
	//ÈôTIM1_CR1¼Ä´æÆ÷µÄUDIS=0¡¢URS=0£¬µ±ÉèÖÃTIM1_EGR¼Ä´æÆ÷µÄUGÎ»Èí¼þ¶Ô¼ÆÊýÆ÷
	//CNTÖØÐÂ³õÊ¼»¯Ê±£»
	//ÈôTIM1_CR1¼Ä´æÆ÷µÄUDIS=0¡¢URS=0£¬µ±¼ÆÊýÆ÷CNT±»´¥·¢ÊÂ¼þÖØÐÂ³õÊ¼»¯Ê± (²Î¿¼0
	//´ÓÄ£Ê½¿ØÖÆ¼Ä´æÆ÷TIM1_SMCR)¡£

    TIM1SR2 =0B00000000;
    
    TIM1EGR =0B00000000;
    //Bit7£º²úÉúÉ²³µÊÂ¼þ,¸ÃÎ»ÓÉÈí¼þÖÃ1£¬ÓÃÓÚ²úÉúÒ»¸öÉ²³µÊÂ¼þ£¬ÓÉÓ²¼þ×Ô¶¯Çå0¡£
	//0£ºÎÞ¶¯×÷£»
	//1£º²úÉúÒ»¸öÉ²³µÊÂ¼þ¡£´ËÊ±MOE=0¡¢BIF=1£¬Èô¿ªÆô¶ÔÓ¦µÄÖÐ¶Ï(BIE=1)£¬Ôò²úÉúÏàÓ¦µÄÖÐ¶Ï¡£
    
	//Bit[6:5]:±£ÁôÎ»
        
	//Bit4£º²úÉú²¶»ñ/±È½Ï4ÊÂ¼þ
	//²Î¿¼CC1GÃèÊö¡£
    
	//Bit3£º²úÉú²¶»ñ/±È½Ï3ÊÂ¼þ
	//²Î¿¼CC1GÃèÊö¡£
    
	//Bit2£º²úÉú²¶»ñ/±È½Ï2ÊÂ¼þ
	//²Î¿¼CC1GÃèÊö¡£
    
	//Bit1£º²úÉú²¶»ñ/±È½Ï1ÊÂ¼þ
	//¸ÃÎ»ÓÉÈí¼þÖÃ1£¬ÓÃÓÚ²úÉúÒ»¸ö²¶»ñ/±È½ÏÊÂ¼þ£¬ÓÉÓ²¼þ×Ô¶¯Çå0¡£
	//0£ºÎÞ¶¯×÷£»
	//1£ºÔÚÍ¨µÀCC1ÉÏ²úÉúÒ»¸ö²¶»ñ/±È½ÏÊÂ¼þ£º ÈôÍ¨µÀCC1ÅäÖÃÎªÊä³ö£º
	//ÉèÖÃCC1IF=1£¬Èô¿ªÆô¶ÔÓ¦µÄÖÐ¶Ï£¬Ôò²úÉúÏàÓ¦µÄÖÐ¶Ï¡£ÈôÍ¨µÀCC1ÅäÖÃÎªÊäÈë£º
	//µ±Ç°µÄ¼ÆÊýÆ÷Öµ±»²¶»ñÖÁTIM1_CCR1¼Ä´æÆ÷£¬ÉèÖÃCC1IF=1£¬Èô¿ªÆô¶ÔÓ¦µÄÖÐ¶Ï£¬Ôò²úÉúÏàÓ¦µÄÖÐ¶Ï¡£ÈôCC1IFÒÑ¾­Îª1£¬ÔòÉèÖÃCC1OF=1¡£
    
	//Bit0: ±£ÁôÎ»
      
    TIM1CCMR1 =0B00000001;		//CC1Í¨µÀ±»ÅäÖÃÎªÊäÈë
	//Bit7£º±£ÁôÎ»
        
	//Bit[6:4]£ºÊä³ö±È½Ï1Ä£Ê½,¸Ã3Î»¶¨ÒåÁËÊä³ö²Î¿¼ÐÅºÅOC1REFµÄ¶¯×÷£¬¶øOC1REF¾ö¶¨ÁËOC1µÄÖµ¡£OC1REFÊÇ¸ßµçÆ½ÓÐÐ§£¬¶øOC1µÄÓÐÐ§µçÆ½È¡¾öÓÚCC1PÎ»¡£
	//000£º¶³½á¡£Êä³ö±È½Ï¼Ä´æÆ÷TIM1_CCR1Óë¼ÆÊýÆ÷TIM1_CNT¼äµÄ±È½Ï¶ÔOC1REF²»Æð×÷ÓÃ£»
	//001£ºÆ¥ÅäÊ±ÉèÖÃÍ¨µÀ1µÄÊä³öÎªÓÐÐ§µçÆ½¡£µ±¼ÆÊýÆ÷TIM1_CNTµÄÖµÓë²¶»ñ/±È½Ï¼Ä´æÆ÷1(TIM1_CCR1)ÏàÍ¬Ê±£¬Ç¿ÖÆOC1REFÎª¸ß¡£
	//010£ºÆ¥ÅäÊ±ÉèÖÃÍ¨µÀ1µÄÊä³öÎªÎÞÐ§µçÆ½¡£µ±¼ÆÊýÆ÷TIM1_CNTµÄÖµÓë²¶»ñ/±È½Ï¼Ä´æÆ÷1(TIM1_CCR1)ÏàÍ¬Ê±£¬Ç¿ÖÆOC1REFÎªµÍ¡£
	//011£º·­×ª¡£µ±TIM1_CCR1=TIM1_CNTÊ±£¬·­×ªOC1REFµÄµçÆ½¡£
	//100£ºÇ¿ÖÆÎªÎÞÐ§µçÆ½¡£Ç¿ÖÆOC1REFÎªµÍ¡£
	//101£ºÇ¿ÖÆÎªÓÐÐ§µçÆ½¡£Ç¿ÖÆOC1REFÎª¸ß¡£
	//110£ºPWMÄ£Ê½1£­ ÔÚÏòÉÏ¼ÆÊýÊ±£¬Ò»µ©TIM1_CNT<TIM1_CCR1Ê±Í¨µÀ1ÎªÓÐÐ§µçÆ½£¬·ñÔòÎªÎÞÐ§µçÆ½£»ÔÚÏòÏÂ¼ÆÊýÊ±£¬Ò»µ©TIM1_CNT>TIM1_CCR1Ê±Í¨µÀ1ÎªÎÞÐ§µçÆ½(OC1REF=0)£¬ ·ñÔòÎªÓÐÐ§µçÆ½(OC1REF=1)¡£
	//111£ºPWMÄ£Ê½2£­ ÔÚÏòÉÏ¼ÆÊýÊ±£¬Ò»µ©TIM1_CNT<TIM1_CCR1Ê±Í¨µÀ1ÎªÎÞÐ§µçÆ½£¬·ñÔòÎªÓÐÐ§µçÆ½£»ÔÚÏòÏÂ¼ÆÊýÊ±£¬Ò»µ©TIM1_CNT>TIM1_CCR1Ê±Í¨µÀ1ÎªÓÐÐ§µçÆ½£¬·ñÔòÎªÎÞÐ§µçÆ½¡£
	//×¢1£ºÒ»µ©LOCK¼¶±ðÉèÎª3(TIM1_BKR¼Ä´æÆ÷ÖÐµÄLOCKÎ»)²¢ÇÒCC1S=00(¸ÃÍ¨µÀÅäÖÃ³ÉÊä³ö) Ôò¸ÃÎ»²»ÄÜ±»ÐÞ¸Ä¡£
	//×¢2£ºÔÚPWMÄ£Ê½1»òPWMÄ£Ê½2ÖÐ£¬Ö»ÓÐµ±±È½Ï½á¹û¸Ä±äÁË»òÔÚÊä³ö±È½ÏÄ£Ê½ÖÐ´Ó¶³½áÄ£Ê½ÇÐ»»µ½PWMÄ£Ê½Ê±£¬OC1REFµçÆ½²Å¸Ä±ä¡£(²Î¿¼17.5.7PWMÄ£Ê½)
	//×¢3£ºÔÚÓÐ»¥²¹Êä³öµÄÍ¨µÀÉÏ£¬ÕâÐ©Î»ÊÇÔ¤×°ÔØµÄ¡£Èç¹ûTIM1_CR2¼Ä´æÆ÷µÄCCPC=1£¬OCM Î»Ö»ÓÐÔÚCOMÊÂ¼þ·¢ÉúÊ±£¬²Å´ÓÔ¤×°ÔØÎ»È¡ÐÂÖµ¡£
    
	//Bit3£ºÊä³ö±È½Ï1Ô¤×°ÔØÊ¹ÄÜ
	//0£º½ûÖ¹TIM1_CCR1¼Ä´æÆ÷µÄÔ¤×°ÔØ¹¦ÄÜ£¬¿ÉËæÊ±Ð´ÈëTIM1_CCR1¼Ä´æÆ÷£¬²¢ÇÒÐÂÐ´ÈëµÄÊýÖµÁ¢¼´Æð×÷ÓÃ¡£
	//1£º¿ªÆôTIM1_CCR1¼Ä´æÆ÷µÄÔ¤×°ÔØ¹¦ÄÜ£¬¶ÁÐ´²Ù×÷½ö¶ÔÔ¤×°ÔØ¼Ä´æÆ÷²Ù×÷£¬TIM1_CCR1µÄÔ¤×°ÔØÖµÔÚ¸üÐÂÊÂ¼þµ½À´Ê±±»¼ÓÔØÖÁµ±Ç°¼Ä´æÆ÷ÖÐ¡£
	//×¢1£ºÒ»µ©LOCK¼¶±ðÉèÎª3(TIM1_BKR¼Ä´æÆ÷ÖÐµÄLOCKÎ»)²¢ÇÒCC1S=00(¸ÃÍ¨µÀÅäÖÃ³ÉÊä³ö) Ôò¸ÃÎ»²»ÄÜ±»ÐÞ¸Ä¡£
	//×¢2£ºÎªÁË²Ù×÷ÕýÈ·£¬ÔÚPWMÄ£Ê½ÏÂ±ØÐëÊ¹ÄÜÔ¤×°ÔØ¹¦ÄÜ¡£µ«ÔÚµ¥Âö³åÄ£Ê½ÏÂ(TIM1_CR1¼Ä´æÆ÷µÄOPM=1)£¬Ëü²»ÊÇ±ØÐëµÄ¡
    
	//Bit2£º±£ÁôÎ»
    
	//Bit[1:0]:²¶»ñ/±È½Ï1 Ñ¡Ôñ¡£Õâ2Î»¶¨ÒåÍ¨µÀµÄ·½Ïò(ÊäÈë/Êä³ö)£¬¼°ÊäÈë½ÅµÄÑ¡Ôñ£º
	//00£ºCC1Í¨µÀ±»ÅäÖÃÎªÊä³ö£»
	//01£ºCC1Í¨µÀ±»ÅäÖÃÎªÊäÈë£¬IC1Ó³ÉäÔÚTI1FP1ÉÏ£»
	//10£ºCC1Í¨µÀ±»ÅäÖÃÎªÊäÈë£¬IC1Ó³ÉäÔÚTI2FP1ÉÏ£»
	//11£ºCC1Í¨µÀ±»ÅäÖÃÎªÊäÈë£¬IC1Ó³ÉäÔÚTRCÉÏ¡£´ËÄ£Ê½½ö¹¤×÷ÔÚÄÚ²¿´¥·¢Æ÷ÊäÈë±»Ñ¡ÖÐÊ±(ÓÉ
	//TIM1_SMCR¼Ä´æÆ÷µÄTSÎ»Ñ¡Ôñ)¡£
	//×¢£ºCC1S½öÔÚÍ¨µÀ¹Ø±ÕÊ±(TIM1_CCER1¼Ä´æÆ÷µÄCC1E=0)²ÅÊÇ¿ÉÐ´µÄ¡£
    
    TIM1CCER1 =0B00000001; 		//ÉÏÉýÑØ´¥·¢£¬´¥·¢Ê¹ÄÜ
    //Bit7£ºÊäÈë²¶»ñ/±È½Ï2»¥²¹Êä³ö¼«ÐÔ¡£²Î¿¼CC1NPµÄÃèÊö¡£
    
	//Bit6£ºÊäÈë²¶»ñ/±È½Ï2»¥²¹Êä³öÊ¹ÄÜ¡£²Î¿¼CC1NEµÄÃèÊö¡£
    
	//Bit5£ºÊäÈë²¶»ñ/±È½Ï2Êä³ö¼«ÐÔ¡£²Î¿¼CC1PµÄÃèÊö¡£
    
	//Bit4£ºÊäÈë²¶»ñ/±È½Ï2Êä³öÊ¹ÄÜ¡£²Î¿¼CC1EµÄÃèÊö¡£
    
	//Bit3£ºÊäÈë²¶»ñ/±È½Ï1»¥²¹Êä³ö¼«ÐÔ
	//0£ºOC1N¸ßµçÆ½ÓÐÐ§£»
	//1£ºOC1NµÍµçÆ½ÓÐÐ§¡£
	//×¢1£ºÒ»µ©LOCK¼¶±ð(TIM1_BKR¼Ä´æÆ÷ÖÐµÄLCCKÎ»)ÉèÎª3»ò2ÇÒCC1S=00(Í¨µÀÅäÖÃÎªÊä³ö) Ôò¸ÃÎ»²»ÄÜ±»ÐÞ¸Ä¡£
    
	//Bit2£ºÊäÈë²¶»ñ/±È½Ï1»¥²¹Êä³öÊ¹ÄÜ
	//0£º¹Ø±Õ£­ OC1N½ûÖ¹Êä³ö£¬Òò´ËOC1NµÄÊä³öµçÆ½ÒÀÀµÓÚMOE¡¢OSSI¡¢OSSR¡¢OIS1¡¢
	//OIS1NºÍCC1EÎ»µÄÖµ¡£
	//1£º¿ªÆô£­ OC1NÐÅºÅÊä³öµ½¶ÔÓ¦µÄÊä³öÒý½Å£¬ÆäÊä³öµçÆ½ÒÀÀµÓÚMOE¡¢OSSI¡¢OSSR¡¢
	//OIS1¡¢OIS1NºÍCC1EÎ»µÄÖµ¡£
    
	//Bit1£ºÊäÈë²¶»ñ/±È½Ï1Êä³ö¼«ÐÔCC1Í¨µÀÅäÖÃÎªÊä³ö£º
	//0£ºOC1¸ßµçÆ½ÓÐÐ§£»
	//1£ºOC1µÍµçÆ½ÓÐÐ§¡£
	//CC1Í¨µÀÅäÖÃÎª´¥·¢(²Î¿¼Í¼61)£º
	//0£º´¥·¢·¢ÉúÔÚTI1FµÄ¸ßµçÆ½»òÉÏÉýÑØ£»
	//1£º´¥·¢·¢ÉúÔÚTI1FµÄµÍµçÆ½»òÏÂ½µÑØ¡£
	//CC1Í¨µÀÅäÖÃÎªÊäÈë(²Î¿¼Í¼61)£º
	//0£º²¶×½·¢ÉúÔÚTI1FµÄ¸ßµçÆ½»òÉÏÉýÑØ£»
	//1£º²¶×½·¢ÉúÔÚTI1FµÄµÍµçÆ½»òÏÂ½µÑØ¡£
	//×¢1£ºÒ»µ©LOCK¼¶±ð(TIM1_BKR¼Ä´æÆ÷ÖÐµÄLCCKÎ»)ÉèÎª3»ò2£¬Ôò¸ÃÎ»²»ÄÜ±»ÐÞ¸Ä¡£
	//COMÊÂ¼þ·¢ÉúÊ±£¬CC1PÎ»²Å´ÓÔ¤×°ÔØÎ»ÖÐÈ¡ÐÂÖµ¡£
            
	//Bit0£ºÊäÈë²¶»ñ/±È½Ï1Êä³öÊ¹ÄÜ
	//CC1Í¨µÀÅäÖÃÎªÊä³ö£º
	//0£º ¹Ø±Õ£­ OC1½ûÖ¹Êä³ö£¬Òò´ËOC1µÄÊä³öµçÆ½ÒÀÀµÓÚMOE¡¢OSSI¡¢OSSR¡¢OIS1¡¢OIS1NºÍCC1NEÎ»µÄÖµ¡£
	//1£º ¿ªÆô£­ OC1ÐÅºÅÊä³öµ½¶ÔÓ¦µÄÊä³öÒý½Å£¬ÆäÊä³öµçÆ½ÒÀÀµÓÚMOE¡¢OSSI¡¢OSSR¡¢OIS1¡¢OIS1NºÍCC1NEÎ»µÄÖµ¡£CC1Í¨µÀÅäÖÃÎªÊäÈë
	//¸ÃÎ»¾ö¶¨ÁË¼ÆÊýÆ÷µÄÖµÊÇ·ñÄÜ²¶»ñÈëTIM1_CCR1¼Ä´æÆ÷¡£
	//0£º²¶»ñ½ûÖ¹£»
	//0£º²¶»ñÊ¹ÄÜ¡£

    TIM1CCER2 = 0B00000000;
    
    TIM1CNTRH = 0B00000000;		//TIM1¼ÆÊýÆ÷
    TIM1CNTRL = 0B00000000;
    
    TIM1PSCRH = 0B00000000;		//¼ÆÊýÊ±ÖÓ²»·ÖÆµ
    TIM1PSCRL = 0B00000000;
            
	T1CEN=1;
}
/*-------------------------------------------------
 * º¯ÊýÃû£ºmain 
 * ¹¦ÄÜ£º  Ö÷º¯Êý
 * ÊäÈë£º  ÎÞ
 * Êä³ö£º  ÎÞ
 --------------------------------------------------*/
void main(void)
{
	POWER_INITIAL();			//ÏµÍ³³õÊ¼»¯
    Time1_Capture_Initial();
    Time4Initial();
    
	while(1)
	{
    	NOP();
	}
}