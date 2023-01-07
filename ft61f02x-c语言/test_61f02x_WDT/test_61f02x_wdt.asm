//Deviec:FT61F02X
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
		LJUMP 	7FEH 			//0000 	3FFE
		ORG		07B6H

		//;test_61f02x_WDT.C: 94: PSA=1;
		BSR 	STATUS,5 		//07B6 	1A83
		BSR 	1H,3 			//07B7 	1981

		//;test_61f02x_WDT.C: 95: WDTCON = 0B00001011;
		LDWI 	BH 			//07B8 	2A0B
		BCR 	STATUS,5 		//07B9 	1283
		STR 	18H 			//07BA 	0198
		RET		 					//07BB 	0004
		STR 	70H 			//07BC 	01F0

		//;test_61f02x_WDT.C: 62: unsigned char a;
		//;test_61f02x_WDT.C: 63: for(a=0;a<Time;a++)
		CLRR 	71H 			//07BD 	0171
		ORG		07BEH
		LDR 	70H,0 			//07BE 	0870
		SUBWR 	71H,0 			//07BF 	0C71
		BTSC 	STATUS,0 		//07C0 	1403
		RET		 					//07C1 	0004

		//;test_61f02x_WDT.C: 64: {
		//;test_61f02x_WDT.C: 65: __nop();
		NOP		 					//07C2 	0000
		INCR	71H,1 			//07C3 	09F1
		LJUMP 	7BEH 			//07C4 	3FBE
		STR 	72H 			//07C5 	01F2
		ORG		07C6H

		//;test_61f02x_WDT.C: 76: unsigned char a,b;
		//;test_61f02x_WDT.C: 77: for(a=0;a<Time;a++)
		CLRR 	73H 			//07C6 	0173
		LDR 	72H,0 			//07C7 	0872
		SUBWR 	73H,0 			//07C8 	0C73
		BTSC 	STATUS,0 		//07C9 	1403
		RET		 					//07CA 	0004

		//;test_61f02x_WDT.C: 78: {
		//;test_61f02x_WDT.C: 79: for(b=0;b<5;b++)
		CLRR 	74H 			//07CB 	0174

		//;test_61f02x_WDT.C: 80: {
		//;test_61f02x_WDT.C: 81: DelayUs(197);
		LDWI 	C5H 			//07CC 	2AC5
		LCALL 	7BCH 			//07CD 	37BC
		ORG		07CEH
		LDWI 	5H 			//07CE 	2A05
		INCR	74H,1 			//07CF 	09F4
		SUBWR 	74H,0 			//07D0 	0C74
		BTSS 	STATUS,0 		//07D1 	1C03
		LJUMP 	7CCH 			//07D2 	3FCC
		INCR	73H,1 			//07D3 	09F3
		LJUMP 	7C7H 			//07D4 	3FC7

		//;test_61f02x_WDT.C: 107: POWER_INITIAL();
		LCALL 	7E9H 			//07D5 	37E9
		ORG		07D6H

		//;test_61f02x_WDT.C: 108: WDT_INITIAL();
		LCALL 	7B6H 			//07D6 	37B6

		//;test_61f02x_WDT.C: 109: PA3 = 1;
		BSR 	5H,3 			//07D7 	1985

		//;test_61f02x_WDT.C: 110: DelayMs(3);
		LDWI 	3H 			//07D8 	2A03
		LCALL 	7C5H 			//07D9 	37C5

		//;test_61f02x_WDT.C: 111: PA3 = 0;
		BCR 	STATUS,5 		//07DA 	1283
		BCR 	STATUS,6 		//07DB 	1303
		BCR 	5H,3 			//07DC 	1185

		//;test_61f02x_WDT.C: 112: DelayMs(3);
		LDWI 	3H 			//07DD 	2A03
		ORG		07DEH
		LCALL 	7C5H 			//07DE 	37C5

		//;test_61f02x_WDT.C: 114: {
		//;test_61f02x_WDT.C: 116: PA3 = 1;
		BCR 	STATUS,5 		//07DF 	1283
		BCR 	STATUS,6 		//07E0 	1303
		BSR 	5H,3 			//07E1 	1985

		//;test_61f02x_WDT.C: 117: DelayMs(1);
		LDWI 	1H 			//07E2 	2A01
		LCALL 	7C5H 			//07E3 	37C5

		//;test_61f02x_WDT.C: 118: PA3 = 0;
		BCR 	STATUS,5 		//07E4 	1283
		BCR 	STATUS,6 		//07E5 	1303
		ORG		07E6H
		BCR 	5H,3 			//07E6 	1185

		//;test_61f02x_WDT.C: 119: DelayMs(1);
		LDWI 	1H 			//07E7 	2A01
		LJUMP 	7DEH 			//07E8 	3FDE

		//;test_61f02x_WDT.C: 36: OSCCON = 0B01110001;
		LDWI 	71H 			//07E9 	2A71
		BSR 	STATUS,5 		//07EA 	1A83
		STR 	FH 			//07EB 	018F

		//;test_61f02x_WDT.C: 37: INTCON = 0;
		CLRR 	INTCON 			//07EC 	010B

		//;test_61f02x_WDT.C: 39: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07ED 	1283
		ORG		07EEH
		CLRR 	5H 			//07EE 	0105

		//;test_61f02x_WDT.C: 40: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07EF 	1A83
		CLRR 	5H 			//07F0 	0105

		//;test_61f02x_WDT.C: 42: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07F1 	1283
		CLRR 	7H 			//07F2 	0107

		//;test_61f02x_WDT.C: 43: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07F3 	1A83
		CLRR 	7H 			//07F4 	0107

		//;test_61f02x_WDT.C: 44: WPUA = 0B00000000;
		CLRR 	15H 			//07F5 	0115
		ORG		07F6H

		//;test_61f02x_WDT.C: 45: WPUC = 0B00000000;
		CLRR 	8H 			//07F6 	0108

		//;test_61f02x_WDT.C: 47: OPTION = 0B00001000;
		LDWI 	8H 			//07F7 	2A08
		STR 	1H 			//07F8 	0181

		//;test_61f02x_WDT.C: 48: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07F9 	1283
		CLRR 	1BH 			//07FA 	011B

		//;test_61f02x_WDT.C: 52: CMCON0 = 0B00000111;
		LDWI 	7H 			//07FB 	2A07
		STR 	19H 			//07FC 	0199
		RET		 					//07FD 	0004
		ORG		07FEH
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7D5H 			//07FF 	3FD5
			END
