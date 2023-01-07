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
	FNCALL	_main,_DelayMs
	FNCALL	_DelayMs,_DelayUs
	FNROOT	_main
	global	_PSTRCON
psect	text47,local,class=CODE,delta=2
global __ptext47
__ptext47:
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
	global	_PA3
_PA3	set	43
	global	_PC3
_PC3	set	59
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
	file	"test_61f02x_io.as"
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
	global	?_POWER_INITIAL
?_POWER_INITIAL:	; 0 bytes @ 0x0
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x0
	global	?_DelayUs
?_DelayUs:	; 0 bytes @ 0x0
	global	??_DelayUs
??_DelayUs:	; 0 bytes @ 0x0
	global	?_DelayMs
?_DelayMs:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	DelayUs@Time
DelayUs@Time:	; 1 bytes @ 0x0
	ds	1
	global	DelayUs@a
DelayUs@a:	; 1 bytes @ 0x1
	ds	1
	global	??_DelayMs
??_DelayMs:	; 0 bytes @ 0x2
	global	DelayMs@Time
DelayMs@Time:	; 1 bytes @ 0x2
	ds	1
	global	DelayMs@a
DelayMs@a:	; 1 bytes @ 0x3
	ds	1
	global	DelayMs@b
DelayMs@b:	; 1 bytes @ 0x4
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x5
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      5       5
;; BANK0           80      0       0
;; BANK1           32      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_DelayMs
;;   _DelayMs->_DelayUs
;;
;; Critical Paths under _main in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
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
;; (0) _main                                                 0     0      0      90
;;                      _POWER_INITIAL
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (1) _DelayMs                                              3     3      0      90
;;                                              2 COMMON     3     3      0
;;                            _DelayUs
;; ---------------------------------------------------------------------------------
;; (2) _DelayUs                                              2     2      0      30
;;                                              0 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _DelayMs
;;     _DelayUs
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      5       5       1       35.7%
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
;;ABS                  0      0       0       7        0.0%
;;DATA                 0      0       0       8        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 90 in file "test_61f02x_IO.C"
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
;;		_DelayMs
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"test_61f02x_IO.C"
	line	90
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	91
	
l2163:	
;test_61f02x_IO.C: 91: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	94
	
