//Deviec:FT61F13X
//-----------------------Variable---------------------------------
//		EEPROMwrite@EEAddr		EQU		73H
//		EEPROMwrite@Data		EQU		72H
//		EEPROMwrite@EEAddr		EQU		C00000H
//		EEPROMread@EEAddr		EQU		72H
//		EEPROMread@ReEEPROMread		EQU		73H
//		EEPROMread@EEAddr		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	0BH 			//0001 	380B
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	PCLATH,0 		//0007 	080A
		STR 	71H 			//0008 	01F1
		BCR 	PCLATH,3 		//0009 	118A
		LJUMP 	4DH 			//000A 	384D
		BCR 	PCLATH,3 		//000B 	118A
		ORG		000CH
		LJUMP 	0DH 			//000C 	380D
		CLRR 	STATUS 			//000D 	0103
		BCR 	PCLATH,3 		//000E 	118A
		LJUMP 	10H 			//000F 	3810

		//;test_61f13x_EEPROM.C: 106: POWER_INITIAL();
		BCR 	PCLATH,3 		//0010 	118A
		LCALL 	3CH 			//0011 	303C
		BCR 	PCLATH,3 		//0012 	118A

		//;test_61f13x_EEPROM.C: 107: EEPROMwrite(0xff,0xaa);
		LDWI 	AAH 			//0013 	2AAA
		ORG		0014H
		STR 	72H 			//0014 	01F2
		LDWI 	FFH 			//0015 	2AFF
		BCR 	PCLATH,3 		//0016 	118A
		LCALL 	2AH 			//0017 	302A
		BCR 	PCLATH,3 		//0018 	118A

		//;test_61f13x_EEPROM.C: 108: EEPROMwrite(0xff,0xaa);
		LDWI 	AAH 			//0019 	2AAA
		STR 	72H 			//001A 	01F2
		LDWI 	FFH 			//001B 	2AFF
		ORG		001CH
		BCR 	PCLATH,3 		//001C 	118A
		LCALL 	2AH 			//001D 	302A
		BCR 	PCLATH,3 		//001E 	118A

		//;test_61f13x_EEPROM.C: 110: EEPROMwrite(0x13,0x55);
		LDWI 	55H 			//001F 	2A55
		STR 	72H 			//0020 	01F2
		LDWI 	13H 			//0021 	2A13
		BCR 	PCLATH,3 		//0022 	118A
		LCALL 	2AH 			//0023 	302A
		ORG		0024H
		BCR 	PCLATH,3 		//0024 	118A

		//;test_61f13x_EEPROM.C: 111: EEReadData = EEPROMread(0x13);
		LDWI 	13H 			//0025 	2A13
		BCR 	PCLATH,3 		//0026 	118A
		LCALL 	54H 			//0027 	3054
		BCR 	PCLATH,3 		//0028 	118A

		//;test_61f13x_EEPROM.C: 113: {
		//;test_61f13x_EEPROM.C: 114: EEReadData=0;
		LJUMP 	29H 			//0029 	3829
		STR 	73H 			//002A 	01F3

		//;test_61f13x_EEPROM.C: 88: GIE = 0;
		BCR 	INTCON,7 		//002B 	138B
		ORG		002CH

		//;test_61f13x_EEPROM.C: 89: while(GIE);
		BTSC 	INTCON,7 		//002C 	178B
		LJUMP 	2CH 			//002D 	382C

		//;test_61f13x_EEPROM.C: 90: EEADR = EEAddr;
		LDR 	73H,0 			//002E 	0873
		STR 	1BH 			//002F 	019B

		//;test_61f13x_EEPROM.C: 91: EEDAT = Data;
		LDR 	72H,0 			//0030 	0872
		STR 	1AH 			//0031 	019A

		//;test_61f13x_EEPROM.C: 92: EEIF = 0;
		BCR 	STATUS,5 		//0032 	1283
		BCR 	CH,7 			//0033 	138C
		ORG		0034H

		//;test_61f13x_EEPROM.C: 93: EECON1 |= 0x34;
		LDWI 	34H 			//0034 	2A34
		BSR 	STATUS,5 		//0035 	1A83
		IORWR 	1CH,1 			//0036 	039C

		//;test_61f13x_EEPROM.C: 94: WR = 1;
		BSR 	1DH,0 			//0037 	181D

		//;test_61f13x_EEPROM.C: 95: while(WR);
		BTSC 	1DH,0 			//0038 	141D
		LJUMP 	38H 			//0039 	3838

		//;test_61f13x_EEPROM.C: 96: GIE = 1;
		BSR 	INTCON,7 		//003A 	1B8B
		RET		 					//003B 	0004
		ORG		003CH

		//;test_61f13x_EEPROM.C: 41: OSCCON = 0B01110001;
		LDWI 	71H 			//003C 	2A71
		BSR 	STATUS,5 		//003D 	1A83
		STR 	FH 			//003E 	018F

		//;test_61f13x_EEPROM.C: 42: INTCON = 0;
		CLRR 	INTCON 			//003F 	010B

		//;test_61f13x_EEPROM.C: 44: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0040 	1283
		CLRR 	5H 			//0041 	0105

		//;test_61f13x_EEPROM.C: 45: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0042 	1A83
		CLRR 	5H 			//0043 	0105
		ORG		0044H

		//;test_61f13x_EEPROM.C: 46: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0044 	1283
		CLRR 	7H 			//0045 	0107

		//;test_61f13x_EEPROM.C: 47: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0046 	1A83
		CLRR 	7H 			//0047 	0107

		//;test_61f13x_EEPROM.C: 49: WPUA = 0B00000000;
		CLRR 	15H 			//0048 	0115

		//;test_61f13x_EEPROM.C: 50: WPUC = 0B00000000;
		CLRR 	13H 			//0049 	0113

		//;test_61f13x_EEPROM.C: 52: OPTION = 0B00001000;
		LDWI 	8H 			//004A 	2A08
		STR 	1H 			//004B 	0181
		ORG		004CH
		RET		 					//004C 	0004
		LDR 	71H,0 			//004D 	0871
		STR 	PCLATH 			//004E 	018A
		SWAPR 	70H,0 			//004F 	0770
		STR 	STATUS 			//0050 	0183
		SWAPR 	7EH,1 			//0051 	07FE
		SWAPR 	7EH,0 			//0052 	077E
		RETI		 			//0053 	0009
		ORG		0054H
		STR 	72H 			//0054 	01F2

		//;test_61f13x_EEPROM.C: 72: unsigned char ReEEPROMread;
		//;test_61f13x_EEPROM.C: 74: EEADR = EEAddr;
		STR 	1BH 			//0055 	019B

		//;test_61f13x_EEPROM.C: 75: RD = 1;
		BSR 	1CH,0 			//0056 	181C

		//;test_61f13x_EEPROM.C: 76: ReEEPROMread = EEDAT;
		LDR 	1AH,0 			//0057 	081A
		STR 	73H 			//0058 	01F3

		//;test_61f13x_EEPROM.C: 77: return ReEEPROMread;
		RET		 					//0059 	0004
			END
