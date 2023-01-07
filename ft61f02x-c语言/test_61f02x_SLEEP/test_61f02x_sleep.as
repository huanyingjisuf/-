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
	FNCALL	_main,_DelayS
	FNCALL	_DelayS,_DelayMs
	FNCALL	_DelayMs,_DelayUs
	FNROOT	_main
	global	_PSTRCON
psect	text53,local,class=CODE,delta=2
global __ptext53
__ptext53:
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
	global	_WDTCON
_WDTCON	set	24
	global	_RA0
_RA0	set	40
	global	_RA1
_RA1	set	41
	global	_ANSEL
_ANSEL	set	145
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
	file	"test_61f02x_sleep.as"
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
	global	?_DelayS
?_DelayS:	; 0 bytes @ 0x0
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
	global	??_DelayS
??_DelayS:	; 0 bytes @ 0x5
	global	DelayS@Time
DelayS@Time:	; 1 bytes @ 0x5
	ds	1
	global	DelayS@a
DelayS@a:	; 1 bytes @ 0x6
	ds	1
	global	DelayS@b
DelayS@b:	; 1 bytes @ 0x7
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x8
;;Data sizes: Strings 0, constant 0, data 0, bss 0, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      8       8
;; BANK0           80      0       0
;; BANK1           32      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_DelayS
;;   _DelayS->_DelayMs
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
;; (0) _main                                                 0     0      0     150
;;                      _POWER_INITIAL
;;                             _DelayS
;; ---------------------------------------------------------------------------------
;; (1) _DelayS                                               3     3      0     150
;;                                              5 COMMON     3     3      0
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (2) _DelayMs                                              3     3      0      90
;;                                              2 COMMON     3     3      0
;;                            _DelayUs
;; ---------------------------------------------------------------------------------
;; (3) _DelayUs                                              2     2      0      30
;;                                              0 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _DelayS
;;     _DelayMs
;;       _DelayUs
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      8       8       1       57.1%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       3       2        0.0%
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
;;		line 131 in file "TEST_61F02X_SLEEP.C"
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
;;		_DelayS
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"TEST_61F02X_SLEEP.C"
	line	131
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 5
; Regs used in _main: [wreg+status,2+status,0+pclath+cstack]
	line	132
	
l2192:	
;TEST_61F02X_SLEEP.C: 132: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	133
	
l2194:	
;TEST_61F02X_SLEEP.C: 133: RA1 = 1;
	bsf	(41/8),(41)&7
	line	134
	
l2196:	
;TEST_61F02X_SLEEP.C: 134: RA0 = 1;
	bsf	(40/8),(40)&7
	line	135
;TEST_61F02X_SLEEP.C: 135: DelayS(4);
	movlw	(04h)
	fcall	_DelayS
	line	136
	
l2198:	
;TEST_61F02X_SLEEP.C: 136: RA1 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(41/8),(41)&7
	line	137
	
l2200:	
;TEST_61F02X_SLEEP.C: 137: RA0 = 0;
	bcf	(40/8),(40)&7
	line	140
	
l2202:	
# 140 "TEST_61F02X_SLEEP.C"
clrwdt ;#
psect	maintext
	line	141
	
l2204:	
;TEST_61F02X_SLEEP.C: 141: _nop();
	nop
	line	142
	
l2206:	
# 142 "TEST_61F02X_SLEEP.C"
sleep ;#
psect	maintext
	goto	l2202
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	144
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_DelayS
psect	text54,local,class=CODE,delta=2
global __ptext54
__ptext54:

;; *************** function _DelayS *****************
;; Defined at:
;;		line 115 in file "TEST_61F02X_SLEEP.C"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    5[COMMON] unsigned char 
;;  b               1    7[COMMON] unsigned char 
;;  a               1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: FFE00/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         3       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayMs
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text54
	file	"TEST_61F02X_SLEEP.C"
	line	115
	global	__size_of_DelayS
	__size_of_DelayS	equ	__end_of_DelayS-_DelayS
	
_DelayS:	
	opt	stack 5
; Regs used in _DelayS: [wreg+status,2+status,0+pclath+cstack]
;DelayS@Time stored from wreg
	line	117
	movwf	(DelayS@Time)
	
l2174:	
;TEST_61F02X_SLEEP.C: 116: unsigned char a,b;
;TEST_61F02X_SLEEP.C: 117: for(a=0;a<Time;a++)
	clrf	(DelayS@a)
	goto	l2190
	line	119
	
