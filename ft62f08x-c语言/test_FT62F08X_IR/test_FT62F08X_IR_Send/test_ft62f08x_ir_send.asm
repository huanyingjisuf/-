//Deviec:FT62F08X
//-----------------------Variable---------------------------------
		_IRSendStatus		EQU		79H
		_IRSendData		EQU		78H
		_TxBit		EQU		77H
		_TxTime		EQU		76H
		_Sendbit		EQU		75H
		_level0		EQU		74H
		_level1		EQU		73H
		_SendLastBit		EQU		7DH
		_SaveLastBit		EQU		72H
		_SYSTime5S		EQU		70H
		_IRData		EQU		20H
//-----------------------Variable END---------------------------------
		ORG		0000H
		MOVLP 	0H 			//0000 	0180
		LJUMP 	1DH 			//0001 	381D
		ORG		0003H
		NOP 					//0003 	1000
		BSR 	7EH, 0H 			//0005 	247E

		//;test_FT62F08X_IR_Send.C: 375: if(T4UIE && T4UIF)
		MOVLP 	0H 			//0006 	0180
		MOVLB 	2H 			//0007 	1022
		BTSC 	12H, 0H 		//0008 	2812
		BTSS 	13H, 0H 		//0008 	2C13
		LJUMP 	13H 			//0009 	3813

		//;test_FT62F08X_IR_Send.C: 376: {
		//;test_FT62F08X_IR_Send.C: 377: T4UIF = 1;
		BSR 	13H, 0H 			//000A 	2413
		ORG		000BH

		//;test_FT62F08X_IR_Send.C: 379: SendCtrl();
		MOVLP 	0H 			//000B 	0180
		LCALL 	8FH 			//000C 	308F
		MOVLP 	0H 			//000D 	0180

		//;test_FT62F08X_IR_Send.C: 380: SYSTime5S++;
		INCR 	70H, 1H 		//000E 	1AF0
		BTSC 	3H, 2H 			//000F 	2903
		INCR 	71H, 1H 		//0010 	1AF1

		//;test_FT62F08X_IR_Send.C: 381: PB3=0;
		MOVLB 	0H 			//0011 	1020
		BCR 	DH, 3H 			//0012 	218D
		ORG		0013H

		//;test_FT62F08X_IR_Send.C: 382: }
		//;test_FT62F08X_IR_Send.C: 384: if(T2UIE && T2UIF)
		MOVLB 	6H 			//0013 	1026
		BTSC 	DH, 0H 			//0014 	280D
		BTSS 	EH, 0H 			//0015 	2C0E
		LJUMP 	1BH 			//0016 	381B

		//;test_FT62F08X_IR_Send.C: 385: {
		//;test_FT62F08X_IR_Send.C: 386: T2UIF = 1;
		BSR 	EH, 0H 			//0017 	240E

		//;test_FT62F08X_IR_Send.C: 388: PB3 = ~PB3;
		LDWI 	8H 			//0018 	0008
		MOVLB 	0H 			//0019 	1020
		XORWR 	DH, 1H 		//001A 	168D
		ORG		001BH
		BCR 	7EH, 0H 			//001B 	207E
		RETI 					//001C 	1009
		MOVLP 	0H 			//001D 	0180
		LJUMP 	1FH 			//001E 	381F
		LDWI 	FFH 			//001F 	00FF
		CLRF 	20H 			//0020 	11A0
		STR 	21H 			//0021 	10A1
		LDWI 	40H 			//0022 	0040
		ORG		0023H
		STR 	22H 			//0023 	10A2
		LDWI 	BFH 			//0024 	00BF
		STR 	23H 			//0025 	10A3
		CLRF 	7DH 			//0026 	11FD
		CLRF 	70H 			//0027 	11F0
		CLRF 	71H 			//0028 	11F1
		CLRF 	72H 			//0029 	11F2
		CLRF 	73H 			//002A 	11F3
		ORG		002BH
		CLRF 	74H 			//002B 	11F4
		CLRF 	75H 			//002C 	11F5
		CLRF 	76H 			//002D 	11F6
		CLRF 	77H 			//002E 	11F7
		CLRF 	78H 			//002F 	11F8
		CLRF 	79H 			//0030 	11F9
		BCR 	7EH, 0H 			//0031 	207E
		MOVLB 	0H 			//0032 	1020
		ORG		0033H
		LJUMP 	34H 			//0033 	3834

		//;test_FT62F08X_IR_Send.C: 399: POWER_INITIAL();
		LCALL 	47H 			//0034 	3047
		MOVLP 	0H 			//0035 	0180

		//;test_FT62F08X_IR_Send.C: 400: TIMER4_INITIAL();
		LCALL 	82H 			//0036 	3082
		MOVLP 	0H 			//0037 	0180

		//;test_FT62F08X_IR_Send.C: 401: TIMER2_INITIAL();
		LCALL 	72H 			//0038 	3072
		MOVLP 	0H 			//0039 	0180

		//;test_FT62F08X_IR_Send.C: 402: GIE = 1;
		BSR 	BH, 7H 			//003A 	278B
		ORG		003BH

		//;test_FT62F08X_IR_Send.C: 404: {
		//;test_FT62F08X_IR_Send.C: 405: if(SYSTime5S >5000)
		LDWI 	13H 			//003B 	0013
		SUBWR 	71H, 0H 		//003C 	1271
		LDWI 	89H 			//003D 	0089
		BTSC 	3H, 2H 			//003E 	2903
		SUBWR 	70H, 0H 		//003F 	1270
		BTSS 	3H, 0H 			//0040 	2C03
		LJUMP 	3BH 			//0041 	383B

		//;test_FT62F08X_IR_Send.C: 406: {
		//;test_FT62F08X_IR_Send.C: 407: SYSTime5S = 0;
		CLRF 	70H 			//0042 	11F0
		ORG		0043H
		CLRF 	71H 			//0043 	11F1

		//;test_FT62F08X_IR_Send.C: 408: IRSendStatus = 1;
		CLRF 	79H 			//0044 	11F9
		INCR 	79H, 1H 		//0045 	1AF9
		LJUMP 	3BH 			//0046 	383B

		//;test_FT62F08X_IR_Send.C: 52: OSCCON = 0B01110001;
		LDWI 	71H 			//0047 	0071
		MOVLB 	1H 			//0048 	1021
		STR 	19H 			//0049 	1099

		//;test_FT62F08X_IR_Send.C: 53: PCKEN |= 0B00001100;
		LDWI 	CH 			//004A 	000C
		ORG		004BH
		IORWR 	1AH, 1H 		//004B 	149A

		//;test_FT62F08X_IR_Send.C: 54: INTCON = 0;
		CLRF 	BH 			//004C 	118B

		//;test_FT62F08X_IR_Send.C: 56: PORTA = 0B00000000;
		MOVLB 	0H 			//004D 	1020
		CLRF 	CH 			//004E 	118C

		//;test_FT62F08X_IR_Send.C: 57: TRISA = 0B00000000;
		MOVLB 	1H 			//004F 	1021
		CLRF 	CH 			//0050 	118C

		//;test_FT62F08X_IR_Send.C: 58: PORTB = 0B00000000;
		MOVLB 	0H 			//0051 	1020
		CLRF 	DH 			//0052 	118D
		ORG		0053H

		//;test_FT62F08X_IR_Send.C: 59: TRISB = 0B00000000;
		MOVLB 	1H 			//0053 	1021
		CLRF 	DH 			//0054 	118D

		//;test_FT62F08X_IR_Send.C: 60: PORTC = 0B00000000;
		MOVLB 	0H 			//0055 	1020
		CLRF 	EH 			//0056 	118E

		//;test_FT62F08X_IR_Send.C: 61: TRISC = 0B00000000;
		MOVLB 	1H 			//0057 	1021
		CLRF 	EH 			//0058 	118E

		//;test_FT62F08X_IR_Send.C: 62: PORTD = 0B00000000;
		MOVLB 	0H 			//0059 	1020
		CLRF 	FH 			//005A 	118F
		ORG		005BH

		//;test_FT62F08X_IR_Send.C: 63: TRISD = 0B00000000;
		MOVLB 	1H 			//005B 	1021
		CLRF 	FH 			//005C 	118F

		//;test_FT62F08X_IR_Send.C: 65: WPUA = 0B00000000;
		MOVLB 	3H 			//005D 	1023
		CLRF 	CH 			//005E 	118C

		//;test_FT62F08X_IR_Send.C: 66: WPUB = 0B00000000;
		CLRF 	DH 			//005F 	118D

		//;test_FT62F08X_IR_Send.C: 67: WPUC = 0B00000000;
		CLRF 	EH 			//0060 	118E

		//;test_FT62F08X_IR_Send.C: 68: WPUD = 0B00000000;
		CLRF 	FH 			//0061 	118F

		//;test_FT62F08X_IR_Send.C: 70: WPDA = 0B00000000;
		MOVLB 	4H 			//0062 	1024
		ORG		0063H
		CLRF 	CH 			//0063 	118C

		//;test_FT62F08X_IR_Send.C: 71: WPDB = 0B00000000;
		CLRF 	DH 			//0064 	118D

		//;test_FT62F08X_IR_Send.C: 72: WPDC = 0B00000000;
		CLRF 	EH 			//0065 	118E

		//;test_FT62F08X_IR_Send.C: 73: WPDD = 0B00000000;
		CLRF 	FH 			//0066 	118F

		//;test_FT62F08X_IR_Send.C: 75: PSRC0 = 0B11111111;
		LDWI 	FFH 			//0067 	00FF
		MOVLB 	2H 			//0068 	1022
		STR 	1AH 			//0069 	109A

		//;test_FT62F08X_IR_Send.C: 76: PSRC1 = 0B11111111;
		STR 	1BH 			//006A 	109B
		ORG		006BH

		//;test_FT62F08X_IR_Send.C: 78: PSINK0 = 0B11111111;
		MOVLB 	3H 			//006B 	1023
		STR 	1AH 			//006C 	109A

		//;test_FT62F08X_IR_Send.C: 79: PSINK1 = 0B11111111;
		STR 	1BH 			//006D 	109B

		//;test_FT62F08X_IR_Send.C: 80: PSINK2 = 0B11111111;
		STR 	1CH 			//006E 	109C

		//;test_FT62F08X_IR_Send.C: 81: PSINK3 = 0B11111111;
		STR 	1DH 			//006F 	109D

		//;test_FT62F08X_IR_Send.C: 83: ANSELA = 0B00000000;
		CLRF 	17H 			//0070 	1197
		RET 					//0071 	1008

		//;test_FT62F08X_IR_Send.C: 162: CKOCON=0B00100000;
		LDWI 	20H 			//0072 	0020
		ORG		0073H
		MOVLB 	1H 			//0073 	1021
		STR 	15H 			//0074 	1095

		//;test_FT62F08X_IR_Send.C: 163: TCKSRC=0B00110000;
		LDWI 	30H 			//0075 	0030
		MOVLB 	6H 			//0076 	1026
		STR 	1FH 			//0077 	109F

		//;test_FT62F08X_IR_Send.C: 188: TIM2CR1 =0B10000101;
		LDWI 	85H 			//0078 	0085
		STR 	CH 			//0079 	108C

		//;test_FT62F08X_IR_Send.C: 219: TIM2IER = 0B00000000;
		CLRF 	DH 			//007A 	118D
		ORG		007BH

		//;test_FT62F08X_IR_Send.C: 238: TIM2ARRH =0x01;
		LDWI 	1H 			//007B 	0001
		STR 	19H 			//007C 	1099

		//;test_FT62F08X_IR_Send.C: 239: TIM2ARRL =0xA0;
		LDWI 	A0H 			//007D 	00A0
		STR 	1AH 			//007E 	109A

		//;test_FT62F08X_IR_Send.C: 241: INTCON = 0B11000000;
		LDWI 	C0H 			//007F 	00C0
		STR 	BH 			//0080 	108B
		RET 					//0081 	1008

		//;test_FT62F08X_IR_Send.C: 93: TIM4CR1 =0B00000101;
		LDWI 	5H 			//0082 	0005
		ORG		0083H
		MOVLB 	2H 			//0083 	1022
		STR 	11H 			//0084 	1091

		//;test_FT62F08X_IR_Send.C: 125: TIM4IER = 0B00000001;
		LDWI 	1H 			//0085 	0001
		STR 	12H 			//0086 	1092

		//;test_FT62F08X_IR_Send.C: 128: TIM4SR = 0B00000000;
		CLRF 	13H 			//0087 	1193

		//;test_FT62F08X_IR_Send.C: 137: TIM4EGR = 0B00000000;
		CLRF 	14H 			//0088 	1194

		//;test_FT62F08X_IR_Send.C: 143: TIM4CNTR = 0;
		CLRF 	15H 			//0089 	1195

		//;test_FT62F08X_IR_Send.C: 145: TIM4PSCR = 0B00000110;
		LDWI 	6H 			//008A 	0006
		ORG		008BH
		STR 	16H 			//008B 	1096

		//;test_FT62F08X_IR_Send.C: 151: TIM4ARR = 140;
		LDWI 	8CH 			//008C 	008C
		STR 	17H 			//008D 	1097
		RET 					//008E 	1008

		//;test_FT62F08X_IR_Send.C: 252: if (IRSendStatus == 0)
		LDR 	79H, 0H 			//008F 	1879
		BTSS 	3H, 2H 			//0090 	2D03
		LJUMP 	97H 			//0091 	3897

		//;test_FT62F08X_IR_Send.C: 253: {
		//;test_FT62F08X_IR_Send.C: 254: T2UIE = 0;
		MOVLB 	6H 			//0092 	1026
		ORG		0093H
		BCR 	DH, 0H 			//0093 	200D

		//;test_FT62F08X_IR_Send.C: 255: Sendbit = 0;
		CLRF 	75H 			//0094 	11F5

		//;test_FT62F08X_IR_Send.C: 256: TxTime = 0;
		CLRF 	76H 			//0095 	11F6

		//;test_FT62F08X_IR_Send.C: 258: }
		RET 					//0096 	1008

		//;test_FT62F08X_IR_Send.C: 259: else if (IRSendStatus == 1)
		DECRSZ 	79H, 0H 		//0097 	1B79
		LJUMP 	B1H 			//0098 	38B1
		LDWI 	11H 			//0099 	0011

		//;test_FT62F08X_IR_Send.C: 260: {
		//;test_FT62F08X_IR_Send.C: 261: TxTime++;
		INCR 	76H, 1H 		//009A 	1AF6
		ORG		009BH

		//;test_FT62F08X_IR_Send.C: 262: if (TxTime < 17)
		SUBWR 	76H, 0H 		//009B 	1276
		BTSC 	3H, 0H 			//009C 	2803
		LJUMP 	A1H 			//009D 	38A1

		//;test_FT62F08X_IR_Send.C: 263: {
		//;test_FT62F08X_IR_Send.C: 264: T2UIE = 1;
		MOVLB 	6H 			//009E 	1026
		BSR 	DH, 0H 			//009F 	240D

		//;test_FT62F08X_IR_Send.C: 265: }
		LJUMP 	ABH 			//00A0 	38AB

		//;test_FT62F08X_IR_Send.C: 266: else if (TxTime < 24)
		LDWI 	18H 			//00A1 	0018
		SUBWR 	76H, 0H 		//00A2 	1276
		ORG		00A3H
		BTSC 	3H, 0H 			//00A3 	2803
		LJUMP 	A8H 			//00A4 	38A8

		//;test_FT62F08X_IR_Send.C: 267: {
		//;test_FT62F08X_IR_Send.C: 268: T2UIE = 0;
		MOVLB 	6H 			//00A5 	1026
		BCR 	DH, 0H 			//00A6 	200D

		//;test_FT62F08X_IR_Send.C: 269: }
		LJUMP 	ABH 			//00A7 	38AB
		LDWI 	2H 			//00A8 	0002

		//;test_FT62F08X_IR_Send.C: 270: else
		//;test_FT62F08X_IR_Send.C: 271: {
		//;test_FT62F08X_IR_Send.C: 272: TxTime = 0;
		CLRF 	76H 			//00A9 	11F6

		//;test_FT62F08X_IR_Send.C: 273: IRSendStatus = 2;
		STR 	79H 			//00AA 	10F9
		ORG		00ABH

		//;test_FT62F08X_IR_Send.C: 274: }
		//;test_FT62F08X_IR_Send.C: 275: IRSendData = IRData[0];
		MOVLB 	0H 			//00AB 	1020
		LDR 	20H, 0H 			//00AC 	1820
		STR 	78H 			//00AD 	10F8

		//;test_FT62F08X_IR_Send.C: 276: TxBit = 0x01;
		CLRF 	77H 			//00AE 	11F7
		INCR 	77H, 1H 		//00AF 	1AF7

		//;test_FT62F08X_IR_Send.C: 277: }
		RET 					//00B0 	1008

		//;test_FT62F08X_IR_Send.C: 278: else if(IRSendStatus == 2)
		LDWI 	2H 			//00B1 	0002
		XORWR 	79H, 0H 		//00B2 	1679
		ORG		00B3H
		BTSS 	3H, 2H 			//00B3 	2D03
		RET 					//00B4 	1008

		//;test_FT62F08X_IR_Send.C: 279: {
		//;test_FT62F08X_IR_Send.C: 280: if (IRSendData & TxBit)
		LDR 	78H, 0H 			//00B5 	1878
		ANDWR 	77H, 0H 		//00B6 	1577
		BTSC 	3H, 2H 			//00B7 	2903
		LJUMP 	BEH 			//00B8 	38BE
		LDWI 	3H 			//00B9 	0003

		//;test_FT62F08X_IR_Send.C: 281: {
		//;test_FT62F08X_IR_Send.C: 282: level1 = 1;
		CLRF 	73H 			//00BA 	11F3
		ORG		00BBH
		INCR 	73H, 1H 		//00BB 	1AF3

		//;test_FT62F08X_IR_Send.C: 283: level0 = 3;
		STR 	74H 			//00BC 	10F4

		//;test_FT62F08X_IR_Send.C: 284: }
		LJUMP 	C2H 			//00BD 	38C2

		//;test_FT62F08X_IR_Send.C: 285: else
		//;test_FT62F08X_IR_Send.C: 286: {
		//;test_FT62F08X_IR_Send.C: 287: level1 = 1;
		CLRF 	73H 			//00BE 	11F3
		INCR 	73H, 1H 		//00BF 	1AF3

		//;test_FT62F08X_IR_Send.C: 288: level0 = 1;
		CLRF 	74H 			//00C0 	11F4
		INCR 	74H, 1H 		//00C1 	1AF4

		//;test_FT62F08X_IR_Send.C: 289: }
		//;test_FT62F08X_IR_Send.C: 290: TxTime++;
		INCR 	76H, 1H 		//00C2 	1AF6
		ORG		00C3H

		//;test_FT62F08X_IR_Send.C: 291: if (TxTime <= level1)
		LDR 	76H, 0H 			//00C3 	1876
		SUBWR 	73H, 0H 		//00C4 	1273
		BTSS 	3H, 0H 			//00C5 	2C03
		LJUMP 	CAH 			//00C6 	38CA

		//;test_FT62F08X_IR_Send.C: 292: {
		//;test_FT62F08X_IR_Send.C: 293: T2UIE = 1;
		MOVLB 	6H 			//00C7 	1026
		BSR 	DH, 0H 			//00C8 	240D

		//;test_FT62F08X_IR_Send.C: 294: }
		RET 					//00C9 	1008

		//;test_FT62F08X_IR_Send.C: 295: else if (TxTime <= (level0+level1))
		LDR 	74H, 0H 			//00CA 	1874
		ORG		00CBH
		ADDWR 	73H, 0H 		//00CB 	1773
		STR 	7AH 			//00CC 	10FA
		CLRF 	7BH 			//00CD 	11FB
		RLR 	7BH, 1H 			//00CE 	1DFB
		LDR 	7BH, 0H 			//00CF 	187B
		XORWI 	80H 			//00D0 	0A80
		STR 	7CH 			//00D1 	10FC
		LDWI 	80H 			//00D2 	0080
		ORG		00D3H
		SUBWR 	7CH, 0H 		//00D3 	127C
		BTSS 	3H, 2H 			//00D4 	2D03
		LJUMP 	D8H 			//00D5 	38D8
		LDR 	76H, 0H 			//00D6 	1876
		SUBWR 	7AH, 0H 		//00D7 	127A
		BTSS 	3H, 0H 			//00D8 	2C03
		LJUMP 	DDH 			//00D9 	38DD

		//;test_FT62F08X_IR_Send.C: 296: {
		//;test_FT62F08X_IR_Send.C: 297: T2UIE = 0;
		MOVLB 	6H 			//00DA 	1026
		ORG		00DBH
		BCR 	DH, 0H 			//00DB 	200D

		//;test_FT62F08X_IR_Send.C: 298: }
		RET 					//00DC 	1008

		//;test_FT62F08X_IR_Send.C: 299: else if (Sendbit < 4)
		LDWI 	4H 			//00DD 	0004
		SUBWR 	75H, 0H 		//00DE 	1275
		BTSC 	3H, 0H 			//00DF 	2803
		LJUMP 	FBH 			//00E0 	38FB

		//;test_FT62F08X_IR_Send.C: 300: {
		//;test_FT62F08X_IR_Send.C: 301: TxTime = 1;
		CLRF 	76H 			//00E1 	11F6
		INCR 	76H, 1H 		//00E2 	1AF6
		ORG		00E3H

		//;test_FT62F08X_IR_Send.C: 302: T2UIE = 1;
		MOVLB 	6H 			//00E3 	1026
		BSR 	DH, 0H 			//00E4 	240D

		//;test_FT62F08X_IR_Send.C: 303: SaveLastBit = IRSendData & TxBit;
		LDR 	78H, 0H 			//00E5 	1878
		STR 	72H 			//00E6 	10F2
		LDR 	77H, 0H 			//00E7 	1877
		ANDWR 	72H, 1H 		//00E8 	15F2

		//;test_FT62F08X_IR_Send.C: 304: TxBit <<= 1;
		LSLF 	77H, 1H 		//00E9 	05F7

		//;test_FT62F08X_IR_Send.C: 305: if (TxBit == 0x00)
		LDR 	77H, 0H 			//00EA 	1877
		ORG		00EBH
		BTSS 	3H, 2H 			//00EB 	2D03
		RET 					//00EC 	1008

		//;test_FT62F08X_IR_Send.C: 306: {
		//;test_FT62F08X_IR_Send.C: 307: TxBit = 0x01;
		CLRF 	77H 			//00ED 	11F7
		INCR 	77H, 1H 		//00EE 	1AF7

		//;test_FT62F08X_IR_Send.C: 308: Sendbit++;
		INCR 	75H, 1H 		//00EF 	1AF5

		//;test_FT62F08X_IR_Send.C: 309: IRSendData = IRData[Sendbit];
		LDR 	75H, 0H 			//00F0 	1875
		ADDWI 	20H 			//00F1 	0E20
		STR 	6H 			//00F2 	1086
		ORG		00F3H
		CLRF 	7H 			//00F3 	1187
		LDR 	1H, 0H 			//00F4 	1801
		STR 	78H 			//00F5 	10F8

		//;test_FT62F08X_IR_Send.C: 310: if (Sendbit > 3)
		LDWI 	4H 			//00F6 	0004
		SUBWR 	75H, 0H 		//00F7 	1275
		BTSC 	3H, 0H 			//00F8 	2803

		//;test_FT62F08X_IR_Send.C: 311: {
		//;test_FT62F08X_IR_Send.C: 312: SendLastBit = 1;
		BSR 	7DH, 0H 			//00F9 	247D
		RET 					//00FA 	1008
		ORG		00FBH

		//;test_FT62F08X_IR_Send.C: 316: else
		//;test_FT62F08X_IR_Send.C: 317: {
		//;test_FT62F08X_IR_Send.C: 318: if(SendLastBit)
		BTSS 	7DH, 0H 		//00FB 	2C7D
		RET 					//00FC 	1008

		//;test_FT62F08X_IR_Send.C: 319: {
		//;test_FT62F08X_IR_Send.C: 320: TxTime++;
		INCR 	76H, 1H 		//00FD 	1AF6

		//;test_FT62F08X_IR_Send.C: 321: if(SaveLastBit)
		LDR 	72H, 0H 			//00FE 	1872
		BTSC 	3H, 2H 			//00FF 	2903
		LJUMP 	111H 			//0100 	3911

		//;test_FT62F08X_IR_Send.C: 322: {
		//;test_FT62F08X_IR_Send.C: 323: if(TxTime < 3)
		LDWI 	3H 			//0101 	0003
		SUBWR 	76H, 0H 		//0102 	1276
		ORG		0103H
		BTSS 	3H, 0H 			//0103 	2C03
		LJUMP 	DAH 			//0104 	38DA

		//;test_FT62F08X_IR_Send.C: 327: else if(TxTime < 4)
		LDWI 	4H 			//0105 	0004
		SUBWR 	76H, 0H 		//0106 	1276
		BTSS 	3H, 0H 			//0107 	2C03
		LJUMP 	C7H 			//0108 	38C7

		//;test_FT62F08X_IR_Send.C: 331: else
		//;test_FT62F08X_IR_Send.C: 332: {
		//;test_FT62F08X_IR_Send.C: 333: T2UIE = 0;
		MOVLB 	6H 			//0109 	1026
		BCR 	DH, 0H 			//010A 	200D
		ORG		010BH

		//;test_FT62F08X_IR_Send.C: 334: IRSendStatus = 0;
		CLRF 	79H 			//010B 	11F9

		//;test_FT62F08X_IR_Send.C: 335: T2UIE = 0;
		BCR 	DH, 0H 			//010C 	200D

		//;test_FT62F08X_IR_Send.C: 336: SendLastBit = 0;
		BCR 	7DH, 0H 			//010D 	207D

		//;test_FT62F08X_IR_Send.C: 337: TxBit = 0;
		CLRF 	77H 			//010E 	11F7

		//;test_FT62F08X_IR_Send.C: 338: TxTime = 0;
		CLRF 	76H 			//010F 	11F6
		RET 					//0110 	1008

		//;test_FT62F08X_IR_Send.C: 341: else
		//;test_FT62F08X_IR_Send.C: 342: {
		//;test_FT62F08X_IR_Send.C: 343: if(TxTime < 5)
		LDWI 	5H 			//0111 	0005
		SUBWR 	76H, 0H 		//0112 	1276
		ORG		0113H
		BTSS 	3H, 0H 			//0113 	2C03
		LJUMP 	DAH 			//0114 	38DA

		//;test_FT62F08X_IR_Send.C: 347: else if(TxTime < 6)
		LDWI 	6H 			//0115 	0006
		LJUMP 	106H 			//0116 	3906
			END
