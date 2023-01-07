//Deviec:FT61F13X
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
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FDH 			//0001 	3FFD
		ORG		07ABH

		//;test_61f13x_MSCK.C: 120: POWER_INITIAL();
		BCR 	PCLATH,3 		//07AB 	118A
		LCALL 	7BBH 			//07AC 	37BB
		BCR 	PCLATH,3 		//07AD 	118A

		//;test_61f13x_MSCK.C: 123: {
		//;test_61f13x_MSCK.C: 125: TestBuff = SlowTimeTest();
		BCR 	PCLATH,3 		//07AE 	118A
		LCALL 	7CEH 			//07AF 	37CE
		BCR 	PCLATH,3 		//07B0 	118A
		LDR 	71H,0 			//07B1 	0871
		STR 	76H 			//07B2 	01F6
		ORG		07B3H
		LDR 	70H,0 			//07B3 	0870
		STR 	75H 			//07B4 	01F5

		//;test_61f13x_MSCK.C: 128: __nop();
		NOP		 					//07B5 	0000

		//;test_61f13x_MSCK.C: 129: DelayMs(200);
		LDWI 	C8H 			//07B6 	2AC8
		BCR 	PCLATH,3 		//07B7 	118A
		LCALL 	7E3H 			//07B8 	37E3
		BCR 	PCLATH,3 		//07B9 	118A
		LJUMP 	7AEH 			//07BA 	3FAE
		ORG		07BBH

		//;test_61f13x_MSCK.C: 39: OSCCON = 0B01110001;
		LDWI 	71H 			//07BB 	2A71
		BSR 	STATUS,5 		//07BC 	1A83
		STR 	FH 			//07BD 	018F

		//;test_61f13x_MSCK.C: 40: OPTION = 0B00001000;
		LDWI 	8H 			//07BE 	2A08
		STR 	1H 			//07BF 	0181

		//;test_61f13x_MSCK.C: 41: INTCON = 0;
		CLRR 	INTCON 			//07C0 	010B

		//;test_61f13x_MSCK.C: 42: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07C1 	1283
		CLRR 	5H 			//07C2 	0105
		ORG		07C3H

		//;test_61f13x_MSCK.C: 43: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07C3 	1A83
		CLRR 	5H 			//07C4 	0105

		//;test_61f13x_MSCK.C: 45: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07C5 	1283
		CLRR 	7H 			//07C6 	0107

		//;test_61f13x_MSCK.C: 46: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07C7 	1A83
		CLRR 	7H 			//07C8 	0107

		//;test_61f13x_MSCK.C: 48: WPUA = 0B00000000;
		CLRR 	15H 			//07C9 	0115

		//;test_61f13x_MSCK.C: 49: WPUC = 0B00000000;
		CLRR 	13H 			//07CA 	0113
		ORG		07CBH

		//;test_61f13x_MSCK.C: 51: MSCON0 = 0B00000000;
		BCR 	STATUS,5 		//07CB 	1283
		CLRR 	1BH 			//07CC 	011B
		RET		 					//07CD 	0004

		//;test_61f13x_MSCK.C: 100: unsigned int TestTime;
		//;test_61f13x_MSCK.C: 101: TMR2ON = 1;
		BCR 	STATUS,5 		//07CE 	1283
		BCR 	STATUS,6 		//07CF 	1303
		BSR 	12H,2 			//07D0 	1912

		//;test_61f13x_MSCK.C: 102: CKMIF = 0;
		BCR 	CH,6 			//07D1 	130C

		//;test_61f13x_MSCK.C: 103: CKMAVG = 0;
		BCR 	1BH,2 			//07D2 	111B
		ORG		07D3H

		//;test_61f13x_MSCK.C: 105: CKCNTI = 1;
		BSR 	1BH,1 			//07D3 	189B

		//;test_61f13x_MSCK.C: 106: while(!CKMIF);
		BTSS 	CH,6 			//07D4 	1F0C
		LJUMP 	7D4H 			//07D5 	3FD4

		//;test_61f13x_MSCK.C: 107: CKMIF = 0;
		BCR 	CH,6 			//07D6 	130C

		//;test_61f13x_MSCK.C: 108: TestTime = SOSCPRH << 8;
		LDR 	1DH,0 			//07D7 	081D
		STR 	73H 			//07D8 	01F3
		CLRR 	72H 			//07D9 	0172

		//;test_61f13x_MSCK.C: 109: TestTime = TestTime + SOSCPRL;
		LDR 	1CH,0 			//07DA 	081C
		ORG		07DBH
		ADDWR 	72H,1 			//07DB 	0BF2
		BTSC 	STATUS,0 		//07DC 	1403
		INCR	73H,1 			//07DD 	09F3

		//;test_61f13x_MSCK.C: 110: return TestTime;
		LDR 	73H,0 			//07DE 	0873
		STR 	71H 			//07DF 	01F1
		LDR 	72H,0 			//07E0 	0872
		STR 	70H 			//07E1 	01F0
		RET		 					//07E2 	0004
		ORG		07E3H
		STR 	72H 			//07E3 	01F2

		//;test_61f13x_MSCK.C: 81: unsigned char a,b;
		//;test_61f13x_MSCK.C: 82: for(a=0;a<Time;a++)
		CLRR 	73H 			//07E4 	0173
		LDR 	72H,0 			//07E5 	0872
		SUBWR 	73H,0 			//07E6 	0C73
		BTSC 	STATUS,0 		//07E7 	1403
		RET		 					//07E8 	0004

		//;test_61f13x_MSCK.C: 83: {
		//;test_61f13x_MSCK.C: 84: for(b=0;b<5;b++)
		CLRR 	74H 			//07E9 	0174

		//;test_61f13x_MSCK.C: 85: {
		//;test_61f13x_MSCK.C: 86: DelayUs(197);
		LDWI 	C5H 			//07EA 	2AC5
		ORG		07EBH
		LCALL 	7F4H 			//07EB 	37F4
		BCR 	PCLATH,3 		//07EC 	118A
		LDWI 	5H 			//07ED 	2A05
		INCR	74H,1 			//07EE 	09F4
		SUBWR 	74H,0 			//07EF 	0C74
		BTSS 	STATUS,0 		//07F0 	1C03
		LJUMP 	7EAH 			//07F1 	3FEA
		INCR	73H,1 			//07F2 	09F3
		ORG		07F3H
		LJUMP 	7E5H 			//07F3 	3FE5
		STR 	70H 			//07F4 	01F0

		//;test_61f13x_MSCK.C: 67: unsigned char a;
		//;test_61f13x_MSCK.C: 68: for(a=0;a<Time;a++)
		CLRR 	71H 			//07F5 	0171
		LDR 	70H,0 			//07F6 	0870
		SUBWR 	71H,0 			//07F7 	0C71
		BTSC 	STATUS,0 		//07F8 	1403
		RET		 					//07F9 	0004

		//;test_61f13x_MSCK.C: 69: {
		//;test_61f13x_MSCK.C: 70: __nop();
		NOP		 					//07FA 	0000
		ORG		07FBH
		INCR	71H,1 			//07FB 	09F1
		LJUMP 	7F6H 			//07FC 	3FF6
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7ABH 			//07FF 	3FAB
			END
