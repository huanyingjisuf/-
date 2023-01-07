//Deviec:FT61F13X
//-----------------------Variable---------------------------------
		_IRbitNum		EQU		78H
		_IRbitTime		EQU		77H
		_IRDataTimer		EQU		70H
		_bitdata		EQU		7CH
		_ReceiveFinish		EQU		76H
		_rdata1		EQU		75H
		_rdata2		EQU		74H
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0DH 			//0001 	380D
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	79H 			//0006 	01F9
		LDR 	FSR,0 			//0007 	0804
		STR 	7AH 			//0008 	01FA
		LDR 	PCLATH,0 		//0009 	080A
		STR 	7BH 			//000A 	01FB
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	1DH 			//000C 	381D
		BCR 	PCLATH,3 		//000D 	118A
		LJUMP 	0FH 			//000E 	380F
		LDWI 	1H 			//000F 	2A01
		STR 	7CH 			//0010 	01FC
		CLRR 	70H 			//0011 	0170
		CLRR 	71H 			//0012 	0171
		CLRR 	72H 			//0013 	0172
		ORG		0014H
		CLRR 	73H 			//0014 	0173
		CLRR 	74H 			//0015 	0174
		CLRR 	75H 			//0016 	0175
		CLRR 	76H 			//0017 	0176
		CLRR 	77H 			//0018 	0177
		CLRR 	78H 			//0019 	0178
		CLRR 	STATUS 			//001A 	0103
		BCR 	PCLATH,3 		//001B 	118A
		ORG		001CH
		LJUMP 	64H 			//001C 	3864

		//;test_61f13x_IR_Receive.C: 99: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//001D 	168B
		BTSS 	INTCON,2 		//001E 	1D0B
		LJUMP 	2CH 			//001F 	382C

		//;test_61f13x_IR_Receive.C: 100: {
		//;test_61f13x_IR_Receive.C: 101: TMR0 = 118;
		LDWI 	76H 			//0020 	2A76
		BCR 	STATUS,5 		//0021 	1283
		BCR 	STATUS,6 		//0022 	1303
		STR 	1H 			//0023 	0181
		ORG		0024H

		//;test_61f13x_IR_Receive.C: 103: T0IF = 0;
		BCR 	INTCON,2 		//0024 	110B
		LDWI 	33H 			//0025 	2A33

		//;test_61f13x_IR_Receive.C: 104: IRbitTime++;
		INCR	77H,1 			//0026 	09F7

		//;test_61f13x_IR_Receive.C: 105: if(IRbitTime > 50)
		SUBWR 	77H,0 			//0027 	0C77
		BTSS 	STATUS,0 		//0028 	1C03
		LJUMP 	2CH 			//0029 	382C

		//;test_61f13x_IR_Receive.C: 106: {
		//;test_61f13x_IR_Receive.C: 107: T0IE = 0;
		BCR 	INTCON,5 		//002A 	128B

		//;test_61f13x_IR_Receive.C: 108: IRbitTime = 0;
		CLRR 	77H 			//002B 	0177
		ORG		002CH

		//;test_61f13x_IR_Receive.C: 109: }
		//;test_61f13x_IR_Receive.C: 110: }
		//;test_61f13x_IR_Receive.C: 113: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//002C 	158B
		BTSS 	INTCON,0 		//002D 	1C0B
		LJUMP 	5BH 			//002E 	385B

		//;test_61f13x_IR_Receive.C: 114: {
		//;test_61f13x_IR_Receive.C: 115: ReadAPin = PORTA;
		BCR 	STATUS,5 		//002F 	1283
		BCR 	STATUS,6 		//0030 	1303
		LDR 	5H,0 			//0031 	0805

		//;test_61f13x_IR_Receive.C: 116: PAIF = 0;
		BCR 	INTCON,0 		//0032 	100B

		//;test_61f13x_IR_Receive.C: 117: if(PA4 == 0)
		BTSC 	5H,4 			//0033 	1605
		ORG		0034H
		LJUMP 	5BH 			//0034 	385B

		//;test_61f13x_IR_Receive.C: 118: {
		//;test_61f13x_IR_Receive.C: 119: T0IE = 1;
		BSR 	INTCON,5 		//0035 	1A8B

		//;test_61f13x_IR_Receive.C: 120: if(IRbitTime > 21)
		LDWI 	16H 			//0036 	2A16
		SUBWR 	77H,0 			//0037 	0C77
		BTSS 	STATUS,0 		//0038 	1C03
		LJUMP 	41H 			//0039 	3841

		//;test_61f13x_IR_Receive.C: 121: {
		//;test_61f13x_IR_Receive.C: 122: IRDataTimer[0] = 0;
		CLRR 	70H 			//003A 	0170

		//;test_61f13x_IR_Receive.C: 123: IRDataTimer[1] = 0;
		CLRR 	71H 			//003B 	0171
		ORG		003CH

		//;test_61f13x_IR_Receive.C: 124: IRDataTimer[2] = 0;
		CLRR 	72H 			//003C 	0172

		//;test_61f13x_IR_Receive.C: 125: IRDataTimer[3] = 0;
		CLRR 	73H 			//003D 	0173

		//;test_61f13x_IR_Receive.C: 126: IRbitNum = 0;
		CLRR 	78H 			//003E 	0178

		//;test_61f13x_IR_Receive.C: 127: bitdata = 0x00;
		CLRR 	7CH 			//003F 	017C

		//;test_61f13x_IR_Receive.C: 128: }
		LJUMP 	4AH 			//0040 	384A

		//;test_61f13x_IR_Receive.C: 129: else if(IRbitTime > 3)
		LDWI 	4H 			//0041 	2A04
		SUBWR 	77H,0 			//0042 	0C77
		BTSS 	STATUS,0 		//0043 	1C03
		ORG		0044H
		LJUMP 	4AH 			//0044 	384A

		//;test_61f13x_IR_Receive.C: 130: {
		//;test_61f13x_IR_Receive.C: 131: IRDataTimer[IRbitNum-1] |= bitdata;
		LDR 	78H,0 			//0045 	0878
		ADDWI 	6FH 			//0046 	276F
		STR 	FSR 			//0047 	0184
		LDR 	7CH,0 			//0048 	087C
		IORWR 	INDF,1 		//0049 	0380

		//;test_61f13x_IR_Receive.C: 132: }
		//;test_61f13x_IR_Receive.C: 133: IRbitTime = 0;
		CLRR 	77H 			//004A 	0177

		//;test_61f13x_IR_Receive.C: 134: bitdata<<=1;
		BCR 	STATUS,0 		//004B 	1003
		ORG		004CH
		RLR 	7CH,1 			//004C 	05FC

		//;test_61f13x_IR_Receive.C: 135: if(bitdata == 0)
		LDR 	7CH,0 			//004D 	087C
		BTSS 	STATUS,2 		//004E 	1D03
		LJUMP 	53H 			//004F 	3853

		//;test_61f13x_IR_Receive.C: 136: {
		//;test_61f13x_IR_Receive.C: 137: bitdata = 0x01;
		CLRR 	7CH 			//0050 	017C
		INCR	7CH,1 			//0051 	09FC

		//;test_61f13x_IR_Receive.C: 138: IRbitNum++;
		INCR	78H,1 			//0052 	09F8

		//;test_61f13x_IR_Receive.C: 139: }
		//;test_61f13x_IR_Receive.C: 140: if(IRbitNum > 4)
		LDWI 	5H 			//0053 	2A05
		ORG		0054H
		SUBWR 	78H,0 			//0054 	0C78
		BTSS 	STATUS,0 		//0055 	1C03
		LJUMP 	5BH 			//0056 	385B

		//;test_61f13x_IR_Receive.C: 141: {
		//;test_61f13x_IR_Receive.C: 142: IRbitNum = 0;
		CLRR 	78H 			//0057 	0178

		//;test_61f13x_IR_Receive.C: 143: T0IE = 0;
		BCR 	INTCON,5 		//0058 	128B

		//;test_61f13x_IR_Receive.C: 144: ReceiveFinish = 1;
		CLRR 	76H 			//0059 	0176
		INCR	76H,1 			//005A 	09F6
		LDR 	7BH,0 			//005B 	087B
		ORG		005CH
		STR 	PCLATH 			//005C 	018A
		LDR 	7AH,0 			//005D 	087A
		STR 	FSR 			//005E 	0184
		SWAPR 	79H,0 			//005F 	0779
		STR 	STATUS 			//0060 	0183
		SWAPR 	7EH,1 			//0061 	07FE
		SWAPR 	7EH,0 			//0062 	077E
		RETI		 			//0063 	0009
		ORG		0064H

		//;test_61f13x_IR_Receive.C: 157: POWER_INITIAL();
		BCR 	PCLATH,3 		//0064 	118A
		LCALL 	81H 			//0065 	3081
		BCR 	PCLATH,3 		//0066 	118A

		//;test_61f13x_IR_Receive.C: 158: TIMER0_INITIAL();
		BCR 	PCLATH,3 		//0067 	118A
		LCALL 	9BH 			//0068 	309B
		BCR 	PCLATH,3 		//0069 	118A

		//;test_61f13x_IR_Receive.C: 159: PA_Level_Change_INITIAL();
		BCR 	PCLATH,3 		//006A 	118A
		LCALL 	92H 			//006B 	3092
		ORG		006CH
		BCR 	PCLATH,3 		//006C 	118A

		//;test_61f13x_IR_Receive.C: 160: GIE = 1;
		BSR 	INTCON,7 		//006D 	1B8B

		//;test_61f13x_IR_Receive.C: 162: {
		//;test_61f13x_IR_Receive.C: 163: if(ReceiveFinish==1)
		DECRSZ 	76H,0 		//006E 	0E76
		LJUMP 	6EH 			//006F 	386E

		//;test_61f13x_IR_Receive.C: 164: {
		//;test_61f13x_IR_Receive.C: 165: ReceiveFinish = 0;
		CLRR 	76H 			//0070 	0176

		//;test_61f13x_IR_Receive.C: 166: rdata1 = 0xFF - IRDataTimer[0];
		COMR 	70H,0 			//0071 	0F70
		STR 	75H 			//0072 	01F5

		//;test_61f13x_IR_Receive.C: 167: rdata2 = 0xFF - IRDataTimer[2];
		COMR 	72H,0 			//0073 	0F72
		ORG		0074H
		STR 	74H 			//0074 	01F4

		//;test_61f13x_IR_Receive.C: 168: if((rdata1 == IRDataTimer[1])&&(rdata2 == IRDataTimer[3]
		//+                          ))
		LDR 	71H,0 			//0075 	0871
		XORWR 	75H,0 			//0076 	0475
		BTSS 	STATUS,2 		//0077 	1D03
		LJUMP 	6EH 			//0078 	386E
		LDR 	73H,0 			//0079 	0873
		XORWR 	74H,0 			//007A 	0474
		BTSS 	STATUS,2 		//007B 	1D03
		ORG		007CH
		LJUMP 	6EH 			//007C 	386E

		//;test_61f13x_IR_Receive.C: 169: {
		//;test_61f13x_IR_Receive.C: 170: PA2 = ~PA2;
		LDWI 	4H 			//007D 	2A04
		BCR 	STATUS,5 		//007E 	1283
		XORWR 	5H,1 			//007F 	0485
		LJUMP 	6EH 			//0080 	386E

		//;test_61f13x_IR_Receive.C: 50: OSCCON = 0B01110001;
		LDWI 	71H 			//0081 	2A71
		BSR 	STATUS,5 		//0082 	1A83
		STR 	FH 			//0083 	018F
		ORG		0084H

		//;test_61f13x_IR_Receive.C: 51: INTCON = 0;
		CLRR 	INTCON 			//0084 	010B

		//;test_61f13x_IR_Receive.C: 52: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0085 	1283
		CLRR 	5H 			//0086 	0105

		//;test_61f13x_IR_Receive.C: 53: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0087 	1A83
		CLRR 	5H 			//0088 	0105

		//;test_61f13x_IR_Receive.C: 56: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0089 	1283
		CLRR 	7H 			//008A 	0107

		//;test_61f13x_IR_Receive.C: 57: TRISC = 0B00000000;
		BSR 	STATUS,5 		//008B 	1A83
		ORG		008CH
		CLRR 	7H 			//008C 	0107

		//;test_61f13x_IR_Receive.C: 59: WPUA = 0B00000000;
		CLRR 	15H 			//008D 	0115

		//;test_61f13x_IR_Receive.C: 60: WPUC = 0B00000000;
		CLRR 	13H 			//008E 	0113

		//;test_61f13x_IR_Receive.C: 62: OPTION = 0B00001000;
		LDWI 	8H 			//008F 	2A08
		STR 	1H 			//0090 	0181
		RET		 					//0091 	0004

		//;test_61f13x_IR_Receive.C: 83: TRISA4 =1;
		BSR 	STATUS,5 		//0092 	1A83
		BSR 	5H,4 			//0093 	1A05
		ORG		0094H

		//;test_61f13x_IR_Receive.C: 84: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0094 	1283
		LDR 	5H,0 			//0095 	0805

		//;test_61f13x_IR_Receive.C: 85: PAIF =0;
		BCR 	INTCON,0 		//0096 	100B

		//;test_61f13x_IR_Receive.C: 86: IOCA4 =1;
		BSR 	STATUS,5 		//0097 	1A83
		BSR 	16H,4 			//0098 	1A16

		//;test_61f13x_IR_Receive.C: 87: PAIE =1;
		BSR 	INTCON,3 		//0099 	198B
		RET		 					//009A 	0004

		//;test_61f13x_IR_Receive.C: 71: OPTION = 0B00000011;
		LDWI 	3H 			//009B 	2A03
		ORG		009CH
		STR 	1H 			//009C 	0181

		//;test_61f13x_IR_Receive.C: 72: TMR0 = 118;
		LDWI 	76H 			//009D 	2A76
		BCR 	STATUS,5 		//009E 	1283
		STR 	1H 			//009F 	0181

		//;test_61f13x_IR_Receive.C: 73: T0IF = 0;
		BCR 	INTCON,2 		//00A0 	110B
		RET		 					//00A1 	0004
			END
