
#ifndef _CHIP_DEVICE_H_
#define _CHIP_DEVICE_H_

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
volatile bit RP                  @ ((unsigned)&STATUS*8)+5;

volatile bit C               		 @ ((unsigned)&STATUS*8)+0;
volatile bit HC                  @ ((unsigned)&STATUS*8)+1;
volatile bit Z                	 @ ((unsigned)&STATUS*8)+2;
volatile bit nPF                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTF                 @ ((unsigned)&STATUS*8)+4;
volatile bit PAGE                @ ((unsigned)&STATUS*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CARRY               : 1;
        unsigned	DC                  : 1;
        unsigned	ZERO                : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	RP                  : 1;
    };
    struct {
        unsigned	C                   : 1;
        unsigned	HC                  : 1;
        unsigned	Z                   : 1;
        unsigned	nPF                 : 1;
        unsigned	nTF                 : 1;
        unsigned	PAGE                : 1;
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

volatile bit PA0                 @ ((unsigned)&PORTA*8)+0;
volatile bit PA1                 @ ((unsigned)&PORTA*8)+1;
volatile bit PA2                 @ ((unsigned)&PORTA*8)+2;
volatile bit PA3                 @ ((unsigned)&PORTA*8)+3;
volatile bit PA4                 @ ((unsigned)&PORTA*8)+4;
volatile bit PA5                 @ ((unsigned)&PORTA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RA0                 : 1;
        unsigned	RA1                 : 1;
        unsigned	RA2                 : 1;
        unsigned	RA3                 : 1;
        unsigned	RA4                 : 1;
        unsigned	RA5                 : 1;
    };
	    struct {
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
    };
} PORTAbits @ 0x005;
#endif

// Register: P1DDTL
volatile unsigned char           P1DDTL                 @ 0x008;
// bit and bitfield definitions

// Register: P1DDTH
volatile unsigned char           P1DDTH                 @ 0x009;
// bit and bitfield definitions

// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PCLATH              : 5;
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
volatile bit TMR2IF              @ ((unsigned)&PIR1*8)+1;
volatile bit OSFIF               @ ((unsigned)&PIR1*8)+2;
volatile bit LVDIF               @ ((unsigned)&PIR1*8)+5;
volatile bit CKMIF               @ ((unsigned)&PIR1*8)+6;
volatile bit EEIF                @ ((unsigned)&PIR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	TMR2IF              : 1;
        unsigned	OSFIF               : 1;
        unsigned	                    : 1;
        unsigned	                    : 1;
        unsigned	LVDIF               : 1;
        unsigned	CKMIF               : 1;
        unsigned	EEIF                : 1;
    };
} PIR1bits @ 0x00C;
#endif
// bit and bitfield definitions

// Register: FOSCCAL
volatile unsigned char           FOSCCAL             @ 0x00D;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	FOSCCAL              : 5;
    };
} FOSCCALbits @ 0x00D;
#endif

// Register: P1ADTL
volatile unsigned char           P1ADTL                @ 0x00E;
// bit and bitfield definitions
// Register: P1BDTL
volatile unsigned char           P1BDTL                @ 0x00F;
// bit and bitfield definitions
// Register: P1CDTL
volatile unsigned char           P1CDTL                @ 0x010;
// bit and bitfield definitions

// Register: TMR2L
volatile unsigned char           TMR2L                @ 0x011;
// bit and bitfield definitions

