//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_TestBuff		EQU		75H
//		SlowTimeTest@TestTime		EQU		72H
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
		ORG		07ACH
		STR 	70H 			//07AC 	01F0

		//;test_61f02x_MSCK.C: 58: unsigned char a;
		//;test_61f02x_MSCK.C: 59: for(a=0;a<Time;a++)
		CLRR 	71H 			//07AD 	0171
		LDR 	70H,0 			//07AE 	0870
		SUBWR 	71H,0 			//07AF 	0C71
		BTSC 	STATUS,0 		//07B0 	1403
		RET		 					//07B1 	0004

		//;test_61f02x_MSCK.C: 60: {
		//;test_61f02x_MSCK.C: 61: __nop();
		NOP		 					//07B2 	0000
		INCR	71H,1 			//07B3 	09F1
		ORG		07B4H
		LJUMP 	7AEH 			//07B4 	3FAE

		//;test_61f02x_MSCK.C: 112: POWER_INITIAL();
		LCALL 	7D1H 			//07B5 	37D1

		//;test_61f02x_MSCK.C: 114: {
		//;test_61f02x_MSCK.C: 115: TestBuff = SlowTimeTest();
		LCALL 	7E6H 			//07B6 	37E6
		LDR 	71H,0 			//07B7 	0871
		STR 	76H 			//07B8 	01F6
		LDR 	70H,0 			//07B9 	0870
		STR 	75H 			//07BA 	01F5

		//;test_61f02x_MSCK.C: 117: __nop();
		NOP		 					//07BB 	0000
		ORG		07BCH

		//;test_61f02x_MSCK.C: 118: __nop();
		NOP		 					//07BC 	0000

		//;test_61f02x_MSCK.C: 119: __nop();
		NOP		 					//07BD 	0000

		//;test_61f02x_MSCK.C: 120: DelayMs(200);
		LDWI 	C8H 			//07BE 	2AC8
		LCALL 	7C1H 			//07BF 	37C1
		LJUMP 	7B6H 			//07C0 	3FB6
		STR 	72H 			//07C1 	01F2

		//;test_61f02x_MSCK.C: 72: unsigned char a,b;
		//;test_61f02x_MSCK.C: 73: for(a=0;a<Time;a++)
		CLRR 	73H 			//07C2 	0173
		LDR 	72H,0 			//07C3 	0872
		ORG		07C4H
		SUBWR 	73H,0 			//07C4 	0C73
		BTSC 	STATUS,0 		//07C5 	1403
		RET		 					//07C6 	0004

		//;test_61f02x_MSCK.C: 74: {
		//;test_61f02x_MSCK.C: 75: for(b=0;b<5;b++)
		CLRR 	74H 			//07C7 	0174

		//;test_61f02x_MSCK.C: 76: {
		//;test_61f02x_MSCK.C: 77: DelayUs(197);
		LDWI 	C5H 			//07C8 	2AC5
		LCALL 	7ACH 			//07C9 	37AC
		LDWI 	5H 			//07CA 	2A05
		INCR	74H,1 			//07CB 	09F4
		ORG		07CCH
		SUBWR 	74H,0 			//07CC 	0C74
		BTSS 	STATUS,0 		//07CD 	1C03
		LJUMP 	7C8H 			//07CE 	3FC8
		INCR	73H,1 			//07CF 	09F3
		LJUMP 	7C3H 			//07D0 	3FC3

		//;test_61f02x_MSCK.C: 34: OSCCON = 0B01110001;
		LDWI 	71H 			//07D1 	2A71
		BSR 	STATUS,5 		//07D2 	1A83
		STR 	FH 			//07D3 	018F
		ORG		07D4H

		//;test_61f02x_MSCK.C: 35: INTCON = 0;
		CLRR 	INTCON 			//07D4 	010B

		//;test_61f02x_MSCK.C: 36: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07D5 	1283
		CLRR 	5H 			//07D6 	0105

		//;test_61f02x_MSCK.C: 37: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07D7 	1A83
		CLRR 	5H 			//07D8 	0105

		//;test_61f02x_MSCK.C: 38: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07D9 	1283
		CLRR 	7H 			//07DA 	0107

		//;test_61f02x_MSCK.C: 39: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07DB 	1A83
		ORG		07DCH
		CLRR 	7H 			//07DC 	0107

		//;test_61f02x_MSCK.C: 40: WPUA = 0;
		CLRR 	15H 			//07DD 	0115

		//;test_61f02x_MSCK.C: 41: WPUC = 0;
		CLRR 	8H 			//07DE 	0108

		//;test_61f02x_MSCK.C: 43: OPTION = 0B00001000;
		LDWI 	8H 			//07DF 	2A08
		STR 	1H 			//07E0 	0181

		//;test_61f02x_MSCK.C: 44: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07E1 	1283
		CLRR 	1BH 			//07E2 	011B

		//;test_61f02x_MSCK.C: 48: CMCON0 = 0B00000111;
		LDWI 	7H 			//07E3 	2A07
		ORG		07E4H
		STR 	19H 			//07E4 	0199
		RET		 					//07E5 	0004

		//;test_61f02x_MSCK.C: 91: unsigned int TestTime;
		//;test_61f02x_MSCK.C: 92: OSCCON = 0B01110001;
		LDWI 	71H 			//07E6 	2A71
		BSR 	STATUS,5 		//07E7 	1A83
		BCR 	STATUS,6 		//07E8 	1303
		STR 	FH 			//07E9 	018F

		//;test_61f02x_MSCK.C: 93: TMR2ON = 1;
		BCR 	STATUS,5 		//07EA 	1283
		BSR 	12H,2 			//07EB 	1912
		ORG		07ECH

		//;test_61f02x_MSCK.C: 94: CKMEAIF = 0;
		BCR 	CH,6 			//07EC 	130C

		//;test_61f02x_MSCK.C: 95: CKMAVG = 0;
		BCR 	1BH,2 			//07ED 	111B

		//;test_61f02x_MSCK.C: 97: CKCNTI = 1;
		BSR 	1BH,1 			//07EE 	189B

		//;test_61f02x_MSCK.C: 98: while(!CKMEAIF);
		BTSS 	CH,6 			//07EF 	1F0C
		LJUMP 	7EFH 			//07F0 	3FEF

		//;test_61f02x_MSCK.C: 99: CKMEAIF = 0;
		BCR 	CH,6 			//07F1 	130C

		//;test_61f02x_MSCK.C: 100: TestTime = SOSCPRH << 8;
		LDR 	1DH,0 			//07F2 	081D
		STR 	73H 			//07F3 	01F3
		ORG		07F4H
		CLRR 	72H 			//07F4 	0172

		//;test_61f02x_MSCK.C: 101: TestTime = TestTime + SOSCPRL;
		LDR 	1CH,0 			//07F5 	081C
		ADDWR 	72H,1 			//07F6 	0BF2
		BTSC 	STATUS,0 		//07F7 	1403
		INCR	73H,1 			//07F8 	09F3

		//;test_61f02x_MSCK.C: 102: return TestTime;
		LDR 	73H,0 			//07F9 	0873
		STR 	71H 			//07FA 	01F1
		LDR 	72H,0 			//07FB 	0872
		ORG		07FCH
		STR 	70H 			//07FC 	01F0
		RET		 					//07FD 	0004
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7B5H 			//07FF 	3FB5
			END
