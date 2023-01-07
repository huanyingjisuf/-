//Deviec:FT61F13X
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
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FDH 			//0001 	3FFD
		ORG		07ABH
		CLRWDT	 			//07AB 	0001

		//;test_61f13x_WDT.C: 98: OPTION = 0B00001000;
		LDWI 	8H 			//07AC 	2A08
		BSR 	STATUS,5 		//07AD 	1A83
		BCR 	STATUS,6 		//07AE 	1303
		STR 	1H 			//07AF 	0181

		//;test_61f13x_WDT.C: 99: WDTCON = 0B00001011;
		LDWI 	BH 			//07B0 	2A0B
		BCR 	STATUS,5 		//07B1 	1283
		STR 	18H 			//07B2 	0198
		ORG		07B3H
		RET		 					//07B3 	0004

		//;test_61f13x_WDT.C: 44: OSCCON = 0B01110001;
		LDWI 	71H 			//07B4 	2A71
		BSR 	STATUS,5 		//07B5 	1A83
		STR 	FH 			//07B6 	018F

		//;test_61f13x_WDT.C: 45: OPTION = 0B00001000;
		LDWI 	8H 			//07B7 	2A08
		STR 	1H 			//07B8 	0181

		//;test_61f13x_WDT.C: 46: INTCON = 0;
		CLRR 	INTCON 			//07B9 	010B

		//;test_61f13x_WDT.C: 47: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07BA 	1283
		ORG		07BBH
		CLRR 	5H 			//07BB 	0105

		//;test_61f13x_WDT.C: 48: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07BC 	1A83
		CLRR 	5H 			//07BD 	0105

		//;test_61f13x_WDT.C: 50: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07BE 	1283
		CLRR 	7H 			//07BF 	0107

		//;test_61f13x_WDT.C: 51: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07C0 	1A83
		CLRR 	7H 			//07C1 	0107

		//;test_61f13x_WDT.C: 53: WPUA = 0B00000000;
		CLRR 	15H 			//07C2 	0115
		ORG		07C3H

		//;test_61f13x_WDT.C: 54: WPUC = 0B00000000;
		CLRR 	13H 			//07C3 	0113
		RET		 					//07C4 	0004
		STR 	72H 			//07C5 	01F2

		//;test_61f13x_WDT.C: 78: unsigned char a,b;
		//;test_61f13x_WDT.C: 79: for(a=0;a<Time;a++)
		CLRR 	73H 			//07C6 	0173
		LDR 	72H,0 			//07C7 	0872
		SUBWR 	73H,0 			//07C8 	0C73
		BTSC 	STATUS,0 		//07C9 	1403
		RET		 					//07CA 	0004
		ORG		07CBH

		//;test_61f13x_WDT.C: 80: {
		//;test_61f13x_WDT.C: 81: for(b=0;b<5;b++)
		CLRR 	74H 			//07CB 	0174

		//;test_61f13x_WDT.C: 82: {
		//;test_61f13x_WDT.C: 83: DelayUs(197);
		LDWI 	C5H 			//07CC 	2AC5
		LCALL 	7D6H 			//07CD 	37D6
		BCR 	PCLATH,3 		//07CE 	118A
		LDWI 	5H 			//07CF 	2A05
		INCR	74H,1 			//07D0 	09F4
		SUBWR 	74H,0 			//07D1 	0C74
		BTSS 	STATUS,0 		//07D2 	1C03
		ORG		07D3H
		LJUMP 	7CCH 			//07D3 	3FCC
		INCR	73H,1 			//07D4 	09F3
		LJUMP 	7C7H 			//07D5 	3FC7
		STR 	70H 			//07D6 	01F0

		//;test_61f13x_WDT.C: 64: unsigned char a;
		//;test_61f13x_WDT.C: 65: for(a=0;a<Time;a++)
		CLRR 	71H 			//07D7 	0171
		LDR 	70H,0 			//07D8 	0870
		SUBWR 	71H,0 			//07D9 	0C71
		BTSC 	STATUS,0 		//07DA 	1403
		ORG		07DBH
		RET		 					//07DB 	0004

		//;test_61f13x_WDT.C: 66: {
		//;test_61f13x_WDT.C: 67: __nop();
		NOP		 					//07DC 	0000
		INCR	71H,1 			//07DD 	09F1
		LJUMP 	7D8H 			//07DE 	3FD8

		//;test_61f13x_WDT.C: 109: POWER_INITIAL();
		BCR 	PCLATH,3 		//07DF 	118A
		LCALL 	7B4H 			//07E0 	37B4
		BCR 	PCLATH,3 		//07E1 	118A

		//;test_61f13x_WDT.C: 110: WDT_INITIAL();
		BCR 	PCLATH,3 		//07E2 	118A
		ORG		07E3H
		LCALL 	7ABH 			//07E3 	37AB
		BCR 	PCLATH,3 		//07E4 	118A

		//;test_61f13x_WDT.C: 111: PA4 = 1;
		BSR 	5H,4 			//07E5 	1A05

		//;test_61f13x_WDT.C: 112: DelayMs(3);
		LDWI 	3H 			//07E6 	2A03
		BCR 	PCLATH,3 		//07E7 	118A
		LCALL 	7C5H 			//07E8 	37C5
		BCR 	PCLATH,3 		//07E9 	118A

		//;test_61f13x_WDT.C: 113: PA4 = 0;
		BCR 	STATUS,5 		//07EA 	1283
		ORG		07EBH
		BCR 	STATUS,6 		//07EB 	1303
		BCR 	5H,4 			//07EC 	1205

		//;test_61f13x_WDT.C: 114: DelayMs(3);
		LDWI 	3H 			//07ED 	2A03
		BCR 	PCLATH,3 		//07EE 	118A
		LCALL 	7C5H 			//07EF 	37C5
		BCR 	PCLATH,3 		//07F0 	118A

		//;test_61f13x_WDT.C: 116: {
		//;test_61f13x_WDT.C: 118: PA4 = 1;
		BCR 	STATUS,5 		//07F1 	1283
		BCR 	STATUS,6 		//07F2 	1303
		ORG		07F3H
		BSR 	5H,4 			//07F3 	1A05

		//;test_61f13x_WDT.C: 119: DelayMs(1);
		LDWI 	1H 			//07F4 	2A01
		BCR 	PCLATH,3 		//07F5 	118A
		LCALL 	7C5H 			//07F6 	37C5
		BCR 	PCLATH,3 		//07F7 	118A

		//;test_61f13x_WDT.C: 120: PA4 = 0;
		BCR 	STATUS,5 		//07F8 	1283
		BCR 	STATUS,6 		//07F9 	1303
		BCR 	5H,4 			//07FA 	1205
		ORG		07FBH

		//;test_61f13x_WDT.C: 121: DelayMs(1);
		LDWI 	1H 			//07FB 	2A01
		LJUMP 	7EEH 			//07FC 	3FEE
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7DFH 			//07FF 	3FDF
			END