// Register: T2CON0
volatile unsigned char           T2CON0               @ 0x012;
// bit and bitfield definitions
volatile bit T2CKPS0             @ ((unsigned)&T2CON0*8)+0;
volatile bit T2CKPS1             @ ((unsigned)&T2CON0*8)+1;
volatile bit TMR2ON              @ ((unsigned)&T2CON0*8)+2;
volatile bit TOUTPS0             @ ((unsigned)&T2CON0*8)+3;
volatile bit TOUTPS1             @ ((unsigned)&T2CON0*8)+4;
volatile bit TOUTPS2             @ ((unsigned)&T2CON0*8)+5;
volatile bit TOUTPS3             @ ((unsigned)&T2CON0*8)+6;
volatile bit PR2U                @ ((unsigned)&T2CON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKPS              : 2;
        unsigned	TMR2ON              : 1;
        unsigned	TOUTPS              : 4;
        unsigned	PR2U                : 1;
    };
    struct {
        unsigned	T2CKPS0             : 1;
        unsigned	T2CKPS1             : 1;
        unsigned	                    : 1;
        unsigned	TOUTPS0             : 1;
        unsigned	TOUTPS1             : 1;
        unsigned	TOUTPS2             : 1;
        unsigned	TOUTPS3             : 1;
    };
} T2CON0bits @ 0x012;
#endif

// Register: TMR2H
volatile unsigned char           TMR2H                @ 0x013;
// bit and bitfield definitions

// Register: P1ADTH
volatile unsigned char           P1ADTH               @ 0x014;
// bit and bitfield definitions

// Register: P1BDTH
volatile unsigned char           P1BDTH               @ 0x015;
// bit and bitfield definitions

// Register: P1CON
volatile unsigned char           P1CON                @ 0x016;
// bit and bitfield definitions
volatile bit P1DC0                @ ((unsigned)&P1CON*8)+0;
volatile bit P1DC1                @ ((unsigned)&P1CON*8)+1;
volatile bit P1DC2                @ ((unsigned)&P1CON*8)+2;
volatile bit P1DC3                @ ((unsigned)&P1CON*8)+3;
volatile bit P1DC4                @ ((unsigned)&P1CON*8)+4;
volatile bit P1DC5             		@ ((unsigned)&P1CON*8)+5;
volatile bit P1DC6             	  @ ((unsigned)&P1CON*8)+6;
volatile bit P1AUE                @ ((unsigned)&P1CON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DC              : 7;
        unsigned	P1AUE             : 1;
    };
    struct {
        unsigned	P1DC0             : 1;
        unsigned	P1DC1             : 1;
        unsigned	P1DC2             : 1;
        unsigned	P1DC3             : 1;
        unsigned	P1DC4             : 1;
        unsigned	P1DC5             : 1;
        unsigned	P1DC6             : 1;
    };
} P1CONbits @ 0x016;
#endif

// Register: P1BR0
volatile unsigned char           P1BR0              @ 0x017;
// bit and bitfield definitions
volatile bit P1ASS0              @ ((unsigned)&P1BR0*8)+0;
volatile bit P1ASS1              @ ((unsigned)&P1BR0*8)+1;
volatile bit P1BSS0              @ ((unsigned)&P1BR0*8)+2;
volatile bit P1BSS1              @ ((unsigned)&P1BR0*8)+3;
volatile bit P1BKS0              @ ((unsigned)&P1BR0*8)+4;
volatile bit P1BKS1              @ ((unsigned)&P1BR0*8)+5;
volatile bit P1BKS2              @ ((unsigned)&P1BR0*8)+6;
volatile bit P1BEVT              @ ((unsigned)&P1BR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1ASS               : 2;
        unsigned	P1BSS               : 2;
        unsigned	P1BKS               : 3;
    };
    struct {
        unsigned	P1ASS0              : 1;
        unsigned	P1ASS1              : 1;
        unsigned	P1BSS0              : 1;
        unsigned	P1BSS1              : 1;
        unsigned	P1BKS0              : 1;
        unsigned	P1BKS1              : 1;
        unsigned	P1BKS2              : 1;
        unsigned	P1BEVT              : 1;
    };
} P1BR0bits @ 0x017;
#endif