l2165:	
;test_61f02x_IO.C: 93: {
;test_61f02x_IO.C: 94: PA3 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(43/8),(43)&7
	line	95
;test_61f02x_IO.C: 95: DelayMs(10);
	movlw	(0Ah)
	fcall	_DelayMs
	line	96
	
l2167:	
;test_61f02x_IO.C: 96: if(PC3 == 1)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(59/8),(59)&7
	goto	u41
	goto	u40
u41:
	goto	l2171
u40:
	line	98
	
l2169:	
;test_61f02x_IO.C: 97: {
;test_61f02x_IO.C: 98: PA3 = 0;
	bcf	(43/8),(43)&7
	line	100
	
l2171:	
;test_61f02x_IO.C: 99: }
;test_61f02x_IO.C: 100: DelayMs(10);
	movlw	(0Ah)
	fcall	_DelayMs
	goto	l2165
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	102
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_DelayMs
psect	text48,local,class=CODE,delta=2
global __ptext48
__ptext48:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 73 in file "test_61f02x_IO.C"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    2[COMMON] unsigned char 
;;  b               1    4[COMMON] unsigned char 
;;  a               1    3[COMMON] unsigned char 
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
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_DelayUs
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text48
	file	"test_61f02x_IO.C"
	line	73
	global	__size_of_DelayMs
	__size_of_DelayMs	equ	__end_of_DelayMs-_DelayMs
	
_DelayMs:	
	opt	stack 6
; Regs used in _DelayMs: [wreg+status,2+status,0+pclath+cstack]
;DelayMs@Time stored from wreg
	line	75
	movwf	(DelayMs@Time)
	
l2145:	
;test_61f02x_IO.C: 74: unsigned char a,b;
;test_61f02x_IO.C: 75: for(a=0;a<Time;a++)
	clrf	(DelayMs@a)
	goto	l2161
	line	77
	
l2147:	
;test_61f02x_IO.C: 76: {
;test_61f02x_IO.C: 77: for(b=0;b<5;b++)
	clrf	(DelayMs@b)
	line	79
	
l2153:	
;test_61f02x_IO.C: 78: {
;test_61f02x_IO.C: 79: DelayUs(197);
	movlw	(0C5h)
	fcall	_DelayUs
	line	77
	
l2155:	
	incf	(DelayMs@b),f
	
l2157:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u21
	goto	u20
u21:
	goto	l2153
u20:
	line	75
	
l2159:	
	incf	(DelayMs@a),f
	
l2161:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u31
	goto	u30
u31:
	goto	l2147
u30:
	line	82
	
l1081:	
	return
	opt stack 0
GLOBAL	__end_of_DelayMs
	__end_of_DelayMs:
;; =============== function _DelayMs ends ============

	signat	_DelayMs,4216
	global	_DelayUs
psect	text49,local,class=CODE,delta=2
global __ptext49
__ptext49:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 59 in file "test_61f02x_IO.C"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    0[COMMON] unsigned char 
;;  a               1    1[COMMON] unsigned char 
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
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_DelayMs
;; This function uses a non-reentrant model
;;
psect	text49
	file	"test_61f02x_IO.C"
	line	59
	global	__size_of_DelayUs
	__size_of_DelayUs	equ	__end_of_DelayUs-_DelayUs
	
_DelayUs:	
	opt	stack 6
; Regs used in _DelayUs: [wreg+status,2+status,0]
;DelayUs@Time stored from wreg
	line	61
	movwf	(DelayUs@Time)
	
l2139:	
;test_61f02x_IO.C: 60: unsigned char a;
;test_61f02x_IO.C: 61: for(a=0;a<Time;a++)
	clrf	(DelayUs@a)
	goto	l2143
	line	62
	
l1071:	
	line	63
;test_61f02x_IO.C: 62: {
;test_61f02x_IO.C: 63: _nop();
	nop
	line	61
	
l2141:	
	incf	(DelayUs@a),f
	
l2143:	
	movf	(DelayUs@Time),w
	subwf	(DelayUs@a),w
	skipc
	goto	u11
	goto	u10
u11:
	goto	l1071
u10:
	line	65
	
l1073:	
	return
	opt stack 0
GLOBAL	__end_of_DelayUs
	__end_of_DelayUs:
;; =============== function _DelayUs ends ============

	signat	_DelayUs,4216
	global	_POWER_INITIAL
psect	text50,local,class=CODE,delta=2
global __ptext50
__ptext50:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 34 in file "test_61f02x_IO.C"
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
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text50
	file	"test_61f02x_IO.C"
	line	34
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 7
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	35
	
l2121:	
;test_61f02x_IO.C: 35: OSCCON = 0B01110001;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
	line	36
	
l2123:	
;test_61f02x_IO.C: 36: INTCON = 0;
	clrf	(11)	;volatile
	line	37
	
l2125:	
;test_61f02x_IO.C: 37: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	38
	
l2127:	
;test_61f02x_IO.C: 38: TRISA = 0B00000000;
	bsf	status, 5	;RP0=1, select bank1
	clrf	(133)^080h	;volatile
	line	39
	
l2129:	
;test_61f02x_IO.C: 39: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	40
;test_61f02x_IO.C: 40: TRISC = 0B00001000;
	movlw	(08h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(135)^080h	;volatile
	line	42
	
l2131:	
;test_61f02x_IO.C: 42: WPUA = 0B00000000;
	clrf	(149)^080h	;volatile
	line	43
	
l2133:	
;test_61f02x_IO.C: 43: WPUC = 0B00001000;
	movlw	(08h)
	movwf	(136)^080h	;volatile
	line	45
	
l2135:	
;test_61f02x_IO.C: 45: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	46
	
l2137:	
;test_61f02x_IO.C: 46: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	50
;test_61f02x_IO.C: 50: CMCON0 = 0B00000111;
	movlw	(07h)
	movwf	(25)	;volatile
	line	51
	
l1067:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
psect	text51,local,class=CODE,delta=2
global __ptext51
__ptext51:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
