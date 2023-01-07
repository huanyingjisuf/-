//Deviec:FT61F02X
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
		LJUMP 	0CH 			//0000 	380C
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	7AH 			//0006 	01FA
		LDR 	FSR,0 			//0007 	0804
		STR 	7BH 			//0008 	01FB
		LDR 	PCLATH,0 		//0009 	080A
		STR 	7CH 			//000A 	01FC
		LJUMP 	A6H 			//000B 	38A6
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		LDWI 	FFH 			//000D 	2AFF
		CLRR 	20H 			//000E 	0120
		STR 	21H 			//000F 	01A1
		LDWI 	40H 			//0010 	2A40
		STR 	22H 			//0011 	01A2
		LDWI 	BFH 			//0012 	2ABF
		STR 	23H 			//0013 	01A3
		ORG		0014H
		CLRR 	24H 			//0014 	0124
		CLRR 	25H 			//0015 	0125
		CLRR 	26H 			//0016 	0126
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
		LJUMP 	DCH 			//0020 	38DC

		//;test_61f02x_IR_Send.C: 129: if (IRSendStatus == 0)
		LDR 	76H,0 			//0021 	0876
		BTSS 	STATUS,2 		//0022 	1D03
		LJUMP 	28H 			//0023 	3828
		ORG		0024H

		//;test_61f02x_IR_Send.C: 130: {
		//;test_61f02x_IR_Send.C: 131: T0IE = 0;
		BCR 	INTCON,5 		//0024 	128B

		//;test_61f02x_IR_Send.C: 132: Sendbit = 0;
		CLRR 	72H 			//0025 	0172

		//;test_61f02x_IR_Send.C: 133: TxTime = 0;
		CLRR 	73H 			//0026 	0173

		//;test_61f02x_IR_Send.C: 135: }
		RET		 					//0027 	0004

		//;test_61f02x_IR_Send.C: 136: else if (IRSendStatus == 1)
		DECRSZ 	76H,0 		//0028 	0E76
		LJUMP 	3FH 			//0029 	383F
		LDWI 	11H 			//002A 	2A11

		//;test_61f02x_IR_Send.C: 137: {
		//;test_61f02x_IR_Send.C: 138: TxTime++;
		INCR	73H,1 			//002B 	09F3
		ORG		002CH

		//;test_61f02x_IR_Send.C: 139: if (TxTime < 17)
		SUBWR 	73H,0 			//002C 	0C73
		BTSC 	STATUS,0 		//002D 	1403
		LJUMP 	31H 			//002E 	3831

		//;test_61f02x_IR_Send.C: 140: {
		//;test_61f02x_IR_Send.C: 141: T0IE = 1;
		BSR 	INTCON,5 		//002F 	1A8B

		//;test_61f02x_IR_Send.C: 142: }
		LJUMP 	3AH 			//0030 	383A

		//;test_61f02x_IR_Send.C: 143: else if (TxTime < 24)
		LDWI 	18H 			//0031 	2A18
		SUBWR 	73H,0 			//0032 	0C73
		BTSC 	STATUS,0 		//0033 	1403
		ORG		0034H
		LJUMP 	37H 			//0034 	3837

		//;test_61f02x_IR_Send.C: 144: {
		//;test_61f02x_IR_Send.C: 145: T0IE = 0;
		BCR 	INTCON,5 		//0035 	128B

		//;test_61f02x_IR_Send.C: 146: }
		LJUMP 	3AH 			//0036 	383A
		LDWI 	2H 			//0037 	2A02

		//;test_61f02x_IR_Send.C: 147: else
		//;test_61f02x_IR_Send.C: 148: {
		//;test_61f02x_IR_Send.C: 149: TxTime = 0;
		CLRR 	73H 			//0038 	0173

		//;test_61f02x_IR_Send.C: 150: IRSendStatus = 2;
		STR 	76H 			//0039 	01F6

		//;test_61f02x_IR_Send.C: 151: }
		//;test_61f02x_IR_Send.C: 152: IRSendData = IRData[0];
		LDR 	20H,0 			//003A 	0820
		STR 	75H 			//003B 	01F5
		ORG		003CH

		//;test_61f02x_IR_Send.C: 153: TxBit = 0x01;
		CLRR 	74H 			//003C 	0174
		INCR	74H,1 			//003D 	09F4

		//;test_61f02x_IR_Send.C: 154: }
		RET		 					//003E 	0004

		//;test_61f02x_IR_Send.C: 155: else if(IRSendStatus == 2)
		LDWI 	2H 			//003F 	2A02
		XORWR 	76H,0 			//0040 	0476
		BTSS 	STATUS,2 		//0041 	1D03
		RET		 					//0042 	0004

		//;test_61f02x_IR_Send.C: 156: {
		//;test_61f02x_IR_Send.C: 157: if (IRSendData & TxBit)
		LDR 	75H,0 			//0043 	0875
		ORG		0044H
		ANDWR 	74H,0 			//0044 	0274
		BTSC 	STATUS,2 		//0045 	1503
		LJUMP 	4CH 			//0046 	384C
		LDWI 	3H 			//0047 	2A03

		//;test_61f02x_IR_Send.C: 158: {
		//;test_61f02x_IR_Send.C: 159: level1 = 1;
		CLRR 	70H 			//0048 	0170
		INCR	70H,1 			//0049 	09F0

		//;test_61f02x_IR_Send.C: 160: level0 = 3;
		STR 	71H 			//004A 	01F1

		//;test_61f02x_IR_Send.C: 161: }
		LJUMP 	50H 			//004B 	3850
		ORG		004CH

		//;test_61f02x_IR_Send.C: 162: else
		//;test_61f02x_IR_Send.C: 163: {
		//;test_61f02x_IR_Send.C: 164: level1 = 1;
		CLRR 	70H 			//004C 	0170
		INCR	70H,1 			//004D 	09F0

		//;test_61f02x_IR_Send.C: 165: level0 = 1;
		CLRR 	71H 			//004E 	0171
		INCR	71H,1 			//004F 	09F1

		//;test_61f02x_IR_Send.C: 166: }
		//;test_61f02x_IR_Send.C: 167: TxTime++;
		INCR	73H,1 			//0050 	09F3

		//;test_61f02x_IR_Send.C: 168: if (TxTime <= level1)
		LDR 	73H,0 			//0051 	0873
		SUBWR 	70H,0 			//0052 	0C70
		BTSS 	STATUS,0 		//0053 	1C03
		ORG		0054H
		LJUMP 	57H 			//0054 	3857

		//;test_61f02x_IR_Send.C: 169: {
		//;test_61f02x_IR_Send.C: 170: T0IE = 1;
		BSR 	INTCON,5 		//0055 	1A8B

		//;test_61f02x_IR_Send.C: 171: }
		RET		 					//0056 	0004

		//;test_61f02x_IR_Send.C: 172: else if (TxTime <= (level0+level1))
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

		//;test_61f02x_IR_Send.C: 173: {
		//;test_61f02x_IR_Send.C: 174: T0IE = 0;
		BCR 	INTCON,5 		//0067 	128B

		//;test_61f02x_IR_Send.C: 175: }
		RET		 					//0068 	0004

		//;test_61f02x_IR_Send.C: 176: else if (Sendbit < 4)
		LDWI 	4H 			//0069 	2A04
		SUBWR 	72H,0 			//006A 	0C72
		BTSC 	STATUS,0 		//006B 	1403
		ORG		006CH
		LJUMP 	89H 			//006C 	3889

		//;test_61f02x_IR_Send.C: 177: {
		//;test_61f02x_IR_Send.C: 178: TxTime = 1;
		CLRR 	73H 			//006D 	0173
		INCR	73H,1 			//006E 	09F3

		//;test_61f02x_IR_Send.C: 179: T0IE = 1;
		BSR 	INTCON,5 		//006F 	1A8B

		//;test_61f02x_IR_Send.C: 180: SaveLastBit = IRSendData & TxBit;
		LDR 	75H,0 			//0070 	0875
		BCR 	STATUS,5 		//0071 	1283
		BCR 	STATUS,6 		//0072 	1303
		STR 	26H 			//0073 	01A6
		ORG		0074H
		LDR 	74H,0 			//0074 	0874
		ANDWR 	26H,1 			//0075 	02A6

		//;test_61f02x_IR_Send.C: 181: TxBit <<= 1;
		BCR 	STATUS,0 		//0076 	1003
		RLR 	74H,1 			//0077 	05F4

		//;test_61f02x_IR_Send.C: 182: if (TxBit == 0x00)
		LDR 	74H,0 			//0078 	0874
		BTSS 	STATUS,2 		//0079 	1D03
		RET		 					//007A 	0004

		//;test_61f02x_IR_Send.C: 183: {
		//;test_61f02x_IR_Send.C: 184: TxBit = 0x01;
		CLRR 	74H 			//007B 	0174
		ORG		007CH
		INCR	74H,1 			//007C 	09F4

		//;test_61f02x_IR_Send.C: 185: Sendbit++;
		INCR	72H,1 			//007D 	09F2

		//;test_61f02x_IR_Send.C: 186: IRSendData = IRData[Sendbit];
		LDR 	72H,0 			//007E 	0872
		ADDWI 	20H 			//007F 	2720
		STR 	FSR 			//0080 	0184
		BCR 	STATUS,7 		//0081 	1383
		LDR 	INDF,0 			//0082 	0800
		STR 	75H 			//0083 	01F5
		ORG		0084H

		//;test_61f02x_IR_Send.C: 187: if (Sendbit > 3)
		LDWI 	4H 			//0084 	2A04
		SUBWR 	72H,0 			//0085 	0C72
		BTSC 	STATUS,0 		//0086 	1403

		//;test_61f02x_IR_Send.C: 188: {
		//;test_61f02x_IR_Send.C: 189: SendLastBit = 1;
		BSR 	7DH,0 			//0087 	187D
		RET		 					//0088 	0004

		//;test_61f02x_IR_Send.C: 193: else
		//;test_61f02x_IR_Send.C: 194: {
		//;test_61f02x_IR_Send.C: 195: if(SendLastBit)
		BTSS 	7DH,0 			//0089 	1C7D
		RET		 					//008A 	0004

		//;test_61f02x_IR_Send.C: 196: {
		//;test_61f02x_IR_Send.C: 197: TxTime++;
		INCR	73H,1 			//008B 	09F3
		ORG		008CH

		//;test_61f02x_IR_Send.C: 198: if(SaveLastBit)
		BCR 	STATUS,5 		//008C 	1283
		BCR 	STATUS,6 		//008D 	1303
		LDR 	26H,0 			//008E 	0826
		BTSC 	STATUS,2 		//008F 	1503
		LJUMP 	A0H 			//0090 	38A0

		//;test_61f02x_IR_Send.C: 199: {
		//;test_61f02x_IR_Send.C: 200: if(TxTime < 3)
		LDWI 	3H 			//0091 	2A03
		SUBWR 	73H,0 			//0092 	0C73
		BTSS 	STATUS,0 		//0093 	1C03
		ORG		0094H
		LJUMP 	67H 			//0094 	3867

		//;test_61f02x_IR_Send.C: 204: else if(TxTime < 4)
		LDWI 	4H 			//0095 	2A04
		SUBWR 	73H,0 			//0096 	0C73
		BTSS 	STATUS,0 		//0097 	1C03
		LJUMP 	55H 			//0098 	3855

		//;test_61f02x_IR_Send.C: 208: else
		//;test_61f02x_IR_Send.C: 209: {
		//;test_61f02x_IR_Send.C: 210: T0IE = 0;
		BCR 	INTCON,5 		//0099 	128B

		//;test_61f02x_IR_Send.C: 211: IRSendStatus = 0;
		CLRR 	76H 			//009A 	0176

		//;test_61f02x_IR_Send.C: 212: T0IE = 0;
		BCR 	INTCON,5 		//009B 	128B
		ORG		009CH

		//;test_61f02x_IR_Send.C: 213: SendLastBit = 0;
		BCR 	7DH,0 			//009C 	107D

		//;test_61f02x_IR_Send.C: 214: TxBit = 0;
		CLRR 	74H 			//009D 	0174

		//;test_61f02x_IR_Send.C: 215: TxTime = 0;
		CLRR 	73H 			//009E 	0173
		RET		 					//009F 	0004

		//;test_61f02x_IR_Send.C: 218: else
		//;test_61f02x_IR_Send.C: 219: {
		//;test_61f02x_IR_Send.C: 220: if(TxTime < 5)
		LDWI 	5H 			//00A0 	2A05
		SUBWR 	73H,0 			//00A1 	0C73
		BTSS 	STATUS,0 		//00A2 	1C03
		LJUMP 	67H 			//00A3 	3867
		ORG		00A4H

		//;test_61f02x_IR_Send.C: 224: else if(TxTime < 6)
		LDWI 	6H 			//00A4 	2A06
		LJUMP 	96H 			//00A5 	3896

		//;test_61f02x_IR_Send.C: 253: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//00A6 	168B
		BTSS 	INTCON,2 		//00A7 	1D0B
		LJUMP 	B0H 			//00A8 	38B0

		//;test_61f02x_IR_Send.C: 254: {
		//;test_61f02x_IR_Send.C: 255: TMR0 = 239;
		LDWI 	EFH 			//00A9 	2AEF
		BCR 	STATUS,5 		//00AA 	1283
		BCR 	STATUS,6 		//00AB 	1303
		ORG		00ACH
		STR 	1H 			//00AC 	0181

		//;test_61f02x_IR_Send.C: 256: T0IF = 0;
		BCR 	INTCON,2 		//00AD 	110B

		//;test_61f02x_IR_Send.C: 257: PA4 = ~PA4;
		LDWI 	10H 			//00AE 	2A10
		XORWR 	5H,1 			//00AF 	0485

		//;test_61f02x_IR_Send.C: 258: }
		//;test_61f02x_IR_Send.C: 261: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//00B0 	1A83
		BCR 	STATUS,6 		//00B1 	1303
		BTSS 	CH,1 			//00B2 	1C8C
		LJUMP 	BEH 			//00B3 	38BE
		ORG		00B4H
		BCR 	STATUS,5 		//00B4 	1283
		BTSS 	CH,1 			//00B5 	1C8C
		LJUMP 	BEH 			//00B6 	38BE

		//;test_61f02x_IR_Send.C: 262: {
		//;test_61f02x_IR_Send.C: 263: TMR2IF = 0;
		BCR 	CH,1 			//00B7 	108C

		//;test_61f02x_IR_Send.C: 264: SendCtrl();
		LCALL 	21H 			//00B8 	3021

		//;test_61f02x_IR_Send.C: 265: SYSTime5S++;
		BCR 	STATUS,5 		//00B9 	1283
		BCR 	STATUS,6 		//00BA 	1303
		INCR	24H,1 			//00BB 	09A4
		ORG		00BCH
		BTSC 	STATUS,2 		//00BC 	1503
		INCR	25H,1 			//00BD 	09A5
		LDR 	7CH,0 			//00BE 	087C
		STR 	PCLATH 			//00BF 	018A
		LDR 	7BH,0 			//00C0 	087B
		STR 	FSR 			//00C1 	0184
		SWAPR 	7AH,0 			//00C2 	077A
		STR 	STATUS 			//00C3 	0183
		ORG		00C4H
		SWAPR 	7EH,1 			//00C4 	07FE
		SWAPR 	7EH,0 			//00C5 	077E
		RETI		 			//00C6 	0009

		//;test_61f02x_IR_Send.C: 62: OSCCON = 0B01110001;
		LDWI 	71H 			//00C7 	2A71
		BSR 	STATUS,5 		//00C8 	1A83
		STR 	FH 			//00C9 	018F

		//;test_61f02x_IR_Send.C: 63: INTCON = 0;
		CLRR 	INTCON 			//00CA 	010B

		//;test_61f02x_IR_Send.C: 64: PORTA = 0B00000000;
		BCR 	STATUS,5 		//00CB 	1283
		ORG		00CCH
		CLRR 	5H 			//00CC 	0105

		//;test_61f02x_IR_Send.C: 65: TRISA = 0B00000000;
		BSR 	STATUS,5 		//00CD 	1A83
		CLRR 	5H 			//00CE 	0105

		//;test_61f02x_IR_Send.C: 67: PORTC = 0B00000000;
		BCR 	STATUS,5 		//00CF 	1283
		CLRR 	7H 			//00D0 	0107

		//;test_61f02x_IR_Send.C: 68: TRISC = 0B00000000;
		BSR 	STATUS,5 		//00D1 	1A83
		CLRR 	7H 			//00D2 	0107

		//;test_61f02x_IR_Send.C: 69: WPUA = 0B00000000;
		CLRR 	15H 			//00D3 	0115
		ORG		00D4H

		//;test_61f02x_IR_Send.C: 70: WPUC = 0B00000000;
		CLRR 	8H 			//00D4 	0108

		//;test_61f02x_IR_Send.C: 72: OPTION = 0B00001000;
		LDWI 	8H 			//00D5 	2A08
		STR 	1H 			//00D6 	0181

		//;test_61f02x_IR_Send.C: 73: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//00D7 	1283
		CLRR 	1BH 			//00D8 	011B

		//;test_61f02x_IR_Send.C: 77: CMCON0 = 0B00000111;
		LDWI 	7H 			//00D9 	2A07
		STR 	19H 			//00DA 	0199
		RET		 					//00DB 	0004
		ORG		00DCH

		//;test_61f02x_IR_Send.C: 278: POWER_INITIAL();
		LCALL 	C7H 			//00DC 	30C7

		//;test_61f02x_IR_Send.C: 279: TIMER0_INITIAL();
		LCALL 	FAH 			//00DD 	30FA

		//;test_61f02x_IR_Send.C: 280: TIMER2_INITIAL();
		LCALL 	ECH 			//00DE 	30EC

		//;test_61f02x_IR_Send.C: 281: GIE = 1;
		BSR 	INTCON,7 		//00DF 	1B8B

		//;test_61f02x_IR_Send.C: 283: {
		//;test_61f02x_IR_Send.C: 284: if(SYSTime5S >10000)
		LDWI 	27H 			//00E0 	2A27
		SUBWR 	25H,0 			//00E1 	0C25
		LDWI 	11H 			//00E2 	2A11
		BTSC 	STATUS,2 		//00E3 	1503
		ORG		00E4H
		SUBWR 	24H,0 			//00E4 	0C24
		BTSS 	STATUS,0 		//00E5 	1C03
		LJUMP 	E0H 			//00E6 	38E0

		//;test_61f02x_IR_Send.C: 285: {
		//;test_61f02x_IR_Send.C: 286: SYSTime5S = 0;
		CLRR 	24H 			//00E7 	0124
		CLRR 	25H 			//00E8 	0125

		//;test_61f02x_IR_Send.C: 287: IRSendStatus = 1;
		CLRR 	76H 			//00E9 	0176
		INCR	76H,1 			//00EA 	09F6
		LJUMP 	E0H 			//00EB 	38E0
		ORG		00ECH

		//;test_61f02x_IR_Send.C: 108: T2CON = 0B00011001;
		LDWI 	19H 			//00EC 	2A19
		STR 	12H 			//00ED 	0192

		//;test_61f02x_IR_Send.C: 111: TMR2 = 0;
		CLRR 	11H 			//00EE 	0111

		//;test_61f02x_IR_Send.C: 112: PR2 = 140;
		LDWI 	8CH 			//00EF 	2A8C
		BSR 	STATUS,5 		//00F0 	1A83
		STR 	12H 			//00F1 	0192

		//;test_61f02x_IR_Send.C: 113: TMR2IF = 0;
		BCR 	STATUS,5 		//00F2 	1283
		BCR 	CH,1 			//00F3 	108C
		ORG		00F4H

		//;test_61f02x_IR_Send.C: 114: TMR2IE = 1;
		BSR 	STATUS,5 		//00F4 	1A83
		BSR 	CH,1 			//00F5 	188C

		//;test_61f02x_IR_Send.C: 115: TMR2ON = 1;
		BCR 	STATUS,5 		//00F6 	1283
		BSR 	12H,2 			//00F7 	1912

		//;test_61f02x_IR_Send.C: 116: PEIE=1;
		BSR 	INTCON,6 		//00F8 	1B0B
		RET		 					//00F9 	0004

		//;test_61f02x_IR_Send.C: 90: OPTION = 0B00000000;
		BSR 	STATUS,5 		//00FA 	1A83
		CLRR 	1H 			//00FB 	0101
		ORG		00FCH

		//;test_61f02x_IR_Send.C: 96: TMR0 = 239;
		LDWI 	EFH 			//00FC 	2AEF
		BCR 	STATUS,5 		//00FD 	1283
		STR 	1H 			//00FE 	0181

		//;test_61f02x_IR_Send.C: 97: T0IF = 0;
		BCR 	INTCON,2 		//00FF 	110B
		RET		 					//0100 	0004
			END
