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
		ORG		07BEH

		//;test_61f13x_IO.C: 48: OSCCON = 0B01110001;
		LDWI 	71H 			//07BE 	2A71
		BSR 	STATUS,5 		//07BF 	1A83
		STR 	FH 			//07C0 	018F

		//;test_61f13x_IO.C: 49: OPTION = 0B00001000;
		LDWI 	8H 			//07C1 	2A08
		STR 	1H 			//07C2 	0181

		//;test_61f13x_IO.C: 50: INTCON = 0;
		CLRR 	INTCON 			//07C3 	010B

		//;test_61f13x_IO.C: 52: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07C4 	1283
		CLRR 	5H 			//07C5 	0105
		ORG		07C6H

		//;test_61f13x_IO.C: 53: TRISA = 0B01000000;
		LDWI 	40H 			//07C6 	2A40
		BSR 	STATUS,5 		//07C7 	1A83
		STR 	5H 			//07C8 	0185

		//;test_61f13x_IO.C: 55: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07C9 	1283
		CLRR 	7H 			//07CA 	0107

		//;test_61f13x_IO.C: 56: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07CB 	1A83
		CLRR 	7H 			//07CC 	0107

		//;test_61f13x_IO.C: 58: WPUA = 0B01000000;
		STR 	15H 			//07CD 	0195
		ORG		07CEH

		//;test_61f13x_IO.C: 60: WPUC = 0B00000000;
		CLRR 	13H 			//07CE 	0113
		RET		 					//07CF 	0004

		//;test_61f13x_IO.C: 101: POWER_INITIAL();
		BCR 	PCLATH,3 		//07D0 	118A
		LCALL 	7BEH 			//07D1 	37BE
		BCR 	PCLATH,3 		//07D2 	118A

		//;test_61f13x_IO.C: 104: {
		//;test_61f13x_IO.C: 105: PA4 = 1;
		BCR 	STATUS,5 		//07D3 	1283
		BCR 	STATUS,6 		//07D4 	1303
		BSR 	5H,4 			//07D5 	1A05
		ORG		07D6H

		//;test_61f13x_IO.C: 106: DelayMs(10);
		LDWI 	AH 			//07D6 	2A0A
		BCR 	PCLATH,3 		//07D7 	118A
		LCALL 	7E3H 			//07D8 	37E3
		BCR 	PCLATH,3 		//07D9 	118A

		//;test_61f13x_IO.C: 107: if(PA6 == 1)
		BCR 	STATUS,5 		//07DA 	1283
		BCR 	STATUS,6 		//07DB 	1303
		BTSC 	5H,6 			//07DC 	1705

		//;test_61f13x_IO.C: 108: {
		//;test_61f13x_IO.C: 109: PA4 = 0;
		BCR 	5H,4 			//07DD 	1205
		ORG		07DEH

		//;test_61f13x_IO.C: 110: }
		//;test_61f13x_IO.C: 111: DelayMs(10);
		LDWI 	AH 			//07DE 	2A0A
		BCR 	PCLATH,3 		//07DF 	118A
		LCALL 	7E3H 			//07E0 	37E3
		BCR 	PCLATH,3 		//07E1 	118A
		LJUMP 	7D3H 			//07E2 	3FD3
		STR 	72H 			//07E3 	01F2

		//;test_61f13x_IO.C: 84: unsigned char a,b;
		//;test_61f13x_IO.C: 85: for(a=0;a<Time;a++)
		CLRR 	73H 			//07E4 	0173
		LDR 	72H,0 			//07E5 	0872
		ORG		07E6H
		SUBWR 	73H,0 			//07E6 	0C73
		BTSC 	STATUS,0 		//07E7 	1403
		RET		 					//07E8 	0004

		//;test_61f13x_IO.C: 86: {
		//;test_61f13x_IO.C: 87: for(b=0;b<5;b++)
		CLRR 	74H 			//07E9 	0174

		//;test_61f13x_IO.C: 88: {
		//;test_61f13x_IO.C: 89: DelayUs(197);
		LDWI 	C5H 			//07EA 	2AC5
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

		//;test_61f13x_IO.C: 70: unsigned char a;
		//;test_61f13x_IO.C: 71: for(a=0;a<Time;a++)
		CLRR 	71H 			//07F5 	0171
		ORG		07F6H
		LDR 	70H,0 			//07F6 	0870
		SUBWR 	71H,0 			//07F7 	0C71
		BTSC 	STATUS,0 		//07F8 	1403
		RET		 					//07F9 	0004

		//;test_61f13x_IO.C: 72: {
		//;test_61f13x_IO.C: 73: __nop();
		NOP		 					//07FA 	0000
		INCR	71H,1 			//07FB 	09F1
		LJUMP 	7F6H 			//07FC 	3FF6
		CLRR 	STATUS 			//07FD 	0103
		ORG		07FEH
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7D0H 			//07FF 	3FD0
			END
