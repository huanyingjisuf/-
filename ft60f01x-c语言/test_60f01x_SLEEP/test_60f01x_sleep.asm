//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	3BAH 			//0000 	3BBA
		ORG		03BAH
		CLRR 	STATUS 			//03BA 	0103
		LJUMP 	3C5H 			//03BB 	3BC5
		STR 	40H 			//03BC 	01C0

		//;test_60f01x_sleep.C: 53: unsigned char a;
		//;test_60f01x_sleep.C: 54: for(a=0;a<Time;a++)
		CLRR 	41H 			//03BD 	0141
		LDR 	40H,0 			//03BE 	0840
		SUBWR 	41H,0 			//03BF 	0C41
		BTSC 	STATUS,0 		//03C0 	1403
		RET		 					//03C1 	0004
		ORG		03C2H
		CLRWDT	 			//03C2 	0001
		INCR	41H,1 			//03C3 	09C1
		LJUMP 	3BEH 			//03C4 	3BBE

		//;test_60f01x_sleep.C: 101: POWER_INITIAL();
		LCALL 	3D2H 			//03C5 	33D2
		LDWI 	4H 			//03C6 	2A04

		//;test_60f01x_sleep.C: 102: PA1 = 1;
		BSR 	5H,1 			//03C7 	1885
		BSR 	5H,0 			//03C8 	1805

		//;test_60f01x_sleep.C: 104: DelayS(4);
		LCALL 	3F0H 			//03C9 	33F0
		ORG		03CAH

		//;test_60f01x_sleep.C: 105: PA1 = 0;
		BCR 	STATUS,5 		//03CA 	1283
		BCR 	5H,1 			//03CB 	1085

		//;test_60f01x_sleep.C: 106: PA0 = 0;
		BCR 	5H,0 			//03CC 	1005
		CLRWDT	 			//03CD 	0001

		//;test_60f01x_sleep.C: 110: _nop();
		NOP		 					//03CE 	0000
		SLEEP	 			//03CF 	0002

		//;test_60f01x_sleep.C: 112: _nop();
		NOP		 					//03D0 	0000
		LJUMP 	3CDH 			//03D1 	3BCD
		ORG		03D2H

		//;test_60f01x_sleep.C: 32: OSCCON = 0B01110000;
		LDWI 	70H 			//03D2 	2A70
		BSR 	STATUS,5 		//03D3 	1A83
		STR 	FH 			//03D4 	018F

		//;test_60f01x_sleep.C: 33: INTCON = 0;
		CLRR 	INTCON 			//03D5 	010B

		//;test_60f01x_sleep.C: 34: OPTION = 0B00001000;
		LDWI 	8H 			//03D6 	2A08
		STR 	1H 			//03D7 	0181

		//;test_60f01x_sleep.C: 36: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03D8 	1283
		CLRR 	5H 			//03D9 	0105
		ORG		03DAH

		//;test_60f01x_sleep.C: 37: TRISA = 0B00000000;
		BSR 	STATUS,5 		//03DA 	1A83
		CLRR 	5H 			//03DB 	0105

		//;test_60f01x_sleep.C: 38: WPUA = 0B00000000;
		CLRR 	15H 			//03DC 	0115

		//;test_60f01x_sleep.C: 40: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03DD 	1283
		CLRR 	1BH 			//03DE 	011B
		RET		 					//03DF 	0004
		STR 	42H 			//03E0 	01C2

		//;test_60f01x_sleep.C: 67: unsigned char a,b;
		//;test_60f01x_sleep.C: 68: for(a=0;a<Time;a++)
		CLRR 	43H 			//03E1 	0143
		ORG		03E2H
		LDR 	42H,0 			//03E2 	0842
		SUBWR 	43H,0 			//03E3 	0C43
		BTSC 	STATUS,0 		//03E4 	1403
		RET		 					//03E5 	0004

		//;test_60f01x_sleep.C: 69: {
		//;test_60f01x_sleep.C: 70: for(b=0;b<5;b++)
		CLRR 	44H 			//03E6 	0144

		//;test_60f01x_sleep.C: 71: {
		//;test_60f01x_sleep.C: 72: DelayUs(98);
		LDWI 	62H 			//03E7 	2A62
		LCALL 	3BCH 			//03E8 	33BC
		LDWI 	5H 			//03E9 	2A05
		ORG		03EAH
		INCR	44H,1 			//03EA 	09C4
		SUBWR 	44H,0 			//03EB 	0C44
		BTSS 	STATUS,0 		//03EC 	1C03
		LJUMP 	3E7H 			//03ED 	3BE7
		INCR	43H,1 			//03EE 	09C3
		LJUMP 	3E2H 			//03EF 	3BE2
		STR 	45H 			//03F0 	01C5

		//;test_60f01x_sleep.C: 84: unsigned char a,b;
		//;test_60f01x_sleep.C: 85: for(a=0;a<Time;a++)
		CLRR 	46H 			//03F1 	0146
		ORG		03F2H
		LDR 	45H,0 			//03F2 	0845
		SUBWR 	46H,0 			//03F3 	0C46
		BTSC 	STATUS,0 		//03F4 	1403
		RET		 					//03F5 	0004

		//;test_60f01x_sleep.C: 86: {
		//;test_60f01x_sleep.C: 87: for(b=0;b<10;b++)
		CLRR 	47H 			//03F6 	0147

		//;test_60f01x_sleep.C: 88: {
		//;test_60f01x_sleep.C: 89: DelayMs(100);
		LDWI 	64H 			//03F7 	2A64
		LCALL 	3E0H 			//03F8 	33E0
		LDWI 	AH 			//03F9 	2A0A
		ORG		03FAH
		INCR	47H,1 			//03FA 	09C7
		SUBWR 	47H,0 			//03FB 	0C47
		BTSS 	STATUS,0 		//03FC 	1C03
		LJUMP 	3F7H 			//03FD 	3BF7
		INCR	46H,1 			//03FE 	09C6
		LJUMP 	3F2H 			//03FF 	3BF2
			END
