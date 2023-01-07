//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_EEReadData		EQU		72H
//		EEPROMwrite@EEAddr		EQU		71H
//		EEPROMwrite@Data		EQU		70H
//		EEPROMwrite@EEAddr		EQU		C00000H
//		EEPROMread@EEAddr		EQU		70H
//		EEPROMread@ReEEPROMread		EQU		71H
//		EEPROMread@EEAddr		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7FDH 			//0000 	3FFD
		ORG		07BDH
		STR 	70H 			//07BD 	01F0

		//;test_61f02x_EEPROM.C: 58: unsigned char ReEEPROMread;
		//;test_61f02x_EEPROM.C: 60: EEADR = EEAddr;
		STR 	1BH 			//07BE 	019B

		//;test_61f02x_EEPROM.C: 61: RD = 1;
		BSR 	1CH,0 			//07BF 	181C

		//;test_61f02x_EEPROM.C: 62: ReEEPROMread = EEDAT;
		LDR 	1AH,0 			//07C0 	081A
		STR 	71H 			//07C1 	01F1

		//;test_61f02x_EEPROM.C: 63: return ReEEPROMread;
		RET		 					//07C2 	0004

		//;test_61f02x_EEPROM.C: 93: POWER_INITIAL();
		LCALL 	7E8H 			//07C3 	37E8

		//;test_61f02x_EEPROM.C: 94: EEPROMwrite(0xff,0xaa);
		LDWI 	AAH 			//07C4 	2AAA
		ORG		07C5H
		STR 	70H 			//07C5 	01F0
		LDWI 	FFH 			//07C6 	2AFF
		LCALL 	7D5H 			//07C7 	37D5

		//;test_61f02x_EEPROM.C: 95: EEPROMwrite(0xff,0xaa);
		LDWI 	AAH 			//07C8 	2AAA
		STR 	70H 			//07C9 	01F0
		LDWI 	FFH 			//07CA 	2AFF
		LCALL 	7D5H 			//07CB 	37D5

		//;test_61f02x_EEPROM.C: 97: EEReadData = EEPROMread(0x12);
		LDWI 	12H 			//07CC 	2A12
		ORG		07CDH
		LCALL 	7BDH 			//07CD 	37BD
		STR 	72H 			//07CE 	01F2

		//;test_61f02x_EEPROM.C: 98: EEPROMwrite(0x13,~EEReadData);
		COMR 	72H,0 			//07CF 	0F72
		STR 	70H 			//07D0 	01F0
		LDWI 	13H 			//07D1 	2A13
		LCALL 	7D5H 			//07D2 	37D5

		//;test_61f02x_EEPROM.C: 100: {
		//;test_61f02x_EEPROM.C: 101: __nop();
		NOP		 					//07D3 	0000
		LJUMP 	7D3H 			//07D4 	3FD3
		ORG		07D5H
		STR 	71H 			//07D5 	01F1

		//;test_61f02x_EEPROM.C: 75: GIE = 0;
		BCR 	INTCON,7 		//07D6 	138B

		//;test_61f02x_EEPROM.C: 76: while(GIE);
		BTSC 	INTCON,7 		//07D7 	178B
		LJUMP 	7D7H 			//07D8 	3FD7

		//;test_61f02x_EEPROM.C: 77: EEADR = EEAddr;
		LDR 	71H,0 			//07D9 	0871
		BSR 	STATUS,5 		//07DA 	1A83
		STR 	1BH 			//07DB 	019B

		//;test_61f02x_EEPROM.C: 78: EEDAT = Data;
		LDR 	70H,0 			//07DC 	0870
		ORG		07DDH
		STR 	1AH 			//07DD 	019A

		//;test_61f02x_EEPROM.C: 79: EEIF = 0;
		BCR 	STATUS,5 		//07DE 	1283
		BCR 	CH,7 			//07DF 	138C

		//;test_61f02x_EEPROM.C: 80: EECON1 = 0x34;
		LDWI 	34H 			//07E0 	2A34
		BSR 	STATUS,5 		//07E1 	1A83
		STR 	1CH 			//07E2 	019C

		//;test_61f02x_EEPROM.C: 81: WR = 1;
		BSR 	1DH,0 			//07E3 	181D

		//;test_61f02x_EEPROM.C: 82: while(WR);
		BTSC 	1DH,0 			//07E4 	141D
		ORG		07E5H
		LJUMP 	7E4H 			//07E5 	3FE4

		//;test_61f02x_EEPROM.C: 83: GIE = 1;
		BSR 	INTCON,7 		//07E6 	1B8B
		RET		 					//07E7 	0004

		//;test_61f02x_EEPROM.C: 34: OSCCON = 0B01110001;
		LDWI 	71H 			//07E8 	2A71
		BSR 	STATUS,5 		//07E9 	1A83
		STR 	FH 			//07EA 	018F

		//;test_61f02x_EEPROM.C: 35: INTCON = 0;
		CLRR 	INTCON 			//07EB 	010B

		//;test_61f02x_EEPROM.C: 36: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07EC 	1283
		ORG		07EDH
		CLRR 	5H 			//07ED 	0105

		//;test_61f02x_EEPROM.C: 37: TRISA = 0B00000000;
		BSR 	STATUS,5 		//07EE 	1A83
		CLRR 	5H 			//07EF 	0105

		//;test_61f02x_EEPROM.C: 38: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07F0 	1283
		CLRR 	7H 			//07F1 	0107

		//;test_61f02x_EEPROM.C: 39: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07F2 	1A83
		CLRR 	7H 			//07F3 	0107

		//;test_61f02x_EEPROM.C: 40: WPUA = 0;
		CLRR 	15H 			//07F4 	0115
		ORG		07F5H

		//;test_61f02x_EEPROM.C: 41: WPUC = 0;
		CLRR 	8H 			//07F5 	0108

		//;test_61f02x_EEPROM.C: 43: OPTION = 0B00001000;
		LDWI 	8H 			//07F6 	2A08
		STR 	1H 			//07F7 	0181

		//;test_61f02x_EEPROM.C: 44: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07F8 	1283
		CLRR 	1BH 			//07F9 	011B

		//;test_61f02x_EEPROM.C: 48: CMCON0 = 0B00000111;
		LDWI 	7H 			//07FA 	2A07
		STR 	19H 			//07FB 	0199
		RET		 					//07FC 	0004
		ORG		07FDH
		CLRR 	72H 			//07FD 	0172
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	7C3H 			//07FF 	3FC3
			END
