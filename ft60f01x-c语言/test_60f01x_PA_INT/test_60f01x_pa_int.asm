//Deviec:FT60F01X
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
		LJUMP 	30H 			//0009 	3830
		LJUMP 	0BH 			//000A 	380B
		CLRR 	STATUS 			//000B 	0103
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D

		//;test_60f01x_pa_int.C: 136: POWER_INITIAL();
		LCALL 	40H 			//000D 	3040

		//;test_60f01x_pa_int.C: 138: {
		//;test_60f01x_pa_int.C: 139: for(FCount=0;FCount<100;FCount++)
		CLRR 	77H 			//000E 	0177

		//;test_60f01x_pa_int.C: 140: {
		//;test_60f01x_pa_int.C: 141: PA4 = 1;
		BCR 	STATUS,5 		//000F 	1283
		BSR 	5H,4 			//0010 	1A05

		//;test_60f01x_pa_int.C: 142: DelayMs(10);
		LDWI 	AH 			//0011 	2A0A
		LCALL 	20H 			//0012 	3020

		//;test_60f01x_pa_int.C: 143: PA4 = 0;
		BCR 	STATUS,5 		//0013 	1283
		ORG		0014H
		BCR 	5H,4 			//0014 	1205

		//;test_60f01x_pa_int.C: 144: DelayMs(10);
		LDWI 	AH 			//0015 	2A0A
		LCALL 	20H 			//0016 	3020
		LDWI 	64H 			//0017 	2A64
		INCR	77H,1 			//0018 	09F7
		SUBWR 	77H,0 			//0019 	0C77
		BTSS 	STATUS,0 		//001A 	1C03
		LJUMP 	0FH 			//001B 	380F
		ORG		001CH

		//;test_60f01x_pa_int.C: 145: }
		//;test_60f01x_pa_int.C: 146: PA2_Level_Change_INITIAL();
		LCALL 	4FH 			//001C 	304F

		//;test_60f01x_pa_int.C: 147: GIE = 1;
		BSR 	INTCON,7 		//001D 	1B8B
		SLEEP	 			//001E 	0002
		LJUMP 	0EH 			//001F 	380E
		STR 	74H 			//0020 	01F4

		//;test_60f01x_pa_int.C: 88: unsigned char a,b;
		//;test_60f01x_pa_int.C: 89: for(a=0;a<Time;a++)
		CLRR 	75H 			//0021 	0175
		LDR 	74H,0 			//0022 	0874
		SUBWR 	75H,0 			//0023 	0C75
		ORG		0024H
		BTSC 	STATUS,0 		//0024 	1403
		RET		 					//0025 	0004

		//;test_60f01x_pa_int.C: 90: {
		//;test_60f01x_pa_int.C: 91: for(b=0;b<5;b++)
		CLRR 	76H 			//0026 	0176

		//;test_60f01x_pa_int.C: 92: {
		//;test_60f01x_pa_int.C: 93: DelayUs(98);
		LDWI 	62H 			//0027 	2A62
		LCALL 	58H 			//0028 	3058
		LDWI 	5H 			//0029 	2A05
		INCR	76H,1 			//002A 	09F6
		SUBWR 	76H,0 			//002B 	0C76
		ORG		002CH
		BTSS 	STATUS,0 		//002C 	1C03
		LJUMP 	27H 			//002D 	3827
		INCR	75H,1 			//002E 	09F5
		LJUMP 	22H 			//002F 	3822

		//;test_60f01x_pa_int.C: 36: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0030 	158B
		BTSS 	INTCON,0 		//0031 	1C0B
		LJUMP 	39H 			//0032 	3839

		//;test_60f01x_pa_int.C: 37: {
		//;test_60f01x_pa_int.C: 38: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0033 	1283
		ORG		0034H
		LDR 	5H,0 			//0034 	0805

		//;test_60f01x_pa_int.C: 39: PAIF = 0;
		BCR 	INTCON,0 		//0035 	100B

		//;test_60f01x_pa_int.C: 40: PAIE = 0;
		BCR 	INTCON,3 		//0036 	118B

		//;test_60f01x_pa_int.C: 41: IOCA2 =0;
		BSR 	STATUS,5 		//0037 	1A83
		BCR 	16H,2 			//0038 	1116
		LDR 	71H,0 			//0039 	0871
		STR 	PCLATH 			//003A 	018A
		SWAPR 	70H,0 			//003B 	0770
		ORG		003CH
		STR 	STATUS 			//003C 	0183
		SWAPR 	7EH,1 			//003D 	07FE
		SWAPR 	7EH,0 			//003E 	077E
		RETI		 			//003F 	0009

		//;test_60f01x_pa_int.C: 52: OSCCON = 0B01110001;
		LDWI 	71H 			//0040 	2A71
		BSR 	STATUS,5 		//0041 	1A83
		STR 	FH 			//0042 	018F

		//;test_60f01x_pa_int.C: 53: INTCON = 0;
		CLRR 	INTCON 			//0043 	010B
		ORG		0044H

		//;test_60f01x_pa_int.C: 55: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0044 	1283
		CLRR 	5H 			//0045 	0105

		//;test_60f01x_pa_int.C: 56: TRISA = 0B11101111;
		LDWI 	EFH 			//0046 	2AEF
		BSR 	STATUS,5 		//0047 	1A83
		STR 	5H 			//0048 	0185

		//;test_60f01x_pa_int.C: 58: WPUA = 0B00000000;
		CLRR 	15H 			//0049 	0115

		//;test_60f01x_pa_int.C: 60: OPTION = 0B00001000;
		LDWI 	8H 			//004A 	2A08
		STR 	1H 			//004B 	0181
		ORG		004CH

		//;test_60f01x_pa_int.C: 61: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//004C 	1283
		CLRR 	1BH 			//004D 	011B
		RET		 					//004E 	0004

		//;test_60f01x_pa_int.C: 122: TRISA2 =1;
		BSR 	STATUS,5 		//004F 	1A83
		BSR 	5H,2 			//0050 	1905

		//;test_60f01x_pa_int.C: 123: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0051 	1283
		LDR 	5H,0 			//0052 	0805

		//;test_60f01x_pa_int.C: 124: PAIF =0;
		BCR 	INTCON,0 		//0053 	100B
		ORG		0054H

		//;test_60f01x_pa_int.C: 125: IOCA2 =1;
		BSR 	STATUS,5 		//0054 	1A83
		BSR 	16H,2 			//0055 	1916

		//;test_60f01x_pa_int.C: 126: PAIE =1;
		BSR 	INTCON,3 		//0056 	198B
		RET		 					//0057 	0004
		STR 	72H 			//0058 	01F2

		//;test_60f01x_pa_int.C: 74: unsigned char a;
		//;test_60f01x_pa_int.C: 75: for(a=0;a<Time;a++)
		CLRR 	73H 			//0059 	0173
		LDR 	72H,0 			//005A 	0872
		SUBWR 	73H,0 			//005B 	0C73
		ORG		005CH
		BTSC 	STATUS,0 		//005C 	1403
		RET		 					//005D 	0004

		//;test_60f01x_pa_int.C: 76: {
		//;test_60f01x_pa_int.C: 77: __nop();
		NOP		 					//005E 	0000
		INCR	73H,1 			//005F 	09F3
		LJUMP 	5AH 			//0060 	385A
			END