// Register: WDTCON
volatile unsigned char           WDTCON              @ 0x018;
// bit and bitfield definitions
volatile bit SWDTEN              @ ((unsigned)&WDTCON*8)+0;
volatile bit WDTPS0              @ ((unsigned)&WDTCON*8)+1;
volatile bit WDTPS1              @ ((unsigned)&WDTCON*8)+2;
volatile bit WDTPS2              @ ((unsigned)&WDTCON*8)+3;
volatile bit WDTPS3              @ ((unsigned)&WDTCON*8)+4;
volatile bit WCKSRC              @ ((unsigned)&WDTCON*8)+5;
volatile bit LVDP                @ ((unsigned)&WDTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SWDTEN              : 1;
        unsigned	WDTPS               : 4;
        unsigned	WCKSRC              : 1;
        unsigned	                    : 1;
        unsigned	LVDP                : 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	WDTPS0              : 1;
        unsigned	WDTPS1              : 1;
        unsigned	WDTPS2              : 1;
        unsigned	WDTPS3              : 1;
    };
} WDTCONbits @ 0x018;
#endif

// Register: P1BR1
volatile unsigned char           P1BR1              @ 0x019;
// bit and bitfield definitions
volatile bit P1CSS0              @ ((unsigned)&P1BR1*8)+0;
volatile bit P1CSS1              @ ((unsigned)&P1BR1*8)+1;
volatile bit P1DALT              @ ((unsigned)&P1BR1*8)+2;
volatile bit P1CALT              @ ((unsigned)&P1BR1*8)+3;
volatile bit P1D2SS0             @ ((unsigned)&P1BR1*8)+4;
volatile bit P1D2SS1             @ ((unsigned)&P1BR1*8)+5;
volatile bit P1DSS0              @ ((unsigned)&P1BR1*8)+6;
volatile bit P1DSS1              @ ((unsigned)&P1BR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1CSS               : 2;
        unsigned	                    : 2;
        unsigned	P1D2SS              : 2;
        unsigned	P1DSS               : 2;
    };
    struct {
        unsigned	P1CSS0              : 1;
        unsigned	P1CSS1              : 1;
        unsigned	P1DALT              : 1;
        unsigned	P1CALT              : 1;
        unsigned	P1D2SS0             : 1;
        unsigned	P1D2SS1             : 1;
        unsigned	P1DSS0              : 1;
        unsigned	P1DSS1              : 1;
    };
} P1BR1bits @ 0x019;
#endif

// Register: P1BR1
volatile unsigned char           P1CDTH              @ 0x01A;
// bit and bitfield definitions

// Register: MSCON
volatile unsigned char           MSCON         @ 0x01B;
// bit and bitfield definitions
volatile bit T2CKRUN                  @ ((unsigned)&MSCON*8)+0;
volatile bit CKCNTI                   @ ((unsigned)&MSCON*8)+1;
volatile bit CKMAVG                   @ ((unsigned)&MSCON*8)+2;
volatile bit SLVREN                   @ ((unsigned)&MSCON*8)+3;
volatile bit LVROE                    @ ((unsigned)&MSCON*8)+6;
volatile bit BGRBOE                   @ ((unsigned)&MSCON*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CKRUN              : 1;
        unsigned	CKCNTI               : 1;
        unsigned	CKMAVG               : 1;
        unsigned	SLVREN						   : 1;
        unsigned	                     : 2;
        unsigned	LVROE                : 1;
        unsigned	BGRBOE						   : 1;
    };
} MSCONbits @ 0x01B;
#endif

// Register: SOSCPRL
volatile unsigned char           SOSCPRL             @ 0x01C;
// bit and bitfield definitions

// Register: SOSCPRH
volatile unsigned char           SOSCPRH              @ 0x01D;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SOSCPRH              : 4;
    };
} SOSCPRHbits @ 0x01D;
#endif

// Register: P1AUX
volatile unsigned char           P1AUX         @ 0x01E;
// bit and bitfield definitions
volatile bit P1DF2                    @ ((unsigned)&P1AUX*8)+0;
volatile bit P1DF2E                   @ ((unsigned)&P1AUX*8)+1;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1DF2                : 1;
        unsigned	P1DF2E               : 1;
    };
} P1AUXbits @ 0x01E;
#endif

