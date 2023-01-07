
#ifndef _CHIP_DEVICE_H_
#define _CHIP_DEVICE_H_
//
// Special function register definitions
//


// Register: INDF0
volatile unsigned char           INDF0               @ 0x000;
// bit and bitfield definitions

// Register: INDF1
volatile unsigned char           INDF1               @ 0x001;
// bit and bitfield definitions

// Register: PCL
volatile unsigned char           PCL                 @ 0x002;
// bit and bitfield definitions

// Register: STATUS
volatile unsigned char           STATUS              @ 0x003;
// bit and bitfield definitions
volatile bit C                   @ ((unsigned)&STATUS*8)+0;
volatile bit DC                  @ ((unsigned)&STATUS*8)+1;
volatile bit Z                   @ ((unsigned)&STATUS*8)+2;
volatile bit nPD                 @ ((unsigned)&STATUS*8)+3;
volatile bit nTO                 @ ((unsigned)&STATUS*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	C                   : 1;
        unsigned	DC                  : 1;
        unsigned	Z                   : 1;
        unsigned	nPD                 : 1;
        unsigned	nTO                 : 1;
        unsigned	                    : 2;
        unsigned	: 1;
    };
} STATUSbits @ 0x003;
#endif
// bit and bitfield definitions

// Register: FSR0L
volatile unsigned char           FSR0L               @ 0x004;
// bit and bitfield definitions

// Register: FSR0H
volatile unsigned char           FSR0H               @ 0x005;
// bit and bitfield definitions

// Register: FSR1L
volatile unsigned char           FSR1L               @ 0x006;
// bit and bitfield definitions

// Register: FSR1H
volatile unsigned char           FSR1H               @ 0x007;
// bit and bitfield definitions

// Register: BSR
volatile unsigned char           BSREG                 @ 0x008;
// bit and bitfield definitions
volatile bit BSREG0                @ ((unsigned)&BSREG*8)+0;
volatile bit BSREG1                @ ((unsigned)&BSREG*8)+1;
volatile bit BSREG2                @ ((unsigned)&BSREG*8)+2;
volatile bit BSREG3                @ ((unsigned)&BSREG*8)+3;
volatile bit BSREG4                @ ((unsigned)&BSREG*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	BSREG0                : 1;
        unsigned	BSREG1                : 1;
        unsigned	BSREG2                : 1;
        unsigned	BSREG3                : 1;
        unsigned	BSREG4                : 1;
    };
    struct {
        unsigned	BSREG                 : 5;
    };
} BSREGbits @ 0x008;
#endif

// Register: WREG
volatile unsigned char           WREG                @ 0x009;
// bit and bitfield definitions

// Register: PCLATH
volatile unsigned char           PCLATH              @ 0x00A;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PCLATH              : 7;
    };
} PCLATHbits @ 0x00A;
#endif

// Register: INTCON
volatile unsigned char           INTCON              @ 0x00B;
// bit and bitfield definitions
volatile bit OSFIF               @ ((unsigned)&INTCON*8)+0;
volatile bit LVDIF               @ ((unsigned)&INTCON*8)+1;
volatile bit EEIF                @ ((unsigned)&INTCON*8)+2;
volatile bit OSFIE               @ ((unsigned)&INTCON*8)+3;
volatile bit LVDIE               @ ((unsigned)&INTCON*8)+4;
volatile bit EEIE                @ ((unsigned)&INTCON*8)+5;
volatile bit PEIE                @ ((unsigned)&INTCON*8)+6;
volatile bit GIE                 @ ((unsigned)&INTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OSFIF               : 1;
        unsigned	LVDIF               : 1;
        unsigned	EEIF                : 1;
        unsigned	OSFIE               : 1;
        unsigned	LVDIE               : 1;
        unsigned	EEIE                : 1;
        unsigned	PEIE                : 1;
        unsigned	GIE                 : 1;
    };
} INTCONbits @ 0x00B;
#endif

// Register: PORTA
volatile unsigned char           PORTA               @ 0x00C;
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
        unsigned	PA0                 : 1;
        unsigned	PA1                 : 1;
        unsigned	PA2                 : 1;
        unsigned	PA3                 : 1;
        unsigned	PA4                 : 1;
        unsigned	PA5                 : 1;
        unsigned	PA6                 : 1;
        unsigned	PA7                 : 1;
    };
} PORTAbits @ 0x00C;
#endif

// Register: PORTB
volatile unsigned char           PORTB               @ 0x00D;
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
        unsigned	PB0                 : 1;
        unsigned	PB1                 : 1;
        unsigned	PB2                 : 1;
        unsigned	PB3                 : 1;
        unsigned	PB4                 : 1;
        unsigned	PB5                 : 1;
        unsigned	PB6                 : 1;
        unsigned	PB7                 : 1;
    };
} PORTBbits @ 0x00D;
#endif

// Register: PORTC
volatile unsigned char           PORTC               @ 0x00E;
// bit and bitfield definitions
volatile bit RC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit RC1                 @ ((unsigned)&PORTC*8)+1;

volatile bit PC0                 @ ((unsigned)&PORTC*8)+0;
volatile bit PC1                 @ ((unsigned)&PORTC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RC0                 : 1;
        unsigned	RC1                 : 1;
    };
    struct {
        unsigned	PC0                 : 1;
        unsigned	PC1                 : 1;
    };
} PORTCbits @ 0x00E;
#endif

// Register: PIR1
volatile unsigned char           PIR1                  @ 0x011;
// bit and bitfield definitions
volatile bit ADCIF               @ ((unsigned)&PIR1*8)+0;
volatile bit CKMIF               @ ((unsigned)&PIR1*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIF               : 1;
        unsigned	CKMIF               : 1;
    };
} PIR1bits @ 0x011;
#endif


// Register: EPIF0
volatile unsigned char           EPIF0               @ 0x014;
// bit and bitfield definitions

// Register: SPIDATA
volatile unsigned char           SPIDATA             @ 0x015;
// bit and bitfield definitions
// bit and bitfield definitions

// Register: SPICTRL
volatile unsigned char           SPICTRL             @ 0x016;
// bit and bitfield definitions
volatile bit SPIEN               @ ((unsigned)&SPICTRL*8)+0;
volatile bit TXBMT               @ ((unsigned)&SPICTRL*8)+1;
volatile bit NSSM0               @ ((unsigned)&SPICTRL*8)+2;
volatile bit NSSM1               @ ((unsigned)&SPICTRL*8)+3;
volatile bit RXOVRN              @ ((unsigned)&SPICTRL*8)+4;
volatile bit MFAULT              @ ((unsigned)&SPICTRL*8)+5;
volatile bit WCOL                @ ((unsigned)&SPICTRL*8)+6;
volatile bit SPIF                @ ((unsigned)&SPICTRL*8)+7 ;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SPIEN               : 1;
        unsigned	TXBMT               : 1;
        unsigned	NSSM0               : 1;
        unsigned	NSSM1               : 1;
        unsigned	RXOVRN              : 1;
        unsigned	MFAULT              : 1;
        unsigned	WCOL                : 1;
        unsigned	SPIF                : 1;
    };
    struct {
        unsigned	                    : 2;
        unsigned	NSSM                : 2;
        unsigned	                    : 4;
    };
} SPICTRLbits @ 0x016;
#endif


// Register: SPICFG
volatile unsigned char           SPICFG             @ 0x017;
// bit and bitfield definitions
volatile bit RXBMT               @ ((unsigned)&SPICFG*8)+0;
volatile bit SRMT                @ ((unsigned)&SPICFG*8)+1;
volatile bit NSSVAL              @ ((unsigned)&SPICFG*8)+2;
volatile bit SLAS                @ ((unsigned)&SPICFG*8)+3;
volatile bit CPOL                @ ((unsigned)&SPICFG*8)+4;
volatile bit CPHA                @ ((unsigned)&SPICFG*8)+5;
volatile bit MSITEN              @ ((unsigned)&SPICFG*8)+6;
volatile bit RZMEN               @ ((unsigned)&SPICFG*8)+7 ;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RXBMT               : 1;
        unsigned	SRMT                : 1;
        unsigned	NSSVAL              : 1;
        unsigned	SLAS                : 1;
        unsigned	CPOL                : 1;
        unsigned	CPHA                : 1;
        unsigned	MSITEN              : 1;
        unsigned	RZMEN               : 1;
    };
} SPICFGbits @ 0x017;
#endif
// Register: SPISCR
volatile unsigned char           SPISCR               @ 0x018;
// bit and bitfield definitions

// Register: SPICRCPOL
volatile unsigned int            SPICRCPOL            @ 0x019;

// Register: SPIRXCRC
volatile unsigned char           SPIRXCRC             @ 0x01A;
// bit and bitfield definitions
// Register: SPIRXCRC
volatile unsigned char           SPITXCRC             @ 0x01B;
// bit and bitfield definitions

// Register: SPIIER
volatile unsigned char           SPIIER               @ 0x01C;
// bit and bitfield definitions
volatile bit TXE                 @ ((unsigned)&SPIIER*8)+0;
volatile bit RXNE                @ ((unsigned)&SPIIER*8)+1;
volatile bit RXERR               @ ((unsigned)&SPIIER*8)+2;
volatile bit WAKUP               @ ((unsigned)&SPIIER*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TXE                 : 1;
        unsigned	RXNE                : 1;
        unsigned	RXERR               : 1;
        unsigned	WAKUP               : 1;
    };
} SPIIERbits @ 0x01C;
#endif 

// Register: SPICTRL2
volatile unsigned char           SPICTRL2               @ 0x01D;
// bit and bitfield definitions
volatile bit LSBFIRST            @ ((unsigned)&SPICTRL2*8)+0;
volatile bit CRCEN               @ ((unsigned)&SPICTRL2*8)+1;
volatile bit CRCNXT              @ ((unsigned)&SPICTRL2*8)+2;
volatile bit SSM                 @ ((unsigned)&SPICTRL2*8)+3;
volatile bit SSI                 @ ((unsigned)&SPICTRL2*8)+4;
volatile bit RXONLY              @ ((unsigned)&SPICTRL2*8)+5;
volatile bit BDOE                @ ((unsigned)&SPICTRL2*8)+6;
volatile bit BDM                 @ ((unsigned)&SPICTRL2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LSBFIRST            : 1;
        unsigned	CRCEN               : 1;
        unsigned	CRCNXT              : 1;
        unsigned	SSM                 : 1;
        unsigned	SSI                 : 1;
        unsigned	RXONLY              : 1;
        unsigned	BDOE                : 1;
        unsigned	BDM                 : 1;
    };
} SPICTRL2bits @ 0x01D;
#endif

// Register: SPISTAT
volatile unsigned char           SPISTAT             @ 0x01E;
// bit and bitfield definitions
volatile bit CRCERR                 @ ((unsigned)&SPISTAT*8)+0;
volatile bit WKF                    @ ((unsigned)&SPISTAT*8)+1;
volatile bit STXBMT                 @ ((unsigned)&SPISTAT*8)+2;
volatile bit SRXBMT                 @ ((unsigned)&SPISTAT*8)+3;
volatile bit SBUSY                  @ ((unsigned)&SPISTAT*8)+4;
volatile bit SRXOVRN                @ ((unsigned)&SPISTAT*8)+5;
volatile bit SMODF                  @ ((unsigned)&SPISTAT*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CRCERR              : 1;
        unsigned	WKF                 : 1;
        unsigned	STXBMT              : 1;
        unsigned	SRXBMT              : 1;
        unsigned	SBUSY               : 1;
        unsigned	SRXOVRN             : 1;
        unsigned	SMODF               : 1;
    };
} SPISTATbits @ 0x01E;
#endif

// Register: ADDLY
volatile unsigned char           ADDLY             @ 0x01F;
// bit and bitfield definitions
//
// Special function register definitions: Bank 1
//

//--------------------------------------------------------------------------------------
// Register: TRISA
// PORTA Data Direction Control Register
volatile unsigned char           TRISA               @ 0x08C;
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
} TRISAbits @ 0x08C;
#endif

// Register: TRISB
// PORTB Data Direction Control Register
volatile unsigned char           TRISB               @ 0x08D;
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
        unsigned	TRISB0              : 1;
        unsigned	TRISB1              : 1;
        unsigned	TRISB2              : 1;
        unsigned	TRISB3              : 1;
        unsigned	TRISB4              : 1;
        unsigned	TRISB5              : 1;
        unsigned	TRISB6              : 1;
        unsigned	TRISB7              : 1;
    };
} TRISBbits @ 0x08D;
#endif

// Register: TRISC
// PORTC Data Direction Control Register
volatile unsigned char           TRISC               @ 0x08E;
// bit and bitfield definitions
volatile bit TRISC0              @ ((unsigned)&TRISC*8)+0;
volatile bit TRISC1              @ ((unsigned)&TRISC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TRISC0              : 1;
        unsigned	TRISC1              : 1;
    };
} TRISCbits @ 0x08E;
#endif


// Register: PIE1
// Peripheral LVDIErrupt Enable Register 1
volatile unsigned char           PIE1                @ 0x091;
// bit and bitfield definitions
volatile bit ADCIE              @ ((unsigned)&PIE1*8)+0;
volatile bit CKMIE              @ ((unsigned)&PIE1*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCIE              : 1;
        unsigned	CKMIE              : 1;
    };
} PIE1bits @ 0x091;
#endif



// Register: EPIE0
// Peripheral LVDIErrupt Enable Register 3
volatile unsigned char           EPIE0                @ 0x094;
// bit and bitfield definitions

// Register: CKOCON
// Option Register
volatile unsigned char           CKOCON          @ 0x095;
// bit and bitfield definitions
volatile bit CCOEN               @ ((unsigned)&CKOCON*8)+0;
volatile bit CCOSEL0             @ ((unsigned)&CKOCON*8)+1;
volatile bit CCOSEL1             @ ((unsigned)&CKOCON*8)+2;
volatile bit CCOSEL2             @ ((unsigned)&CKOCON*8)+3;
volatile bit DTYSEL0             @ ((unsigned)&CKOCON*8)+4;
volatile bit DTYSEL1             @ ((unsigned)&CKOCON*8)+5;
volatile bit CCORDY              @ ((unsigned)&CKOCON*8)+6;
volatile bit SYSON               @ ((unsigned)&CKOCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCOEN               : 1;
        unsigned	CCOSEL0             : 1;
        unsigned	CCOSEL1             : 1;
        unsigned	CCOSEL2             : 1;
        unsigned	DTYSEL0             : 1;
        unsigned	DTYSEL1             : 1;
        unsigned	CCORDY              : 1;
        unsigned	SYSON               : 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	CCOSEL              : 3;
        unsigned	DTYSEL              : 2;
        unsigned	                    : 2;
    };
} CKOCONbits @ 0x095;
#endif

// Register: PCON
// Power Control Register
volatile unsigned char           PCON                @ 0x096;
// bit and bitfield definitions
volatile bit nBORF                @ ((unsigned)&PCON*8)+0;
volatile bit nPORF                @ ((unsigned)&PCON*8)+1;
volatile bit nSRSTF               @ ((unsigned)&PCON*8)+2;
volatile bit nMCLRF               @ ((unsigned)&PCON*8)+3;
volatile bit IERRF                @ ((unsigned)&PCON*8)+4;
volatile bit EMCF                 @ ((unsigned)&PCON*8)+5;
volatile bit STKUNF               @ ((unsigned)&PCON*8)+6;
volatile bit STKOVF               @ ((unsigned)&PCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	nBORF                : 1;
        unsigned	nPORF                : 1;
        unsigned	nSRSTF               : 1;
        unsigned	nMCLRF               : 1;
        unsigned	IERRF                : 1;
        unsigned	EMCF                 : 1;
        unsigned	STKUNF               : 1;
        unsigned	STKOVF               : 1;
    };
} PCONbits @ 0x096;
#endif

