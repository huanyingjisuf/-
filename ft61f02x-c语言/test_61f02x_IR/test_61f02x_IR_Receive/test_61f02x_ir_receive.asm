//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_IRbitNum		EQU		76H
		_IRbitTime		EQU		75H
		_IRDataTimer		EQU		70H
		_bitdata		EQU		7CH
		_ReceiveFinish		EQU		74H
//		main@rdata2		EQU		7BH
//		main@rdata1		EQU		7AH
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0CH 			//0000 	380C
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	77H 			//0006 	01F7
		LDR 	FSR,0 			//0007 	0804
		STR 	78H 			//0008 	01F8
		LDR 	PCLATH,0 		//0009 	080A
		STR 	79H 			//000A 	01F9
		LJUMP 	18H 			//000B 	3818
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		LDWI 	1H 			//000D 	2A01
		STR 	7CH 			//000E 	01FC
		CLRR 	70H 			//000F 	0170
		CLRR 	71H 			//0010 	0171
		CLRR 	72H 			//0011 	0172
		CLRR 	73H 			//0012 	0173
		CLRR 	74H 			//0013 	0174
		ORG		0014H
		CLRR 	75H 			//0014 	0175
		CLRR 	76H 			//0015 	0176
		CLRR 	STATUS 			//0016 	0103
		LJUMP 	5FH 			//0017 	385F

		//;test_61f02x_IR_Receive.C: 109: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//0018 	168B
		BTSS 	INTCON,2 		//0019 	1D0B
		LJUMP 	27H 			//001A 	3827

		//;test_61f02x_IR_Receive.C: 110: {
		//;test_61f02x_IR_Receive.C: 111: TMR0 = 118;
		LDWI 	76H 			//001B 	2A76
		ORG		001CH
		BCR 	STATUS,5 		//001C 	1283
		BCR 	STATUS,6 		//001D 	1303
		STR 	1H 			//001E 	0181

		//;test_61f02x_IR_Receive.C: 113: T0IF = 0;
		BCR 	INTCON,2 		//001F 	110B
		LDWI 	33H 			//0020 	2A33

		//;test_61f02x_IR_Receive.C: 114: IRbitTime++;
		INCR	75H,1 			//0021 	09F5

		//;test_61f02x_IR_Receive.C: 115: if(IRbitTime > 50)
		SUBWR 	75H,0 			//0022 	0C75
		BTSS 	STATUS,0 		//0023 	1C03
		ORG		0024H
		LJUMP 	27H 			//0024 	3827

		//;test_61f02x_IR_Receive.C: 116: {
		//;test_61f02x_IR_Receive.C: 117: T0IE = 0;
		BCR 	INTCON,5 		//0025 	128B

		//;test_61f02x_IR_Receive.C: 118: IRbitTime = 0;
		CLRR 	75H 			//0026 	0175

		//;test_61f02x_IR_Receive.C: 119: }
		//;test_61f02x_IR_Receive.C: 120: }
		//;test_61f02x_IR_Receive.C: 123: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0027 	158B
		BTSS 	INTCON,0 		//0028 	1C0B
		LJUMP 	56H 			//0029 	3856

		//;test_61f02x_IR_Receive.C: 124: {
		//;test_61f02x_IR_Receive.C: 125: ReadAPin = PORTA;
		BCR 	STATUS,5 		//002A 	1283
		BCR 	STATUS,6 		//002B 	1303
		ORG		002CH
		LDR 	5H,0 			//002C 	0805

		//;test_61f02x_IR_Receive.C: 126: PAIF = 0;
		BCR 	INTCON,0 		//002D 	100B

		//;test_61f02x_IR_Receive.C: 127: if(PA4 == 0)
		BTSC 	5H,4 			//002E 	1605
		LJUMP 	56H 			//002F 	3856

		//;test_61f02x_IR_Receive.C: 128: {
		//;test_61f02x_IR_Receive.C: 129: T0IE = 1;
		BSR 	INTCON,5 		//0030 	1A8B

		//;test_61f02x_IR_Receive.C: 130: if(IRbitTime > 21)
		LDWI 	16H 			//0031 	2A16
		SUBWR 	75H,0 			//0032 	0C75
		BTSS 	STATUS,0 		//0033 	1C03
		ORG		0034H
		LJUMP 	3CH 			//0034 	383C

		//;test_61f02x_IR_Receive.C: 131: {
		//;test_61f02x_IR_Receive.C: 132: IRDataTimer[0] = 0;
		CLRR 	70H 			//0035 	0170

		//;test_61f02x_IR_Receive.C: 133: IRDataTimer[1] = 0;
		CLRR 	71H 			//0036 	0171

		//;test_61f02x_IR_Receive.C: 134: IRDataTimer[2] = 0;
		CLRR 	72H 			//0037 	0172

		//;test_61f02x_IR_Receive.C: 135: IRDataTimer[3] = 0;
		CLRR 	73H 			//0038 	0173

		//;test_61f02x_IR_Receive.C: 136: IRbitNum = 0;
		CLRR 	76H 			//0039 	0176

		//;test_61f02x_IR_Receive.C: 137: bitdata = 0x00;
		CLRR 	7CH 			//003A 	017C

		//;test_61f02x_IR_Receive.C: 138: }
		LJUMP 	45H 			//003B 	3845
		ORG		003CH

		//;test_61f02x_IR_Receive.C: 139: else if(IRbitTime > 3)
		LDWI 	4H 			//003C 	2A04
		SUBWR 	75H,0 			//003D 	0C75
		BTSS 	STATUS,0 		//003E 	1C03
		LJUMP 	45H 			//003F 	3845

		//;test_61f02x_IR_Receive.C: 140: {
		//;test_61f02x_IR_Receive.C: 141: IRDataTimer[IRbitNum-1] |= bitdata;
		LDR 	76H,0 			//0040 	0876
		ADDWI 	6FH 			//0041 	276F
		STR 	FSR 			//0042 	0184
		LDR 	7CH,0 			//0043 	087C
		ORG		0044H
		IORWR 	INDF,1 		//0044 	0380

		//;test_61f02x_IR_Receive.C: 142: }
		//;test_61f02x_IR_Receive.C: 143: IRbitTime = 0;
		CLRR 	75H 			//0045 	0175

		//;test_61f02x_IR_Receive.C: 144: bitdata<<=1;
		BCR 	STATUS,0 		//0046 	1003
		RLR 	7CH,1 			//0047 	05FC

		//;test_61f02x_IR_Receive.C: 145: if(bitdata == 0)
		LDR 	7CH,0 			//0048 	087C
		BTSS 	STATUS,2 		//0049 	1D03
		LJUMP 	4EH 			//004A 	384E

		//;test_61f02x_IR_Receive.C: 146: {
		//;test_61f02x_IR_Receive.C: 147: bitdata = 0x01;
		CLRR 	7CH 			//004B 	017C
		ORG		004CH
		INCR	7CH,1 			//004C 	09FC

		//;test_61f02x_IR_Receive.C: 148: IRbitNum++;
		INCR	76H,1 			//004D 	09F6

		//;test_61f02x_IR_Receive.C: 149: }
		//;test_61f02x_IR_Receive.C: 150: if(IRbitNum > 4)
		LDWI 	5H 			//004E 	2A05
		SUBWR 	76H,0 			//004F 	0C76
		BTSS 	STATUS,0 		//0050 	1C03
		LJUMP 	56H 			//0051 	3856

		//;test_61f02x_IR_Receive.C: 151: {
		//;test_61f02x_IR_Receive.C: 152: IRbitNum = 0;
		CLRR 	76H 			//0052 	0176

		//;test_61f02x_IR_Receive.C: 153: T0IE = 0;
		BCR 	INTCON,5 		//0053 	128B
		ORG		0054H

		//;test_61f02x_IR_Receive.C: 154: ReceiveFinish = 1;
		CLRR 	74H 			//0054 	0174
		INCR	74H,1 			//0055 	09F4
		LDR 	79H,0 			//0056 	0879
		STR 	PCLATH 			//0057 	018A
		LDR 	78H,0 			//0058 	0878
		STR 	FSR 			//0059 	0184
		SWAPR 	77H,0 			//005A 	0777
		STR 	STATUS 			//005B 	0183
		ORG		005CH
		SWAPR 	7EH,1 			//005C 	07FE
		SWAPR 	7EH,0 			//005D 	077E
		RETI		 			//005E 	0009

		//;test_61f02x_IR_Receive.C: 168: unsigned char rdata1,rdata2;
		//;test_61f02x_IR_Receive.C: 169: POWER_INITIAL();
		LCALL 	77H 			//005F 	3077

		//;test_61f02x_IR_Receive.C: 170: TIMER0_INITIAL();
		LCALL 	95H 			//0060 	3095

		//;test_61f02x_IR_Receive.C: 171: PA_Level_Change_INITIAL();
		LCALL 	8CH 			//0061 	308C

		//;test_61f02x_IR_Receive.C: 172: GIE = 1;
		BSR 	INTCON,7 		//0062 	1B8B

		//;test_61f02x_IR_Receive.C: 174: {
		//;test_61f02x_IR_Receive.C: 175: if(ReceiveFinish)
		LDR 	74H,0 			//0063 	0874
		ORG		0064H
		BTSC 	STATUS,2 		//0064 	1503
		LJUMP 	63H 			//0065 	3863

		//;test_61f02x_IR_Receive.C: 176: {
		//;test_61f02x_IR_Receive.C: 177: ReceiveFinish = 0;
		CLRR 	74H 			//0066 	0174

		//;test_61f02x_IR_Receive.C: 178: rdata1 = 0xFF - IRDataTimer[0];
		COMR 	70H,0 			//0067 	0F70
		STR 	7AH 			//0068 	01FA

		//;test_61f02x_IR_Receive.C: 179: rdata2 = 0xFF - IRDataTimer[2];
		COMR 	72H,0 			//0069 	0F72
		STR 	7BH 			//006A 	01FB

		//;test_61f02x_IR_Receive.C: 180: if((rdata1 == IRDataTimer[1])&&(rdata2 == IRDataTimer[3]
		//+                          ))
		LDR 	71H,0 			//006B 	0871
		ORG		006CH
		XORWR 	7AH,0 			//006C 	047A
		BTSS 	STATUS,2 		//006D 	1D03
		LJUMP 	63H 			//006E 	3863
		LDR 	73H,0 			//006F 	0873
		XORWR 	7BH,0 			//0070 	047B
		BTSS 	STATUS,2 		//0071 	1D03
		LJUMP 	63H 			//0072 	3863

		//;test_61f02x_IR_Receive.C: 181: {
		//;test_61f02x_IR_Receive.C: 182: PA2 = ~PA2;
		LDWI 	4H 			//0073 	2A04
		ORG		0074H
		BCR 	STATUS,5 		//0074 	1283
		XORWR 	5H,1 			//0075 	0485
		LJUMP 	63H 			//0076 	3863

		//;test_61f02x_IR_Receive.C: 46: OSCCON = 0B01110001;
		LDWI 	71H 			//0077 	2A71
		BSR 	STATUS,5 		//0078 	1A83
		STR 	FH 			//0079 	018F

		//;test_61f02x_IR_Receive.C: 47: INTCON = 0;
		CLRR 	INTCON 			//007A 	010B

		//;test_61f02x_IR_Receive.C: 48: PORTA = 0B00000000;
		BCR 	STATUS,5 		//007B 	1283
		ORG		007CH
		CLRR 	5H 			//007C 	0105

		//;test_61f02x_IR_Receive.C: 49: TRISA = 0B00010000;
		LDWI 	10H 			//007D 	2A10
		BSR 	STATUS,5 		//007E 	1A83
		STR 	5H 			//007F 	0185

		//;test_61f02x_IR_Receive.C: 51: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0080 	1283
		CLRR 	7H 			//0081 	0107

		//;test_61f02x_IR_Receive.C: 52: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0082 	1A83
		CLRR 	7H 			//0083 	0107
		ORG		0084H

		//;test_61f02x_IR_Receive.C: 53: WPUA = 0B00000000;
		CLRR 	15H 			//0084 	0115

		//;test_61f02x_IR_Receive.C: 54: WPUC = 0B00000000;
		CLRR 	8H 			//0085 	0108

		//;test_61f02x_IR_Receive.C: 56: OPTION = 0B00000000;
		CLRR 	1H 			//0086 	0101

		//;test_61f02x_IR_Receive.C: 57: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0087 	1283
		CLRR 	1BH 			//0088 	011B

		//;test_61f02x_IR_Receive.C: 61: CMCON0 = 0B00000111;
		LDWI 	7H 			//0089 	2A07
		STR 	19H 			//008A 	0199
		RET		 					//008B 	0004
		ORG		008CH

		//;test_61f02x_IR_Receive.C: 92: TRISA4 =1;
		BSR 	STATUS,5 		//008C 	1A83
		BSR 	5H,4 			//008D 	1A05

		//;test_61f02x_IR_Receive.C: 93: ReadAPin = PORTA;
		BCR 	STATUS,5 		//008E 	1283
		LDR 	5H,0 			//008F 	0805

		//;test_61f02x_IR_Receive.C: 94: PAIF =0;
		BCR 	INTCON,0 		//0090 	100B

		//;test_61f02x_IR_Receive.C: 95: IOCA4 =1;
		BSR 	STATUS,5 		//0091 	1A83
		BSR 	16H,4 			//0092 	1A16

		//;test_61f02x_IR_Receive.C: 96: PAIE =1;
		BSR 	INTCON,3 		//0093 	198B
		ORG		0094H
		RET		 					//0094 	0004

		//;test_61f02x_IR_Receive.C: 73: OPTION = 0B00000011;
		LDWI 	3H 			//0095 	2A03
		BSR 	STATUS,5 		//0096 	1A83
		STR 	1H 			//0097 	0181

		//;test_61f02x_IR_Receive.C: 80: TMR0 = 118;
		LDWI 	76H 			//0098 	2A76
		BCR 	STATUS,5 		//0099 	1283
		STR 	1H 			//009A 	0181

		//;test_61f02x_IR_Receive.C: 81: T0IF = 0;
		BCR 	INTCON,2 		//009B 	110B
		ORG		009CH
		RET		 					//009C 	0004
			END