// Register: T0CON0
volatile unsigned char           T0CON0         @ 0x01F;
// bit and bitfield definitions
volatile bit T0CKSRC0                    @ ((unsigned)&T0CON0*8)+0;
volatile bit T0CKSRC1                    @ ((unsigned)&T0CON0*8)+1;
volatile bit T0CKRUN                     @ ((unsigned)&T0CON0*8)+2;
volatile bit T0ON                        @ ((unsigned)&T0CON0*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T0CKSRC0               : 1;
        unsigned	T0CKSRC1               : 1;
        unsigned	T0CKRUN                : 1;
        unsigned	T0ON                   : 1;
    };
    struct {
        unsigned	T0CKSRC                : 2;
    };
} T0CON0bits @ 0x01F;
#endif
//
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
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISA0              : 1;
        unsigned	TRISA1              : 1;
        unsigned	TRISA2              : 1;
        unsigned	TRISA3              : 1;
        unsigned	TRISA4              : 1;
        unsigned	TRISA5              : 1;
    };
    struct {
        unsigned	TRISA               : 6;
    };
} TRISAbits @ 0x085;
#endif


// Register: PSRCA
volatile unsigned char           PSRCA          @ 0x088;
// bit and bitfield definitions
volatile bit PSRCA40                 @ ((unsigned)&PSRCA*8)+0;
volatile bit PSRCA41                 @ ((unsigned)&PSRCA*8)+1;
volatile bit PSRCA50                 @ ((unsigned)&PSRCA*8)+2;
volatile bit PSRCA51                 @ ((unsigned)&PSRCA*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCA4               : 2;
        unsigned	PSRCA5               : 2;
    };
    struct {
        unsigned	PSRCA40                 : 1;
        unsigned	PSRCA41                 : 1;
        unsigned	PSRCA50                 : 1;
        unsigned	PSRCA51                 : 1;
    };
} PSRCAbits @ 0x088;
#endif

// Register: PIE1
volatile unsigned char           PIE1                @ 0x08C;
// bit and bitfield definitions
volatile bit TMR2IE              @ ((unsigned)&PIE1*8)+1;
volatile bit OSFIE               @ ((unsigned)&PIE1*8)+2;
volatile bit LVDIE               @ ((unsigned)&PIE1*8)+5;
volatile bit CKMIE               @ ((unsigned)&PIE1*8)+6;
volatile bit EEIE                @ ((unsigned)&PIE1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	TMR2IE              : 1;
        unsigned	OSFIE               : 1;
        unsigned	                    : 2;
        unsigned	LVDIE               : 1;
        unsigned	CKMEAIE             : 1;
        unsigned	EEIE                : 1;
    };
} PIE1bits @ 0x08C;
#endif

// Register: LVDCON
volatile unsigned char           LVDCON                @ 0x08D;
// bit and bitfield definitions
volatile bit LVDM0               @ ((unsigned)&LVDCON*8)+0;
volatile bit LVDM1               @ ((unsigned)&LVDCON*8)+1;
volatile bit LVDDEB              @ ((unsigned)&LVDCON*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVDM0              : 1;
        unsigned	LVDM1              : 1;
        unsigned	LVDDEB             : 1;
    };
    struct {
        unsigned	LVDM               : 2;
    };
} LVDCONbits @ 0x08D;
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
        unsigned	LVDL0               : 1;
        unsigned	LVDL1               : 1;
        unsigned	LVDL2               : 1;
        unsigned	LVDL3               : 1;
    };
    struct {
        unsigned	                		: 4;
        unsigned	LVDL                : 4;
    };
} PCONbits @ 0x08E;
#endif

// Register: OSCCON
volatile unsigned char           OSCCON              @ 0x08F;
// bit and bitfield definitions
volatile bit LTS                    @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                    @ ((unsigned)&OSCCON*8)+2;
volatile bit IRCF0                  @ ((unsigned)&OSCCON*8)+4;
volatile bit IRCF1                  @ ((unsigned)&OSCCON*8)+5;
volatile bit IRCF2                  @ ((unsigned)&OSCCON*8)+6;
volatile bit LFMOD                  @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                       : 1;
        unsigned	LTS                    : 1;
        unsigned	HTS                    : 1;
        unsigned	                       : 1;
        unsigned	IRCF0                  : 1;
        unsigned	IRCF1                  : 1;
        unsigned	IRCF2                  : 1;
        unsigned	LFMOD                  : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	IRCF                : 3;
    };
} OSCCONbits @ 0x08F;
#endif