// Register: WDTCON
// Watchdog Timer Control Register
volatile unsigned char           WDTCON              @ 0x097;
// bit and bitfield definitions
volatile bit SWDTEN              @ ((unsigned)&WDTCON*8)+0;
volatile bit WDTPS0              @ ((unsigned)&WDTCON*8)+1;
volatile bit WDTPS1              @ ((unsigned)&WDTCON*8)+2;
volatile bit WDTPS2              @ ((unsigned)&WDTCON*8)+3;
volatile bit WDTPS3              @ ((unsigned)&WDTCON*8)+4;
volatile bit WDTPRE0             @ ((unsigned)&WDTCON*8)+5;
volatile bit WDTPRE1             @ ((unsigned)&WDTCON*8)+6;
volatile bit WDTPRE2             @ ((unsigned)&WDTCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SWDTEN              : 1;
        unsigned	WDTPS0              : 1;
        unsigned	WDTPS1              : 1;
        unsigned	WDTPS2              : 1;
        unsigned	WDTPS3              : 1;
        unsigned	WDTPRE0             : 1;
        unsigned	WDTPRE1             : 1;
        unsigned	WDTPRE2             : 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	WDTPS               : 4;
        unsigned	WDTPRE               : 3;
    };
} WDTCONbits @ 0x097;
#endif

// Register: OSCTUNE
// Oscillator Tuning Register
volatile unsigned char           OSCTUNE             @ 0x098;
// bit and bitfield definitions
volatile bit TUN0                @ ((unsigned)&OSCTUNE*8)+0;
volatile bit TUN1                @ ((unsigned)&OSCTUNE*8)+1;
volatile bit TUN2                @ ((unsigned)&OSCTUNE*8)+2;
volatile bit TUN3                @ ((unsigned)&OSCTUNE*8)+3;
volatile bit TUN4                @ ((unsigned)&OSCTUNE*8)+4;
volatile bit TUN5                @ ((unsigned)&OSCTUNE*8)+5;
volatile bit TUN6                @ ((unsigned)&OSCTUNE*8)+6;
volatile bit TUN7                @ ((unsigned)&OSCTUNE*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	TUN0                : 1;
        unsigned	TUN1                : 1;
        unsigned	TUN2                : 1;
        unsigned	TUN3                : 1;
        unsigned	TUN4                : 1;
        unsigned	TUN5                : 1;
        unsigned	TUN6                : 1;
        unsigned	TUN7                : 1;
    };
    struct {
        unsigned	TUN                 : 8;
    };
} OSCTUNEbits @ 0x098;
#endif

// Register: OSCCON
// Oscillator Control Register
volatile unsigned char           OSCCON              @ 0x099;
// bit and bitfield definitions
volatile bit SCS                 @ ((unsigned)&OSCCON*8)+0;
volatile bit LTS                 @ ((unsigned)&OSCCON*8)+1;
volatile bit HTS                 @ ((unsigned)&OSCCON*8)+2;
volatile bit OSTS                @ ((unsigned)&OSCCON*8)+3;
volatile bit MCKCF0              @ ((unsigned)&OSCCON*8)+4;
volatile bit MCKCF1              @ ((unsigned)&OSCCON*8)+5;
volatile bit MCKCF2              @ ((unsigned)&OSCCON*8)+6;
volatile bit MCKCF3              @ ((unsigned)&OSCCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SCS                 : 1;
        unsigned	LTS                 : 1;
        unsigned	HTS                 : 1;
        unsigned	OSTS                : 1;
        unsigned	MCKCF0              : 1;
        unsigned	MCKCF1              : 1;
        unsigned	MCKCF2              : 1;
        unsigned	MCKCF3              : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	MCKCF               : 4;
    };
} OSCCONbits @ 0x099;
#endif

// Register: PCKEN
// Oscillator Status Register
volatile unsigned char           PCKEN             @ 0x09A;
// bit and bitfield definitions
volatile bit ADCEN               @ ((unsigned)&PCKEN*8)+0;
volatile bit TIM1EN              @ ((unsigned)&PCKEN*8)+1;
volatile bit TIM2EN              @ ((unsigned)&PCKEN*8)+2;
volatile bit TIM4EN              @ ((unsigned)&PCKEN*8)+3;
volatile bit SPICKEN             @ ((unsigned)&PCKEN*8)+4;
volatile bit UARTEN              @ ((unsigned)&PCKEN*8)+5;
volatile bit I2CEN               @ ((unsigned)&PCKEN*8)+6;
volatile bit UART2EN             @ ((unsigned)&PCKEN*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADCEN               : 1;
        unsigned	TIM1EN              : 1;
        unsigned	TIM2EN              : 1;
        unsigned	TIM4EN              : 1;
        unsigned	SPICKEN             : 1;
        unsigned	UARTEN              : 1;
        unsigned	I2CEN               : 1;
        unsigned	UART2EN             : 1;
    };
} PCKENbits @ 0x09A;
#endif
// bit and bitfield definitions

// Register: ADRESL
// A/D Result Register LSB
volatile unsigned char           ADRESL              @ 0x09B;
// bit and bitfield definitions

// Register: ADRESH
// A/D Result Register MSB
volatile unsigned char           ADRESH              @ 0x09C;
// bit and bitfield definitions

// Register: ADCON0
// Analog-to-Digital Control Register 0
volatile unsigned char           ADCON0              @ 0x09D;
// bit and bitfield definitions
volatile bit ADON                @ ((unsigned)&ADCON0*8)+0;
volatile bit GO                  @ ((unsigned)&ADCON0*8)+1;
volatile bit nDONE               @ ((unsigned)&ADCON0*8)+1;
volatile bit ADEX                @ ((unsigned)&ADCON0*8)+2;
volatile bit CHS0                @ ((unsigned)&ADCON0*8)+4;
volatile bit CHS1                @ ((unsigned)&ADCON0*8)+5;
volatile bit CHS2                @ ((unsigned)&ADCON0*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADON                : 1;
        unsigned	GO                  : 1;
        unsigned	ADEX                : 1;
        unsigned	                    : 1;
        unsigned	CHS0                : 1;
        unsigned	CHS1                : 1;
        unsigned	CHS2                : 1;
    };
    struct {
        unsigned	                    : 1;
        unsigned	nDONE               : 1;
    };
    struct {
        unsigned	                    : 4;
        unsigned	CHS                 : 3;
    };
} ADCON0bits @ 0x09D;
#endif

// Register: ADCON1
// Analog-to-Digital Control Register 1
volatile unsigned char           ADCON1              @ 0x09E;
// bit and bitfield definitions
volatile bit ADPREF0             @ ((unsigned)&ADCON1*8)+0;
volatile bit ADPREF1             @ ((unsigned)&ADCON1*8)+1;
volatile bit ADNREF0             @ ((unsigned)&ADCON1*8)+2;
volatile bit ADNREF1             @ ((unsigned)&ADCON1*8)+3;
volatile bit ADCS0               @ ((unsigned)&ADCON1*8)+4;
volatile bit ADCS1               @ ((unsigned)&ADCON1*8)+5;
volatile bit ADCS2               @ ((unsigned)&ADCON1*8)+6;
volatile bit ADFM                @ ((unsigned)&ADCON1*8)+7;
#ifndef _LIB_BUILD
volatile union {
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
    struct {
        unsigned	ADPREF              : 2;
        unsigned	ADNREF              : 2;
        unsigned	ADCS                : 3;
    };
} ADCON1bits @ 0x09E;
#endif

// Register: ADCON2
// Analog-to-Digital Control Register 1
volatile unsigned char           ADCON2              @ 0x09F;
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
        unsigned	ETGSEL0             : 1;
        unsigned	ETGSEL1             : 1;
        unsigned	ETGSEL2             : 1;
        unsigned	ADDLY8              : 1;
        unsigned	ETGTYP0             : 1;
        unsigned	ETGTYP1             : 1;
        unsigned	ADINTREF0           : 1;
        unsigned	ADINTREF1           : 1;
    };
    struct {
        unsigned	ETGSEL              : 3;
        unsigned	                    : 1;
        unsigned	ETGTYP              : 2;
        unsigned	ADINTREF            : 2;
    };
} ADCON2bits @ 0x09F;
#endif

//
// Special function register definitions: Bank 2
//


// Register: LATA
volatile unsigned char           LATA                @ 0x10C;
// bit and bitfield definitions
volatile bit LATA0               @ ((unsigned)&LATA*8)+0;
volatile bit LATA1               @ ((unsigned)&LATA*8)+1;
volatile bit LATA2               @ ((unsigned)&LATA*8)+2;
volatile bit LATA3               @ ((unsigned)&LATA*8)+3;
volatile bit LATA4               @ ((unsigned)&LATA*8)+4;
volatile bit LATA5               @ ((unsigned)&LATA*8)+5;
volatile bit LATA6               @ ((unsigned)&LATA*8)+6;
volatile bit LATA7               @ ((unsigned)&LATA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LATA0               : 1;
        unsigned	LATA1               : 1;
        unsigned	LATA2               : 1;
        unsigned	LATA3               : 1;
        unsigned	LATA4               : 1;
        unsigned	LATA5               : 1;
        unsigned	LATA6               : 1;
        unsigned	LATA7               : 1;
    };
    struct {
        unsigned	LATA               : 8;
    };
} LATAbits @ 0x10C;
#endif

// Register: LATB
volatile unsigned char           LATB                @ 0x10D;
// bit and bitfield definitions
volatile bit LATB0               @ ((unsigned)&LATB*8)+0;
volatile bit LATB1               @ ((unsigned)&LATB*8)+1;
volatile bit LATB2               @ ((unsigned)&LATB*8)+2;
volatile bit LATB3               @ ((unsigned)&LATB*8)+3;
volatile bit LATB4               @ ((unsigned)&LATB*8)+4;
volatile bit LATB5               @ ((unsigned)&LATB*8)+5;
volatile bit LATB6               @ ((unsigned)&LATB*8)+6;
volatile bit LATB7               @ ((unsigned)&LATB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LATB0               : 1;
        unsigned	LATB1               : 1;
        unsigned	LATB2               : 1;
        unsigned	LATB3               : 1;
        unsigned	LATB4               : 1;
        unsigned	LATB5               : 1;
        unsigned	LATB6               : 1;
        unsigned	LATB7               : 1;
    };
    struct {
        unsigned	LATB               : 8;
    };
} LATBbits @ 0x10D;
#endif

// Register: LATC
volatile unsigned char           LATC                @ 0x10E;
// bit and bitfield definitions
volatile bit LATC0               @ ((unsigned)&LATC*8)+0;
volatile bit LATC1               @ ((unsigned)&LATC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LATC0               : 1;
        unsigned	LATC1               : 1;
    };
    struct {
        unsigned	LATC               : 2;
    };
} LATCbits @ 0x10E;
#endif


// Register: TIM4CR1
volatile unsigned char           TIM4CR1             @ 0x111;
// bit and bitfield definitions
volatile bit T4CEN                 @ ((unsigned)&TIM4CR1*8)+0;
volatile bit T4UDIS                @ ((unsigned)&TIM4CR1*8)+1;
volatile bit T4URS                 @ ((unsigned)&TIM4CR1*8)+2;
volatile bit T4OPM                 @ ((unsigned)&TIM4CR1*8)+3;
volatile bit T4CKS0                @ ((unsigned)&TIM4CR1*8)+4;
volatile bit T4CKS1                @ ((unsigned)&TIM4CR1*8)+5;
volatile bit T4ARPE                @ ((unsigned)&TIM4CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T4CEN                 : 1;
        unsigned	T4UDIS                : 1;
        unsigned	T4URS                 : 1;
        unsigned	T4OPM                 : 1;
        unsigned	T4CKS0                : 1;
        unsigned	T4CKS1                : 1;
        unsigned	                      : 1;
        unsigned	T4ARPE                : 1;
    };
} TIM4CR1bits @ 0x111;
#endif

// Register: TIM4IER
volatile unsigned char           TIM4IER             @ 0x112;
// bit and bitfield definitions
volatile bit T4UIE                @ ((unsigned)&TIM4IER*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T4UIE              : 1; 
    };
} TIM4IERbits @ 0x112;
#endif

// Register: TIM4SR
volatile unsigned char           TIM4SR             @ 0x113;
// bit and bitfield definitions
volatile bit T4UIF              @ ((unsigned)&TIM4SR*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T4UIF              : 1;
    };
} TIM4SRbits @ 0x113;
#endif

// Register: TIM4EGR
// Comparator Output Register
volatile unsigned char           TIM4EGR               @ 0x114;
// bit and bitfield definitions
volatile bit T4UG              @ ((unsigned)&TIM4EGR*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T4UG              : 1;
    };
} TIM4EGRbits @ 0x114;
#endif

// Register: TIM4CNTR
// Brown-out Reset Control Register
volatile unsigned char           TIM4CNTR              @ 0x115;
// bit and bitfield definitions

// Register: TIM4PSCR 
// Voltage Reference Control Register 0
volatile unsigned char           TIM4PSCR              @ 0x116;
// bit and bitfield definitions
volatile bit T4PSC0              @ ((unsigned)&TIM4PSCR*8)+0;
volatile bit T4PSC1              @ ((unsigned)&TIM4PSCR*8)+1;
volatile bit T4PSC2              @ ((unsigned)&TIM4PSCR*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T4PSC0                : 1;
        unsigned	T4PSC1                : 1;
        unsigned	T4PSC2                : 1;
    };
    struct {
        unsigned	T4PSC                 : 3;
    };
} TIM4PSCRbits @ 0x116;
#endif

// Register: TIM4ARR
// Brown-out Reset Control Register
volatile unsigned char           TIM4ARR              @ 0x117;
// bit and bitfield definitions

// Register: EPS0
// Voltage Reference Control Register 1
volatile unsigned char           EPS0             @ 0x118;
// bit and bitfield definitions

// Register: EPS1
// Voltage Reference Control Register 1
volatile unsigned char           EPS1             @ 0x119;
// bit and bitfield definitions

// Register: PSRC0
// SR Latch Control Register 0
volatile unsigned char           PSRC0              @ 0x11A;
// bit and bitfield definitions

// Register: PSRC1
// SR Latch Control Register 1
volatile unsigned char           PSRC1              @ 0x11B;
// bit and bitfield definitions

// Register: PSRC2
// SR Latch Control Register 1
volatile unsigned char           PSRC2              @ 0x11C;
// bit and bitfield definitions
volatile bit PSRCC00              @ ((unsigned)&PSRC2*8)+0;
volatile bit PSRCC01              @ ((unsigned)&PSRC2*8)+1;
volatile bit PSRCC10              @ ((unsigned)&PSRC2*8)+2;
volatile bit PSRCC11              @ ((unsigned)&PSRC2*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	PSRCC00                : 1;
        unsigned	PSRCC01                : 1;
        unsigned	PSRCC10                : 1;
        unsigned	PSRCC11                : 1;
    };
    struct {
        unsigned	PSRCC0                 : 2;
        unsigned	PSRCC1                 : 2;
    };
} PSRC2bits @ 0x11C;
#endif

// Register: ITYPE0
// SR Latch Control Register 0
volatile unsigned char           ITYPE0              @ 0x11E;
// bit and bitfield definitions


// Register: PSRC1
// SR Latch Control Register 1
volatile unsigned char           ITYPE1              @ 0x11F;
// bit and bitfield definitions


//
// Special function register definitions: Bank 3
//


// Register: WPUA
volatile unsigned char           WPUA              @ 0x18C;
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
        unsigned	WPUA0                : 1;
        unsigned	WPUA1                : 1;
        unsigned	WPUA2                : 1;
        unsigned	WPUA3                : 1;
        unsigned	WPUA4                : 1;
        unsigned	WPUA5                : 1;
        unsigned	WPUA6                : 1;
        unsigned	WPUA7                : 1;
    };
    struct {
        unsigned	WPUA                 : 8;
    };
} WPUAbits @ 0x18C;
#endif

