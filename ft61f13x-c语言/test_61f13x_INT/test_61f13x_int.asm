//Deviec:FT61F13X
//-----------------------Variable---------------------------------
		_FCount		EQU		25H
//		DelayMs@Time		EQU		22H
//		DelayMs@b		EQU		24H
//		DelayMs@a		EQU		23H
//		DelayMs@Time		EQU		22H
//		DelayMs@Time		EQU		22H
//		DelayUs@Time		EQU		20H
//		DelayUs@a		EQU		21H
//		DelayUs@Time		EQU		20H
//		DelayUs@Time		EQU		20H
//		i1DelayMs@Time		EQU		72H
//		i1DelayMs@b		EQU		74H
//		i1DelayMs@a		EQU		73H
//		i1DelayMs@Time		EQU		72H
//		i1DelayMs@Time		EQU		72H
//		i1DelayUs@Time		EQU		70H
//		i1DelayUs@a		EQU		71H
//		i1DelayUs@Time		EQU		70H
//		i1DelayUs@Time		EQU		70H
//-----------------------Variable END---------------------------------

		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0BH 			//0001 	380B
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	75H 			//0006 	01F5
		LDR 	PCLATH,0 		//0007 	080A
		STR 	76H 			//0008 	01F6
		BCR 	PCLATH,3 		//0009 	118A
		LJUMP 	10H 			//000A 	3810
		BCR 	PCLATH,3 		//000B 	118A
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	57H 			//000F 	3857

		//;test_61f13x_INT.C: 103: if(INTF==1)
		BTSS 	INTCON,1 		//0010 	1C8B
		LJUMP 	17H 			//0011 	3817

		//;test_61f13x_INT.C: 104: {
		//;test_61f13x_INT.C: 105: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0012 	1283
		BCR 	STATUS,6 		//0013 	1303
		LDR 	5H,0 			//0014 	0805

		//;test_61f13x_INT.C: 106: INTF = 0;
		BCR 	INTCON,1 		//0015 	108B

		//;test_61f13x_INT.C: 107: INTE = 0;
		BCR 	INTCON,4 		//0016 	120B

		//;test_61f13x_INT.C: 108: }
		//;test_61f13x_INT.C: 109: DelayMs(10);
		LDWI 	AH 			//0017 	2A0A
		LCALL 	20H 			//0018 	3020
		LDR 	76H,0 			//0019 	0876
		STR 	PCLATH 			//001A 	018A
		SWAPR 	75H,0 			//001B 	0775
		STR 	STATUS 			//001C 	0183
		SWAPR 	7EH,1 			//001D 	07FE
		SWAPR 	7EH,0 			//001E 	077E
		RETI		 			//001F 	0009
		STR 	72H 			//0020 	01F2

		//;test_61f13x_INT.C: 61: unsigned char a,b;
		//;test_61f13x_INT.C: 62: for(a=0;a<Time;a++)
		CLRR 	73H 			//0021 	0173
		LDR 	72H,0 			//0022 	0872
		SUBWR 	73H,0 			//0023 	0C73
		BTSC 	STATUS,0 		//0024 	1403
		RET		 					//0025 	0004

		//;test_61f13x_INT.C: 63: {
		//;test_61f13x_INT.C: 64: for(b=0;b<5;b++)
		CLRR 	74H 			//0026 	0174
		LDWI 	5H 			//0027 	2A05
		SUBWR 	74H,0 			//0028 	0C74
		BTSC 	STATUS,0 		//0029 	1403
		LJUMP 	30H 			//002A 	3830

		//;test_61f13x_INT.C: 65: {
		//;test_61f13x_INT.C: 66: DelayUs(197);
		LDWI 	C5H 			//002B 	2AC5
		LCALL 	32H 			//002C 	3032
		BCR 	PCLATH,3 		//002D 	118A
		INCR	74H,1 			//002E 	09F4
		LJUMP 	27H 			//002F 	3827
		INCR	73H,1 			//0030 	09F3
		LJUMP 	22H 			//0031 	3822
		STR 	70H 			//0032 	01F0

		//;test_61f13x_INT.C: 47: unsigned char a;
		//;test_61f13x_INT.C: 48: for(a=0;a<Time;a++)
		CLRR 	71H 			//0033 	0171
		LDR 	70H,0 			//0034 	0870
		SUBWR 	71H,0 			//0035 	0C71
		BTSC 	STATUS,0 		//0036 	1403
		RET		 					//0037 	0004

		//;test_61f13x_INT.C: 49: {
		//;test_61f13x_INT.C: 50: __nop();
		NOP		 					//0038 	0000
		INCR	71H,1 			//0039 	09F1
		LJUMP 	34H 			//003A 	3834
		STR 	22H 			//003B 	01A2

		//;test_61f13x_INT.C: 61: unsigned char a,b;
		//;test_61f13x_INT.C: 62: for(a=0;a<Time;a++)
		CLRR 	23H 			//003C 	0123
		LDR 	22H,0 			//003D 	0822
		SUBWR 	23H,0 			//003E 	0C23
		BTSC 	STATUS,0 		//003F 	1403
		RET		 					//0040 	0004

		//;test_61f13x_INT.C: 63: {
		//;test_61f13x_INT.C: 64: for(b=0;b<5;b++)
		CLRR 	24H 			//0041 	0124

		//;test_61f13x_INT.C: 65: {
		//;test_61f13x_INT.C: 66: DelayUs(197);
		LDWI 	C5H 			//0042 	2AC5
		LCALL 	4CH 			//0043 	304C
		BCR 	PCLATH,3 		//0044 	118A
		LDWI 	5H 			//0045 	2A05
		INCR	24H,1 			//0046 	09A4
		SUBWR 	24H,0 			//0047 	0C24
		BTSS 	STATUS,0 		//0048 	1C03
		LJUMP 	42H 			//0049 	3842
		INCR	23H,1 			//004A 	09A3
		LJUMP 	3DH 			//004B 	383D
		STR 	20H 			//004C 	01A0

		//;test_61f13x_INT.C: 47: unsigned char a;
		//;test_61f13x_INT.C: 48: for(a=0;a<Time;a++)
		CLRR 	21H 			//004D 	0121
		LDR 	20H,0 			//004E 	0820
		SUBWR 	21H,0 			//004F 	0C21
		BTSC 	STATUS,0 		//0050 	1403
		RET		 					//0051 	0004

		//;test_61f13x_INT.C: 49: {
		//;test_61f13x_INT.C: 50: __nop();
		NOP		 					//0052 	0000
		BCR 	STATUS,5 		//0053 	1283
		BCR 	STATUS,6 		//0054 	1303
		INCR	21H,1 			//0055 	09A1
		LJUMP 	4EH 			//0056 	384E

		//;test_61f13x_INT.C: 133: POWER_INITIAL();
		BCR 	PCLATH,3 		//0057 	118A
		LCALL 	72H 			//0058 	3072
		BCR 	PCLATH,3 		//0059 	118A

		//;test_61f13x_INT.C: 135: {
		//;test_61f13x_INT.C: 136: for(FCount=0;FCount<100;FCount++)
		BCR 	STATUS,5 		//005A 	1283
		BCR 	STATUS,6 		//005B 	1303
		CLRR 	25H 			//005C 	0125

		//;test_61f13x_INT.C: 137: {
		//;test_61f13x_INT.C: 138: PA2 = 1;
		BSR 	5H,2 			//005D 	1905

		//;test_61f13x_INT.C: 139: DelayMs(10);
		LDWI 	AH 			//005E 	2A0A
		BCR 	PCLATH,3 		//005F 	118A
		LCALL 	3BH 			//0060 	303B
		BCR 	PCLATH,3 		//0061 	118A

		//;test_61f13x_INT.C: 140: PA2 = 0;
		BCR 	5H,2 			//0062 	1105

		//;test_61f13x_INT.C: 141: DelayMs(10);
		LDWI 	AH 			//0063 	2A0A
		BCR 	PCLATH,3 		//0064 	118A
		LCALL 	3BH 			//0065 	303B
		BCR 	PCLATH,3 		//0066 	118A
		LDWI 	64H 			//0067 	2A64
		INCR	25H,1 			//0068 	09A5
		SUBWR 	25H,0 			//0069 	0C25
		BTSS 	STATUS,0 		//006A 	1C03
		LJUMP 	5DH 			//006B 	385D

		//;test_61f13x_INT.C: 142: }
		//;test_61f13x_INT.C: 143: INT_INITIAL();
		BCR 	PCLATH,3 		//006C 	118A
		LCALL 	87H 			//006D 	3087
		BCR 	PCLATH,3 		//006E 	118A

		//;test_61f13x_INT.C: 144: GIE = 1;
		BSR 	INTCON,7 		//006F 	1B8B
		SLEEP	 			//0070 	0002
		LJUMP 	5AH 			//0071 	385A

		//;test_61f13x_INT.C: 78: OSCCON = 0B01110001;
		LDWI 	71H 			//0072 	2A71
		BSR 	STATUS,5 		//0073 	1A83
		STR 	FH 			//0074 	018F

		//;test_61f13x_INT.C: 79: INTCON = 0;
		CLRR 	INTCON 			//0075 	010B

		//;test_61f13x_INT.C: 80: OPTION = 0B00001000;
		LDWI 	8H 			//0076 	2A08
		STR 	1H 			//0077 	0181

		//;test_61f13x_INT.C: 82: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0078 	1283
		CLRR 	5H 			//0079 	0105

		//;test_61f13x_INT.C: 83: TRISA = 0B00010000;
		LDWI 	10H 			//007A 	2A10
		BSR 	STATUS,5 		//007B 	1A83
		STR 	5H 			//007C 	0185

		//;test_61f13x_INT.C: 85: PORTC = 0B00000000;
		BCR 	STATUS,5 		//007D 	1283
		CLRR 	7H 			//007E 	0107

		//;test_61f13x_INT.C: 86: TRISC = 0B00000000;
		BSR 	STATUS,5 		//007F 	1A83
		CLRR 	7H 			//0080 	0107

		//;test_61f13x_INT.C: 88: WPUA = 0B00010000;
		STR 	15H 			//0081 	0195

		//;test_61f13x_INT.C: 90: WPUC = 0B00000000;
		CLRR 	13H 			//0082 	0113

		//;test_61f13x_INT.C: 92: ANSEL0 = 0B00000000;
		BCR 	STATUS,5 		//0083 	1283
		BSR 	STATUS,6 		//0084 	1B03
		CLRR 	1EH 			//0085 	011E
		RET		 					//0086 	0004

		//;test_61f13x_INT.C: 119: TRISA4 =1;
		BSR 	STATUS,5 		//0087 	1A83
		BSR 	5H,4 			//0088 	1A05

		//;test_61f13x_INT.C: 120: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0089 	1283
		LDR 	5H,0 			//008A 	0805

		//;test_61f13x_INT.C: 121: INTEDG =1;
		BSR 	STATUS,5 		//008B 	1A83
		ORG		008CH
		BSR 	1H,6 			//008C 	1B01

		//;test_61f13x_INT.C: 122: INTF =0;
		BCR 	INTCON,1 		//008D 	108B

		//;test_61f13x_INT.C: 123: INTE =1;
		BSR 	INTCON,4 		//008E 	1A0B
		RET		 					//008F 	0004
			END