l2176:	
;TEST_61F02X_SLEEP.C: 118: {
;TEST_61F02X_SLEEP.C: 119: for(b=0;b<10;b++)
	clrf	(DelayS@b)
	line	121
	
l2182:	
;TEST_61F02X_SLEEP.C: 120: {
;TEST_61F02X_SLEEP.C: 121: DelayMs(100);
	movlw	(064h)
	fcall	_DelayMs
	line	119
	
l2184:	
	incf	(DelayS@b),f
	
l2186:	
	movlw	(0Ah)
	subwf	(DelayS@b),w
	skipc
	goto	u41
	goto	u40
u41:
	goto	l2182
u40:
	line	117
	
l2188:	
	incf	(DelayS@a),f
	
l2190:	
	movf	(DelayS@Time),w
	subwf	(DelayS@a),w
	skipc
	goto	u51
	goto	u50
u51:
	goto	l2176
u50:
	line	124
	
l1089:	
	return
	opt stack 0
GLOBAL	__end_of_DelayS
	__end_of_DelayS:
;; =============== function _DelayS ends ============

	signat	_DelayS,4216
	global	_DelayMs
psect	text55,local,class=CODE,delta=2
global __ptext55
__ptext55:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 98 in file "TEST_61F02X_SLEEP.C"
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
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: FFE00/0
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
;;		_DelayS
;; This function uses a non-reentrant model
;;
psect	text55
	file	"TEST_61F02X_SLEEP.C"
	line	98
	global	__size_of_DelayMs
	__size_of_DelayMs	equ	__end_of_DelayMs-_DelayMs
	
_DelayMs:	
	opt	stack 5
; Regs used in _DelayMs: [wreg+status,2+status,0+pclath+cstack]
;DelayMs@Time stored from wreg
	line	100
	movwf	(DelayMs@Time)
	
l2156:	
;TEST_61F02X_SLEEP.C: 99: unsigned char a,b;
;TEST_61F02X_SLEEP.C: 100: for(a=0;a<Time;a++)
	clrf	(DelayMs@a)
	goto	l2172
	line	102
	
l2158:	
;TEST_61F02X_SLEEP.C: 101: {
;TEST_61F02X_SLEEP.C: 102: for(b=0;b<5;b++)
	clrf	(DelayMs@b)
	line	104
	
l2164:	
;TEST_61F02X_SLEEP.C: 103: {
;TEST_61F02X_SLEEP.C: 104: DelayUs(197);
	movlw	(0C5h)
	fcall	_DelayUs
	line	102
	
l2166:	
	incf	(DelayMs@b),f
	
l2168:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u21
	goto	u20
u21:
	goto	l2164
u20:
	line	100
	
l2170:	
	incf	(DelayMs@a),f
	
l2172:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u31
	goto	u30
u31:
	goto	l2158
u30:
	line	107
	
l1081:	
	return
	opt stack 0
GLOBAL	__end_of_DelayMs
	__end_of_DelayMs:
;; =============== function _DelayMs ends ============

	signat	_DelayMs,4216
	global	_DelayUs
psect	text56,local,class=CODE,delta=2
global __ptext56
__ptext56:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 84 in file "TEST_61F02X_SLEEP.C"
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
;;		Unchanged: FFE00/0
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
psect	text56
	file	"TEST_61F02X_SLEEP.C"
	line	84
	global	__size_of_DelayUs
	__size_of_DelayUs	equ	__end_of_DelayUs-_DelayUs
	
_DelayUs:	
	opt	stack 5
; Regs used in _DelayUs: [wreg+status,2+status,0]
;DelayUs@Time stored from wreg
	line	86
	movwf	(DelayUs@Time)
	
l2150:	
;TEST_61F02X_SLEEP.C: 85: unsigned char a;
;TEST_61F02X_SLEEP.C: 86: for(a=0;a<Time;a++)
	clrf	(DelayUs@a)
	goto	l2154
	line	87
	
l1071:	
	line	88
# 88 "TEST_61F02X_SLEEP.C"
clrwdt ;#
psect	text56
	line	86
	
l2152:	
	incf	(DelayUs@a),f
	
l2154:	
	movf	(DelayUs@Time),w
	subwf	(DelayUs@a),w
	skipc
	goto	u11
	goto	u10
u11:
	goto	l1071
u10:
	line	90
	
l1073:	
	return
	opt stack 0
GLOBAL	__end_of_DelayUs
	__end_of_DelayUs:
;; =============== function _DelayUs ends ============

	signat	_DelayUs,4216
	global	_POWER_INITIAL
psect	text57,local,class=CODE,delta=2
global __ptext57
__ptext57:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 54 in file "TEST_61F02X_SLEEP.C"
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
psect	text57
	file	"TEST_61F02X_SLEEP.C"
	line	54
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 7
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	55
	
l2128:	
;TEST_61F02X_SLEEP.C: 55: OSCCON = 0X00|0X70|0X01;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(143)^080h	;volatile
	line	59
	
l2130:	
;TEST_61F02X_SLEEP.C: 59: INTCON = 0;
	clrf	(11)	;volatile
	line	60
	
l2132:	
;TEST_61F02X_SLEEP.C: 60: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	61
	
l2134:	
;TEST_61F02X_SLEEP.C: 61: TRISA = 0B00000000;
	bsf	status, 5	;RP0=1, select bank1
	clrf	(133)^080h	;volatile
	line	62
	
l2136:	
;TEST_61F02X_SLEEP.C: 62: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	63
	
l2138:	
;TEST_61F02X_SLEEP.C: 63: TRISC = 0B00000000;
	bsf	status, 5	;RP0=1, select bank1
	clrf	(135)^080h	;volatile
	line	65
	
l2140:	
;TEST_61F02X_SLEEP.C: 65: WPUA = 0B00000000;
	clrf	(149)^080h	;volatile
	line	66
	
l2142:	
;TEST_61F02X_SLEEP.C: 66: WPUC = 0B00000000;
	clrf	(136)^080h	;volatile
	line	68
	
l2144:	
;TEST_61F02X_SLEEP.C: 68: ANSEL = 0B00000000;
	clrf	(145)^080h	;volatile
	line	69
;TEST_61F02X_SLEEP.C: 69: OPTION = 0B00001000;
	movlw	(08h)
	movwf	(129)^080h	;volatile
	line	71
;TEST_61F02X_SLEEP.C: 71: WDTCON = 0B00010001;
	movlw	(011h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(24)	;volatile
	line	72
	
l2146:	
;TEST_61F02X_SLEEP.C: 72: MSCKCON = 0B00000000;
	clrf	(27)	;volatile
	line	75
	
l2148:	
;TEST_61F02X_SLEEP.C: 75: CMCON0 = 0B00000111;
	movlw	(07h)
	movwf	(25)	;volatile
	line	76
	
l1067:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
psect	text58,local,class=CODE,delta=2
global __ptext58
__ptext58:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