// Register: WPUB
volatile unsigned char           WPUB              @ 0x18D;
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
        unsigned	WPUB0                : 1;
        unsigned	WPUB1                : 1;
        unsigned	WPUB2                : 1;
        unsigned	WPUB3                : 1;
        unsigned	WPUB4                : 1;
        unsigned	WPUB5                : 1;
        unsigned	WPUB6                : 1;
        unsigned	WPUB7                : 1;
    };
    struct {
        unsigned	WPUB                 : 8;
    };
} WPUBbits @ 0x18D;
#endif

// Register: WPUC
volatile unsigned char           WPUC              @ 0x18E;
// bit and bitfield definitions
volatile bit WPUC0              @ ((unsigned)&WPUC*8)+0;
volatile bit WPUC1              @ ((unsigned)&WPUC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPUC0                : 1;
        unsigned	WPUC1                : 1;
    };
    struct {
        unsigned	WPUC                 : 2;
    };
} WPUCbits @ 0x18E;
#endif


// Register: EEADRL
volatile unsigned char           EEADRL              @ 0x191;
// bit and bitfield definitions

// Register: EEADRH
volatile unsigned char           EEADRH              @ 0x192;
// bit and bitfield definitions
volatile bit EEADRH0               @ ((unsigned)&EEADRH*8)+0;
volatile bit EEADRH1               @ ((unsigned)&EEADRH*8)+1;
volatile bit EEADRH2               @ ((unsigned)&EEADRH*8)+2;
volatile bit EEADRH3               @ ((unsigned)&EEADRH*8)+3;
volatile bit EEADRH4               @ ((unsigned)&EEADRH*8)+4;
volatile bit EEADRH5               @ ((unsigned)&EEADRH*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	EEADRH0             : 1;
        unsigned	EEADRH1             : 1;
        unsigned	EEADRH2             : 1;
        unsigned	EEADRH3             : 1;
        unsigned	EEADRH4             : 1;
        unsigned	EEADRH5             : 1;
    };
    struct {
        unsigned	EEADRH              : 6;
    };
} EEADRHbits @ 0x192;
#endif

// Register: EEDATL
volatile unsigned char           EEDATL              @ 0x193;

// Register: EEDATH
volatile unsigned char           EEDATH              @ 0x194;
// bit and bitfield definitions
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	EEDATH0             : 1;
        unsigned	EEDATH1             : 1;
        unsigned	EEDATH2             : 1;
        unsigned	EEDATH3             : 1;
        unsigned	EEDATH4             : 1;
        unsigned	EEDATH5             : 1;
    };
    struct {
        unsigned	EEDATH              : 6;
    };
} EEDATHbits @ 0x194;
#endif

// Register: EECON1
volatile unsigned char           EECON1              @ 0x195;
// bit and bitfield definitions
volatile bit RD                  @ ((unsigned)&EECON1*8)+0;
volatile bit WR                  @ ((unsigned)&EECON1*8)+1;
volatile bit WREN                @ ((unsigned)&EECON1*8)+2;
volatile bit WRERR               @ ((unsigned)&EECON1*8)+3;
volatile bit FERAE               @ ((unsigned)&EECON1*8)+4; 
volatile bit CFGS                @ ((unsigned)&EECON1*8)+6;
volatile bit EEPGD               @ ((unsigned)&EECON1*8)+7;

volatile bit FREE                @ ((unsigned)&EECON1*8)+4; 
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RD                  : 1;
        unsigned	WR                  : 1;
        unsigned	WREN                : 1;
        unsigned	WRERR               : 1;
        unsigned	FERAE               : 1;
        unsigned	                    : 1;
        unsigned	CFGS                : 1;
        unsigned	EEPGD               : 1;
    };
 //   struct {
 //       unsigned	                    : 1;
 //       unsigned	                    : 1;
 //       unsigned	                    : 1;
 //       unsigned	                    : 1;
 //       unsigned	FREE                : 1;
 //   };
} EECON1bits @ 0x195;
#endif

// Register: EECON2
volatile unsigned char           EECON2              @ 0x196;
// bit and bitfield definitions

// Register: EECON2
volatile unsigned char           ANSELA              @ 0x197;
// bit and bitfield definitions

// Register: AFP2
volatile unsigned char           AFP2                @ 0x198;
// bit and bitfield definitions

// Register: LVDCON0
volatile unsigned char           LVDCON0               @ 0x199;
// bit and bitfield definitions
volatile bit LVDL0               @ ((unsigned)&LVDCON0*8)+0;
volatile bit LVDL1               @ ((unsigned)&LVDCON0*8)+1;
volatile bit LVDL2               @ ((unsigned)&LVDCON0*8)+2;
volatile bit LVDW                @ ((unsigned)&LVDCON0*8)+3;
volatile bit LVDEN               @ ((unsigned)&LVDCON0*8)+4; 
volatile bit LVROE               @ ((unsigned)&LVDCON0*8)+5; 
volatile bit LVDM                @ ((unsigned)&LVDCON0*8)+6;
volatile bit SLVREN              @ ((unsigned)&LVDCON0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVDL0               : 1;
        unsigned	LVDL1               : 1;
        unsigned	LVDL2               : 1;
        unsigned	LVDW                : 1;
        unsigned	LVDEN               : 1;
        unsigned	LVROE               : 1;
        unsigned	LVDM                : 1;
        unsigned	SLVREN              : 1;
        	
    };
    struct {
        unsigned	LVDL                : 3;
    };
} LVDCON0bits @ 0x199;
#endif

// Register: PSINK0
volatile unsigned char           PSINK0               @ 0x19A;
// bit and bitfield definitions

// Register: PSINK1
volatile unsigned char           PSINK1              @ 0x19B;

// Register: PSINK2
volatile unsigned char           PSINK2              @ 0x19C;
// bit and bitfield definitions

// Register: MISC0
// Receive Status and Control Register
volatile unsigned char           MISC0               @ 0x19D;
// bit and bitfield definitions
volatile bit WCKSEL0               @ ((unsigned)&MISC0*8)+0;
volatile bit WCKSEL1               @ ((unsigned)&MISC0*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WCKSEL0               : 1;
        unsigned	WCKSEL1               : 1;
    };
    struct {
        unsigned	WCKSEL                : 2;
    };
} MISC0bits @ 0x19D;
#endif

// Register: AFP0
// Transmit Status and Control Register
volatile unsigned char           AFP0               @ 0x19E;
// bit and bitfield definitions

// Register: AFP1
// Baud Rate Control Register
volatile unsigned char           AFP1               @ 0x19F;
// bit and bitfield definitions

//
// Special function register definitions: Bank 4
//

// Register: WPDA
volatile unsigned char           WPDA                @ 0x20C;
// bit and bitfield definitions
volatile bit WPDA0               @ ((unsigned)&WPDA*8)+0;
volatile bit WPDA1               @ ((unsigned)&WPDA*8)+1;
volatile bit WPDA2               @ ((unsigned)&WPDA*8)+2;
volatile bit WPDA3               @ ((unsigned)&WPDA*8)+3;
volatile bit WPDA4               @ ((unsigned)&WPDA*8)+4;
volatile bit WPDA5               @ ((unsigned)&WPDA*8)+5;
volatile bit WPDA6               @ ((unsigned)&WPDA*8)+6;
volatile bit WPDA7               @ ((unsigned)&WPDA*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDA0               : 1;
        unsigned	WPDA1               : 1;
        unsigned	WPDA2               : 1;
        unsigned	WPDA3               : 1;
        unsigned	WPDA4               : 1;
        unsigned	WPDA5               : 1;
        unsigned	WPDA6               : 1;
        unsigned	WPDA7               : 1;
    };
} WPDAbits @ 0x20C;
#endif


// Register: WPDB
volatile unsigned char           WPDB                @ 0x20D;
// bit and bitfield definitions
volatile bit WPDB0               @ ((unsigned)&WPDB*8)+0;
volatile bit WPDB1               @ ((unsigned)&WPDB*8)+1;
volatile bit WPDB2               @ ((unsigned)&WPDB*8)+2;
volatile bit WPDB3               @ ((unsigned)&WPDB*8)+3;
volatile bit WPDB4               @ ((unsigned)&WPDB*8)+4;
volatile bit WPDB5               @ ((unsigned)&WPDB*8)+5;
volatile bit WPDB6               @ ((unsigned)&WPDB*8)+6;
volatile bit WPDB7               @ ((unsigned)&WPDB*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDB0               : 1;
        unsigned	WPDB1               : 1;
        unsigned	WPDB2               : 1;
        unsigned	WPDB3               : 1;
        unsigned	WPDB4               : 1;
        unsigned	WPDB5               : 1;
        unsigned	WPDB6               : 1;
        unsigned	WPDB7               : 1;
    };
} WPDBbits @ 0x20D;
#endif

// Register: WPDC
volatile unsigned char           WPDC                @ 0x20E;
// bit and bitfield definitions
volatile bit WPDC0               @ ((unsigned)&WPDC*8)+0;
volatile bit WPDC1               @ ((unsigned)&WPDC*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	WPDC0               : 1;
        unsigned	WPDC1               : 1;
    };
    struct {
        unsigned	WPDC                : 2;
    };
} WPDCbits @ 0x20E;
#endif


// Register: TIM1CR1
volatile unsigned char           TIM1CR1              @ 0x211;
// bit and bitfield definitions
volatile bit T1CEN                 @ ((unsigned)&TIM1CR1*8)+0;
volatile bit T1UDIS                @ ((unsigned)&TIM1CR1*8)+1;
volatile bit T1URS                 @ ((unsigned)&TIM1CR1*8)+2;
volatile bit T1OPM                 @ ((unsigned)&TIM1CR1*8)+3;
volatile bit T1DIR                   @ ((unsigned)&TIM1CR1*8)+4;
volatile bit T1CMS0                  @ ((unsigned)&TIM1CR1*8)+5;
volatile bit T1CMS1                  @ ((unsigned)&TIM1CR1*8)+6;
volatile bit T1ARPE                @ ((unsigned)&TIM1CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CEN                 : 1;
        unsigned	T1UDIS                : 1;
        unsigned	T1URS                 : 1;
        unsigned	T1OPM                 : 1;
        unsigned	T1DIR                 : 1;
        unsigned	T1CMS0                : 1;
        unsigned	T1CMS1                : 1;
        unsigned	T1ARPE                : 1;
    };
    struct {
        unsigned	                    : 5;
        unsigned	T1CMS               : 2;
    };
} TIM1CR1bits @ 0x211;
#endif

// Register: TIM1CR2
volatile unsigned char           TIM1CR2              @ 0x212;
// bit and bitfield definitions
volatile bit T1CCPC                 @ ((unsigned)&TIM1CR2*8)+0;
volatile bit T1COMS                 @ ((unsigned)&TIM1CR2*8)+2;
volatile bit T1ENCTRL               @ ((unsigned)&TIM1CR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CCPC                 : 1;
        unsigned	                       : 1;
        unsigned	T1COMS                 : 1;
        unsigned	                       : 1;
        unsigned	                       : 1;
        unsigned	                       : 1;
        unsigned	                       : 1;
        unsigned	T1ENCTRL               : 1;
    };
} TIM1CR2bits @ 0x212;
#endif

// Register: TIM1SMCR
volatile unsigned char           TIM1SMCR             @ 0x213;
// bit and bitfield definitions
volatile bit T1SMS0                @ ((unsigned)&TIM1SMCR*8)+0;
volatile bit T1SMS1                @ ((unsigned)&TIM1SMCR*8)+1;
volatile bit T1SMS2                @ ((unsigned)&TIM1SMCR*8)+2;
volatile bit T1TS0                 @ ((unsigned)&TIM1SMCR*8)+4;
volatile bit T1TS1                 @ ((unsigned)&TIM1SMCR*8)+5;
volatile bit T1TS2                 @ ((unsigned)&TIM1SMCR*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1SMS0                : 1;
        unsigned	T1SMS1                : 1;
        unsigned	T1SMS2                : 1;
        unsigned	                      : 1;
        unsigned	T1TS0                 : 1;
        unsigned	T1TS1                 : 1;
        unsigned	T1TS2                 : 1;
    };
    struct {
        unsigned	T1SMS                 : 3;
        unsigned	                      : 1;
        unsigned	T1TS                  : 3;
    };
} TIM1SMCRbits @ 0x213;
#endif

// Register: TIM1ETR
volatile unsigned char           TIM1ETR             @ 0x214;
// bit and bitfield definitions
volatile bit T1ETF0                @ ((unsigned)&TIM1ETR*8)+0;
volatile bit T1ETF1                @ ((unsigned)&TIM1ETR*8)+1;
volatile bit T1ETF2                @ ((unsigned)&TIM1ETR*8)+2;
volatile bit T1ETF3                @ ((unsigned)&TIM1ETR*8)+3;
volatile bit T1ETPS0               @ ((unsigned)&TIM1ETR*8)+4;
volatile bit T1ETPS1               @ ((unsigned)&TIM1ETR*8)+5;
volatile bit T1ECE                 @ ((unsigned)&TIM1ETR*8)+6;
volatile bit T1ETP                 @ ((unsigned)&TIM1ETR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1ETF0                : 1;
        unsigned	T1ETF1                : 1;
        unsigned	T1ETF2                : 1;
        unsigned	T1ETF3                : 1;
        unsigned	T1ETPS0               : 1;
        unsigned	T1ETPS1               : 1;
        unsigned	T1ECE                 : 1;
        unsigned	T1ETP                 : 1;
    };
    struct {
        unsigned	T1ETF                 : 4;
        unsigned	T1ETPS                : 2;
    };
} TIM1ETRbits @ 0x214;
#endif

// Register: TIM1IER
volatile unsigned char           TIM1IER             @ 0x215;
// bit and bitfield definitions
volatile bit T1UIE                 @ ((unsigned)&TIM1IER*8)+0;
volatile bit T1CC1IE               @ ((unsigned)&TIM1IER*8)+1;
volatile bit T1CC2IE               @ ((unsigned)&TIM1IER*8)+2;
volatile bit T1CC3IE               @ ((unsigned)&TIM1IER*8)+3;
volatile bit T1CC4IE               @ ((unsigned)&TIM1IER*8)+4;
volatile bit T1COMIE               @ ((unsigned)&TIM1IER*8)+5;
volatile bit T1TIE                 @ ((unsigned)&TIM1IER*8)+6;
volatile bit T1BIE                 @ ((unsigned)&TIM1IER*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1UIE                 : 1;
        unsigned	T1CC1IE               : 1;
        unsigned	T1CC2IE               : 1;
        unsigned	T1CC3IE               : 1;
        unsigned	T1CC4IE               : 1;
        unsigned	T1COMIE               : 1;
        unsigned	T1TIE                 : 1;
        unsigned	T1BIE                 : 1;
    };
} TIM1IERbits @ 0x215;
#endif

// Register: TIM1SR1
volatile unsigned char           TIM1SR1             @ 0x216;
// bit and bitfield definitions
volatile bit T1UIF               @ ((unsigned)&TIM1SR1*8)+0;
volatile bit T1CC1IF             @ ((unsigned)&TIM1SR1*8)+1;
volatile bit T1CC2IF             @ ((unsigned)&TIM1SR1*8)+2;
volatile bit T1CC3IF             @ ((unsigned)&TIM1SR1*8)+3;
volatile bit T1CC4IF             @ ((unsigned)&TIM1SR1*8)+4;
volatile bit T1COMIF             @ ((unsigned)&TIM1SR1*8)+5;
volatile bit T1TIF               @ ((unsigned)&TIM1SR1*8)+6;
volatile bit T1BIF               @ ((unsigned)&TIM1SR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1UIF                 : 1;
        unsigned	T1CC1IF               : 1;
        unsigned	T1CC2IF               : 1;
        unsigned	T1CC3IF               : 1;
        unsigned	T1CC4IF               : 1;
        unsigned	T1COMIF               : 1;
        unsigned	T1TIF                 : 1;
        unsigned	T1BIF                 : 1;
    };
} TIM1SR1bits @ 0x216;
#endif

