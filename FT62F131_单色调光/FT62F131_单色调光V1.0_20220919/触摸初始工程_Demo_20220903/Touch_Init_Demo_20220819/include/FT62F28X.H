
#ifndef _CHIP_DEVICE_H_
#define _CHIP_DEVICE_H_
//
// Special function register definitions
//
// Register: INDF
volatile unsigned char           INDF                @ 0x000;
// bit and bitfield definitions

// Register: TMR0
volatile unsigned char           TMR0                @ 0x001;
// bit and bitfield definitions

// Register: PCL
volatile unsigned char           PCL                 @ 0x002;
// bit and bitfield definitions

// Register: STATUS
volatile unsigned char           STATUS              @ 0x003;
// bit and bitfield definitions
volatile bit CARRY               @ ((unsigned)&STATUS*8)+0;
volatile bit DC                  @ ((unsigned)&STATUS*8)+1;
volatile bit ZERO                @ ((unsigned)&STATUS*8)+2;
volatile bit nPD                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTO                 @ ((unsigned)&STATUS*8)+4;
volatile bit RP0                 @ ((unsigned)&STATUS*8)+5;
volatile bit RP1                 @ ((unsigned)&STATUS*8)+6;
volatile bit FSR_B8              @ ((unsigned)&STATUS*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CARRY               : 1;
        unsigned	DC                  : 1;
        unsigned	ZERO                : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 2;
        unsigned	FSR_B8              : 1;
    };
    struct{
    		unsigned  C										:1;
    		unsigned HC 									:1;
    		unsigned Z  									:1;
    		unsigned nPF 									:1;
    		unsigned nTF									:1;
    		unsigned PAGE									:2;
        unsigned FSRB8                : 1;
    };
    struct{
    		unsigned    									:5;
    		unsigned PAGE0								:1;
    		unsigned PAGE1								:1;
    };
    struct{
    		unsigned    									:5;
    		unsigned RP0								  :1;
    		unsigned RP1								  :1;
    };
} STATUSbits @ 0x003;
#endif

// Register: FSR
volatile unsigned char           FSR                 @ 0x004;
// bit and bitfield definitions

// Register: PORTA
volatile unsigned char           PORTA               @ 0x005;
// bit and bitfield definitions
volatile bit RA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit RA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit RA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit RA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit RA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit RA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit RA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit RA7                 @ ((unsigned)&PORTA*8)+7;

volatile bit PA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit PA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit PA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit PA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit PA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit PA5                 @ ((unsigned)&PORTA*8)+5;
volatile bit PA6                 @ ((unsigned)&PORTA*8)+6;
volatile bit PA7                 @ ((unsigned)&PORTA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RA0                 : 1;
        unsigned	RA1                 : 1;
        unsigned	RA2                 : 1;
        unsigned	RA3                 : 1;
        unsigned	RA4                 : 1;
        unsigned	RA5                 : 1;
        unsigned	RA6                 : 1;
        unsigned	RA7                 : 1;
    };
    struct {
        unsigned	RA                  : 8;
    };
	struct {
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
        unsigned	PA6                 : 1;
        unsigned	PA7                 : 1;
    };
    struct {
        unsigned	PA                  : 8;
    };
} PORTAbits @ 0x005;
#endif


// Register: PORTB
volatile unsigned char           PORTB              @ 0x006;
// bit and bitfield definitions
volatile bit RB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit RB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit RB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit RB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit RB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit RB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit RB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit RB7                 @ ((unsigned)&PORTB*8)+7;

volatile bit PB0                 @ ((unsigned)&PORTB*8)+0;
volatile bit PB1                 @ ((unsigned)&PORTB*8)+1;
volatile bit PB2                 @ ((unsigned)&PORTB*8)+2;
volatile bit PB3                 @ ((unsigned)&PORTB*8)+3;
volatile bit PB4                 @ ((unsigned)&PORTB*8)+4;
volatile bit PB5                 @ ((unsigned)&PORTB*8)+5;
volatile bit PB6                 @ ((unsigned)&PORTB*8)+6;
volatile bit PB7                 @ ((unsigned)&PORTB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RB0                 : 1;
        unsigned	RB1                 : 1;
        unsigned	RB2                 : 1;
        unsigned	RB3                 : 1;
        unsigned	RB4                 : 1;
        unsigned	RB5                 : 1;
        unsigned	RB6                 : 1;
        unsigned	RB7                 : 1;
    };
    struct {
        unsigned	RB                  : 8;
    };
	struct {
        unsigned	PB0                 : 1;
        unsigned	PB1                 : 1;
        unsigned	PB2                 : 1;
        unsigned	PB3                 : 1;
        unsigned	PB4                 : 1;
        unsigned	PB5                 : 1;
        unsigned	PB6                 : 1;
        unsigned	PB7                 : 1;
    };
    struct {
        unsigned	PB                  : 8;
    };
} PORTBbits @ 0x006;
#endif

// Register: PORTC
volatile unsigned char           PORTC               @ 0x007;
// bit and bitfield definitions
volatile bit RC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit RC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit RC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit RC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit RC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit RC5                 @ ((unsigned)&PORTC*8)+5;
volatile bit RC6                 @ ((unsigned)&PORTC*8)+6;
volatile bit RC7                 @ ((unsigned)&PORTC*8)+7;

volatile bit PC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit PC1                 @ ((unsigned)&PORTC*8)+1;
volatile bit PC2                 @ ((unsigned)&PORTC*8)+2;
volatile bit PC3                 @ ((unsigned)&PORTC*8)+3;
volatile bit PC4                 @ ((unsigned)&PORTC*8)+4;
volatile bit PC5                 @ ((unsigned)&PORTC*8)+5;
volatile bit PC6                 @ ((unsigned)&PORTC*8)+6;
volatile bit PC7                 @ ((unsigned)&PORTC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
        unsigned	RC2                 : 1;
        unsigned	RC3                 : 1;
        unsigned	RC4                 : 1;
        unsigned	RC5                 : 1;
        unsigned	RC6                 : 1;
        unsigned	RC7                 : 1;
    };
    struct {
        unsigned	RC                  : 8;
    };
	struct {
        unsigned	PC0                 : 1;
        unsigned	PC1                 : 1;
        unsigned	PC2                 : 1;
        unsigned	PC3                 : 1;
        unsigned	PC4                 : 1;
        unsigned	PC5                 : 1;
        unsigned	PC6                 : 1;
        unsigned	PC7                 : 1;
    };
    struct {
        unsigned	PC                  : 8;
    };
} PORTCbits @ 0x007;
#endif

// Register: PORTD
volatile unsigned char           PORTD               @ 0x008;
// bit and bitfield definitions
volatile bit RD0                 @ ((unsigned)&PORTD*8)+0;
volatile bit RD1                 @ ((unsigned)&PORTD*8)+1;
volatile bit RD2                 @ ((unsigned)&PORTD*8)+2;
volatile bit RD3                 @ ((unsigned)&PORTD*8)+3;
volatile bit RD4                 @ ((unsigned)&PORTD*8)+4;
volatile bit RD5                 @ ((unsigned)&PORTD*8)+5;

volatile bit PD0                 @ ((unsigned)&PORTD*8)+0;
volatile bit PD1                 @ ((unsigned)&PORTD*8)+1;
volatile bit PD2                 @ ((unsigned)&PORTD*8)+2;
volatile bit PD3                 @ ((unsigned)&PORTD*8)+3;
volatile bit PD4                 @ ((unsigned)&PORTD*8)+4;
volatile bit PD5                 @ ((unsigned)&PORTD*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD0                 : 1;
        unsigned	RD1                 : 1;
        unsigned	RD2                 : 1;
        unsigned	RD3                 : 1;
        unsigned	RD4                 : 1;
        unsigned	RD5                 : 1;
    };
    struct {
        unsigned	RD                  : 6;
    };
	struct {
        unsigned	PD0                 : 1;
        unsigned	PD1                 : 1;
        unsigned	PD2                 : 1;
        unsigned	PD3                 : 1;
        unsigned	PD4                 : 1;
        unsigned	PD5                 : 1;
    };
    struct {
        unsigned	PD                  : 6;
    };
} PORTDbits @ 0x008;
#endif

// Register: PIR2
volatile unsigned char           PIR2               @ 0x009;
// bit and bitfield definitions
volatile bit C0IF                 @ ((unsigned)&PIR2*8)+0;
volatile bit C1IF                 @ ((unsigned)&PIR2*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C0IF                 : 1;
        unsigned	C1IF                 : 1;
    };
} PIR2bits @ 0x009;
#endif

// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 5;
    };
} PCLATHbits @ 0x00A;
#endif

// Register: INTCON
volatile unsigned char           INTCON              @ 0x00B;
// bit and bitfield definitions
volatile bit PAIF                @ ((unsigned)&INTCON*8)+0;
volatile bit INTF                @ ((unsigned)&INTCON*8)+1;
volatile bit T0IF                @ ((unsigned)&INTCON*8)+2;
volatile bit PAIE                @ ((unsigned)&INTCON*8)+3;
volatile bit INTE                @ ((unsigned)&INTCON*8)+4;
volatile bit T0IE                @ ((unsigned)&INTCON*8)+5;
volatile bit PEIE                @ ((unsigned)&INTCON*8)+6;
volatile bit GIE                 @ ((unsigned)&INTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PAIF                : 1;
        unsigned	INTF                : 1;
        unsigned	T0IF                : 1;
        unsigned	PAIE                : 1;
        unsigned	INTE                : 1;
        unsigned	T0IE                : 1;
        unsigned	PEIE                : 1;
        unsigned	GIE                 : 1;
    };
} INTCONbits @ 0x00B;
#endif


// Register: PIR1
volatile unsigned char           PIR1                @ 0x00C;
// bit and bitfield definitions
volatile bit ADCIF               @ ((unsigned)&PIR1*8)+0;
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF               @ ((unsigned)&PIR1*8)+2;
volatile bit TMR1IF              @ ((unsigned)&PIR1*8)+3;
volatile bit ACMPIF              @ ((unsigned)&PIR1*8)+4;
volatile bit LVDIF               @ ((unsigned)&PIR1*8)+5;
volatile bit CKMIF               @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                @ ((unsigned)&PIR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIF          			: 1;
        unsigned	TMR2IF              : 1;
        unsigned	OSFIF         			: 1;
        unsigned	TMR1IF        			: 1;
        unsigned	ACMPIF        			: 1;
        unsigned	LVDIF               : 1;
        unsigned	CKMIF               : 1;
        unsigned	EEIF                : 1;
    };
} PIR1bits @ 0x00C;
#endif

// Register: P1ADTL
volatile unsigned char           P1ADTL                @ 0x00D;
// bit and bitfield definitions

// Register: P1ADTH
volatile unsigned char           P1ADTH                @ 0x00E;
// bit and bitfield definitions

// Register: P1BDTL
volatile unsigned char           P1BDTL                @ 0x00F;
// bit and bitfield definitions

// Register: P1BDTH
volatile unsigned char           P1BDTH                @ 0x0010;
// bit and bitfield definitions


// Register: P1CDTL
volatile unsigned char           P1CDTL                @ 0x011;
// bit and bitfield definitions

// Register: P1CDTH
volatile unsigned char           P1CDTH                @ 0x012;
// bit and bitfield definitions

// Register: P1DDTL
volatile unsigned char           P1DDTL                @ 0x013;
// bit and bitfield definitions

// Register: P1DDTH
volatile unsigned char           P1DDTH                @ 0x014;
// bit and bitfield definitions

// Register: TMR2L
volatile unsigned char           TMR2L                 @ 0x015;
// bit and bitfield definitions

// Register: TMR2H
volatile unsigned char           TMR2H                 @ 0x016;
// bit and bitfield definitions

// Register: PR2L
volatile unsigned char           PR2L                  @ 0x017;
// bit and bitfield definitions

// Register: PR2H
volatile unsigned char           PR2H                  @ 0x018;
// bit and bitfield definitions

// Register: P1BR0
volatile unsigned char           P1BR0                @ 0x019;
// bit and bitfield definitions
volatile bit P1ASS0                @ ((unsigned)&P1BR0*8)+0;
volatile bit P1ASS1                @ ((unsigned)&P1BR0*8)+1;
volatile bit P1BSS0                @ ((unsigned)&P1BR0*8)+2;
volatile bit P1BSS1                @ ((unsigned)&P1BR0*8)+3;
volatile bit P1BKS0                @ ((unsigned)&P1BR0*8)+4;
volatile bit P1BKS1                @ ((unsigned)&P1BR0*8)+5;
volatile bit P1BKS2                @ ((unsigned)&P1BR0*8)+6;
volatile bit P1BEVT                @ ((unsigned)&P1BR0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1ASS0             : 1;
        unsigned	P1ASS1		         : 1;
        unsigned	P1BSS0             : 1;
        unsigned	P1BSS1             : 1;
        unsigned	P1BKS0             : 1;
        unsigned	P1BKS1             : 1;
        unsigned	P1BKS2             : 1;
        unsigned	P1BEVT             : 1;
    };
    struct {
        unsigned	P1ASS              : 2;
        unsigned	P1BSS              : 2;
        unsigned	P1BKS              : 3;
    };
} P1BR0bits @ 0x019;
#endif

// Register: P1BR1
volatile unsigned char           P1BR1             @ 0x01A;
// bit and bitfield definitions
volatile bit P1CSS0                   @ ((unsigned)&P1BR1*8)+0;
volatile bit P1CSS1                   @ ((unsigned)&P1BR1*8)+1;
volatile bit P1C2SS0                  @ ((unsigned)&P1BR1*8)+2;
volatile bit P1C2SS1                  @ ((unsigned)&P1BR1*8)+3;
volatile bit P1DSS0                   @ ((unsigned)&P1BR1*8)+4;
volatile bit P1DSS1                   @ ((unsigned)&P1BR1*8)+5;
volatile bit P1D2SS0                  @ ((unsigned)&P1BR1*8)+6;
volatile bit P1D2SS1                  @ ((unsigned)&P1BR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1CSS0             	: 1;
        unsigned	P1CSS1			 	      : 1;
				unsigned 	P1C2SS0	            : 1;
				unsigned	P1C2SS1	            : 1;
				unsigned	P1DSS0				      : 1;
				unsigned	P1DSS1				      : 1;
				unsigned 	P1D2SS0	            : 1;
				unsigned	P1D2SS1	            : 1;

    };
	struct{
				unsigned	P1CSS               : 2;
				unsigned	P1C2SS				      : 2;
				unsigned	P1DSS 				      : 2;
				unsigned	P1D2SS				      : 2;
	};
} P1BR1bits @ 0x01A;
#endif

