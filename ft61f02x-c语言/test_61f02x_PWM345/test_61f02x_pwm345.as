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
	FNCALL	_main,_PWM_INITIAL
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_PSTRCON
psect	text43,local,class=CODE,delta=2
global __ptext43
__ptext43:
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
	global	_TRISC2
_TRISC2	set	1082
	global	_TRISC3
_TRISC3	set	1083
	global	_TRISC4
_TRISC4	set	1084
	global	_PR3L
_PR3L	set	270
	global	_PR4L
_PR4L	set	276
	global	_PR5L
_PR5L	set	282
	global	_PWM3CR0
_PWM3CR0	set	271
	global	_PWM3CR1
_PWM3CR1	set	272
	global	_PWM4CR0
_PWM4CR0	set	277
	global	_PWM4CR1
_PWM4CR1	set	278
	global	_PWM5CR0
_PWM5CR0	set	283
	global	_PWM5CR1
_PWM5CR1	set	284
	global	_T3CKDIV
_T3CKDIV	set	273
	global	_T4CKDIV
_T4CKDIV	set	279
	global	_T5CKDIV
_T5CKDIV	set	285
	global	_TMR3H
_TMR3H	set	269
	global	_TMR4H
_TMR4H	set	275
	global	_TMR5H
_TMR5H	set	281
	global	_TMR3ON
_TMR3ON	set	2178
	global	_TMR4ON
_TMR4ON	set	2226
	global	_TMR5ON
_TMR5ON	set	2274
	file	"test_61f02x_pwm345.as"
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
	global	?_PWM_INITIAL
?_PWM_INITIAL:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	ds	2
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x2
	global	??_PWM_INITIAL
??_PWM_INITIAL:	; 0 bytes @ 0x2
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
;;                        _PWM_INITIAL
;; ---------------------------------------------------------------------------------
;; (1) _PWM_INITIAL                                          0     0      0       0
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
;;   _PWM_INITIAL
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
;;		line 160 in file "TEST_61F02x_PWM345.C"
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
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_POWER_INITIAL
;;		_PWM_INITIAL
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"TEST_61F02x_PWM345.C"
	line	160
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	161
	
l2150:	
;TEST_61F02x_PWM345.C: 161: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	162
;TEST_61F02x_PWM345.C: 162: PWM_INITIAL();
	fcall	_PWM_INITIAL
	line	164
	
l2152:	
;TEST_61F02x_PWM345.C: 164: TMR3ON=1;
	bsf	(2178/8)^0100h,(2178)&7
	line	165
	
l2154:	
;TEST_61F02x_PWM345.C: 165: TMR4ON=1;
	bsf	(2226/8)^0100h,(2226)&7
	line	166
	
l2156:	
;TEST_61F02x_PWM345.C: 166: TMR5ON=1;
	bsf	(2274/8)^0100h,(2274)&7
	line	167
	
l2158:	
;TEST_61F02x_PWM345.C: 167: TRISC4 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1084/8)^080h,(1084)&7
	line	168
	
l2160:	
;TEST_61F02x_PWM345.C: 168: TRISC3 = 0;
	bcf	(1083/8)^080h,(1083)&7
	line	169
	
l2162:	
;TEST_61F02x_PWM345.C: 169: TRISC2 = 0;
	bcf	(1082/8)^080h,(1082)&7
	line	180
	
l2164:	
;TEST_61F02x_PWM345.C: 171: {
;TEST_61F02x_PWM345.C: 180: _nop();
	nop
	goto	l2164
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	182
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_PWM_INITIAL
psect	text44,local,class=CODE,delta=2
global __ptext44
__ptext44:

;; *************** function _PWM_INITIAL *****************
;; Defined at:
;;		line 79 in file "TEST_61F02x_PWM345.C"
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
;;		On exit  : 17F/40
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
psect	text44
	file	"TEST_61F02x_PWM345.C"
	line	79
	global	__size_of_PWM_INITIAL
	__size_of_PWM_INITIAL	equ	__end_of_PWM_INITIAL-_PWM_INITIAL
	
_PWM_INITIAL:	
	opt	stack 6
; Regs used in _PWM_INITIAL: [wreg+status,2]
	line	94
	
l2128:	
;TEST_61F02x_PWM345.C: 94: TRISC4 = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1084/8)^080h,(1084)&7
	line	95
;TEST_61F02x_PWM345.C: 95: TRISC3 = 1;
	bsf	(1083/8)^080h,(1083)&7
	line	96
;TEST_61F02x_PWM345.C: 96: TRISC2 = 1;
	bsf	(1082/8)^080h,(1082)&7
	line	98
	
l2130:	
;TEST_61F02x_PWM345.C: 98: PWM3CR0 = 0B00110010;
	movlw	(032h)
	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	movwf	(271)^0100h	;volatile
	line	103
