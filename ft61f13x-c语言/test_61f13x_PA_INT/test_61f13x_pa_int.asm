//Deviec:FT61F13X
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
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0BH 			//0001 	380B
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		BCR 	PCLATH,3 		//0009 	118A
		LJUMP 	59H 			//000A 	3859
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	10H 			//000F 	3810

		//;test_61f13x_PA_INT.C: 127: POWER_INITIAL();
		BCR 	PCLATH,3 		//0010 	118A
		LCALL 	47H 			//0011 	3047
		BCR 	PCLATH,3 		//0012 	118A

		//;test_61f13x_PA_INT.C: 130: {
		//;test_61f13x_PA_INT.C: 131: for(FCount=0;FCount<100;FCount++)
		CLRR 	77H 			//0013 	0177
		ORG		0014H

		//;test_61f13x_PA_INT.C: 132: {
		//;test_61f13x_PA_INT.C: 133: PA4 = 1;
		BCR 	STATUS,5 		//0014 	1283
		BCR 	STATUS,6 		//0015 	1303
		BSR 	5H,4 			//0016 	1A05

		//;test_61f13x_PA_INT.C: 134: DelayMs(10);
		LDWI 	AH 			//0017 	2A0A
		BCR 	PCLATH,3 		//0018 	118A
		LCALL 	2DH 			//0019 	302D
		BCR 	PCLATH,3 		//001A 	118A

		//;test_61f13x_PA_INT.C: 135: PA4 = 0;
		BCR 	STATUS,5 		//001B 	1283
		ORG		001CH
		BCR 	STATUS,6 		//001C 	1303
		BCR 	5H,4 			//001D 	1205

		//;test_61f13x_PA_INT.C: 136: DelayMs(10);
		LDWI 	AH 			//001E 	2A0A
		BCR 	PCLATH,3 		//001F 	118A
		LCALL 	2DH 			//0020 	302D
		BCR 	PCLATH,3 		//0021 	118A
		LDWI 	64H 			//0022 	2A64
		INCR	77H,1 			//0023 	09F7
		ORG		0024H
		SUBWR 	77H,0 			//0024 	0C77
		BTSS 	STATUS,0 		//0025 	1C03
		LJUMP 	14H 			//0026 	3814

		//;test_61f13x_PA_INT.C: 137: }
		//;test_61f13x_PA_INT.C: 138: PA2_INITIAL();
		BCR 	PCLATH,3 		//0027 	118A
		LCALL 	6AH 			//0028 	306A
		BCR 	PCLATH,3 		//0029 	118A

		//;test_61f13x_PA_INT.C: 139: GIE = 1;
		BSR 	INTCON,7 		//002A 	1B8B
		SLEEP	 			//002B 	0002
		ORG		002CH
		LJUMP 	13H 			//002C 	3813
		STR 	74H 			//002D 	01F4

		//;test_61f13x_PA_INT.C: 95: unsigned char a,b;
		//;test_61f13x_PA_INT.C: 96: for(a=0;a<Time;a++)
		CLRR 	75H 			//002E 	0175
		LDR 	74H,0 			//002F 	0874
		SUBWR 	75H,0 			//0030 	0C75
		BTSC 	STATUS,0 		//0031 	1403
		RET		 					//0032 	0004

		//;test_61f13x_PA_INT.C: 97: {
		//;test_61f13x_PA_INT.C: 98: for(b=0;b<5;b++)
		CLRR 	76H 			//0033 	0176
		ORG		0034H

		//;test_61f13x_PA_INT.C: 99: {
		//;test_61f13x_PA_INT.C: 100: DelayUs(197);
		LDWI 	C5H 			//0034 	2AC5
		LCALL 	3EH 			//0035 	303E
		BCR 	PCLATH,3 		//0036 	118A
		LDWI 	5H 			//0037 	2A05
		INCR	76H,1 			//0038 	09F6
		SUBWR 	76H,0 			//0039 	0C76
		BTSS 	STATUS,0 		//003A 	1C03
		LJUMP 	34H 			//003B 	3834
		ORG		003CH
		INCR	75H,1 			//003C 	09F5
		LJUMP 	2FH 			//003D 	382F
		STR 	72H 			//003E 	01F2

		//;test_61f13x_PA_INT.C: 81: unsigned char a;
		//;test_61f13x_PA_INT.C: 82: for(a=0;a<Time;a++)
		CLRR 	73H 			//003F 	0173
		LDR 	72H,0 			//0040 	0872
		SUBWR 	73H,0 			//0041 	0C73
		BTSC 	STATUS,0 		//0042 	1403
		RET		 					//0043 	0004
		ORG		0044H

		//;test_61f13x_PA_INT.C: 83: {
		//;test_61f13x_PA_INT.C: 84: __nop();
		NOP		 					//0044 	0000
		INCR	73H,1 			//0045 	09F3
		LJUMP 	40H 			//0046 	3840

		//;test_61f13x_PA_INT.C: 59: OSCCON = 0B01110001;
		LDWI 	71H 			//0047 	2A71
		BSR 	STATUS,5 		//0048 	1A83
		STR 	FH 			//0049 	018F

		//;test_61f13x_PA_INT.C: 60: INTCON = 0;
		CLRR 	INTCON 			//004A 	010B

		//;test_61f13x_PA_INT.C: 61: PORTA = 0B00000000;
		BCR 	STATUS,5 		//004B 	1283
		ORG		004CH
		CLRR 	5H 			//004C 	0105

		//;test_61f13x_PA_INT.C: 62: TRISA = 0B00000100;
		LDWI 	4H 			//004D 	2A04
		BSR 	STATUS,5 		//004E 	1A83
		STR 	5H 			//004F 	0185

		//;test_61f13x_PA_INT.C: 64: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0050 	1283
		CLRR 	7H 			//0051 	0107

		//;test_61f13x_PA_INT.C: 65: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0052 	1A83
		CLRR 	7H 			//0053 	0107
		ORG		0054H

		//;test_61f13x_PA_INT.C: 67: WPUA = 0B00000100;
		STR 	15H 			//0054 	0195

		//;test_61f13x_PA_INT.C: 69: WPUC = 0B00000000;
		CLRR 	13H 			//0055 	0113

		//;test_61f13x_PA_INT.C: 71: OPTION = 0B00001000;
		LDWI 	8H 			//0056 	2A08
		STR 	1H 			//0057 	0181
		RET		 					//0058 	0004

		//;test_61f13x_PA_INT.C: 42: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0059 	158B
		BTSS 	INTCON,0 		//005A 	1C0B
		LJUMP 	63H 			//005B 	3863
		ORG		005CH

		//;test_61f13x_PA_INT.C: 43: {
		//;test_61f13x_PA_INT.C: 44: ReadAPin = PORTA;
		BCR 	STATUS,5 		//005C 	1283
		BCR 	STATUS,6 		//005D 	1303
		LDR 	5H,0 			//005E 	0805

		//;test_61f13x_PA_INT.C: 45: PAIF = 0;
		BCR 	INTCON,0 		//005F 	100B

		//;test_61f13x_PA_INT.C: 46: PAIE = 0;
		BCR 	INTCON,3 		//0060 	118B

		//;test_61f13x_PA_INT.C: 47: IOCA2 =0;
		BSR 	STATUS,5 		//0061 	1A83
		BCR 	16H,2 			//0062 	1116
		LDR 	71H,0 			//0063 	0871
		ORG		0064H
		STR 	PCLATH 			//0064 	018A
		SWAPR 	70H,0 			//0065 	0770
		STR 	STATUS 			//0066 	0183
		SWAPR 	7EH,1 			//0067 	07FE
		SWAPR 	7EH,0 			//0068 	077E
		RETI		 			//0069 	0009

		//;test_61f13x_PA_INT.C: 113: TRISA2 =1;
		BSR 	STATUS,5 		//006A 	1A83
		BCR 	STATUS,6 		//006B 	1303
		ORG		006CH
		BSR 	5H,2 			//006C 	1905

		//;test_61f13x_PA_INT.C: 114: ReadAPin = PORTA;
		BCR 	STATUS,5 		//006D 	1283
		LDR 	5H,0 			//006E 	0805

		//;test_61f13x_PA_INT.C: 115: PAIF =0;
		BCR 	INTCON,0 		//006F 	100B

		//;test_61f13x_PA_INT.C: 116: IOCA2 =1;
		BSR 	STATUS,5 		//0070 	1A83
		BSR 	16H,2 			//0071 	1916

		//;test_61f13x_PA_INT.C: 117: PAIE =1;
		BSR 	INTCON,3 		//0072 	198B
		RET		 					//0073 	0004
			END