// Register: P1POL0
volatile unsigned char           P1POL0         @ 0x01B;       
// bit and bitfield definitions
volatile bit P1A0P                    @ ((unsigned)&P1POL0*8)+0;
volatile bit P1A0NP                   @ ((unsigned)&P1POL0*8)+1;
volatile bit P1A1P                    @ ((unsigned)&P1POL0*8)+2;
volatile bit P1A1NP                   @ ((unsigned)&P1POL0*8)+3;
volatile bit P1A2P                    @ ((unsigned)&P1POL0*8)+4;
volatile bit P1A2NP                   @ ((unsigned)&P1POL0*8)+5;
volatile bit P1B0P                    @ ((unsigned)&P1POL0*8)+6;
volatile bit P1C0P                    @ ((unsigned)&P1POL0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0P                : 1;
        unsigned	P1A0NP               : 1;
        unsigned	P1A1P                : 1;
        unsigned	P1A1NP               : 1;
        unsigned	P1A2P                : 1;
        unsigned	P1A2NP				       : 1;
        unsigned	P1B0P                : 1;
        unsigned	P1C0P  				       : 1;
    };
} P1POL0bits @ 0x01B;
#endif


// Register: P1POL1
volatile unsigned char           P1POL1         @ 0x01C;       
// bit and bitfield definitions
volatile bit P1B1P                    @ ((unsigned)&P1POL1*8)+1;
volatile bit P1C1P                    @ ((unsigned)&P1POL1*8)+2;
volatile bit P1D0P                    @ ((unsigned)&P1POL1*8)+5;
volatile bit P1D1P                    @ ((unsigned)&P1POL1*8)+6;
volatile bit P1D2P                    @ ((unsigned)&P1POL1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                     : 1;
        unsigned	P1B1P                : 1;
        unsigned	P1C1P                : 1;
        unsigned	                     : 1;
        unsigned	                     : 1;
        unsigned	P1D0P  				       : 1;
        unsigned	P1D1P                : 1;
        unsigned	P1D2P  				       : 1;
    };
} P1POL1bits @ 0x01C;
#endif

// Register: P1CON
volatile unsigned char           P1CON              @ 0x01D;
// bit and bitfield definitions
volatile bit P1DC0                    @ ((unsigned)&P1CON*8)+0;
volatile bit P1DC1                    @ ((unsigned)&P1CON*8)+1;
volatile bit P1DC2                    @ ((unsigned)&P1CON*8)+2;
volatile bit P1DC3                    @ ((unsigned)&P1CON*8)+3;
volatile bit P1DC4                    @ ((unsigned)&P1CON*8)+4;
volatile bit P1DC5                    @ ((unsigned)&P1CON*8)+5;
volatile bit P1DC6                    @ ((unsigned)&P1CON*8)+6;
volatile bit P1AUE                    @ ((unsigned)&P1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DC0              : 1;
        unsigned	P1DC1              : 1;
        unsigned	P1DC2              : 1;
        unsigned	P1DC3              : 1;
        unsigned	P1DC4              : 1;
        unsigned	P1DC5              : 1;
        unsigned	P1DC6              : 1;
        unsigned	P1AUE              : 1;
    };
    struct {
        unsigned	P1DC              : 7;
    };
} P1CONbits @ 0x01D;
#endif

// Register: T2CON0
volatile unsigned char           T2CON0              @ 0x01E;
// bit and bitfield definitions
volatile bit T2CKPS0                    @ ((unsigned)&T2CON0*8)+0;
volatile bit T2CKPS1                    @ ((unsigned)&T2CON0*8)+1;
volatile bit TMR2ON                     @ ((unsigned)&T2CON0*8)+2;
volatile bit TOUTPS0                    @ ((unsigned)&T2CON0*8)+3;
volatile bit TOUTPS1                    @ ((unsigned)&T2CON0*8)+4;
volatile bit TOUTPS2                    @ ((unsigned)&T2CON0*8)+5;
volatile bit TOUTPS3                    @ ((unsigned)&T2CON0*8)+6;
volatile bit PR2U                       @ ((unsigned)&T2CON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS0              : 1;
        unsigned	T2CKPS1              : 1;
        unsigned	TMR2ON               : 1;
        unsigned	TOUTPS0              : 1;
        unsigned	TOUTPS1              : 1;
        unsigned	TOUTPS2              : 1;
        unsigned	TOUTPS3              : 1;
        unsigned	PR2U                 : 1;
    };
    struct {
        unsigned	T2CKPS               : 2;
        unsigned	                           : 1;
        unsigned	TOUTPS               : 4;
    };
} T2CON0bits @ 0x01E;
#endif

//
// Register: T2CON1
volatile unsigned char           T2CON1             @ 0x01F;
// bit and bitfield definitions
volatile bit T2CKSRC0                      @ ((unsigned)&T2CON1*8)+0;
volatile bit T2CKSRC1                      @ ((unsigned)&T2CON1*8)+1;
volatile bit T2CKSRC2                      @ ((unsigned)&T2CON1*8)+2;
volatile bit P1BZM                         @ ((unsigned)&T2CON1*8)+3;
volatile bit P1OS                          @ ((unsigned)&T2CON1*8)+4;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKSRC0                 : 1;
        unsigned	T2CKSRC1                 : 1;
        unsigned	T2CKSRC2                 : 1;
        unsigned	P1BZM                    : 1;
        unsigned	P1OS                     : 1;
    };
    struct {
        unsigned	T2CKSRC                  : 3;
    };
} T2CON1bits @ 0x01F;
#endif
//---------------------------------------------------------------------------------------------------------
// Special function register definitions: Bank 1
//

// Register: OPTION_REG
volatile unsigned char           OPTION          @ 0x081;
// bit and bitfield definitions
volatile bit PS0                 @ ((unsigned)&OPTION*8)+0;
volatile bit PS1                 @ ((unsigned)&OPTION*8)+1;
volatile bit PS2                 @ ((unsigned)&OPTION*8)+2;
volatile bit PSA                 @ ((unsigned)&OPTION*8)+3;
volatile bit T0SE                @ ((unsigned)&OPTION*8)+4;
volatile bit T0CS                @ ((unsigned)&OPTION*8)+5;
volatile bit INTEDG              @ ((unsigned)&OPTION*8)+6;
volatile bit nPAPU               @ ((unsigned)&OPTION*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PS                  : 3;
        unsigned	PSA                 : 1;
        unsigned	T0SE                : 1;
        unsigned	T0CS                : 1;
        unsigned	INTEDG              : 1;
        unsigned	nPAPU               : 1;
    };
    struct {
        unsigned	PS0                 : 1;
        unsigned	PS1                 : 1;
        unsigned	PS2                 : 1;
    };
} OPTIONbits @ 0x081;
#endif

// Register: TRISA
volatile unsigned char           TRISA               @ 0x085;
// bit and bitfield definitions
volatile bit TRISA0              @ ((unsigned)&TRISA*8)+0;
volatile bit TRISA1              @ ((unsigned)&TRISA*8)+1;
volatile bit TRISA2              @ ((unsigned)&TRISA*8)+2;
volatile bit TRISA3              @ ((unsigned)&TRISA*8)+3;
volatile bit TRISA4              @ ((unsigned)&TRISA*8)+4;
volatile bit TRISA5              @ ((unsigned)&TRISA*8)+5;
volatile bit TRISA6              @ ((unsigned)&TRISA*8)+6;
volatile bit TRISA7              @ ((unsigned)&TRISA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISA0              : 1;
        unsigned	TRISA1              : 1;
        unsigned	TRISA2              : 1;
        unsigned	TRISA3              : 1;
        unsigned	TRISA4              : 1;
        unsigned	TRISA5              : 1;
        unsigned	TRISA6              : 1;
        unsigned	TRISA7              : 1;
    };
    struct {
        unsigned	TRISA               : 8;
    };
} TRISAbits @ 0x085;
#endif

// Register: TRISA
volatile unsigned char           TRISB               @ 0x086;
// bit and bitfield definitions
volatile bit TRISB0              @ ((unsigned)&TRISB*8)+0;
volatile bit TRISB1              @ ((unsigned)&TRISB*8)+1;
volatile bit TRISB2              @ ((unsigned)&TRISB*8)+2;
volatile bit TRISB3              @ ((unsigned)&TRISB*8)+3;
volatile bit TRISB4              @ ((unsigned)&TRISB*8)+4;
volatile bit TRISB5              @ ((unsigned)&TRISB*8)+5;
volatile bit TRISB6              @ ((unsigned)&TRISB*8)+6;
volatile bit TRISB7              @ ((unsigned)&TRISB*8)+7;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	TRISB               : 8;
    };
    struct {
        unsigned	TRISB0              : 1;
        unsigned	TRISB1              : 1;
        unsigned	TRISB2              : 1;
        unsigned	TRISB3              : 1;
        unsigned	TRISB4              : 1;
        unsigned	TRISB5              : 1;
        unsigned	TRISB6              : 1;
        unsigned	TRISB7              : 1;
    };
} TRISBbits @ 0x086;
#endif

// Register: TRISC
volatile unsigned char           TRISC               @ 0x087;
// bit and bitfield definitions
volatile bit TRISC0              @ ((unsigned)&TRISC*8)+0;
volatile bit TRISC1              @ ((unsigned)&TRISC*8)+1;
volatile bit TRISC2              @ ((unsigned)&TRISC*8)+2;
volatile bit TRISC3              @ ((unsigned)&TRISC*8)+3;
volatile bit TRISC4              @ ((unsigned)&TRISC*8)+4;
volatile bit TRISC5              @ ((unsigned)&TRISC*8)+5;
volatile bit TRISC6              @ ((unsigned)&TRISC*8)+6;
volatile bit TRISC7              @ ((unsigned)&TRISC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC               : 8;
    };
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
        unsigned	TRISC2              : 1;
        unsigned	TRISC3              : 1;
        unsigned	TRISC4              : 1;
        unsigned	TRISC5              : 1;
        unsigned	TRISC6              : 1;
        unsigned	TRISC7              : 1;
    };
} TRISCbits @ 0x087;
#endif

// Register: TRISD
volatile unsigned char           TRISD               @ 0x088;
// bit and bitfield definitions
volatile bit TRISD0              @ ((unsigned)&TRISD*8)+0;
volatile bit TRISD1              @ ((unsigned)&TRISD*8)+1;
volatile bit TRISD2              @ ((unsigned)&TRISD*8)+2;
volatile bit TRISD3              @ ((unsigned)&TRISD*8)+3;
volatile bit TRISD4              @ ((unsigned)&TRISD*8)+4;
volatile bit TRISD5              @ ((unsigned)&TRISD*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISD               : 6;
    };
    struct {
        unsigned	TRISD0              : 1;
        unsigned	TRISD1              : 1;
        unsigned	TRISD2              : 1;
        unsigned	TRISD3              : 1;
        unsigned	TRISD4              : 1;
        unsigned	TRISD5              : 1;
    };
} TRISDbits @ 0x088;
#endif


// Register: PIE2
volatile unsigned char           PIE2               @ 0x089;
// bit and bitfield definitions
volatile bit C0IE              @ ((unsigned)&PIE2*8)+0;
volatile bit C1IE              @ ((unsigned)&PIE2*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C0IE              : 1;
        unsigned	C1IE              : 1;
    };
} PIE2bits @ 0x089;
#endif

       
// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit ADCIE                 @ ((unsigned)&PIE1*8)+0;
volatile bit TMR2IE                @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE                 @ ((unsigned)&PIE1*8)+2;
volatile bit TMR1IE                @ ((unsigned)&PIE1*8)+3;
volatile bit ACMPIE                @ ((unsigned)&PIE1*8)+4;
volatile bit LVDIE                 @ ((unsigned)&PIE1*8)+5;
volatile bit CKMIE                 @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                  @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIE               : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
        unsigned	TMR1IE              : 1;
        unsigned	ACMPIE              : 1;
        unsigned	LVDIE               : 1;
        unsigned	CKMIE               : 1;
        unsigned	EEIE                : 1;
    };
} PIE1bits @ 0x08C;
#endif

// Register: P1AUX
volatile unsigned char           P1AUX                @ 0x08D;
// bit and bitfield definitions
volatile bit P1DF2                  @ ((unsigned)&P1AUX*8)+0;
volatile bit P1DF2E                 @ ((unsigned)&P1AUX*8)+1;
volatile bit P1CF2                  @ ((unsigned)&P1AUX*8)+2;
volatile bit P1CF2E                 @ ((unsigned)&P1AUX*8)+3;
volatile bit P1B2SS0                @ ((unsigned)&P1AUX*8)+4;
volatile bit P1B2SS1                @ ((unsigned)&P1AUX*8)+5;
volatile bit P1BKM                  @ ((unsigned)&P1AUX*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DF2                  : 1;
        unsigned	P1DF2E                 : 1;
        unsigned	P1CF2                  : 1;
        unsigned	P1CF2E                 : 1;
        unsigned	P1B2SS0                : 1;
        unsigned	P1B2SS1                : 1;
        unsigned	                       : 1;
        unsigned	P1BKM                  : 1;
    };
} P1AUXbits @ 0x08D;
#endif

