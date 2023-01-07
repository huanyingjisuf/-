//Deviec:FT61F02X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7C3H 			//0000 	3FC3
		ORG		07C3H
		CLRR 	STATUS 			//07C3 	0103
		LJUMP 	7CEH 			//07C4 	3FCE
		STR 	70H 			//07C5 	01F0

		//;test_61f02x_IO.C: 60: unsigned char a;
		//;test_61f02x_IO.C: 61: for(a=0;a<Time;a++)
		CLRR 	71H 			//07C6 	0171
		LDR 	70H,0 			//07C7 	0870
		SUBWR 	71H,0 			//07C8 	0C71
		BTSC 	STATUS,0 		//07C9 	1403
		RET		 					//07CA 	0004
		ORG		07CBH

		//;test_61f02x_IO.C: 62: {
		//;test_61f02x_IO.C: 63: _nop();
		NOP		 					//07CB 	0000
		INCR	71H,1 			//07CC 	09F1
		LJUMP 	7C7H 			//07CD 	3FC7

		//;test_61f02x_IO.C: 91: POWER_INITIAL();
		LCALL 	7EBH 			//07CE 	37EB
		LDWI 	AH 			//07CF 	2A0A

		//;test_61f02x_IO.C: 93: {
		//;test_61f02x_IO.C: 94: PA3 = 1;
		BCR 	STATUS,5 		//07D0 	1283
		BCR 	STATUS,6 		//07D1 	1303
		BSR 	5H,3 			//07D2 	1985
		ORG		07D3H

		//;test_61f02x_IO.C: 95: DelayMs(10);
		LCALL 	7DBH 			//07D3 	37DB

		//;test_61f02x_IO.C: 96: if(PC3 == 1)
		BCR 	STATUS,5 		//07D4 	1283
		BCR 	STATUS,6 		//07D5 	1303
		BTSC 	7H,3 			//07D6 	1587

		//;test_61f02x_IO.C: 97: {
		//;test_61f02x_IO.C: 98: PA3 = 0;
		BCR 	5H,3 			//07D7 	1185

		//;test_61f02x_IO.C: 99: }
		//;test_61f02x_IO.C: 100: DelayMs(10);
		LDWI 	AH 			//07D8 	2A0A
		LCALL 	7DBH 			//07D9 	37DB
		LJUMP 	7CFH 			//07DA 	3FCF
		ORG		07DBH
		STR 	72H 			//07DB 	01F2

		//;test_61f02x_IO.C: 74: unsigned char a,b;
		//;test_61f02x_IO.C: 75: for(a=0;a<Time;a++)
		CLRR 	73H 			//07DC 	0173
		LDR 	72H,0 			//07DD 	0872
		SUBWR 	73H,0 			//07DE 	0C73
		BTSC 	STATUS,0 		//07DF 	1403
		RET		 					//07E0 	0004

		//;test_61f02x_IO.C: 76: {
		//;test_61f02x_IO.C: 77: for(b=0;b<5;b++)
		CLRR 	74H 			//07E1 	0174

		//;test_61f02x_IO.C: 78: {
		//;test_61f02x_IO.C: 79: DelayUs(197);
		LDWI 	C5H 			//07E2 	2AC5
		ORG		07E3H
		LCALL 	7C5H 			//07E3 	37C5
		LDWI 	5H 			//07E4 	2A05
		INCR	74H,1 			//07E5 	09F4
		SUBWR 	74H,0 			//07E6 	0C74
		BTSS 	STATUS,0 		//07E7 	1C03
		LJUMP 	7E2H 			//07E8 	3FE2
		INCR	73H,1 			//07E9 	09F3
		LJUMP 	7DDH 			//07EA 	3FDD
		ORG		07EBH

		//;test_61f02x_IO.C: 35: OSCCON = 0B01110001;
		LDWI 	71H 			//07EB 	2A71
		BSR 	STATUS,5 		//07EC 	1A83
		STR 	FH 			//07ED 	018F

		//;test_61f02x_IO.C: 36: INTCON = 0;
		CLRR 	INTCON 			//07EE 	010B

		//;test_61f02x_IO.C: 37: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07EF 	1283
		CLRR 	5H 			//07F0 	0105

		//;test_61f02x_IO.C: 38: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07F1 	1A83
		CLRR 	5H 			//07F2 	0105
		ORG		07F3H

		//;test_61f02x_IO.C: 39: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07F3 	1283
		CLRR 	7H 			//07F4 	0107

		//;test_61f02x_IO.C: 40: TRISC = 0B00001000;
		LDWI 	8H 			//07F5 	2A08
		BSR 	STATUS,5 		//07F6 	1A83
		STR 	7H 			//07F7 	0187

		//;test_61f02x_IO.C: 42: WPUA = 0B00000000;
		CLRR 	15H 			//07F8 	0115

		//;test_61f02x_IO.C: 43: WPUC = 0B00001000;
		STR 	8H 			//07F9 	0188

		//;test_61f02x_IO.C: 45: OPTION = 0B00001000;
		STR 	1H 			//07FA 	0181
		ORG		07FBH

		//;test_61f02x_IO.C: 46: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07FB 	1283
		CLRR 	1BH 			//07FC 	011B

		//;test_61f02x_IO.C: 50: CMCON0 = 0B00000111;
		LDWI 	7H 			//07FD 	2A07
		STR 	19H 			//07FE 	0199
		RET		 					//07FF 	0004
			END
