//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_RXFLAG		EQU		75H
//		main@rdata		EQU		74H
//		WByte@input		EQU		72H
//		WByte@i		EQU		73H
//		WByte@input		EQU		C00000H
//		RByte@Output		EQU		73H
//		RByte@i		EQU		72H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		LJUMP 	2CH 			//0009 	382C
		LJUMP 	0BH 			//000A 	380B
		CLRR 	75H 			//000B 	0175
		ORG		000CH
		CLRR 	STATUS 			//000C 	0103
		LJUMP 	61H 			//000D 	3861
		STR 	72H 			//000E 	01F2

		//;test_60f01x_UART.C: 131: unsigned char i=8;
		LDWI 	8H 			//000F 	2A08
		STR 	73H 			//0010 	01F3

		//;test_60f01x_UART.C: 132: PA4 = 1;
		BCR 	STATUS,5 		//0011 	1283
		BSR 	5H,4 			//0012 	1A05

		//;test_60f01x_UART.C: 133: TMR0 = 49;
		LDWI 	31H 			//0013 	2A31
		ORG		0014H
		STR 	1H 			//0014 	0181

		//;test_60f01x_UART.C: 134: T0IE = 1;
		BSR 	INTCON,5 		//0015 	1A8B

		//;test_60f01x_UART.C: 135: WaitTF0();
		LCALL 	91H 			//0016 	3091

		//;test_60f01x_UART.C: 136: PA4=0;
		BCR 	STATUS,5 		//0017 	1283
		BCR 	5H,4 			//0018 	1205

		//;test_60f01x_UART.C: 137: WaitTF0();
		LCALL 	91H 			//0019 	3091

		//;test_60f01x_UART.C: 139: while(i--)
		LJUMP 	25H 			//001A 	3825

		//;test_60f01x_UART.C: 140: {
		//;test_60f01x_UART.C: 141: if(input&0x01)
		BTSS 	72H,0 			//001B 	1C72
		ORG		001CH
		LJUMP 	20H 			//001C 	3820

		//;test_60f01x_UART.C: 142: {
		//;test_60f01x_UART.C: 143: PA4=1;
		BCR 	STATUS,5 		//001D 	1283
		BSR 	5H,4 			//001E 	1A05

		//;test_60f01x_UART.C: 144: }
		LJUMP 	22H 			//001F 	3822

		//;test_60f01x_UART.C: 145: else
		//;test_60f01x_UART.C: 146: {
		//;test_60f01x_UART.C: 147: PA4 = 0;
		BCR 	STATUS,5 		//0020 	1283
		BCR 	5H,4 			//0021 	1205

		//;test_60f01x_UART.C: 148: }
		//;test_60f01x_UART.C: 149: WaitTF0();
		LCALL 	91H 			//0022 	3091

		//;test_60f01x_UART.C: 150: input=input>>1;
		BCR 	STATUS,0 		//0023 	1003
		ORG		0024H
		RRR	72H,1 			//0024 	06F2
		DECR 	73H,1 			//0025 	0DF3
		INCRSZ 	73H,0 		//0026 	0A73
		LJUMP 	1BH 			//0027 	381B

		//;test_60f01x_UART.C: 151: }
		//;test_60f01x_UART.C: 154: PA4=(bit)1;
		BCR 	STATUS,5 		//0028 	1283
		BSR 	5H,4 			//0029 	1A05

		//;test_60f01x_UART.C: 155: T0IE=0;
		BCR 	INTCON,5 		//002A 	128B
		RET		 					//002B 	0004
		ORG		002CH

		//;test_60f01x_UART.C: 90: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//002C 	168B
		BTSS 	INTCON,2 		//002D 	1D0B
		LJUMP 	34H 			//002E 	3834

		//;test_60f01x_UART.C: 91: {
		//;test_60f01x_UART.C: 92: TMR0 = 49;
		LDWI 	31H 			//002F 	2A31
		BCR 	STATUS,5 		//0030 	1283
		STR 	1H 			//0031 	0181

		//;test_60f01x_UART.C: 93: T0IF = 0;
		BCR 	INTCON,2 		//0032 	110B

		//;test_60f01x_UART.C: 94: T0IE = 0;
		BCR 	INTCON,5 		//0033 	128B
		ORG		0034H

		//;test_60f01x_UART.C: 95: }
		//;test_60f01x_UART.C: 98: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0034 	158B
		BTSS 	INTCON,0 		//0035 	1C0B
		LJUMP 	41H 			//0036 	3841

		//;test_60f01x_UART.C: 99: {
		//;test_60f01x_UART.C: 100: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0037 	1283
		LDR 	5H,0 			//0038 	0805

		//;test_60f01x_UART.C: 101: PAIF = 0;
		BCR 	INTCON,0 		//0039 	100B

		//;test_60f01x_UART.C: 102: if(PA2 == 0)
		BTSC 	5H,2 			//003A 	1505
		LJUMP 	41H 			//003B 	3841
		ORG		003CH

		//;test_60f01x_UART.C: 103: {
		//;test_60f01x_UART.C: 104: PAIE = 0;
		BCR 	INTCON,3 		//003C 	118B

		//;test_60f01x_UART.C: 105: IOCA2 =0;
		BSR 	STATUS,5 		//003D 	1A83
		BCR 	16H,2 			//003E 	1116

		//;test_60f01x_UART.C: 106: RXFLAG = 1;
		CLRR 	75H 			//003F 	0175
		INCR	75H,1 			//0040 	09F5
		LDR 	71H,0 			//0041 	0871
		STR 	PCLATH 			//0042 	018A
		SWAPR 	70H,0 			//0043 	0770
		ORG		0044H
		STR 	STATUS 			//0044 	0183
		SWAPR 	7EH,1 			//0045 	07FE
		SWAPR 	7EH,0 			//0046 	077E
		RETI		 			//0047 	0009
		LDWI 	8H 			//0048 	2A08

		//;test_60f01x_UART.C: 165: unsigned char Output=0;
		CLRR 	73H 			//0049 	0173

		//;test_60f01x_UART.C: 166: unsigned char i=8;
		STR 	72H 			//004A 	01F2

		//;test_60f01x_UART.C: 167: T0IE=1;
		BSR 	INTCON,5 		//004B 	1A8B
		ORG		004CH

		//;test_60f01x_UART.C: 168: TMR0 = 49;
		LDWI 	31H 			//004C 	2A31
		BCR 	STATUS,5 		//004D 	1283
		STR 	1H 			//004E 	0181

		//;test_60f01x_UART.C: 169: WaitTF0();
		LCALL 	91H 			//004F 	3091

		//;test_60f01x_UART.C: 170: T0IE=1;
		BSR 	INTCON,5 		//0050 	1A8B

		//;test_60f01x_UART.C: 171: TMR0 = 49;
		LDWI 	31H 			//0051 	2A31
		BCR 	STATUS,5 		//0052 	1283
		STR 	1H 			//0053 	0181
		ORG		0054H

		//;test_60f01x_UART.C: 174: while(i--)
		LJUMP 	5AH 			//0054 	385A

		//;test_60f01x_UART.C: 175: {
		//;test_60f01x_UART.C: 176: Output >>=1;
		BCR 	STATUS,0 		//0055 	1003
		RRR	73H,1 			//0056 	06F3

		//;test_60f01x_UART.C: 177: if(PA2)
		BCR 	STATUS,5 		//0057 	1283
		BTSC 	5H,2 			//0058 	1505

		//;test_60f01x_UART.C: 178: {
		//;test_60f01x_UART.C: 179: Output|=0x80;
		BSR 	73H,7 			//0059 	1BF3

		//;test_60f01x_UART.C: 172: WaitTF0();
		LCALL 	91H 			//005A 	3091
		DECR 	72H,1 			//005B 	0DF2
		ORG		005CH
		INCRSZ 	72H,0 		//005C 	0A72
		LJUMP 	55H 			//005D 	3855

		//;test_60f01x_UART.C: 182: }
		//;test_60f01x_UART.C: 183: T0IE=0;
		BCR 	INTCON,5 		//005E 	128B

		//;test_60f01x_UART.C: 184: return Output;
		LDR 	73H,0 			//005F 	0873
		RET		 					//0060 	0004

		//;test_60f01x_UART.C: 195: POWER_INITIAL();
		LCALL 	72H 			//0061 	3072

		//;test_60f01x_UART.C: 196: TIMER0_INITIAL();
		LCALL 	8AH 			//0062 	308A

		//;test_60f01x_UART.C: 197: PA2_Level_Change_INITIAL();
		LCALL 	81H 			//0063 	3081
		ORG		0064H

		//;test_60f01x_UART.C: 198: GIE = 1;
		BSR 	INTCON,7 		//0064 	1B8B

		//;test_60f01x_UART.C: 199: T0IE = 1;
		BSR 	INTCON,5 		//0065 	1A8B

		//;test_60f01x_UART.C: 201: {
		//;test_60f01x_UART.C: 203: if(RXFLAG)
		LDR 	75H,0 			//0066 	0875
		BTSC 	STATUS,2 		//0067 	1503
		LJUMP 	66H 			//0068 	3866

		//;test_60f01x_UART.C: 204: {
		//;test_60f01x_UART.C: 205: rdata = RByte();
		LCALL 	48H 			//0069 	3048
		STR 	74H 			//006A 	01F4

		//;test_60f01x_UART.C: 206: WByte(rdata);
		LDR 	74H,0 			//006B 	0874
		ORG		006CH
		LCALL 	EH 			//006C 	300E

		//;test_60f01x_UART.C: 208: IOCA2 =1;
		BSR 	STATUS,5 		//006D 	1A83
		BSR 	16H,2 			//006E 	1916

		//;test_60f01x_UART.C: 209: PAIE =1;
		BSR 	INTCON,3 		//006F 	198B

		//;test_60f01x_UART.C: 210: RXFLAG = 0;
		CLRR 	75H 			//0070 	0175
		LJUMP 	66H 			//0071 	3866

		//;test_60f01x_UART.C: 37: OSCCON = 0B01110000;
		LDWI 	70H 			//0072 	2A70
		BSR 	STATUS,5 		//0073 	1A83
		ORG		0074H
		STR 	FH 			//0074 	018F

		//;test_60f01x_UART.C: 38: INTCON = 0;
		CLRR 	INTCON 			//0075 	010B

		//;test_60f01x_UART.C: 39: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0076 	1283
		CLRR 	5H 			//0077 	0105

		//;test_60f01x_UART.C: 40: TRISA = 0B00000100;
		LDWI 	4H 			//0078 	2A04
		BSR 	STATUS,5 		//0079 	1A83
		STR 	5H 			//007A 	0185

		//;test_60f01x_UART.C: 42: WPUA = 0B00000100;
		STR 	15H 			//007B 	0195
		ORG		007CH

		//;test_60f01x_UART.C: 44: OPTION = 0B00001000;
		LDWI 	8H 			//007C 	2A08
		STR 	1H 			//007D 	0181

		//;test_60f01x_UART.C: 45: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//007E 	1283
		CLRR 	1BH 			//007F 	011B
		RET		 					//0080 	0004

		//;test_60f01x_UART.C: 75: TRISA2 =1;
		BSR 	STATUS,5 		//0081 	1A83
		BSR 	5H,2 			//0082 	1905

		//;test_60f01x_UART.C: 76: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0083 	1283
		ORG		0084H
		LDR 	5H,0 			//0084 	0805

		//;test_60f01x_UART.C: 77: PAIF =0;
		BCR 	INTCON,0 		//0085 	100B

		//;test_60f01x_UART.C: 78: IOCA2 =1;
		BSR 	STATUS,5 		//0086 	1A83
		BSR 	16H,2 			//0087 	1916

		//;test_60f01x_UART.C: 79: PAIE =1;
		BSR 	INTCON,3 		//0088 	198B
		RET		 					//0089 	0004

		//;test_60f01x_UART.C: 58: OPTION = 0B00000000;
		BSR 	STATUS,5 		//008A 	1A83
		CLRR 	1H 			//008B 	0101
		ORG		008CH

		//;test_60f01x_UART.C: 64: TMR0 = 49;
		LDWI 	31H 			//008C 	2A31
		BCR 	STATUS,5 		//008D 	1283
		STR 	1H 			//008E 	0181

		//;test_60f01x_UART.C: 65: T0IF = 0;
		BCR 	INTCON,2 		//008F 	110B
		RET		 					//0090 	0004

		//;test_60f01x_UART.C: 118: while(T0IE);
		BTSC 	INTCON,5 		//0091 	168B
		LJUMP 	91H 			//0092 	3891

		//;test_60f01x_UART.C: 119: T0IE=1;
		BSR 	INTCON,5 		//0093 	1A8B
		ORG		0094H
		RET		 					//0094 	0004
			END
