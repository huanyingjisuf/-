//Deviec:FT61F13X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FDH 			//0001 	3FFD
		ORG		07D2H

		//;test_61f13x_LVD.C: 59: PCON = 0B01000011;
		LDWI 	43H 			//07D2 	2A43
		STR 	EH 			//07D3 	018E

		//;test_61f13x_LVD.C: 66: LVDCON = 0B00001010;
		LDWI 	AH 			//07D4 	2A0A
		BCR 	STATUS,5 		//07D5 	1283
		BSR 	STATUS,6 		//07D6 	1B03
		STR 	10H 			//07D7 	0190
		RET		 					//07D8 	0004

		//;test_61f13x_LVD.C: 38: OSCCON = 0B01110001;
		LDWI 	71H 			//07D9 	2A71
		ORG		07DAH
		BSR 	STATUS,5 		//07DA 	1A83
		STR 	FH 			//07DB 	018F

		//;test_61f13x_LVD.C: 39: OPTION = 0B00001000;
		LDWI 	8H 			//07DC 	2A08
		STR 	1H 			//07DD 	0181

		//;test_61f13x_LVD.C: 40: INTCON = 0;
		CLRR 	INTCON 			//07DE 	010B

		//;test_61f13x_LVD.C: 41: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07DF 	1283
		CLRR 	5H 			//07E0 	0105

		//;test_61f13x_LVD.C: 42: TRISA = 0B00000010;
		LDWI 	2H 			//07E1 	2A02
		ORG		07E2H
		BSR 	STATUS,5 		//07E2 	1A83
		STR 	5H 			//07E3 	0185

		//;test_61f13x_LVD.C: 44: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07E4 	1283
		CLRR 	7H 			//07E5 	0107

		//;test_61f13x_LVD.C: 45: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07E6 	1A83
		CLRR 	7H 			//07E7 	0107

		//;test_61f13x_LVD.C: 47: WPUA = 0B00000010;
		STR 	15H 			//07E8 	0195

		//;test_61f13x_LVD.C: 49: WPUC = 0B00000000;
		CLRR 	13H 			//07E9 	0113
		ORG		07EAH
		RET		 					//07EA 	0004

		//;test_61f13x_LVD.C: 79: POWER_INITIAL();
		BCR 	PCLATH,3 		//07EB 	118A
		LCALL 	7D9H 			//07EC 	37D9
		BCR 	PCLATH,3 		//07ED 	118A

		//;test_61f13x_LVD.C: 80: LVD_INITIAL();
		BCR 	PCLATH,3 		//07EE 	118A
		LCALL 	7D2H 			//07EF 	37D2
		BCR 	PCLATH,3 		//07F0 	118A

		//;test_61f13x_LVD.C: 81: PCON|= 0B00001000;
		BSR 	STATUS,5 		//07F1 	1A83
		ORG		07F2H
		BCR 	STATUS,6 		//07F2 	1303
		BSR 	EH,3 			//07F3 	198E
		LJUMP 	7F7H 			//07F4 	3FF7

		//;test_61f13x_LVD.C: 85: {
		//;test_61f13x_LVD.C: 86: PA4 = 1;
		BCR 	STATUS,5 		//07F5 	1283
		BSR 	5H,4 			//07F6 	1A05

		//;test_61f13x_LVD.C: 87: }
		//;test_61f13x_LVD.C: 83: {
		//;test_61f13x_LVD.C: 84: if(PCON&0x04)
		BSR 	STATUS,5 		//07F7 	1A83
		BTSC 	EH,2 			//07F8 	150E
		LJUMP 	7F5H 			//07F9 	3FF5
		ORG		07FAH

		//;test_61f13x_LVD.C: 88: else
		//;test_61f13x_LVD.C: 89: {
		//;test_61f13x_LVD.C: 90: PA4 = 0;
		BCR 	STATUS,5 		//07FA 	1283
		BCR 	5H,4 			//07FB 	1205
		LJUMP 	7F7H 			//07FC 	3FF7
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	7EBH 			//07FF 	3FEB
			END