// Register: TIM1SR2
volatile unsigned char           TIM1SR2             @ 0x217;
// bit and bitfield definitions
volatile bit T1CC1OF               @ ((unsigned)&TIM1SR2*8)+1;
volatile bit T1CC2OF               @ ((unsigned)&TIM1SR2*8)+2;
volatile bit T1CC3OF               @ ((unsigned)&TIM1SR2*8)+3;
volatile bit T1CC4OF               @ ((unsigned)&TIM1SR2*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                      : 1;
        unsigned	T1CC1OF               : 1;
        unsigned	T1CC2OF               : 1;
        unsigned	T1CC3OF               : 1;
        unsigned	T1CC4OF               : 1;
    };
} TIM1SR2bits @ 0x217;
#endif

// Register: TIM1EGR
volatile unsigned char           TIM1EGR             @ 0x218;
// bit and bitfield definitions
volatile bit T1UG                 @ ((unsigned)&TIM1EGR*8)+0;
volatile bit T1CC1G               @ ((unsigned)&TIM1EGR*8)+1;
volatile bit T1CC2G               @ ((unsigned)&TIM1EGR*8)+2;
volatile bit T1CC3G               @ ((unsigned)&TIM1EGR*8)+3;
volatile bit T1CC4G               @ ((unsigned)&TIM1EGR*8)+4;
volatile bit T1COMG               @ ((unsigned)&TIM1EGR*8)+5;
volatile bit T1TG                 @ ((unsigned)&TIM1EGR*8)+6;
volatile bit T1BG                 @ ((unsigned)&TIM1EGR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1UG                 : 1;
        unsigned	T1CC1G               : 1;
        unsigned	T1CC2G               : 1;
        unsigned	T1CC3G               : 1;
        unsigned	T1CC4G               : 1;
        unsigned	T1COMG               : 1;
        unsigned	T1TG                 : 1;
        unsigned	T1BG                 : 1;
    };
} TIM1EGRbits @ 0x218;
#endif
// Register: TIM1CCMR1
volatile unsigned char           TIM1CCMR1             @ 0x219;
// bit and bitfield definitions
volatile bit T1CC1S0              @ ((unsigned)&TIM1CCMR1*8)+0;
volatile bit T1CC1S1              @ ((unsigned)&TIM1CCMR1*8)+1;
volatile bit T1OC1FE              @ ((unsigned)&TIM1CCMR1*8)+2;
volatile bit T1OC1PE              @ ((unsigned)&TIM1CCMR1*8)+3;
volatile bit T1OC1M0              @ ((unsigned)&TIM1CCMR1*8)+4;
volatile bit T1OC1M1              @ ((unsigned)&TIM1CCMR1*8)+5;
volatile bit T1OC1M2              @ ((unsigned)&TIM1CCMR1*8)+6;
volatile bit T1OC1CE              @ ((unsigned)&TIM1CCMR1*8)+7;

volatile bit T1IC1PSC0            @ ((unsigned)&TIM1CCMR1*8)+2;
volatile bit T1IC1PSC1            @ ((unsigned)&TIM1CCMR1*8)+3;
volatile bit T1IC1F0              @ ((unsigned)&TIM1CCMR1*8)+4;
volatile bit T1IC1F1              @ ((unsigned)&TIM1CCMR1*8)+5;
volatile bit T1IC1F2              @ ((unsigned)&TIM1CCMR1*8)+6;
volatile bit T1IC1F3              @ ((unsigned)&TIM1CCMR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC1S0               : 1;
        unsigned	T1CC1S1               : 1;
        unsigned	T1OC1FE               : 1;
        unsigned	T1OC1PE               : 1;
        unsigned	T1OC1M0               : 1;
        unsigned	T1OC1M1               : 1;
        unsigned	T1OC1M2               : 1;
        unsigned	T1OC1CE               : 1;
    };
    struct {
        unsigned	                      : 2;
        unsigned	T1IC1PSC0             : 1;
        unsigned	T1IC1PSC1             : 1;
        unsigned	T1IC1F0               : 1;
        unsigned	T1IC1F1               : 1;
        unsigned	T1IC1F2               : 1;
        unsigned	T1IC1F3               : 1;
    };
    struct {
        unsigned	T1CC1S              : 2;
        unsigned	                    : 2;
        unsigned	T1OC1M              : 3;
        unsigned	                    : 1;
    };
    struct {
        unsigned	                    : 2;
        unsigned	T1IC1PSC            : 2;
        unsigned	T1IC1F              : 4;
    };
} TIM1CCMR1bits @ 0x219;
#endif

// Register: TIM1CCMR2
volatile unsigned char           TIM1CCMR2             @ 0x21A;
// bit and bitfield definitions
volatile bit T1CC2S0                @ ((unsigned)&TIM1CCMR2*8)+0;
volatile bit T1CC2S1                @ ((unsigned)&TIM1CCMR2*8)+1;
volatile bit T1OC2FE                @ ((unsigned)&TIM1CCMR2*8)+2;
volatile bit T1OC2PE                @ ((unsigned)&TIM1CCMR2*8)+3;
volatile bit T1OC2M0                @ ((unsigned)&TIM1CCMR2*8)+4;
volatile bit T1OC2M1                @ ((unsigned)&TIM1CCMR2*8)+5;
volatile bit T1OC2M2                @ ((unsigned)&TIM1CCMR2*8)+6;
volatile bit T1OC2CE                @ ((unsigned)&TIM1CCMR2*8)+7;

volatile bit T1IC2PSC0              @ ((unsigned)&TIM1CCMR2*8)+2;
volatile bit T1IC2PSC1              @ ((unsigned)&TIM1CCMR2*8)+3;
volatile bit T1IC2F0                @ ((unsigned)&TIM1CCMR2*8)+4;
volatile bit T1IC2F1                @ ((unsigned)&TIM1CCMR2*8)+5;
volatile bit T1IC2F2                @ ((unsigned)&TIM1CCMR2*8)+6;
volatile bit T1IC2F3                @ ((unsigned)&TIM1CCMR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC2S0               : 1;
        unsigned	T1CC2S1               : 1;
        unsigned	T1OC2FE               : 1;
        unsigned	T1OC2PE               : 1;
        unsigned	T1OC2M0               : 1;
        unsigned	T1OC2M1               : 1;
        unsigned	T1OC2M2               : 1;
        unsigned	T1OC2CE               : 1;
    };
    struct {
        unsigned	                      : 1;
        unsigned	                      : 1;
        unsigned	T1IC2PSC0             : 1;
        unsigned	T1IC2PSC1             : 1;
        unsigned	T1IC2F0               : 1;
        unsigned	T1IC2F1               : 1;
        unsigned	T1IC2F2               : 1;
        unsigned	T1IC2F3               : 1;
    };
    struct {
        unsigned	T1CC2S              : 2;
        unsigned	                    : 2;
        unsigned	T1OC2M              : 3;
        unsigned	                    : 1;
    };
    struct {
        unsigned	T1IC2PSC              : 2;
        unsigned	T1IC2F                : 4;
    };
} TIM1CCMR2bits @ 0x21A;
#endif


// Register: TIM1CCMR3
volatile unsigned char           TIM1CCMR3             @ 0x21B;
// bit and bitfield definitions
volatile bit T1CC3S0                @ ((unsigned)&TIM1CCMR3*8)+0;
volatile bit T1CC3S1                @ ((unsigned)&TIM1CCMR3*8)+1;
volatile bit T1OC3FE                @ ((unsigned)&TIM1CCMR3*8)+2;
volatile bit T1OC3PE                @ ((unsigned)&TIM1CCMR3*8)+3;
volatile bit T1OC3M0                @ ((unsigned)&TIM1CCMR3*8)+4;
volatile bit T1OC3M1                @ ((unsigned)&TIM1CCMR3*8)+5;
volatile bit T1OC3M2                @ ((unsigned)&TIM1CCMR3*8)+6;
volatile bit T1OC3CE                @ ((unsigned)&TIM1CCMR3*8)+7;

volatile bit T1IC3PSC0              @ ((unsigned)&TIM1CCMR3*8)+2;
volatile bit T1IC3PSC1              @ ((unsigned)&TIM1CCMR3*8)+3;
volatile bit T1IC3F0                @ ((unsigned)&TIM1CCMR3*8)+4;
volatile bit T1IC3F1                @ ((unsigned)&TIM1CCMR3*8)+5;
volatile bit T1IC3F2                @ ((unsigned)&TIM1CCMR3*8)+6;
volatile bit T1IC3F3                @ ((unsigned)&TIM1CCMR3*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC3S0               : 1;
        unsigned	T1CC3S1               : 1;
        unsigned	T1OC3FE               : 1;
        unsigned	T1OC3PE               : 1;
        unsigned	T1OC3M0               : 1;
        unsigned	T1OC3M1               : 1;
        unsigned	T1OC3M2               : 1;
        unsigned	T1OC3CE               : 1;
    };
    struct {
        unsigned	                      : 2;
        unsigned	T1IC3PSC0             : 1;
        unsigned	T1IC3PSC1             : 1;
        unsigned	T1IC3F0               : 1;
        unsigned	T1IC3F1               : 1;
        unsigned	T1IC3F2               : 1;
        unsigned	T1IC3F3               : 1;
    };
    struct {
        unsigned	T1CC3S              : 2;
        unsigned	                    : 2;
        unsigned	T1OC3M              : 3;
        unsigned	                    : 1;
    };
    struct {
        unsigned	                      : 2;
        unsigned	T1IC3PSC              : 2;
        unsigned	T1IC3F                : 4;
    };
} TIM1CCMR3bits @ 0x21B;
#endif


// Register: TIM1CCMR4
volatile unsigned char           TIM1CCMR4             @ 0x21C;
// bit and bitfield definitions
volatile bit T1CC4S0                @ ((unsigned)&TIM1CCMR4*8)+0;
volatile bit T1CC4S1                @ ((unsigned)&TIM1CCMR4*8)+1;
volatile bit T1OC4FE                @ ((unsigned)&TIM1CCMR4*8)+2;
volatile bit T1OC4PE                @ ((unsigned)&TIM1CCMR4*8)+3;
volatile bit T1OC4M0                @ ((unsigned)&TIM1CCMR4*8)+4;
volatile bit T1OC4M1                @ ((unsigned)&TIM1CCMR4*8)+5;
volatile bit T1OC4M2                @ ((unsigned)&TIM1CCMR4*8)+6;
volatile bit T1OC4CE                @ ((unsigned)&TIM1CCMR4*8)+6;

volatile bit T1IC4PSC0              @ ((unsigned)&TIM1CCMR4*8)+2;
volatile bit T1IC4PSC1              @ ((unsigned)&TIM1CCMR4*8)+3;
volatile bit T1IC4F0                @ ((unsigned)&TIM1CCMR4*8)+4;
volatile bit T1IC4F1                @ ((unsigned)&TIM1CCMR4*8)+5;
volatile bit T1IC4F2                @ ((unsigned)&TIM1CCMR4*8)+6;
volatile bit T1IC4F3                @ ((unsigned)&TIM1CCMR4*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC4S0               : 1;
        unsigned	T1CC4S1               : 1;
        unsigned	T1OC4FE               : 1;
        unsigned	T1OC4PE               : 1;
        unsigned	T1OC4M0               : 1;
        unsigned	T1OC4M1               : 1;
        unsigned	T1OC4M2               : 1;
        unsigned	T1OC4CE               : 1;
    };
    struct {
        unsigned	                      : 2;
        unsigned	T1IC4PSC0             : 1;
        unsigned	T1IC4PSC1             : 1;
        unsigned	T1IC4F0               : 1;
        unsigned	T1IC4F1               : 1;
        unsigned	T1IC4F2               : 1;
        unsigned	T1IC4F3               : 1;
    };
    struct {
        unsigned	T1CC4S                : 2;
        unsigned	                      : 2;
        unsigned	T1OC4M                : 3;
        unsigned	                      : 1;
    };
    struct {
        unsigned	                      : 2;
        unsigned	T1IC4PSC              : 2;
        unsigned	T1IC4F                : 4;
    };
} TIM1CCMR4bits @ 0x21C;
#endif


// Register: TIM1CCER1
volatile unsigned char           TIM1CCER1             @ 0x21D;
// bit and bitfield definitions
volatile bit T1CC1E                 @ ((unsigned)&TIM1CCER1*8)+0;
volatile bit T1CC1P                 @ ((unsigned)&TIM1CCER1*8)+1;
volatile bit T1CC1NE                @ ((unsigned)&TIM1CCER1*8)+2;
volatile bit T1CC1NP                @ ((unsigned)&TIM1CCER1*8)+3;
volatile bit T1CC2E                 @ ((unsigned)&TIM1CCER1*8)+4;
volatile bit T1CC2P                 @ ((unsigned)&TIM1CCER1*8)+5;
volatile bit T1CC2NE                @ ((unsigned)&TIM1CCER1*8)+6;
volatile bit T1CC2NP                @ ((unsigned)&TIM1CCER1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC1E                : 1;
        unsigned	T1CC1P                : 1;
        unsigned	T1CC1NE               : 1;
        unsigned	T1CC1NP               : 1;
        unsigned	T1CC2E                : 1;
        unsigned	T1CC2P                : 1;
        unsigned	T1CC2NE               : 1;
        unsigned	T1CC2NP               : 1;
    };
} TIM1CCER1bits @ 0x21D;
#endif

// Register: TIM1CCER2
volatile unsigned char           TIM1CCER2             @ 0x21E;
// bit and bitfield definitions
volatile bit T1CC3E                 @ ((unsigned)&TIM1CCER2*8)+0;
volatile bit T1CC3P                 @ ((unsigned)&TIM1CCER2*8)+1;
volatile bit T1CC3NE                @ ((unsigned)&TIM1CCER2*8)+2;
volatile bit T1CC3NP                @ ((unsigned)&TIM1CCER2*8)+3;
volatile bit T1CC4E                 @ ((unsigned)&TIM1CCER2*8)+4;
volatile bit T1CC4P                 @ ((unsigned)&TIM1CCER2*8)+5;
volatile bit T1SMOD                 @ ((unsigned)&TIM1CCER2*8)+6;
volatile bit T1GP                   @ ((unsigned)&TIM1CCER2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CC3E                : 1;
        unsigned	T1CC3P                : 1;
        unsigned	T1CC3NE               : 1;
        unsigned	T1CC3NP               : 1;
        unsigned	T1CC4E                : 1;
        unsigned	T1CC4P                : 1;
        unsigned	T1SMOD                : 1;
        unsigned	T1GP                  : 1;
    };
} TIM1CCER2bits @ 0x21E;
#endif
 
// Register: ODCON0
volatile unsigned char           ODCON0             @ 0x21F;
// bit and bitfield definitions
volatile bit UR1OD                 @ ((unsigned)&ODCON0*8)+0;
volatile bit I2COD                 @ ((unsigned)&ODCON0*8)+1;
volatile bit SPIOD                 @ ((unsigned)&ODCON0*8)+2;
volatile bit UR2OD                 @ ((unsigned)&ODCON0*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1OD                : 1;
        unsigned	I2COD                : 1;
        unsigned	SPIOD                : 1;
        unsigned	UR2OD                : 1;
    };
} ODCON0bits @ 0x21F;
#endif
//
// Special function register definitions: Bank 5--------------------------------------------------------------
//

// Register: TIM1CNTRH
volatile unsigned char           TIM1CNTRH             @ 0x28C;
// bit and bitfield definitions
 
// Register: TIM1CNTRL
volatile unsigned char           TIM1CNTRL             @ 0x28D;
// bit and bitfield definitions

// Register: TIM1PSCRH
volatile unsigned char           TIM1PSCRH             @ 0x28E;
// bit and bitfield definitions 

// Register: TIM1PSCRL
volatile unsigned char           TIM1PSCRL             @ 0x28F;
// bit and bitfield definitions 

// Register: TIM1ARRH
volatile unsigned char           TIM1ARRH              @ 0x290;
// bit and bitfield definitions 

