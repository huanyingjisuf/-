//Deviec:FT61F13X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0BH 			//0001 	380B
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		BCR 	PCLATH,3 		//0009 	118A
		LJUMP 	21H 			//000A 	3821
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	30H 			//000F 	3830

		//;test_61f13x_Timer0.C: 56: OSCCON = 0B01110001;
		LDWI 	71H 			//0010 	2A71
		BSR 	STATUS,5 		//0011 	1A83
		STR 	FH 			//0012 	018F

		//;test_61f13x_Timer0.C: 57: OPTION = 0B00001000;
		LDWI 	8H 			//0013 	2A08
		ORG		0014H
		STR 	1H 			//0014 	0181

		//;test_61f13x_Timer0.C: 58: INTCON = 0;
		CLRR 	INTCON 			//0015 	010B

		//;test_61f13x_Timer0.C: 59: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0016 	1283
		CLRR 	5H 			//0017 	0105

		//;test_61f13x_Timer0.C: 60: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0018 	1A83
		CLRR 	5H 			//0019 	0105

		//;test_61f13x_Timer0.C: 62: PORTC = 0B00000000;
		BCR 	STATUS,5 		//001A 	1283
		CLRR 	7H 			//001B 	0107
		ORG		001CH

		//;test_61f13x_Timer0.C: 63: TRISC = 0B00000000;
		BSR 	STATUS,5 		//001C 	1A83
		CLRR 	7H 			//001D 	0107

		//;test_61f13x_Timer0.C: 65: WPUA = 0B00000000;
		CLRR 	15H 			//001E 	0115

		//;test_61f13x_Timer0.C: 66: WPUC = 0B00000000;
		CLRR 	13H 			//001F 	0113
		RET		 					//0020 	0004

		//;test_61f13x_Timer0.C: 41: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//0021 	168B
		BTSS 	INTCON,2 		//0022 	1D0B
		LJUMP 	29H 			//0023 	3829
		ORG		0024H

		//;test_61f13x_Timer0.C: 42: {
		//;test_61f13x_Timer0.C: 43: T0IF = 0;
		BCR 	INTCON,2 		//0024 	110B

		//;test_61f13x_Timer0.C: 44: PA4 = ~PA4;
		LDWI 	10H 			//0025 	2A10
		BCR 	STATUS,5 		//0026 	1283
		BCR 	STATUS,6 		//0027 	1303
		XORWR 	5H,1 			//0028 	0485
		LDR 	71H,0 			//0029 	0871
		STR 	PCLATH 			//002A 	018A
		SWAPR 	70H,0 			//002B 	0770
		ORG		002CH
		STR 	STATUS 			//002C 	0183
		SWAPR 	7EH,1 			//002D 	07FE
		SWAPR 	7EH,0 			//002E 	077E
		RETI		 			//002F 	0009

		//;test_61f13x_Timer0.C: 87: POWER_INITIAL();
		BCR 	PCLATH,3 		//0030 	118A
		LCALL 	10H 			//0031 	3010
		BCR 	PCLATH,3 		//0032 	118A

		//;test_61f13x_Timer0.C: 88: TIMER0_INITIAL();
		BCR 	PCLATH,3 		//0033 	118A
		ORG		0034H
		LCALL 	3AH 			//0034 	303A
		BCR 	PCLATH,3 		//0035 	118A

		//;test_61f13x_Timer0.C: 89: GIE = 1;
		BSR 	INTCON,7 		//0036 	1B8B

		//;test_61f13x_Timer0.C: 90: T0IE = 1;
		BSR 	INTCON,5 		//0037 	1A8B

		//;test_61f13x_Timer0.C: 92: {
		//;test_61f13x_Timer0.C: 93: __nop();
		NOP		 					//0038 	0000
		LJUMP 	38H 			//0039 	3838

		//;test_61f13x_Timer0.C: 75: OPTION = 0B00000111;
		LDWI 	7H 			//003A 	2A07
		STR 	1H 			//003B 	0181
		ORG		003CH

		//;test_61f13x_Timer0.C: 76: T0IF = 0;
		BCR 	INTCON,2 		//003C 	110B

		//;test_61f13x_Timer0.C: 77: TMR0 = 0;
		BCR 	STATUS,5 		//003D 	1283
		CLRR 	1H 			//003E 	0101
		RET		 					//003F 	0004
			END
