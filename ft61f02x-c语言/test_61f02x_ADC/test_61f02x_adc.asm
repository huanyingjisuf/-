//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_TestADC		EQU		20H
//		GET_ADC_DATA@AN_CH		EQU		77H
//		GET_ADC_DATA@ADC_DATA		EQU		78H
//		GET_ADC_DATA@tBuffer		EQU		75H
//		GET_ADC_DATA@ADCON0Buff		EQU		7AH
//		GET_ADC_DATA@AN_CH		EQU		C00000H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7FEH 			//0000 	3FFE
		ORG		0781H
		STR 	70H 			//0781 	01F0

		//;test_61f02x_ADC.C: 63: unsigned char a;
		//;test_61f02x_ADC.C: 64: for(a=0;a<Time;a++)
		CLRR 	71H 			//0782 	0171
		LDR 	70H,0 			//0783 	0870
		SUBWR 	71H,0 			//0784 	0C71
		BTSC 	STATUS,0 		//0785 	1403
		RET		 					//0786 	0004

		//;test_61f02x_ADC.C: 65: {
		//;test_61f02x_ADC.C: 66: __nop();
		NOP		 					//0787 	0000
		INCR	71H,1 			//0788 	09F1
		ORG		0789H
		LJUMP 	783H 			//0789 	3F83

		//;test_61f02x_ADC.C: 77: ADCON1 = 0B01100000;
		LDWI 	60H 			//078A 	2A60
		BSR 	STATUS,5 		//078B 	1A83
		STR 	1FH 			//078C 	019F

		//;test_61f02x_ADC.C: 81: ADCON0 = 0B10001001;
		LDWI 	89H 			//078D 	2A89
		BCR 	STATUS,5 		//078E 	1283
		STR 	1FH 			//078F 	019F

		//;test_61f02x_ADC.C: 91: ANSEL = 0B00000100;
		LDWI 	4H 			//0790 	2A04
		ORG		0791H
		BSR 	STATUS,5 		//0791 	1A83
		STR 	11H 			//0792 	0191
		RET		 					//0793 	0004

		//;test_61f02x_ADC.C: 134: TRISC4 =1;
		BSR 	7H,4 			//0794 	1A07

		//;test_61f02x_ADC.C: 136: PWM3CR0 = 0B00110010;
		LDWI 	32H 			//0795 	2A32
		BCR 	STATUS,5 		//0796 	1283
		BSR 	STATUS,6 		//0797 	1B03
		STR 	FH 			//0798 	018F
		ORG		0799H

		//;test_61f02x_ADC.C: 141: PWM3CR1 = 0B10000000;
		LDWI 	80H 			//0799 	2A80
		STR 	10H 			//079A 	0190

		//;test_61f02x_ADC.C: 148: TMR3H=0;
		CLRR 	DH 			//079B 	010D

		//;test_61f02x_ADC.C: 149: T3CKDIV = 30;
		LDWI 	1EH 			//079C 	2A1E
		STR 	11H 			//079D 	0191

		//;test_61f02x_ADC.C: 150: PR3L = 128;
		LDWI 	80H 			//079E 	2A80
		STR 	EH 			//079F 	018E
		RET		 					//07A0 	0004
		ORG		07A1H

		//;test_61f02x_ADC.C: 37: OSCCON = 0B01110001;
		LDWI 	71H 			//07A1 	2A71
		BSR 	STATUS,5 		//07A2 	1A83
		STR 	FH 			//07A3 	018F

		//;test_61f02x_ADC.C: 38: INTCON = 0;
		CLRR 	INTCON 			//07A4 	010B

		//;test_61f02x_ADC.C: 40: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07A5 	1283
		CLRR 	5H 			//07A6 	0105

		//;test_61f02x_ADC.C: 41: TRISA = 0B00000100;
		LDWI 	4H 			//07A7 	2A04
		BSR 	STATUS,5 		//07A8 	1A83
		ORG		07A9H
		STR 	5H 			//07A9 	0185

		//;test_61f02x_ADC.C: 43: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07AA 	1283
		CLRR 	7H 			//07AB 	0107

		//;test_61f02x_ADC.C: 44: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07AC 	1A83
		CLRR 	7H 			//07AD 	0107

		//;test_61f02x_ADC.C: 45: WPUA = 0;
		CLRR 	15H 			//07AE 	0115

		//;test_61f02x_ADC.C: 46: WPUC = 0;
		CLRR 	8H 			//07AF 	0108

		//;test_61f02x_ADC.C: 48: OPTION = 0B00001000;
		LDWI 	8H 			//07B0 	2A08
		ORG		07B1H
		STR 	1H 			//07B1 	0181

		//;test_61f02x_ADC.C: 49: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07B2 	1283
		CLRR 	1BH 			//07B3 	011B

		//;test_61f02x_ADC.C: 53: CMCON0 = 0B00000111;
		LDWI 	7H 			//07B4 	2A07
		STR 	19H 			//07B5 	0199
		RET		 					//07B6 	0004

		//;test_61f02x_ADC.C: 160: POWER_INITIAL();
		LCALL 	7A1H 			//07B7 	37A1

		//;test_61f02x_ADC.C: 161: ADC_INITIAL();
		LCALL 	78AH 			//07B8 	378A
		ORG		07B9H

		//;test_61f02x_ADC.C: 162: PWM_INITIAL();
		LCALL 	794H 			//07B9 	3794

		//;test_61f02x_ADC.C: 163: TMR3ON = 1;
		BSR 	10H,2 			//07BA 	1910

		//;test_61f02x_ADC.C: 164: TRISC4 = 0;
		BSR 	STATUS,5 		//07BB 	1A83
		BCR 	STATUS,6 		//07BC 	1303
		BCR 	7H,4 			//07BD 	1207

		//;test_61f02x_ADC.C: 165: while(1)
		//;test_61f02x_ADC.C: 166: {
		//;test_61f02x_ADC.C: 167: TestADC = GET_ADC_DATA(2);
		LDWI 	2H 			//07BE 	2A02
		LCALL 	7D5H 			//07BF 	37D5
		LDR 	73H,0 			//07C0 	0873
		ORG		07C1H
		BCR 	STATUS,5 		//07C1 	1283
		STR 	21H 			//07C2 	01A1
		LDR 	72H,0 			//07C3 	0872
		STR 	20H 			//07C4 	01A0

		//;test_61f02x_ADC.C: 168: PR3L = TestADC >> 2;
		LDR 	21H,0 			//07C5 	0821
		STR 	7CH 			//07C6 	01FC
		LDR 	20H,0 			//07C7 	0820
		STR 	7BH 			//07C8 	01FB
		ORG		07C9H
		BCR 	STATUS,0 		//07C9 	1003
		RRR	7CH,1 			//07CA 	06FC
		RRR	7BH,1 			//07CB 	06FB
		BCR 	STATUS,0 		//07CC 	1003
		RRR	7CH,1 			//07CD 	06FC
		RRR	7BH,1 			//07CE 	06FB
		LDR 	7BH,0 			//07CF 	087B
		BSR 	STATUS,6 		//07D0 	1B03
		ORG		07D1H
		STR 	EH 			//07D1 	018E

		//;test_61f02x_ADC.C: 170: __nop();
		NOP		 					//07D2 	0000

		//;test_61f02x_ADC.C: 171: __nop();
		NOP		 					//07D3 	0000
		LJUMP 	7BEH 			//07D4 	3FBE
		STR 	77H 			//07D5 	01F7

		//;test_61f02x_ADC.C: 104: unsigned int ADC_DATA=0;
		CLRR 	78H 			//07D6 	0178
		CLRR 	79H 			//07D7 	0179

		//;test_61f02x_ADC.C: 106: ADCON0Buff = ADCON0 & 0B11100011;
		BCR 	STATUS,5 		//07D8 	1283
		ORG		07D9H
		BCR 	STATUS,6 		//07D9 	1303
		LDR 	1FH,0 			//07DA 	081F
		STR 	7AH 			//07DB 	01FA
		LDWI 	E3H 			//07DC 	2AE3
		ANDWR 	7AH,1 			//07DD 	02FA

		//;test_61f02x_ADC.C: 108: AN_CH <<=2;
		BCR 	STATUS,0 		//07DE 	1003
		RLR 	77H,1 			//07DF 	05F7
		BCR 	STATUS,0 		//07E0 	1003
		ORG		07E1H
		RLR 	77H,1 			//07E1 	05F7

		//;test_61f02x_ADC.C: 109: ADCON0Buff |= AN_CH;
		LDR 	77H,0 			//07E2 	0877
		IORWR 	7AH,1 			//07E3 	03FA

		//;test_61f02x_ADC.C: 111: ADCON0 = ADCON0Buff;
		LDR 	7AH,0 			//07E4 	087A
		STR 	1FH 			//07E5 	019F

		//;test_61f02x_ADC.C: 112: DelayUs(20);
		LDWI 	14H 			//07E6 	2A14
		LCALL 	781H 			//07E7 	3781

		//;test_61f02x_ADC.C: 113: GO_DONE = 1;
		BCR 	STATUS,5 		//07E8 	1283
		ORG		07E9H
		BCR 	STATUS,6 		//07E9 	1303
		BSR 	1FH,1 			//07EA 	189F

		//;test_61f02x_ADC.C: 114: while( GO_DONE==1 );
		BTSC 	1FH,1 			//07EB 	149F
		LJUMP 	7EBH 			//07EC 	3FEB

		//;test_61f02x_ADC.C: 116: ADC_DATA = ADRESH;
		LDR 	1EH,0 			//07ED 	081E
		STR 	78H 			//07EE 	01F8
		CLRR 	79H 			//07EF 	0179

		//;test_61f02x_ADC.C: 117: ADC_DATA <<=8;
		STR 	79H 			//07F0 	01F9
		ORG		07F1H
		CLRR 	78H 			//07F1 	0178

		//;test_61f02x_ADC.C: 118: ADC_DATA |= ADRESL;
		BSR 	STATUS,5 		//07F2 	1A83
		LDR 	1EH,0 			//07F3 	081E
		IORWR 	78H,1 			//07F4 	03F8

		//;test_61f02x_ADC.C: 119: tBuffer = ADC_DATA;
		LDR 	79H,0 			//07F5 	0879
		STR 	76H 			//07F6 	01F6
		LDR 	78H,0 			//07F7 	0878
		STR 	75H 			//07F8 	01F5
		ORG		07F9H

		//;test_61f02x_ADC.C: 120: return tBuffer;
		LDR 	76H,0 			//07F9 	0876
		STR 	73H 			//07FA 	01F3
		LDR 	75H,0 			//07FB 	0875
		STR 	72H 			//07FC 	01F2
		RET		 					//07FD 	0004
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7B7H 			//07FF 	3FB7
			END
