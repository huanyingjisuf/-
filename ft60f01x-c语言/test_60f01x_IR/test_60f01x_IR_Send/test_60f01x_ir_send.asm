//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_IRSendStatus		EQU		76H
		_IRSendData		EQU		75H
		_TxBit		EQU		74H
		_TxTime		EQU		73H
		_Sendbit		EQU		72H
		_level0		EQU		71H
		_level1		EQU		70H
		_SendLastBit		EQU		7DH
		_SaveLastBit		EQU		46H
		_SYSTime5S		EQU		44H
		_IRData		EQU		40H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0CH 			//0000 	380C
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	7AH 			//0006 	01FA
		LDR 	FSR,0 			//0007 	0804
		STR 	7BH 			//0008 	01FB
		LDR 	PCLATH,0 		//0009 	080A
		STR 	7CH 			//000A 	01FC
		LJUMP 	A4H 			//000B 	38A4
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		LDWI 	FFH 			//000D 	2AFF
		CLRR 	40H 			//000E 	0140
		STR 	41H 			//000F 	01C1
		LDWI 	40H 			//0010 	2A40
		STR 	42H 			//0011 	01C2
		LDWI 	BFH 			//0012 	2ABF
		STR 	43H 			//0013 	01C3
		ORG		0014H
		CLRR 	44H 			//0014 	0144
		CLRR 	45H 			//0015 	0145
		CLRR 	46H 			//0016 	0146
		CLRR 	70H 			//0017 	0170
		CLRR 	71H 			//0018 	0171
		CLRR 	72H 			//0019 	0172
		CLRR 	73H 			//001A 	0173
		CLRR 	74H 			//001B 	0174
		ORG		001CH
		CLRR 	75H 			//001C 	0175
		CLRR 	76H 			//001D 	0176
		CLRR 	7DH 			//001E 	017D
		CLRR 	STATUS 			//001F 	0103
		LJUMP 	C3H 			//0020 	38C3

		//;test_60f01x_IR_Send.C: 118: if (IRSendStatus == 0)
		LDR 	76H,0 			//0021 	0876
		BTSS 	STATUS,2 		//0022 	1D03
		LJUMP 	28H 			//0023 	3828
		ORG		0024H

		//;test_60f01x_IR_Send.C: 119: {
		//;test_60f01x_IR_Send.C: 120: T0IE = 0;
		BCR 	INTCON,5 		//0024 	128B

		//;test_60f01x_IR_Send.C: 121: Sendbit = 0;
		CLRR 	72H 			//0025 	0172

		//;test_60f01x_IR_Send.C: 122: TxTime = 0;
		CLRR 	73H 			//0026 	0173

		//;test_60f01x_IR_Send.C: 123: }
		RET		 					//0027 	0004

		//;test_60f01x_IR_Send.C: 124: else if (IRSendStatus == 1)
		DECRSZ 	76H,0 		//0028 	0E76
		LJUMP 	3FH 			//0029 	383F
		LDWI 	11H 			//002A 	2A11

		//;test_60f01x_IR_Send.C: 125: {
		//;test_60f01x_IR_Send.C: 126: TxTime++;
		INCR	73H,1 			//002B 	09F3
		ORG		002CH

		//;test_60f01x_IR_Send.C: 127: if (TxTime < 17)
		SUBWR 	73H,0 			//002C 	0C73
		BTSC 	STATUS,0 		//002D 	1403
		LJUMP 	31H 			//002E 	3831

		//;test_60f01x_IR_Send.C: 128: {
		//;test_60f01x_IR_Send.C: 129: T0IE = 1;
		BSR 	INTCON,5 		//002F 	1A8B

		//;test_60f01x_IR_Send.C: 130: }
		LJUMP 	3AH 			//0030 	383A

		//;test_60f01x_IR_Send.C: 131: else if (TxTime < 24)
		LDWI 	18H 			//0031 	2A18
		SUBWR 	73H,0 			//0032 	0C73
		BTSC 	STATUS,0 		//0033 	1403
		ORG		0034H
		LJUMP 	37H 			//0034 	3837

		//;test_60f01x_IR_Send.C: 132: {
		//;test_60f01x_IR_Send.C: 133: T0IE = 0;
		BCR 	INTCON,5 		//0035 	128B

		//;test_60f01x_IR_Send.C: 134: }
		LJUMP 	3AH 			//0036 	383A
		LDWI 	2H 			//0037 	2A02

		//;test_60f01x_IR_Send.C: 135: else
		//;test_60f01x_IR_Send.C: 136: {
		//;test_60f01x_IR_Send.C: 137: TxTime = 0;
		CLRR 	73H 			//0038 	0173

		//;test_60f01x_IR_Send.C: 138: IRSendStatus = 2;
		STR 	76H 			//0039 	01F6

		//;test_60f01x_IR_Send.C: 139: }
		//;test_60f01x_IR_Send.C: 140: IRSendData = IRData[0];
		LDR 	40H,0 			//003A 	0840
		STR 	75H 			//003B 	01F5
		ORG		003CH

		//;test_60f01x_IR_Send.C: 141: TxBit = 0x01;
		CLRR 	74H 			//003C 	0174
		INCR	74H,1 			//003D 	09F4

		//;test_60f01x_IR_Send.C: 142: }
		RET		 					//003E 	0004

		//;test_60f01x_IR_Send.C: 143: else if(IRSendStatus == 2)
		LDWI 	2H 			//003F 	2A02
		XORWR 	76H,0 			//0040 	0476
		BTSS 	STATUS,2 		//0041 	1D03
		RET		 					//0042 	0004

		//;test_60f01x_IR_Send.C: 144: {
		//;test_60f01x_IR_Send.C: 145: if (IRSendData & TxBit)
		LDR 	75H,0 			//0043 	0875
		ORG		0044H
		ANDWR 	74H,0 			//0044 	0274
		BTSC 	STATUS,2 		//0045 	1503
		LJUMP 	4CH 			//0046 	384C
		LDWI 	3H 			//0047 	2A03

		//;test_60f01x_IR_Send.C: 146: {
		//;test_60f01x_IR_Send.C: 147: level1 = 1;
		CLRR 	70H 			//0048 	0170
		INCR	70H,1 			//0049 	09F0

		//;test_60f01x_IR_Send.C: 148: level0 = 3;
		STR 	71H 			//004A 	01F1

		//;test_60f01x_IR_Send.C: 150: }
		LJUMP 	50H 			//004B 	3850
		ORG		004CH

		//;test_60f01x_IR_Send.C: 151: else
		//;test_60f01x_IR_Send.C: 152: {
		//;test_60f01x_IR_Send.C: 153: level1 = 1;
		CLRR 	70H 			//004C 	0170
		INCR	70H,1 			//004D 	09F0

		//;test_60f01x_IR_Send.C: 154: level0 = 1;
		CLRR 	71H 			//004E 	0171
		INCR	71H,1 			//004F 	09F1

		//;test_60f01x_IR_Send.C: 155: }
		//;test_60f01x_IR_Send.C: 156: TxTime++;
		INCR	73H,1 			//0050 	09F3

		//;test_60f01x_IR_Send.C: 157: if (TxTime <= level1)
		LDR 	73H,0 			//0051 	0873
		SUBWR 	70H,0 			//0052 	0C70
		BTSS 	STATUS,0 		//0053 	1C03
		ORG		0054H
		LJUMP 	57H 			//0054 	3857

		//;test_60f01x_IR_Send.C: 158: {
		//;test_60f01x_IR_Send.C: 159: T0IE = 1;
		BSR 	INTCON,5 		//0055 	1A8B

		//;test_60f01x_IR_Send.C: 160: }
		RET		 					//0056 	0004

		//;test_60f01x_IR_Send.C: 161: else if (TxTime <= (level0+level1))
		LDR 	71H,0 			//0057 	0871
		ADDWR 	70H,0 			//0058 	0B70
		STR 	77H 			//0059 	01F7
		CLRR 	78H 			//005A 	0178
		RLR 	78H,1 			//005B 	05F8
		ORG		005CH
		LDR 	78H,0 			//005C 	0878
		XORWI 	80H 			//005D 	2680
		STR 	79H 			//005E 	01F9
		LDWI 	80H 			//005F 	2A80
		SUBWR 	79H,0 			//0060 	0C79
		BTSS 	STATUS,2 		//0061 	1D03
		LJUMP 	65H 			//0062 	3865
		LDR 	73H,0 			//0063 	0873
		ORG		0064H
		SUBWR 	77H,0 			//0064 	0C77
		BTSS 	STATUS,0 		//0065 	1C03
		LJUMP 	69H 			//0066 	3869

		//;test_60f01x_IR_Send.C: 162: {
		//;test_60f01x_IR_Send.C: 163: T0IE = 0;
		BCR 	INTCON,5 		//0067 	128B

		//;test_60f01x_IR_Send.C: 164: }
		RET		 					//0068 	0004

		//;test_60f01x_IR_Send.C: 165: else if (Sendbit < 4)
		LDWI 	4H 			//0069 	2A04
		SUBWR 	72H,0 			//006A 	0C72
		BTSC 	STATUS,0 		//006B 	1403
		ORG		006CH
		LJUMP 	88H 			//006C 	3888

		//;test_60f01x_IR_Send.C: 166: {
		//;test_60f01x_IR_Send.C: 167: TxTime = 1;
		CLRR 	73H 			//006D 	0173
		INCR	73H,1 			//006E 	09F3

		//;test_60f01x_IR_Send.C: 168: T0IE = 1;
		BSR 	INTCON,5 		//006F 	1A8B

		//;test_60f01x_IR_Send.C: 169: SaveLastBit = IRSendData & TxBit;
		LDR 	75H,0 			//0070 	0875
		BCR 	STATUS,5 		//0071 	1283
		STR 	46H 			//0072 	01C6
		LDR 	74H,0 			//0073 	0874
		ORG		0074H
		ANDWR 	46H,1 			//0074 	02C6

		//;test_60f01x_IR_Send.C: 170: TxBit <<= 1;
		BCR 	STATUS,0 		//0075 	1003
		RLR 	74H,1 			//0076 	05F4

		//;test_60f01x_IR_Send.C: 171: if (TxBit == 0x00)
		LDR 	74H,0 			//0077 	0874
		BTSS 	STATUS,2 		//0078 	1D03
		RET		 					//0079 	0004

		//;test_60f01x_IR_Send.C: 172: {
		//;test_60f01x_IR_Send.C: 173: TxBit = 0x01;
		CLRR 	74H 			//007A 	0174
		INCR	74H,1 			//007B 	09F4
		ORG		007CH

		//;test_60f01x_IR_Send.C: 174: Sendbit++;
		INCR	72H,1 			//007C 	09F2

		//;test_60f01x_IR_Send.C: 175: IRSendData = IRData[Sendbit];
		LDR 	72H,0 			//007D 	0872
		ADDWI 	40H 			//007E 	2740
		STR 	FSR 			//007F 	0184
		BCR 	STATUS,7 		//0080 	1383
		LDR 	INDF,0 			//0081 	0800
		STR 	75H 			//0082 	01F5

		//;test_60f01x_IR_Send.C: 176: if (Sendbit > 3)
		LDWI 	4H 			//0083 	2A04
		ORG		0084H
		SUBWR 	72H,0 			//0084 	0C72
		BTSC 	STATUS,0 		//0085 	1403

		//;test_60f01x_IR_Send.C: 177: {
		//;test_60f01x_IR_Send.C: 178: SendLastBit = 1;
		BSR 	7DH,0 			//0086 	187D
		RET		 					//0087 	0004

		//;test_60f01x_IR_Send.C: 182: else
		//;test_60f01x_IR_Send.C: 183: {
		//;test_60f01x_IR_Send.C: 184: if(SendLastBit)
		BTSS 	7DH,0 			//0088 	1C7D
		RET		 					//0089 	0004

		//;test_60f01x_IR_Send.C: 185: {
		//;test_60f01x_IR_Send.C: 186: TxTime++;
		INCR	73H,1 			//008A 	09F3

		//;test_60f01x_IR_Send.C: 187: if(SaveLastBit)
		BCR 	STATUS,5 		//008B 	1283
		ORG		008CH
		LDR 	46H,0 			//008C 	0846
		BTSC 	STATUS,2 		//008D 	1503
		LJUMP 	9EH 			//008E 	389E

		//;test_60f01x_IR_Send.C: 188: {
		//;test_60f01x_IR_Send.C: 189: if(TxTime < 3)
		LDWI 	3H 			//008F 	2A03
		SUBWR 	73H,0 			//0090 	0C73
		BTSS 	STATUS,0 		//0091 	1C03
		LJUMP 	67H 			//0092 	3867

		//;test_60f01x_IR_Send.C: 193: else if(TxTime < 4)
		LDWI 	4H 			//0093 	2A04
		ORG		0094H
		SUBWR 	73H,0 			//0094 	0C73
		BTSS 	STATUS,0 		//0095 	1C03
		LJUMP 	55H 			//0096 	3855

		//;test_60f01x_IR_Send.C: 197: else
		//;test_60f01x_IR_Send.C: 198: {
		//;test_60f01x_IR_Send.C: 199: T0IE = 0;
		BCR 	INTCON,5 		//0097 	128B

		//;test_60f01x_IR_Send.C: 200: IRSendStatus = 0;
		CLRR 	76H 			//0098 	0176

		//;test_60f01x_IR_Send.C: 201: T0IE = 0;
		BCR 	INTCON,5 		//0099 	128B

		//;test_60f01x_IR_Send.C: 202: SendLastBit = 0;
		BCR 	7DH,0 			//009A 	107D

		//;test_60f01x_IR_Send.C: 203: TxBit = 0;
		CLRR 	74H 			//009B 	0174
		ORG		009CH

		//;test_60f01x_IR_Send.C: 204: TxTime = 0;
		CLRR 	73H 			//009C 	0173
		RET		 					//009D 	0004

		//;test_60f01x_IR_Send.C: 207: else
		//;test_60f01x_IR_Send.C: 208: {
		//;test_60f01x_IR_Send.C: 209: if(TxTime < 5)
		LDWI 	5H 			//009E 	2A05
		SUBWR 	73H,0 			//009F 	0C73
		BTSS 	STATUS,0 		//00A0 	1C03
		LJUMP 	67H 			//00A1 	3867

		//;test_60f01x_IR_Send.C: 213: else if(TxTime < 6)
		LDWI 	6H 			//00A2 	2A06
		LJUMP 	94H 			//00A3 	3894
		ORG		00A4H

		//;test_60f01x_IR_Send.C: 240: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//00A4 	168B
		BTSS 	INTCON,2 		//00A5 	1D0B
		LJUMP 	ADH 			//00A6 	38AD

		//;test_60f01x_IR_Send.C: 241: {
		//;test_60f01x_IR_Send.C: 242: TMR0 = 239;
		LDWI 	EFH 			//00A7 	2AEF
		BCR 	STATUS,5 		//00A8 	1283
		STR 	1H 			//00A9 	0181

		//;test_60f01x_IR_Send.C: 243: T0IF = 0;
		BCR 	INTCON,2 		//00AA 	110B

		//;test_60f01x_IR_Send.C: 244: PA4 = ~PA4;
		LDWI 	10H 			//00AB 	2A10
		ORG		00ACH
		XORWR 	5H,1 			//00AC 	0485

		//;test_60f01x_IR_Send.C: 245: }
		//;test_60f01x_IR_Send.C: 248: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//00AD 	1A83
		BTSS 	CH,1 			//00AE 	1C8C
		LJUMP 	BAH 			//00AF 	38BA
		BCR 	STATUS,5 		//00B0 	1283
		BTSS 	CH,1 			//00B1 	1C8C
		LJUMP 	BAH 			//00B2 	38BA

		//;test_60f01x_IR_Send.C: 249: {
		//;test_60f01x_IR_Send.C: 250: TMR2IF = 0;
		BCR 	CH,1 			//00B3 	108C
		ORG		00B4H

		//;test_60f01x_IR_Send.C: 251: SendCtrl();
		LCALL 	21H 			//00B4 	3021

		//;test_60f01x_IR_Send.C: 252: SYSTime5S++;
		BCR 	STATUS,5 		//00B5 	1283
		INCR	44H,1 			//00B6 	09C4
		BTSC 	STATUS,2 		//00B7 	1503
		INCR	45H,1 			//00B8 	09C5

		//;test_60f01x_IR_Send.C: 253: PA4 = 0;
		BCR 	5H,4 			//00B9 	1205
		LDR 	7CH,0 			//00BA 	087C
		STR 	PCLATH 			//00BB 	018A
		ORG		00BCH
		LDR 	7BH,0 			//00BC 	087B
		STR 	FSR 			//00BD 	0184
		SWAPR 	7AH,0 			//00BE 	077A
		STR 	STATUS 			//00BF 	0183
		SWAPR 	7EH,1 			//00C0 	07FE
		SWAPR 	7EH,0 			//00C1 	077E
		RETI		 			//00C2 	0009

		//;test_60f01x_IR_Send.C: 264: POWER_INITIAL();
		LCALL 	E1H 			//00C3 	30E1
		ORG		00C4H

		//;test_60f01x_IR_Send.C: 265: TIMER0_INITIAL();
		LCALL 	EFH 			//00C4 	30EF

		//;test_60f01x_IR_Send.C: 266: TIMER2_INITIAL();
		LCALL 	D3H 			//00C5 	30D3

		//;test_60f01x_IR_Send.C: 267: GIE = 1;
		BSR 	INTCON,7 		//00C6 	1B8B

		//;test_60f01x_IR_Send.C: 269: {
		//;test_60f01x_IR_Send.C: 270: if(SYSTime5S >10000)
		LDWI 	27H 			//00C7 	2A27
		SUBWR 	45H,0 			//00C8 	0C45
		LDWI 	11H 			//00C9 	2A11
		BTSC 	STATUS,2 		//00CA 	1503
		SUBWR 	44H,0 			//00CB 	0C44
		ORG		00CCH
		BTSS 	STATUS,0 		//00CC 	1C03
		LJUMP 	C7H 			//00CD 	38C7

		//;test_60f01x_IR_Send.C: 271: {
		//;test_60f01x_IR_Send.C: 272: SYSTime5S = 0;
		CLRR 	44H 			//00CE 	0144
		CLRR 	45H 			//00CF 	0145

		//;test_60f01x_IR_Send.C: 273: IRSendStatus = 1;
		CLRR 	76H 			//00D0 	0176
		INCR	76H,1 			//00D1 	09F6
		LJUMP 	C7H 			//00D2 	38C7

		//;test_60f01x_IR_Send.C: 97: T2CON = 0B00011001;
		LDWI 	19H 			//00D3 	2A19
		ORG		00D4H
		STR 	12H 			//00D4 	0192

		//;test_60f01x_IR_Send.C: 101: TMR2 = 0;
		CLRR 	11H 			//00D5 	0111

		//;test_60f01x_IR_Send.C: 102: PR2 = 140;
		LDWI 	8CH 			//00D6 	2A8C
		BSR 	STATUS,5 		//00D7 	1A83
		STR 	12H 			//00D8 	0192

		//;test_60f01x_IR_Send.C: 104: TMR2IF = 0;
		BCR 	STATUS,5 		//00D9 	1283
		BCR 	CH,1 			//00DA 	108C

		//;test_60f01x_IR_Send.C: 105: TMR2IE = 1;
		BSR 	STATUS,5 		//00DB 	1A83
		ORG		00DCH
		BSR 	CH,1 			//00DC 	188C

		//;test_60f01x_IR_Send.C: 106: TMR2ON = 1;
		BCR 	STATUS,5 		//00DD 	1283
		BSR 	12H,2 			//00DE 	1912

		//;test_60f01x_IR_Send.C: 107: PEIE=1;
		BSR 	INTCON,6 		//00DF 	1B0B
		RET		 					//00E0 	0004

		//;test_60f01x_IR_Send.C: 57: OSCCON = 0B01110000;
		LDWI 	70H 			//00E1 	2A70
		BSR 	STATUS,5 		//00E2 	1A83
		STR 	FH 			//00E3 	018F
		ORG		00E4H

		//;test_60f01x_IR_Send.C: 58: INTCON = 0;
		CLRR 	INTCON 			//00E4 	010B

		//;test_60f01x_IR_Send.C: 59: OPTION = 0B00001000;
		LDWI 	8H 			//00E5 	2A08
		STR 	1H 			//00E6 	0181

		//;test_60f01x_IR_Send.C: 61: PORTA = 0B00000000;
		BCR 	STATUS,5 		//00E7 	1283
		CLRR 	5H 			//00E8 	0105

		//;test_60f01x_IR_Send.C: 62: TRISA = 0B00000000;
		BSR 	STATUS,5 		//00E9 	1A83
		CLRR 	5H 			//00EA 	0105

		//;test_60f01x_IR_Send.C: 64: WPUA = 0B00000000;
		CLRR 	15H 			//00EB 	0115
		ORG		00ECH

		//;test_60f01x_IR_Send.C: 65: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//00EC 	1283
		CLRR 	1BH 			//00ED 	011B
		RET		 					//00EE 	0004

		//;test_60f01x_IR_Send.C: 80: OPTION = 0B00000000;
		BSR 	STATUS,5 		//00EF 	1A83
		CLRR 	1H 			//00F0 	0101

		//;test_60f01x_IR_Send.C: 86: TMR0 = 239;
		LDWI 	EFH 			//00F1 	2AEF
		BCR 	STATUS,5 		//00F2 	1283
		STR 	1H 			//00F3 	0181
		ORG		00F4H

		//;test_60f01x_IR_Send.C: 87: T0IF = 0;
		BCR 	INTCON,2 		//00F4 	110B
		RET		 					//00F5 	0004
			END
