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
	FNCALL	_main,_PWM_INITIAL
	FNCALL	_main,_pwm_duty_count
	FNCALL	_main,_DelayMs
	FNCALL	_DelayMs,_DelayUs
	FNCALL	_PWM_INITIAL,_pwm_duty_count
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_PSTRCON
psect	text100,local,class=CODE,delta=2
global __ptext100
__ptext100:
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

	global	_pwm_d
psect	nvCOMMON,class=COMMON,space=1
global __pnvCOMMON
__pnvCOMMON:
_pwm_d:
       ds      2

	global	_SAFlag
psect	bitnvCOMMON,class=COMMON,bit,space=1
global __pbitnvCOMMON
__pbitnvCOMMON:
_SAFlag:
       ds      1

	global	_CCP1CON
_CCP1CON	set	21
	global	_CCPR1L
_CCPR1L	set	19
	global	_CMCON0
_CMCON0	set	25
	global	_ECCPAS
_ECCPAS	set	23
	global	_INTCON
_INTCON	set	11
	global	_MSCKCON
_MSCKCON	set	27
	global	_PORTA
_PORTA	set	5
	global	_PORTC
_PORTC	set	7
	global	_PWM1CON
_PWM1CON	set	22
	global	_T1CON
_T1CON	set	16
	global	_T2CON
_T2CON	set	18
	global	_TMR1H
_TMR1H	set	15
	global	_TMR1L
_TMR1L	set	14
	global	_GIE
_GIE	set	95
	global	_PEIE
_PEIE	set	94
	global	_TMR1IF
_TMR1IF	set	96
	global	_TMR1ON
_TMR1ON	set	128
	global	_TMR2IF
_TMR2IF	set	97
	global	_TMR2ON
_TMR2ON	set	146
	global	_OPTION
_OPTION	set	129
	global	_OSCCON
_OSCCON	set	143
	global	_PR2
_PR2	set	146
	global	_PWM1AUX
_PWM1AUX	set	144
	global	_TRISA
_TRISA	set	133
	global	_TRISC
_TRISC	set	135
	global	_WPUA
_WPUA	set	149
	global	_WPUC
_WPUC	set	136
	global	_P1AOE
_P1AOE	set	1152
	global	_TMR1IE
_TMR1IE	set	1120
	global	_TRISC5
_TRISC5	set	1085
	file	"test_61f02x_pwm.as"
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
	global	?_pwm_duty_count
?_pwm_duty_count:	; 0 bytes @ 0x0
	global	?_PWM_INITIAL
?_PWM_INITIAL:	; 0 bytes @ 0x0
	global	?_DelayUs
?_DelayUs:	; 0 bytes @ 0x0
	global	?_DelayMs
?_DelayMs:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	ds	2
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x2
	global	??_TIMER1_INITIAL
??_TIMER1_INITIAL:	; 0 bytes @ 0x2
	global	??_pwm_duty_count
??_pwm_duty_count:	; 0 bytes @ 0x2
	global	??_DelayUs
??_DelayUs:	; 0 bytes @ 0x2
	global	DelayUs@Time
DelayUs@Time:	; 1 bytes @ 0x2
	global	pwm_duty_count@lsb22
pwm_duty_count@lsb22:	; 2 bytes @ 0x2
	ds	1
	global	DelayUs@a
DelayUs@a:	; 1 bytes @ 0x3
	ds	1
	global	??_DelayMs
??_DelayMs:	; 0 bytes @ 0x4
	global	pwm_duty_count@lsb23
pwm_duty_count@lsb23:	; 1 bytes @ 0x4
	global	DelayMs@Time
DelayMs@Time:	; 1 bytes @ 0x4
	ds	1
	global	??_PWM_INITIAL
??_PWM_INITIAL:	; 0 bytes @ 0x5
	global	PWM_INITIAL@SET_PR2
PWM_INITIAL@SET_PR2:	; 1 bytes @ 0x5
	global	DelayMs@a
DelayMs@a:	; 1 bytes @ 0x5
	ds	1
	global	DelayMs@b
