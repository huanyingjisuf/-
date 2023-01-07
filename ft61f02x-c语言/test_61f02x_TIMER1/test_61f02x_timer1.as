opt subtitle "HI-TECH Software Omniscient Code Generator (PRO mode) build 10920"

opt pagewidth 120

	opt pm

	processor	16F685
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
	FNCALL	_main,_POWER_INITIAL
	FNCALL	_main,_TIMER1_INITIAL
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_PSTRCON
psect	text49,local,class=CODE,delta=2
global __ptext49
__ptext49:
_PSTRCON	set	413
	DABS	1,413,1	;_PSTRCON

	global	_SRCON
_SRCON	set	414
	DABS	1,414,1	;_SRCON

	global	_C1SEN
_C1SEN	set	3317
	DABS	1,414,1	;_C1SEN

	global	_C2REN
_C2REN	set	3316
	DABS	1,414,1	;_C2REN

	global	_EEPGD
_EEPGD	set	3175
	DABS	1,396,1	;_EEPGD

	global	_PULSR
_PULSR	set	3314
	DABS	1,414,1	;_PULSR

	global	_PULSS
_PULSS	set	3315
	DABS	1,414,1	;_PULSS

	global	_SR0
_SR0	set	3318
	DABS	1,414,1	;_SR0

	global	_SR1
_SR1	set	3319
	DABS	1,414,1	;_SR1

	global	_STRA
_STRA	set	3304
	DABS	1,413,1	;_STRA

	global	_STRB
_STRB	set	3305
	DABS	1,413,1	;_STRB

	global	_STRC
_STRC	set	3306
	DABS	1,413,1	;_STRC

	global	_STRD
_STRD	set	3307
	DABS	1,413,1	;_STRD

	global	_STRSYNC
_STRSYNC	set	3308
	DABS	1,413,1	;_STRSYNC

	global	_WREN
_WREN	set	3170
	DABS	1,396,1	;_WREN

	global	_CMCON0
_CMCON0	set	25
	global	_INTCON
_INTCON	set	11
	global	_MSCKCON
_MSCKCON	set	27
	global	_PORTA
_PORTA	set	5
	global	_PORTC
_PORTC	set	7
	global	_T1CON
_T1CON	set	16
	global	_TMR1H
_TMR1H	set	15
	global	_TMR1L
_TMR1L	set	14
	global	_GIE
_GIE	set	95
	global	_PEIE
_PEIE	set	94
	global	_RA3
_RA3	set	43
	global	_RC3
_RC3	set	59
	global	_TMR1IF
_TMR1IF	set	96
	global	_TMR1ON
_TMR1ON	set	128
	global	_OPTION
_OPTION	set	129
	global	_OSCCON
_OSCCON	set	143
	global	_TRISA
_TRISA	set	133
	global	_TRISC
_TRISC	set	135
	global	_WPUA
_WPUA	set	149
	global	_WPUC
_WPUC	set	136
	global	_TMR1IE
_TMR1IE	set	1120
	file	"test_61f02x_timer1.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	??_ISR
??_ISR:	; 0 bytes @ 0x0
	global	?_POWER_INITIAL
?_POWER_INITIAL:	; 0 bytes @ 0x0
	global	?_TIMER1_INITIAL
?_TIMER1_INITIAL:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	ds	2
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x2
	global	??_TIMER1_INITIAL
??_TIMER1_INITIAL:	; 0 bytes @ 0x2
	global	??_main
??_main:	; 0 bytes @ 0x2
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      2       2
;; BANK0           80      0       0
;; BANK1           32      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _ISR in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK1
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0       0
;;                      _POWER_INITIAL
;;                     _TIMER1_INITIAL
;; ---------------------------------------------------------------------------------
;; (1) _TIMER1_INITIAL                                       0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _ISR                                                  2     2      0       0
;;                                              0 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _TIMER1_INITIAL
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      2       2       1       14.3%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       1       2        0.0%
;;BITBANK0            50      0       0       3        0.0%
;;BANK0               50      0       0       4        0.0%
;;BITBANK1            20      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BANK1               20      0       0       6        0.0%
;;ABS                  0      0       0       7        0.0%
;;DATA                 0      0       0       8        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 114 in file "TEST_61F02x_Timer1.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 17F/0
;;		Unchanged: FFE80/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_POWER_INITIAL
;;		_TIMER1_INITIAL
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"TEST_61F02x_Timer1.c"
	line	114
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	115
	
l2149:	
;TEST_61F02x_Timer1.c: 115: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	116
;TEST_61F02x_Timer1.c: 116: TIMER1_INITIAL();
	fcall	_TIMER1_INITIAL
	line	120
	
l2151:	
;TEST_61F02x_Timer1.c: 119: {
;TEST_61F02x_Timer1.c: 120: if(RC3 == 1)
	bcf	status, 5	;RP0=0, select bank0
	btfss	(59/8),(59)&7
	goto	u21
	goto	u20
u21:
	goto	l1076
u20:
	line	122
	
l2153:	
;TEST_61F02x_Timer1.c: 121: {
;TEST_61F02x_Timer1.c: 122: TMR1IE = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1120/8)^080h,(1120)&7
	line	123
;TEST_61F02x_Timer1.c: 123: }
	goto	l2151
	line	124
	
l1076:	
	line	126
;TEST_61F02x_Timer1.c: 124: else
;TEST_61F02x_Timer1.c: 125: {
;TEST_61F02x_Timer1.c: 126: TMR1IE = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1120/8)^080h,(1120)&7
	line	127