;TEST_61F02x_PWM345.C: 103: PWM3CR1 = 0B10000000;
	movlw	(080h)
	movwf	(272)^0100h	;volatile
	line	110
	
l2132:	
;TEST_61F02x_PWM345.C: 110: TMR3H=0;
	clrf	(269)^0100h	;volatile
	line	111
	
l2134:	
;TEST_61F02x_PWM345.C: 111: T3CKDIV = 30;
	movlw	(01Eh)
	movwf	(273)^0100h	;volatile
	line	113
	
l2136:	
;TEST_61F02x_PWM345.C: 113: PR3L = 128;
	movlw	(080h)
	movwf	(270)^0100h	;volatile
	line	115
	
l2138:	
;TEST_61F02x_PWM345.C: 115: PWM4CR0 = 0B00110010;
	movlw	(032h)
	movwf	(277)^0100h	;volatile
	line	120
	
l2140:	
;TEST_61F02x_PWM345.C: 120: PWM4CR1 = 0B10000000;
	movlw	(080h)
	movwf	(278)^0100h	;volatile
	line	127
	
l2142:	
;TEST_61F02x_PWM345.C: 127: TMR4H=0;
	clrf	(275)^0100h	;volatile
	line	129
;TEST_61F02x_PWM345.C: 129: T4CKDIV = 62;
	movlw	(03Eh)
	movwf	(279)^0100h	;volatile
	line	131
;TEST_61F02x_PWM345.C: 131: PR4L = 128;
	movlw	(080h)
	movwf	(276)^0100h	;volatile
	line	133
;TEST_61F02x_PWM345.C: 133: PWM5CR0 = 0B00110010;
	movlw	(032h)
	movwf	(283)^0100h	;volatile
	line	139
;TEST_61F02x_PWM345.C: 139: PWM5CR1 = 0B10000000;
	movlw	(080h)
	movwf	(284)^0100h	;volatile
	line	147
	
l2144:	
;TEST_61F02x_PWM345.C: 147: TMR5H=0;
	clrf	(281)^0100h	;volatile
	line	148
	
l2146:	
;TEST_61F02x_PWM345.C: 148: T5CKDIV = 124;
	movlw	(07Ch)
	movwf	(285)^0100h	;volatile
	line	150
	
l2148:	
;TEST_61F02x_PWM345.C: 150: PR5L = 128;
	movlw	(080h)
	movwf	(282)^0100h	;volatile
	line	152
	
l1073:	
	return
	opt stack 0
GLOBAL	__end_of_PWM_INITIAL
	__end_of_PWM_INITIAL:
;; =============== function _PWM_INITIAL ends ============

	signat	_PWM_INITIAL,88
	global	_POWER_INITIAL
psect	text45,local,class=CODE,delta=2
global __ptext45
__ptext45:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 54 in file "TEST_61F02x_PWM345.C"
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
psect	text45
	file	"TEST_61F02x_PWM345.C"
	line	54
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 6
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	55
	
l2114:	
;TEST_61F02x_PWM345.C: 55: OSCCON = 0B01110001;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
	line	57
	
l2116:	
;TEST_61F02x_PWM345.C: 57: INTCON = 0;
	clrf	(11)	;volatile
	line	58
	
l2118:	
;TEST_61F02x_PWM345.C: 58: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	59
;TEST_61F02x_PWM345.C: 59: TRISA = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(133)^080h	;volatile
	line	60
	
l2120:	
;TEST_61F02x_PWM345.C: 60: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	61
	
l2122:	
;TEST_61F02x_PWM345.C: 61: TRISC = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(135)^080h	;volatile
	line	63
;TEST_61F02x_PWM345.C: 63: WPUA = 0B00000000;
	clrf	(149)^080h	;volatile
	line	64
;TEST_61F02x_PWM345.C: 64: WPUC = 0B00000000;
	clrf	(136)^080h	;volatile
	line	65
	
l2124:	
;TEST_61F02x_PWM345.C: 65: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	67
	
l2126:	
;TEST_61F02x_PWM345.C: 67: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	70
;TEST_61F02x_PWM345.C: 70: CMCON0 = 0B00000111;
	movlw	(07h)
	movwf	(25)	;volatile
	line	71
	
l1070:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
	global	_ISR
psect	text46,local,class=CODE,delta=2
global __ptext46
__ptext46:

;; *************** function _ISR *****************
;; Defined at:
;;		line 44 in file "TEST_61F02x_PWM345.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
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
psect	text46
	file	"TEST_61F02x_PWM345.C"
	line	44
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 6
; Regs used in _ISR: []
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
psect	text46
	line	45
	
i1l2112:	
;TEST_61F02x_PWM345.C: 45: _nop();
	nop
	line	46
	
i1l1067:	
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
psect	text47,local,class=CODE,delta=2
global __ptext47
__ptext47:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