// Register: PCON
volatile unsigned char           PCON                @ 0x08E;
// bit and bitfield definitions
volatile bit nBOR                @ ((unsigned)&PCON*8)+0;
volatile bit nPOR                @ ((unsigned)&PCON*8)+1;
volatile bit LVDW                @ ((unsigned)&PCON*8)+2;
volatile bit LVDEN               @ ((unsigned)&PCON*8)+3;
volatile bit LVDL0               @ ((unsigned)&PCON*8)+4;
volatile bit LVDL1               @ ((unsigned)&PCON*8)+5;
volatile bit LVDL2               @ ((unsigned)&PCON*8)+6;
volatile bit LVDL3               @ ((unsigned)&PCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	nBOR                : 1;
        unsigned	nPOR                : 1;
        unsigned	LVDW                : 1;
        unsigned	LVDEN               : 1;
        unsigned	LVDL                : 4;
        	
    };
    struct {
				unsigned	                    : 4;
        unsigned	LVDL0               : 1;
        unsigned	LVDL1               : 1;
        unsigned	LVDL2               : 1;
        unsigned	LVDL3               : 1;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCCON
volatile unsigned char           OSCCON              @ 0x08F;
// bit and bitfield definitions
volatile bit SCS                    @ ((unsigned)&OSCCON*8)+0;
volatile bit LTS                    @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                    @ ((unsigned)&OSCCON*8)+2;
volatile bit OSTS                   @ ((unsigned)&OSCCON*8)+3;
volatile bit IRCF0                  @ ((unsigned)&OSCCON*8)+4;
volatile bit IRCF1                  @ ((unsigned)&OSCCON*8)+5;
volatile bit IRCF2                  @ ((unsigned)&OSCCON*8)+6;
volatile bit LFMOD                  @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCS                    : 1;
        unsigned	LTS                    : 1;
        unsigned	HTS                    : 1;
        unsigned	OSTS                   : 1;
        unsigned	IRCF                   : 3;
        unsigned	LFMOD                  : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	IRCF0               : 1;
        unsigned	IRCF1               : 1;
        unsigned	IRCF2               : 1;
    };
} OSCCONbits @ 0x08F;
#endif

// Register: UR1DATL
volatile unsigned char           UR1DATL              @ 0x090;
// bit and bitfield definitions

// Register: UR1DATH
volatile unsigned char           UR1DATH              @ 0x091;
       
// Register: UR1CR1
volatile unsigned char           UR1CR1                 @ 0x092;
// bit and bitfield definitions
volatile bit UR1EN                      @ ((unsigned)&UR1CR1*8)+0;
volatile bit UR1TXEN                    @ ((unsigned)&UR1CR1*8)+1;
volatile bit UR1RXEN                    @ ((unsigned)&UR1CR1*8)+2;
volatile bit UR1PCEN                    @ ((unsigned)&UR1CR1*8)+3;
volatile bit UR1EVEN                    @ ((unsigned)&UR1CR1*8)+4;
volatile bit UR1MODE                    @ ((unsigned)&UR1CR1*8)+5;
volatile bit UR1STOP                    @ ((unsigned)&UR1CR1*8)+6;
volatile bit UR1HDSEL                   @ ((unsigned)&UR1CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1EN                      : 1;
        unsigned	UR1TXEN                    : 1;
        unsigned	UR1RXEN                    : 1;
        unsigned	UR1PCEN                    : 1;
        unsigned	UR1EVEN                	   : 1;
        unsigned	UR1MODE                    : 1;
        unsigned	UR1STOP              	     : 1;
        unsigned	UR1HDSEL                   : 1;
    };
} UR1CR1bits @ 0x091;
#endif

// Register: UR1CR2
volatile unsigned char           UR1CR2              @ 0x093;
// bit and bitfield definitions
volatile bit UR1TXEIE                     @ ((unsigned)&UR1CR2*8)+0;
volatile bit UR1RXNEIE                    @ ((unsigned)&UR1CR2*8)+1;
volatile bit UR1ERRIE                     @ ((unsigned)&UR1CR2*8)+2;
volatile bit UR1BRRH0                     @ ((unsigned)&UR1CR2*8)+4;
volatile bit UR1BRRH1                     @ ((unsigned)&UR1CR2*8)+5;
volatile bit UR1BRRH2                     @ ((unsigned)&UR1CR2*8)+6;
volatile bit UR1BRRH3                     @ ((unsigned)&UR1CR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
	 struct {
        unsigned	                    	       : 4;
        unsigned	UR1BRRH                      : 4;
    };
    struct {
        unsigned	UR1TXEIE                     : 1;
        unsigned	UR1RXNEIE                    : 1;
        unsigned	UR1ERRIE                     : 1;
        unsigned			                         : 1;
        unsigned	UR1BRRH0                	   : 1;
        unsigned	UR1BRRH1                     : 1;
        unsigned	UR1BRRH2                	   : 1;
        unsigned	UR1BRRH3                	   : 1;
    };
} UR1CR2bits @ 0x093;
#endif


// Register: UR1BRRL
volatile unsigned char           UR1BRRL              @ 0x094;

      
// Register: UR1STAT
volatile unsigned char           UR1STAT                @ 0x095;
// bit and bitfield definitions
volatile bit UR1TXEF                @ ((unsigned)&UR1STAT*8)+0;
volatile bit UR1RXNEF               @ ((unsigned)&UR1STAT*8)+1;
volatile bit UR1FEF                 @ ((unsigned)&UR1STAT*8)+2;
volatile bit UR1RXFULL              @ ((unsigned)&UR1STAT*8)+3;
volatile bit UR1PEF                 @ ((unsigned)&UR1STAT*8)+4;
volatile bit UR1OVF                 @ ((unsigned)&UR1STAT*8)+5;
volatile bit UR1TXBSY               @ ((unsigned)&UR1STAT*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1TXEF               : 1;
        unsigned	UR1RXNEF              : 1;
        unsigned	UR1FEF                : 1;
        unsigned	UR1RXFULL             : 1;
        unsigned	UR1PEF                : 1;
        unsigned	UR1OVF                : 1;
        unsigned	UR1TXBSY              : 1;
    };
} UR1STATbits @ 0x095;
#endif


// Register: OP0CR0
volatile unsigned char           OP0CR0                @ 0x096;
// bit and bitfield definitions
volatile bit OP0ON                @ ((unsigned)&OP0CR0*8)+0;
volatile bit OP0FR0               @ ((unsigned)&OP0CR0*8)+1;
volatile bit OP0FR1               @ ((unsigned)&OP0CR0*8)+2;
volatile bit OP0FR2               @ ((unsigned)&OP0CR0*8)+3;
volatile bit OP0NSEL0             @ ((unsigned)&OP0CR0*8)+4;
volatile bit OP0NSEL1             @ ((unsigned)&OP0CR0*8)+5;
volatile bit OP0PSEL              @ ((unsigned)&OP0CR0*8)+6;
volatile bit OP0OUT               @ ((unsigned)&OP0CR0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OP0ON               : 1;
        unsigned	OP0FR0              : 1;
        unsigned	OP0FR1              : 1;
        unsigned	OP0FR2              : 1;
        unsigned	OP0NSEL0            : 1;
        unsigned	OP0NSEL1            : 1;
        unsigned	OP0PSEL             : 1;
        unsigned	OP0OUT              : 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	OP0FR               : 3;
        unsigned	OP0NSEL             : 2;
    };
} OP0CR0bits @ 0x096;
#endif
    
// Register: OP0CR1
volatile unsigned char           OP0CR1              @ 0x097;
// bit and bitfield definitions
volatile bit OPTOIO                    @ ((unsigned)&OP0CR1*8)+0;
volatile bit OPTODIG                   @ ((unsigned)&OP0CR1*8)+1;
volatile bit OP0FCAPE                  @ ((unsigned)&OP0CR1*8)+3;
volatile bit IPINSW                    @ ((unsigned)&OP0CR1*8)+4;
volatile bit OPINSW                    @ ((unsigned)&OP0CR1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OPTOIO             : 1;
        unsigned	OPTODIG            : 1;
        unsigned	                   : 1;
        unsigned	OP0FCAPE		       : 1;
        unsigned	IPINSW             : 1;
        unsigned	OPINSW             : 1;
    };
} OP0CR1bits @ 0x097;
#endif

// Register: IOCA
volatile unsigned char           IOCA              @ 0x098;
// bit and bitfield definitions
volatile bit IOCA0                    @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1                    @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2                    @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3                    @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4                    @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5                    @ ((unsigned)&IOCA*8)+5;
volatile bit IOCA6                    @ ((unsigned)&IOCA*8)+6;
volatile bit IOCA7                    @ ((unsigned)&IOCA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA0               : 1;
        unsigned	IOCA1               : 1;
        unsigned	IOCA2               : 1;
        unsigned	IOCA3               : 1;
        unsigned	IOCA4               : 1;
        unsigned	IOCA5               : 1;
        unsigned	IOCA6               : 1;
        unsigned	IOCA7               : 1;
    };
    struct {
        unsigned	IOCA                : 8;
    };
} IOCAbits @ 0x098;
#endif

// Register: WDTCON
volatile unsigned char           WDTCON              @ 0x099;
// bit and bitfield definitions
volatile bit SWDTEN           @ ((unsigned)&WDTCON*8)+0;
volatile bit WDTPS0           @ ((unsigned)&WDTCON*8)+1;
volatile bit WDTPS1           @ ((unsigned)&WDTCON*8)+2;
volatile bit WDTPS2           @ ((unsigned)&WDTCON*8)+3;
volatile bit WDTPS3           @ ((unsigned)&WDTCON*8)+4;
volatile bit WCKSRC0          @ ((unsigned)&WDTCON*8)+5;
volatile bit WCKSRC1          @ ((unsigned)&WDTCON*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	WDTPS               : 4;
        unsigned	WCKSRC              : 2;
    };
    struct {
        unsigned	SWDTEN              : 1;
        unsigned	WDTPS0              : 1;
        unsigned	WDTPS1              : 1;
        unsigned	WDTPS2              : 1;
        unsigned	WDTPS3              : 1;
        unsigned	WCKSRC0             : 1;
        unsigned	WCKSRC1             : 1;
    };
} WDTCONbits @ 0x099;
#endif

// Register: EEDAT
volatile unsigned char           EEDAT              @ 0x09A;
// bit and bitfield definitions

// Register: EEADR
volatile unsigned char           EEADR              @ 0x09B;
// bit and bitfield definitions


// Register: EECON1
volatile unsigned char           EECON1              @ 0x09C;
// bit and bitfield definitions
volatile bit RD                  @ ((unsigned)&EECON1*8)+0;
volatile bit PONLY               @ ((unsigned)&EECON1*8)+1;
volatile bit WREN1               @ ((unsigned)&EECON1*8)+2;
volatile bit WRERR               @ ((unsigned)&EECON1*8)+3;
volatile bit WREN2               @ ((unsigned)&EECON1*8)+4;
volatile bit WREN3               @ ((unsigned)&EECON1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	PONLY               : 1;
        unsigned	WREN1               : 1;
        unsigned	WRERR               : 1;
        unsigned	WREN2               : 1;
        unsigned	WREN3               : 1;
    };
} EECON1bits @ 0x09C;
#endif

// Register: EECON2
volatile unsigned char           EECON2             @ 0x09D;
// bit and bitfield definitions
volatile bit WR                  @ ((unsigned)&EECON2*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WR                  : 1;
    };
} EECON2bits @ 0x09D;
#endif
       
// Register: P1OE0
volatile unsigned char           P1OE0             @ 0x09E;
// bit and bitfield definitions
volatile bit P1A0OE               @ ((unsigned)&P1OE0*8)+0;
volatile bit P1A0NOE              @ ((unsigned)&P1OE0*8)+1;
volatile bit P1A1OE               @ ((unsigned)&P1OE0*8)+2;
volatile bit P1A1NOE              @ ((unsigned)&P1OE0*8)+3;
volatile bit P1A2OE               @ ((unsigned)&P1OE0*8)+4;
volatile bit P1A2NOE              @ ((unsigned)&P1OE0*8)+5;
volatile bit P1B0OE               @ ((unsigned)&P1OE0*8)+6;
volatile bit P1C0OE               @ ((unsigned)&P1OE0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0OE                  : 1;
        unsigned	P1A0NOE                 : 1;
        unsigned	P1A1OE                  : 1;
        unsigned	P1A1NOE                 : 1;
        unsigned	P1A2OE                  : 1;
        unsigned	P1A2NOE                 : 1;
        unsigned	P1B0OE                  : 1;
        unsigned	P1C0OE                  : 1;
    };
} P1OE0bits @ 0x09E;
#endif


// Register: ADCON1
volatile unsigned char           P1OE1             @ 0x09F;
// bit and bitfield definitions
volatile bit P1B1OE                  @ ((unsigned)&P1OE1*8)+1;
volatile bit P1C1OE                  @ ((unsigned)&P1OE1*8)+2;
volatile bit P1D0OE                  @ ((unsigned)&P1OE1*8)+5;
volatile bit P1D1OE                  @ ((unsigned)&P1OE1*8)+6;
volatile bit P1D2OE                  @ ((unsigned)&P1OE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
				unsigned	                      : 1;
				unsigned	P1B1OE                : 1;
				unsigned	P1C1OE                : 1;
        unsigned	                      : 2;
        unsigned	P1D0OE                : 1;
        unsigned	P1D1OE                : 1;
        unsigned	P1D2OE                : 1;
    };
} P1OE1bits @ 0x09F;
#endif

// Special function register definitions: Bank 2
//

// Register: MSCON1
volatile unsigned char           MSCON1          @ 0x0101;
// bit and bitfield definitions
volatile bit HIRCM             	  @ ((unsigned)&MSCON1*8)+0;
volatile bit AUXPGE             	@ ((unsigned)&MSCON1*8)+1;
volatile bit LVRCKS             	@ ((unsigned)&MSCON1*8)+2;
volatile bit LVRDEB             	@ ((unsigned)&MSCON1*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	HIRCM              : 1;
        unsigned	AUXPGE             : 1;
        unsigned	LVRCKS             : 1;
        unsigned	LVRDEB             : 1;
    };
} MSCON1bits @ 0x0101;
#endif


// Register: T0CON0
volatile unsigned char           T0CON0          @ 0x0105;
// bit and bitfield definitions
volatile bit T0CKSRC0             	@ ((unsigned)&T0CON0*8)+0;
volatile bit T0CKSRC1             	@ ((unsigned)&T0CON0*8)+1;
volatile bit T0CKRUN              	@ ((unsigned)&T0CON0*8)+2;
volatile bit T0ON                 	@ ((unsigned)&T0CON0*8)+3;
volatile bit P0AOE                	@ ((unsigned)&T0CON0*8)+4;
volatile bit P0ANOE               	@ ((unsigned)&T0CON0*8)+5;
volatile bit T0DZ0                	@ ((unsigned)&T0CON0*8)+6;
volatile bit T0DZ1                 	@ ((unsigned)&T0CON0*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T0CKSRC              : 2;
        unsigned	                     : 4;
        unsigned	T0DZ                 : 2;
    };
    struct {
        unsigned	T0CKSRC0             : 1;
        unsigned	T0CKSRC1             : 1;
        unsigned	T0CKRUN              : 1;
        unsigned	T0ON                 : 1;
        unsigned	P0AOE                : 1;
        unsigned	P0ANOE               : 1;
        unsigned	T0DZ0                : 1;
        unsigned	T0DZ1                : 1;
    };
} T0CON0bits @ 0x0105;
#endif


