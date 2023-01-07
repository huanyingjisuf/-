//Deviec:FT61F02X
//-----------------------Variable---------------------------------
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7FEH 			//0000 	3FFE
		ORG		07D2H

		//;test_61f02x_comp.C: 63: CMCON0 = 0B00000010;
		LDWI 	2H 			//07D2 	2A02
		STR 	19H 			//07D3 	0199

		//;test_61f02x_comp.C: 82: CMCON1 = 0B00000000;
		CLRR 	1AH 			//07D4 	011A

		//;test_61f02x_comp.C: 83: VRCON = 0B10001111;
		LDWI 	8FH 			//07D5 	2A8F
		BSR 	STATUS,5 		//07D6 	1A83
		STR 	19H 			//07D7 	0199

		//;test_61f02x_comp.C: 89: ANSEL = 0B00110011;
		LDWI 	33H 			//07D8 	2A33
		STR 	11H 			//07D9 	0191
		ORG		07DAH
		RET		 					//07DA 	0004

		//;test_61f02x_comp.C: 99: POWER_INITIAL();
		LCALL 	7E8H 			//07DB 	37E8

		//;test_61f02x_comp.C: 100: COMP_INITIAL();
		LCALL 	7D2H 			//07DC 	37D2

		//;test_61f02x_comp.C: 103: {
		//;test_61f02x_comp.C: 104: PA3 = C2OUT;
		BCR 	STATUS,5 		//07DD 	1283
		BTSS 	19H,7 			//07DE 	1F99
		LJUMP 	7E4H 			//07DF 	3FE4
		BCR 	STATUS,5 		//07E0 	1283
		BCR 	STATUS,6 		//07E1 	1303
		ORG		07E2H
		BSR 	5H,3 			//07E2 	1985
		LJUMP 	7DDH 			//07E3 	3FDD
		BCR 	STATUS,5 		//07E4 	1283
		BCR 	STATUS,6 		//07E5 	1303
		BCR 	5H,3 			//07E6 	1185
		LJUMP 	7DDH 			//07E7 	3FDD

		//;test_61f02x_comp.C: 36: OSCCON = 0B01110001;
		LDWI 	71H 			//07E8 	2A71
		BSR 	STATUS,5 		//07E9 	1A83
		ORG		07EAH
		STR 	FH 			//07EA 	018F

		//;test_61f02x_comp.C: 37: INTCON = 0;
		CLRR 	INTCON 			//07EB 	010B

		//;test_61f02x_comp.C: 38: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07EC 	1283
		CLRR 	5H 			//07ED 	0105

		//;test_61f02x_comp.C: 39: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07EE 	1A83
		CLRR 	5H 			//07EF 	0105

		//;test_61f02x_comp.C: 41: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07F0 	1283
		CLRR 	7H 			//07F1 	0107
		ORG		07F2H

		//;test_61f02x_comp.C: 42: TRISC = 0B00000010;
		LDWI 	2H 			//07F2 	2A02
		BSR 	STATUS,5 		//07F3 	1A83
		STR 	7H 			//07F4 	0187

		//;test_61f02x_comp.C: 45: WPUA = 0B00000000;
		CLRR 	15H 			//07F5 	0115

		//;test_61f02x_comp.C: 46: WPUC = 0B00000000;
		CLRR 	8H 			//07F6 	0108

		//;test_61f02x_comp.C: 48: OPTION = 0B00001000;
		LDWI 	8H 			//07F7 	2A08
		STR 	1H 			//07F8 	0181

		//;test_61f02x_comp.C: 49: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07F9 	1283
		ORG		07FAH
		CLRR 	1BH 			//07FA 	011B

		//;test_61f02x_comp.C: 53: CMCON0 = 0B00000111;
		LDWI 	7H 			//07FB 	2A07
		STR 	19H 			//07FC 	0199
		RET		 					//07FD 	0004
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7DBH 			//07FF 	3FDB
			END
