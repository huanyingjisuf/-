//Deviec:FT61F02X
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
		LJUMP 	78H 			//000D 	3878
		STR 	72H 			//000E 	01F2

		//;test_61f02x_UART.C: 144: unsigned char i=8;
		LDWI 	8H 			//000F 	2A08
		STR 	73H 			//0010 	01F3

		//;test_61f02x_UART.C: 145: PA4 = 1;
		BCR 	STATUS,5 		//0011 	1283
		BSR 	5H,4 			//0012 	1A05

		//;test_61f02x_UART.C: 146: TMR0 = 49;
		LDWI 	31H 			//0013 	2A31
		ORG		0014H
		STR 	1H 			//0014 	0181

		//;test_61f02x_UART.C: 147: T0IE = 1;
		BSR 	INTCON,5 		//0015 	1A8B

		//;test_61f02x_UART.C: 148: WaitTF0();
		LCALL 	9DH 			//0016 	309D

		//;test_61f02x_UART.C: 149: PA4=0;
		BCR 	STATUS,5 		//0017 	1283
		BCR 	5H,4 			//0018 	1205

		//;test_61f02x_UART.C: 150: WaitTF0();
		LCALL 	9DH 			//0019 	309D

		//;test_61f02x_UART.C: 152: while(i--)
		LJUMP 	25H 			//001A 	3825

		//;test_61f02x_UART.C: 153: {
		//;test_61f02x_UART.C: 154: if(input&0x01)
		BTSS 	72H,0 			//001B 	1C72
		ORG		001CH
		LJUMP 	20H 			//001C 	3820

		//;test_61f02x_UART.C: 155: {
		//;test_61f02x_UART.C: 156: PA4=1;
		BCR 	STATUS,5 		//001D 	1283
		BSR 	5H,4 			//001E 	1A05

		//;test_61f02x_UART.C: 157: }
		LJUMP 	22H 			//001F 	3822

		//;test_61f02x_UART.C: 158: else
		//;test_61f02x_UART.C: 159: {
		//;test_61f02x_UART.C: 160: PA4 = 0;
		BCR 	STATUS,5 		//0020 	1283
		BCR 	5H,4 			//0021 	1205

		//;test_61f02x_UART.C: 161: }
		//;test_61f02x_UART.C: 162: WaitTF0();
		LCALL 	9DH 			//0022 	309D

		//;test_61f02x_UART.C: 163: input=input>>1;
		BCR 	STATUS,0 		//0023 	1003
		ORG		0024H
		RRR	72H,1 			//0024 	06F2
		DECR 	73H,1 			//0025 	0DF3
		INCRSZ 	73H,0 		//0026 	0A73
		LJUMP 	1BH 			//0027 	381B

		//;test_61f02x_UART.C: 164: }
		//;test_61f02x_UART.C: 167: PA4=(bit)1;
		BCR 	STATUS,5 		//0028 	1283
		BSR 	5H,4 			//0029 	1A05

		//;test_61f02x_UART.C: 168: T0IE=0;
		BCR 	INTCON,5 		//002A 	128B
		RET		 					//002B 	0004
		ORG		002CH

		//;test_61f02x_UART.C: 103: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//002C 	168B
		BTSS 	INTCON,2 		//002D 	1D0B
		LJUMP 	35H 			//002E 	3835

		//;test_61f02x_UART.C: 104: {
		//;test_61f02x_UART.C: 105: TMR0 = 49;
		LDWI 	31H 			//002F 	2A31
		BCR 	STATUS,5 		//0030 	1283
		BCR 	STATUS,6 		//0031 	1303
		STR 	1H 			//0032 	0181

		//;test_61f02x_UART.C: 107: T0IF = 0;
		BCR 	INTCON,2 		//0033 	110B
		ORG		0034H

		//;test_61f02x_UART.C: 108: T0IE = 0;
		BCR 	INTCON,5 		//0034 	128B

		//;test_61f02x_UART.C: 109: }
		//;test_61f02x_UART.C: 112: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0035 	158B
		BTSS 	INTCON,0 		//0036 	1C0B
		LJUMP 	43H 			//0037 	3843

		//;test_61f02x_UART.C: 113: {
		//;test_61f02x_UART.C: 114: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0038 	1283
		BCR 	STATUS,6 		//0039 	1303
		LDR 	5H,0 			//003A 	0805

		//;test_61f02x_UART.C: 115: PAIF = 0;
		BCR 	INTCON,0 		//003B 	100B
		ORG		003CH

		//;test_61f02x_UART.C: 116: if(PA2 == 0)
		BTSC 	5H,2 			//003C 	1505
		LJUMP 	43H 			//003D 	3843

		//;test_61f02x_UART.C: 117: {
		//;test_61f02x_UART.C: 118: PAIE = 0;
		BCR 	INTCON,3 		//003E 	118B

		//;test_61f02x_UART.C: 119: IOCA2 = 0;
		BSR 	STATUS,5 		//003F 	1A83
		BCR 	16H,2 			//0040 	1116

		//;test_61f02x_UART.C: 120: RXFLAG = 1;
		CLRR 	75H 			//0041 	0175
		INCR	75H,1 			//0042 	09F5
		LDR 	71H,0 			//0043 	0871
		ORG		0044H
		STR 	PCLATH 			//0044 	018A
		SWAPR 	70H,0 			//0045 	0770
		STR 	STATUS 			//0046 	0183
		SWAPR 	7EH,1 			//0047 	07FE
		SWAPR 	7EH,0 			//0048 	077E
		RETI		 			//0049 	0009
		LDWI 	8H 			//004A 	2A08

		//;test_61f02x_UART.C: 178: unsigned char Output=0;
		CLRR 	73H 			//004B 	0173
		ORG		004CH

		//;test_61f02x_UART.C: 179: unsigned char i=8;
		STR 	72H 			//004C 	01F2

		//;test_61f02x_UART.C: 180: T0IE=1;
		BSR 	INTCON,5 		//004D 	1A8B

		//;test_61f02x_UART.C: 181: TMR0 = 49;
		LDWI 	31H 			//004E 	2A31
		BCR 	STATUS,5 		//004F 	1283
		STR 	1H 			//0050 	0181

		//;test_61f02x_UART.C: 182: WaitTF0();
		LCALL 	9DH 			//0051 	309D

		//;test_61f02x_UART.C: 183: T0IE=1;
		BSR 	INTCON,5 		//0052 	1A8B

		//;test_61f02x_UART.C: 184: TMR0 = 49;
		LDWI 	31H 			//0053 	2A31
		ORG		0054H
		BCR 	STATUS,5 		//0054 	1283
		STR 	1H 			//0055 	0181

		//;test_61f02x_UART.C: 187: while(i--)
		LJUMP 	5CH 			//0056 	385C

		//;test_61f02x_UART.C: 188: {
		//;test_61f02x_UART.C: 189: Output >>=1;
		BCR 	STATUS,0 		//0057 	1003
		RRR	73H,1 			//0058 	06F3

		//;test_61f02x_UART.C: 190: if(PA2)
		BCR 	STATUS,5 		//0059 	1283
		BTSC 	5H,2 			//005A 	1505

		//;test_61f02x_UART.C: 191: {
		//;test_61f02x_UART.C: 192: Output |=0x80;
		BSR 	73H,7 			//005B 	1BF3
		ORG		005CH

		//;test_61f02x_UART.C: 185: WaitTF0();
		LCALL 	9DH 			//005C 	309D
		DECR 	72H,1 			//005D 	0DF2
		INCRSZ 	72H,0 		//005E 	0A72
		LJUMP 	57H 			//005F 	3857

		//;test_61f02x_UART.C: 195: }
		//;test_61f02x_UART.C: 196: T0IE=0;
		BCR 	INTCON,5 		//0060 	128B

		//;test_61f02x_UART.C: 197: return Output;
		LDR 	73H,0 			//0061 	0873
		RET		 					//0062 	0004

		//;test_61f02x_UART.C: 41: OSCCON = 0B01110001;
		LDWI 	71H 			//0063 	2A71
		ORG		0064H
		BSR 	STATUS,5 		//0064 	1A83
		STR 	FH 			//0065 	018F

		//;test_61f02x_UART.C: 42: INTCON = 0;
		CLRR 	INTCON 			//0066 	010B

		//;test_61f02x_UART.C: 44: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0067 	1283
		CLRR 	5H 			//0068 	0105

		//;test_61f02x_UART.C: 45: TRISA = 0B00000100;
		LDWI 	4H 			//0069 	2A04
		BSR 	STATUS,5 		//006A 	1A83
		STR 	5H 			//006B 	0185
		ORG		006CH

		//;test_61f02x_UART.C: 46: PORTC = 0B00000000;
		BCR 	STATUS,5 		//006C 	1283
		CLRR 	7H 			//006D 	0107

		//;test_61f02x_UART.C: 47: TRISC = 0B00000000;
		BSR 	STATUS,5 		//006E 	1A83
		CLRR 	7H 			//006F 	0107

		//;test_61f02x_UART.C: 49: WPUA = 0B00000100;
		STR 	15H 			//0070 	0195

		//;test_61f02x_UART.C: 50: WPUC = 0B00000000;
		CLRR 	8H 			//0071 	0108

		//;test_61f02x_UART.C: 51: OPTION = 0B00000000;
		CLRR 	1H 			//0072 	0101

		//;test_61f02x_UART.C: 52: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0073 	1283
		ORG		0074H
		CLRR 	1BH 			//0074 	011B

		//;test_61f02x_UART.C: 57: CMCON0 = 0B00000111;
		LDWI 	7H 			//0075 	2A07
		STR 	19H 			//0076 	0199
		RET		 					//0077 	0004

		//;test_61f02x_UART.C: 208: POWER_INITIAL();
		LCALL 	63H 			//0078 	3063

		//;test_61f02x_UART.C: 209: TIMER0_INITIAL();
		LCALL 	96H 			//0079 	3096

		//;test_61f02x_UART.C: 210: PA2_Level_Change_INITIAL();
		LCALL 	89H 			//007A 	3089

		//;test_61f02x_UART.C: 211: GIE = 1;
		BSR 	INTCON,7 		//007B 	1B8B
		ORG		007CH

		//;test_61f02x_UART.C: 212: T0IE = 1;
		BSR 	INTCON,5 		//007C 	1A8B

		//;test_61f02x_UART.C: 214: {
		//;test_61f02x_UART.C: 215: if(RXFLAG)
		LDR 	75H,0 			//007D 	0875
		BTSC 	STATUS,2 		//007E 	1503
		LJUMP 	7DH 			//007F 	387D

		//;test_61f02x_UART.C: 216: {
		//;test_61f02x_UART.C: 217: rdata = RByte();
		LCALL 	4AH 			//0080 	304A
		STR 	74H 			//0081 	01F4

		//;test_61f02x_UART.C: 218: WByte(rdata);
		LDR 	74H,0 			//0082 	0874
		LCALL 	EH 			//0083 	300E
		ORG		0084H

		//;test_61f02x_UART.C: 220: IOCA2 =1;
		BSR 	STATUS,5 		//0084 	1A83
		BSR 	16H,2 			//0085 	1916

		//;test_61f02x_UART.C: 221: PAIE =1;
		BSR 	INTCON,3 		//0086 	198B

		//;test_61f02x_UART.C: 222: RXFLAG = 0;
		CLRR 	75H 			//0087 	0175
		LJUMP 	7DH 			//0088 	387D

		//;test_61f02x_UART.C: 85: TRISA2 =1;
		BSR 	STATUS,5 		//0089 	1A83
		BSR 	5H,2 			//008A 	1905

		//;test_61f02x_UART.C: 86: ANSEL &= 0xeb;
		LDWI 	EBH 			//008B 	2AEB
		ORG		008CH
		ANDWR 	11H,1 			//008C 	0291

		//;test_61f02x_UART.C: 87: CMCON0 = 0B00000111;
		LDWI 	7H 			//008D 	2A07
		BCR 	STATUS,5 		//008E 	1283
		STR 	19H 			//008F 	0199

		//;test_61f02x_UART.C: 88: ReadAPin = PORTA;
		LDR 	5H,0 			//0090 	0805

		//;test_61f02x_UART.C: 89: PAIF = 0;
		BCR 	INTCON,0 		//0091 	100B

		//;test_61f02x_UART.C: 90: IOCA2 = 1;
		BSR 	STATUS,5 		//0092 	1A83
		BSR 	16H,2 			//0093 	1916
		ORG		0094H

		//;test_61f02x_UART.C: 91: PAIE = 1;
		BSR 	INTCON,3 		//0094 	198B
		RET		 					//0095 	0004

		//;test_61f02x_UART.C: 67: OPTION = 0B00000000;
		BSR 	STATUS,5 		//0096 	1A83
		CLRR 	1H 			//0097 	0101

		//;test_61f02x_UART.C: 74: TMR0 = 49;
		LDWI 	31H 			//0098 	2A31
		BCR 	STATUS,5 		//0099 	1283
		STR 	1H 			//009A 	0181

		//;test_61f02x_UART.C: 75: T0IF = 0;
		BCR 	INTCON,2 		//009B 	110B
		ORG		009CH
		RET		 					//009C 	0004

		//;test_61f02x_UART.C: 132: while(T0IE);
		BTSC 	INTCON,5 		//009D 	168B
		LJUMP 	9DH 			//009E 	389D

		//;test_61f02x_UART.C: 133: T0IE=1;
		BSR 	INTCON,5 		//009F 	1A8B
		RET		 					//00A0 	0004
			END