// Register: TIM1ARRL
volatile unsigned char           TIM1ARRL              @ 0x291;
// bit and bitfield definitions

// Register: TIM1RCR
volatile unsigned char           TIM1RCR               @ 0x292;
// bit and bitfield definitions

// Register: TIM1CCR1H
volatile unsigned char           TIM1CCR1H             @ 0x293;
// bit and bitfield definitions

// Register: TIM1CCR1L
volatile unsigned char           TIM1CCR1L             @ 0x294;
// bit and bitfield definitions

// Register: TIM1CCR2H
volatile unsigned char           TIM1CCR2H             @ 0x295;
// bit and bitfield definitions

// Register: TIM1CCR2L
volatile unsigned char           TIM1CCR2L             @ 0x296;
// bit and bitfield definitions

// Register: TIM1CCR3H
volatile unsigned char           TIM1CCR3H             @ 0x297;
// bit and bitfield definitions

// Register: TIM1CCR3L
volatile unsigned char           TIM1CCR3L             @ 0x298;
// bit and bitfield definitions

// Register: TIM1CCR4H
volatile unsigned char           TIM1CCR4H             @ 0x299;
// bit and bitfield definitions

// Register: TIM1CCR4L
volatile unsigned char           TIM1CCR4L             @ 0x29A;
// bit and bitfield definitions

// Register: TIM1BKR
volatile unsigned char           TIM1BKR               @ 0x29B;
// bit and bitfield definitions
volatile bit T1LOCK0               @ ((unsigned)&TIM1BKR*8)+0;
volatile bit T1LOCK1               @ ((unsigned)&TIM1BKR*8)+1;
volatile bit T1OSSI                @ ((unsigned)&TIM1BKR*8)+2;
volatile bit T1OSSR                @ ((unsigned)&TIM1BKR*8)+3;
volatile bit T1BKE                 @ ((unsigned)&TIM1BKR*8)+4;
volatile bit T1BKP                 @ ((unsigned)&TIM1BKR*8)+5;
volatile bit T1AOE                 @ ((unsigned)&TIM1BKR*8)+6;
volatile bit T1MOE                 @ ((unsigned)&TIM1BKR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1LOCK0               : 1;
        unsigned	T1LOCK1               : 1;
        unsigned	T1OSSI                : 1;
        unsigned	T1OSSR                : 1;
        unsigned	T1BKE                 : 1;
        unsigned	T1BKP                 : 1;
        unsigned	T1AOE                 : 1;
        unsigned	T1MOE                 : 1;
    };
} TIM1BKRbits @ 0x29B;
#endif

// Register: TIM1DTR
volatile unsigned char           TIM1DTR               @ 0x29C;
// bit and bitfield definitions
volatile bit T1DTG0                 @ ((unsigned)&TIM1DTR*8)+0;
volatile bit T1DTG1                 @ ((unsigned)&TIM1DTR*8)+1;
volatile bit T1DTG2                 @ ((unsigned)&TIM1DTR*8)+2;
volatile bit T1DTG3                 @ ((unsigned)&TIM1DTR*8)+3;
volatile bit T1DTG4                 @ ((unsigned)&TIM1DTR*8)+4;
volatile bit T1DTG5                 @ ((unsigned)&TIM1DTR*8)+5;
volatile bit T1DTG6                 @ ((unsigned)&TIM1DTR*8)+6;
volatile bit T1DTG7                 @ ((unsigned)&TIM1DTR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1DTG0                 : 1;
        unsigned	T1DTG1                 : 1;
        unsigned	T1DTG2                 : 1;
        unsigned	T1DTG3                 : 1;
        unsigned	T1DTG4                 : 1;
        unsigned	T1DTG5                 : 1;
        unsigned	T1DTG6                 : 1;
        unsigned	T1DTG7                 : 1;
    };
    struct {
        unsigned	T1DTG                  : 8;
    };
} TIM1DTRbits @ 0x29C;
#endif

// Register: TIM1OISR
volatile unsigned char           TIM1OISR            @ 0x29D;
// bit and bitfield definitions
volatile bit T1OIS1                @ ((unsigned)&TIM1OISR*8)+0;
volatile bit T1OIS1N               @ ((unsigned)&TIM1OISR*8)+1;
volatile bit T1OIS2                @ ((unsigned)&TIM1OISR*8)+2;
volatile bit T1OIS2N               @ ((unsigned)&TIM1OISR*8)+3;
volatile bit T1OIS3                @ ((unsigned)&TIM1OISR*8)+4;
volatile bit T1OIS3N               @ ((unsigned)&TIM1OISR*8)+5;
volatile bit T1OIS4                @ ((unsigned)&TIM1OISR*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1OIS1               : 1;
        unsigned	T1OIS1N              : 1;
        unsigned	T1OIS2               : 1;
        unsigned	T1OIS2N              : 1;
        unsigned	T1OIS3               : 1;
        unsigned	T1OIS3N              : 1;
        unsigned	T1OIS4               : 1;
    };
} TIM1OISRbits @ 0x29D;
#endif

// Register: TIM2CCR3H
volatile unsigned char           TIM2CCR3H            @ 0x29E;
// bit and bitfield definitions

// Register: TIM2CCR3L
volatile unsigned char           TIM2CCR3L            @ 0x29F;
// bit and bitfield definitions 
//
// Special function register definitions: Bank 6
//

// Register: TIM2CR1
volatile unsigned char           TIM2CR1            @ 0x30C;
// bit and bitfield definitions
volatile bit T2CEN                 @ ((unsigned)&TIM2CR1*8)+0;
volatile bit T2UDIS                @ ((unsigned)&TIM2CR1*8)+1;
volatile bit T2URS                 @ ((unsigned)&TIM2CR1*8)+2;
volatile bit T2OPM                 @ ((unsigned)&TIM2CR1*8)+3;
volatile bit T2ARPE                @ ((unsigned)&TIM2CR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CEN                : 1;
        unsigned	T2UDIS               : 1;
        unsigned	T2URS                : 1;
        unsigned	T2OPM                : 1;
        unsigned	                     : 3;
        unsigned	T2ARPE               : 1;
    };
} TIM2CR1bits @ 0x30C;
#endif

// Register: TIM2IER
volatile unsigned char           TIM2IER              @ 0x30D;
// bit and bitfield definitions
volatile bit T2UIE                 @ ((unsigned)&TIM2IER*8)+0;
volatile bit T2CC1IE               @ ((unsigned)&TIM2IER*8)+1;
volatile bit T2CC2IE               @ ((unsigned)&TIM2IER*8)+2;
volatile bit T2CC3IE               @ ((unsigned)&TIM2IER*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2UIE              : 1;
        unsigned	T2CC1IE              : 1;
        unsigned	T2CC2IE              : 1;
        unsigned	T2CC3IE              : 1;
    };
} TIM2IERbits @ 0x30D;
#endif

// Register: TIM2SR1
volatile unsigned char           TIM2SR1              @ 0x30E;
// bit and bitfield definitions
volatile bit T2UIF                 @ ((unsigned)&TIM2SR1*8)+0;
volatile bit T2CC1IF               @ ((unsigned)&TIM2SR1*8)+1;
volatile bit T2CC2IF               @ ((unsigned)&TIM2SR1*8)+2;
volatile bit T2CC3IF               @ ((unsigned)&TIM2SR1*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2UIF                : 1;
        unsigned	T2CC1IF              : 1;
        unsigned	T2CC2IF              : 1;
        unsigned	T2CC3IF              : 1;
    };
} TIM2SR1bits @ 0x30E;
#endif

// Register: TIM2SR2
volatile unsigned char           TIM2SR2              @ 0x30F;
// bit and bitfield definitions
volatile bit T2CC1OF               @ ((unsigned)&TIM2SR2*8)+1;
volatile bit T2CC2OF               @ ((unsigned)&TIM2SR2*8)+2;
volatile bit T2CC3OF               @ ((unsigned)&TIM2SR2*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                   : 1;
        unsigned	T2CC1OF              : 1;
        unsigned	T2CC2OF              : 1;
        unsigned	T2CC3OF              : 1;
    };
} TIM2SR2bits @ 0x30F;
#endif

// Register: TIM2EGR
volatile unsigned char           TIM2EGR              @ 0x310;
// bit and bitfield definitions
volatile bit T2UG                 @ ((unsigned)&TIM2EGR*8)+0;
volatile bit T2CC1G               @ ((unsigned)&TIM2EGR*8)+1;
volatile bit T2CC2G               @ ((unsigned)&TIM2EGR*8)+2;
volatile bit T2CC3G               @ ((unsigned)&TIM2EGR*8)+3;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2UG                 : 1;
        unsigned	T2CC1G               : 1;
        unsigned	T2CC2G               : 1;
        unsigned	T2CC3G               : 1;
    };
} TIM2EGRbits @ 0x310;
#endif


// Register: TIM2CCMR1
volatile unsigned char           TIM2CCMR1              @ 0x311;
// bit and bitfield definitions
volatile bit T2CC1S0               @ ((unsigned)&TIM2CCMR1*8)+0;
volatile bit T2CC1S1               @ ((unsigned)&TIM2CCMR1*8)+1;
volatile bit T2OC1PE               @ ((unsigned)&TIM2CCMR1*8)+3;
volatile bit T2OC1M0               @ ((unsigned)&TIM2CCMR1*8)+4;
volatile bit T2OC1M1               @ ((unsigned)&TIM2CCMR1*8)+5;
volatile bit T2OC1M2               @ ((unsigned)&TIM2CCMR1*8)+6;

volatile bit T2IC1PSC0             @ ((unsigned)&TIM2CCMR1*8)+2;
volatile bit T2IC1PSC1             @ ((unsigned)&TIM2CCMR1*8)+3;
volatile bit T2IC1F0               @ ((unsigned)&TIM2CCMR1*8)+4;
volatile bit T2IC1F1               @ ((unsigned)&TIM2CCMR1*8)+5;
volatile bit T2IC1F2               @ ((unsigned)&TIM2CCMR1*8)+6;
volatile bit T2IC1F3               @ ((unsigned)&TIM2CCMR1*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CC1S0              : 1;
        unsigned	T2CC1S1              : 1;
        unsigned	                     : 1;
        unsigned	T2OC1PE              : 1;
        unsigned	T2OC1M0              : 1;
        unsigned	T2OC1M1              : 1;
        unsigned	T2OC1M2              : 1;
    };
    struct {
        unsigned	                     : 1;
        unsigned	                     : 1;
        unsigned	T2IC1PSC0            : 1;
        unsigned	T2IC1PSC1            : 1;
        unsigned	T2IC1F0              : 1;
        unsigned	T2IC1F1              : 1;
        unsigned	T2IC1F2              : 1;
        unsigned	T2IC1F3              : 1;
    };
    struct {
        unsigned	T2CC1S               : 2;
        unsigned	                     : 2;
        unsigned	T2OC1M               : 3;
    };
    struct {
        unsigned	                   : 2;
        unsigned	T2IC1PSC           : 2;
        unsigned	T2IC1F             : 4;
    };
} TIM2CCMR1bits @ 0x311;
#endif


// Register: TIM2CCMR2
volatile unsigned char           TIM2CCMR2              @ 0x312;
// bit and bitfield definitions
volatile bit T2CC2S0               @ ((unsigned)&TIM2CCMR2*8)+0;
volatile bit T2CC2S1               @ ((unsigned)&TIM2CCMR2*8)+1;
volatile bit T2OC2PE               @ ((unsigned)&TIM2CCMR2*8)+3;
volatile bit T2OC2M0               @ ((unsigned)&TIM2CCMR2*8)+4;
volatile bit T2OC2M1               @ ((unsigned)&TIM2CCMR2*8)+5;
volatile bit T2OC2M2               @ ((unsigned)&TIM2CCMR2*8)+6;

volatile bit T2IC2PSC0             @ ((unsigned)&TIM2CCMR2*8)+2;
volatile bit T2IC2PSC1             @ ((unsigned)&TIM2CCMR2*8)+3;
volatile bit T2IC2F0               @ ((unsigned)&TIM2CCMR2*8)+4;
volatile bit T2IC2F1               @ ((unsigned)&TIM2CCMR2*8)+5;
volatile bit T2IC2F2               @ ((unsigned)&TIM2CCMR2*8)+6;
volatile bit T2IC2F3               @ ((unsigned)&TIM2CCMR2*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CC2S0              : 1;
        unsigned	T2CC2S1              : 1;
        unsigned	                   : 1;
        unsigned	T2OC2PE              : 1;
        unsigned	T2OC2M0              : 1;
        unsigned	T2OC2M1              : 1;
        unsigned	T2OC2M2              : 1;
    };
    struct {
        unsigned	                   : 1;
        unsigned	                   : 1;
        unsigned	T2IC2PSC0            : 1;
        unsigned	T2IC2PSC1            : 1;
        unsigned	T2IC2F0              : 1;
        unsigned	T2IC2F1              : 1;
        unsigned	T2IC2F2              : 1;
        unsigned	T2IC2F3              : 1;
    };
    struct {
        unsigned	T2CC2S             : 2;
        unsigned	                   : 2;
        unsigned	T2OC2M               : 3;
    };
    struct {
        unsigned	                   : 2;
        unsigned	T2IC2PSC             : 2;
        unsigned	T2IC2F               : 4;
    };
} TIM2CCMR2bits @ 0x312;
#endif

// Register: TIM2CCMR3
volatile unsigned char           TIM2CCMR3              @ 0x313;
// bit and bitfield definitions
volatile bit T2CC3S0               @ ((unsigned)&TIM2CCMR3*8)+0;
volatile bit T2CC3S1               @ ((unsigned)&TIM2CCMR3*8)+1;
volatile bit T2OC3PE               @ ((unsigned)&TIM2CCMR3*8)+3;
volatile bit T2OC3M0               @ ((unsigned)&TIM2CCMR3*8)+4;
volatile bit T2OC3M1               @ ((unsigned)&TIM2CCMR3*8)+5;
volatile bit T2OC3M2               @ ((unsigned)&TIM2CCMR3*8)+6;

volatile bit T2IC3PSC0             @ ((unsigned)&TIM2CCMR3*8)+2;
volatile bit T2IC3PSC1             @ ((unsigned)&TIM2CCMR3*8)+3;
volatile bit T2IC3F0               @ ((unsigned)&TIM2CCMR3*8)+4;
volatile bit T2IC3F1               @ ((unsigned)&TIM2CCMR3*8)+5;
volatile bit T2IC3F2               @ ((unsigned)&TIM2CCMR3*8)+6;
volatile bit T2IC3F3               @ ((unsigned)&TIM2CCMR3*8)+7;

#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CC3S0              : 1;
        unsigned	T2CC3S1              : 1;
        unsigned	                     : 1;
        unsigned	T2OC3PE              : 1;
        unsigned	T2OC3M0              : 1;
        unsigned	T2OC3M1              : 1;
        unsigned	T2OC3M2              : 1;
    };
    struct {
        unsigned	                     : 1;
        unsigned	                     : 1;
        unsigned	T2IC3PSC0            : 1;
        unsigned	T2IC3PSC1            : 1;
        unsigned	T2IC3F0              : 1;
        unsigned	T2IC3F1              : 1;
        unsigned	T2IC3F2              : 1;
        unsigned	T2IC3F3              : 1;
    };
    struct {
        unsigned	T2CC3S               : 2;
        unsigned	                     : 2;
        unsigned	T2OC3M               : 3;
    };
    struct {
        unsigned	                     : 2;
        unsigned	T2IC3PSC             : 2;
        unsigned	T2IC3F               : 4;
    };
} TIM2CCMR3bits @ 0x313;
#endif

