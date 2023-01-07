//Deviec:FT60F01X
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
		LJUMP 	3FEH 			//0000 	3BFE
		ORG		03BFH
		CLRWDT	 			//03BF 	0001

		//;test_60f01x_WDT.C: 103: PSA=1;
		BSR 	STATUS,5 		//03C0 	1A83
		BSR 	1H,3 			//03C1 	1981

		//;test_60f01x_WDT.C: 104: WDTCON = 0B00001011;
		LDWI 	BH 			//03C2 	2A0B
		BCR 	STATUS,5 		//03C3 	1283
		STR 	18H 			//03C4 	0198
		RET		 					//03C5 	0004
		STR 	70H 			//03C6 	01F0
		ORG		03C7H

		//;test_60f01x_WDT.C: 54: unsigned char a;
		//;test_60f01x_WDT.C: 55: for(a=0;a<Time;a++)
		CLRR 	71H 			//03C7 	0171
		LDR 	70H,0 			//03C8 	0870
		SUBWR 	71H,0 			//03C9 	0C71
		BTSC 	STATUS,0 		//03CA 	1403
		RET		 					//03CB 	0004

		//;test_60f01x_WDT.C: 56: {
		//;test_60f01x_WDT.C: 57: __nop();
		NOP		 					//03CC 	0000
		INCR	71H,1 			//03CD 	09F1
		LJUMP 	3C8H 			//03CE 	3BC8
		ORG		03CFH

		//;test_60f01x_WDT.C: 32: OSCCON = 0B01110000;
		LDWI 	70H 			//03CF 	2A70
		BSR 	STATUS,5 		//03D0 	1A83
		STR 	FH 			//03D1 	018F

		//;test_60f01x_WDT.C: 33: INTCON = 0;
		CLRR 	INTCON 			//03D2 	010B

		//;test_60f01x_WDT.C: 35: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03D3 	1283
		CLRR 	5H 			//03D4 	0105

		//;test_60f01x_WDT.C: 36: TRISA = 0B00000000;
		BSR 	STATUS,5 		//03D5 	1A83
		CLRR 	5H 			//03D6 	0105
		ORG		03D7H

		//;test_60f01x_WDT.C: 38: WPUA = 0B00000000;
		CLRR 	15H 			//03D7 	0115

		//;test_60f01x_WDT.C: 40: OPTION = 0B00001000;
		LDWI 	8H 			//03D8 	2A08
		STR 	1H 			//03D9 	0181

		//;test_60f01x_WDT.C: 41: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03DA 	1283
		CLRR 	1BH 			//03DB 	011B
		RET		 					//03DC 	0004
		STR 	72H 			//03DD 	01F2

		//;test_60f01x_WDT.C: 68: unsigned char a,b;
		//;test_60f01x_WDT.C: 69: for(a=0;a<Time;a++)
		CLRR 	73H 			//03DE 	0173
		ORG		03DFH
		LDR 	72H,0 			//03DF 	0872
		SUBWR 	73H,0 			//03E0 	0C73
		BTSC 	STATUS,0 		//03E1 	1403
		RET		 					//03E2 	0004

		//;test_60f01x_WDT.C: 70: {
		//;test_60f01x_WDT.C: 71: for(b=0;b<5;b++)
		CLRR 	74H 			//03E3 	0174

		//;test_60f01x_WDT.C: 72: {
		//;test_60f01x_WDT.C: 73: DelayUs(98);
		LDWI 	62H 			//03E4 	2A62
		LCALL 	3C6H 			//03E5 	33C6
		LDWI 	5H 			//03E6 	2A05
		ORG		03E7H
		INCR	74H,1 			//03E7 	09F4
		SUBWR 	74H,0 			//03E8 	0C74
		BTSS 	STATUS,0 		//03E9 	1C03
		LJUMP 	3E4H 			//03EA 	3BE4
		INCR	73H,1 			//03EB 	09F3
		LJUMP 	3DFH 			//03EC 	3BDF

		//;test_60f01x_WDT.C: 114: POWER_INITIAL();
		LCALL 	3CFH 			//03ED 	33CF

		//;test_60f01x_WDT.C: 115: WDT_INITIAL();
		LCALL 	3BFH 			//03EE 	33BF
		ORG		03EFH

		//;test_60f01x_WDT.C: 116: PA4 = 1;
		BSR 	5H,4 			//03EF 	1A05

		//;test_60f01x_WDT.C: 117: DelayMs(3);
		LDWI 	3H 			//03F0 	2A03
		LCALL 	3DDH 			//03F1 	33DD

		//;test_60f01x_WDT.C: 118: PA4 = 0;
		BCR 	STATUS,5 		//03F2 	1283
		BCR 	5H,4 			//03F3 	1205

		//;test_60f01x_WDT.C: 119: DelayMs(3);
		LDWI 	3H 			//03F4 	2A03
		LCALL 	3DDH 			//03F5 	33DD

		//;test_60f01x_WDT.C: 121: {
		//;test_60f01x_WDT.C: 123: PA4 = 1;
		BCR 	STATUS,5 		//03F6 	1283
		ORG		03F7H
		BSR 	5H,4 			//03F7 	1A05

		//;test_60f01x_WDT.C: 124: DelayMs(1);
		LDWI 	1H 			//03F8 	2A01
		LCALL 	3DDH 			//03F9 	33DD

		//;test_60f01x_WDT.C: 125: PA4 = 0;
		BCR 	STATUS,5 		//03FA 	1283
		BCR 	5H,4 			//03FB 	1205

		//;test_60f01x_WDT.C: 126: DelayMs(1);
		LDWI 	1H 			//03FC 	2A01
		LJUMP 	3F5H 			//03FD 	3BF5
		CLRR 	STATUS 			//03FE 	0103
		ORG		03FFH
		LJUMP 	3EDH 			//03FF 	3BED
			END