// Register: T1CON0
volatile unsigned char           T1CON0          @ 0x0106;
// bit and bitfield definitions
volatile bit T1CKSRC0             	@ ((unsigned)&T1CON0*8)+0;
volatile bit T1CKSRC1             	@ ((unsigned)&T1CON0*8)+1;
volatile bit T1ON             	    @ ((unsigned)&T1CON0*8)+2;
volatile bit T1CKRUN               	@ ((unsigned)&T1CON0*8)+3;
volatile bit T1CKPSA               	@ ((unsigned)&T1CON0*8)+4;
volatile bit T1ECKE               	@ ((unsigned)&T1CON0*8)+5;
volatile bit T1AUSTP               	@ ((unsigned)&T1CON0*8)+6;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CKSRC           : 2;
    };
    struct {
        unsigned	T1CKSRC0          : 1;
        unsigned	T1CKSRC1          : 1;
        unsigned	T1ON              : 1;
        unsigned	T1CKRUN           : 1;
        unsigned	T1CKPSA           : 1;
        unsigned	T1ECKE            : 1;
        unsigned	T1AUSTP           : 1;
    };
} T1CON0bits @ 0x0106;
#endif


// Register: PR0
volatile unsigned char           PR0            @ 0x0107;
// bit and bitfield definitions


// Register: T0DUTY
volatile unsigned char           T0DUTY         @ 0x0108;
// bit and bitfield definitions

// Register: FOSCCALL
volatile unsigned char           FOSCCALL       @ 0x0109;
// bit and bitfield definitions

// Register: MSCON0
volatile unsigned char           MSCON0         @ 0x010C;
// bit and bitfield definitions
volatile bit T2CKRUN             @ ((unsigned)&MSCON0*8)+0;
volatile bit CKCNTI              @ ((unsigned)&MSCON0*8)+1;
volatile bit CKMAVG              @ ((unsigned)&MSCON0*8)+2;
volatile bit SLVREN              @ ((unsigned)&MSCON0*8)+3;
volatile bit CLKOS               @ ((unsigned)&MSCON0*8)+4;
volatile bit ROMLPE              @ ((unsigned)&MSCON0*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKRUN            : 1;
        unsigned	CKCNTI             : 1;
        unsigned	CKMAVG             : 1;
        unsigned	SLVREN             : 1;
        unsigned	CLKOS              : 1;
        unsigned	ROMLPE             : 1;
    };
} MSCON0bits @ 0x010C;
#endif
// Register: MSCON2
volatile unsigned char           MSCON2         @ 0x010D;
// bit and bitfield definitions
volatile bit T1EVTS0              @ ((unsigned)&MSCON2*8)+0;
volatile bit T1EVTS1              @ ((unsigned)&MSCON2*8)+1;
volatile bit T1EVTS2              @ ((unsigned)&MSCON2*8)+2;
volatile bit STRTYP0              @ ((unsigned)&MSCON2*8)+3;
volatile bit STRTYP1              @ ((unsigned)&MSCON2*8)+4;
volatile bit CMAUSTR              @ ((unsigned)&MSCON2*8)+5;
volatile bit P0AP                 @ ((unsigned)&MSCON2*8)+6;
volatile bit P0ANP                @ ((unsigned)&MSCON2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1EVTS0            : 1;
        unsigned	T1EVTS1            : 1;
        unsigned	T1EVTS2            : 1;
        unsigned	STRTYP0            : 1;
        unsigned	STRTYP1            : 1;
        unsigned	CMAUSTR            : 1;
        unsigned	P0AP               : 1;
        unsigned	P0ANP              : 1;
    };
    struct {
        unsigned	T1EVTS            : 3;
        unsigned	STRTYP            : 2;
    };
} MSCON2bits @ 0x010D;
#endif

// Register: LEBCON
volatile unsigned char           LEBCON          @ 0x010E;
// bit and bitfield definitions
volatile bit EDGS               @ ((unsigned)&LEBCON*8)+3;
volatile bit LEBCH0             @ ((unsigned)&LEBCON*8)+5;
volatile bit LEBCH1             @ ((unsigned)&LEBCON*8)+6;
volatile bit LEBEN              @ ((unsigned)&LEBCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                   : 3;
        unsigned	EDGS               : 1; 
        unsigned	                   : 1; 
        unsigned	LEBCH0             : 1;
        unsigned	LEBCH1             : 1;
        unsigned	LEBEN              : 1;
    };
    struct {
        unsigned	                   : 5;
        unsigned	LEBCH              : 2;
    };
} LEBCONbits @ 0x010E;
#endif

// Register: ADCMPH
volatile unsigned char           ADCMPH       @ 0x010F;
// bit and bitfield definitions

// Register: ADDLY
volatile unsigned char           ADDLY        @ 0x0110;
// bit and bitfield definitions

// Register: ADRESL
volatile unsigned char           ADRESL       @ 0x0111;
// bit and bitfield definitions


// Register: ADRESH
volatile unsigned char           ADRESH          @ 0x0112;
// bit and bitfield definitions

// Register: ADCON0
volatile unsigned char           ADCON0          @ 0x0113;
// bit and bitfield definitions
volatile bit ADON               @ ((unsigned)&ADCON0*8)+0;
volatile bit GO_DONE            @ ((unsigned)&ADCON0*8)+1;
volatile bit ADEX               @ ((unsigned)&ADCON0*8)+2;
volatile bit CHS0               @ ((unsigned)&ADCON0*8)+3;
volatile bit CHS1               @ ((unsigned)&ADCON0*8)+4;
volatile bit CHS2               @ ((unsigned)&ADCON0*8)+5;
volatile bit CHS3               @ ((unsigned)&ADCON0*8)+6;
volatile bit CHS4               @ ((unsigned)&ADCON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 3;
        unsigned	CHS                 : 5;
    };
    struct {
        unsigned	ADON              : 1;
        unsigned	GO_DONE           : 1;
        unsigned	ADEX              : 1;
        unsigned	CHS0              : 1;
        unsigned	CHS1              : 1;
        unsigned	CHS2              : 1;
        unsigned	CHS3              : 1;
        unsigned	CHS4              : 1;
    };
} ADCON0bits @ 0x0113;
#endif

// Register: ADCON1
volatile unsigned char           ADCON1          @ 0x0114;
// bit and bitfield definitions
volatile bit ADPREF0               @ ((unsigned)&ADCON1*8)+0;
volatile bit ADPREF1               @ ((unsigned)&ADCON1*8)+1;
volatile bit ADNREF0               @ ((unsigned)&ADCON1*8)+2;
volatile bit ADNREF1               @ ((unsigned)&ADCON1*8)+3;
volatile bit ADCS0                 @ ((unsigned)&ADCON1*8)+4;
volatile bit ADCS1                 @ ((unsigned)&ADCON1*8)+5;
volatile bit ADCS2                 @ ((unsigned)&ADCON1*8)+6;
volatile bit ADFM                  @ ((unsigned)&ADCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADPREF              : 2;
        unsigned	ADNREF              : 2;
        unsigned	ADCS                : 3;
    };
    struct {
        unsigned	ADPREF0             : 1;
        unsigned	ADPREF1             : 1;
        unsigned	ADNREF0             : 1;
        unsigned	ADNREF1             : 1;
        unsigned	ADCS0               : 1;
        unsigned	ADCS1               : 1;
        unsigned	ADCS2               : 1;
        unsigned	ADFM                : 1;
    };
} ADCON1bits @ 0x0114;
#endif


// Register: ADCON2
volatile unsigned char           ADCON2       @ 0x0115;
// bit and bitfield definitions
volatile bit ETGSEL0             @ ((unsigned)&ADCON2*8)+0;
volatile bit ETGSEL1             @ ((unsigned)&ADCON2*8)+1;
volatile bit ETGSEL2             @ ((unsigned)&ADCON2*8)+2;
volatile bit ADDLY8              @ ((unsigned)&ADCON2*8)+3;
volatile bit ETGTYP0             @ ((unsigned)&ADCON2*8)+4;
volatile bit ETGTYP1             @ ((unsigned)&ADCON2*8)+5;
volatile bit ADINTREF0           @ ((unsigned)&ADCON2*8)+6;
volatile bit ADINTREF1           @ ((unsigned)&ADCON2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ETGSEL            : 3;
        unsigned	                  : 1;
        unsigned	ETGTYP            : 2;
        unsigned	ADINTREF          : 2;
    };
    struct {
        unsigned	ETGSEL0            : 1;
        unsigned	ETGSEL1            : 1;
        unsigned	ETGSEL2            : 1;
        unsigned	ADDLY8             : 1;
        unsigned	ETGTYP0            : 1;
        unsigned	ETGTYP1            : 1;
        unsigned	ADINTREF0          : 1;
        unsigned	ADINTREF1          : 1;
    };
} ADCON2bits @ 0x0115;
#endif

// Register: ADCON3
volatile unsigned char           ADCON3       @ 0x0116;
// bit and bitfield definitions
volatile bit LEBADT               @ ((unsigned)&ADCON3*8)+3;
volatile bit ADCMPE               @ ((unsigned)&ADCON3*8)+5;
volatile bit ADCMPP               @ ((unsigned)&ADCON3*8)+6;
volatile bit ADFBEN               @ ((unsigned)&ADCON3*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 3;
        unsigned	LEBADT            : 1;
        unsigned	                  : 1;
        unsigned	ADCMPE            : 1;
        unsigned	ADCMPP            : 1;
        unsigned	ADFBEN            : 1;
    };
} ADCON3bits @ 0x0116;
#endif

// Register: PR1L
volatile unsigned char           PR1L       @ 0x0117;
// bit and bitfield definitions

// Register: PR1H
volatile unsigned char           PR1H          @ 0x0118;
// bit and bitfield definitions

// Register: TMR5H
volatile unsigned char           TMR1L          @ 0x0119;
// bit and bitfield definitions

// Register: PR5L
volatile unsigned char           TMR1H          @ 0x011A;
// bit and bitfield definitions

// Register: TKCON0
volatile unsigned char           TKCON0       @ 0x011B;
// bit and bitfield definitions
volatile bit TKON               @ ((unsigned)&TKCON0*8)+0;
volatile bit TKCHGS0            @ ((unsigned)&TKCON0*8)+1;
volatile bit TKCHGS1            @ ((unsigned)&TKCON0*8)+2;
volatile bit TKMOD              @ ((unsigned)&TKCON0*8)+3;
volatile bit TKRSEL0            @ ((unsigned)&TKCON0*8)+4;
volatile bit TKRSEL1            @ ((unsigned)&TKCON0*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 1;
        unsigned	TKCHGS            : 2;
        unsigned	                  : 1;
        unsigned	TKRSEL            : 2;
    };
    struct {
        unsigned	TKON              : 1;
        unsigned	TKCHGS0           : 1;
        unsigned	TKCHGS1           : 1;
        unsigned	TKMOD             : 1;
        unsigned	TKRSEL0           : 1;
        unsigned	TKRSEL1           : 1;
    };
} TKCON0bits @ 0x011B;
#endif

// Register: TKEN0
volatile unsigned char           TKEN0       @ 0x011C;
// bit and bitfield definitions
volatile bit TKEN00               @ ((unsigned)&TKEN0*8)+0;
volatile bit TKEN01               @ ((unsigned)&TKEN0*8)+1;
volatile bit TKEN02               @ ((unsigned)&TKEN0*8)+2;
volatile bit TKEN03               @ ((unsigned)&TKEN0*8)+3;
volatile bit TKEN04               @ ((unsigned)&TKEN0*8)+4;
volatile bit TKEN05               @ ((unsigned)&TKEN0*8)+5;
volatile bit TKEN06               @ ((unsigned)&TKEN0*8)+6;
volatile bit TKEN07               @ ((unsigned)&TKEN0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKEN00            : 1;
        unsigned	TKEN01            : 1;
        unsigned	TKEN02            : 1;
        unsigned	TKEN03            : 1;
        unsigned	TKEN04            : 1;
        unsigned	TKEN05            : 1;
        unsigned	TKEN06            : 1;
        unsigned	TKEN07            : 1;
    };
    struct {
        unsigned	TKEN0             : 8;
    };
} TKEN0bits @ 0x011C;
#endif

// Register: TKEN1
volatile unsigned char           TKEN1       @ 0x011D;
// bit and bitfield definitions
volatile bit TKEN10               @ ((unsigned)&TKEN1*8)+0;
volatile bit TKEN11               @ ((unsigned)&TKEN1*8)+1;
volatile bit TKEN12               @ ((unsigned)&TKEN1*8)+2;
volatile bit TKEN13               @ ((unsigned)&TKEN1*8)+3;
volatile bit TKEN14               @ ((unsigned)&TKEN1*8)+4;
volatile bit TKEN15               @ ((unsigned)&TKEN1*8)+5;
volatile bit TKREN                @ ((unsigned)&TKEN1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKEN10            : 1;
        unsigned	TKEN11            : 1;
        unsigned	TKEN12            : 1;
        unsigned	TKEN13            : 1;
        unsigned	TKEN14            : 1;
        unsigned	TKEN15            : 1;
        unsigned	                  : 1;
        unsigned	TKREN             : 1;
    };
    struct {
        unsigned	TKEN1             : 5;
    };
} TKEN1bits @ 0x011D;
#endif


// Register: ANSEL0
volatile unsigned char           ANSEL0       @ 0x011E;
// bit and bitfield definitions

// Register: ANSEL1
volatile unsigned char           ANSEL1       @ 0x011F;
// bit and bitfield definitions

// Special function register definitions: Bank 3
//

// Register: UR0DATL
volatile unsigned char           UR0DATL       @ 0x0185;
// bit and bitfield definitions

// Register: UR0DATL
volatile unsigned char           UR0DATH       @ 0x0186;
// bit and bitfield definitions