// Register: P1OE
volatile unsigned char           P1OE              @ 0x090;
// bit and bitfield definitions
volatile bit P1A0OE                   @ ((unsigned)&P1OE*8)+0;
volatile bit P1A0NOE                  @ ((unsigned)&P1OE*8)+1;
volatile bit P1C2SS0                  @ ((unsigned)&P1OE*8)+2;
volatile bit P1C2SS1                  @ ((unsigned)&P1OE*8)+3;
volatile bit P1DOE                    @ ((unsigned)&P1OE*8)+5;
volatile bit P1BOE                    @ ((unsigned)&P1OE*8)+6;
volatile bit P1COE                    @ ((unsigned)&P1OE*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0OE                 : 1;
        unsigned	P1A0NOE                : 1;
        unsigned	P1C2SS0                : 1;
        unsigned	P1C2SS1                : 1;
        unsigned	                       : 1;
        unsigned	P1DOE                  : 1;
        unsigned	P1BOE                  : 1;
        unsigned	P1COE                  : 1;
    };
    struct {
        unsigned	                       : 2;
        unsigned	P1C2SS                 : 2;
    };
} P1OEbits @ 0x090;
#endif

// Register: PR2L
volatile unsigned char           PR2L                @ 0x091;
// bit and bitfield definitions

// Register: PR2H
volatile unsigned char           PR2H                @ 0x092;
// bit and bitfield definitions

// Register: WPUA
volatile unsigned char           WPUA                @ 0x095;
volatile unsigned char           WPU                 @ 0x095;
// bit and bitfield definitions
volatile bit WPUA0               @ ((unsigned)&WPUA*8)+0;
volatile bit WPUA1               @ ((unsigned)&WPUA*8)+1;
volatile bit WPUA2               @ ((unsigned)&WPUA*8)+2;
volatile bit WPUA3               @ ((unsigned)&WPUA*8)+3;
volatile bit WPUA4               @ ((unsigned)&WPUA*8)+4;
volatile bit WPUA5               @ ((unsigned)&WPUA*8)+5;

volatile bit WPU0                @ ((unsigned)&WPUA*8)+0;
volatile bit WPU1                @ ((unsigned)&WPUA*8)+1;
volatile bit WPU2                @ ((unsigned)&WPUA*8)+2;
volatile bit WPU3                @ ((unsigned)&WPUA*8)+3;
volatile bit WPU4                @ ((unsigned)&WPUA*8)+4;
volatile bit WPU5                @ ((unsigned)&WPUA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUA0               : 1;
        unsigned	WPUA1               : 1;
        unsigned	WPUA2               : 1;
        unsigned	WPUA3               : 1;
        unsigned	WPUA4               : 1;
        unsigned	WPUA5               : 1;
    };
    struct {
        unsigned	WPU0                : 1;
        unsigned	WPU1                : 1;
        unsigned	WPU2                : 1;
        unsigned	WPU3                : 1;
        unsigned	WPU4                : 1;
        unsigned	WPU5                : 1;
    };
    struct {
        unsigned	WPUA                : 6;
    };
    struct {
        unsigned	WPU                 : 6;
    };
} WPUAbits @ 0x095;
#endif

// Register: IOCA
volatile unsigned char           IOCA                @ 0x096;
volatile unsigned char           IOC                 @ 0x096;
// bit and bitfield definitions
volatile bit IOCA0               @ ((unsigned)&IOCA*8)+0;
volatile bit IOCA1               @ ((unsigned)&IOCA*8)+1;
volatile bit IOCA2               @ ((unsigned)&IOCA*8)+2;
volatile bit IOCA3               @ ((unsigned)&IOCA*8)+3;
volatile bit IOCA4               @ ((unsigned)&IOCA*8)+4;
volatile bit IOCA5               @ ((unsigned)&IOCA*8)+5;