DelayMs@b:	; 1 bytes @ 0x6
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x7
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 2 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      7      10
;; BANK0           80      0       0
;; BANK1           32      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_DelayMs
;;   _DelayMs->_DelayUs
;;   _PWM_INITIAL->_pwm_duty_count
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
;; (0) _main                                                 0     0      0     225
;;                      _POWER_INITIAL
;;                     _TIMER1_INITIAL
;;                        _PWM_INITIAL
;;                     _pwm_duty_count
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (1) _DelayMs                                              3     3      0      90
;;                                              4 COMMON     3     3      0
;;                            _DelayUs
;; ---------------------------------------------------------------------------------
;; (2) _DelayUs                                              2     2      0      30
;;                                              2 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (1) _PWM_INITIAL                                          1     1      0      75
;;                                              5 COMMON     1     1      0
;;                     _pwm_duty_count
;; ---------------------------------------------------------------------------------
;; (1) _pwm_duty_count                                       3     3      0      60
;;                                              2 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; (1) _TIMER1_INITIAL                                       0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (3) _ISR                                                  2     2      0       0
;;                                              0 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _TIMER1_INITIAL
;;   _PWM_INITIAL
;;     _pwm_duty_count
;;   _pwm_duty_count
;;   _DelayMs
;;     _DelayUs
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       1       0        7.1%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      7       A       1       71.4%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       2       2        0.0%
;;BITBANK0            50      0       0       3        0.0%
;;BANK0               50      0       0       4        0.0%
;;BITBANK1            20      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BANK1               20      0       0       6        0.0%
;;ABS                  0      0       A       7        0.0%
;;DATA                 0      0       C       8        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 225 in file "TEST_61F02x_PWM.c"
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
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_POWER_INITIAL
;;		_TIMER1_INITIAL
;;		_PWM_INITIAL
;;		_pwm_duty_count
;;		_DelayMs
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"TEST_61F02x_PWM.c"
	line	225
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 5
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	226
	
l2241:	
;TEST_61F02x_PWM.c: 226: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	227
;TEST_61F02x_PWM.c: 227: TIMER1_INITIAL();
	fcall	_TIMER1_INITIAL
	line	228
	
l2243:	
;TEST_61F02x_PWM.c: 228: pwm_d = 10;
	movlw	0Ah
	movwf	(_pwm_d)	;volatile
	clrf	(_pwm_d+1)	;volatile
	line	229
	
l2245:	
;TEST_61F02x_PWM.c: 229: PWM_INITIAL(99);
	movlw	(063h)
	fcall	_PWM_INITIAL
	line	231
	
l2247:	
;TEST_61F02x_PWM.c: 231: P1AOE = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1152/8)^080h,(1152)&7
	line	235
	
l2249:	
;TEST_61F02x_PWM.c: 235: TRISC5 = 0;
	bcf	(1085/8)^080h,(1085)&7
	line	239
	
l2251:	
;TEST_61F02x_PWM.c: 239: TMR2ON = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(146/8),(146)&7
	line	240
	
l2253:	
;TEST_61F02x_PWM.c: 240: SAFlag = 1;
	bsf	(_SAFlag/8),(_SAFlag)&7
	line	243
	