// Register: UR0CR1
volatile unsigned char           UR0CR1       @ 0x0187;
// bit and bitfield definitions
volatile bit UR0EN                 @ ((unsigned)&UR0CR1*8)+0;
volatile bit UR0TXEN               @ ((unsigned)&UR0CR1*8)+1;
volatile bit UR0RXEN               @ ((unsigned)&UR0CR1*8)+2;
volatile bit UR0PCEN               @ ((unsigned)&UR0CR1*8)+3;
volatile bit UR0EVEN               @ ((unsigned)&UR0CR1*8)+4;
volatile bit UR0MODE               @ ((unsigned)&UR0CR1*8)+5;
volatile bit UR0STOP               @ ((unsigned)&UR0CR1*8)+6;
volatile bit UR0HDSEL              @ ((unsigned)&UR0CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR0EN             : 1;
        unsigned	UR0TXEN           : 1;
        unsigned	UR0RXEN           : 1;
        unsigned	UR0PCEN           : 1;
        unsigned	UR0EVEN           : 1;
        unsigned	UR0MODE           : 1;
				unsigned	UR0STOP           : 1;
				unsigned	UR0HDSEL          : 1;
    };
} UR0CR1bits @ 0x0187;
#endif

// Register: UR0CR2
volatile unsigned char           UR0CR2       @ 0x0188;
// bit and bitfield definitions
volatile bit UR0TXEIE              @ ((unsigned)&UR0CR2*8)+0;
volatile bit UR0RXNEIE             @ ((unsigned)&UR0CR2*8)+1;
volatile bit UR0ERRIE              @ ((unsigned)&UR0CR2*8)+2;
volatile bit UR0BRRH0              @ ((unsigned)&UR0CR2*8)+4;
volatile bit UR0BRRH1              @ ((unsigned)&UR0CR2*8)+5;
volatile bit UR0BRRH2              @ ((unsigned)&UR0CR2*8)+6;
volatile bit UR0BRRH3              @ ((unsigned)&UR0CR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR0TXEIE            : 1;
        unsigned	UR0RXNEIE           : 1;
        unsigned	UR0ERRIE            : 1;
        unsigned	                    : 1;
        unsigned	UR0BRRH0            : 1;
        unsigned	UR0BRRH1            : 1;
        unsigned	UR0BRRH2            : 1;
				unsigned	UR0BRRH3            : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	UR0BRRH             : 4;
    };
} UR0CR2bits @ 0x0188;
#endif


// Register: UR0BRRL
volatile unsigned char           UR0BRRL       @ 0x0189;
// bit and bitfield definitions

// Register: SPIDAT
volatile unsigned char           SPIDAT       @ 0x018C;
// bit and bitfield definitions

// Register: SPICR0
volatile unsigned char           SPICR0       @ 0x018D;
// bit and bitfield definitions
volatile bit SPIEN              @ ((unsigned)&SPICR0*8)+0;
volatile bit TXBMT              @ ((unsigned)&SPICR0*8)+1;
volatile bit NSSM0              @ ((unsigned)&SPICR0*8)+2;
volatile bit NSSM1              @ ((unsigned)&SPICR0*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SPIEN               : 1;
        unsigned	TXBMT               : 1;
        unsigned	NSSM0               : 1;
        unsigned	NSSM1               : 1;
    };
    struct {
        unsigned	                    : 2;
        unsigned	NSSM                : 2;
    };
} SPICR0bits @ 0x018D;
#endif


// Register: SPICFG
volatile unsigned char           SPICFG       @ 0x018E;
// bit and bitfield definitions
volatile bit RXBMT              @ ((unsigned)&SPICFG*8)+0;
volatile bit SRMT               @ ((unsigned)&SPICFG*8)+1;
volatile bit NSSVAL             @ ((unsigned)&SPICFG*8)+2;
volatile bit SLAS               @ ((unsigned)&SPICFG*8)+3;
volatile bit CPOL               @ ((unsigned)&SPICFG*8)+4;
volatile bit CPHA               @ ((unsigned)&SPICFG*8)+5;
volatile bit MSTEN              @ ((unsigned)&SPICFG*8)+6;
volatile bit SPIBUSY            @ ((unsigned)&SPICFG*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RXBMT               : 1;
        unsigned	SRMT                : 1;
        unsigned	NSSVAL              : 1;
        unsigned	SLAS                : 1;
        unsigned	CPOL                : 1;
        unsigned	CPHA                : 1;
        unsigned	MSTEN               : 1;
        unsigned	SPIBUSY             : 1;
    };
    
} SPICFGbits @ 0x018E;
#endif

// Register: SPISCR
volatile unsigned char           SPISCR       @ 0x018F;
// bit and bitfield definitions


// Register: SPICRCP
volatile unsigned char           SPICRCP       @ 0x0190;
// bit and bitfield definitions

// Register: SPIRXCRC
volatile unsigned char           SPIRXCRC      @ 0x0191;
// bit and bitfield definitions

// Register: SPITXCRC
volatile unsigned char           SPITXCRC      @ 0x0192;
// bit and bitfield definitions


// Register: SPIIER
volatile unsigned char           SPIIER       @ 0x0193;
// bit and bitfield definitions
volatile bit TXE                @ ((unsigned)&SPIIER*8)+0;
volatile bit RXNE               @ ((unsigned)&SPIIER*8)+1;
volatile bit RXERR              @ ((unsigned)&SPIIER*8)+2;
volatile bit WAKUP              @ ((unsigned)&SPIIER*8)+3;
#ifndef _LIB_BUILD
volatile union {
	struct {
        unsigned	TXE                   : 1;
        unsigned	RXNE                  : 1;
				unsigned	RXERR                 : 1;
				unsigned	WAKUP                 : 1;
    };
} SPIIERbits @ 0x0193;
#endif


// Register: SPICR1
volatile unsigned char           SPICR1       @ 0x0194;
// bit and bitfield definitions
volatile bit LSBFIRST             @ ((unsigned)&SPICR1*8)+0;
volatile bit CRCEN                @ ((unsigned)&SPICR1*8)+1;
volatile bit CRCNXT               @ ((unsigned)&SPICR1*8)+2;
volatile bit SSM                  @ ((unsigned)&SPICR1*8)+3;
volatile bit SSI                  @ ((unsigned)&SPICR1*8)+4;
volatile bit RXONLY               @ ((unsigned)&SPICR1*8)+5;
volatile bit BDOE                 @ ((unsigned)&SPICR1*8)+6;
volatile bit BDM                  @ ((unsigned)&SPICR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LSBFIRST             : 1;
        unsigned	CRCEN                : 1;
        unsigned	CRCNXT               : 1;
        unsigned	SSM                  : 1;
        unsigned	SSI            	     : 1;
        unsigned	RXONLY               : 1;
        unsigned	BDOE                 : 1;
        unsigned	BDM             	   : 1;
    };
} SPICR1bits @ 0x0194;
#endif

 
// Register: SPISTAT
volatile unsigned char           SPISTAT       @ 0x0195;
// bit and bitfield definitions
volatile bit CRCERR               @ ((unsigned)&SPISTAT*8)+0;
volatile bit WKF                  @ ((unsigned)&SPISTAT*8)+1;
volatile bit RXOVRN               @ ((unsigned)&SPISTAT*8)+4;
volatile bit MODF                 @ ((unsigned)&SPISTAT*8)+5;
volatile bit WCOL                 @ ((unsigned)&SPISTAT*8)+6;
volatile bit SPIF                 @ ((unsigned)&SPISTAT*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CRCERR               : 1;
        unsigned	WKF                  : 1;
        unsigned	                     : 2;
        unsigned	RXOVRN            	 : 1;
        unsigned	MODF                 : 1;
        unsigned	WCOL                 : 1;
        unsigned	SPIF             	   : 1;
    };
} SPISTATbits @ 0x0195;
#endif

// Register: I2CCR1
volatile unsigned char           I2CCR1       @ 0x0196;
// bit and bitfield definitions
volatile bit I2CEN                 @ ((unsigned)&I2CCR1*8)+0;
volatile bit MASTER                @ ((unsigned)&I2CCR1*8)+1;
volatile bit START                 @ ((unsigned)&I2CCR1*8)+2;
volatile bit WRN                   @ ((unsigned)&I2CCR1*8)+3;
volatile bit STOP                  @ ((unsigned)&I2CCR1*8)+4;
volatile bit ADDRM                 @ ((unsigned)&I2CCR1*8)+5;
volatile bit STRET                 @ ((unsigned)&I2CCR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	I2CEN                : 1;
        unsigned	MASTER               : 1;
        unsigned	START                : 1;
        unsigned	WRN                	 : 1;
        unsigned	STOP                 : 1;
        unsigned	ADDRM                : 1;
        unsigned	                     : 1;
        unsigned	STRET           	   : 1;
    };
} I2CCR1bits @ 0x0196;
#endif

// Register: I2CCR2
volatile unsigned char           I2CCR2       @ 0x0197;
// bit and bitfield definitions
volatile bit I2CIE                 @ ((unsigned)&I2CCR2*8)+0;
volatile bit DUTY                  @ ((unsigned)&I2CCR2*8)+4;
volatile bit NACK                  @ ((unsigned)&I2CCR2*8)+5;
volatile bit I2CADDRH0             @ ((unsigned)&I2CCR2*8)+6;
volatile bit I2CADDRH1             @ ((unsigned)&I2CCR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	I2CIE                : 1;
        unsigned	                     : 3;
        unsigned	DUTY                 : 1;
        unsigned	NACK               	 : 1;
        unsigned	STOP                 : 1;
        unsigned	I2CADDRH0            : 1;
        unsigned	I2CADDRH1       	   : 1;
    };
} I2CCR2bits @ 0x0197;
#endif

// Register: I2CADDR
volatile unsigned char           I2CADDR          @ 0x0198;
// bit and bitfield definitions

// Register: I2CCCR
volatile unsigned char           I2CCCR          @ 0x0199;
// bit and bitfield definitions

// Register: I2CDAT
volatile unsigned char           I2CDAT          @ 0x019A;
// bit and bitfield definitions

// Register: TKEN2
volatile unsigned char           TKEN2       @ 0x019C;
// bit and bitfield definitions
volatile bit TKEN20              @ ((unsigned)&TKEN2*8)+0;
volatile bit TKEN21              @ ((unsigned)&TKEN2*8)+1;
volatile bit TKEN22              @ ((unsigned)&TKEN2*8)+2;
volatile bit TKEN23              @ ((unsigned)&TKEN2*8)+3;
volatile bit TKEN24              @ ((unsigned)&TKEN2*8)+4;
volatile bit TKEN25              @ ((unsigned)&TKEN2*8)+5;
volatile bit TKEN26              @ ((unsigned)&TKEN2*8)+6;
volatile bit TKEN27              @ ((unsigned)&TKEN2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKEN2             : 8;
    };
    struct {
        unsigned	TKEN20  	       : 1;
        unsigned	TKEN21           : 1;
        unsigned	TKEN22           : 1;
        unsigned	TKEN23           : 1;
        unsigned	TKEN24  	       : 1;
        unsigned	TKEN25           : 1;
        unsigned	TKEN26           : 1;
        unsigned	TKEN27           : 1;
    };
} TKEN2bits @ 0x019C;
#endif

// Register: TKEN3
volatile unsigned char           TKEN3       @ 0x019D;
// bit and bitfield definitions
volatile bit TKEN30              @ ((unsigned)&TKEN3*8)+0;
volatile bit TKEN31              @ ((unsigned)&TKEN3*8)+1;
volatile bit TKEN32              @ ((unsigned)&TKEN3*8)+2;
volatile bit TKEN33              @ ((unsigned)&TKEN3*8)+3;
volatile bit TKEN34              @ ((unsigned)&TKEN3*8)+4;
volatile bit TKEN35              @ ((unsigned)&TKEN3*8)+5;
volatile bit TKCAPM              @ ((unsigned)&TKEN3*8)+6;
volatile bit VREFM               @ ((unsigned)&TKEN3*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKEN3             : 8;
    };
    struct {
        unsigned	TKEN30  	       : 1;
        unsigned	TKEN31           : 1;
        unsigned	TKEN32           : 1;
        unsigned	TKEN33           : 1;
        unsigned	TKEN34  	       : 1;
        unsigned	TKEN35           : 1;
        unsigned	TKCAPM           : 1;
        unsigned	VREFM            : 1;
    };
} TKEN3bits @ 0x019D;
#endif

// Register: I2CISR
volatile unsigned char           I2CISR       @ 0x019E;
// bit and bitfield definitions
volatile bit IICTXEF           @ ((unsigned)&I2CISR*8)+0;
volatile bit IICRXNEF          @ ((unsigned)&I2CISR*8)+1;
volatile bit BUSERR            @ ((unsigned)&I2CISR*8)+2;
volatile bit DIRF              @ ((unsigned)&I2CISR*8)+2;
volatile bit I2CBUSY           @ ((unsigned)&I2CISR*8)+3;
volatile bit NACKF             @ ((unsigned)&I2CISR*8)+4;
volatile bit ADDRF             @ ((unsigned)&I2CISR*8)+5;
volatile bit STOPF             @ ((unsigned)&I2CISR*8)+6;
volatile bit HOLDF             @ ((unsigned)&I2CISR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IICTXEF           : 1;
        unsigned	IICRXNEF          : 1;
        unsigned	BUSERR            : 1;
        unsigned	I2CBUSY           : 1;
        unsigned	NACKF             : 1;
        unsigned	ADDRF             : 1;
        unsigned	STOPF             : 1;
        unsigned	HOLDF             : 1;
    };
    struct {
        unsigned	                  : 2;
        unsigned	DIRF              : 1;
    };
} I2CISRbits @ 0x019E;
#endif

// Register: UR0STAT
volatile unsigned char           UR0STAT       @ 0x019F;
// bit and bitfield definitions
volatile bit UR0TXEF           @ ((unsigned)&UR0STAT*8)+0;
volatile bit UR0RXNEF          @ ((unsigned)&UR0STAT*8)+1;
volatile bit UR0FEF            @ ((unsigned)&UR0STAT*8)+2;
volatile bit UR0RXFULL         @ ((unsigned)&UR0STAT*8)+3;
volatile bit UR0PEF            @ ((unsigned)&UR0STAT*8)+4;
volatile bit UR0OVF            @ ((unsigned)&UR0STAT*8)+5;
volatile bit UR0TXBSY          @ ((unsigned)&UR0STAT*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR0TXEF           : 1;
        unsigned	UR0RXNEF          : 1;
        unsigned	UR0FEF            : 1;
        unsigned	UR0RXFULL         : 1;
        unsigned	UR0PEF            : 1;
        unsigned	UR0OVF            : 1;
        unsigned	UR0TXBSY          : 1;
    };
} UR0STATbits @ 0x019F;
#endif