volatile bit IOC0                @ ((unsigned)&IOCA*8)+0;
volatile bit IOC1                @ ((unsigned)&IOCA*8)+1;
volatile bit IOC2                @ ((unsigned)&IOCA*8)+2;
volatile bit IOC3                @ ((unsigned)&IOCA*8)+3;
volatile bit IOC4                @ ((unsigned)&IOCA*8)+4;
volatile bit IOC5                @ ((unsigned)&IOCA*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	IOCA0               : 1;
        unsigned	IOCA1               : 1;
        unsigned	IOCA2               : 1;
        unsigned	IOCA3               : 1;
        unsigned	IOCA4               : 1;
        unsigned	IOCA5               : 1;
    };
    struct {
        unsigned	IOC0                : 1;
        unsigned	IOC1                : 1;
        unsigned	IOC2                : 1;
        unsigned	IOC3                : 1;
        unsigned	IOC4                : 1;
        unsigned	IOC5                : 1;
    };
    struct {
        unsigned	IOCA                : 6;
    };
    struct {
        unsigned	IOC                 : 6;
    };
} IOCAbits @ 0x096;
#endif

// Register: PSINKA
volatile unsigned char           PSINKA              @ 0x097;
// bit and bitfield definitions
volatile bit PSINKA0                @ ((unsigned)&PSINKA*8)+0;
volatile bit PSINKA1                @ ((unsigned)&PSINKA*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSINKA0             : 1;
        unsigned	PSINKA1             : 1;
    };
    struct {
        unsigned	PSINKA              : 2;
    };
} PSINKAbits @ 0x097;
#endif

// Register: SCKCFG
volatile unsigned char           SCKCFG              @ 0x098;
// bit and bitfield definitions
volatile bit SCKOE                @ ((unsigned)&SCKCFG*8)+1;
volatile bit SCKEN                @ ((unsigned)&SCKCFG*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	SCKOE               : 1;
        unsigned	                    : 5;
        unsigned	SCKEN               : 1;
    };
} SCKCFGbits @ 0x098;
#endif

// Register: P1POL
volatile unsigned char           P1POL              @ 0x099;
// bit and bitfield definitions
volatile bit P1A0P                    @ ((unsigned)&P1POL*8)+0;
volatile bit P1A0NP                   @ ((unsigned)&P1POL*8)+1;
volatile bit P1DP                     @ ((unsigned)&P1POL*8)+5;
volatile bit P1BP                     @ ((unsigned)&P1POL*8)+6;
volatile bit P1CP                     @ ((unsigned)&P1POL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	P1A0P               : 1;
        unsigned	P1A0NP              : 1;
        unsigned	                    : 3;
        unsigned	P1DP                : 1;
        unsigned	P1BP                : 1;
        unsigned	P1CP                : 1;
    };
} P1POLbits @ 0x099;
#endif

// Register: EEDAT
volatile unsigned char           EEDAT               @ 0x09A;
volatile unsigned char           EEDATA              @ 0x09A;
// bit and bitfield definitions

// Register: EEADR
volatile unsigned char           EEADR               @ 0x09B;
// bit and bitfield definitions

// Register: EECON1
volatile unsigned char           EECON1              @ 0x09C;
// bit and bitfield definitions
volatile bit RD                  @ ((unsigned)&EECON1*8)+0;
volatile bit WREN1               @ ((unsigned)&EECON1*8)+2;
volatile bit WRERR               @ ((unsigned)&EECON1*8)+3;
volatile bit WREN2               @ ((unsigned)&EECON1*8)+4;
volatile bit WREN3               @ ((unsigned)&EECON1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	                    : 1;
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
} EECON2bits @ 0x09d;
#endif


