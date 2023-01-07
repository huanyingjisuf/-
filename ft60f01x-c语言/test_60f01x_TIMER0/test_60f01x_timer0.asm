//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	40H 			//0006 	01C0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	41H 			//0008 	01C1
		LJUMP 	19H 			//0009 	3819
		LJUMP 	32H 			//000A 	3832

		//;test_60f01x_timer0.C: 44: OSCCON = 0B01110000;
		LDWI 	70H 			//000B 	2A70
		ORG		000CH
		BSR 	STATUS,5 		//000C 	1A83
		STR 	FH 			//000D 	018F

		//;test_60f01x_timer0.C: 45: INTCON = 0;
		CLRR 	INTCON 			//000E 	010B

		//;test_60f01x_timer0.C: 46: OPTION = 0B00001000;
		LDWI 	8H 			//000F 	2A08
		STR 	1H 			//0010 	0181

		//;test_60f01x_timer0.C: 48: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0011 	1283
		CLRR 	5H 			//0012 	0105

		//;test_60f01x_timer0.C: 49: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0013 	1A83
		ORG		0014H
		CLRR 	5H 			//0014 	0105

		//;test_60f01x_timer0.C: 51: WPUA = 0B00000000;
		CLRR 	15H 			//0015 	0115

		//;test_60f01x_timer0.C: 52: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0016 	1283
		CLRR 	1BH 			//0017 	011B
		RET		 					//0018 	0004

		//;test_60f01x_timer0.C: 30: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//0019 	168B
		BTSS 	INTCON,2 		//001A 	1D0B
		LJUMP 	20H 			//001B 	3820
		ORG		001CH
		LDWI 	10H 			//001C 	2A10

		//;test_60f01x_timer0.C: 31: {
		//;test_60f01x_timer0.C: 32: T0IF = 0;
		BCR 	INTCON,2 		//001D 	110B

		//;test_60f01x_timer0.C: 33: PA4 = ~PA4;
		BCR 	STATUS,5 		//001E 	1283
		XORWR 	5H,1 			//001F 	0485
		LDR 	41H,0 			//0020 	0841
		STR 	PCLATH 			//0021 	018A
		SWAPR 	40H,0 			//0022 	0740
		STR 	STATUS 			//0023 	0183
		ORG		0024H
		SWAPR 	7EH,1 			//0024 	07FE
		SWAPR 	7EH,0 			//0025 	077E
		RETI		 			//0026 	0009

		//;test_60f01x_timer0.C: 81: POWER_INITIAL();
		LCALL 	BH 			//0027 	300B

		//;test_60f01x_timer0.C: 82: TIMER0_INITIAL();
		LCALL 	2DH 			//0028 	302D

		//;test_60f01x_timer0.C: 83: GIE = 1;
		BSR 	INTCON,7 		//0029 	1B8B

		//;test_60f01x_timer0.C: 84: T0IE = 1;
		BSR 	INTCON,5 		//002A 	1A8B

		//;test_60f01x_timer0.C: 86: {
		//;test_60f01x_timer0.C: 87: _nop();
		NOP		 					//002B 	0000
		ORG		002CH
		LJUMP 	2BH 			//002C 	382B

		//;test_60f01x_timer0.C: 65: OPTION = 0B00000111;
		LDWI 	7H 			//002D 	2A07
		BSR 	STATUS,5 		//002E 	1A83
		STR 	1H 			//002F 	0181

		//;test_60f01x_timer0.C: 71: T0IF = 0;
		BCR 	INTCON,2 		//0030 	110B
		RET		 					//0031 	0004
		CLRR 	STATUS 			//0032 	0103
		LJUMP 	27H 			//0033 	3827
			END