// Special function register definitions: Bank 4
// AUXPGE = 1£¬

// Register: ODCONA
volatile unsigned char           ODCONA       @ (0x0205-0X200);
// bit and bitfield definitions
volatile bit ODCONA0            @ ((unsigned)&ODCONA*8)+0;
volatile bit ODCONA1            @ ((unsigned)&ODCONA*8)+1;
volatile bit ODCONA2            @ ((unsigned)&ODCONA*8)+2;
volatile bit ODCONA3            @ ((unsigned)&ODCONA*8)+3;
volatile bit ODCONA4            @ ((unsigned)&ODCONA*8)+4;
volatile bit ODCONA5            @ ((unsigned)&ODCONA*8)+5;
volatile bit ODCONA6            @ ((unsigned)&ODCONA*8)+6;
volatile bit ODCONA7            @ ((unsigned)&ODCONA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ODCONA0            : 1;
        unsigned	ODCONA1            : 1;
        unsigned	ODCONA2            : 1;
        unsigned	ODCONA3            : 1;
        unsigned	ODCONA4            : 1;
        unsigned	ODCONA5            : 1;
        unsigned	ODCONA6            : 1;
        unsigned	ODCONA7            : 1;
    };
    struct {
        unsigned	ODCONA             : 8;
    };
} ODCONAbits @ (0x0205-0X200);
#endif

// Register: ODCONB
volatile unsigned char           ODCONB       @ (0x0206-0X200);
// bit and bitfield definitions
volatile bit ODCONB0            @ ((unsigned)&ODCONB*8)+0;
volatile bit ODCONB1            @ ((unsigned)&ODCONB*8)+1;
volatile bit ODCONB2            @ ((unsigned)&ODCONB*8)+2;
volatile bit ODCONB3            @ ((unsigned)&ODCONB*8)+3;
volatile bit ODCONB4            @ ((unsigned)&ODCONB*8)+4;
volatile bit ODCONB5            @ ((unsigned)&ODCONB*8)+5;
volatile bit ODCONB6            @ ((unsigned)&ODCONB*8)+6;
volatile bit ODCONB7            @ ((unsigned)&ODCONB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ODCONB0            : 1;
        unsigned	ODCONB1            : 1;
        unsigned	ODCONB2            : 1;
        unsigned	ODCONB3            : 1;
        unsigned	ODCONB4            : 1;
        unsigned	ODCONB5            : 1;
        unsigned	ODCONB6            : 1;
        unsigned	ODCONB7            : 1;
    };
    struct {
        unsigned	ODCONB             : 8;
    };
} ODCONBbits @ (0x0206-0X200);
#endif

// Register: ODCONC
volatile unsigned char           ODCONC       @ (0x0207-0X200);
// bit and bitfield definitions
volatile bit ODCONC0            @ ((unsigned)&ODCONC*8)+0;
volatile bit ODCONC1            @ ((unsigned)&ODCONC*8)+1;
volatile bit ODCONC2            @ ((unsigned)&ODCONC*8)+2;
volatile bit ODCONC3            @ ((unsigned)&ODCONC*8)+3;
volatile bit ODCONC4            @ ((unsigned)&ODCONC*8)+4;
volatile bit ODCONC5            @ ((unsigned)&ODCONC*8)+5;
volatile bit ODCONC6            @ ((unsigned)&ODCONC*8)+6;
volatile bit ODCONC7            @ ((unsigned)&ODCONC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ODCONC0            : 1;
        unsigned	ODCONC1            : 1;
        unsigned	ODCONC2            : 1;
        unsigned	ODCONC3            : 1;
        unsigned	ODCONC4            : 1;
        unsigned	ODCONC5            : 1;
        unsigned	ODCONC6            : 1;
        unsigned	ODCONC7            : 1;
    };
    struct {
        unsigned	ODCONC             : 8;
    };
} ODCONCbits @ (0x0207-0X200);
#endif

// Register: ODCOND
volatile unsigned char           ODCOND       @ (0x0208-0X200);
// bit and bitfield definitions
volatile bit ODCOND0            @ ((unsigned)&ODCOND*8)+0;
volatile bit ODCOND1            @ ((unsigned)&ODCOND*8)+1;
volatile bit ODCOND2            @ ((unsigned)&ODCOND*8)+2;
volatile bit ODCOND3            @ ((unsigned)&ODCOND*8)+3;
volatile bit ODCOND4            @ ((unsigned)&ODCOND*8)+4;
volatile bit ODCOND5            @ ((unsigned)&ODCOND*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ODCOND0            : 1;
        unsigned	ODCOND1            : 1;
        unsigned	ODCOND2            : 1;
        unsigned	ODCOND3            : 1;
        unsigned	ODCOND4            : 1;
        unsigned	ODCOND5            : 1;
    };
    struct {
        unsigned	ODCOND             : 6;
    };
} ODCONDbits @ (0x0208-0X200);
#endif

// Register: SCKCFG
volatile unsigned char           SCKCFG       @ (0x0209-0X200);
// bit and bitfield definitions
volatile bit SCKOE              @ ((unsigned)&SCKCFG*8)+1;
volatile bit SCKEN              @ ((unsigned)&SCKCFG*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                   : 1;
        unsigned	SCKOE              : 1;
        unsigned	                   : 5;
        unsigned	SCKEN              : 1;
    };
} SCKCFGbits @ (0x0209-0X200);
#endif

// Register: PSRCAL
volatile unsigned char           PSRCAL       @ (0x020C-0X200);
// bit and bitfield definitions
volatile bit PSRCAL0            @ ((unsigned)&PSRCAL*8)+0;
volatile bit PSRCAL1            @ ((unsigned)&PSRCAL*8)+1;
volatile bit PSRCAL2            @ ((unsigned)&PSRCAL*8)+2;
volatile bit PSRCAL3            @ ((unsigned)&PSRCAL*8)+3;
volatile bit PSRCAL4            @ ((unsigned)&PSRCAL*8)+4;
volatile bit PSRCAL5            @ ((unsigned)&PSRCAL*8)+5;
volatile bit PSRCAL6            @ ((unsigned)&PSRCAL*8)+6;
volatile bit PSRCAL7            @ ((unsigned)&PSRCAL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCAL0            : 1;
        unsigned	PSRCAL1            : 1;
        unsigned	PSRCAL2            : 1;
        unsigned	PSRCAL3            : 1;
        unsigned	PSRCAL4            : 1;
        unsigned	PSRCAL5            : 1;
        unsigned	PSRCAL6            : 1;
        unsigned	PSRCAL7            : 1;
    };
    struct {
        unsigned	PSRCAL             : 8;
    };
} PSRCALbits @ (0x020C-0X200);
#endif

// Register: PSRCAH
volatile unsigned char           PSRCAH       @ (0x020D-0X200);
// bit and bitfield definitions
volatile bit PSRCAH0            @ ((unsigned)&PSRCAH*8)+0;
volatile bit PSRCAH1            @ ((unsigned)&PSRCAH*8)+1;
volatile bit PSRCAH2            @ ((unsigned)&PSRCAH*8)+2;
volatile bit PSRCAH3            @ ((unsigned)&PSRCAH*8)+3;
volatile bit PSRCAH4            @ ((unsigned)&PSRCAH*8)+4;
volatile bit PSRCAH5            @ ((unsigned)&PSRCAH*8)+5;
volatile bit PSRCAH6            @ ((unsigned)&PSRCAH*8)+6;
volatile bit PSRCAH7            @ ((unsigned)&PSRCAH*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCAH0            : 1;
        unsigned	PSRCAH1            : 1;
        unsigned	PSRCAH2            : 1;
        unsigned	PSRCAH3            : 1;
        unsigned	PSRCAH4            : 1;
        unsigned	PSRCAH5            : 1;
        unsigned	PSRCAH6            : 1;
        unsigned	PSRCAH7            : 1;
    };
    struct {
        unsigned	PSRCAH             : 8;
    };
} PSRCAHbits @ (0x020D-0X200);
#endif


// Register: PSRCBL
volatile unsigned char           PSRCBL       @ (0x020E-0X200);
// bit and bitfield definitions
volatile bit PSRCBL0            @ ((unsigned)&PSRCBL*8)+0;
volatile bit PSRCBL1            @ ((unsigned)&PSRCBL*8)+1;
volatile bit PSRCBL2            @ ((unsigned)&PSRCBL*8)+2;
volatile bit PSRCBL3            @ ((unsigned)&PSRCBL*8)+3;
volatile bit PSRCBL4            @ ((unsigned)&PSRCBL*8)+4;
volatile bit PSRCBL5            @ ((unsigned)&PSRCBL*8)+5;
volatile bit PSRCBL6            @ ((unsigned)&PSRCBL*8)+6;
volatile bit PSRCBL7            @ ((unsigned)&PSRCBL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCBL0            : 1;
        unsigned	PSRCBL1            : 1;
        unsigned	PSRCBL2            : 1;
        unsigned	PSRCBL3            : 1;
        unsigned	PSRCBL4            : 1;
        unsigned	PSRCBL5            : 1;
        unsigned	PSRCBL6            : 1;
        unsigned	PSRCBL7            : 1;
    };
    struct {
        unsigned	PSRCBL             : 8;
    };
} PSRCBLbits @ (0x020E-0X200);
#endif

// Register: PSRCBH
volatile unsigned char           PSRCBH       @ (0x020F-0X200);
// bit and bitfield definitions
volatile bit PSRCBH0            @ ((unsigned)&PSRCBH*8)+0;
volatile bit PSRCBH1            @ ((unsigned)&PSRCBH*8)+1;
volatile bit PSRCBH2            @ ((unsigned)&PSRCBH*8)+2;
volatile bit PSRCBH3            @ ((unsigned)&PSRCBH*8)+3;
volatile bit PSRCBH4            @ ((unsigned)&PSRCBH*8)+4;
volatile bit PSRCBH5            @ ((unsigned)&PSRCBH*8)+5;
volatile bit PSRCBH6            @ ((unsigned)&PSRCBH*8)+6;
volatile bit PSRCBH7            @ ((unsigned)&PSRCBH*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCBH0            : 1;
        unsigned	PSRCBH1            : 1;
        unsigned	PSRCBH2            : 1;
        unsigned	PSRCBH3            : 1;
        unsigned	PSRCBH4            : 1;
        unsigned	PSRCBH5            : 1;
        unsigned	PSRCBH6            : 1;
        unsigned	PSRCBH7            : 1;
    };
    struct {
        unsigned	PSRCBH             : 8;
    };
} PSRCBHbits @ (0x020F-0X200);
#endif


// Register: PSRCCL
volatile unsigned char           PSRCCL       @ (0x0210-0X200);
// bit and bitfield definitions
volatile bit PSRCCL0            @ ((unsigned)&PSRCCL*8)+0;
volatile bit PSRCCL1            @ ((unsigned)&PSRCCL*8)+1;
volatile bit PSRCCL2            @ ((unsigned)&PSRCCL*8)+2;
volatile bit PSRCCL3            @ ((unsigned)&PSRCCL*8)+3;
volatile bit PSRCCL4            @ ((unsigned)&PSRCCL*8)+4;
volatile bit PSRCCL5            @ ((unsigned)&PSRCCL*8)+5;
volatile bit PSRCCL6            @ ((unsigned)&PSRCCL*8)+6;
volatile bit PSRCCL7            @ ((unsigned)&PSRCCL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCCL0            : 1;
        unsigned	PSRCCL1            : 1;
        unsigned	PSRCCL2            : 1;
        unsigned	PSRCCL3            : 1;
        unsigned	PSRCCL4            : 1;
        unsigned	PSRCCL5            : 1;
        unsigned	PSRCCL6            : 1;
        unsigned	PSRCCL7            : 1;
    };
    struct {
        unsigned	PSRCCL             : 8;
    };
} PSRCCLbits @ (0x0210-0X200);
#endif

// Register: PSRCCH
volatile unsigned char           PSRCCH       @ (0x0211-0X200);
// bit and bitfield definitions
volatile bit PSRCCH0            @ ((unsigned)&PSRCCH*8)+0;
volatile bit PSRCCH1            @ ((unsigned)&PSRCCH*8)+1;
volatile bit PSRCCH2            @ ((unsigned)&PSRCCH*8)+2;
volatile bit PSRCCH3            @ ((unsigned)&PSRCCH*8)+3;
volatile bit PSRCCH4            @ ((unsigned)&PSRCCH*8)+4;
volatile bit PSRCCH5            @ ((unsigned)&PSRCCH*8)+5;
volatile bit PSRCCH6            @ ((unsigned)&PSRCCH*8)+6;
volatile bit PSRCCH7            @ ((unsigned)&PSRCCH*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCCH0            : 1;
        unsigned	PSRCCH1            : 1;
        unsigned	PSRCCH2            : 1;
        unsigned	PSRCCH3            : 1;
        unsigned	PSRCCH4            : 1;
        unsigned	PSRCCH5            : 1;
        unsigned	PSRCCH6            : 1;
        unsigned	PSRCCH7            : 1;
    };
    struct {
        unsigned	PSRCCH             : 8;
    };
} PSRCCHbits @ (0x0211-0X200);
#endif

// Register: PSRCDL
volatile unsigned char           PSRCDL       @ (0x0212-0X200);
// bit and bitfield definitions
volatile bit PSRCCL0            @ ((unsigned)&PSRCCL*8)+0;
volatile bit PSRCCL1            @ ((unsigned)&PSRCCL*8)+1;
volatile bit PSRCCL2            @ ((unsigned)&PSRCCL*8)+2;
volatile bit PSRCCL3            @ ((unsigned)&PSRCCL*8)+3;
volatile bit PSRCCL4            @ ((unsigned)&PSRCCL*8)+4;
volatile bit PSRCCL5            @ ((unsigned)&PSRCCL*8)+5;
volatile bit PSRCCL6            @ ((unsigned)&PSRCCL*8)+6;
volatile bit PSRCCL7            @ ((unsigned)&PSRCCL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCCL0            : 1;
        unsigned	PSRCCL1            : 1;
        unsigned	PSRCCL2            : 1;
        unsigned	PSRCCL3            : 1;
        unsigned	PSRCCL4            : 1;
        unsigned	PSRCCL5            : 1;
        unsigned	PSRCCL6            : 1;
        unsigned	PSRCCL7            : 1;
    };
    struct {
        unsigned	PSRCDL             : 8;
    };
} PSRCDLbits @ (0x0212-0X200);
#endif

