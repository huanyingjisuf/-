//Deviec:FT60F01X
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
		LJUMP 	3FEH 			//0000 	3BFE
		ORG		03B9H
		STR 	70H 			//03B9 	01F0

		//;test_60f01x_MSCK.C: 50: unsigned char a;
		//;test_60f01x_MSCK.C: 51: for(a=0;a<Time;a++)
		CLRR 	71H 			//03BA 	0171
		LDR 	70H,0 			//03BB 	0870
		SUBWR 	71H,0 			//03BC 	0C71
		BTSC 	STATUS,0 		//03BD 	1403
		RET		 					//03BE 	0004

		//;test_60f01x_MSCK.C: 52: {
		//;test_60f01x_MSCK.C: 53: __nop();
		NOP		 					//03BF 	0000
		INCR	71H,1 			//03C0 	09F1
		ORG		03C1H
		LJUMP 	3BBH 			//03C1 	3BBB

		//;test_60f01x_MSCK.C: 103: POWER_INITIAL();
		LCALL 	3CCH 			//03C2 	33CC

		//;test_60f01x_MSCK.C: 105: {
		//;test_60f01x_MSCK.C: 107: TestBuff = SlowTimeTest();
		LCALL 	3EAH 			//03C3 	33EA
		LDR 	71H,0 			//03C4 	0871
		STR 	76H 			//03C5 	01F6
		LDR 	70H,0 			//03C6 	0870
		STR 	75H 			//03C7 	01F5

		//;test_60f01x_MSCK.C: 109: __nop();
		NOP		 					//03C8 	0000
		ORG		03C9H

		//;test_60f01x_MSCK.C: 110: DelayMs(200);
		LDWI 	C8H 			//03C9 	2AC8
		LCALL 	3DAH 			//03CA 	33DA
		LJUMP 	3C3H 			//03CB 	3BC3

		//;test_60f01x_MSCK.C: 30: OSCCON = 0B01110000;
		LDWI 	70H 			//03CC 	2A70
		BSR 	STATUS,5 		//03CD 	1A83
		STR 	FH 			//03CE 	018F

		//;test_60f01x_MSCK.C: 31: INTCON = 0;
		CLRR 	INTCON 			//03CF 	010B

		//;test_60f01x_MSCK.C: 32: OPTION = 0B00001000;
		LDWI 	8H 			//03D0 	2A08
		ORG		03D1H
		STR 	1H 			//03D1 	0181

		//;test_60f01x_MSCK.C: 34: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03D2 	1283
		CLRR 	5H 			//03D3 	0105

		//;test_60f01x_MSCK.C: 35: TRISA = 0B00000000;
		BSR 	STATUS,5 		//03D4 	1A83
		CLRR 	5H 			//03D5 	0105

		//;test_60f01x_MSCK.C: 36: WPUA = 0B00000000;
		CLRR 	15H 			//03D6 	0115

		//;test_60f01x_MSCK.C: 37: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03D7 	1283
		CLRR 	1BH 			//03D8 	011B
		ORG		03D9H
		RET		 					//03D9 	0004
		STR 	72H 			//03DA 	01F2

		//;test_60f01x_MSCK.C: 64: unsigned char a,b;
		//;test_60f01x_MSCK.C: 65: for(a=0;a<Time;a++)
		CLRR 	73H 			//03DB 	0173
		LDR 	72H,0 			//03DC 	0872
		SUBWR 	73H,0 			//03DD 	0C73
		BTSC 	STATUS,0 		//03DE 	1403
		RET		 					//03DF 	0004

		//;test_60f01x_MSCK.C: 66: {
		//;test_60f01x_MSCK.C: 67: for(b=0;b<5;b++)
		CLRR 	74H 			//03E0 	0174
		ORG		03E1H

		//;test_60f01x_MSCK.C: 68: {
		//;test_60f01x_MSCK.C: 69: DelayUs(98);
		LDWI 	62H 			//03E1 	2A62
		LCALL 	3B9H 			//03E2 	33B9
		LDWI 	5H 			//03E3 	2A05
		INCR	74H,1 			//03E4 	09F4
		SUBWR 	74H,0 			//03E5 	0C74
		BTSS 	STATUS,0 		//03E6 	1C03
		LJUMP 	3E1H 			//03E7 	3BE1
		INCR	73H,1 			//03E8 	09F3
		ORG		03E9H
		LJUMP 	3DCH 			//03E9 	3BDC

		//;test_60f01x_MSCK.C: 83: unsigned int TestTime;
		//;test_60f01x_MSCK.C: 84: TMR2ON = 1;
		BCR 	STATUS,5 		//03EA 	1283
		BSR 	12H,2 			//03EB 	1912

		//;test_60f01x_MSCK.C: 85: CKMEAIF = 0;
		BCR 	CH,6 			//03EC 	130C

		//;test_60f01x_MSCK.C: 86: CKMAVG = 0;
		BCR 	1BH,2 			//03ED 	111B

		//;test_60f01x_MSCK.C: 88: CKCNTI = 1;
		BSR 	1BH,1 			//03EE 	189B

		//;test_60f01x_MSCK.C: 89: while(!CKMEAIF);
		BTSS 	CH,6 			//03EF 	1F0C
		LJUMP 	3EFH 			//03F0 	3BEF
		ORG		03F1H

		//;test_60f01x_MSCK.C: 90: CKMEAIF = 0;
		BCR 	CH,6 			//03F1 	130C

		//;test_60f01x_MSCK.C: 91: TestTime = SOSCPRH << 8;
		LDR 	1DH,0 			//03F2 	081D
		STR 	73H 			//03F3 	01F3
		CLRR 	72H 			//03F4 	0172

		//;test_60f01x_MSCK.C: 92: TestTime = TestTime + SOSCPRL;
		LDR 	1CH,0 			//03F5 	081C
		ADDWR 	72H,1 			//03F6 	0BF2
		BTSC 	STATUS,0 		//03F7 	1403
		INCR	73H,1 			//03F8 	09F3
		ORG		03F9H

		//;test_60f01x_MSCK.C: 93: return TestTime;
		LDR 	73H,0 			//03F9 	0873
		STR 	71H 			//03FA 	01F1
		LDR 	72H,0 			//03FB 	0872
		STR 	70H 			//03FC 	01F0
		RET		 					//03FD 	0004
		CLRR 	STATUS 			//03FE 	0103
		LJUMP 	3C2H 			//03FF 	3BC2
			END