l2255:	
;TEST_61F02x_PWM.c: 242: {
;TEST_61F02x_PWM.c: 243: if(SAFlag == 1)
	btfss	(_SAFlag/8),(_SAFlag)&7
	goto	u51
	goto	u50
u51:
	goto	l2263
u50:
	line	245
	
l2257:	
;TEST_61F02x_PWM.c: 244: {
;TEST_61F02x_PWM.c: 245: pwm_d++;
	incf	(_pwm_d),f	;volatile
	skipnz
	incf	(_pwm_d+1),f	;volatile
	line	246
	
l2259:	
;TEST_61F02x_PWM.c: 246: if(pwm_d > 400)
	movlw	high(0191h)
	subwf	(_pwm_d+1),w	;volatile
	movlw	low(0191h)
	skipnz
	subwf	(_pwm_d),w	;volatile
	skipc
	goto	u61
	goto	u60
u61:
	goto	l2269
u60:
	line	249
	
l2261:	
;TEST_61F02x_PWM.c: 247: {
;TEST_61F02x_PWM.c: 249: SAFlag = 0;
	bcf	(_SAFlag/8),(_SAFlag)&7
	goto	l2269
	line	254
	
l2263:	
;TEST_61F02x_PWM.c: 252: else
;TEST_61F02x_PWM.c: 253: {
;TEST_61F02x_PWM.c: 254: pwm_d--;
	movlw	low(01h)
	subwf	(_pwm_d),f	;volatile
	movlw	high(01h)
	skipc
	decf	(_pwm_d+1),f	;volatile
	subwf	(_pwm_d+1),f	;volatile
	line	255
	
l2265:	
;TEST_61F02x_PWM.c: 255: if(pwm_d == 0)
	movf	((_pwm_d+1)),w	;volatile
	iorwf	((_pwm_d)),w	;volatile
	skipz
	goto	u71
	goto	u70
u71:
	goto	l2269
u70:
	line	257
	
l2267:	
;TEST_61F02x_PWM.c: 256: {
;TEST_61F02x_PWM.c: 257: SAFlag = 1;
	bsf	(_SAFlag/8),(_SAFlag)&7
	line	260
	
l2269:	
;TEST_61F02x_PWM.c: 258: }
;TEST_61F02x_PWM.c: 259: }
;TEST_61F02x_PWM.c: 260: pwm_duty_count();
	fcall	_pwm_duty_count
	line	261
;TEST_61F02x_PWM.c: 261: DelayMs(10);
	movlw	(0Ah)
	fcall	_DelayMs
	goto	l2255
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	263
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_DelayMs
psect	text101,local,class=CODE,delta=2
global __ptext101
__ptext101:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 195 in file "TEST_61F02x_PWM.c"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    4[COMMON] unsigned char 
;;  b               1    6[COMMON] unsigned char 
;;  a               1    5[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         3       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayUs
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text101
	file	"TEST_61F02x_PWM.c"
	line	195
	global	__size_of_DelayMs
	__size_of_DelayMs	equ	__end_of_DelayMs-_DelayMs
	
_DelayMs:	
	opt	stack 5
; Regs used in _DelayMs: [wreg+status,2+status,0+pclath+cstack]
;DelayMs@Time stored from wreg
	line	197
	movwf	(DelayMs@Time)
	
l2223:	
;TEST_61F02x_PWM.c: 196: unsigned char a,b;
;TEST_61F02x_PWM.c: 197: for(a=0;a<Time;a++)
	clrf	(DelayMs@a)
	goto	l2239
	line	199
	
l2225:	
;TEST_61F02x_PWM.c: 198: {
;TEST_61F02x_PWM.c: 199: for(b=0;b<5;b++)
	clrf	(DelayMs@b)
	line	201
	
l2231:	
;TEST_61F02x_PWM.c: 200: {
;TEST_61F02x_PWM.c: 201: DelayUs(197);
	movlw	(0C5h)
	fcall	_DelayUs
	line	199
	
l2233:	
	incf	(DelayMs@b),f
	
l2235:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u31
	goto	u30
u31:
	goto	l2231
u30:
	line	197
	
l2237:	
	incf	(DelayMs@a),f
	
l2239:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u41
	goto	u40
u41:
	goto	l2225
u40:
	line	204
	
l1098:	
	return
	opt stack 0
GLOBAL	__end_of_DelayMs
	__end_of_DelayMs:
;; =============== function _DelayMs ends ============

	signat	_DelayMs,4216
	global	_DelayUs
psect	text102,local,class=CODE,delta=2
global __ptext102
__ptext102:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 181 in file "TEST_61F02x_PWM.c"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    2[COMMON] unsigned char 
;;  a               1    3[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_DelayMs
;; This function uses a non-reentrant model
;;
psect	text102
	file	"TEST_61F02x_PWM.c"
	line	181
	global	__size_of_DelayUs
	__size_of_DelayUs	equ	__end_of_DelayUs-_DelayUs
	
_DelayUs:	
	opt	stack 5
; Regs used in _DelayUs: [wreg+status,2+status,0]
;DelayUs@Time stored from wreg
	line	183
	movwf	(DelayUs@Time)
	
l2217:	
;TEST_61F02x_PWM.c: 182: unsigned char a;
;TEST_61F02x_PWM.c: 183: for(a=0;a<Time;a++)
	clrf	(DelayUs@a)
	goto	l2221
	line	184
	
l1088:	
	line	185
;TEST_61F02x_PWM.c: 184: {
;TEST_61F02x_PWM.c: 185: _nop();
	nop
	line	183
	
l2219:	
	incf	(DelayUs@a),f
	
l2221:	
	movf	(DelayUs@Time),w
	subwf	(DelayUs@a),w
	skipc
	goto	u21
	goto	u20
u21:
	goto	l1088
u20:
	line	187
	
l1090:	
	return
	opt stack 0
GLOBAL	__end_of_DelayUs
	__end_of_DelayUs:
;; =============== function _DelayUs ends ============

	signat	_DelayUs,4216
	global	_PWM_INITIAL
psect	text103,local,class=CODE,delta=2
global __ptext103
__ptext103:

;; *************** function _PWM_INITIAL *****************
;; Defined at:
;;		line 135 in file "TEST_61F02x_PWM.c"
;; Parameters:    Size  Location     Type
;;  SET_PR2         1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  SET_PR2         1    5[COMMON] unsigned char 
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
;;      Locals:         1       0       0
;;      Temps:          0       0       0
;;      Totals:         1       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_pwm_duty_count
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text103
	file	"TEST_61F02x_PWM.c"
	line	135
	global	__size_of_PWM_INITIAL
	__size_of_PWM_INITIAL	equ	__end_of_PWM_INITIAL-_PWM_INITIAL
	
_PWM_INITIAL:	
	opt	stack 5
; Regs used in _PWM_INITIAL: [wreg+status,2+status,0+pclath+cstack]
;PWM_INITIAL@SET_PR2 stored from wreg
	movwf	(PWM_INITIAL@SET_PR2)
	line	136
	
l2201:	
;TEST_61F02x_PWM.c: 136: MSCKCON = 0B00000000;
	clrf	(27)	;volatile
	line	139
;TEST_61F02x_PWM.c: 139: T2CON = 0B00000000;
	clrf	(18)	;volatile
	line	146
	
l2203:	
;TEST_61F02x_PWM.c: 146: PR2 = SET_PR2;
	movf	(PWM_INITIAL@SET_PR2),w
	bsf	status, 5	;RP0=1, select bank1
	movwf	(146)^080h	;volatile
	line	151
	
l2205:	
;TEST_61F02x_PWM.c: 151: CCP1CON = 0B10001101;
	movlw	(08Dh)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(21)	;volatile
	line	155
	
l2207:	
;TEST_61F02x_PWM.c: 155: pwm_duty_count();
	fcall	_pwm_duty_count
	line	157
	
l2209:	
;TEST_61F02x_PWM.c: 157: PWM1CON = 0B10000001;
	movlw	(081h)
	movwf	(22)	;volatile
	line	160
	
l2211:	
;TEST_61F02x_PWM.c: 160: ECCPAS = 0B00001111;
	movlw	(0Fh)
	movwf	(23)	;volatile
	line	167
	
l2213:	
;TEST_61F02x_PWM.c: 167: PWM1AUX = 0B10000000;
	movlw	(080h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(144)^080h	;volatile
	line	171
	
l2215:	
;TEST_61F02x_PWM.c: 171: TMR2IF = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(97/8),(97)&7
	line	173
	
l1084:	
	return
	opt stack 0
GLOBAL	__end_of_PWM_INITIAL
	__end_of_PWM_INITIAL:
;; =============== function _PWM_INITIAL ends ============

	signat	_PWM_INITIAL,4216
	global	_pwm_duty_count
psect	text104,local,class=CODE,delta=2
global __ptext104
__ptext104:

;; *************** function _pwm_duty_count *****************
;; Defined at:
;;		line 115 in file "TEST_61F02x_PWM.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  lsb22           2    2[COMMON] unsigned int 
;;  lsb23           1    4[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         3       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_PWM_INITIAL
;;		_main
;; This function uses a non-reentrant model
;;
psect	text104
	file	"TEST_61F02x_PWM.c"
	line	115
	global	__size_of_pwm_duty_count
	__size_of_pwm_duty_count	equ	__end_of_pwm_duty_count-_pwm_duty_count
	
_pwm_duty_count:	
	opt	stack 6
; Regs used in _pwm_duty_count: [wreg+status,2+status,0]
	line	118
	
l2183:	
;TEST_61F02x_PWM.c: 116: unsigned int lsb22;
;TEST_61F02x_PWM.c: 117: unsigned char lsb23;
;TEST_61F02x_PWM.c: 118: lsb22 = (unsigned char) pwm_d & 0B00000011;
	movf	(_pwm_d),w	;volatile
	andlw	03h
	movwf	(pwm_duty_count@lsb22)
	clrf	(pwm_duty_count@lsb22+1)
	line	119
	
l2185:	
;TEST_61F02x_PWM.c: 119: CCP1CON = CCP1CON & 0B11001111;
	movlw	(0CFh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	andwf	(21),f	;volatile
	line	120
	
l2187:	
;TEST_61F02x_PWM.c: 120: lsb22 <<= 4;
	swapf	(pwm_duty_count@lsb22),f
	swapf	(pwm_duty_count@lsb22+1),f
	movlw	0f0h
	andwf	(pwm_duty_count@lsb22+1),f
	movf	(pwm_duty_count@lsb22),w
	andlw	0fh
	iorwf	(pwm_duty_count@lsb22+1),f
	movlw	0f0h
	andwf	(pwm_duty_count@lsb22),f
	line	121
	
l2189:	
;TEST_61F02x_PWM.c: 121: lsb23 = (unsigned char)lsb22;
	movf	(pwm_duty_count@lsb22),w
	movwf	(pwm_duty_count@lsb23)
	line	122
	
l2191:	
;TEST_61F02x_PWM.c: 122: CCP1CON = CCP1CON | lsb23;
	movf	(pwm_duty_count@lsb23),w
	iorwf	(21),f	;volatile
	line	123
	
l2193:	
;TEST_61F02x_PWM.c: 123: lsb22 = pwm_d >> 2;
	movf	(_pwm_d+1),w	;volatile
	movwf	(pwm_duty_count@lsb22+1)
	movf	(_pwm_d),w	;volatile
	movwf	(pwm_duty_count@lsb22)
	
l2195:	
	clrc
	rrf	(pwm_duty_count@lsb22+1),f
	rrf	(pwm_duty_count@lsb22),f
	clrc
	rrf	(pwm_duty_count@lsb22+1),f
	rrf	(pwm_duty_count@lsb22),f
	line	124
	
l2197:	
;TEST_61F02x_PWM.c: 124: lsb23 = (unsigned char)lsb22;
	movf	(pwm_duty_count@lsb22),w
	movwf	(pwm_duty_count@lsb23)
	line	125
	
l2199:	
;TEST_61F02x_PWM.c: 125: CCPR1L = lsb23;
	movf	(pwm_duty_count@lsb23),w
	movwf	(19)	;volatile
	line	126
	
l1081:	
	return
	opt stack 0
GLOBAL	__end_of_pwm_duty_count
	__end_of_pwm_duty_count:
;; =============== function _pwm_duty_count ends ============

	signat	_pwm_duty_count,88
	global	_TIMER1_INITIAL
psect	text105,local,class=CODE,delta=2
global __ptext105
__ptext105:

;; *************** function _TIMER1_INITIAL *****************
;; Defined at:
;;		line 94 in file "TEST_61F02x_PWM.c"
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
psect	text105
	file	"TEST_61F02x_PWM.c"
	line	94
	global	__size_of_TIMER1_INITIAL
	__size_of_TIMER1_INITIAL	equ	__end_of_TIMER1_INITIAL-_TIMER1_INITIAL
	
_TIMER1_INITIAL:	
	opt	stack 6
; Regs used in _TIMER1_INITIAL: [wreg+status,2]
	line	96
	
l2169:	
;TEST_61F02x_PWM.c: 96: T1CON = 0B00000000;
	clrf	(16)	;volatile
	line	99
	
l2171:	
;TEST_61F02x_PWM.c: 99: TMR1L = 0X80;
	movlw	(080h)
	movwf	(14)	;volatile
	line	101
	
l2173:	
;TEST_61F02x_PWM.c: 101: TMR1H = 0XC1;
	movlw	(0C1h)
	movwf	(15)	;volatile
	line	102
	
l2175:	
;TEST_61F02x_PWM.c: 102: TMR1IE = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1120/8)^080h,(1120)&7
	line	103
	
l2177:	
;TEST_61F02x_PWM.c: 103: TMR1ON = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(128/8),(128)&7
	line	104
	
l2179:	
;TEST_61F02x_PWM.c: 104: PEIE=1;
	bsf	(94/8),(94)&7
	line	105
	
l2181:	
;TEST_61F02x_PWM.c: 105: GIE = 1;
	bsf	(95/8),(95)&7
	line	107
	
l1078:	
	return
	opt stack 0
GLOBAL	__end_of_TIMER1_INITIAL
	__end_of_TIMER1_INITIAL:
;; =============== function _TIMER1_INITIAL ends ============

	signat	_TIMER1_INITIAL,88
	global	_POWER_INITIAL
psect	text106,local,class=CODE,delta=2
global __ptext106
__ptext106:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 68 in file "TEST_61F02x_PWM.c"
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
psect	text106
	file	"TEST_61F02x_PWM.c"
	line	68
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 6
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	69
	
l2155:	
;TEST_61F02x_PWM.c: 69: OSCCON = 0B01110001;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
	line	72
	
l2157:	
;TEST_61F02x_PWM.c: 72: INTCON = 0;
	clrf	(11)	;volatile
	line	73
	
l2159:	
;TEST_61F02x_PWM.c: 73: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	74
;TEST_61F02x_PWM.c: 74: TRISA = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(133)^080h	;volatile
	line	75
	
l2161:	
;TEST_61F02x_PWM.c: 75: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	76
	
l2163:	
;TEST_61F02x_PWM.c: 76: TRISC = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(135)^080h	;volatile
	line	78
;TEST_61F02x_PWM.c: 78: WPUA = 0;
	clrf	(149)^080h	;volatile
	line	79
;TEST_61F02x_PWM.c: 79: WPUC = 0 ;
	clrf	(136)^080h	;volatile
	line	80
	
l2165:	
;TEST_61F02x_PWM.c: 80: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	82
	
l2167:	
;TEST_61F02x_PWM.c: 82: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	85
;TEST_61F02x_PWM.c: 85: CMCON0 = 0B00000111;
	movlw	(07h)
	movwf	(25)	;volatile
	line	86
	
l1075:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
	global	_ISR
psect	text107,local,class=CODE,delta=2
global __ptext107
__ptext107:

;; *************** function _ISR *****************
;; Defined at:
;;		line 52 in file "TEST_61F02x_PWM.c"
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
psect	text107
	file	"TEST_61F02x_PWM.c"
	line	52
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 5
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
psect	text107
	line	53
	
i1l2149:	
;TEST_61F02x_PWM.c: 53: if(TMR1IF)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(96/8),(96)&7
	goto	u1_21
	goto	u1_20
u1_21:
	goto	i1l1072
u1_20:
	line	55
	
i1l2151:	
;TEST_61F02x_PWM.c: 54: {
;TEST_61F02x_PWM.c: 55: TMR1IF = 0;
	bcf	(96/8),(96)&7
	line	56
	
i1l2153:	
;TEST_61F02x_PWM.c: 56: TMR1L = 0X80;
	movlw	(080h)
	movwf	(14)	;volatile
	line	58
;TEST_61F02x_PWM.c: 58: TMR1H = 0XC1;
	movlw	(0C1h)
	movwf	(15)	;volatile
	line	60
	
i1l1072:	
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
psect	text108,local,class=CODE,delta=2
global __ptext108
__ptext108:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
