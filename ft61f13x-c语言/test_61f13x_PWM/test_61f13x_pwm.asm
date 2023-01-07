//Deviec:FT61F13X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FDH 			//0001 	3FFD
		ORG		07C2H

		//;test_61f13x_PWM.C: 122: POWER_INITIAL();
		BCR 	PCLATH,3 		//07C2 	118A
		LCALL 	7C9H 			//07C3 	37C9
		BCR 	PCLATH,3 		//07C4 	118A

		//;test_61f13x_PWM.C: 123: PWM_INITIAL();
		BCR 	PCLATH,3 		//07C5 	118A
		LCALL 	7D2H 			//07C6 	37D2
		BCR 	PCLATH,3 		//07C7 	118A

		//;test_61f13x_PWM.C: 124: while(1)
		//;test_61f13x_PWM.C: 125: {
		LJUMP 	7C8H 			//07C8 	3FC8

		//;test_61f13x_PWM.C: 37: OSCCON = 0B01110001;
		LDWI 	71H 			//07C9 	2A71
		ORG		07CAH
		BSR 	STATUS,5 		//07CA 	1A83
		STR 	FH 			//07CB 	018F

		//;test_61f13x_PWM.C: 40: TRISA=0;
		CLRR 	5H 			//07CC 	0105

		//;test_61f13x_PWM.C: 41: TRISB=0;
		CLRR 	6H 			//07CD 	0106

		//;test_61f13x_PWM.C: 42: PORTA=0;
		BCR 	STATUS,5 		//07CE 	1283
		CLRR 	5H 			//07CF 	0105

		//;test_61f13x_PWM.C: 43: PORTB=0;
		CLRR 	6H 			//07D0 	0106
		RET		 					//07D1 	0004
		ORG		07D2H

		//;test_61f13x_PWM.C: 55: T2CON0=0;
		CLRR 	12H 			//07D2 	0112

		//;test_61f13x_PWM.C: 60: T2CON1=0X02;
		LDWI 	2H 			//07D3 	2A02
		BSR 	STATUS,5 		//07D4 	1A83
		STR 	1EH 			//07D5 	019E

		//;test_61f13x_PWM.C: 62: PR2H=0;
		CLRR 	12H 			//07D6 	0112

		//;test_61f13x_PWM.C: 63: PR2L=31;
		LDWI 	1FH 			//07D7 	2A1F
		STR 	11H 			//07D8 	0191

		//;test_61f13x_PWM.C: 65: P1OE2=0B11100110;
		LDWI 	E6H 			//07D9 	2AE6
		ORG		07DAH
		BCR 	STATUS,5 		//07DA 	1283
		BSR 	STATUS,6 		//07DB 	1B03
		STR 	1BH 			//07DC 	019B

		//;test_61f13x_PWM.C: 71: TMR2H=0;
		BCR 	STATUS,6 		//07DD 	1303
		CLRR 	13H 			//07DE 	0113

		//;test_61f13x_PWM.C: 72: TMR2L=0;
		CLRR 	11H 			//07DF 	0111

		//;test_61f13x_PWM.C: 74: P1OE=0B11111111;
		LDWI 	FFH 			//07E0 	2AFF
		BSR 	STATUS,5 		//07E1 	1A83
		ORG		07E2H
		STR 	10H 			//07E2 	0190

		//;test_61f13x_PWM.C: 83: P1CON=0B00000001;
		LDWI 	1H 			//07E3 	2A01
		BCR 	STATUS,5 		//07E4 	1283
		STR 	16H 			//07E5 	0196

		//;test_61f13x_PWM.C: 85: P1POL=0B00000000;
		BSR 	STATUS,5 		//07E6 	1A83
		CLRR 	19H 			//07E7 	0119

		//;test_61f13x_PWM.C: 94: P1POL2=0B11100110;
		LDWI 	E6H 			//07E8 	2AE6
		BCR 	STATUS,5 		//07E9 	1283
		ORG		07EAH
		BSR 	STATUS,6 		//07EA 	1B03
		STR 	9H 			//07EB 	0189

		//;test_61f13x_PWM.C: 100: P1ADTH=0;
		BCR 	STATUS,6 		//07EC 	1303
		CLRR 	14H 			//07ED 	0114

		//;test_61f13x_PWM.C: 101: P1ADTL =3;
		LDWI 	3H 			//07EE 	2A03
		STR 	EH 			//07EF 	018E

		//;test_61f13x_PWM.C: 103: P1BDTH=0;
		CLRR 	15H 			//07F0 	0115

		//;test_61f13x_PWM.C: 104: P1BDTL=10;
		LDWI 	AH 			//07F1 	2A0A
		ORG		07F2H
		STR 	FH 			//07F2 	018F

		//;test_61f13x_PWM.C: 106: P1CDTH=0;
		CLRR 	1AH 			//07F3 	011A

		//;test_61f13x_PWM.C: 107: P1CDTL=26;
		LDWI 	1AH 			//07F4 	2A1A
		STR 	10H 			//07F5 	0190

		//;test_61f13x_PWM.C: 109: P1DDTH=0;
		CLRR 	9H 			//07F6 	0109

		//;test_61f13x_PWM.C: 110: P1DDTL =29;
		LDWI 	1DH 			//07F7 	2A1D
		STR 	8H 			//07F8 	0188

		//;test_61f13x_PWM.C: 112: T2CON0=T2CON0|0x04;
		LDR 	12H,0 			//07F9 	0812
		ORG		07FAH
		IORWI 	4H 			//07FA 	2504
		STR 	12H 			//07FB 	0192
		RET		 					//07FC 	0004
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7C2H 			//07FF 	3FC2
			END