// Register: T2CON1
volatile unsigned char           T2CON1             @ 0x09E;
// bit and bitfield definitions
volatile bit T2CKSRC0            @ ((unsigned)&T2CON1*8)+0;
volatile bit T2CKSRC1            @ ((unsigned)&T2CON1*8)+1;
volatile bit T2CKSRC2            @ ((unsigned)&T2CON1*8)+2;
volatile bit P1BZM               @ ((unsigned)&T2CON1*8)+3;
volatile bit P1OS                @ ((unsigned)&T2CON1*8)+4;
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
} T2CON1bits @ 0x09E;
#endif
//--------------------------------------------------------------------------by yangxu
volatile unsigned char           SFR00             @0x000;
volatile unsigned char           SFR01             @0x001;
volatile unsigned char           SFR02             @0x002;
volatile unsigned char           SFR03             @0x003;
volatile unsigned char           SFR04             @0x004;
volatile unsigned char           SFR05             @0x005;
volatile unsigned char           SFR06             @0x006;
volatile unsigned char           SFR07             @0x007;
volatile unsigned char           SFR08             @0x008;
volatile unsigned char           SFR09             @0x009;
volatile unsigned char           SFR0A             @0x00A;
volatile unsigned char           SFR0B             @0x00B;
volatile unsigned char           SFR0C             @0x00C;
volatile unsigned char           SFR0D             @0x00D;
volatile unsigned char           SFR0E             @0x00E;
volatile unsigned char           SFR0F             @0x00F;

volatile unsigned char           SFR10             @0x010;
volatile unsigned char           SFR11             @0x011;
volatile unsigned char           SFR12             @0x012;
volatile unsigned char           SFR13             @0x013;
volatile unsigned char           SFR14             @0x014;
volatile unsigned char           SFR15             @0x015;
volatile unsigned char           SFR16             @0x016;
volatile unsigned char           SFR17             @0x017;
volatile unsigned char           SFR18             @0x018;
volatile unsigned char           SFR19             @0x019;
volatile unsigned char           SFR1A             @0x01A;
volatile unsigned char           SFR1B             @0x01B;
volatile unsigned char           SFR1C             @0x01C;
volatile unsigned char           SFR1D             @0x01D;
volatile unsigned char           SFR1E             @0x01E;
volatile unsigned char           SFR1F             @0x01F;


volatile unsigned char           SFR80             @0x080;
volatile unsigned char           SFR81             @0x081;
volatile unsigned char           SFR82             @0x082;
volatile unsigned char           SFR83             @0x083;
volatile unsigned char           SFR84             @0x084;
volatile unsigned char           SFR85             @0x085;
volatile unsigned char           SFR86             @0x086;
volatile unsigned char           SFR87             @0x087;
volatile unsigned char           SFR88             @0x088;
volatile unsigned char           SFR89             @0x089;
volatile unsigned char           SFR8A             @0x08A;
volatile unsigned char           SFR8B             @0x08B;
volatile unsigned char           SFR8C             @0x08C;
volatile unsigned char           SFR8D             @0x08D;
volatile unsigned char           SFR8E             @0x08E;
volatile unsigned char           SFR8F             @0x08F;

volatile unsigned char           SFR90             @0x090;
volatile unsigned char           SFR91             @0x091;
volatile unsigned char           SFR92             @0x092;
volatile unsigned char           SFR93             @0x093;
volatile unsigned char           SFR94             @0x094;
volatile unsigned char           SFR95             @0x095;
volatile unsigned char           SFR96             @0x096;
volatile unsigned char           SFR97             @0x097;
volatile unsigned char           SFR98             @0x098;
volatile unsigned char           SFR99             @0x099;
volatile unsigned char           SFR9A             @0x09A;
volatile unsigned char           SFR9B             @0x09B;
volatile unsigned char           SFR9C             @0x09C;
volatile unsigned char           SFR9D             @0x09D;
volatile unsigned char           SFR9E             @0x09E;
volatile unsigned char           SFR9F             @0x09F;
//---------------------------------------------------------------------------
#endif