;TEST_61F02x_Timer1.c: 127: RA3 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(43/8),(43)&7
	goto	l2151
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	130
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_TIMER1_INITIAL
psect	text50,local,class=CODE,delta=2
global __ptext50
__ptext50:

;; *************** function _TIMER1_INITIAL *****************
;; Defined at:
;;		line 93 in file "TEST_61F02x_Timer1.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 17F/0
;;		Unchanged: FFE80/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text50
	file	"TEST_61F02x_Timer1.c"
	line	93
	global	__size_of_TIMER1_INITIAL
	__size_of_TIMER1_INITIAL	equ	__end_of_TIMER1_INITIAL-_TIMER1_INITIAL
	
_TIMER1_INITIAL:	
	opt	stack 6
; Regs used in _TIMER1_INITIAL: [wreg+status,2]
	line	95
	
l2135:	
;TEST_61F02x_Timer1.c: 95: T1CON = 0B00000000;
	clrf	(16)	;volatile
	line	98
	
l2137:	
;TEST_61F02x_Timer1.c: 98: TMR1L = 0X60;
	movlw	(060h)
	movwf	(14)	;volatile
	line	100
	
l2139:	
;TEST_61F02x_Timer1.c: 100: TMR1H = 0XF0;
	movlw	(0F0h)
	movwf	(15)	;volatile
	line	102
	
l2141:	
;TEST_61F02x_Timer1.c: 102: TMR1IE = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1120/8)^080h,(1120)&7
	line	103
	
l2143:	
;TEST_61F02x_Timer1.c: 103: TMR1ON = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(128/8),(128)&7
	line	104
	
l2145:	
;TEST_61F02x_Timer1.c: 104: PEIE=1;
	bsf	(94/8),(94)&7
	line	105
	
l2147:	
;TEST_61F02x_Timer1.c: 105: GIE = 1;
	bsf	(95/8),(95)&7
	line	106
	
l1072:	
	return
	opt stack 0
GLOBAL	__end_of_TIMER1_INITIAL
	__end_of_TIMER1_INITIAL:
;; =============== function _TIMER1_INITIAL ends ============

	signat	_TIMER1_INITIAL,88
	global	_POWER_INITIAL
psect	text51,local,class=CODE,delta=2
global __ptext51
__ptext51:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 64 in file "TEST_61F02x_Timer1.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 17F/0
;;		Unchanged: FFE80/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text51
	file	"TEST_61F02x_Timer1.c"
	line	64
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 6
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	66
	
l2119:	
;TEST_61F02x_Timer1.c: 66: OSCCON = 0B01110001;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
	line	69
	
l2121:	
;TEST_61F02x_Timer1.c: 69: INTCON = 0;
	clrf	(11)	;volatile
	line	70
	
l2123:	
;TEST_61F02x_Timer1.c: 70: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	71
;TEST_61F02x_Timer1.c: 71: TRISA = 0B11110111;
	movlw	(0F7h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(133)^080h	;volatile
	line	73
	
l2125:	
;TEST_61F02x_Timer1.c: 73: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	74
	
l2127:	
;TEST_61F02x_Timer1.c: 74: TRISC = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(135)^080h	;volatile
	line	75
;TEST_61F02x_Timer1.c: 75: WPUA = 0B00000000;
	clrf	(149)^080h	;volatile
	line	76
	
l2129:	
;TEST_61F02x_Timer1.c: 76: WPUC = 0B00001000;
	movlw	(08h)
	movwf	(136)^080h	;volatile
	line	78
	
l2131:	
;TEST_61F02x_Timer1.c: 78: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	81
;TEST_61F02x_Timer1.c: 81: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	84
	
l2133:	
;TEST_61F02x_Timer1.c: 84: CMCON0 = 0B00000111;
	movlw	(07h)
	movwf	(25)	;volatile
	line	86
	
l1069:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
	global	_ISR
psect	text52,local,class=CODE,delta=2
global __ptext52
__ptext52:

;; *************** function _ISR *****************
;; Defined at:
;;		line 43 in file "TEST_61F02x_Timer1.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          2       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text52
	file	"TEST_61F02x_Timer1.c"
	line	43
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 6
; Regs used in _ISR: [wreg]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_ISR+0)
	movf	pclath,w
	movwf	(??_ISR+1)
	ljmp	_ISR
psect	text52
	line	46
	
i1l2113:	
;TEST_61F02x_Timer1.c: 46: if(TMR1IF)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(96/8),(96)&7
	goto	u1_21
	goto	u1_20
u1_21:
	goto	i1l1066
u1_20:
	line	48
	
i1l2115:	
;TEST_61F02x_Timer1.c: 47: {
;TEST_61F02x_Timer1.c: 48: TMR1IF = 0;
	bcf	(96/8),(96)&7
	line	50
	
i1l2117:	
;TEST_61F02x_Timer1.c: 50: TMR1L = 0X60;
	movlw	(060h)
	movwf	(14)	;volatile
	line	52
;TEST_61F02x_Timer1.c: 52: TMR1H = 0XF0;
	movlw	(0F0h)
	movwf	(15)	;volatile
	line	54
;TEST_61F02x_Timer1.c: 54: RA3 = ~RA3;
	movlw	1<<((43)&7)
	xorwf	((43)/8),f
	line	56
	
i1l1066:	
	movf	(??_ISR+1),w
	movwf	pclath
	swapf	(??_ISR+0)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_ISR
	__end_of_ISR:
;; =============== function _ISR ends ============

	signat	_ISR,88
psect	text53,local,class=CODE,delta=2
global __ptext53
__ptext53:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