// Register: TIM2CCER1
volatile unsigned char           TIM2CCER1             @ 0x314;
// bit and bitfield definitions
volatile bit T2CC1E               @ ((unsigned)&TIM2CCER1*8)+0;
volatile bit T2CC1P               @ ((unsigned)&TIM2CCER1*8)+1;
volatile bit T2CC2E               @ ((unsigned)&TIM2CCER1*8)+4;
volatile bit T2CC2P               @ ((unsigned)&TIM2CCER1*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CC1E               : 1;
        unsigned	T2CC1P               : 1;
        unsigned	                     : 2;
        unsigned	T2CC2E               : 1;
        unsigned	T2CC2P               : 1;
    };
} TIM2CCER1bits @ 0x314;
#endif

// Register: TIM2CCER2
volatile unsigned char           TIM2CCER2             @ 0x315;
// bit and bitfield definitions
volatile bit T2CC3E               @ ((unsigned)&TIM2CCER2*8)+0;
volatile bit T2CC3P               @ ((unsigned)&TIM2CCER2*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2CC3E               : 1;
        unsigned	T2CC3P               : 1;
    };
} TIM2CCER2bits @ 0x315;
#endif

// Register: TIM2CNTRH
volatile unsigned char           TIM2CNTRH             @ 0x316;
// bit and bitfield definitions

// Register: TIM2CNTRL
volatile unsigned char           TIM2CNTRL             @ 0x317;
// bit and bitfield definitions

// Register: TIM2PSCR
volatile unsigned char           TIM2PSCR         @ 0x318;
// bit and bitfield definitions
volatile bit T2PSC0              @ ((unsigned)&TIM2PSCR*8)+0;
volatile bit T2PSC1              @ ((unsigned)&TIM2PSCR*8)+1;
volatile bit T2PSC2              @ ((unsigned)&TIM2PSCR*8)+2;
volatile bit T2PSC3              @ ((unsigned)&TIM2PSCR*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T2PSC0              : 1;
        unsigned	T2PSC1              : 1;
        unsigned	T2PSC2              : 1;
        unsigned	T2PSC3              : 1;
    };
    struct {
        unsigned	T2PSC               : 4;
    };
} TIM2PSCRbits @ 0x318;
#endif

// Register: TIM2ARRH
volatile unsigned char           TIM2ARRH              @ 0x319;
// bit and bitfield definitions

// Register: TIM2ARRL
volatile unsigned char           TIM2ARRL              @ 0x31A;
// bit and bitfield definitions

// Register: TIM2CCR1H
volatile unsigned char           TIM2CCR1H              @ 0x31B;
// bit and bitfield definitions

// Register: TIM2CCR1L
volatile unsigned char           TIM2CCR1L              @ 0x31C;
// bit and bitfield definitions

// Register: TIM2CCR2H
volatile unsigned char           TIM2CCR2H              @ 0x31D;
// bit and bitfield definitions

// Register: TIM2CCR2L
volatile unsigned char           TIM2CCR2L              @ 0x31E;
// bit and bitfield definitions

// Register: TCKSRC
volatile unsigned char           TCKSRC         @ 0x31F;
// bit and bitfield definitions
volatile bit T1CKSRC0              @ ((unsigned)&TCKSRC*8)+0;
volatile bit T1CKSRC1              @ ((unsigned)&TCKSRC*8)+1;
volatile bit T1CKSRC2              @ ((unsigned)&TCKSRC*8)+2;
volatile bit T2CKSRC0              @ ((unsigned)&TCKSRC*8)+4;
volatile bit T2CKSRC1              @ ((unsigned)&TCKSRC*8)+5;
volatile bit T2CKSRC2              @ ((unsigned)&TCKSRC*8)+6;
volatile bit LFMOD                 @ ((unsigned)&TCKSRC*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	T1CKSRC0              : 1;
        unsigned	T1CKSRC1              : 1;
        unsigned	T1CKSRC2              : 1;
        unsigned	                      : 1;
        unsigned	T2CKSRC0              : 1;
        unsigned	T2CKSRC1              : 1;
        unsigned	T2CKSRC2              : 1;
        unsigned	LFMOD                 : 1;
    };
    struct {
        unsigned	T1CKSRC               : 3;
        unsigned	                      : 1;
        unsigned	T2CKSRC               : 3;
    };
} TCKSRCbits @ 0x31F;
#endif
//
// Special function register definitions: Bank 7
//

//
// Special function register definitions: Bank 8
//

// Register: I2CCR1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCR1               @ 0x40C;
// bit and bitfield definitions
volatile bit MASTER               @ ((unsigned)&I2CCR1*8)+0;
volatile bit SPEED                @ ((unsigned)&I2CCR1*8)+1;
volatile bit SLV10B               @ ((unsigned)&I2CCR1*8)+3;
volatile bit MST10B               @ ((unsigned)&I2CCR1*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	MASTER              : 1;
        unsigned	SPEED               : 1;
        unsigned	                    : 1;
        unsigned	SLV10B              : 1;
        unsigned	MST10B              : 1;
    };
} I2CCR1bits @ 0x40C;
#endif

// Register: I2CCR2
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCR2               @ 0x40D;
// bit and bitfield definitions
volatile bit RXHLD                 @ ((unsigned)&I2CCR2*8)+1;
volatile bit SNACK                 @ ((unsigned)&I2CCR2*8)+4;
volatile bit AGCALL                @ ((unsigned)&I2CCR2*8)+5;
volatile bit SOFTRST               @ ((unsigned)&I2CCR2*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                    : 1;
        unsigned	RXHLD               : 1;
        unsigned	                    : 2;
        unsigned	SNACK               : 1;
        unsigned	AGCALL              : 1;
        unsigned	SOFTRST             : 1;
    };
} I2CCR2bits @ 0x40D;
#endif

// Register: I2CEN
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCR3               @ 0x40E;
// bit and bitfield definitions
volatile bit ENABLE                 @ ((unsigned)&I2CCR3*8)+0;
volatile bit EVSTRE                 @ ((unsigned)&I2CCR3*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ENABLE              : 1;
        unsigned	                    : 1;
        unsigned	EVSTRE              : 1;
    };
} I2CCR3bits @ 0x40E;
#endif

// Register: I2COARL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2COARL               @ 0x40F;
// bit and bitfield definitions
volatile bit ADD0                   @ ((unsigned)&I2COARL*8)+0;
volatile bit ADD1                   @ ((unsigned)&I2COARL*8)+1;
volatile bit ADD2                   @ ((unsigned)&I2COARL*8)+2;
volatile bit ADD3                   @ ((unsigned)&I2COARL*8)+3;
volatile bit ADD4                   @ ((unsigned)&I2COARL*8)+4;
volatile bit ADD5                   @ ((unsigned)&I2COARL*8)+5;
volatile bit ADD6                   @ ((unsigned)&I2COARL*8)+6;
volatile bit ADD7                   @ ((unsigned)&I2COARL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADD0              : 1;
        unsigned	ADD1              : 1;
        unsigned	ADD2              : 1;
        unsigned	ADD3              : 1;
        unsigned	ADD4              : 1;
        unsigned	ADD5              : 1;
        unsigned	ADD6              : 1;
        unsigned	ADD7              : 1;
    };
    struct {
        unsigned	ADD               : 8;
    };
} I2COARLbits @ 0x40E;
#endif

// Register: I2COARH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2COARH               @ 0x410;
// bit and bitfield definitions
volatile bit ADD8                   @ ((unsigned)&I2COARH*8)+0;
volatile bit ADD9                   @ ((unsigned)&I2COARH*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ADD8              : 1;
        unsigned	ADD9              : 1;
    };
} I2COARHbits @ 0x410;
#endif

// Register: I2CFREQ
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CFREQ               @ 0x411;
// bit and bitfield definitions
volatile bit FREQ0                   @ ((unsigned)&I2CFREQ*8)+0;
volatile bit FREQ1                   @ ((unsigned)&I2CFREQ*8)+1;
volatile bit FREQ2                   @ ((unsigned)&I2CFREQ*8)+2;
volatile bit FREQ3                   @ ((unsigned)&I2CFREQ*8)+3;
volatile bit FREQ4                   @ ((unsigned)&I2CFREQ*8)+4;
volatile bit FREQ5                   @ ((unsigned)&I2CFREQ*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	FREQ0              : 1;
        unsigned	FREQ1              : 1;
        unsigned	FREQ2              : 1;
        unsigned	FREQ3              : 1;
        unsigned	FREQ4              : 1;
        unsigned	FREQ5              : 1;
    };
    struct {
        unsigned	FREQ               : 6;
    };
} I2CFREQbits @ 0x411;
#endif

// Register: I2CDR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CDR               @ 0x412;
// bit and bitfield definitions

// Register: I2CCMD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCMD               @ 0x413;
// bit and bitfield definitions
volatile bit MSTDIR                    @ ((unsigned)&I2CCMD*8)+0;
volatile bit STOP                      @ ((unsigned)&I2CCMD*8)+1;
volatile bit RESTART                   @ ((unsigned)&I2CCMD*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	MSTDIR              : 1;
        unsigned	STOP                : 1;
        unsigned	RESTART             : 1;
    };
} I2CCMDbits @ 0x413;
#endif

// Register: I2CCCRL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCCRL               @ 0x414;
// bit and bitfield definitions
volatile bit CCR0                    @ ((unsigned)&I2CCCRL*8)+0;
volatile bit CCR1                    @ ((unsigned)&I2CCCRL*8)+1;
volatile bit CCR2                    @ ((unsigned)&I2CCCRL*8)+2;
volatile bit CCR3                    @ ((unsigned)&I2CCCRL*8)+3;
volatile bit CCR4                    @ ((unsigned)&I2CCCRL*8)+4;
volatile bit CCR5                    @ ((unsigned)&I2CCCRL*8)+5;
volatile bit CCR6                    @ ((unsigned)&I2CCCRL*8)+6;
volatile bit CCR7                    @ ((unsigned)&I2CCCRL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCR0                : 1;
        unsigned	CCR1                : 1;
        unsigned	CCR2                : 1;
        unsigned	CCR3                : 1;
        unsigned	CCR4                : 1;
        unsigned	CCR5                : 1;
        unsigned	CCR6                : 1;
        unsigned	CCR7                : 1;
    };
    struct {
        unsigned	CCR                 : 7;
    };
} I2CCCRLbits @ 0x414;
#endif

// Register: I2CCCRL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CCCRH               @ 0x415;
// bit and bitfield definitions
volatile bit CCR8                    @ ((unsigned)&I2CCCRH*8)+0;
volatile bit CCR9                    @ ((unsigned)&I2CCCRH*8)+1;
volatile bit CCR10                   @ ((unsigned)&I2CCCRH*8)+2;
volatile bit CCR11                   @ ((unsigned)&I2CCCRH*8)+3;
volatile bit DUTY                    @ ((unsigned)&I2CCCRH*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CCR8                : 1;
        unsigned	CCR9                : 1;
        unsigned	CCR10               : 1;
        unsigned	CCR11               : 1;
        unsigned	                    : 2;
        unsigned	DUTY                : 1;
    };
} I2CCCRHbits @ 0x415;
#endif

// Register: I2CITR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CITR               @ 0x416;
// bit and bitfield definitions
volatile bit ITERREN                 @ ((unsigned)&I2CITR*8)+0;
volatile bit ITEVEN                  @ ((unsigned)&I2CITR*8)+1;
volatile bit ITBUFEN                 @ ((unsigned)&I2CITR*8)+2;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ITERREN               : 1;
        unsigned	ITEVEN                : 1;
        unsigned	ITBUFEN               : 1;
    };
} I2CITRbits @ 0x416;
#endif

// Register: I2CSR1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CSR1               @ 0x417;
// bit and bitfield definitions
volatile bit SBF                    @ ((unsigned)&I2CSR1*8)+0;
volatile bit ADDRF                  @ ((unsigned)&I2CSR1*8)+1;
volatile bit ADD10F                 @ ((unsigned)&I2CSR1*8)+3;
volatile bit STOPF                  @ ((unsigned)&I2CSR1*8)+4;
volatile bit IICRXNE                @ ((unsigned)&I2CSR1*8)+6;
volatile bit IICTXE                 @ ((unsigned)&I2CSR1*8)+7;

volatile bit ADDF                   @ ((unsigned)&I2CSR1*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SBF               : 1;
        unsigned	ADDRF             : 1;
        unsigned	                  : 1;
        unsigned	ADD10F            : 1;
        unsigned	STOPF             : 1;
        unsigned	                  : 1;
        unsigned	IICRXNE           : 1;
        unsigned	IICTXE            : 1;
    };
    struct {
        unsigned	                  : 1;
        unsigned	ADDF              : 1;
    };
} I2CSR1bits @ 0x417;
#endif

// Register: I2CSR2
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CSR2               @ 0x418;
// bit and bitfield definitions
volatile bit BERR                   @ ((unsigned)&I2CSR2*8)+0;
volatile bit ARLO                   @ ((unsigned)&I2CSR2*8)+1;
volatile bit AF                     @ ((unsigned)&I2CSR2*8)+2;
volatile bit OVR                    @ ((unsigned)&I2CSR2*8)+3;
volatile bit TXARBT                 @ ((unsigned)&I2CSR2*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	BERR              : 1;
        unsigned	ARLO              : 1;
        unsigned	AF                : 1;
        unsigned	OVR               : 1;
        unsigned	TXARBT            : 1;
    };
} I2CSR2bits @ 0x418;
#endif

// Register: I2CSR3
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           I2CSR3               @ 0x419;
// bit and bitfield definitions
volatile bit RXHOLD                 @ ((unsigned)&I2CSR3*8)+0;
volatile bit ACTIVE                 @ ((unsigned)&I2CSR3*8)+1;
volatile bit RDREQ                  @ ((unsigned)&I2CSR3*8)+2;
volatile bit GCALL                  @ ((unsigned)&I2CSR3*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	RXHOLD            : 1;
        unsigned	ACTIVE            : 1;
        unsigned	RDREQ             : 1;
        unsigned	                  : 2;
        unsigned	GCALL             : 1;
    };
} I2CSR3bits @ 0x419;
#endif


// Register: ADCON3
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           ADCON3               @ 0x41A;
// bit and bitfield definitions
volatile bit ELVDS0                 @ ((unsigned)&ADCON3*8)+0;
volatile bit ELVDS1                 @ ((unsigned)&ADCON3*8)+1;
volatile bit AN4SELB                @ ((unsigned)&ADCON3*8)+2;
volatile bit LEBADT                 @ ((unsigned)&ADCON3*8)+3;
volatile bit ADCMPO                 @ ((unsigned)&ADCON3*8)+4;
volatile bit ADCMPEN                @ ((unsigned)&ADCON3*8)+5;
volatile bit ADCMPOP                @ ((unsigned)&ADCON3*8)+6;
volatile bit ADFBEN                 @ ((unsigned)&ADCON3*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	ELVDS0            : 1;
        unsigned	ELVDS1            : 1;
        unsigned	AN4SELB           : 1;
        unsigned	LEBADT            : 1;
        unsigned	ADCMPO            : 1;
        unsigned	ADCMPEN           : 1;
        unsigned	ADCMPOP           : 1;
        unsigned	ADFBEN            : 1;
    };
} ADCON3bits @ 0x41A;
#endif


// Register: ADCON3
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           ADCMPH               @ 0x41B;
// bit and bitfield definitions


// Register: ADCON3
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           LEBCON               @ 0x41C;
// bit and bitfield definitions
volatile bit BKS0                 @ ((unsigned)&LEBCON*8)+0;
volatile bit BKS1                 @ ((unsigned)&LEBCON*8)+1;
volatile bit KBS2                 @ ((unsigned)&LEBCON*8)+2;
volatile bit EDGS                @ ((unsigned)&LEBCON*8)+3;
volatile bit LEBCH0               @ ((unsigned)&LEBCON*8)+5;
volatile bit LEBCH1               @ ((unsigned)&LEBCON*8)+6;
volatile bit LEBEN                @ ((unsigned)&LEBCON*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	BKS0              : 1;
        unsigned	BKS1              : 1;
        unsigned	KBS2              : 1;
        unsigned	EDGS              : 1;
        unsigned	                  : 1;
        unsigned	LEBCH0            : 1;
        unsigned	LEBCH1            : 1;
        unsigned	LEBEN             : 1;
    };
} LEBCONbits @ 0x41C;
#endif


