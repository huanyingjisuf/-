//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_FCount		EQU		77H
//		DelayMs@Time		EQU		74H
//		DelayMs@b		EQU		76H
//		DelayMs@a		EQU		75H
//		DelayMs@Time		EQU		C00000H
//		DelayUs@Time		EQU		72H
//		DelayUs@a		EQU		73H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0AH 			//0000 	380A
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		LJUMP 	48H 			//0009 	3848
		LJUMP 	0BH 			//000A 	380B
		CLRR 	STATUS 			//000B 	0103
		ORG		000CH
		LJUMP 	23H 			//000C 	3823

		//;test_61f02x_INT.C: 51: OSCCON = 0B01110001;
		LDWI 	71H 			//000D 	2A71
		BSR 	STATUS,5 		//000E 	1A83
		STR 	FH 			//000F 	018F

		//;test_61f02x_INT.C: 52: INTCON = 0;
		CLRR 	INTCON 			//0010 	010B

		//;test_61f02x_INT.C: 53: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0011 	1283
		CLRR 	5H 			//0012 	0105

		//;test_61f02x_INT.C: 54: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0013 	1A83
		ORG		0014H
		CLRR 	5H 			//0014 	0105

		//;test_61f02x_INT.C: 55: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0015 	1283
		CLRR 	7H 			//0016 	0107

		//;test_61f02x_INT.C: 56: TRISC = 0B00000010;
		LDWI 	2H 			//0017 	2A02
		BSR 	STATUS,5 		//0018 	1A83
		STR 	7H 			//0019 	0187

		//;test_61f02x_INT.C: 58: WPUA = 0B00000000;
		CLRR 	15H 			//001A 	0115

		//;test_61f02x_INT.C: 59: WPUC = 0B00000000;
		CLRR 	8H 			//001B 	0108
		ORG		001CH

		//;test_61f02x_INT.C: 61: OPTION = 0B00001000;
		LDWI 	8H 			//001C 	2A08
		STR 	1H 			//001D 	0181

		//;test_61f02x_INT.C: 62: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//001E 	1283
		CLRR 	1BH 			//001F 	011B

		//;test_61f02x_INT.C: 66: CMCON0 = 0B00000111;
		LDWI 	7H 			//0020 	2A07
		STR 	19H 			//0021 	0199
		RET		 					//0022 	0004

		//;test_61f02x_INT.C: 122: POWER_INITIAL();
		LCALL 	DH 			//0023 	300D
		ORG		0024H

		//;test_61f02x_INT.C: 125: {
		//;test_61f02x_INT.C: 126: for(FCount=0;FCount<100;FCount++)
		CLRR 	77H 			//0024 	0177

		//;test_61f02x_INT.C: 127: {
		//;test_61f02x_INT.C: 128: PA3 = 1;
		BCR 	STATUS,5 		//0025 	1283
		BCR 	STATUS,6 		//0026 	1303
		BSR 	5H,3 			//0027 	1985

		//;test_61f02x_INT.C: 129: DelayMs(10);
		LDWI 	AH 			//0028 	2A0A
		LCALL 	38H 			//0029 	3038

		//;test_61f02x_INT.C: 130: PA3 = 0;
		BCR 	STATUS,5 		//002A 	1283
		BCR 	STATUS,6 		//002B 	1303
		ORG		002CH
		BCR 	5H,3 			//002C 	1185

		//;test_61f02x_INT.C: 131: DelayMs(10);
		LDWI 	AH 			//002D 	2A0A
		LCALL 	38H 			//002E 	3038
		LDWI 	64H 			//002F 	2A64
		INCR	77H,1 			//0030 	09F7
		SUBWR 	77H,0 			//0031 	0C77
		BTSS 	STATUS,0 		//0032 	1C03
		LJUMP 	25H 			//0033 	3825
		ORG		0034H

		//;test_61f02x_INT.C: 132: }
		//;test_61f02x_INT.C: 133: INT_INITIAL();
		LCALL 	5DH 			//0034 	305D

		//;test_61f02x_INT.C: 134: GIE = 1;
		BSR 	INTCON,7 		//0035 	1B8B
		SLEEP	 			//0036 	0002
		LJUMP 	24H 			//0037 	3824
		STR 	74H 			//0038 	01F4

		//;test_61f02x_INT.C: 90: unsigned char a,b;
		//;test_61f02x_INT.C: 91: for(a=0;a<Time;a++)
		CLRR 	75H 			//0039 	0175
		LDR 	74H,0 			//003A 	0874
		SUBWR 	75H,0 			//003B 	0C75
		ORG		003CH
		BTSC 	STATUS,0 		//003C 	1403
		RET		 					//003D 	0004

		//;test_61f02x_INT.C: 92: {
		//;test_61f02x_INT.C: 93: for(b=0;b<5;b++)
		CLRR 	76H 			//003E 	0176

		//;test_61f02x_INT.C: 94: {
		//;test_61f02x_INT.C: 95: DelayUs(197);
		LDWI 	C5H 			//003F 	2AC5
		LCALL 	54H 			//0040 	3054
		LDWI 	5H 			//0041 	2A05
		INCR	76H,1 			//0042 	09F6
		SUBWR 	76H,0 			//0043 	0C76
		ORG		0044H
		BTSS 	STATUS,0 		//0044 	1C03
		LJUMP 	3FH 			//0045 	383F
		INCR	75H,1 			//0046 	09F5
		LJUMP 	3AH 			//0047 	383A

		//;test_61f02x_INT.C: 37: if(INTE && INTF)
		BTSC 	INTCON,4 		//0048 	160B
		BTSS 	INTCON,1 		//0049 	1C8B
		LJUMP 	4DH 			//004A 	384D

		//;test_61f02x_INT.C: 38: {
		//;test_61f02x_INT.C: 39: INTF = 0;
		BCR 	INTCON,1 		//004B 	108B
		ORG		004CH

		//;test_61f02x_INT.C: 40: INTE = 0;
		BCR 	INTCON,4 		//004C 	120B
		LDR 	71H,0 			//004D 	0871
		STR 	PCLATH 			//004E 	018A
		SWAPR 	70H,0 			//004F 	0770
		STR 	STATUS 			//0050 	0183
		SWAPR 	7EH,1 			//0051 	07FE
		SWAPR 	7EH,0 			//0052 	077E
		RETI		 			//0053 	0009
		ORG		0054H
		STR 	72H 			//0054 	01F2

		//;test_61f02x_INT.C: 76: unsigned char a;
		//;test_61f02x_INT.C: 77: for(a=0;a<Time;a++)
		CLRR 	73H 			//0055 	0173
		LDR 	72H,0 			//0056 	0872
		SUBWR 	73H,0 			//0057 	0C73
		BTSC 	STATUS,0 		//0058 	1403
		RET		 					//0059 	0004

		//;test_61f02x_INT.C: 78: {
		//;test_61f02x_INT.C: 79: __nop();
		NOP		 					//005A 	0000
		INCR	73H,1 			//005B 	09F3
		ORG		005CH
		LJUMP 	56H 			//005C 	3856

		//;test_61f02x_INT.C: 107: TRISC1 = 1;
		BSR 	STATUS,5 		//005D 	1A83
		BCR 	STATUS,6 		//005E 	1303
		BSR 	7H,1 			//005F 	1887

		//;test_61f02x_INT.C: 108: ANSEL = 0B00000000;
		CLRR 	11H 			//0060 	0111

		//;test_61f02x_INT.C: 110: INTEDG =1;
		BSR 	1H,6 			//0061 	1B01

		//;test_61f02x_INT.C: 111: INTF =0;
		BCR 	INTCON,1 		//0062 	108B

		//;test_61f02x_INT.C: 112: INTE =1;
		BSR 	INTCON,4 		//0063 	1A0B
		ORG		0064H
		RET		 					//0064 	0004
			END
