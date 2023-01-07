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
		LJUMP 	3FH 			//0009 	383F
		LJUMP 	0BH 			//000A 	380B
		CLRR 	STATUS 			//000B 	0103
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D

		//;test_60f01x_INT.C: 112: POWER_INITIAL();
		LCALL 	30H 			//000D 	3030

		//;test_60f01x_INT.C: 114: {
		//;test_60f01x_INT.C: 115: for(FCount=0;FCount<100;FCount++)
		CLRR 	77H 			//000E 	0177

		//;test_60f01x_INT.C: 116: {
		//;test_60f01x_INT.C: 117: PA4 = 1;
		BCR 	STATUS,5 		//000F 	1283
		BSR 	5H,4 			//0010 	1A05

		//;test_60f01x_INT.C: 118: DelayMs(10);
		LDWI 	AH 			//0011 	2A0A
		LCALL 	20H 			//0012 	3020

		//;test_60f01x_INT.C: 119: PA4 = 0;
		BCR 	STATUS,5 		//0013 	1283
		ORG		0014H
		BCR 	5H,4 			//0014 	1205

		//;test_60f01x_INT.C: 120: DelayMs(10);
		LDWI 	AH 			//0015 	2A0A
		LCALL 	20H 			//0016 	3020
		LDWI 	64H 			//0017 	2A64
		INCR	77H,1 			//0018 	09F7
		SUBWR 	77H,0 			//0019 	0C77
		BTSS 	STATUS,0 		//001A 	1C03
		LJUMP 	0FH 			//001B 	380F
		ORG		001CH

		//;test_60f01x_INT.C: 121: }
		//;test_60f01x_INT.C: 122: INT_INITIAL();
		LCALL 	54H 			//001C 	3054

		//;test_60f01x_INT.C: 123: GIE = 1;
		BSR 	INTCON,7 		//001D 	1B8B
		SLEEP	 			//001E 	0002
		LJUMP 	0EH 			//001F 	380E
		STR 	74H 			//0020 	01F4

		//;test_60f01x_INT.C: 82: unsigned char a,b;
		//;test_60f01x_INT.C: 83: for(a=0;a<Time;a++)
		CLRR 	75H 			//0021 	0175
		LDR 	74H,0 			//0022 	0874
		SUBWR 	75H,0 			//0023 	0C75
		ORG		0024H
		BTSC 	STATUS,0 		//0024 	1403
		RET		 					//0025 	0004

		//;test_60f01x_INT.C: 84: {
		//;test_60f01x_INT.C: 85: for(b=0;b<5;b++)
		CLRR 	76H 			//0026 	0176

		//;test_60f01x_INT.C: 86: {
		//;test_60f01x_INT.C: 87: DelayUs(98);
		LDWI 	62H 			//0027 	2A62
		LCALL 	4BH 			//0028 	304B
		LDWI 	5H 			//0029 	2A05
		INCR	76H,1 			//002A 	09F6
		SUBWR 	76H,0 			//002B 	0C76
		ORG		002CH
		BTSS 	STATUS,0 		//002C 	1C03
		LJUMP 	27H 			//002D 	3827
		INCR	75H,1 			//002E 	09F5
		LJUMP 	22H 			//002F 	3822

		//;test_60f01x_INT.C: 47: OSCCON = 0B01110000;
		LDWI 	70H 			//0030 	2A70
		BSR 	STATUS,5 		//0031 	1A83
		STR 	FH 			//0032 	018F

		//;test_60f01x_INT.C: 48: INTCON = 0;
		CLRR 	INTCON 			//0033 	010B
		ORG		0034H

		//;test_60f01x_INT.C: 49: OPTION = 0B00001000;
		LDWI 	8H 			//0034 	2A08
		STR 	1H 			//0035 	0181

		//;test_60f01x_INT.C: 51: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0036 	1283
		CLRR 	5H 			//0037 	0105

		//;test_60f01x_INT.C: 52: TRISA = 0B00000100;
		LDWI 	4H 			//0038 	2A04
		BSR 	STATUS,5 		//0039 	1A83
		STR 	5H 			//003A 	0185

		//;test_60f01x_INT.C: 53: WPUA = 0B00000100;
		STR 	15H 			//003B 	0195
		ORG		003CH

		//;test_60f01x_INT.C: 55: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//003C 	1283
		CLRR 	1BH 			//003D 	011B
		RET		 					//003E 	0004

		//;test_60f01x_INT.C: 33: if(INTE && INTF)
		BTSC 	INTCON,4 		//003F 	160B
		BTSS 	INTCON,1 		//0040 	1C8B
		LJUMP 	44H 			//0041 	3844

		//;test_60f01x_INT.C: 34: {
		//;test_60f01x_INT.C: 35: INTF = 0;
		BCR 	INTCON,1 		//0042 	108B

		//;test_60f01x_INT.C: 36: INTE = 0;
		BCR 	INTCON,4 		//0043 	120B
		ORG		0044H
		LDR 	71H,0 			//0044 	0871
		STR 	PCLATH 			//0045 	018A
		SWAPR 	70H,0 			//0046 	0770
		STR 	STATUS 			//0047 	0183
		SWAPR 	7EH,1 			//0048 	07FE
		SWAPR 	7EH,0 			//0049 	077E
		RETI		 			//004A 	0009
		STR 	72H 			//004B 	01F2
		ORG		004CH

		//;test_60f01x_INT.C: 68: unsigned char a;
		//;test_60f01x_INT.C: 69: for(a=0;a<Time;a++)
		CLRR 	73H 			//004C 	0173
		LDR 	72H,0 			//004D 	0872
		SUBWR 	73H,0 			//004E 	0C73
		BTSC 	STATUS,0 		//004F 	1403
		RET		 					//0050 	0004

		//;test_60f01x_INT.C: 70: {
		//;test_60f01x_INT.C: 71: __nop();
		NOP		 					//0051 	0000
		INCR	73H,1 			//0052 	09F3
		LJUMP 	4DH 			//0053 	384D
		ORG		0054H

		//;test_60f01x_INT.C: 99: TRISA2 = 1;
		BSR 	STATUS,5 		//0054 	1A83
		BSR 	5H,2 			//0055 	1905

		//;test_60f01x_INT.C: 100: INTEDG = 1;
		BSR 	1H,6 			//0056 	1B01

		//;test_60f01x_INT.C: 101: INTF =0;
		BCR 	INTCON,1 		//0057 	108B

		//;test_60f01x_INT.C: 102: INTE =1;
		BSR 	INTCON,4 		//0058 	1A0B
		RET		 					//0059 	0004
			END