// Register: MSCKCON
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           MSCKCON               @ 0x41D;
// bit and bitfield definitions
volatile bit CKCNTI                 @ ((unsigned)&MSCKCON*8)+0;
volatile bit CKMAVG                 @ ((unsigned)&MSCKCON*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	CKCNTI              : 1;
        unsigned	CKMAVG              : 1;
    };
} MSCKCONbits @ 0x41D;
#endif


// Register: SOSCPRL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           SOSCPRL               @ 0x41E;
// bit and bitfield definitions
volatile bit SOSCPR0                 @ ((unsigned)&SOSCPRL*8)+0;
volatile bit SOSCPR1                 @ ((unsigned)&SOSCPRL*8)+1;
volatile bit SOSCPR2                 @ ((unsigned)&SOSCPRL*8)+2;
volatile bit SOSCPR3                 @ ((unsigned)&SOSCPRL*8)+3;
volatile bit SOSCPR4                 @ ((unsigned)&SOSCPRL*8)+4;
volatile bit SOSCPR5                 @ ((unsigned)&SOSCPRL*8)+5;
volatile bit SOSCPR6                 @ ((unsigned)&SOSCPRL*8)+6;
volatile bit SOSCPR7                 @ ((unsigned)&SOSCPRL*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	SOSCPR              : 8;
    };
} SOSCPRLbits @ 0x41E;
#endif

// Register: SOSCPRL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           SOSCPRH               @ 0x41F;
// bit and bitfield definitions
volatile bit SOSCPR8                  @ ((unsigned)&SOSCPRH*8)+0;
volatile bit SOSCPR9                  @ ((unsigned)&SOSCPRH*8)+1;
volatile bit SOSCPR10                 @ ((unsigned)&SOSCPRH*8)+2;
volatile bit SOSCPR11                 @ ((unsigned)&SOSCPRH*8)+3;

//
// Special function register definitions: Bank 9
//
 
// Register: UR1DATAL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1DATAL               @ 0x48C;
// bit and bitfield definitions
//

// Register: UR1DATAH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1DATAH               @ 0x48D;
// bit and bitfield definitions
volatile bit UR1DATAH0                 @ ((unsigned)&UR1DATAH*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1DATAH0            : 1;
    };
} UR1DATAHbits @ 0x48D;
#endif

// Register: UR1IER
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1IER               @ 0x48E;
// bit and bitfield definitions
volatile bit UR1RXNE                   @ ((unsigned)&UR1IER*8)+0;
volatile bit UR1TE                     @ ((unsigned)&UR1IER*8)+1;
volatile bit UR1RXSE                   @ ((unsigned)&UR1IER*8)+2;
volatile bit UR1IDELE                  @ ((unsigned)&UR1IER*8)+3;
volatile bit UR1TCEN                   @ ((unsigned)&UR1IER*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1RXNE              : 1;
        unsigned	UR1TE                : 1;
        unsigned	UR1RXSE              : 1;
        unsigned	UR1IDELE             : 1;
        unsigned	                     : 1;
        unsigned	UR1TCEN              : 1;
    };
} UR1IERbits @ 0x48E;
#endif

// Register: UR1LCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1LCR               @ 0x48F;
// bit and bitfield definitions
volatile bit UR1LTH                    @ ((unsigned)&UR1LCR*8)+0;
volatile bit UR1STOP                 @ ((unsigned)&UR1LCR*8)+2;
volatile bit UR1PEN                    @ ((unsigned)&UR1LCR*8)+3;
volatile bit UR1EVEN                   @ ((unsigned)&UR1LCR*8)+4;
volatile bit UR1BKREQ                  @ ((unsigned)&UR1LCR*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1LTH               : 1;
        unsigned	                     : 1;
        unsigned	UR1STOP              : 1;
        unsigned	UR1PEN               : 1;
        unsigned	UR1EVEN              : 1;
        unsigned	                     : 1;
        unsigned	UR1BKREQ             : 1;
    };
} UR1LCRbits @ 0x48F;
#endif

// Register: UR1LCREXT
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1LCREXT               @ 0x490;
// bit and bitfield definitions
volatile bit UR1EXTEN                  @ ((unsigned)&UR1LCREXT*8)+0;
volatile bit UR1RWU                    @ ((unsigned)&UR1LCREXT*8)+1;
volatile bit UR1TDEN                   @ ((unsigned)&UR1LCREXT*8)+2;
volatile bit VTHTRIM1                  @ ((unsigned)&UR1LCREXT*8)+3;
volatile bit VTHTRIM1X                 @ ((unsigned)&UR1LCREXT*8)+4;
volatile bit TSL0                      @ ((unsigned)&UR1LCREXT*8)+5;
volatile bit TSL1                      @ ((unsigned)&UR1LCREXT*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1EXTEN             : 1;
        unsigned	UR1RWU               : 1; 
        unsigned	UR1TDEN              : 1;
        unsigned	VTHTRIM1             : 1;
        unsigned	VTHTRIM1X            : 1;
        unsigned	TSL0                 : 1;
        unsigned	TSL1                 : 1;
    };
    struct {
        unsigned	                     : 5;
        unsigned	TSL                  : 2;
    };
} UR1LCREXTbits @ 0x490;
#endif

// Register: UR1MCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1MCR               @ 0x491;
// bit and bitfield definitions
volatile bit UR1SIREN                  @ ((unsigned)&UR1MCR*8)+0;
volatile bit UR1HDSEL                  @ ((unsigned)&UR1MCR*8)+1;
volatile bit UR1WAKE                   @ ((unsigned)&UR1MCR*8)+2;
volatile bit UR1RXEN                   @ ((unsigned)&UR1MCR*8)+3;
volatile bit UR1TXEN                   @ ((unsigned)&UR1MCR*8)+4;
volatile bit UR1SIRLP                  @ ((unsigned)&UR1MCR*8)+5;
volatile bit RS485EN                   @ ((unsigned)&UR1MCR*8)+6;
volatile bit RE                        @ ((unsigned)&UR1MCR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1SIREN             : 1;
        unsigned	UR1HDSEL             : 1; 
        unsigned	UR1WAKE              : 1; 
        unsigned	UR1RXEN              : 1; 
        unsigned	UR1TXEN              : 1; 
        unsigned	UR1SIRLP             : 1; 
        unsigned	RS485EN              : 1; 
        unsigned	RE                   : 1; 
    };
} UR1MCRbits @ 0x491;
#endif

// Register: UR1LSR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1LSR               @ 0x492;
// bit and bitfield definitions
volatile bit UR1RXNEF                  @ ((unsigned)&UR1LSR*8)+0;
volatile bit UR1OVERF                  @ ((unsigned)&UR1LSR*8)+1;
volatile bit UR1PEF                    @ ((unsigned)&UR1LSR*8)+2;
volatile bit UR1FEF                    @ ((unsigned)&UR1LSR*8)+3;
volatile bit UR1BKF                    @ ((unsigned)&UR1LSR*8)+4;
volatile bit UR1TXEF                   @ ((unsigned)&UR1LSR*8)+5;
volatile bit UR1IDLEF                  @ ((unsigned)&UR1LSR*8)+6;
volatile bit UR1ADDRF                @ ((unsigned)&UR1LSR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1RXNEF             : 1;
        unsigned	UR1OVERF             : 1; 
        unsigned	UR1PEF               : 1; 
        unsigned	UR1FEF               : 1; 
        unsigned	UR1BKF               : 1; 
        unsigned	UR1TXEF              : 1; 
        unsigned	UR1IDLEF             : 1; 
        unsigned	UR1ADDRF           : 1; 
    };
} UR1LSRbits @ 0x492;
#endif

// Register: UR1RAR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1RAR               @ 0x493;
// bit and bitfield definitions

// Register: UR1DLL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1DLL               @ 0x494;
// bit and bitfield definitions

// Register: UR1DLH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1DLH               @ 0x495;
// bit and bitfield definitions

// Register: UR1ABCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1ABCR               @ 0x496;
// bit and bitfield definitions
volatile bit UR1ABREN                  @ ((unsigned)&UR1ABCR*8)+0;
volatile bit UR1ABRF                   @ ((unsigned)&UR1ABCR*8)+1;
volatile bit UR1ABRM                   @ ((unsigned)&UR1ABCR*8)+2;
volatile bit UR1ABRE                   @ ((unsigned)&UR1ABCR*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1ABREN             : 1;
        unsigned	UR1ABRF              : 1; 
        unsigned	UR1ABRM              : 1; 
        unsigned	UR1ABRE              : 1; 
    };
} UR1ABCRbits @ 0x496;
#endif

// Register: UR1SYNCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1SYNCR               @ 0x497;
// bit and bitfield definitions
volatile bit UR1SYNEN                  @ ((unsigned)&UR1SYNCR*8)+0;
volatile bit UR1CPOL                   @ ((unsigned)&UR1SYNCR*8)+1;
volatile bit UR1CPHA                   @ ((unsigned)&UR1SYNCR*8)+2;
volatile bit UR1LBCL                   @ ((unsigned)&UR1SYNCR*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1SYNEN             : 1;
        unsigned	UR1CPOL              : 1; 
        unsigned	UR1CPHA              : 1; 
        unsigned	UR1LBCL              : 1; 
    };
} UR1SYNCRbits @ 0x497;
#endif

// Register: UR1LINCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1LINCR               @ 0x498;
// bit and bitfield definitions
volatile bit UR1BLTH0                  @ ((unsigned)&UR1LINCR*8)+0;
volatile bit UR1BLTH1                  @ ((unsigned)&UR1LINCR*8)+1;
volatile bit UR1BLTH2                  @ ((unsigned)&UR1LINCR*8)+2;
volatile bit UR1BLTH3                  @ ((unsigned)&UR1LINCR*8)+3;
volatile bit UR1LINEN                  @ ((unsigned)&UR1LINCR*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1BLTH0             : 1;
        unsigned	UR1BLTH1             : 1; 
        unsigned	UR1BLTH2             : 1; 
        unsigned	UR1BLTH3             : 1; 
        unsigned	UR1LINEN             : 1; 
    };
    struct {
        unsigned	UR1BLTH              : 4;
    };
} UR1LINCRbits @ 0x498;
#endif

// Register: UR1SDCR0
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1SDCR0               @ 0x499;
// bit and bitfield definitions
volatile bit UR1SDEN                   @ ((unsigned)&UR1SDCR0*8)+4;
volatile bit UR1CKOE                   @ ((unsigned)&UR1SDCR0*8)+5;
volatile bit UR1NACK                   @ ((unsigned)&UR1SDCR0*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 4;
        unsigned	UR1SDEN              : 1; 
        unsigned	UR1CKOE              : 1; 
        unsigned	UR1NACK              : 1; 
    };
} UR1SDCR0bits @ 0x499;
#endif

// Register: UR1SDCR1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1SDCR1               @ 0x49A;
// bit and bitfield definitions
volatile bit UR1GT0                   @ ((unsigned)&UR1SDCR1*8)+0;
volatile bit UR1GT1                   @ ((unsigned)&UR1SDCR1*8)+1;
volatile bit UR1GT2                   @ ((unsigned)&UR1SDCR1*8)+2;
volatile bit UR1GT3                   @ ((unsigned)&UR1SDCR1*8)+3;
volatile bit UR1GT4                   @ ((unsigned)&UR1SDCR1*8)+4;
volatile bit UR1GT5                   @ ((unsigned)&UR1SDCR1*8)+5;
volatile bit UR1GT6                   @ ((unsigned)&UR1SDCR1*8)+6;
volatile bit UR1GT7                   @ ((unsigned)&UR1SDCR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1GT0               : 1;
        unsigned	UR1GT1               : 1;
        unsigned	UR1GT2               : 1;
        unsigned	UR1GT3               : 1;
        unsigned	UR1GT4               : 1;
        unsigned	UR1GT5               : 1;
        unsigned	UR1GT6               : 1;
        unsigned	UR1GT7               : 1;
    };
    struct {
        unsigned	UR1GT                : 8;
    };
} UR1SDCR1bits @ 0x49A;
#endif

// Register: UR1SDCR2
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1SDCR2               @ 0x49B;
// bit and bitfield definitions
volatile bit UR1PSC0                   @ ((unsigned)&UR1SDCR2*8)+0;
volatile bit UR1PSC1                   @ ((unsigned)&UR1SDCR2*8)+1;
volatile bit UR1PSC2                   @ ((unsigned)&UR1SDCR2*8)+2;
volatile bit UR1PSC3                   @ ((unsigned)&UR1SDCR2*8)+3;
volatile bit UR1PSC4                   @ ((unsigned)&UR1SDCR2*8)+4;
volatile bit UR1PSC5                   @ ((unsigned)&UR1SDCR2*8)+5;
volatile bit UR1PSC6                   @ ((unsigned)&UR1SDCR2*8)+6;
volatile bit UR1PSC7                   @ ((unsigned)&UR1SDCR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1PSC0               : 1;
        unsigned	UR1PSC1               : 1;
        unsigned	UR1PSC2               : 1;
        unsigned	UR1PSC3               : 1;
        unsigned	UR1PSC4               : 1;
        unsigned	UR1PSC5               : 1;
        unsigned	UR1PSC6               : 1;
        unsigned	UR1PSC7               : 1;
    };
    struct {
        unsigned	UR1PSC                : 8;
    };
} UR1SDCR2bits @ 0x49B;
#endif

// Register: UR1TC
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1TC               @ 0x49C;
// bit and bitfield definitions
volatile bit UR1TCF                   @ ((unsigned)&UR1TC*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR1TCF               : 1;
    };
} UR1TCbits @ 0x49C;
#endif

// Register: UR1RSM
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR1RSM               @ 0x49D;
// bit and bitfield definitions
volatile bit AS                   @ ((unsigned)&UR1RSM*8)+0;
volatile bit ABSEN                @ ((unsigned)&UR1RSM*8)+2;
volatile bit ADR                  @ ((unsigned)&UR1RSM*8)+3;
volatile bit BDR                  @ ((unsigned)&UR1RSM*8)+4;
volatile bit ASINK                @ ((unsigned)&UR1RSM*8)+5;
volatile bit BSINK                @ ((unsigned)&UR1RSM*8)+6;
volatile bit HTF                  @ ((unsigned)&UR1RSM*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	AS               : 1;
        unsigned	                 : 1;
        unsigned	ABSEN            : 1;
        unsigned	ADR              : 1;
        unsigned	BDR              : 1;
        unsigned	ASINK            : 1;
        unsigned	BSINK            : 1;
        unsigned	HTF              : 1;
    };
} UR1RSMbits @ 0x49D;
#endif

//
// Special function register definitions: Bank 10
//
 
// Register: UR2DATAL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2DATAL               @ 0x50C;
// bit and bitfield definitions
//

// Register: UR2DATAH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2DATAH               @ 0x50D;
// bit and bitfield definitions
volatile bit UR2DATAH0                 @ ((unsigned)&UR2DATAH*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2DATAH0            : 1;
    };
} UR2DATAHbits @ 0x50D;
#endif

// Register: UR2IER
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2IER               @ 0x50E;
// bit and bitfield definitions
volatile bit UR2RXNE                   @ ((unsigned)&UR2IER*8)+0;
volatile bit UR2TE                     @ ((unsigned)&UR2IER*8)+1;
volatile bit UR2RXSE                   @ ((unsigned)&UR2IER*8)+2;
volatile bit UR2IDELE                  @ ((unsigned)&UR2IER*8)+3;
volatile bit UR2TCEN                   @ ((unsigned)&UR2IER*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2RXNE              : 1;
        unsigned	UR2TE                : 1;
        unsigned	UR2RXSE              : 1;
        unsigned	UR2IDELE             : 1;
        unsigned	                     : 1;
        unsigned	UR2TCEN              : 1;
    };
} UR2IERbits @ 0x50E;
#endif

