//Deviec:FT62F08X
//-----------------------Variable---------------------------------
//		DelayMs@Time		EQU		72H
//		DelayMs@b		EQU		74H
//		DelayMs@a		EQU		73H
//		DelayMs@Time		EQU		C00000H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		MOVLP 	0H 			//0000 	0180
		LJUMP 	8H 			//0001 	3808
		ORG		0003H
		NOP 					//0003 	1000
		BSR 	7EH, 0H 			//0004 	247E
		MOVLP 	0H 			//0005 	0180
		BCR 	7EH, 0H 			//0006 	207E
		RETI 					//0007 	1009
		MOVLP 	0H 			//0008 	0180
		LJUMP 	AH 			//0009 	380A
		BCR 	7EH, 0H 			//000A 	207E
		ORG		000BH
		MOVLB 	0H 			//000B 	1020
		LJUMP 	DH 			//000C 	380D

		//;test_FT62F08X_IO.C: 107: POWER_INITIAL();
		LCALL 	35H 			//000D 	3035
		MOVLP 	0H 			//000E 	0180

		//;test_FT62F08X_IO.C: 109: {
		//;test_FT62F08X_IO.C: 110: PB3 = 1;
		MOVLB 	0H 			//000F 	1020
		BSR 	DH, 3H 			//0010 	258D

		//;test_FT62F08X_IO.C: 111: DelayMs(10);
		LDWI 	AH 			//0011 	000A
		LCALL 	1BH 			//0012 	301B
		ORG		0013H
		MOVLP 	0H 			//0013 	0180

		//;test_FT62F08X_IO.C: 112: if(PC3 == 1)
		MOVLB 	0H 			//0014 	1020
		BTSC 	EH, 3H 			//0015 	298E

		//;test_FT62F08X_IO.C: 113: {
		//;test_FT62F08X_IO.C: 114: PB3 = 0;
		BCR 	DH, 3H 			//0016 	218D

		//;test_FT62F08X_IO.C: 115: }
		//;test_FT62F08X_IO.C: 116: DelayMs(10);
		LDWI 	AH 			//0017 	000A
		LCALL 	1BH 			//0018 	301B
		MOVLP 	0H 			//0019 	0180
		LJUMP 	FH 			//001A 	380F
		ORG		001BH
		STR 	72H 			//001B 	10F2

		//;test_FT62F08X_IO.C: 90: unsigned char a,b;
		//;test_FT62F08X_IO.C: 91: for(a=0;a<Time;a++)
		CLRF 	73H 			//001C 	11F3
		LDR 	72H, 0H 			//001D 	1872
		SUBWR 	73H, 0H 		//001E 	1273
		BTSC 	3H, 0H 			//001F 	2803
		RET 					//0020 	1008

		//;test_FT62F08X_IO.C: 92: {
		//;test_FT62F08X_IO.C: 93: for(b=0;b<5;b++)
		CLRF 	74H 			//0021 	11F4

		//;test_FT62F08X_IO.C: 94: {
		//;test_FT62F08X_IO.C: 95: DelayUs(197);
		LDWI 	C5H 			//0022 	00C5
		ORG		0023H
		LCALL 	2CH 			//0023 	302C
		MOVLP 	0H 			//0024 	0180
		LDWI 	5H 			//0025 	0005
		INCR 	74H, 1H 		//0026 	1AF4
		SUBWR 	74H, 0H 		//0027 	1274
		BTSS 	3H, 0H 			//0028 	2C03
		LJUMP 	22H 			//0029 	3822
		INCR 	73H, 1H 		//002A 	1AF3
		ORG		002BH
		LJUMP 	1DH 			//002B 	381D
		STR 	70H 			//002C 	10F0

		//;test_FT62F08X_IO.C: 76: unsigned char a;
		//;test_FT62F08X_IO.C: 77: for(a=0;a<Time;a++)
		CLRF 	71H 			//002D 	11F1
		LDR 	70H, 0H 			//002E 	1870
		SUBWR 	71H, 0H 		//002F 	1271
		BTSC 	3H, 0H 			//0030 	2803
		RET 					//0031 	1008

		//;test_FT62F08X_IO.C: 78: {
		//;test_FT62F08X_IO.C: 79: __nop();
		NOP 					//0032 	1000
		ORG		0033H
		INCR 	71H, 1H 		//0033 	1AF1
		LJUMP 	2EH 			//0034 	382E

		//;test_FT62F08X_IO.C: 36: OSCCON = 0B01110001;
		LDWI 	71H 			//0035 	0071
		MOVLB 	1H 			//0036 	1021
		STR 	19H 			//0037 	1099

		//;test_FT62F08X_IO.C: 37: INTCON = 0;
		CLRF 	BH 			//0038 	118B

		//;test_FT62F08X_IO.C: 39: PORTA = 0B00000000;
		MOVLB 	0H 			//0039 	1020
		CLRF 	CH 			//003A 	118C
		ORG		003BH

		//;test_FT62F08X_IO.C: 40: TRISA = 0B00000000;
		MOVLB 	1H 			//003B 	1021
		CLRF 	CH 			//003C 	118C

		//;test_FT62F08X_IO.C: 41: PORTB = 0B00000000;
		MOVLB 	0H 			//003D 	1020
		CLRF 	DH 			//003E 	118D

		//;test_FT62F08X_IO.C: 42: TRISB = 0B00000000;
		MOVLB 	1H 			//003F 	1021
		CLRF 	DH 			//0040 	118D

		//;test_FT62F08X_IO.C: 43: PORTC = 0B00000000;
		MOVLB 	0H 			//0041 	1020
		CLRF 	EH 			//0042 	118E
		ORG		0043H

		//;test_FT62F08X_IO.C: 44: TRISC = 0B00001000;
		LDWI 	8H 			//0043 	0008
		MOVLB 	1H 			//0044 	1021
		STR 	EH 			//0045 	108E

		//;test_FT62F08X_IO.C: 45: PORTD = 0B00000000;
		MOVLB 	0H 			//0046 	1020
		CLRF 	FH 			//0047 	118F

		//;test_FT62F08X_IO.C: 46: TRISD = 0B00000000;
		MOVLB 	1H 			//0048 	1021
		CLRF 	FH 			//0049 	118F

		//;test_FT62F08X_IO.C: 48: WPUA = 0B00000000;
		MOVLB 	3H 			//004A 	1023
		ORG		004BH
		CLRF 	CH 			//004B 	118C

		//;test_FT62F08X_IO.C: 49: WPUB = 0B00000000;
		CLRF 	DH 			//004C 	118D

		//;test_FT62F08X_IO.C: 50: WPUC = 0B00001000;
		STR 	EH 			//004D 	108E

		//;test_FT62F08X_IO.C: 51: WPUD = 0B00000000;
		CLRF 	FH 			//004E 	118F

		//;test_FT62F08X_IO.C: 53: WPDA = 0B00000000;
		MOVLB 	4H 			//004F 	1024
		CLRF 	CH 			//0050 	118C

		//;test_FT62F08X_IO.C: 54: WPDB = 0B00000000;
		CLRF 	DH 			//0051 	118D

		//;test_FT62F08X_IO.C: 55: WPDC = 0B00000000;
		CLRF 	EH 			//0052 	118E
		ORG		0053H

		//;test_FT62F08X_IO.C: 56: WPDD = 0B00000000;
		CLRF 	FH 			//0053 	118F

		//;test_FT62F08X_IO.C: 58: PSRC0 = 0B11111111;
		LDWI 	FFH 			//0054 	00FF
		MOVLB 	2H 			//0055 	1022
		STR 	1AH 			//0056 	109A

		//;test_FT62F08X_IO.C: 59: PSRC1 = 0B11111111;
		STR 	1BH 			//0057 	109B

		//;test_FT62F08X_IO.C: 61: PSINK0 = 0B11111111;
		MOVLB 	3H 			//0058 	1023
		STR 	1AH 			//0059 	109A

		//;test_FT62F08X_IO.C: 62: PSINK1 = 0B11111111;
		STR 	1BH 			//005A 	109B
		ORG		005BH

		//;test_FT62F08X_IO.C: 63: PSINK2 = 0B11111111;
		STR 	1CH 			//005B 	109C

		//;test_FT62F08X_IO.C: 64: PSINK3 = 0B11111111;
		STR 	1DH 			//005C 	109D

		//;test_FT62F08X_IO.C: 66: ANSELA = 0B00000000;
		CLRF 	17H 			//005D 	1197
		RET 					//005E 	1008
			END
