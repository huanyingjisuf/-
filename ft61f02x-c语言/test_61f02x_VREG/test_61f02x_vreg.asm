//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_SAFlag		EQU		75H
		_VREGC		EQU		76H
//		DelayMs@Time		EQU		72H
//		DelayMs@b		EQU		74H
//		DelayMs@a		EQU		73H
//		DelayMs@Time		EQU		C00000H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7FDH 			//0000 	3FFD
		ORG		07AAH
		STR 	70H 			//07AA 	01F0

		//;test_61f02x_VREG.C: 64: unsigned char a;
		//;test_61f02x_VREG.C: 65: for(a=0;a<Time;a++)
		CLRR 	71H 			//07AB 	0171
		LDR 	70H,0 			//07AC 	0870
		SUBWR 	71H,0 			//07AD 	0C71
		BTSC 	STATUS,0 		//07AE 	1403
		RET		 					//07AF 	0004

		//;test_61f02x_VREG.C: 66: {
		//;test_61f02x_VREG.C: 67: __nop();
		NOP		 					//07B0 	0000
		INCR	71H,1 			//07B1 	09F1
		ORG		07B2H
		LJUMP 	7ACH 			//07B2 	3FAC

		//;test_61f02x_VREG.C: 97: VREG_OE = 0;
		BCR 	1BH,6 			//07B3 	131B

		//;test_61f02x_VREG.C: 98: VCON1 = 0B00111111;
		LDWI 	3FH 			//07B4 	2A3F
		BSR 	STATUS,6 		//07B5 	1B03
		STR 	8H 			//07B6 	0188

		//;test_61f02x_VREG.C: 102: VCON2 = 0B00001111;
		LDWI 	FH 			//07B7 	2A0F
		STR 	9H 			//07B8 	0189

		//;test_61f02x_VREG.C: 106: VREG_OE = 1;
		BCR 	STATUS,6 		//07B9 	1303
		ORG		07BAH
		BSR 	1BH,6 			//07BA 	1B1B
		RET		 					//07BB 	0004
		STR 	72H 			//07BC 	01F2

		//;test_61f02x_VREG.C: 78: unsigned char a,b;
		//;test_61f02x_VREG.C: 79: for(a=0;a<Time;a++)
		CLRR 	73H 			//07BD 	0173
		LDR 	72H,0 			//07BE 	0872
		SUBWR 	73H,0 			//07BF 	0C73
		BTSC 	STATUS,0 		//07C0 	1403
		RET		 					//07C1 	0004
		ORG		07C2H

		//;test_61f02x_VREG.C: 80: {
		//;test_61f02x_VREG.C: 81: for(b=0;b<5;b++)
		CLRR 	74H 			//07C2 	0174

		//;test_61f02x_VREG.C: 82: {
		//;test_61f02x_VREG.C: 83: DelayUs(197);
		LDWI 	C5H 			//07C3 	2AC5
		LCALL 	7AAH 			//07C4 	37AA
		LDWI 	5H 			//07C5 	2A05
		INCR	74H,1 			//07C6 	09F4
		SUBWR 	74H,0 			//07C7 	0C74
		BTSS 	STATUS,0 		//07C8 	1C03
		LJUMP 	7C3H 			//07C9 	3FC3
		ORG		07CAH
		INCR	73H,1 			//07CA 	09F3
		LJUMP 	7BEH 			//07CB 	3FBE

		//;test_61f02x_VREG.C: 36: OSCCON = 0B01110001;
		LDWI 	71H 			//07CC 	2A71
		BSR 	STATUS,5 		//07CD 	1A83
		STR 	FH 			//07CE 	018F

		//;test_61f02x_VREG.C: 37: INTCON = 0;
		CLRR 	INTCON 			//07CF 	010B

		//;test_61f02x_VREG.C: 38: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07D0 	1283
		CLRR 	5H 			//07D1 	0105
		ORG		07D2H

		//;test_61f02x_VREG.C: 39: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07D2 	1A83
		CLRR 	5H 			//07D3 	0105

		//;test_61f02x_VREG.C: 41: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07D4 	1283
		CLRR 	7H 			//07D5 	0107

		//;test_61f02x_VREG.C: 42: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07D6 	1A83
		CLRR 	7H 			//07D7 	0107

		//;test_61f02x_VREG.C: 44: WPUA = 0B00000000;
		CLRR 	15H 			//07D8 	0115

		//;test_61f02x_VREG.C: 46: WPUC = 0B00000000;
		CLRR 	8H 			//07D9 	0108
		ORG		07DAH

		//;test_61f02x_VREG.C: 48: OPTION = 0B00001000;
		LDWI 	8H 			//07DA 	2A08
		STR 	1H 			//07DB 	0181

		//;test_61f02x_VREG.C: 49: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07DC 	1283
		CLRR 	1BH 			//07DD 	011B

		//;test_61f02x_VREG.C: 54: CMCON0 = 0B00000111;
		LDWI 	7H 			//07DE 	2A07
		STR 	19H 			//07DF 	0199
		RET		 					//07E0 	0004

		//;test_61f02x_VREG.C: 116: POWER_INITIAL();
		LCALL 	7CCH 			//07E1 	37CC
		ORG		07E2H

		//;test_61f02x_VREG.C: 117: VREG_INITIAL();
		LCALL 	7B3H 			//07E2 	37B3

		//;test_61f02x_VREG.C: 118: SAFlag = 1;
		BSR 	75H,0 			//07E3 	1875

		//;test_61f02x_VREG.C: 120: {
		//;test_61f02x_VREG.C: 121: if(SAFlag == 1)
		BTSS 	75H,0 			//07E4 	1C75
		LJUMP 	7EEH 			//07E5 	3FEE

		//;test_61f02x_VREG.C: 122: {
		//;test_61f02x_VREG.C: 123: VREGC++;
		INCR	76H,1 			//07E6 	09F6

		//;test_61f02x_VREG.C: 124: VCON1 &= 0B11100000;
		//;test_61f02x_VREG.C: 125: VCON1 |= VREGC;
		LCALL 	7F6H 			//07E7 	37F6

		//;test_61f02x_VREG.C: 126: if(VREGC >= 31)
		LDWI 	1FH 			//07E8 	2A1F
		SUBWR 	76H,0 			//07E9 	0C76
		ORG		07EAH
		BTSS 	STATUS,0 		//07EA 	1C03
		LJUMP 	7F3H 			//07EB 	3FF3

		//;test_61f02x_VREG.C: 127: {
		//;test_61f02x_VREG.C: 128: SAFlag = 0;
		BCR 	75H,0 			//07EC 	1075
		LJUMP 	7F3H 			//07ED 	3FF3

		//;test_61f02x_VREG.C: 131: else
		//;test_61f02x_VREG.C: 132: {
		//;test_61f02x_VREG.C: 133: VREGC--;
		DECR 	76H,1 			//07EE 	0DF6

		//;test_61f02x_VREG.C: 134: VCON1 &= 0B11100000;
		//;test_61f02x_VREG.C: 135: VCON1 |= VREGC;
		LCALL 	7F6H 			//07EF 	37F6

		//;test_61f02x_VREG.C: 136: if(VREGC == 0)
		LDR 	76H,0 			//07F0 	0876
		BTSC 	STATUS,2 		//07F1 	1503
		ORG		07F2H

		//;test_61f02x_VREG.C: 137: {
		//;test_61f02x_VREG.C: 138: SAFlag = 1;
		BSR 	75H,0 			//07F2 	1875

		//;test_61f02x_VREG.C: 139: }
		//;test_61f02x_VREG.C: 140: }
		//;test_61f02x_VREG.C: 141: DelayMs(1);
		LDWI 	1H 			//07F3 	2A01
		LCALL 	7BCH 			//07F4 	37BC
		LJUMP 	7E4H 			//07F5 	3FE4
		LDWI 	E0H 			//07F6 	2AE0
		BCR 	STATUS,5 		//07F7 	1283
		BSR 	STATUS,6 		//07F8 	1B03
		ANDWR 	8H,1 			//07F9 	0288
		ORG		07FAH
		LDR 	76H,0 			//07FA 	0876
		IORWR 	8H,1 			//07FB 	0388
		RET		 					//07FC 	0004
		CLRR 	76H 			//07FD 	0176
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7E1H 			//07FF 	3FE1
			END
