//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_EEReadData		EQU		72H
//		EEPROMwrite@EEAddr		EQU		71H
//		EEPROMwrite@EEAddr		EQU		71H
//		EEPROMwrite@Data		EQU		70H
//		EEPROMwrite@EEAddr		EQU		71H
//		EEPROMread@EEAddr		EQU		70H
//		EEPROMread@ReEEPROMread		EQU		71H
//		EEPROMread@EEAddr		EQU		70H
//		EEPROMread@EEAddr		EQU		70H
//-----------------------Variable END---------------------------------

		ORG		0000H
		LJUMP 	3FDH 			//0000 	3BFD
		ORG		03C4H
		STR 	70H 			//03C4 	01F0

		//;test_60f01x_EEPROM.C: 52: unsigned char ReEEPROMread;
		//;test_60f01x_EEPROM.C: 53: EEADR = EEAddr;
		STR 	1BH 			//03C5 	019B

		//;test_60f01x_EEPROM.C: 54: RD = 1;
		BSR 	1CH,0 			//03C6 	181C

		//;test_60f01x_EEPROM.C: 55: ReEEPROMread = EEDAT;
		LDR 	1AH,0 			//03C7 	081A
		STR 	71H 			//03C8 	01F1

		//;test_60f01x_EEPROM.C: 56: return ReEEPROMread;
		RET		 					//03C9 	0004

		//;test_60f01x_EEPROM.C: 31: OSCCON = 0B01110000;
		LDWI 	70H 			//03CA 	2A70
		BSR 	STATUS,5 		//03CB 	1A83
		STR 	FH 			//03CC 	018F

		//;test_60f01x_EEPROM.C: 33: INTCON = 0;
		CLRR 	INTCON 			//03CD 	010B

		//;test_60f01x_EEPROM.C: 34: OPTION = 0B00001000;
		LDWI 	8H 			//03CE 	2A08
		STR 	1H 			//03CF 	0181

		//;test_60f01x_EEPROM.C: 35: PORTA = 0B00000000;
		BCR 	STATUS,5 		//03D0 	1283
		CLRR 	5H 			//03D1 	0105

		//;test_60f01x_EEPROM.C: 36: TRISA = 0B00000000;
		BSR 	STATUS,5 		//03D2 	1A83
		CLRR 	5H 			//03D3 	0105

		//;test_60f01x_EEPROM.C: 37: WPUA = 0B00000000;
		CLRR 	15H 			//03D4 	0115

		//;test_60f01x_EEPROM.C: 39: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//03D5 	1283
		CLRR 	1BH 			//03D6 	011B
		RET		 					//03D7 	0004

		//;test_60f01x_EEPROM.C: 85: POWER_INITIAL();
		LCALL 	3CAH 			//03D8 	33CA

		//;test_60f01x_EEPROM.C: 86: EEPROMwrite(0xFF,0xAA);
		LDWI 	AAH 			//03D9 	2AAA
		STR 	70H 			//03DA 	01F0
		LDWI 	FFH 			//03DB 	2AFF
		LCALL 	3EAH 			//03DC 	33EA

		//;test_60f01x_EEPROM.C: 87: EEPROMwrite(0xFF,0xAA);
		LDWI 	AAH 			//03DD 	2AAA
		STR 	70H 			//03DE 	01F0
		LDWI 	FFH 			//03DF 	2AFF
		LCALL 	3EAH 			//03E0 	33EA

		//;test_60f01x_EEPROM.C: 89: EEReadData = EEPROMread(0x12);
		LDWI 	12H 			//03E1 	2A12
		LCALL 	3C4H 			//03E2 	33C4
		STR 	72H 			//03E3 	01F2

		//;test_60f01x_EEPROM.C: 90: EEPROMwrite(0x13,~EEReadData);
		COMR 	72H,0 			//03E4 	0F72
		STR 	70H 			//03E5 	01F0
		LDWI 	13H 			//03E6 	2A13
		LCALL 	3EAH 			//03E7 	33EA

		//;test_60f01x_EEPROM.C: 93: {
		//;test_60f01x_EEPROM.C: 94: __nop();
		NOP		 					//03E8 	0000
		LJUMP 	3E8H 			//03E9 	3BE8
		STR 	71H 			//03EA 	01F1

		//;test_60f01x_EEPROM.C: 67: GIE = 0;
		BCR 	INTCON,7 		//03EB 	138B

		//;test_60f01x_EEPROM.C: 68: while(GIE);
		BTSC 	INTCON,7 		//03EC 	178B
		LJUMP 	3ECH 			//03ED 	3BEC

		//;test_60f01x_EEPROM.C: 69: EEADR = EEAddr;
		LDR 	71H,0 			//03EE 	0871
		BSR 	STATUS,5 		//03EF 	1A83
		STR 	1BH 			//03F0 	019B

		//;test_60f01x_EEPROM.C: 70: EEDAT = Data;
		LDR 	70H,0 			//03F1 	0870
		STR 	1AH 			//03F2 	019A

		//;test_60f01x_EEPROM.C: 71: EEIF = 0;
		BCR 	STATUS,5 		//03F3 	1283
		BCR 	CH,7 			//03F4 	138C

		//;test_60f01x_EEPROM.C: 72: EECON1|= 0x34;
		LDWI 	34H 			//03F5 	2A34
		BSR 	STATUS,5 		//03F6 	1A83
		IORWR 	1CH,1 			//03F7 	039C

		//;test_60f01x_EEPROM.C: 73: WR = 1;
		BSR 	1DH,0 			//03F8 	181D

		//;test_60f01x_EEPROM.C: 74: while(WR);
		BTSC 	1DH,0 			//03F9 	141D
		LJUMP 	3F9H 			//03FA 	3BF9

		//;test_60f01x_EEPROM.C: 75: GIE = 1;
		BSR 	INTCON,7 		//03FB 	1B8B
		ORG		03FCH
		RET		 					//03FC 	0004
		CLRR 	72H 			//03FD 	0172
		CLRR 	STATUS 			//03FE 	0103
		LJUMP 	3D8H 			//03FF 	3BD8
			END
