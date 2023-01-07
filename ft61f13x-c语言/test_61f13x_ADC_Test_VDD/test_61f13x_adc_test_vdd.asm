//Deviec:FT61F13X
//-----------------------Variable---------------------------------
		_adcData		EQU		79H
		_VDD_Voltage		EQU		77H
//		___lwdiv@quotient		EQU		74H
//		___lwdiv@counter		EQU		76H
//		___lwdiv@divisor		EQU		70H
//		___lwdiv@dividend		EQU		72H
//		GET_ADC_DATA@adcChannel		EQU		75H
//		GET_ADC_DATA@adcChannel		EQU		75H
//		GET_ADC_DATA@adcChannel		EQU		75H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		70H
//		DelayUs@Time		EQU		70H
//-----------------------Variable END---------------------------------

		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7F9H 			//0001 	3FF9
		ORG		0750H

		//;test_61f13x_ADC_Test_VDD.C: 36: OSCCON = 0B01110001;
		LDWI 	71H 			//0750 	2A71
		BSR 	STATUS,5 		//0751 	1A83
		STR 	FH 			//0752 	018F

		//;test_61f13x_ADC_Test_VDD.C: 37: INTCON = 0B00000000;
		CLRR 	INTCON 			//0753 	010B

		//;test_61f13x_ADC_Test_VDD.C: 39: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0754 	1283
		CLRR 	5H 			//0755 	0105

		//;test_61f13x_ADC_Test_VDD.C: 40: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0756 	1A83
		CLRR 	5H 			//0757 	0105

		//;test_61f13x_ADC_Test_VDD.C: 41: PORTB = 0B00000000;
		BCR 	STATUS,5 		//0758 	1283
		CLRR 	6H 			//0759 	0106

		//;test_61f13x_ADC_Test_VDD.C: 42: TRISB = 0B00000000;
		BSR 	STATUS,5 		//075A 	1A83
		CLRR 	6H 			//075B 	0106

		//;test_61f13x_ADC_Test_VDD.C: 43: PORTC = 0B00000000;
		BCR 	STATUS,5 		//075C 	1283
		CLRR 	7H 			//075D 	0107

		//;test_61f13x_ADC_Test_VDD.C: 44: TRISC = 0B00000000;
		BSR 	STATUS,5 		//075E 	1A83
		CLRR 	7H 			//075F 	0107

		//;test_61f13x_ADC_Test_VDD.C: 46: WPUA = 0B00000000;
		CLRR 	15H 			//0760 	0115

		//;test_61f13x_ADC_Test_VDD.C: 47: WPUB = 0B00000000;
		BCR 	STATUS,5 		//0761 	1283
		BSR 	STATUS,6 		//0762 	1B03
		CLRR 	DH 			//0763 	010D

		//;test_61f13x_ADC_Test_VDD.C: 48: WPUC = 0B00000000;
		BSR 	STATUS,5 		//0764 	1A83
		BCR 	STATUS,6 		//0765 	1303
		CLRR 	13H 			//0766 	0113
		RET		 					//0767 	0004

		//;test_61f13x_ADC_Test_VDD.C: 199: POWER_INITIAL();
		BCR 	PCLATH,3 		//0768 	118A
		LCALL 	750H 			//0769 	3750
		BCR 	PCLATH,3 		//076A 	118A

		//;test_61f13x_ADC_Test_VDD.C: 200: ADC_INITIAL();
		BCR 	PCLATH,3 		//076B 	118A
		LCALL 	7DCH 			//076C 	37DC
		BCR 	PCLATH,3 		//076D 	118A

		//;test_61f13x_ADC_Test_VDD.C: 202: while(1)
		//;test_61f13x_ADC_Test_VDD.C: 203: {
		//;test_61f13x_ADC_Test_VDD.C: 204: adcData = GET_ADC_DATA(0x08);
		LDWI 	8H 			//076E 	2A08
		BCR 	PCLATH,3 		//076F 	118A
		LCALL 	7BAH 			//0770 	37BA
		BCR 	PCLATH,3 		//0771 	118A
		LDR 	73H,0 			//0772 	0873
		STR 	7AH 			//0773 	01FA
		LDR 	72H,0 			//0774 	0872
		STR 	79H 			//0775 	01F9

		//;test_61f13x_ADC_Test_VDD.C: 205: adcData >>=4;
		SWAPR 	79H,1 			//0776 	07F9
		SWAPR 	7AH,1 			//0777 	07FA
		LDWI 	FH 			//0778 	2A0F
		ANDWR 	79H,1 			//0779 	02F9
		LDR 	7AH,0 			//077A 	087A
		ANDWI 	F0H 			//077B 	24F0
		IORWR 	79H,1 			//077C 	03F9
		LDWI 	FH 			//077D 	2A0F
		ANDWR 	7AH,1 			//077E 	02FA

		//;test_61f13x_ADC_Test_VDD.C: 207: VDD_Voltage = (unsigned long)((512*100/adcData));
		LDR 	7AH,0 			//077F 	087A
		STR 	71H 			//0780 	01F1
		LDR 	79H,0 			//0781 	0879
		STR 	70H 			//0782 	01F0
		LDWI 	C8H 			//0783 	2AC8
		CLRR 	72H 			//0784 	0172
		STR 	73H 			//0785 	01F3
		BCR 	PCLATH,3 		//0786 	118A
		LCALL 	790H 			//0787 	3790
		BCR 	PCLATH,3 		//0788 	118A
		LDR 	71H,0 			//0789 	0871
		STR 	78H 			//078A 	01F8
		LDR 	70H,0 			//078B 	0870
		STR 	77H 			//078C 	01F7

		//;test_61f13x_ADC_Test_VDD.C: 209: __nop();
		NOP		 					//078D 	0000

		//;test_61f13x_ADC_Test_VDD.C: 210: __nop();
		NOP		 					//078E 	0000
		LJUMP 	76EH 			//078F 	3F6E
		CLRR 	74H 			//0790 	0174
		CLRR 	75H 			//0791 	0175
		LDR 	70H,0 			//0792 	0870
		IORWR 	71H,0 			//0793 	0371
		BTSC 	STATUS,2 		//0794 	1503
		LJUMP 	7B5H 			//0795 	3FB5
		CLRR 	76H 			//0796 	0176
		INCR	76H,1 			//0797 	09F6
		BTSC 	71H,7 			//0798 	17F1
		LJUMP 	79EH 			//0799 	3F9E
		BCR 	STATUS,0 		//079A 	1003
		RLR 	70H,1 			//079B 	05F0
		RLR 	71H,1 			//079C 	05F1
		LJUMP 	797H 			//079D 	3F97
		BCR 	STATUS,0 		//079E 	1003
		RLR 	74H,1 			//079F 	05F4
		RLR 	75H,1 			//07A0 	05F5
		LDR 	71H,0 			//07A1 	0871
		SUBWR 	73H,0 			//07A2 	0C73
		BTSS 	STATUS,2 		//07A3 	1D03
		LJUMP 	7A7H 			//07A4 	3FA7
		LDR 	70H,0 			//07A5 	0870
		SUBWR 	72H,0 			//07A6 	0C72
		BTSS 	STATUS,0 		//07A7 	1C03
		LJUMP 	7B1H 			//07A8 	3FB1
		LDR 	70H,0 			//07A9 	0870
		SUBWR 	72H,1 			//07AA 	0CF2
		LDR 	71H,0 			//07AB 	0871
		BTSS 	STATUS,0 		//07AC 	1C03
		DECR 	73H,1 			//07AD 	0DF3
		SUBWR 	73H,1 			//07AE 	0CF3
		BSR 	74H,0 			//07AF 	1874
		BCR 	STATUS,0 		//07B0 	1003
		RRR	71H,1 			//07B1 	06F1
		RRR	70H,1 			//07B2 	06F0
		DECRSZ 	76H,1 		//07B3 	0EF6
		LJUMP 	79EH 			//07B4 	3F9E
		LDR 	75H,0 			//07B5 	0875
		STR 	71H 			//07B6 	01F1
		LDR 	74H,0 			//07B7 	0874
		STR 	70H 			//07B8 	01F0
		RET		 					//07B9 	0004
		STR 	75H 			//07BA 	01F5

		//;test_61f13x_ADC_Test_VDD.C: 181: ADCON0 &= 0B00000111;
		LDWI 	7H 			//07BB 	2A07
		BCR 	STATUS,5 		//07BC 	1283
		BSR 	STATUS,6 		//07BD 	1B03
		ANDWR 	13H,1 			//07BE 	0293

		//;test_61f13x_ADC_Test_VDD.C: 182: ADCON0 |= adcChannel<<3;
		LDR 	75H,0 			//07BF 	0875
		STR 	74H 			//07C0 	01F4
		BCR 	STATUS,0 		//07C1 	1003
		RLR 	74H,1 			//07C2 	05F4
		BCR 	STATUS,0 		//07C3 	1003
		RLR 	74H,1 			//07C4 	05F4
		BCR 	STATUS,0 		//07C5 	1003
		RLR 	74H,0 			//07C6 	0574
		IORWR 	13H,1 			//07C7 	0393

		//;test_61f13x_ADC_Test_VDD.C: 183: DelayUs(40);
		LDWI 	28H 			//07C8 	2A28
		LCALL 	7F0H 			//07C9 	37F0
		BCR 	PCLATH,3 		//07CA 	118A

		//;test_61f13x_ADC_Test_VDD.C: 184: ADCON0 = ADCON0|0x02;
		BCR 	STATUS,5 		//07CB 	1283
		BSR 	STATUS,6 		//07CC 	1B03
		LDR 	13H,0 			//07CD 	0813
		IORWI 	2H 			//07CE 	2502
		STR 	13H 			//07CF 	0193

		//;test_61f13x_ADC_Test_VDD.C: 185: __nop();
		NOP		 					//07D0 	0000

		//;test_61f13x_ADC_Test_VDD.C: 186: __nop();
		NOP		 					//07D1 	0000

		//;test_61f13x_ADC_Test_VDD.C: 187: while(ADCON0&0x02);
		BCR 	STATUS,5 		//07D2 	1283
		BSR 	STATUS,6 		//07D3 	1B03
		BTSC 	13H,1 			//07D4 	1493
		LJUMP 	7D2H 			//07D5 	3FD2

		//;test_61f13x_ADC_Test_VDD.C: 189: return (unsigned int)(ADRESH<<8|ADRESL);
		LDR 	12H,0 			//07D6 	0812
		STR 	73H 			//07D7 	01F3
		CLRR 	72H 			//07D8 	0172
		LDR 	11H,0 			//07D9 	0811
		IORWR 	72H,1 			//07DA 	03F2
		RET		 					//07DB 	0004

		//;test_61f13x_ADC_Test_VDD.C: 72: ADCON1 = 0B10100101;
		LDWI 	A5H 			//07DC 	2AA5
		BCR 	STATUS,5 		//07DD 	1283
		BSR 	STATUS,6 		//07DE 	1B03
		STR 	14H 			//07DF 	0194

		//;test_61f13x_ADC_Test_VDD.C: 100: ADCON0 = 0B00000000;
		CLRR 	13H 			//07E0 	0113

		//;test_61f13x_ADC_Test_VDD.C: 125: DelayUs(200);
		LDWI 	C8H 			//07E1 	2AC8
		LCALL 	7F0H 			//07E2 	37F0
		BCR 	PCLATH,3 		//07E3 	118A

		//;test_61f13x_ADC_Test_VDD.C: 126: DelayUs(250);
		LDWI 	FAH 			//07E4 	2AFA
		LCALL 	7F0H 			//07E5 	37F0

		//;test_61f13x_ADC_Test_VDD.C: 128: ADCON2 = 0B01000000;
		LDWI 	40H 			//07E6 	2A40
		BCR 	STATUS,5 		//07E7 	1283
		BSR 	STATUS,6 		//07E8 	1B03
		STR 	15H 			//07E9 	0195

		//;test_61f13x_ADC_Test_VDD.C: 152: ADCON3 = 0B00000000;
		BSR 	STATUS,5 		//07EA 	1A83
		CLRR 	6H 			//07EB 	0106

		//;test_61f13x_ADC_Test_VDD.C: 169: ADCMPH = 0B00000000;
		CLRR 	7H 			//07EC 	0107

		//;test_61f13x_ADC_Test_VDD.C: 171: ADON=1;
		BCR 	STATUS,5 		//07ED 	1283
		BSR 	13H,0 			//07EE 	1813
		RET		 					//07EF 	0004
		STR 	70H 			//07F0 	01F0

		//;test_61f13x_ADC_Test_VDD.C: 58: unsigned char a;
		//;test_61f13x_ADC_Test_VDD.C: 59: for(a=0;a<Time;a++)
		CLRR 	71H 			//07F1 	0171
		LDR 	70H,0 			//07F2 	0870
		SUBWR 	71H,0 			//07F3 	0C71
		BTSC 	STATUS,0 		//07F4 	1403
		RET		 					//07F5 	0004

		//;test_61f13x_ADC_Test_VDD.C: 60: {
		//;test_61f13x_ADC_Test_VDD.C: 61: __nop();
		NOP		 					//07F6 	0000
		INCR	71H,1 			//07F7 	09F1
		LJUMP 	7F2H 			//07F8 	3FF2
		CLRR 	77H 			//07F9 	0177
		CLRR 	78H 			//07FA 	0178
		CLRR 	79H 			//07FB 	0179
		CLRR 	7AH 			//07FC 	017A
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	768H 			//07FF 	3F68
			END
