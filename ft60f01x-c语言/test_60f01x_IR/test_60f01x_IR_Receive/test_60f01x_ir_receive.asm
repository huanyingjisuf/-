//Deviec:FT60F01X
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
		LJUMP 	5DH 			//0017 	385D

		//;test_60f01x_IR_Receive.C: 96: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//0018 	168B
		BTSS 	INTCON,2 		//0019 	1D0B
		LJUMP 	26H 			//001A 	3826

		//;test_60f01x_IR_Receive.C: 97: {
		//;test_60f01x_IR_Receive.C: 98: TMR0 = 118;
		LDWI 	76H 			//001B 	2A76
		ORG		001CH
		BCR 	STATUS,5 		//001C 	1283
		STR 	1H 			//001D 	0181

		//;test_60f01x_IR_Receive.C: 100: T0IF = 0;
		BCR 	INTCON,2 		//001E 	110B
		LDWI 	33H 			//001F 	2A33

		//;test_60f01x_IR_Receive.C: 101: IRbitTime++;
		INCR	75H,1 			//0020 	09F5

		//;test_60f01x_IR_Receive.C: 102: if(IRbitTime > 50)
		SUBWR 	75H,0 			//0021 	0C75
		BTSS 	STATUS,0 		//0022 	1C03
		LJUMP 	26H 			//0023 	3826
		ORG		0024H

		//;test_60f01x_IR_Receive.C: 103: {
		//;test_60f01x_IR_Receive.C: 104: T0IE = 0;
		BCR 	INTCON,5 		//0024 	128B

		//;test_60f01x_IR_Receive.C: 105: IRbitTime = 0;
		CLRR 	75H 			//0025 	0175

		//;test_60f01x_IR_Receive.C: 106: }
		//;test_60f01x_IR_Receive.C: 107: }
		//;test_60f01x_IR_Receive.C: 110: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0026 	158B
		BTSS 	INTCON,0 		//0027 	1C0B
		LJUMP 	54H 			//0028 	3854

		//;test_60f01x_IR_Receive.C: 111: {
		//;test_60f01x_IR_Receive.C: 112: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0029 	1283
		LDR 	5H,0 			//002A 	0805

		//;test_60f01x_IR_Receive.C: 113: PAIF = 0;
		BCR 	INTCON,0 		//002B 	100B
		ORG		002CH

		//;test_60f01x_IR_Receive.C: 114: if(PA4 == 0)
		BTSC 	5H,4 			//002C 	1605
		LJUMP 	54H 			//002D 	3854

		//;test_60f01x_IR_Receive.C: 115: {
		//;test_60f01x_IR_Receive.C: 116: T0IE = 1;
		BSR 	INTCON,5 		//002E 	1A8B

		//;test_60f01x_IR_Receive.C: 117: if(IRbitTime > 21)
		LDWI 	16H 			//002F 	2A16
		SUBWR 	75H,0 			//0030 	0C75
		BTSS 	STATUS,0 		//0031 	1C03
		LJUMP 	3AH 			//0032 	383A

		//;test_60f01x_IR_Receive.C: 118: {
		//;test_60f01x_IR_Receive.C: 119: IRDataTimer[0] = 0;
		CLRR 	70H 			//0033 	0170
		ORG		0034H

		//;test_60f01x_IR_Receive.C: 120: IRDataTimer[1] = 0;
		CLRR 	71H 			//0034 	0171

		//;test_60f01x_IR_Receive.C: 121: IRDataTimer[2] = 0;
		CLRR 	72H 			//0035 	0172

		//;test_60f01x_IR_Receive.C: 122: IRDataTimer[3] = 0;
		CLRR 	73H 			//0036 	0173

		//;test_60f01x_IR_Receive.C: 123: IRbitNum = 0;
		CLRR 	76H 			//0037 	0176

		//;test_60f01x_IR_Receive.C: 124: bitdata = 0x00;
		CLRR 	7CH 			//0038 	017C

		//;test_60f01x_IR_Receive.C: 125: }
		LJUMP 	43H 			//0039 	3843

		//;test_60f01x_IR_Receive.C: 126: else if(IRbitTime > 3)
		LDWI 	4H 			//003A 	2A04
		SUBWR 	75H,0 			//003B 	0C75
		ORG		003CH
		BTSS 	STATUS,0 		//003C 	1C03
		LJUMP 	43H 			//003D 	3843

		//;test_60f01x_IR_Receive.C: 127: {
		//;test_60f01x_IR_Receive.C: 128: IRDataTimer[IRbitNum-1] |= bitdata;
		LDR 	76H,0 			//003E 	0876
		ADDWI 	6FH 			//003F 	276F
		STR 	FSR 			//0040 	0184
		LDR 	7CH,0 			//0041 	087C
		IORWR 	INDF,1 		//0042 	0380

		//;test_60f01x_IR_Receive.C: 129: }
		//;test_60f01x_IR_Receive.C: 130: IRbitTime = 0;
		CLRR 	75H 			//0043 	0175
		ORG		0044H

		//;test_60f01x_IR_Receive.C: 131: bitdata<<=1;
		BCR 	STATUS,0 		//0044 	1003
		RLR 	7CH,1 			//0045 	05FC

		//;test_60f01x_IR_Receive.C: 132: if(bitdata == 0)
		LDR 	7CH,0 			//0046 	087C
		BTSS 	STATUS,2 		//0047 	1D03
		LJUMP 	4CH 			//0048 	384C

		//;test_60f01x_IR_Receive.C: 133: {
		//;test_60f01x_IR_Receive.C: 134: bitdata = 0x01;
		CLRR 	7CH 			//0049 	017C
		INCR	7CH,1 			//004A 	09FC

		//;test_60f01x_IR_Receive.C: 135: IRbitNum++;
		INCR	76H,1 			//004B 	09F6
		ORG		004CH

		//;test_60f01x_IR_Receive.C: 136: }
		//;test_60f01x_IR_Receive.C: 137: if(IRbitNum > 4)
		LDWI 	5H 			//004C 	2A05
		SUBWR 	76H,0 			//004D 	0C76
		BTSS 	STATUS,0 		//004E 	1C03
		LJUMP 	54H 			//004F 	3854

		//;test_60f01x_IR_Receive.C: 138: {
		//;test_60f01x_IR_Receive.C: 139: IRbitNum = 0;
		CLRR 	76H 			//0050 	0176

		//;test_60f01x_IR_Receive.C: 140: T0IE = 0;
		BCR 	INTCON,5 		//0051 	128B

		//;test_60f01x_IR_Receive.C: 141: ReceiveFinish = 1;
		CLRR 	74H 			//0052 	0174
		INCR	74H,1 			//0053 	09F4
		ORG		0054H
		LDR 	79H,0 			//0054 	0879
		STR 	PCLATH 			//0055 	018A
		LDR 	78H,0 			//0056 	0878
		STR 	FSR 			//0057 	0184
		SWAPR 	77H,0 			//0058 	0777
		STR 	STATUS 			//0059 	0183
		SWAPR 	7EH,1 			//005A 	07FE
		SWAPR 	7EH,0 			//005B 	077E
		ORG		005CH
		RETI		 			//005C 	0009

		//;test_60f01x_IR_Receive.C: 155: unsigned char rdata1,rdata2;
		//;test_60f01x_IR_Receive.C: 156: POWER_INITIAL();
		LCALL 	76H 			//005D 	3076

		//;test_60f01x_IR_Receive.C: 157: TIMER0_INITIAL();
		LCALL 	8EH 			//005E 	308E

		//;test_60f01x_IR_Receive.C: 158: PA_Level_Change_INITIAL();
		LCALL 	85H 			//005F 	3085

		//;test_60f01x_IR_Receive.C: 159: GIE = 1;
		BSR 	INTCON,7 		//0060 	1B8B

		//;test_60f01x_IR_Receive.C: 160: T0IE = 1;
		BSR 	INTCON,5 		//0061 	1A8B

		//;test_60f01x_IR_Receive.C: 162: {
		//;test_60f01x_IR_Receive.C: 163: if(ReceiveFinish)
		LDR 	74H,0 			//0062 	0874
		BTSC 	STATUS,2 		//0063 	1503
		ORG		0064H
		LJUMP 	62H 			//0064 	3862

		//;test_60f01x_IR_Receive.C: 164: {
		//;test_60f01x_IR_Receive.C: 165: ReceiveFinish = 0;
		CLRR 	74H 			//0065 	0174

		//;test_60f01x_IR_Receive.C: 166: rdata1 = 0xFF - IRDataTimer[0];
		COMR 	70H,0 			//0066 	0F70
		STR 	7AH 			//0067 	01FA

		//;test_60f01x_IR_Receive.C: 167: rdata2 = 0xFF - IRDataTimer[2];
		COMR 	72H,0 			//0068 	0F72
		STR 	7BH 			//0069 	01FB

		//;test_60f01x_IR_Receive.C: 168: if((rdata1 == IRDataTimer[1])&&(rdata2 == IRDataTimer[3]
		//+                          ))
		LDR 	71H,0 			//006A 	0871
		XORWR 	7AH,0 			//006B 	047A
		ORG		006CH
		BTSS 	STATUS,2 		//006C 	1D03
		LJUMP 	62H 			//006D 	3862
		LDR 	73H,0 			//006E 	0873
		XORWR 	7BH,0 			//006F 	047B
		BTSS 	STATUS,2 		//0070 	1D03
		LJUMP 	62H 			//0071 	3862

		//;test_60f01x_IR_Receive.C: 169: {
		//;test_60f01x_IR_Receive.C: 170: PA2 = ~PA2;
		LDWI 	4H 			//0072 	2A04
		BCR 	STATUS,5 		//0073 	1283
		ORG		0074H
		XORWR 	5H,1 			//0074 	0485
		LJUMP 	62H 			//0075 	3862

		//;test_60f01x_IR_Receive.C: 42: OSCCON = 0B01110000;
		LDWI 	70H 			//0076 	2A70
		BSR 	STATUS,5 		//0077 	1A83
		STR 	FH 			//0078 	018F

		//;test_60f01x_IR_Receive.C: 43: INTCON = 0;
		CLRR 	INTCON 			//0079 	010B

		//;test_60f01x_IR_Receive.C: 44: OPTION = 0B00001000;
		LDWI 	8H 			//007A 	2A08
		STR 	1H 			//007B 	0181
		ORG		007CH

		//;test_60f01x_IR_Receive.C: 46: PORTA = 0B00000000;
		BCR 	STATUS,5 		//007C 	1283
		CLRR 	5H 			//007D 	0105

		//;test_60f01x_IR_Receive.C: 47: TRISA = 0B00010000;
		LDWI 	10H 			//007E 	2A10
		BSR 	STATUS,5 		//007F 	1A83
		STR 	5H 			//0080 	0185

		//;test_60f01x_IR_Receive.C: 49: WPUA = 0B00000000;
		CLRR 	15H 			//0081 	0115

		//;test_60f01x_IR_Receive.C: 50: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0082 	1283
		CLRR 	1BH 			//0083 	011B
		ORG		0084H
		RET		 					//0084 	0004

		//;test_60f01x_IR_Receive.C: 81: TRISA4=1;
		BSR 	STATUS,5 		//0085 	1A83
		BSR 	5H,4 			//0086 	1A05

		//;test_60f01x_IR_Receive.C: 82: ReadAPin=PORTA;
		BCR 	STATUS,5 		//0087 	1283
		LDR 	5H,0 			//0088 	0805

		//;test_60f01x_IR_Receive.C: 83: PAIF=0;
		BCR 	INTCON,0 		//0089 	100B

		//;test_60f01x_IR_Receive.C: 84: IOCA4=1;
		BSR 	STATUS,5 		//008A 	1A83
		BSR 	16H,4 			//008B 	1A16
		ORG		008CH

		//;test_60f01x_IR_Receive.C: 85: PAIE=1;
		BSR 	INTCON,3 		//008C 	198B
		RET		 					//008D 	0004

		//;test_60f01x_IR_Receive.C: 63: OPTION = 0B00000011;
		LDWI 	3H 			//008E 	2A03
		BSR 	STATUS,5 		//008F 	1A83
		STR 	1H 			//0090 	0181

		//;test_60f01x_IR_Receive.C: 70: TMR0 = 118;
		LDWI 	76H 			//0091 	2A76
		BCR 	STATUS,5 		//0092 	1283
		STR 	1H 			//0093 	0181
		ORG		0094H

		//;test_60f01x_IR_Receive.C: 71: T0IF = 0;
		BCR 	INTCON,2 		//0094 	110B
		RET		 					//0095 	0004
			END
