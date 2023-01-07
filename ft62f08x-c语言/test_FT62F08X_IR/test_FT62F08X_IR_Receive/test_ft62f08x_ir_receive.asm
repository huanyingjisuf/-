//Deviec:FT62F08X
//-----------------------Variable---------------------------------
		_IRbitNum		EQU		78H
		_IRbitTime		EQU		77H
		_IRDataTimer		EQU		70H
		_bitdata		EQU		79H
		_ReceiveFinish		EQU		76H
		_rdata1		EQU		75H
		_rdata2		EQU		74H
//-----------------------Variable END---------------------------------
		ORG		0000H
		MOVLP 	0H 			//0000 	0180
		LJUMP 	41H 			//0001 	3841
		ORG		0003H
		NOP 					//0003 	1000
		BSR 	7EH, 0H 			//0005 	247E

		//;test_FT62F08X_IR.C: 169: if(T4UIE && T4UIF)
		MOVLP 	0H 			//0006 	0180
		MOVLB 	2H 			//0007 	1022
		BTSC 	12H, 0H 		//0008 	2812
		BTSS 	13H, 0H 		//0008 	2C13
		LJUMP 	12H 			//0009 	3812

		//;test_FT62F08X_IR.C: 170: {
		//;test_FT62F08X_IR.C: 171: T4UIF = 1;
		BSR 	13H, 0H 			//000A 	2413
		ORG		000BH
		LDWI 	33H 			//000B 	0033

		//;test_FT62F08X_IR.C: 173: IRbitTime++;
		INCR 	77H, 1H 		//000C 	1AF7

		//;test_FT62F08X_IR.C: 174: if(IRbitTime > 50)
		SUBWR 	77H, 0H 		//000D 	1277
		BTSS 	3H, 0H 			//000E 	2C03
		LJUMP 	12H 			//000F 	3812

		//;test_FT62F08X_IR.C: 175: {
		//;test_FT62F08X_IR.C: 176: T4UIE = 0;
		BCR 	12H, 0H 			//0010 	2012

		//;test_FT62F08X_IR.C: 177: IRbitTime = 0;
		CLRF 	77H 			//0011 	11F7

		//;test_FT62F08X_IR.C: 178: }
		//;test_FT62F08X_IR.C: 179: }
		//;test_FT62F08X_IR.C: 182: if(EPIF0 & 0x08)
		MOVLB 	0H 			//0012 	1020
		ORG		0013H
		BTSS 	14H, 3H 		//0013 	2D94
		LJUMP 	3FH 			//0014 	383F

		//;test_FT62F08X_IR.C: 183: {
		//;test_FT62F08X_IR.C: 184: EPIF0 |= 0x08;
		BSR 	14H, 3H 			//0015 	2594

		//;test_FT62F08X_IR.C: 186: if(PC3 == 0)
		BTSC 	EH, 3H 			//0016 	298E
		LJUMP 	3FH 			//0017 	383F

		//;test_FT62F08X_IR.C: 187: {
		//;test_FT62F08X_IR.C: 188: T4UIE = 1;
		MOVLB 	2H 			//0018 	1022
		BSR 	12H, 0H 			//0019 	2412

		//;test_FT62F08X_IR.C: 189: if(IRbitTime > 21)
		LDWI 	16H 			//001A 	0016
		ORG		001BH
		SUBWR 	77H, 0H 		//001B 	1277
		BTSS 	3H, 0H 			//001C 	2C03
		LJUMP 	25H 			//001D 	3825

		//;test_FT62F08X_IR.C: 190: {
		//;test_FT62F08X_IR.C: 191: IRDataTimer[0] = 0;
		CLRF 	70H 			//001E 	11F0

		//;test_FT62F08X_IR.C: 192: IRDataTimer[1] = 0;
		CLRF 	71H 			//001F 	11F1

		//;test_FT62F08X_IR.C: 193: IRDataTimer[2] = 0;
		CLRF 	72H 			//0020 	11F2

		//;test_FT62F08X_IR.C: 194: IRDataTimer[3] = 0;
		CLRF 	73H 			//0021 	11F3

		//;test_FT62F08X_IR.C: 195: IRbitNum = 0;
		CLRF 	78H 			//0022 	11F8
		ORG		0023H

		//;test_FT62F08X_IR.C: 196: bitdata = 0x00;
		CLRF 	79H 			//0023 	11F9

		//;test_FT62F08X_IR.C: 197: }
		LJUMP 	2FH 			//0024 	382F

		//;test_FT62F08X_IR.C: 198: else if(IRbitTime > 3)
		LDWI 	4H 			//0025 	0004
		SUBWR 	77H, 0H 		//0026 	1277
		BTSS 	3H, 0H 			//0027 	2C03
		LJUMP 	2FH 			//0028 	382F

		//;test_FT62F08X_IR.C: 199: {
		//;test_FT62F08X_IR.C: 200: IRDataTimer[IRbitNum-1] |= bitdata;
		LDR 	78H, 0H 			//0029 	1878
		ADDWI 	6FH 			//002A 	0E6F
		ORG		002BH
		STR 	6H 			//002B 	1086
		CLRF 	7H 			//002C 	1187
		LDR 	79H, 0H 			//002D 	1879
		IORWR 	1H, 1H 		//002E 	1481

		//;test_FT62F08X_IR.C: 201: }
		//;test_FT62F08X_IR.C: 202: IRbitTime = 0;
		CLRF 	77H 			//002F 	11F7

		//;test_FT62F08X_IR.C: 203: bitdata<<=1;
		LSLF 	79H, 1H 		//0030 	05F9

		//;test_FT62F08X_IR.C: 204: if(bitdata == 0)
		LDR 	79H, 0H 			//0031 	1879
		BTSS 	3H, 2H 			//0032 	2D03
		ORG		0033H
		LJUMP 	37H 			//0033 	3837

		//;test_FT62F08X_IR.C: 205: {
		//;test_FT62F08X_IR.C: 206: bitdata = 0x01;
		CLRF 	79H 			//0034 	11F9
		INCR 	79H, 1H 		//0035 	1AF9

		//;test_FT62F08X_IR.C: 207: IRbitNum++;
		INCR 	78H, 1H 		//0036 	1AF8

		//;test_FT62F08X_IR.C: 208: }
		//;test_FT62F08X_IR.C: 209: if(IRbitNum > 4)
		LDWI 	5H 			//0037 	0005
		SUBWR 	78H, 0H 		//0038 	1278
		BTSS 	3H, 0H 			//0039 	2C03
		LJUMP 	3FH 			//003A 	383F
		ORG		003BH

		//;test_FT62F08X_IR.C: 210: {
		//;test_FT62F08X_IR.C: 211: IRbitNum = 0;
		CLRF 	78H 			//003B 	11F8

		//;test_FT62F08X_IR.C: 212: T4UIE = 0;
		BCR 	12H, 0H 			//003C 	2012

		//;test_FT62F08X_IR.C: 213: ReceiveFinish = 1;
		CLRF 	76H 			//003D 	11F6
		INCR 	76H, 1H 		//003E 	1AF6
		BCR 	7EH, 0H 			//003F 	207E
		RETI 					//0040 	1009
		MOVLP 	0H 			//0041 	0180
		LJUMP 	43H 			//0042 	3843
		ORG		0043H
		LDWI 	1H 			//0043 	0001
		STR 	79H 			//0044 	10F9
		CLRF 	70H 			//0045 	11F0
		CLRF 	71H 			//0046 	11F1
		CLRF 	72H 			//0047 	11F2
		CLRF 	73H 			//0048 	11F3
		CLRF 	74H 			//0049 	11F4
		CLRF 	75H 			//004A 	11F5
		ORG		004BH
		CLRF 	76H 			//004B 	11F6
		CLRF 	77H 			//004C 	11F7
		CLRF 	78H 			//004D 	11F8
		BCR 	7EH, 0H 			//004E 	207E
		MOVLB 	0H 			//004F 	1020
		LJUMP 	51H 			//0050 	3851

		//;test_FT62F08X_IR.C: 226: POWER_INITIAL();
		LCALL 	6BH 			//0051 	306B
		MOVLP 	0H 			//0052 	0180
		ORG		0053H

		//;test_FT62F08X_IR.C: 227: TIMER4_INITIAL();
		LCALL 	A1H 			//0053 	30A1
		MOVLP 	0H 			//0054 	0180

		//;test_FT62F08X_IR.C: 228: Px_Level_Change_INITIAL();
		LCALL 	95H 			//0055 	3095
		MOVLP 	0H 			//0056 	0180

		//;test_FT62F08X_IR.C: 229: GIE = 1;
		BSR 	BH, 7H 			//0057 	278B

		//;test_FT62F08X_IR.C: 232: {
		//;test_FT62F08X_IR.C: 233: if(ReceiveFinish==1)
		DECRSZ 	76H, 0H 		//0058 	1B76
		LJUMP 	58H 			//0059 	3858

		//;test_FT62F08X_IR.C: 234: {
		//;test_FT62F08X_IR.C: 235: ReceiveFinish = 0;
		CLRF 	76H 			//005A 	11F6
		ORG		005BH

		//;test_FT62F08X_IR.C: 236: rdata1 = 0xFF - IRDataTimer[0];
		COMR 	70H, 0H 		//005B 	1970
		STR 	75H 			//005C 	10F5

		//;test_FT62F08X_IR.C: 237: rdata2 = 0xFF - IRDataTimer[2];
		COMR 	72H, 0H 		//005D 	1972
		STR 	74H 			//005E 	10F4

		//;test_FT62F08X_IR.C: 238: if((rdata1 == IRDataTimer[1])&&(rdata2 == IRDataTimer[3]))
		LDR 	71H, 0H 			//005F 	1871
		XORWR 	75H, 0H 		//0060 	1675
		BTSS 	3H, 2H 			//0061 	2D03
		LJUMP 	58H 			//0062 	3858
		ORG		0063H
		LDR 	73H, 0H 			//0063 	1873
		XORWR 	74H, 0H 		//0064 	1674
		BTSS 	3H, 2H 			//0065 	2D03
		LJUMP 	58H 			//0066 	3858

		//;test_FT62F08X_IR.C: 239: {
		//;test_FT62F08X_IR.C: 240: PB3 = ~PB3;
		LDWI 	8H 			//0067 	0008
		MOVLB 	0H 			//0068 	1020
		XORWR 	DH, 1H 		//0069 	168D
		LJUMP 	58H 			//006A 	3858
		ORG		006BH

		//;test_FT62F08X_IR.C: 37: OSCCON = 0B01110001;
		LDWI 	71H 			//006B 	0071
		MOVLB 	1H 			//006C 	1021
		STR 	19H 			//006D 	1099

		//;test_FT62F08X_IR.C: 38: INTCON = 0;
		CLRF 	BH 			//006E 	118B

		//;test_FT62F08X_IR.C: 40: PORTA = 0B00000000;
		MOVLB 	0H 			//006F 	1020
		CLRF 	CH 			//0070 	118C

		//;test_FT62F08X_IR.C: 41: TRISA = 0B00000000;
		MOVLB 	1H 			//0071 	1021
		CLRF 	CH 			//0072 	118C
		ORG		0073H

		//;test_FT62F08X_IR.C: 42: PORTB = 0B00000000;
		MOVLB 	0H 			//0073 	1020
		CLRF 	DH 			//0074 	118D

		//;test_FT62F08X_IR.C: 43: TRISB = 0B00000000;
		MOVLB 	1H 			//0075 	1021
		CLRF 	DH 			//0076 	118D

		//;test_FT62F08X_IR.C: 44: PORTC = 0B00000000;
		MOVLB 	0H 			//0077 	1020
		CLRF 	EH 			//0078 	118E

		//;test_FT62F08X_IR.C: 45: TRISC = 0B00001000;
		LDWI 	8H 			//0079 	0008
		MOVLB 	1H 			//007A 	1021
		ORG		007BH
		STR 	EH 			//007B 	108E

		//;test_FT62F08X_IR.C: 46: PORTD = 0B00000000;
		MOVLB 	0H 			//007C 	1020
		CLRF 	FH 			//007D 	118F

		//;test_FT62F08X_IR.C: 47: TRISD = 0B00000000;
		MOVLB 	1H 			//007E 	1021
		CLRF 	FH 			//007F 	118F

		//;test_FT62F08X_IR.C: 49: WPUA = 0B00000000;
		MOVLB 	3H 			//0080 	1023
		CLRF 	CH 			//0081 	118C

		//;test_FT62F08X_IR.C: 50: WPUB = 0B00000000;
		CLRF 	DH 			//0082 	118D
		ORG		0083H

		//;test_FT62F08X_IR.C: 51: WPUC = 0B00001000;
		STR 	EH 			//0083 	108E

		//;test_FT62F08X_IR.C: 52: WPUD = 0B00000000;
		CLRF 	FH 			//0084 	118F

		//;test_FT62F08X_IR.C: 54: WPDA = 0B00000000;
		MOVLB 	4H 			//0085 	1024
		CLRF 	CH 			//0086 	118C

		//;test_FT62F08X_IR.C: 55: WPDB = 0B00000000;
		CLRF 	DH 			//0087 	118D

		//;test_FT62F08X_IR.C: 56: WPDC = 0B00000000;
		CLRF 	EH 			//0088 	118E

		//;test_FT62F08X_IR.C: 57: WPDD = 0B00000000;
		CLRF 	FH 			//0089 	118F

		//;test_FT62F08X_IR.C: 59: PSRC0 = 0B11111111;
		LDWI 	FFH 			//008A 	00FF
		ORG		008BH
		MOVLB 	2H 			//008B 	1022
		STR 	1AH 			//008C 	109A

		//;test_FT62F08X_IR.C: 60: PSRC1 = 0B11111111;
		STR 	1BH 			//008D 	109B

		//;test_FT62F08X_IR.C: 62: PSINK0 = 0B11111111;
		MOVLB 	3H 			//008E 	1023
		STR 	1AH 			//008F 	109A

		//;test_FT62F08X_IR.C: 63: PSINK1 = 0B11111111;
		STR 	1BH 			//0090 	109B

		//;test_FT62F08X_IR.C: 64: PSINK2 = 0B11111111;
		STR 	1CH 			//0091 	109C

		//;test_FT62F08X_IR.C: 65: PSINK3 = 0B11111111;
		STR 	1DH 			//0092 	109D
		ORG		0093H

		//;test_FT62F08X_IR.C: 67: ANSELA = 0B00000000;
		CLRF 	17H 			//0093 	1197
		RET 					//0094 	1008

		//;test_FT62F08X_IR.C: 147: EPS0=0B10000000;
		LDWI 	80H 			//0095 	0080
		STR 	18H 			//0096 	1098

		//;test_FT62F08X_IR.C: 149: EPS1=0B00000000;
		CLRF 	19H 			//0097 	1199

		//;test_FT62F08X_IR.C: 152: ITYPE0 = 0B11000000;
		LDWI 	C0H 			//0098 	00C0
		STR 	1EH 			//0099 	109E

		//;test_FT62F08X_IR.C: 153: ITYPE1 = 0B00000000;
		CLRF 	1FH 			//009A 	119F
		ORG		009BH

		//;test_FT62F08X_IR.C: 155: EPIE0 = 0B00001000;
		LDWI 	8H 			//009B 	0008
		MOVLB 	1H 			//009C 	1021
		STR 	14H 			//009D 	1094

		//;test_FT62F08X_IR.C: 157: INTCON = 0B01000000;
		LDWI 	40H 			//009E 	0040
		STR 	BH 			//009F 	108B
		RET 					//00A0 	1008

		//;test_FT62F08X_IR.C: 76: PCKEN |= 0B00001000;
		MOVLB 	1H 			//00A1 	1021
		BSR 	1AH, 3H 			//00A2 	259A
		ORG		00A3H

		//;test_FT62F08X_IR.C: 78: TIM4CR1 = 0B00000101;
		LDWI 	5H 			//00A3 	0005
		MOVLB 	2H 			//00A4 	1022
		STR 	11H 			//00A5 	1091

		//;test_FT62F08X_IR.C: 109: TIM4IER = 0B00000001;
		LDWI 	1H 			//00A6 	0001
		STR 	12H 			//00A7 	1092

		//;test_FT62F08X_IR.C: 112: TIM4SR = 0B00000000;
		CLRF 	13H 			//00A8 	1193

		//;test_FT62F08X_IR.C: 121: TIM4EGR =0B00000000;
		CLRF 	14H 			//00A9 	1194

		//;test_FT62F08X_IR.C: 127: TIM4CNTR=0;
		CLRF 	15H 			//00AA 	1195
		ORG		00ABH

		//;test_FT62F08X_IR.C: 129: TIM4PSCR=0B00000110;
		LDWI 	6H 			//00AB 	0006
		STR 	16H 			//00AC 	1096

		//;test_FT62F08X_IR.C: 135: TIM4ARR =140;
		LDWI 	8CH 			//00AD 	008C
		STR 	17H 			//00AE 	1097
		RET 					//00AF 	1008
			END