// Register: PSRCDH
volatile unsigned char           PSRCDH       @ (0x0213-0X200);
// bit and bitfield definitions
volatile bit PSRCDH0            @ ((unsigned)&PSRCDH*8)+0;
volatile bit PSRCDH1            @ ((unsigned)&PSRCDH*8)+1;
volatile bit PSRCDH2            @ ((unsigned)&PSRCDH*8)+2;
volatile bit PSRCDH3            @ ((unsigned)&PSRCDH*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCDH0            : 1;
        unsigned	PSRCDH1            : 1;
        unsigned	PSRCDH2            : 1;
        unsigned	PSRCDH3            : 1;
        	
    };
    struct {
        unsigned	PSRCDH             : 4;
    };
} PSRCDHbits @ (0x0213-0X200);
#endif

// Register: PSINKA
volatile unsigned char           PSINKA       @ (0x0214-0X200);
// bit and bitfield definitions
volatile bit PSINKA0            @ ((unsigned)&PSINKA*8)+0;
volatile bit PSINKA1            @ ((unsigned)&PSINKA*8)+1;
volatile bit PSINKA2            @ ((unsigned)&PSINKA*8)+2;
volatile bit PSINKA3            @ ((unsigned)&PSINKA*8)+3;
volatile bit PSINKA4            @ ((unsigned)&PSINKA*8)+4;
volatile bit PSINKA5            @ ((unsigned)&PSINKA*8)+5;
volatile bit PSINKA6            @ ((unsigned)&PSINKA*8)+6;
volatile bit PSINKA7            @ ((unsigned)&PSINKA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKA0            : 1;
        unsigned	PSINKA1            : 1;
        unsigned	PSINKA2            : 1;
        unsigned	PSINKA3            : 1;
        unsigned	PSINKA4            : 1;
        unsigned	PSINKA5            : 1;
        unsigned	PSINKA6            : 1;
        unsigned	PSINKA7            : 1;
    };
    struct {
        unsigned	PSINKA             : 8;
    };
} PSINKAbits @ (0x0214-0X200);
#endif


// Register: PSINKB
volatile unsigned char           PSINKB       @ (0x0215-0X200);
// bit and bitfield definitions
volatile bit PSINKB0            @ ((unsigned)&PSINKB*8)+0;
volatile bit PSINKB1            @ ((unsigned)&PSINKB*8)+1;
volatile bit PSINKB2            @ ((unsigned)&PSINKB*8)+2;
volatile bit PSINKB3            @ ((unsigned)&PSINKB*8)+3;
volatile bit PSINKB4            @ ((unsigned)&PSINKB*8)+4;
volatile bit PSINKB5            @ ((unsigned)&PSINKB*8)+5;
volatile bit PSINKB6            @ ((unsigned)&PSINKB*8)+6;
volatile bit PSINKB7            @ ((unsigned)&PSINKB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKB0            : 1;
        unsigned	PSINKB1            : 1;
        unsigned	PSINKB2            : 1;
        unsigned	PSINKB3            : 1;
        unsigned	PSINKB4            : 1;
        unsigned	PSINKB5            : 1;
        unsigned	PSINKB6            : 1;
        unsigned	PSINKB7            : 1;
    };
    struct {
        unsigned	PSINKB             : 8;
    };
} PSINKBbits @ (0x0215-0X200);
#endif

// Register: PSINKC
volatile unsigned char           PSINKC       @ (0x0216-0X200);
// bit and bitfield definitions
volatile bit PSINKC0            @ ((unsigned)&PSINKC*8)+0;
volatile bit PSINKC1            @ ((unsigned)&PSINKC*8)+1;
volatile bit PSINKC2            @ ((unsigned)&PSINKC*8)+2;
volatile bit PSINKC3            @ ((unsigned)&PSINKC*8)+3;
volatile bit PSINKC4            @ ((unsigned)&PSINKC*8)+4;
volatile bit PSINKC5            @ ((unsigned)&PSINKC*8)+5;
volatile bit PSINKC6            @ ((unsigned)&PSINKC*8)+6;
volatile bit PSINKC7            @ ((unsigned)&PSINKC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKC0            : 1;
        unsigned	PSINKC1            : 1;
        unsigned	PSINKC2            : 1;
        unsigned	PSINKC3            : 1;
        unsigned	PSINKC4            : 1;
        unsigned	PSINKC5            : 1;
        unsigned	PSINKC6            : 1;
        unsigned	PSINKC7            : 1;
    };
    struct {
        unsigned	PSINKC             : 8;
    };
} PSINKCbits @ (0x0216-0X200);
#endif

// Register: PSINKD
volatile unsigned char           PSINKD       @ (0x0217-0X200);
// bit and bitfield definitions
volatile bit PSINKD0            @ ((unsigned)&PSINKD*8)+0;
volatile bit PSINKD1            @ ((unsigned)&PSINKD*8)+1;
volatile bit PSINKD2            @ ((unsigned)&PSINKD*8)+2;
volatile bit PSINKD3            @ ((unsigned)&PSINKD*8)+3;
volatile bit PSINKD4            @ ((unsigned)&PSINKD*8)+4;
volatile bit PSINKD5            @ ((unsigned)&PSINKD*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKD0            : 1;
        unsigned	PSINKD1            : 1;
        unsigned	PSINKD2            : 1;
        unsigned	PSINKD3            : 1;
        unsigned	PSINKD4            : 1;
        unsigned	PSINKD5            : 1;
    };
    struct {
        unsigned	PSINKD             : 6;
    };
} PSINKDbits @ (0x0217-0X200);
#endif

// Register: SOSCPRL
volatile unsigned char           SOSCPRL       @ (0x0218-0X200);
// bit and bitfield definitions

// Register: SOSCPRH
volatile unsigned char           SOSCPRH       @ (0x0219-0X200);
// bit and bitfield definitions

// Register: LVDCON
volatile unsigned char           LVDCON       @ (0x021A-0X200);
// bit and bitfield definitions
volatile bit LVDM0              @ ((unsigned)&LVDCON*8)+0;
volatile bit LVDM1              @ ((unsigned)&LVDCON*8)+1;
volatile bit LVDM2              @ ((unsigned)&LVDCON*8)+2;
volatile bit LVDDEB             @ ((unsigned)&LVDCON*8)+3;
volatile bit LVDP               @ ((unsigned)&LVDCON*8)+4;
volatile bit LVDCKS0            @ ((unsigned)&LVDCON*8)+5;
volatile bit LVDCKS1            @ ((unsigned)&LVDCON*8)+6;
volatile bit SYSON              @ ((unsigned)&LVDCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVDM0              : 1;
        unsigned	LVDM1              : 1;
        unsigned	LVDM2              : 1;
        unsigned	LVDDEB             : 1;
        unsigned	LVDP               : 1;
        unsigned	LVDCKS0            : 1;
        unsigned	LVDCKS1            : 1;
        unsigned	SYSON              : 1;
    };
    struct {
        unsigned	LVDM               : 3;
        unsigned	                   : 2;
        unsigned	LVDCKS             : 2;
    };
} LVDCONbits @ (0x021A-0X200);
#endif

// Register: SECCODE
volatile unsigned char           SECCODE       @ (0x021B-0X200);
// bit and bitfield definitions

// Register: LVDTRIM
volatile unsigned char           LVDTRIM       @ (0x021C-0X200);
// bit and bitfield definitions
volatile bit LVRADJ0              @ ((unsigned)&LVDTRIM*8)+0;
volatile bit LVRADJ1              @ ((unsigned)&LVDTRIM*8)+1;
volatile bit LVRADJ2              @ ((unsigned)&LVDTRIM*8)+2;
volatile bit LVDADJ0              @ ((unsigned)&LVDTRIM*8)+3;
volatile bit LVDADJ1              @ ((unsigned)&LVDTRIM*8)+4;
volatile bit LVDADJ2              @ ((unsigned)&LVDTRIM*8)+5;
volatile bit LVDADJ3              @ ((unsigned)&LVDTRIM*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVRADJ0            : 1;
        unsigned	LVRADJ1            : 1;
        unsigned	LVRADJ2            : 1;
        unsigned	LVDADJ0            : 1;
        unsigned	LVDADJ1            : 1;
        unsigned	LVDADJ2            : 1;
        unsigned	LVDADJ3            : 1;
    };
    struct {
        unsigned	LVRADJ             : 3;
        unsigned	LVDADJ             : 4;
    };
} LVDTRIMbits @ (0x021C-0X200);
#endif

// Register: VRP5VCAL
volatile unsigned char           VRP5VCAL       @ (0x021D-0X200);
// bit and bitfield definitions

// Register: VR2VCAL
volatile unsigned char           VR2VCAL       @ (0x021E-0X200);
// bit and bitfield definitions

// Register: VR3VCAL
volatile unsigned char           VR3VCAL       @ (0x021F-0X200);
// bit and bitfield definitions

// Special function register definitions: Bank 5
//
// AUXPGE = 1£¬

// Register: COMAF0
volatile unsigned char           COMAF0       @ (0x0285-0X200);
// bit and bitfield definitions
volatile bit SCLPO0              @ ((unsigned)&COMAF0*8)+0;
volatile bit SCLPO1              @ ((unsigned)&COMAF0*8)+1;
volatile bit SDAPO0              @ ((unsigned)&COMAF0*8)+2;
volatile bit SDAPO1              @ ((unsigned)&COMAF0*8)+3;
volatile bit MISOPO              @ ((unsigned)&COMAF0*8)+4;
volatile bit MOSIPO              @ ((unsigned)&COMAF0*8)+5;
volatile bit NSSPO               @ ((unsigned)&COMAF0*8)+6;
volatile bit SCKPO               @ ((unsigned)&COMAF0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCLPO0            : 1;
        unsigned	SCLPO1            : 1;
        unsigned	SDAPO0            : 1;
        unsigned	SDAPO1            : 1;
        unsigned	MISOPO            : 1;
        unsigned	MOSIPO            : 1;
        unsigned	NSSPO             : 1;
        unsigned	SCKPO             : 1;
    };
    struct {
        unsigned	SCLPO             : 2;
        unsigned	SDAPO             : 2;
    };
} COMAF0bits @ (0x0285-0X200);
#endif

// Register: COMAF1
volatile unsigned char           COMAF1       @ (0x0286-0X200);
// bit and bitfield definitions
volatile bit RX0PO0              @ ((unsigned)&COMAF1*8)+0;
volatile bit RX0PO1              @ ((unsigned)&COMAF1*8)+1;
volatile bit RX0PO2              @ ((unsigned)&COMAF1*8)+2;
volatile bit TX0PO0              @ ((unsigned)&COMAF1*8)+3;
volatile bit TX0PO1              @ ((unsigned)&COMAF1*8)+4;
volatile bit TX0PO2              @ ((unsigned)&COMAF1*8)+5;
volatile bit INTPO0              @ ((unsigned)&COMAF1*8)+6;
volatile bit INTPO1              @ ((unsigned)&COMAF1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RX0PO0            : 1;
        unsigned	RX0PO1            : 1;
        unsigned	RX0PO2            : 1;
        unsigned	TX0PO0            : 1;
        unsigned	TX0PO1            : 1;
        unsigned	TX0PO2            : 1;
        unsigned	INTPO0            : 1;
        unsigned	INTPO1            : 1;
    };
    struct {
        unsigned	RX0PO             : 3;
        unsigned	TX0PO             : 3;
        unsigned	INTPO             : 2;
    };
} COMAF1bits @ (0x0286-0X200);
#endif

// Register: COMAF2
volatile unsigned char           COMAF2       @ (0x0287-0X200);
// bit and bitfield definitions
volatile bit RX1PO0              @ ((unsigned)&COMAF2*8)+0;
volatile bit RX1PO1              @ ((unsigned)&COMAF2*8)+1;
volatile bit INTFIXB             @ ((unsigned)&COMAF2*8)+2;
volatile bit TX1PO0              @ ((unsigned)&COMAF2*8)+3;
volatile bit TX1PO1              @ ((unsigned)&COMAF2*8)+4;
volatile bit UR0SW               @ ((unsigned)&COMAF2*8)+6;
volatile bit UR1SW               @ ((unsigned)&COMAF2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RX1PO0            : 1;
        unsigned	RX1PO1            : 1;
        unsigned	INTFIXB           : 1;
        unsigned	TX1PO0            : 1;
        unsigned	TX1PO1            : 1;
        unsigned	                  : 1;
        unsigned	UR0SW             : 1;
        unsigned	UR1SW             : 1;
    };
    struct {
        unsigned	RX1PO             : 2;
        unsigned	                  : 1;
        unsigned	TX1PO             : 2;
    };
} COMAF2bits @ (0x0287-0X200);
#endif

// Register: ANSEL2
volatile unsigned char           ANSEL2       @ (0x028C-0X200);
// bit and bitfield definitions

// Register: ANSEL3
volatile unsigned char           ANSEL3       @ (0x028D-0X200);
// bit and bitfield definitions


// Register: TKCTRIM
volatile unsigned char           TKCTRIM       @ (0x028E-0X200);
// bit and bitfield definitions
volatile bit TKCTRIM0              @ ((unsigned)&TKCTRIM*8)+0;
volatile bit TKCTRIM1              @ ((unsigned)&TKCTRIM*8)+1;
volatile bit TKCTRIM2              @ ((unsigned)&TKCTRIM*8)+2;
volatile bit TKCTRIM3              @ ((unsigned)&TKCTRIM*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TKCTRIM0            : 1;
        unsigned	TKCTRIM1            : 1;
        unsigned	TKCTRIM2            : 1;
        unsigned	TKCTRIM3            : 1;
    };
    struct {
        unsigned	TKCTRIM             : 4;
    };
} TKCTRIMbits @ (0x028E-0X200);
#endif

