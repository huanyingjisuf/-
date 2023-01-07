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
		LJUMP 	33H 			//000A 	3833
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	41H 			//000F 	3841

		//;test_61f13x_Timer1.C: 74: T1CON0 = 0B00010000;
		LDWI 	10H 			//0010 	2A10
		BCR 	STATUS,5 		//0011 	1283
		BSR 	STATUS,6 		//0012 	1B03
		STR 	1AH 			//0013 	019A
		ORG		0014H

		//;test_61f13x_Timer1.C: 80: T2CON0 = 0B00000011;
		LDWI 	3H 			//0014 	2A03
		BCR 	STATUS,6 		//0015 	1303
		STR 	12H 			//0016 	0192

		//;test_61f13x_Timer1.C: 82: TMR1L = 0;
		BSR 	STATUS,6 		//0017 	1B03
		CLRR 	18H 			//0018 	0118

		//;test_61f13x_Timer1.C: 83: TMR1H = 0;
		CLRR 	19H 			//0019 	0119

		//;test_61f13x_Timer1.C: 85: PR1L = 250;
		LDWI 	FAH 			//001A 	2AFA
		STR 	16H 			//001B 	0196
		ORG		001CH

		//;test_61f13x_Timer1.C: 86: PR1H = 0;
		CLRR 	17H 			//001C 	0117

		//;test_61f13x_Timer1.C: 88: TMR1IF = 0;
		BCR 	STATUS,6 		//001D 	1303
		BCR 	CH,3 			//001E 	118C

		//;test_61f13x_Timer1.C: 89: T1ON = 1;
		BSR 	STATUS,6 		//001F 	1B03
		BSR 	1AH,2 			//0020 	191A
		RET		 					//0021 	0004

		//;test_61f13x_Timer1.C: 52: OSCCON = 0B01110001;
		LDWI 	71H 			//0022 	2A71
		BSR 	STATUS,5 		//0023 	1A83
		ORG		0024H
		STR 	FH 			//0024 	018F

		//;test_61f13x_Timer1.C: 53: OPTION = 0B00001000;
		LDWI 	8H 			//0025 	2A08
		STR 	1H 			//0026 	0181

		//;test_61f13x_Timer1.C: 54: INTCON = 0;
		CLRR 	INTCON 			//0027 	010B

		//;test_61f13x_Timer1.C: 56: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0028 	1283
		CLRR 	5H 			//0029 	0105

		//;test_61f13x_Timer1.C: 57: TRISA = 0B00000000;
		BSR 	STATUS,5 		//002A 	1A83
		CLRR 	5H 			//002B 	0105
		ORG		002CH

		//;test_61f13x_Timer1.C: 59: PORTC = 0B00000000;
		BCR 	STATUS,5 		//002C 	1283
		CLRR 	7H 			//002D 	0107

		//;test_61f13x_Timer1.C: 60: TRISC = 0B00000000;
		BSR 	STATUS,5 		//002E 	1A83
		CLRR 	7H 			//002F 	0107

		//;test_61f13x_Timer1.C: 62: WPUA = 0B00000000;
		CLRR 	15H 			//0030 	0115

		//;test_61f13x_Timer1.C: 63: WPUC = 0B00000000;
		CLRR 	13H 			//0031 	0113
		RET		 					//0032 	0004

		//;test_61f13x_Timer1.C: 37: if(TMR1IF)
		BCR 	STATUS,5 		//0033 	1283
		ORG		0034H
		BCR 	STATUS,6 		//0034 	1303
		BTSS 	CH,3 			//0035 	1D8C
		LJUMP 	3AH 			//0036 	383A

		//;test_61f13x_Timer1.C: 38: {
		//;test_61f13x_Timer1.C: 39: TMR1IF = 0;
		BCR 	CH,3 			//0037 	118C

		//;test_61f13x_Timer1.C: 40: PA4 = ~PA4;
		LDWI 	10H 			//0038 	2A10
		XORWR 	5H,1 			//0039 	0485
		LDR 	71H,0 			//003A 	0871
		STR 	PCLATH 			//003B 	018A
		ORG		003CH
		SWAPR 	70H,0 			//003C 	0770
		STR 	STATUS 			//003D 	0183
		SWAPR 	7EH,1 			//003E 	07FE
		SWAPR 	7EH,0 			//003F 	077E
		RETI		 			//0040 	0009

		//;test_61f13x_Timer1.C: 99: POWER_INITIAL();
		BCR 	PCLATH,3 		//0041 	118A
		LCALL 	22H 			//0042 	3022
		BCR 	PCLATH,3 		//0043 	118A
		ORG		0044H

		//;test_61f13x_Timer1.C: 100: TIMER1_INITIAL();
		BCR 	PCLATH,3 		//0044 	118A
		LCALL 	10H 			//0045 	3010
		BCR 	PCLATH,3 		//0046 	118A

		//;test_61f13x_Timer1.C: 102: GIE = 1;
		BSR 	INTCON,7 		//0047 	1B8B

		//;test_61f13x_Timer1.C: 103: PEIE = 1;
		BSR 	INTCON,6 		//0048 	1B0B

		//;test_61f13x_Timer1.C: 104: TMR1IE = 1;
		BSR 	STATUS,5 		//0049 	1A83
		BCR 	STATUS,6 		//004A 	1303
		BSR 	CH,3 			//004B 	198C
		ORG		004CH

		//;test_61f13x_Timer1.C: 106: {
		//;test_61f13x_Timer1.C: 107: __nop();
		NOP		 					//004C 	0000
		LJUMP 	4CH 			//004D 	384C
			END
