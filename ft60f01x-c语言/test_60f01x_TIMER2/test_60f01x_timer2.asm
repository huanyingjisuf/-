//Deviec:FT60F01X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		LJUMP 	0DH 			//0009 	380D
		LJUMP 	0BH 			//000A 	380B
		CLRR 	STATUS 			//000B 	0103
		ORG		000CH
		LJUMP 	3BH 			//000C 	383B

		//;test_60f01x_timer2.C: 33: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//000D 	1A83
		BTSS 	CH,1 			//000E 	1C8C
		LJUMP 	16H 			//000F 	3816
		BCR 	STATUS,5 		//0010 	1283
		BTSS 	CH,1 			//0011 	1C8C
		LJUMP 	16H 			//0012 	3816

		//;test_60f01x_timer2.C: 34: {
		//;test_60f01x_timer2.C: 35: TMR2IF = 0;
		BCR 	CH,1 			//0013 	108C
		ORG		0014H

		//;test_60f01x_timer2.C: 36: PA4 = ~PA4;
		LDWI 	10H 			//0014 	2A10
		XORWR 	5H,1 			//0015 	0485
		LDR 	71H,0 			//0016 	0871
		STR 	PCLATH 			//0017 	018A
		SWAPR 	70H,0 			//0018 	0770
		STR 	STATUS 			//0019 	0183
		SWAPR 	7EH,1 			//001A 	07FE
		SWAPR 	7EH,0 			//001B 	077E
		ORG		001CH
		RETI		 			//001C 	0009

		//;test_60f01x_timer2.C: 70: T2CON = 0B00000001;
		LDWI 	1H 			//001D 	2A01
		STR 	12H 			//001E 	0192

		//;test_60f01x_timer2.C: 75: TMR2 = 0;
		CLRR 	11H 			//001F 	0111

		//;test_60f01x_timer2.C: 76: PR2 = 200;
		LDWI 	C8H 			//0020 	2AC8
		BSR 	STATUS,5 		//0021 	1A83
		STR 	12H 			//0022 	0192

		//;test_60f01x_timer2.C: 77: TMR2IF = 0;
		BCR 	STATUS,5 		//0023 	1283
		ORG		0024H
		BCR 	CH,1 			//0024 	108C

		//;test_60f01x_timer2.C: 78: TMR2IE = 1;
		BSR 	STATUS,5 		//0025 	1A83
		BSR 	CH,1 			//0026 	188C

		//;test_60f01x_timer2.C: 79: TMR2ON = 1;
		BCR 	STATUS,5 		//0027 	1283
		BSR 	12H,2 			//0028 	1912

		//;test_60f01x_timer2.C: 80: PEIE=1;
		BSR 	INTCON,6 		//0029 	1B0B

		//;test_60f01x_timer2.C: 81: GIE = 1;
		BSR 	INTCON,7 		//002A 	1B8B
		RET		 					//002B 	0004
		ORG		002CH

		//;test_60f01x_timer2.C: 47: OSCCON = 0B01110000;
		LDWI 	70H 			//002C 	2A70
		BSR 	STATUS,5 		//002D 	1A83
		STR 	FH 			//002E 	018F

		//;test_60f01x_timer2.C: 49: INTCON = 0;
		CLRR 	INTCON 			//002F 	010B

		//;test_60f01x_timer2.C: 50: OPTION = 0B00001000;
		LDWI 	8H 			//0030 	2A08
		STR 	1H 			//0031 	0181

		//;test_60f01x_timer2.C: 52: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0032 	1283
		CLRR 	5H 			//0033 	0105
		ORG		0034H

		//;test_60f01x_timer2.C: 53: TRISA = 0B00000100;
		LDWI 	4H 			//0034 	2A04
		BSR 	STATUS,5 		//0035 	1A83
		STR 	5H 			//0036 	0185

		//;test_60f01x_timer2.C: 55: WPUA = 0B00000100;
		STR 	15H 			//0037 	0195

		//;test_60f01x_timer2.C: 57: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0038 	1283
		CLRR 	1BH 			//0039 	011B
		RET		 					//003A 	0004

		//;test_60f01x_timer2.C: 91: POWER_INITIAL();
		LCALL 	2CH 			//003B 	302C
		ORG		003CH

		//;test_60f01x_timer2.C: 92: TIMER2_INITIAL();
		LCALL 	1DH 			//003C 	301D
		LJUMP 	40H 			//003D 	3840

		//;test_60f01x_timer2.C: 97: {
		//;test_60f01x_timer2.C: 98: TMR2IE = 1;
		BSR 	STATUS,5 		//003E 	1A83
		BSR 	CH,1 			//003F 	188C

		//;test_60f01x_timer2.C: 99: }
		//;test_60f01x_timer2.C: 95: {
		//;test_60f01x_timer2.C: 96: if(PA2 == 1)
		BCR 	STATUS,5 		//0040 	1283
		BTSC 	5H,2 			//0041 	1505
		LJUMP 	3EH 			//0042 	383E

		//;test_60f01x_timer2.C: 100: else
		//;test_60f01x_timer2.C: 101: {
		//;test_60f01x_timer2.C: 102: TMR2IE = 0;
		BSR 	STATUS,5 		//0043 	1A83
		ORG		0044H
		BCR 	CH,1 			//0044 	108C

		//;test_60f01x_timer2.C: 103: PA4 = 1;
		BCR 	STATUS,5 		//0045 	1283
		BSR 	5H,4 			//0046 	1A05
		LJUMP 	40H 			//0047 	3840
			END
