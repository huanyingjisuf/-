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
		LJUMP 	49H 			//000A 	3849
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	38H 			//000F 	3838

		//;test_61f13x_Timer2.C: 74: T2CON0 = 0B00000001;
		LDWI 	1H 			//0010 	2A01
		BCR 	STATUS,5 		//0011 	1283
		STR 	12H 			//0012 	0192

		//;test_61f13x_Timer2.C: 80: T2CON1 = 0B00000000;
		BSR 	STATUS,5 		//0013 	1A83
		ORG		0014H
		CLRR 	1EH 			//0014 	011E

		//;test_61f13x_Timer2.C: 82: TMR2H = 0;
		BCR 	STATUS,5 		//0015 	1283
		CLRR 	13H 			//0016 	0113

		//;test_61f13x_Timer2.C: 83: TMR2L = 0;
		CLRR 	11H 			//0017 	0111

		//;test_61f13x_Timer2.C: 85: PR2H = 0;
		BSR 	STATUS,5 		//0018 	1A83
		CLRR 	12H 			//0019 	0112

		//;test_61f13x_Timer2.C: 86: PR2L = 199;
		LDWI 	C7H 			//001A 	2AC7
		STR 	11H 			//001B 	0191
		ORG		001CH

		//;test_61f13x_Timer2.C: 88: TMR2IF = 0;
		BCR 	STATUS,5 		//001C 	1283
		BCR 	CH,1 			//001D 	108C

		//;test_61f13x_Timer2.C: 89: TMR2IE = 1;
		BSR 	STATUS,5 		//001E 	1A83
		BSR 	CH,1 			//001F 	188C

		//;test_61f13x_Timer2.C: 90: TMR2ON = 1;
		BCR 	STATUS,5 		//0020 	1283
		BSR 	12H,2 			//0021 	1912

		//;test_61f13x_Timer2.C: 91: PEIE = 1;
		BSR 	INTCON,6 		//0022 	1B0B

		//;test_61f13x_Timer2.C: 92: GIE = 1;
		BSR 	INTCON,7 		//0023 	1B8B
		ORG		0024H
		RET		 					//0024 	0004

		//;test_61f13x_Timer2.C: 52: OSCCON = 0B01110001;
		LDWI 	71H 			//0025 	2A71
		BSR 	STATUS,5 		//0026 	1A83
		STR 	FH 			//0027 	018F

		//;test_61f13x_Timer2.C: 53: OPTION = 0B00001000;
		LDWI 	8H 			//0028 	2A08
		STR 	1H 			//0029 	0181

		//;test_61f13x_Timer2.C: 54: INTCON = 0;
		CLRR 	INTCON 			//002A 	010B

		//;test_61f13x_Timer2.C: 55: PORTA = 0B01000000;
		LDWI 	40H 			//002B 	2A40
		ORG		002CH
		BCR 	STATUS,5 		//002C 	1283
		STR 	5H 			//002D 	0185

		//;test_61f13x_Timer2.C: 56: TRISA = 0B00000100;
		LDWI 	4H 			//002E 	2A04
		BSR 	STATUS,5 		//002F 	1A83
		STR 	5H 			//0030 	0185

		//;test_61f13x_Timer2.C: 58: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0031 	1283
		CLRR 	7H 			//0032 	0107

		//;test_61f13x_Timer2.C: 59: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0033 	1A83
		ORG		0034H
		CLRR 	7H 			//0034 	0107

		//;test_61f13x_Timer2.C: 61: WPUA = 0B00000100;
		STR 	15H 			//0035 	0195

		//;test_61f13x_Timer2.C: 63: WPUC = 0B00000000;
		CLRR 	13H 			//0036 	0113
		RET		 					//0037 	0004

		//;test_61f13x_Timer2.C: 102: POWER_INITIAL();
		BCR 	PCLATH,3 		//0038 	118A
		LCALL 	25H 			//0039 	3025
		BCR 	PCLATH,3 		//003A 	118A

		//;test_61f13x_Timer2.C: 103: TIMER2_INITIAL();
		BCR 	PCLATH,3 		//003B 	118A
		ORG		003CH
		LCALL 	10H 			//003C 	3010
		BCR 	PCLATH,3 		//003D 	118A
		LJUMP 	41H 			//003E 	3841

		//;test_61f13x_Timer2.C: 108: {
		//;test_61f13x_Timer2.C: 109: TMR2IE = 1;
		BSR 	STATUS,5 		//003F 	1A83
		BSR 	CH,1 			//0040 	188C

		//;test_61f13x_Timer2.C: 110: }
		//;test_61f13x_Timer2.C: 106: {
		//;test_61f13x_Timer2.C: 107: if(PA2)
		BCR 	STATUS,5 		//0041 	1283
		BTSC 	5H,2 			//0042 	1505
		LJUMP 	3FH 			//0043 	383F
		ORG		0044H

		//;test_61f13x_Timer2.C: 111: else
		//;test_61f13x_Timer2.C: 112: {
		//;test_61f13x_Timer2.C: 113: TMR2IE = 0;
		BSR 	STATUS,5 		//0044 	1A83
		BCR 	CH,1 			//0045 	108C

		//;test_61f13x_Timer2.C: 114: PA4 = 1;
		BCR 	STATUS,5 		//0046 	1283
		BSR 	5H,4 			//0047 	1A05
		LJUMP 	41H 			//0048 	3841

		//;test_61f13x_Timer2.C: 38: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//0049 	1A83
		BCR 	STATUS,6 		//004A 	1303
		BTSS 	CH,1 			//004B 	1C8C
		ORG		004CH
		LJUMP 	53H 			//004C 	3853
		BCR 	STATUS,5 		//004D 	1283
		BTSS 	CH,1 			//004E 	1C8C
		LJUMP 	53H 			//004F 	3853

		//;test_61f13x_Timer2.C: 39: {
		//;test_61f13x_Timer2.C: 40: TMR2IF = 0;
		BCR 	CH,1 			//0050 	108C

		//;test_61f13x_Timer2.C: 41: PA4 = ~PA4;
		LDWI 	10H 			//0051 	2A10
		XORWR 	5H,1 			//0052 	0485
		LDR 	71H,0 			//0053 	0871
		ORG		0054H
		STR 	PCLATH 			//0054 	018A
		SWAPR 	70H,0 			//0055 	0770
		STR 	STATUS 			//0056 	0183
		SWAPR 	7EH,1 			//0057 	07FE
		SWAPR 	7EH,0 			//0058 	077E
		RETI		 			//0059 	0009
			END
