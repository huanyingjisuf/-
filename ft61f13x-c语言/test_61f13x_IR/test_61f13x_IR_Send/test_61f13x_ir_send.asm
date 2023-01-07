//Deviec:FT61F13X
//-----------------------Variable---------------------------------
		_IRSendStatus		EQU		76H
		_IRSendData		EQU		75H
		_TxBit		EQU		74H
		_TxTime		EQU		73H
		_Sendbit		EQU		72H
		_level0		EQU		71H
		_level1		EQU		70H
		_SendLastBit		EQU		7DH
		_SaveLastBit		EQU		26H
		_SYSTime5S		EQU		24H
		_IRData		EQU		20H
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0DH 			//0001 	380D
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	7AH 			//0006 	01FA
		LDR 	FSR,0 			//0007 	0804
		STR 	7BH 			//0008 	01FB
		LDR 	PCLATH,0 		//0009 	080A
		STR 	7CH 			//000A 	01FC
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	24H 			//000C 	3824
		BCR 	PCLATH,3 		//000D 	118A
		LJUMP 	0FH 			//000E 	380F
		LDWI 	FFH 			//000F 	2AFF
		CLRR 	20H 			//0010 	0120
		STR 	21H 			//0011 	01A1
		LDWI 	40H 			//0012 	2A40
		STR 	22H 			//0013 	01A2
		ORG		0014H
		LDWI 	BFH 			//0014 	2ABF
		STR 	23H 			//0015 	01A3
		CLRR 	24H 			//0016 	0124
		CLRR 	25H 			//0017 	0125
		CLRR 	26H 			//0018 	0126
		CLRR 	70H 			//0019 	0170
		CLRR 	71H 			//001A 	0171
		CLRR 	72H 			//001B 	0172
		ORG		001CH
		CLRR 	73H 			//001C 	0173
		CLRR 	74H 			//001D 	0174
		CLRR 	75H 			//001E 	0175
		CLRR 	76H 			//001F 	0176
		CLRR 	7DH 			//0020 	017D
		CLRR 	STATUS 			//0021 	0103
		BCR 	PCLATH,3 		//0022 	118A
		LJUMP 	E9H 			//0023 	38E9
		ORG		0024H

		//;test_61f13x_IR_Send.C: 282: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//0024 	168B
		BTSS 	INTCON,2 		//0025 	1D0B
		LJUMP 	2EH 			//0026 	382E

		//;test_61f13x_IR_Send.C: 283: {
		//;test_61f13x_IR_Send.C: 284: TMR0 = 239;
		LDWI 	EFH 			//0027 	2AEF
		BCR 	STATUS,5 		//0028 	1283
		BCR 	STATUS,6 		//0029 	1303
		STR 	1H 			//002A 	0181

		//;test_61f13x_IR_Send.C: 285: T0IF = 0;
		BCR 	INTCON,2 		//002B 	110B
		ORG		002CH

		//;test_61f13x_IR_Send.C: 286: PA4 = ~PA4;
		LDWI 	10H 			//002C 	2A10
		XORWR 	5H,1 			//002D 	0485

		//;test_61f13x_IR_Send.C: 288: }
		//;test_61f13x_IR_Send.C: 291: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//002E 	1A83
		BCR 	STATUS,6 		//002F 	1303
		BTSS 	CH,1 			//0030 	1C8C
		LJUMP 	3CH 			//0031 	383C
		BCR 	STATUS,5 		//0032 	1283
		BTSS 	CH,1 			//0033 	1C8C
		ORG		0034H
		LJUMP 	3CH 			//0034 	383C

		//;test_61f13x_IR_Send.C: 292: {
		//;test_61f13x_IR_Send.C: 293: TMR2IF = 0;
		BCR 	CH,1 			//0035 	108C

		//;test_61f13x_IR_Send.C: 294: SendCtrl();
		LCALL 	45H 			//0036 	3045

		//;test_61f13x_IR_Send.C: 295: SYSTime5S++;
		BCR 	STATUS,5 		//0037 	1283
		BCR 	STATUS,6 		//0038 	1303
		INCR	24H,1 			//0039 	09A4
		BTSC 	STATUS,2 		//003A 	1503
		INCR	25H,1 			//003B 	09A5
		ORG		003CH
		LDR 	7CH,0 			//003C 	087C
		STR 	PCLATH 			//003D 	018A
		LDR 	7BH,0 			//003E 	087B
		STR 	FSR 			//003F 	0184
		SWAPR 	7AH,0 			//0040 	077A
		STR 	STATUS 			//0041 	0183
		SWAPR 	7EH,1 			//0042 	07FE
		SWAPR 	7EH,0 			//0043 	077E
		ORG		0044H
		RETI		 			//0044 	0009

		//;test_61f13x_IR_Send.C: 157: if (IRSendStatus == 0)
		LDR 	76H,0 			//0045 	0876
		BTSS 	STATUS,2 		//0046 	1D03
		LJUMP 	4CH 			//0047 	384C

		//;test_61f13x_IR_Send.C: 158: {
		//;test_61f13x_IR_Send.C: 159: T0IE = 0;
		BCR 	INTCON,5 		//0048 	128B

		//;test_61f13x_IR_Send.C: 160: Sendbit = 0;
		CLRR 	72H 			//0049 	0172

		//;test_61f13x_IR_Send.C: 161: TxTime = 0;
		CLRR 	73H 			//004A 	0173

		//;test_61f13x_IR_Send.C: 163: }
		RET		 					//004B 	0004
		ORG		004CH

		//;test_61f13x_IR_Send.C: 164: else if (IRSendStatus == 1)
		DECRSZ 	76H,0 		//004C 	0E76
		LJUMP 	63H 			//004D 	3863
		LDWI 	11H 			//004E 	2A11

		//;test_61f13x_IR_Send.C: 165: {
		//;test_61f13x_IR_Send.C: 166: TxTime++;
		INCR	73H,1 			//004F 	09F3

		//;test_61f13x_IR_Send.C: 167: if (TxTime < 17)
		SUBWR 	73H,0 			//0050 	0C73
		BTSC 	STATUS,0 		//0051 	1403
		LJUMP 	55H 			//0052 	3855

		//;test_61f13x_IR_Send.C: 168: {
		//;test_61f13x_IR_Send.C: 169: T0IE = 1;
		BSR 	INTCON,5 		//0053 	1A8B
		ORG		0054H

		//;test_61f13x_IR_Send.C: 170: }
		LJUMP 	5EH 			//0054 	385E

		//;test_61f13x_IR_Send.C: 171: else if (TxTime < 24)
		LDWI 	18H 			//0055 	2A18
		SUBWR 	73H,0 			//0056 	0C73
		BTSC 	STATUS,0 		//0057 	1403
		LJUMP 	5BH 			//0058 	385B

		//;test_61f13x_IR_Send.C: 172: {
		//;test_61f13x_IR_Send.C: 173: T0IE = 0;
		BCR 	INTCON,5 		//0059 	128B

		//;test_61f13x_IR_Send.C: 174: }
		LJUMP 	5EH 			//005A 	385E
		LDWI 	2H 			//005B 	2A02
		ORG		005CH

		//;test_61f13x_IR_Send.C: 175: else
		//;test_61f13x_IR_Send.C: 176: {
		//;test_61f13x_IR_Send.C: 177: TxTime = 0;
		CLRR 	73H 			//005C 	0173

		//;test_61f13x_IR_Send.C: 178: IRSendStatus = 2;
		STR 	76H 			//005D 	01F6

		//;test_61f13x_IR_Send.C: 179: }
		//;test_61f13x_IR_Send.C: 180: IRSendData = IRData[0];
		LDR 	20H,0 			//005E 	0820
		STR 	75H 			//005F 	01F5

		//;test_61f13x_IR_Send.C: 181: TxBit = 0x01;
		CLRR 	74H 			//0060 	0174
		INCR	74H,1 			//0061 	09F4

		//;test_61f13x_IR_Send.C: 182: }
		RET		 					//0062 	0004

		//;test_61f13x_IR_Send.C: 183: else if(IRSendStatus == 2)
		LDWI 	2H 			//0063 	2A02
		ORG		0064H
		XORWR 	76H,0 			//0064 	0476
		BTSS 	STATUS,2 		//0065 	1D03
		RET		 					//0066 	0004

		//;test_61f13x_IR_Send.C: 184: {
		//;test_61f13x_IR_Send.C: 185: if (IRSendData & TxBit)
		LDR 	75H,0 			//0067 	0875
		ANDWR 	74H,0 			//0068 	0274
		BTSC 	STATUS,2 		//0069 	1503
		LJUMP 	70H 			//006A 	3870
		LDWI 	3H 			//006B 	2A03
		ORG		006CH

		//;test_61f13x_IR_Send.C: 186: {
		//;test_61f13x_IR_Send.C: 187: level1 = 1;
		CLRR 	70H 			//006C 	0170
		INCR	70H,1 			//006D 	09F0

		//;test_61f13x_IR_Send.C: 188: level0 = 3;
		STR 	71H 			//006E 	01F1

		//;test_61f13x_IR_Send.C: 189: }
		LJUMP 	74H 			//006F 	3874

		//;test_61f13x_IR_Send.C: 190: else
		//;test_61f13x_IR_Send.C: 191: {
		//;test_61f13x_IR_Send.C: 192: level1 = 1;
		CLRR 	70H 			//0070 	0170
		INCR	70H,1 			//0071 	09F0

		//;test_61f13x_IR_Send.C: 193: level0 = 1;
		CLRR 	71H 			//0072 	0171
		INCR	71H,1 			//0073 	09F1
		ORG		0074H

		//;test_61f13x_IR_Send.C: 194: }
		//;test_61f13x_IR_Send.C: 195: TxTime++;
		INCR	73H,1 			//0074 	09F3

		//;test_61f13x_IR_Send.C: 196: if (TxTime <= level1)
		LDR 	73H,0 			//0075 	0873
		SUBWR 	70H,0 			//0076 	0C70
		BTSS 	STATUS,0 		//0077 	1C03
		LJUMP 	7BH 			//0078 	387B

		//;test_61f13x_IR_Send.C: 197: {
		//;test_61f13x_IR_Send.C: 198: T0IE = 1;
		BSR 	INTCON,5 		//0079 	1A8B

		//;test_61f13x_IR_Send.C: 199: }
		RET		 					//007A 	0004

		//;test_61f13x_IR_Send.C: 200: else if (TxTime <= (level0+level1))
		LDR 	71H,0 			//007B 	0871
		ORG		007CH
		ADDWR 	70H,0 			//007C 	0B70
		STR 	77H 			//007D 	01F7
		CLRR 	78H 			//007E 	0178
		RLR 	78H,1 			//007F 	05F8
		LDR 	78H,0 			//0080 	0878
		XORWI 	80H 			//0081 	2680
		STR 	79H 			//0082 	01F9
		LDWI 	80H 			//0083 	2A80
		ORG		0084H
		SUBWR 	79H,0 			//0084 	0C79
		BTSS 	STATUS,2 		//0085 	1D03
		LJUMP 	89H 			//0086 	3889
		LDR 	73H,0 			//0087 	0873
		SUBWR 	77H,0 			//0088 	0C77
		BTSS 	STATUS,0 		//0089 	1C03
		LJUMP 	8DH 			//008A 	388D

		//;test_61f13x_IR_Send.C: 201: {
		//;test_61f13x_IR_Send.C: 202: T0IE = 0;
		BCR 	INTCON,5 		//008B 	128B
		ORG		008CH

		//;test_61f13x_IR_Send.C: 203: }
		RET		 					//008C 	0004

		//;test_61f13x_IR_Send.C: 204: else if (Sendbit < 4)
		LDWI 	4H 			//008D 	2A04
		SUBWR 	72H,0 			//008E 	0C72
		BTSC 	STATUS,0 		//008F 	1403
		LJUMP 	ADH 			//0090 	38AD

		//;test_61f13x_IR_Send.C: 205: {
		//;test_61f13x_IR_Send.C: 206: TxTime = 1;
		CLRR 	73H 			//0091 	0173
		INCR	73H,1 			//0092 	09F3

		//;test_61f13x_IR_Send.C: 207: T0IE = 1;
		BSR 	INTCON,5 		//0093 	1A8B
		ORG		0094H

		//;test_61f13x_IR_Send.C: 208: SaveLastBit = IRSendData & TxBit;
		LDR 	75H,0 			//0094 	0875
		BCR 	STATUS,5 		//0095 	1283
		BCR 	STATUS,6 		//0096 	1303
		STR 	26H 			//0097 	01A6
		LDR 	74H,0 			//0098 	0874
		ANDWR 	26H,1 			//0099 	02A6

		//;test_61f13x_IR_Send.C: 209: TxBit <<= 1;
		BCR 	STATUS,0 		//009A 	1003
		RLR 	74H,1 			//009B 	05F4
		ORG		009CH

		//;test_61f13x_IR_Send.C: 210: if (TxBit == 0x00)
		LDR 	74H,0 			//009C 	0874
		BTSS 	STATUS,2 		//009D 	1D03
		RET		 					//009E 	0004

		//;test_61f13x_IR_Send.C: 211: {
		//;test_61f13x_IR_Send.C: 212: TxBit = 0x01;
		CLRR 	74H 			//009F 	0174
		INCR	74H,1 			//00A0 	09F4

		//;test_61f13x_IR_Send.C: 213: Sendbit++;
		INCR	72H,1 			//00A1 	09F2

		//;test_61f13x_IR_Send.C: 214: IRSendData = IRData[Sendbit];
		LDR 	72H,0 			//00A2 	0872
		ADDWI 	20H 			//00A3 	2720
		ORG		00A4H
		STR 	FSR 			//00A4 	0184
		BCR 	STATUS,7 		//00A5 	1383
		LDR 	INDF,0 			//00A6 	0800
		STR 	75H 			//00A7 	01F5

		//;test_61f13x_IR_Send.C: 215: if (Sendbit > 3)
		LDWI 	4H 			//00A8 	2A04
		SUBWR 	72H,0 			//00A9 	0C72
		BTSC 	STATUS,0 		//00AA 	1403

		//;test_61f13x_IR_Send.C: 216: {
		//;test_61f13x_IR_Send.C: 217: SendLastBit = 1;
		BSR 	7DH,0 			//00AB 	187D
		ORG		00ACH
		RET		 					//00AC 	0004

		//;test_61f13x_IR_Send.C: 221: else
		//;test_61f13x_IR_Send.C: 222: {
		//;test_61f13x_IR_Send.C: 223: if(SendLastBit)
		BTSS 	7DH,0 			//00AD 	1C7D
		RET		 					//00AE 	0004

		//;test_61f13x_IR_Send.C: 224: {
		//;test_61f13x_IR_Send.C: 225: TxTime++;
		INCR	73H,1 			//00AF 	09F3

		//;test_61f13x_IR_Send.C: 226: if(SaveLastBit)
		BCR 	STATUS,5 		//00B0 	1283
		BCR 	STATUS,6 		//00B1 	1303
		LDR 	26H,0 			//00B2 	0826
		BTSC 	STATUS,2 		//00B3 	1503
		ORG		00B4H
		LJUMP 	C4H 			//00B4 	38C4

		//;test_61f13x_IR_Send.C: 227: {
		//;test_61f13x_IR_Send.C: 228: if(TxTime < 3)
		LDWI 	3H 			//00B5 	2A03
		SUBWR 	73H,0 			//00B6 	0C73
		BTSS 	STATUS,0 		//00B7 	1C03
		LJUMP 	8BH 			//00B8 	388B

		//;test_61f13x_IR_Send.C: 232: else if(TxTime < 4)
		LDWI 	4H 			//00B9 	2A04
		SUBWR 	73H,0 			//00BA 	0C73
		BTSS 	STATUS,0 		//00BB 	1C03
		ORG		00BCH
		LJUMP 	79H 			//00BC 	3879

		//;test_61f13x_IR_Send.C: 236: else
		//;test_61f13x_IR_Send.C: 237: {
		//;test_61f13x_IR_Send.C: 238: T0IE = 0;
		BCR 	INTCON,5 		//00BD 	128B

		//;test_61f13x_IR_Send.C: 239: IRSendStatus = 0;
		CLRR 	76H 			//00BE 	0176

		//;test_61f13x_IR_Send.C: 240: T0IE = 0;
		BCR 	INTCON,5 		//00BF 	128B

		//;test_61f13x_IR_Send.C: 241: SendLastBit = 0;
		BCR 	7DH,0 			//00C0 	107D

		//;test_61f13x_IR_Send.C: 242: TxBit = 0;
		CLRR 	74H 			//00C1 	0174

		//;test_61f13x_IR_Send.C: 243: TxTime = 0;
		CLRR 	73H 			//00C2 	0173
		RET		 					//00C3 	0004
		ORG		00C4H

		//;test_61f13x_IR_Send.C: 246: else
		//;test_61f13x_IR_Send.C: 247: {
		//;test_61f13x_IR_Send.C: 248: if(TxTime < 5)
		LDWI 	5H 			//00C4 	2A05
		SUBWR 	73H,0 			//00C5 	0C73
		BTSS 	STATUS,0 		//00C6 	1C03
		LJUMP 	8BH 			//00C7 	388B

		//;test_61f13x_IR_Send.C: 252: else if(TxTime < 6)
		LDWI 	6H 			//00C8 	2A06
		LJUMP 	BAH 			//00C9 	38BA

		//;test_61f13x_IR_Send.C: 100: T2CON0 = 0B00011001;
		LDWI 	19H 			//00CA 	2A19
		STR 	12H 			//00CB 	0192
		ORG		00CCH

		//;test_61f13x_IR_Send.C: 105: T2CON1 = 0B00000000;
		BSR 	STATUS,5 		//00CC 	1A83
		CLRR 	1EH 			//00CD 	011E

		//;test_61f13x_IR_Send.C: 111: TMR2H = 0;
		BCR 	STATUS,5 		//00CE 	1283
		CLRR 	13H 			//00CF 	0113

		//;test_61f13x_IR_Send.C: 112: TMR2L = 141;
		LDWI 	8DH 			//00D0 	2A8D
		STR 	11H 			//00D1 	0191

		//;test_61f13x_IR_Send.C: 115: PR2H = 0;
		BSR 	STATUS,5 		//00D2 	1A83
		CLRR 	12H 			//00D3 	0112
		ORG		00D4H

		//;test_61f13x_IR_Send.C: 116: PR2L = 141;
		STR 	11H 			//00D4 	0191

		//;test_61f13x_IR_Send.C: 118: P1ADTH = 0;
		BCR 	STATUS,5 		//00D5 	1283
		CLRR 	14H 			//00D6 	0114

		//;test_61f13x_IR_Send.C: 119: P1ADTL = 50;
		LDWI 	32H 			//00D7 	2A32
		STR 	EH 			//00D8 	018E

		//;test_61f13x_IR_Send.C: 121: P1OE=0B00000000;
		BSR 	STATUS,5 		//00D9 	1A83
		CLRR 	10H 			//00DA 	0110

		//;test_61f13x_IR_Send.C: 130: P1CON=0B00000001;
		LDWI 	1H 			//00DB 	2A01
		ORG		00DCH
		BCR 	STATUS,5 		//00DC 	1283
		STR 	16H 			//00DD 	0196

		//;test_61f13x_IR_Send.C: 132: P1POL=0B00000000;
		BSR 	STATUS,5 		//00DE 	1A83
		CLRR 	19H 			//00DF 	0119

		//;test_61f13x_IR_Send.C: 142: TMR2IF = 0;
		BCR 	STATUS,5 		//00E0 	1283
		BCR 	CH,1 			//00E1 	108C

		//;test_61f13x_IR_Send.C: 143: TMR2IE = 1;
		BSR 	STATUS,5 		//00E2 	1A83
		BSR 	CH,1 			//00E3 	188C
		ORG		00E4H

		//;test_61f13x_IR_Send.C: 144: TMR2ON = 1;
		BCR 	STATUS,5 		//00E4 	1283
		BSR 	12H,2 			//00E5 	1912

		//;test_61f13x_IR_Send.C: 145: PEIE = 1;
		BSR 	INTCON,6 		//00E6 	1B0B

		//;test_61f13x_IR_Send.C: 146: GIE = 1;
		BSR 	INTCON,7 		//00E7 	1B8B
		RET		 					//00E8 	0004

		//;test_61f13x_IR_Send.C: 309: POWER_INITIAL();
		BCR 	PCLATH,3 		//00E9 	118A
		LCALL 	FFH 			//00EA 	30FF
		BCR 	PCLATH,3 		//00EB 	118A
		ORG		00ECH

		//;test_61f13x_IR_Send.C: 310: TIMER0_INITIAL();
		BCR 	PCLATH,3 		//00EC 	118A
		LCALL 	111H 			//00ED 	3111
		BCR 	PCLATH,3 		//00EE 	118A

		//;test_61f13x_IR_Send.C: 311: Timer2Inital();
		BCR 	PCLATH,3 		//00EF 	118A
		LCALL 	CAH 			//00F0 	30CA
		BCR 	PCLATH,3 		//00F1 	118A

		//;test_61f13x_IR_Send.C: 312: GIE = 1;
		BSR 	INTCON,7 		//00F2 	1B8B

		//;test_61f13x_IR_Send.C: 314: {
		//;test_61f13x_IR_Send.C: 315: if(SYSTime5S >10000)
		LDWI 	27H 			//00F3 	2A27
		ORG		00F4H
		SUBWR 	25H,0 			//00F4 	0C25
		LDWI 	11H 			//00F5 	2A11
		BTSC 	STATUS,2 		//00F6 	1503
		SUBWR 	24H,0 			//00F7 	0C24
		BTSS 	STATUS,0 		//00F8 	1C03
		LJUMP 	F3H 			//00F9 	38F3

		//;test_61f13x_IR_Send.C: 316: {
		//;test_61f13x_IR_Send.C: 317: SYSTime5S = 0;
		CLRR 	24H 			//00FA 	0124
		CLRR 	25H 			//00FB 	0125
		ORG		00FCH

		//;test_61f13x_IR_Send.C: 318: IRSendStatus = 1;
		CLRR 	76H 			//00FC 	0176
		INCR	76H,1 			//00FD 	09F6
		LJUMP 	F3H 			//00FE 	38F3

		//;test_61f13x_IR_Send.C: 65: OSCCON = 0B01110001;
		LDWI 	71H 			//00FF 	2A71
		BSR 	STATUS,5 		//0100 	1A83
		STR 	FH 			//0101 	018F

		//;test_61f13x_IR_Send.C: 66: OPTION = 0B00001000;
		LDWI 	8H 			//0102 	2A08
		STR 	1H 			//0103 	0181
		ORG		0104H

		//;test_61f13x_IR_Send.C: 67: INTCON = 0;
		CLRR 	INTCON 			//0104 	010B

		//;test_61f13x_IR_Send.C: 68: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0105 	1283
		CLRR 	5H 			//0106 	0105

		//;test_61f13x_IR_Send.C: 69: TRISA = 0B00000010;
		LDWI 	2H 			//0107 	2A02
		BSR 	STATUS,5 		//0108 	1A83
		STR 	5H 			//0109 	0185

		//;test_61f13x_IR_Send.C: 71: PORTC = 0B00000000;
		BCR 	STATUS,5 		//010A 	1283
		CLRR 	7H 			//010B 	0107
		ORG		010CH

		//;test_61f13x_IR_Send.C: 72: TRISC = 0B00000000;
		BSR 	STATUS,5 		//010C 	1A83
		CLRR 	7H 			//010D 	0107

		//;test_61f13x_IR_Send.C: 74: WPUA = 0B00000010;
		STR 	15H 			//010E 	0195

		//;test_61f13x_IR_Send.C: 76: WPUC = 0B00000000;
		CLRR 	13H 			//010F 	0113
		RET		 					//0110 	0004

		//;test_61f13x_IR_Send.C: 87: OPTION = 0B00000000;
		CLRR 	1H 			//0111 	0101

		//;test_61f13x_IR_Send.C: 88: TMR0 = 239;
		LDWI 	EFH 			//0112 	2AEF
		BCR 	STATUS,5 		//0113 	1283
		ORG		0114H
		STR 	1H 			//0114 	0181

		//;test_61f13x_IR_Send.C: 89: T0IF = 0;
		BCR 	INTCON,2 		//0115 	110B
		RET		 					//0116 	0004
			END