// Register: UR2LCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2LCR               @ 0x50F;
// bit and bitfield definitions
volatile bit UR2LTH                    @ ((unsigned)&UR2LCR*8)+0;
volatile bit UR2STOP                 @ ((unsigned)&UR2LCR*8)+2;
volatile bit UR2PEN                    @ ((unsigned)&UR2LCR*8)+3;
volatile bit UR2EVEN                   @ ((unsigned)&UR2LCR*8)+4;
volatile bit UR2BKREQ                  @ ((unsigned)&UR2LCR*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2LTH               : 1;
        unsigned	                     : 1;
        unsigned	UR2STOP              : 1;
        unsigned	UR2PEN               : 1;
        unsigned	UR2EVEN              : 1;
        unsigned	                     : 1;
        unsigned	UR2BKREQ             : 1;
    };
} UR2LCRbits @ 0x50F;
#endif

// Register: UR2LCREXT
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2LCREXT               @ 0x510;
// bit and bitfield definitions
volatile bit UR2EXTEN                  @ ((unsigned)&UR2LCREXT*8)+0;
volatile bit UR2RWU                    @ ((unsigned)&UR2LCREXT*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2EXTEN             : 1;
        unsigned	UR2RWU               : 1; 
    };
} UR2LCREXTbits @ 0x510;
#endif

// Register: UR2MCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2MCR               @ 0x511;
// bit and bitfield definitions
volatile bit UR2SIREN                  @ ((unsigned)&UR2MCR*8)+0;
volatile bit UR2HDSEL                  @ ((unsigned)&UR2MCR*8)+1;
volatile bit UR2WAKE                   @ ((unsigned)&UR2MCR*8)+2;
volatile bit UR2RXEN                   @ ((unsigned)&UR2MCR*8)+3;
volatile bit UR2TXEN                   @ ((unsigned)&UR2MCR*8)+4;
volatile bit UR2SIRLP                  @ ((unsigned)&UR2MCR*8)+5;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2SIREN             : 1;
        unsigned	UR2HDSEL             : 1; 
        unsigned	UR2WAKE              : 1; 
        unsigned	UR2RXEN              : 1; 
        unsigned	UR2TXEN              : 1; 
        unsigned	UR2SIRLP             : 1; 
    };
} UR2MCRbits @ 0x511;
#endif

// Register: UR2LSR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2LSR               @ 0x512;
// bit and bitfield definitions
volatile bit UR2RXNEF                  @ ((unsigned)&UR2LSR*8)+0;
volatile bit UR2OVERF                  @ ((unsigned)&UR2LSR*8)+1;
volatile bit UR2PEF                    @ ((unsigned)&UR2LSR*8)+2;
volatile bit UR2FEF                    @ ((unsigned)&UR2LSR*8)+3;
volatile bit UR2BKF                    @ ((unsigned)&UR2LSR*8)+4;
volatile bit UR2TXEF                   @ ((unsigned)&UR2LSR*8)+5;
volatile bit UR2IDLEF                  @ ((unsigned)&UR2LSR*8)+6;
volatile bit UR2ADDRF                @ ((unsigned)&UR2LSR*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2RXNEF             : 1;
        unsigned	UR2OVERF             : 1; 
        unsigned	UR2PEF               : 1; 
        unsigned	UR2FEF               : 1; 
        unsigned	UR2BKF               : 1; 
        unsigned	UR2TXEF              : 1; 
        unsigned	UR2IDLEF             : 1; 
        unsigned	UR2ADDRF           : 1; 
    };
} UR2LSRbits @ 0x512;
#endif

// Register: UR2RAR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2RAR               @ 0x513;
// bit and bitfield definitions

// Register: UR2DLL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2DLL               @ 0x514;
// bit and bitfield definitions

// Register: UR2DLH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2DLH               @ 0x515;
// bit and bitfield definitions

// Register: UR2ABCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2ABCR               @ 0x516;
// bit and bitfield definitions
volatile bit UR2ABREN                  @ ((unsigned)&UR2ABCR*8)+0;
volatile bit UR2ABRF                   @ ((unsigned)&UR2ABCR*8)+1;
volatile bit UR2ABRM                   @ ((unsigned)&UR2ABCR*8)+2;
volatile bit UR2ABRE                   @ ((unsigned)&UR2ABCR*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2ABREN             : 1;
        unsigned	UR2ABRF              : 1; 
        unsigned	UR2ABRM              : 1; 
        unsigned	UR2ABRE              : 1; 
    };
} UR2ABCRbits @ 0x516;
#endif

// Register: UR2SYNCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2SYNCR               @ 0x517;
// bit and bitfield definitions
volatile bit UR2SYNEN                  @ ((unsigned)&UR2SYNCR*8)+0;
volatile bit UR2CPOL                   @ ((unsigned)&UR2SYNCR*8)+1;
volatile bit UR2CPHA                   @ ((unsigned)&UR2SYNCR*8)+2;
volatile bit UR2LBCL                   @ ((unsigned)&UR2SYNCR*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2SYNEN             : 1;
        unsigned	UR2CPOL              : 1; 
        unsigned	UR2CPHA              : 1; 
        unsigned	UR2LBCL              : 1; 
    };
} UR2SYNCRbits @ 0x517;
#endif

// Register: UR2LINCR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2LINCR               @ 0x518;
// bit and bitfield definitions
volatile bit UR2BLTH0                  @ ((unsigned)&UR2LINCR*8)+0;
volatile bit UR2BLTH1                  @ ((unsigned)&UR2LINCR*8)+1;
volatile bit UR2BLTH2                  @ ((unsigned)&UR2LINCR*8)+2;
volatile bit UR2BLTH3                  @ ((unsigned)&UR2LINCR*8)+3;
volatile bit UR2LINEN                  @ ((unsigned)&UR2LINCR*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2BLTH0             : 1;
        unsigned	UR2BLTH1             : 1; 
        unsigned	UR2BLTH2             : 1; 
        unsigned	UR2BLTH3             : 1; 
        unsigned	UR2LINEN             : 1; 
    };
    struct {
        unsigned	UR2BLTH              : 4;
    };
} UR2LINCRbits @ 0x518;
#endif

// Register: UR2SDCR0
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2SDCR0               @ 0x519;
// bit and bitfield definitions
volatile bit UR2SDEN                   @ ((unsigned)&UR2SDCR0*8)+4;
volatile bit UR2CKOE                   @ ((unsigned)&UR2SDCR0*8)+5;
volatile bit UR2NACK                   @ ((unsigned)&UR2SDCR0*8)+6;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                  : 4;
        unsigned	UR2SDEN              : 1; 
        unsigned	UR2CKOE              : 1; 
        unsigned	UR2NACK              : 1; 
    };
} UR2SDCR0bits @ 0x519;
#endif

// Register: UR2SDCR1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2SDCR1               @ 0x51A;
// bit and bitfield definitions
volatile bit UR2GT0                   @ ((unsigned)&UR2SDCR1*8)+0;
volatile bit UR2GT1                   @ ((unsigned)&UR2SDCR1*8)+1;
volatile bit UR2GT2                   @ ((unsigned)&UR2SDCR1*8)+2;
volatile bit UR2GT3                   @ ((unsigned)&UR2SDCR1*8)+3;
volatile bit UR2GT4                   @ ((unsigned)&UR2SDCR1*8)+4;
volatile bit UR2GT5                   @ ((unsigned)&UR2SDCR1*8)+5;
volatile bit UR2GT6                   @ ((unsigned)&UR2SDCR1*8)+6;
volatile bit UR2GT7                   @ ((unsigned)&UR2SDCR1*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2GT0               : 1;
        unsigned	UR2GT1               : 1;
        unsigned	UR2GT2               : 1;
        unsigned	UR2GT3               : 1;
        unsigned	UR2GT4               : 1;
        unsigned	UR2GT5               : 1;
        unsigned	UR2GT6               : 1;
        unsigned	UR2GT7               : 1;
    };
    struct {
        unsigned	UR2GT                : 8;
    };
} UR2SDCR1bits @ 0x51A;
#endif

// Register: UR2SDCR2
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2SDCR2               @ 0x51B;
// bit and bitfield definitions
volatile bit UR2PSC0                   @ ((unsigned)&UR2SDCR2*8)+0;
volatile bit UR2PSC1                   @ ((unsigned)&UR2SDCR2*8)+1;
volatile bit UR2PSC2                   @ ((unsigned)&UR2SDCR2*8)+2;
volatile bit UR2PSC3                   @ ((unsigned)&UR2SDCR2*8)+3;
volatile bit UR2PSC4                   @ ((unsigned)&UR2SDCR2*8)+4;
volatile bit UR2PSC5                   @ ((unsigned)&UR2SDCR2*8)+5;
volatile bit UR2PSC6                   @ ((unsigned)&UR2SDCR2*8)+6;
volatile bit UR2PSC7                   @ ((unsigned)&UR2SDCR2*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2PSC0               : 1;
        unsigned	UR2PSC1               : 1;
        unsigned	UR2PSC2               : 1;
        unsigned	UR2PSC3               : 1;
        unsigned	UR2PSC4               : 1;
        unsigned	UR2PSC5               : 1;
        unsigned	UR2PSC6               : 1;
        unsigned	UR2PSC7               : 1;
    };
    struct {
        unsigned	UR2PSC                : 8;
    };
} UR2SDCR2bits @ 0x51B;
#endif

// Register: UR2TC
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           UR2TC               @ 0x51C;
// bit and bitfield definitions
volatile bit UR2TCF                   @ ((unsigned)&UR2TC*8)+0;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	UR2TCF               : 1;
    };
} UR2TCbits @ 0x51C;
#endif
//
// Special function register definitions: Bank 31

// Register: CKAUX
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           CKAUX              @ 0xF8D;
// bit and bitfield definitions
volatile bit CLKOS                   @ ((unsigned)&CKAUX*8)+1;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                     : 1;
        unsigned	CLKOS                : 1;
    };
} CKAUXbits @ 0xF8D;
#endif
//
// Register: LVDCON1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           LVDCON1              @ 0xF8E;
// bit and bitfield definitions
volatile bit LVDOS0                   @ ((unsigned)&LVDCON1*8)+0;
volatile bit LVDOS1                   @ ((unsigned)&LVDCON1*8)+1;
volatile bit LVDOE                    @ ((unsigned)&LVDCON1*8)+2;
volatile bit LVDEB                    @ ((unsigned)&LVDCON1*8)+3;
volatile bit LVDP                     @ ((unsigned)&LVDCON1*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	LVDOS0               : 1;
        unsigned	LVDOS1               : 1;
        unsigned	LVDOE                : 1;
        unsigned	LVDEB                : 1;
        unsigned	LVDP                 : 1;
    };
    struct {
        unsigned	LVDOS               : 2;
    };
} LVDCON1bits @ 0xF8E;
#endif

					
// Register: OP0CR0
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           OP0CR0              @ 0xF8F;
// bit and bitfield definitions
volatile bit OP0ON                        @ ((unsigned)&OP0CR0*8)+0;
volatile bit OP0FR0                       @ ((unsigned)&OP0CR0*8)+1;
volatile bit OP0FR1                       @ ((unsigned)&OP0CR0*8)+2;
volatile bit OP0FR2                       @ ((unsigned)&OP0CR0*8)+3;
volatile bit OP0NSEL0                     @ ((unsigned)&OP0CR0*8)+4;
volatile bit OP0NSEL1                     @ ((unsigned)&OP0CR0*8)+5;
volatile bit OP0PSEL                      @ ((unsigned)&OP0CR0*8)+6;
volatile bit OP0OUT                       @ ((unsigned)&OP0CR0*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OP0ON                 : 1;
        unsigned	OP0FR0                : 1;
        unsigned	OP0FR1                : 1;
        unsigned	OP0FR2                : 1;
        unsigned	OP0NSEL0              : 1;
        unsigned	OP0NSEL1              : 1;
        unsigned	OP0PSEL               : 1;
        unsigned	OP0OUT                : 1;
    };
    struct {
        unsigned	                      : 1;
        unsigned	OP0FR                 : 3;
        unsigned	OP0NSEL               : 2;
    };
} OP0CR0bits @ 0xF8F;
#endif

// Register: OP0CR1
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           OP0CR1              @ 0xF90;
// bit and bitfield definitions
volatile bit OPTOIO                        @ ((unsigned)&OP0CR1*8)+0;
volatile bit OPTODIG                       @ ((unsigned)&OP0CR1*8)+1;
volatile bit OP0TM                         @ ((unsigned)&OP0CR1*8)+2;
volatile bit OP0FCAPE                      @ ((unsigned)&OP0CR1*8)+3;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OPTOIO                : 1;
        unsigned	OPTODIG               : 1;
        unsigned	OP0TM                 : 1;
        unsigned	OP0FCAPE              : 1;
    };
} OP0CR1bits @ 0xF90;
#endif

// Register: OP0CFG
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           OP0CFG              @ 0xF91;
// bit and bitfield definitions
volatile bit OP0COF0                      @ ((unsigned)&OP0CFG*8)+0;
volatile bit OP0COF1                      @ ((unsigned)&OP0CFG*8)+1;
volatile bit OP0COF2                      @ ((unsigned)&OP0CFG*8)+2;
volatile bit OP0COF3                      @ ((unsigned)&OP0CFG*8)+3;
volatile bit OP0COF4                      @ ((unsigned)&OP0CFG*8)+4;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	OP0COF0               : 1;
        unsigned	OP0COF1               : 1;
        unsigned	OP0COF2               : 1;
        unsigned	OP0COF3               : 1;
        unsigned	OP0COF4               : 1;
    };
    struct {
        unsigned	OP0COF                : 5;
    };
} OP0CFGbits @ 0xF91;
#endif
// Register: CF0OUT3L
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           LVDTUNE              @ 0xF92;
// bit and bitfield definitions
volatile bit LVDCAL0                      @ ((unsigned)&LVDTUNE*8)+4;
volatile bit LVDCAL1                      @ ((unsigned)&LVDTUNE*8)+5;
volatile bit LVDCAL2                      @ ((unsigned)&LVDTUNE*8)+6;
volatile bit LVDCAL3                      @ ((unsigned)&LVDTUNE*8)+7;
#ifndef _LIB_BUILD
volatile union {
    struct {
        unsigned	                      : 4;
        unsigned	LVDCAL0               : 1;
        unsigned	LVDCAL1               : 1;
        unsigned	LVDCAL2               : 1;
        unsigned	LVDCAL3               : 1;
    };
    struct {
        unsigned	                      : 4;
        unsigned	LVDCAL                : 4;
    };
} LVDTUNEbits @ 0xF92;
#endif



// Register: STATUS_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           STATUS_SHAD           @ 0xFE4;
// bit and bitfield definitions

// Register: WREG_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           WREG_SHAD             @ 0xFE5;
// bit and bitfield definitions

// Register: BSREG_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           BSREG_SHAD            @ 0xFE6;
// bit and bitfield definitions

// Register: PCLATH_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           PCLATH_SHAD            @ 0xFE7;
// bit and bitfield definitions

// Register: FSR0L_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           FSR0L_SHAD            @ 0xFE8;
// bit and bitfield definitions

// Register: FSR0L_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           FSR0H_SHAD            @ 0xFE9;
// bit and bitfield definitions

// Register: FSR0L_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           FSR1L_SHAD            @ 0xFEA;
// bit and bitfield definitions

// Register: FSR0L_SHAD
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           FSR1H_SHAD            @ 0xFEB;
// bit and bitfield definitions

// Register: STKPTR
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           STKPTR                @ 0xFED;
// bit and bitfield definitions

// Register: TOSL
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           TOSL                  @ 0xFEE;
// bit and bitfield definitions

// Register: TOSH
// LVDIErrupt-On-Change Flag Register
volatile unsigned char           TOSH                  @ 0xFEF;
// bit and bitfield definitions

#endif
