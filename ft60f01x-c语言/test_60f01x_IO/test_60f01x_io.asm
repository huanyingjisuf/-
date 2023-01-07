//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	3CBH 			//0000 	3BCB
		ORG		03CBH
		CLRR 	STATUS 			//03CB 	0103
		LJUMP 	3D6H 			//03CC 	3BD6
		STR 	40H 			//03CD 	01C0

		//;test_60f01x_io.C: 56: unsigned char a;
		//;test_60f01x_io.C: 57: for(a=0;a<Time;a++)
		CLRR 	41H 			//03CE 	0141
		LDR 	40H,0 			//03CF 	0840
		SUBWR 	41H,0 			//03D0 	0C41
		BTSC 	STATUS,0 		//03D1 	1403
		RET		 					//03D2 	0004
		ORG		03D3H

		//;test_60f01x_io.C: 58: {
		//;test_60f01x_io.C: 59: _nop();
		NOP		 					//03D3 	0000
		INCR	41H,1 			//03D4 	09C1
		LJUMP 	3CFH 			//03D5 	3BCF

		//;test_60f01x_io.C: 87: POWER_INITIAL();
		LCALL 	3E1H 			//03D6 	33E1
		LDWI 	AH 			//03D7 	2A0A

		//;test_60f01x_io.C: 89: {
		//;test_60f01x_io.C: 90: PA4 = 1;
		BCR 	STATUS,5 		//03D8 	1283
		BSR 	5H,4 			//03D9 	1A05

		//;test_60f01x_io.C: 91: DelayMs(10);
		LCALL 	3F0H 			//03DA 	33F0
		ORG		03DBH

		//;test_60f01x_io.C: 92: if(PA2 == 1)
		BCR 	STATUS,5 		//03DB 	1283
		BTSC 	5H,2 			//03DC 	1505

		//;test_60f01x_io.C: 93: {
		//;test_60f01x_io.C: 94: PA4 = 0;
		BCR 	5H,4 			//03DD 	1205

		//;test_60f01x_io.C: 95: }
		//;test_60f01x_io.C: 96: DelayMs(10);
		LDWI 	AH 			//03DE 	2A0A
		LCALL 	3F0H 			//03DF 	33F0
		LJUMP 	3D7H 			//03E0 	3BD7

		//;test_60f01x_io.C: 33: OSCCON = 0B01110000;
		LDWI 	70H 			//03E1 	2A70
		BSR 	STATUS,5 		//03E2 	1A83
		ORG		03E3H
		STR 	FH 			//03E3 	018F

		//;test_60f01x_io.C: 35: INTCON = 0;
		CLRR 	INTCON 			//03E4 	010B

		//;test_60f01x_io.C: 36: OPTION = 0B00001000;
		LDWI 	8H 			//03E5 	2A08
		STR 	1H 			//03E6 	0181

		//;test_60f01x_io.C: 38: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03E7 	1283
		CLRR 	5H 			//03E8 	0105

		//;test_60f01x_io.C: 39: TRISA = 0B00000100;
		LDWI 	4H 			//03E9 	2A04
		BSR 	STATUS,5 		//03EA 	1A83
		ORG		03EBH
		STR 	5H 			//03EB 	0185

		//;test_60f01x_io.C: 41: WPUA = 0B00000100;
		STR 	15H 			//03EC 	0195

		//;test_60f01x_io.C: 43: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03ED 	1283
		CLRR 	1BH 			//03EE 	011B
		RET		 					//03EF 	0004
		STR 	42H 			//03F0 	01C2

		//;test_60f01x_io.C: 70: unsigned char a,b;
		//;test_60f01x_io.C: 71: for(a=0;a<Time;a++)
		CLRR 	43H 			//03F1 	0143
		LDR 	42H,0 			//03F2 	0842
		ORG		03F3H
		SUBWR 	43H,0 			//03F3 	0C43
		BTSC 	STATUS,0 		//03F4 	1403
		RET		 					//03F5 	0004

		//;test_60f01x_io.C: 72: {
		//;test_60f01x_io.C: 73: for(b=0;b<5;b++)
		CLRR 	44H 			//03F6 	0144

		//;test_60f01x_io.C: 74: {
		//;test_60f01x_io.C: 75: DelayUs(98);
		LDWI 	62H 			//03F7 	2A62
		LCALL 	3CDH 			//03F8 	33CD
		LDWI 	5H 			//03F9 	2A05
		INCR	44H,1 			//03FA 	09C4
		ORG		03FBH
		SUBWR 	44H,0 			//03FB 	0C44
		BTSS 	STATUS,0 		//03FC 	1C03
		LJUMP 	3F7H 			//03FD 	3BF7
		INCR	43H,1 			//03FE 	09C3
		LJUMP 	3F2H 			//03FF 	3BF2
			END
