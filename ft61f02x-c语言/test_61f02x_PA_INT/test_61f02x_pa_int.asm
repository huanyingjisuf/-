//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_FCount		EQU		77H
//		DelayMs@Time		EQU		74H
//		DelayMs@b		EQU		76H
//		DelayMs@a		EQU		75H
//		DelayMs@Time		EQU		C00000H
//		DelayUs@Time		EQU		72H
//		DelayUs@a		EQU		73H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		LJUMP 	38H 			//0009 	3838
		LJUMP 	0BH 			//000A 	380B
		CLRR 	STATUS 			//000B 	0103
		ORG		000CH
		LJUMP 	23H 			//000C 	3823

		//;test_61f02x_PA_INT.C: 55: OSCCON = 0B01110001;
		LDWI 	71H 			//000D 	2A71
		BSR 	STATUS,5 		//000E 	1A83
		STR 	FH 			//000F 	018F

		//;test_61f02x_PA_INT.C: 56: INTCON = 0;
		CLRR 	INTCON 			//0010 	010B

		//;test_61f02x_PA_INT.C: 57: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0011 	1283
		CLRR 	5H 			//0012 	0105

		//;test_61f02x_PA_INT.C: 58: TRISA = 0B00000100;
		LDWI 	4H 			//0013 	2A04
		ORG		0014H
		BSR 	STATUS,5 		//0014 	1A83
		STR 	5H 			//0015 	0185

		//;test_61f02x_PA_INT.C: 60: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0016 	1283
		CLRR 	7H 			//0017 	0107

		//;test_61f02x_PA_INT.C: 61: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0018 	1A83
		CLRR 	7H 			//0019 	0107

		//;test_61f02x_PA_INT.C: 62: WPUA = 0B00000000;
		CLRR 	15H 			//001A 	0115

		//;test_61f02x_PA_INT.C: 63: WPUC = 0B00000000;
		CLRR 	8H 			//001B 	0108
		ORG		001CH

		//;test_61f02x_PA_INT.C: 65: OPTION = 0B00001000;
		LDWI 	8H 			//001C 	2A08
		STR 	1H 			//001D 	0181

		//;test_61f02x_PA_INT.C: 66: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//001E 	1283
		CLRR 	1BH 			//001F 	011B

		//;test_61f02x_PA_INT.C: 70: CMCON0 = 0B00000111;
		LDWI 	7H 			//0020 	2A07
		STR 	19H 			//0021 	0199
		RET		 					//0022 	0004

		//;test_61f02x_PA_INT.C: 126: POWER_INITIAL();
		LCALL 	DH 			//0023 	300D
		ORG		0024H

		//;test_61f02x_PA_INT.C: 129: {
		//;test_61f02x_PA_INT.C: 130: for(FCount=0;FCount<100;FCount++)
		CLRR 	77H 			//0024 	0177

		//;test_61f02x_PA_INT.C: 131: {
		//;test_61f02x_PA_INT.C: 132: PA3 = 1;
		BCR 	STATUS,5 		//0025 	1283
		BCR 	STATUS,6 		//0026 	1303
		BSR 	5H,3 			//0027 	1985

		//;test_61f02x_PA_INT.C: 133: DelayMs(10);
		LDWI 	AH 			//0028 	2A0A
		LCALL 	49H 			//0029 	3049

		//;test_61f02x_PA_INT.C: 134: PA3 = 0;
		BCR 	STATUS,5 		//002A 	1283
		BCR 	STATUS,6 		//002B 	1303
		ORG		002CH
		BCR 	5H,3 			//002C 	1185

		//;test_61f02x_PA_INT.C: 135: DelayMs(10);
		LDWI 	AH 			//002D 	2A0A
		LCALL 	49H 			//002E 	3049
		LDWI 	64H 			//002F 	2A64
		INCR	77H,1 			//0030 	09F7
		SUBWR 	77H,0 			//0031 	0C77
		BTSS 	STATUS,0 		//0032 	1C03
		LJUMP 	25H 			//0033 	3825
		ORG		0034H

		//;test_61f02x_PA_INT.C: 136: }
		//;test_61f02x_PA_INT.C: 137: PA2_Level_Change_INITIAL();
		LCALL 	59H 			//0034 	3059

		//;test_61f02x_PA_INT.C: 138: GIE = 1;
		BSR 	INTCON,7 		//0035 	1B8B
		SLEEP	 			//0036 	0002
		LJUMP 	24H 			//0037 	3824

		//;test_61f02x_PA_INT.C: 39: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0038 	158B
		BTSS 	INTCON,0 		//0039 	1C0B
		LJUMP 	42H 			//003A 	3842

		//;test_61f02x_PA_INT.C: 40: {
		//;test_61f02x_PA_INT.C: 41: ReadAPin = PORTA;
		BCR 	STATUS,5 		//003B 	1283
		ORG		003CH
		BCR 	STATUS,6 		//003C 	1303
		LDR 	5H,0 			//003D 	0805

		//;test_61f02x_PA_INT.C: 42: PAIF = 0;
		BCR 	INTCON,0 		//003E 	100B

		//;test_61f02x_PA_INT.C: 43: PAIE = 0;
		BCR 	INTCON,3 		//003F 	118B

		//;test_61f02x_PA_INT.C: 44: IOCA2 =0;
		BSR 	STATUS,5 		//0040 	1A83
		BCR 	16H,2 			//0041 	1116
		LDR 	71H,0 			//0042 	0871
		STR 	PCLATH 			//0043 	018A
		ORG		0044H
		SWAPR 	70H,0 			//0044 	0770
		STR 	STATUS 			//0045 	0183
		SWAPR 	7EH,1 			//0046 	07FE
		SWAPR 	7EH,0 			//0047 	077E
		RETI		 			//0048 	0009
		STR 	74H 			//0049 	01F4

		//;test_61f02x_PA_INT.C: 94: unsigned char a,b;
		//;test_61f02x_PA_INT.C: 95: for(a=0;a<Time;a++)
		CLRR 	75H 			//004A 	0175
		LDR 	74H,0 			//004B 	0874
		ORG		004CH
		SUBWR 	75H,0 			//004C 	0C75
		BTSC 	STATUS,0 		//004D 	1403
		RET		 					//004E 	0004

		//;test_61f02x_PA_INT.C: 96: {
		//;test_61f02x_PA_INT.C: 97: for(b=0;b<5;b++)
		CLRR 	76H 			//004F 	0176

		//;test_61f02x_PA_INT.C: 98: {
		//;test_61f02x_PA_INT.C: 99: DelayUs(197);
		LDWI 	C5H 			//0050 	2AC5
		LCALL 	64H 			//0051 	3064
		LDWI 	5H 			//0052 	2A05
		INCR	76H,1 			//0053 	09F6
		ORG		0054H
		SUBWR 	76H,0 			//0054 	0C76
		BTSS 	STATUS,0 		//0055 	1C03
		LJUMP 	50H 			//0056 	3850
		INCR	75H,1 			//0057 	09F5
		LJUMP 	4BH 			//0058 	384B

		//;test_61f02x_PA_INT.C: 111: ANSEL = 0B00000000;
		BSR 	STATUS,5 		//0059 	1A83
		BCR 	STATUS,6 		//005A 	1303
		CLRR 	11H 			//005B 	0111
		ORG		005CH

		//;test_61f02x_PA_INT.C: 112: TRISA2 =1;
		BSR 	5H,2 			//005C 	1905

		//;test_61f02x_PA_INT.C: 113: ReadAPin = PORTA;
		BCR 	STATUS,5 		//005D 	1283
		LDR 	5H,0 			//005E 	0805

		//;test_61f02x_PA_INT.C: 114: PAIF =0;
		BCR 	INTCON,0 		//005F 	100B

		//;test_61f02x_PA_INT.C: 115: IOCA2 =1;
		BSR 	STATUS,5 		//0060 	1A83
		BSR 	16H,2 			//0061 	1916

		//;test_61f02x_PA_INT.C: 116: PAIE =1;
		BSR 	INTCON,3 		//0062 	198B
		RET		 					//0063 	0004
		ORG		0064H
		STR 	72H 			//0064 	01F2

		//;test_61f02x_PA_INT.C: 80: unsigned char a;
		//;test_61f02x_PA_INT.C: 81: for(a=0;a<Time;a++)
		CLRR 	73H 			//0065 	0173
		LDR 	72H,0 			//0066 	0872
		SUBWR 	73H,0 			//0067 	0C73
		BTSC 	STATUS,0 		//0068 	1403
		RET		 					//0069 	0004

		//;test_61f02x_PA_INT.C: 82: {
		//;test_61f02x_PA_INT.C: 83: __nop();
		NOP		 					//006A 	0000
		INCR	73H,1 			//006B 	09F3
		ORG		006CH
		LJUMP 	66H 			//006C 	3866
			END