// Register: WPDA
volatile unsigned char           WPDA       @ (0x0290-0X200);
// bit and bitfield definitions
volatile bit WPDA0              @ ((unsigned)&WPDA*8)+0;
volatile bit WPDA1              @ ((unsigned)&WPDA*8)+1;
volatile bit WPDA2              @ ((unsigned)&WPDA*8)+2;
volatile bit WPDA3              @ ((unsigned)&WPDA*8)+3;
volatile bit WPDA4              @ ((unsigned)&WPDA*8)+4;
volatile bit WPDA5              @ ((unsigned)&WPDA*8)+5;
volatile bit WPDA6              @ ((unsigned)&WPDA*8)+6;
volatile bit WPDA7              @ ((unsigned)&WPDA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDA0            : 1;
        unsigned	WPDA1            : 1;
        unsigned	WPDA2            : 1;
        unsigned	WPDA3            : 1;
        unsigned	WPDA4            : 1;
        unsigned	WPDA5            : 1;
        unsigned	WPDA6            : 1;
        unsigned	WPDA7            : 1;
    };
    struct {
        unsigned	WPDA             : 8;
    };
} WPDAbits @ (0x0290-0X200);
#endif

// Register: WPDB
volatile unsigned char           WPDB       @ (0x0291-0X200);
// bit and bitfield definitions
volatile bit WPDB0              @ ((unsigned)&WPDB*8)+0;
volatile bit WPDB1              @ ((unsigned)&WPDB*8)+1;
volatile bit WPDB2              @ ((unsigned)&WPDB*8)+2;
volatile bit WPDB3              @ ((unsigned)&WPDB*8)+3;
volatile bit WPDB4              @ ((unsigned)&WPDB*8)+4;
volatile bit WPDB5              @ ((unsigned)&WPDB*8)+5;
volatile bit WPDB6              @ ((unsigned)&WPDB*8)+6;
volatile bit WPDB7              @ ((unsigned)&WPDB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDB0            : 1;
        unsigned	WPDB1            : 1;
        unsigned	WPDB2            : 1;
        unsigned	WPDB3            : 1;
        unsigned	WPDB4            : 1;
        unsigned	WPDB5            : 1;
        unsigned	WPDB6            : 1;
        unsigned	WPDB7            : 1;
    };
    struct {
        unsigned	WPDB             : 8;
    };
} WPDBbits @ (0x0291-0X200);
#endif


// Register: WPDC
volatile unsigned char           WPDC       @ (0x0292-0X200);
// bit and bitfield definitions
volatile bit WPDC0              @ ((unsigned)&WPDC*8)+0;
volatile bit WPDC1              @ ((unsigned)&WPDC*8)+1;
volatile bit WPDC2              @ ((unsigned)&WPDC*8)+2;
volatile bit WPDC3              @ ((unsigned)&WPDC*8)+3;
volatile bit WPDC4              @ ((unsigned)&WPDC*8)+4;
volatile bit WPDC5              @ ((unsigned)&WPDC*8)+5;
volatile bit WPDC6              @ ((unsigned)&WPDC*8)+6;
volatile bit WPDC7              @ ((unsigned)&WPDC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDC0            : 1;
        unsigned	WPDC1            : 1;
        unsigned	WPDC2            : 1;
        unsigned	WPDC3            : 1;
        unsigned	WPDC4            : 1;
        unsigned	WPDC5            : 1;
        unsigned	WPDC6            : 1;
        unsigned	WPDC7            : 1;
    };
    struct {
        unsigned	WPDC             : 8;
    };
} WPDCbits @ (0x0292-0X200);
#endif


// Register: WPDD
volatile unsigned char           WPDD       @ (0x0293-0X200);
// bit and bitfield definitions
volatile bit WPDD0              @ ((unsigned)&WPDD*8)+0;
volatile bit WPDD1              @ ((unsigned)&WPDD*8)+1;
volatile bit WPDD2              @ ((unsigned)&WPDD*8)+2;
volatile bit WPDD3              @ ((unsigned)&WPDD*8)+3;
volatile bit WPDD4              @ ((unsigned)&WPDD*8)+4;
volatile bit WPDD5              @ ((unsigned)&WPDD*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDD0            : 1;
        unsigned	WPDD1            : 1;
        unsigned	WPDD2            : 1;
        unsigned	WPDD3            : 1;
        unsigned	WPDD4            : 1;
        unsigned	WPDD5            : 1;
    };
    struct {
        unsigned	WPDD             : 6;
    };
} WPDDbits @ (0x0293-0X200);
#endif


// Register: WPUA
volatile unsigned char           WPUA       @ (0x0294-0X200);
// bit and bitfield definitions
volatile bit WPUA0              @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1              @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2              @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA3              @ ((unsigned)&WPUA*8)+3;
volatile bit WPUA4              @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA5              @ ((unsigned)&WPUA*8)+5;
volatile bit WPUA6              @ ((unsigned)&WPUA*8)+6;
volatile bit WPUA7              @ ((unsigned)&WPUA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA0            : 1;
        unsigned	WPUA1            : 1;
        unsigned	WPUA2            : 1;
        unsigned	WPUA3            : 1;
        unsigned	WPUA4            : 1;
        unsigned	WPUA5            : 1;
        unsigned	WPUA6            : 1;
        unsigned	WPUA7            : 1;
    };
    struct {
        unsigned	WPUA             : 8;
    };
} WPUAbits @ (0x0294-0X200);
#endif

// Register: WPUB
volatile unsigned char           WPUB       @ (0x0295-0X200);
// bit and bitfield definitions
volatile bit WPUB0              @ ((unsigned)&WPUB*8)+0;
volatile bit WPUB1              @ ((unsigned)&WPUB*8)+1;
volatile bit WPUB2              @ ((unsigned)&WPUB*8)+2;
volatile bit WPUB3              @ ((unsigned)&WPUB*8)+3;
volatile bit WPUB4              @ ((unsigned)&WPUB*8)+4;
volatile bit WPUB5              @ ((unsigned)&WPUB*8)+5;
volatile bit WPUB6              @ ((unsigned)&WPUB*8)+6;
volatile bit WPUB7              @ ((unsigned)&WPUB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUB0            : 1;
        unsigned	WPUB1            : 1;
        unsigned	WPUB2            : 1;
        unsigned	WPUB3            : 1;
        unsigned	WPUB4            : 1;
        unsigned	WPUB5            : 1;
        unsigned	WPUB6            : 1;
        unsigned	WPUB7            : 1;
    };
    struct {
        unsigned	WPUB             : 8;
    };
} WPUBbits @ (0x0295-0X200);
#endif


// Register: WPUC
volatile unsigned char           WPUC       @ (0x0296-0X200);
// bit and bitfield definitions
volatile bit WPUC0              @ ((unsigned)&WPUC*8)+0;
volatile bit WPUC1              @ ((unsigned)&WPUC*8)+1;
volatile bit WPUC2              @ ((unsigned)&WPUC*8)+2;
volatile bit WPUC3              @ ((unsigned)&WPUC*8)+3;
volatile bit WPUC4              @ ((unsigned)&WPUC*8)+4;
volatile bit WPUC5              @ ((unsigned)&WPUC*8)+5;
volatile bit WPUC6              @ ((unsigned)&WPUC*8)+6;
volatile bit WPUC7              @ ((unsigned)&WPUC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUC0            : 1;
        unsigned	WPUC1            : 1;
        unsigned	WPUC2            : 1;
        unsigned	WPUC3            : 1;
        unsigned	WPUC4            : 1;
        unsigned	WPUC5            : 1;
        unsigned	WPUC6            : 1;
        unsigned	WPUC7            : 1;
    };
    struct {
        unsigned	WPUC             : 8;
    };
} WPUCbits @ (0x0296-0X200);
#endif


// Register: WPUD
volatile unsigned char           WPUD       @ (0x0297-0X200);
// bit and bitfield definitions
volatile bit WPUD0              @ ((unsigned)&WPUD*8)+0;
volatile bit WPUD1              @ ((unsigned)&WPUD*8)+1;
volatile bit WPUD2              @ ((unsigned)&WPUD*8)+2;
volatile bit WPUD3              @ ((unsigned)&WPUD*8)+3;
volatile bit WPUD4              @ ((unsigned)&WPUD*8)+4;
volatile bit WPUD5              @ ((unsigned)&WPUD*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUD0            : 1;
        unsigned	WPUD1            : 1;
        unsigned	WPUD2            : 1;
        unsigned	WPUD3            : 1;
        unsigned	WPUD4            : 1;
        unsigned	WPUD5            : 1;
    };
    struct {
        unsigned	WPUD             : 6;
    };
} WPUDbits @ (0x0297-0X200);
#endif

// Register: DAC1DAT
volatile unsigned char           DAC1DAT       @ (0x029A-0X200);
// bit and bitfield definitions

// Register: DAC2DAT
volatile unsigned char           DAC2DAT       @ (0x029B-0X200);
// bit and bitfield definitions

// Register: DACCON0
volatile unsigned char           DACCON0       @ (0x029C-0X200);
// bit and bitfield definitions
volatile bit DACVREF0            @ ((unsigned)&DACCON0*8)+0;
volatile bit DACVREF1            @ ((unsigned)&DACCON0*8)+1;
volatile bit DACEN               @ ((unsigned)&DACCON0*8)+2;
volatile bit WNDEN               @ ((unsigned)&DACCON0*8)+3;
volatile bit DEBPR0              @ ((unsigned)&DACCON0*8)+5;
volatile bit DEBPR1              @ ((unsigned)&DACCON0*8)+6;
volatile bit CMDEBS              @ ((unsigned)&DACCON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	DACVREF0          : 1;
        unsigned	DACVREF1          : 1;
        unsigned	DACEN             : 1;
        unsigned	WNDEN             : 1;
        unsigned	                  : 1;
        unsigned	DEBPR0            : 1;
        unsigned	DEBPR1            : 1;
        unsigned	CMDEBS            : 1;
    };
    struct {
        unsigned	DACVREF           : 2;
        unsigned	                  : 3;
        unsigned	DEBPR             : 2;
    };
} DACCON0bits @ (0x029C-0X200);
#endif


// Register: CM0CON0
volatile unsigned char           CM0CON0       @ (0x029D-0X200);
// bit and bitfield definitions
volatile bit CM0NSEL0            @ ((unsigned)&CM0CON0*8)+0;
volatile bit CM0NSEL1            @ ((unsigned)&CM0CON0*8)+1;
volatile bit CM0PSEL0            @ ((unsigned)&CM0CON0*8)+2;
volatile bit CM0PSEL1            @ ((unsigned)&CM0CON0*8)+3;
volatile bit C0OUT               @ ((unsigned)&CM0CON0*8)+4;
volatile bit CM0OE               @ ((unsigned)&CM0CON0*8)+5;
volatile bit CM0POL              @ ((unsigned)&CM0CON0*8)+6;
volatile bit CM0EN               @ ((unsigned)&CM0CON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CM0NSEL0          : 1;
        unsigned	CM0NSEL1          : 1;
        unsigned	CM0PSEL0          : 1;
        unsigned	CM0PSEL1          : 1;
        unsigned	C0OUT             : 1;
        unsigned	CM0OE             : 1;
        unsigned	CM0POL            : 1;
        unsigned	CM0EN             : 1;
    };
    struct {
        unsigned	CM0NSEL           : 2;
        unsigned	CM0PSEL           : 2;
    };
} CM0CON0bits @ (0x029D-0X200);
#endif

// Register: CM1CON0
volatile unsigned char           CM1CON0       @ (0x029E-0X200);
// bit and bitfield definitions
volatile bit CM1NSEL0            @ ((unsigned)&CM1CON0*8)+0;
volatile bit CM1NSEL1            @ ((unsigned)&CM1CON0*8)+1;
volatile bit CM1PSEL0            @ ((unsigned)&CM1CON0*8)+2;
volatile bit CM1PSEL1            @ ((unsigned)&CM1CON0*8)+3;
volatile bit C1OUT               @ ((unsigned)&CM1CON0*8)+4;
volatile bit CM1OE               @ ((unsigned)&CM1CON0*8)+5;
volatile bit CM1POL              @ ((unsigned)&CM1CON0*8)+6;
volatile bit CM1EN               @ ((unsigned)&CM1CON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CM1NSEL0          : 1;
        unsigned	CM1NSEL1          : 1;
        unsigned	CM1PSEL0          : 1;
        unsigned	CM1PSEL1          : 1;
        unsigned	C1OUT             : 1;
        unsigned	CM1OE             : 1;
        unsigned	CM1POL            : 1;
        unsigned	CM1EN             : 1;
    };
    struct {
        unsigned	CM1NSEL           : 2;
        unsigned	CM1PSEL           : 2;
    };
} CM1CON0bits @ (0x029E-0X200);
#endif

// Special function register definitions: Bank 6
//
// AUXPGE = 1£¬

// Register: MSCON1
//volatile unsigned char           MSCON1       @ (0x0301-0X200);
//// bit and bitfield definitions
//volatile bit HIRCM             @ ((unsigned)&MSCON1*8)+0;
//volatile bit AUXPGE            @ ((unsigned)&MSCON1*8)+1;
//volatile bit LVRCKS            @ ((unsigned)&MSCON1*8)+2;
//volatile bit LVRDEB            @ ((unsigned)&MSCON1*8)+3;
//#ifndef _LIB_BUILD
//volatile union {
//    struct {
//        unsigned	HIRCM           : 1;
//        unsigned	AUXPGE          : 1;
//        unsigned	LVRCKS          : 1;
//        unsigned	LVRDEB          : 1;
//    };
//} MSCON1bits @ (0x0301-0X200);
//#endif

// Register: FOSCCALH
volatile unsigned char           FOSCCALH       @ (0x0309-0X200);
// bit and bitfield definitions
volatile bit FOSCCALL8             @ ((unsigned)&FOSCCALH*8)+0;
volatile bit FOSCCALl9             @ ((unsigned)&FOSCCALH*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	FOSCCALL8       : 1;
        unsigned	FOSCCALL9       : 1;
    };
} FOSCCALHbits @ (0x0309-0X200);
#endif
// Special function register definitions: Bank 7
//
// AUXPGE = 1£¬
#endif