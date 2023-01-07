//Deviec:FT61F13X
//-----------------------Variable---------------------------------
//		DelayS@Time		EQU		75H
//		DelayS@b		EQU		77H
//		DelayS@a		EQU		76H
//		DelayS@Time		EQU		C00000H
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
		ORG		07AEH

		//;test_61f13x_SLEEP.C: 38: OSCCON = 0B01110001;
		LDWI 	71H 			//07AE 	2A71
		BSR 	STATUS,5 		//07AF 	1A83
		STR 	FH 			//07B0 	018F

		//;test_61f13x_SLEEP.C: 39: OPTION = 0B00001000;
		LDWI 	8H 			//07B1 	2A08
		STR 	1H 			//07B2 	0181

		//;test_61f13x_SLEEP.C: 40: INTCON = 0;
		CLRR 	INTCON 			//07B3 	010B

		//;test_61f13x_SLEEP.C: 42: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07B4 	1283
		CLRR 	5H 			//07B5 	0105
		ORG		07B6H

		//;test_61f13x_SLEEP.C: 43: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07B6 	1A83
		CLRR 	5H 			//07B7 	0105

		//;test_61f13x_SLEEP.C: 45: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07B8 	1283
		CLRR 	7H 			//07B9 	0107

		//;test_61f13x_SLEEP.C: 46: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07BA 	1A83
		CLRR 	7H 			//07BB 	0107

		//;test_61f13x_SLEEP.C: 48: WPUA = 0B00000000;
		CLRR 	15H 			//07BC 	0115

		//;test_61f13x_SLEEP.C: 49: WPUC = 0B00000000;
		CLRR 	13H 			//07BD 	0113
		ORG		07BEH
		RET		 					//07BE 	0004

		//;test_61f13x_SLEEP.C: 106: POWER_INITIAL();
		BCR 	PCLATH,3 		//07BF 	118A
		LCALL 	7AEH 			//07C0 	37AE
		BCR 	PCLATH,3 		//07C1 	118A

		//;test_61f13x_SLEEP.C: 107: PA1 = 1;
		BCR 	STATUS,5 		//07C2 	1283
		BSR 	5H,1 			//07C3 	1885

		//;test_61f13x_SLEEP.C: 108: PA0 = 1;
		BSR 	5H,0 			//07C4 	1805

		//;test_61f13x_SLEEP.C: 109: DelayS(4);
		LDWI 	4H 			//07C5 	2A04
		ORG		07C6H
		BCR 	PCLATH,3 		//07C6 	118A
		LCALL 	7D2H 			//07C7 	37D2
		BCR 	PCLATH,3 		//07C8 	118A

		//;test_61f13x_SLEEP.C: 110: PA1 = 0;
		BCR 	STATUS,5 		//07C9 	1283
		BCR 	STATUS,6 		//07CA 	1303
		BCR 	5H,1 			//07CB 	1085

		//;test_61f13x_SLEEP.C: 111: PA0 = 0;
		BCR 	5H,0 			//07CC 	1005

		//;test_61f13x_SLEEP.C: 113: while(1)
		CLRWDT	 			//07CD 	0001
		ORG		07CEH

		//;test_61f13x_SLEEP.C: 116: __nop();
		NOP		 					//07CE 	0000
		SLEEP	 			//07CF 	0002

		//;test_61f13x_SLEEP.C: 118: __nop();
		NOP		 					//07D0 	0000
		LJUMP 	7CDH 			//07D1 	3FCD
		STR 	75H 			//07D2 	01F5

		//;test_61f13x_SLEEP.C: 90: unsigned char a,b;
		//;test_61f13x_SLEEP.C: 91: for(a=0;a<Time;a++)
		CLRR 	76H 			//07D3 	0176
		LDR 	75H,0 			//07D4 	0875
		SUBWR 	76H,0 			//07D5 	0C76
		ORG		07D6H
		BTSC 	STATUS,0 		//07D6 	1403
		RET		 					//07D7 	0004

		//;test_61f13x_SLEEP.C: 92: {
		//;test_61f13x_SLEEP.C: 93: for(b=0;b<10;b++)
		CLRR 	77H 			//07D8 	0177

		//;test_61f13x_SLEEP.C: 94: {
		//;test_61f13x_SLEEP.C: 95: DelayMs(100);
		LDWI 	64H 			//07D9 	2A64
		LCALL 	7E3H 			//07DA 	37E3
		BCR 	PCLATH,3 		//07DB 	118A
		LDWI 	AH 			//07DC 	2A0A
		INCR	77H,1 			//07DD 	09F7
		ORG		07DEH
		SUBWR 	77H,0 			//07DE 	0C77
		BTSS 	STATUS,0 		//07DF 	1C03
		LJUMP 	7D9H 			//07E0 	3FD9
		INCR	76H,1 			//07E1 	09F6
		LJUMP 	7D4H 			//07E2 	3FD4
		STR 	72H 			//07E3 	01F2

		//;test_61f13x_SLEEP.C: 73: unsigned char a,b;
		//;test_61f13x_SLEEP.C: 74: for(a=0;a<Time;a++)
		CLRR 	73H 			//07E4 	0173
		LDR 	72H,0 			//07E5 	0872
		ORG		07E6H
		SUBWR 	73H,0 			//07E6 	0C73
		BTSC 	STATUS,0 		//07E7 	1403
		RET		 					//07E8 	0004

		//;test_61f13x_SLEEP.C: 75: {
		//;test_61f13x_SLEEP.C: 76: for(b=0;b<5;b++)
		CLRR 	74H 			//07E9 	0174

		//;test_61f13x_SLEEP.C: 77: {
		//;test_61f13x_SLEEP.C: 78: DelayUs(98);
		LDWI 	62H 			//07EA 	2A62
		LCALL 	7F4H 			//07EB 	37F4
		BCR 	PCLATH,3 		//07EC 	118A
		LDWI 	5H 			//07ED 	2A05
		ORG		07EEH
		INCR	74H,1 			//07EE 	09F4
		SUBWR 	74H,0 			//07EF 	0C74
		BTSS 	STATUS,0 		//07F0 	1C03
		LJUMP 	7EAH 			//07F1 	3FEA
		INCR	73H,1 			//07F2 	09F3
		LJUMP 	7E5H 			//07F3 	3FE5
		STR 	70H 			//07F4 	01F0

		//;test_61f13x_SLEEP.C: 59: unsigned char a;
		//;test_61f13x_SLEEP.C: 60: for(a=0;a<Time;a++)
		CLRR 	71H 			//07F5 	0171
		ORG		07F6H
		LDR 	70H,0 			//07F6 	0870
		SUBWR 	71H,0 			//07F7 	0C71
		BTSC 	STATUS,0 		//07F8 	1403
		RET		 					//07F9 	0004

		//;test_61f13x_SLEEP.C: 61: {
		//;test_61f13x_SLEEP.C: 62: __nop();
		NOP		 					//07FA 	0000
		INCR	71H,1 			//07FB 	09F1
		LJUMP 	7F6H 			//07FC 	3FF6
		CLRR 	STATUS 			//07FD 	0103
		ORG		07FEH
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7BFH 			//07FF 	3FBF
			END
