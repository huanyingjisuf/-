#ifndef __CA51F1_H__
#define __CA51F1_H__

sfr P0    	 = 0x80;
sfr SP       = 0x81;
sfr DP0L     = 0x82;
sfr DP0H     = 0x83;
sfr DP1L     = 0x84;
sfr DP1H     = 0x85;
sfr PWCON    = 0x86;
sfr PCON     = 0x87;
sfr TCON     = 0x88;
sfr TMOD     = 0x89;
sfr TL0      = 0x8a;
sfr TL1      = 0x8b;
sfr TH0      = 0x8c;
sfr TH1      = 0x8d;
sfr IDLST    = 0x8e;
sfr STPST    = 0x8f;

sfr PWM2DUTH 	= 0x91;
sfr LEDUTL 		= 0x92;
sfr LEDUTH 		= 0x93;
sfr LEDWTML 	= 0x94;
sfr LEDWTMH 	= 0x95;
sfr LEDAT0 		= 0x96;
sfr LEFLG 		= 0x97;
sfr SCON    	= 0x98;
sfr SBUF    	= 0x99;

sfr PWM0DUTL 	= 0x9b;
sfr PWM0DUTH 	= 0x9c;
sfr PWM1DUTL 	= 0x9d;
sfr PWM1DUTH 	= 0x9e;
sfr PWM2DUTL 	= 0x9f;


sfr WDCON    = 0xa0;
sfr WDFLG    = 0xa1;
sfr WDVTHL   = 0xa2;
sfr WDVTHH   = 0xa3;
sfr IE       = 0xa8;
sfr PWM0DIVL = 0xa9;
sfr PWM0DIVH = 0xaa;
sfr PWM1DIVL = 0xab;
sfr PWM1DIVH = 0xac;
sfr PWM2DIVL = 0xad;
sfr PWM2DIVH = 0xae;


sfr P3       = 0xb0;
sfr PWM0CKD  = 0xb1;
sfr PWM1CKD  = 0xb2;
sfr PWM2CKD  = 0xb3;
sfr IP       = 0xb8;
sfr PWM0CON  = 0xb9;
sfr PWM1CON  = 0xba;
sfr PWM2CON  = 0xbb;


sfr I2CCON   = 0xc0;
sfr I2CADR   = 0xc1;
sfr I2CADM   = 0xc2;
sfr I2CCR    = 0xc3;
sfr I2CDAT   = 0xc4;
sfr I2CSTA   = 0xc5;
sfr I2CFLG   = 0xc6;
sfr PWMEN    = 0xc7;


sfr CKCON    = 0xc8;
sfr CKDIV    = 0xc9;
sfr IHCFG    = 0xca;
sfr TPCTL    = 0xcf;


sfr PSW      = 0xd0;
sfr TMCON    = 0xd5;
sfr TMSNU    = 0xd6;
sfr I2CIOS   = 0xd7;

sfr UDCKS    = 0xd8;
sfr TK3MSH   = 0xd9;
sfr TK4MSL   = 0xda;
sfr TK4MSH   = 0xdb;
sfr TK5MSL   = 0xdc;
sfr TK5MSH   = 0xdd;
sfr TKCKS    = 0xde;
sfr TKPWC    = 0xdf;

sfr ACC      = 0xe0;
sfr TK0MSL   = 0xe1;
sfr TK0MSH   = 0xe2;
sfr TK1MSL   = 0xe3;
sfr TK1MSH   = 0xe4;
sfr TK2MSL   = 0xe5;
sfr TK2MSH   = 0xe6;
sfr TK3MSL   = 0xe7;

sfr LVDCON   	= 0xe8;
sfr IDCODE  	= 0xef;

sfr B        = 0xf0;
sfr SPMAX    = 0xf3;
sfr TKCON    = 0xf8;
sfr TKCFG    = 0xf9;
sfr TKMTS    = 0xfa;
sfr TKIF     = 0xfb;


/*  BIT Register  */
/*	PSW	*/
sbit CY   		= 0xD7;
sbit AC   		= 0xD6;
sbit F0   		= 0xD5;
sbit RS1  		= 0xD4;
sbit RS0  		= 0xD3;
sbit OV   		= 0xD2;
sbit DPS   		= 0xD1;
sbit P    		= 0xD0;
		  		
/*	TCON	*/
sbit TF1  		= 0x8F;
sbit TR1  		= 0x8E;
sbit TF0  		= 0x8D;
sbit TR0  		= 0x8C;
sbit IE1  		= 0x8B;
sbit IT1  		= 0x8A;
sbit IE0  		= 0x89;
sbit IT0  		= 0x88;

/*	IE	*/
sbit EA   		= 0xAF;
sbit INT4EN  	= 0xAE;
sbit INT3EN  	= 0xAD;
sbit INT2EN	  = 0xAC;
sbit ET1  		= 0xAB;
sbit EX1  		= 0xAA;
sbit ET0  		= 0xA9;
sbit EX0  		= 0xA8;

/*	IP	*/ 
sbit PS1  		= 0xBE;
sbit PT2  		= 0xBD;
sbit PS0   		= 0xBC;
sbit PT1  		= 0xBB;
sbit PX1  		= 0xBA;
sbit PT0  		= 0xB9;
sbit PX0  		= 0xB8;

/*	P0	*/
sbit P01		= P0^1;


/*	P3	*/
sbit P30		= P3^0;
sbit P31		= P3^1;
sbit P32		= P3^2;
sbit P34		= P3^4;
sbit P35		= P3^5;
	
#endif  
