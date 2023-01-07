//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_SPIReadData		EQU		76H
//		SPI_Write@addr		EQU		73H
//		SPI_Write@dat		EQU		75H
//		SPI_Read@spidata		EQU		75H
//		SPI_Read@addr		EQU		73H
//		SPI_ReadStatus@status		EQU		72H
//		SPI_RW@data		EQU		71H
//		SPI_RW@i		EQU		70H
//		SPI_RW@data		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	7FEH 			//0000 	3FFE
		ORG		077DH

		//;test_61f02x_SPI.C: 68: PA7 = 1;
		BSR 	5H,7 			//077D 	1B85

		//;test_61f02x_SPI.C: 69: PA6 = 0;
		BCR 	5H,6 			//077E 	1305

		//;test_61f02x_SPI.C: 70: PA2 = 0;
		BCR 	5H,2 			//077F 	1105
		RET		 					//0780 	0004

		//;test_61f02x_SPI.C: 116: PA7=0;
		BCR 	5H,7 			//0781 	1385

		//;test_61f02x_SPI.C: 117: SPI_RW(0x04);
		LDWI 	4H 			//0782 	2A04
		LCALL 	7DEH 			//0783 	37DE

		//;test_61f02x_SPI.C: 118: PA7=1;
		BSR 	5H,7 			//0784 	1B85
		ORG		0785H
		RET		 					//0785 	0004

		//;test_61f02x_SPI.C: 106: PA7=0;
		BCR 	5H,7 			//0786 	1385

		//;test_61f02x_SPI.C: 107: SPI_RW(0x06);
		LDWI 	6H 			//0787 	2A06
		LCALL 	7DEH 			//0788 	37DE

		//;test_61f02x_SPI.C: 108: PA7=1;
		BSR 	5H,7 			//0789 	1B85
		RET		 					//078A 	0004

		//;test_61f02x_SPI.C: 129: PA7=0;
		BCR 	5H,7 			//078B 	1385

		//;test_61f02x_SPI.C: 130: SPI_RW(0x05);
		LDWI 	5H 			//078C 	2A05
		ORG		078DH
		LCALL 	7DEH 			//078D 	37DE

		//;test_61f02x_SPI.C: 131: status = SPI_RW(0x00);
		LDWI 	0H 			//078E 	2A00
		LCALL 	7DEH 			//078F 	37DE
		STR 	72H 			//0790 	01F2

		//;test_61f02x_SPI.C: 132: PA7=1;
		BSR 	5H,7 			//0791 	1B85

		//;test_61f02x_SPI.C: 133: return status;
		RET		 					//0792 	0004

		//;test_61f02x_SPI.C: 193: POWER_INITIAL();
		LCALL 	7C7H 			//0793 	37C7

		//;test_61f02x_SPI.C: 194: init_25c64_io();
		LCALL 	77DH 			//0794 	377D
		ORG		0795H

		//;test_61f02x_SPI.C: 195: SPIReadData = SPI_Read(0x0012);
		LDWI 	12H 			//0795 	2A12
		STR 	73H 			//0796 	01F3
		CLRR 	74H 			//0797 	0174
		LCALL 	7A2H 			//0798 	37A2
		STR 	76H 			//0799 	01F6

		//;test_61f02x_SPI.C: 196: SPI_Write(0x0013,~SPIReadData);
		LDWI 	13H 			//079A 	2A13
		STR 	73H 			//079B 	01F3
		CLRR 	74H 			//079C 	0174
		ORG		079DH
		COMR 	76H,0 			//079D 	0F76
		STR 	75H 			//079E 	01F5
		LCALL 	7B2H 			//079F 	37B2

		//;test_61f02x_SPI.C: 198: {
		//;test_61f02x_SPI.C: 199: __nop();
		NOP		 					//07A0 	0000
		LJUMP 	7A0H 			//07A1 	3FA0

		//;test_61f02x_SPI.C: 156: unsigned char spidata;
		//;test_61f02x_SPI.C: 157: while(SPI_ReadStatus()&0x01);
		LCALL 	78BH 			//07A2 	378B
		ANDWI 	1H 			//07A3 	2401
		BTSS 	STATUS,2 		//07A4 	1D03
		ORG		07A5H
		LJUMP 	7A2H 			//07A5 	3FA2

		//;test_61f02x_SPI.C: 158: PA7=0;
		BCR 	5H,7 			//07A6 	1385

		//;test_61f02x_SPI.C: 159: SPI_RW(0x03);
		LDWI 	3H 			//07A7 	2A03
		LCALL 	7DEH 			//07A8 	37DE

		//;test_61f02x_SPI.C: 160: SPI_RW((unsigned char)((addr)>>8));
		LDR 	74H,0 			//07A9 	0874
		LCALL 	7DEH 			//07AA 	37DE

		//;test_61f02x_SPI.C: 161: SPI_RW((unsigned char)addr);
		LDR 	73H,0 			//07AB 	0873
		LCALL 	7DEH 			//07AC 	37DE
		ORG		07ADH

		//;test_61f02x_SPI.C: 162: spidata = SPI_RW(0x00);
		LDWI 	0H 			//07AD 	2A00
		LCALL 	7DEH 			//07AE 	37DE
		STR 	75H 			//07AF 	01F5

		//;test_61f02x_SPI.C: 163: PA7=1;
		BSR 	5H,7 			//07B0 	1B85

		//;test_61f02x_SPI.C: 164: return spidata;
		RET		 					//07B1 	0004

		//;test_61f02x_SPI.C: 173: while(SPI_ReadStatus()&0x01);
		LCALL 	78BH 			//07B2 	378B
		ANDWI 	1H 			//07B3 	2401
		BTSS 	STATUS,2 		//07B4 	1D03
		ORG		07B5H
		LJUMP 	7B2H 			//07B5 	3FB2

		//;test_61f02x_SPI.C: 174: WriteEnable();
		LCALL 	786H 			//07B6 	3786

		//;test_61f02x_SPI.C: 175: PA7=0;
		BCR 	5H,7 			//07B7 	1385

		//;test_61f02x_SPI.C: 176: SPI_RW(0x02);
		LDWI 	2H 			//07B8 	2A02
		LCALL 	7DEH 			//07B9 	37DE

		//;test_61f02x_SPI.C: 177: SPI_RW((unsigned char)((addr)>>8));
		LDR 	74H,0 			//07BA 	0874
		LCALL 	7DEH 			//07BB 	37DE

		//;test_61f02x_SPI.C: 178: SPI_RW((unsigned char)addr);
		LDR 	73H,0 			//07BC 	0873
		ORG		07BDH
		LCALL 	7DEH 			//07BD 	37DE

		//;test_61f02x_SPI.C: 180: SPI_RW(dat);
		LDR 	75H,0 			//07BE 	0875
		LCALL 	7DEH 			//07BF 	37DE

		//;test_61f02x_SPI.C: 181: PA7=1;
		BSR 	5H,7 			//07C0 	1B85

		//;test_61f02x_SPI.C: 182: WriteDisable();
		LCALL 	781H 			//07C1 	3781

		//;test_61f02x_SPI.C: 183: while(SPI_ReadStatus()&0x01);
		LCALL 	78BH 			//07C2 	378B
		ANDWI 	1H 			//07C3 	2401
		BTSC 	STATUS,2 		//07C4 	1503
		ORG		07C5H
		RET		 					//07C5 	0004
		LJUMP 	7C2H 			//07C6 	3FC2

		//;test_61f02x_SPI.C: 41: OSCCON = 0B01110001;
		LDWI 	71H 			//07C7 	2A71
		BSR 	STATUS,5 		//07C8 	1A83
		STR 	FH 			//07C9 	018F

		//;test_61f02x_SPI.C: 42: INTCON = 0;
		CLRR 	INTCON 			//07CA 	010B

		//;test_61f02x_SPI.C: 44: PORTA = 0B00000000;
		BCR 	STATUS,5 		//07CB 	1283
		CLRR 	5H 			//07CC 	0105
		ORG		07CDH

		//;test_61f02x_SPI.C: 45: TRISA = 0B00010000;
		LDWI 	10H 			//07CD 	2A10
		BSR 	STATUS,5 		//07CE 	1A83
		STR 	5H 			//07CF 	0185

		//;test_61f02x_SPI.C: 46: PORTC = 0B00000000;
		BCR 	STATUS,5 		//07D0 	1283
		CLRR 	7H 			//07D1 	0107

		//;test_61f02x_SPI.C: 47: TRISC = 0B00000000;
		BSR 	STATUS,5 		//07D2 	1A83
		CLRR 	7H 			//07D3 	0107

		//;test_61f02x_SPI.C: 48: WPUA = 0B00010000;
		STR 	15H 			//07D4 	0195
		ORG		07D5H

		//;test_61f02x_SPI.C: 49: WPUC = 0B00000000;
		CLRR 	8H 			//07D5 	0108

		//;test_61f02x_SPI.C: 51: ANSEL = 0B00000000;
		CLRR 	11H 			//07D6 	0111

		//;test_61f02x_SPI.C: 52: OPTION = 0B00001000;
		LDWI 	8H 			//07D7 	2A08
		STR 	1H 			//07D8 	0181

		//;test_61f02x_SPI.C: 53: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//07D9 	1283
		CLRR 	1BH 			//07DA 	011B

		//;test_61f02x_SPI.C: 57: CMCON0 = 0B00000111;
		LDWI 	7H 			//07DB 	2A07
		STR 	19H 			//07DC 	0199
		ORG		07DDH
		RET		 					//07DD 	0004
		STR 	71H 			//07DE 	01F1

		//;test_61f02x_SPI.C: 80: unsigned char i;
		//;test_61f02x_SPI.C: 81: for(i=0;i<8;i++)
		CLRR 	70H 			//07DF 	0170

		//;test_61f02x_SPI.C: 82: {
		//;test_61f02x_SPI.C: 83: if(data&0x80)
		BTSS 	71H,7 			//07E0 	1FF1
		LJUMP 	7E4H 			//07E1 	3FE4

		//;test_61f02x_SPI.C: 84: PA2 = 1;
		BSR 	5H,2 			//07E2 	1905
		LJUMP 	7E5H 			//07E3 	3FE5

		//;test_61f02x_SPI.C: 85: else
		//;test_61f02x_SPI.C: 86: PA2 = 0;
		BCR 	5H,2 			//07E4 	1105
		ORG		07E5H

		//;test_61f02x_SPI.C: 87: __nop();
		NOP		 					//07E5 	0000

		//;test_61f02x_SPI.C: 88: data<<=1;
		BCR 	STATUS,0 		//07E6 	1003
		RLR 	71H,1 			//07E7 	05F1

		//;test_61f02x_SPI.C: 89: PA6 = 1;
		BCR 	STATUS,5 		//07E8 	1283
		BCR 	STATUS,6 		//07E9 	1303
		BSR 	5H,6 			//07EA 	1B05

		//;test_61f02x_SPI.C: 90: __nop();
		NOP		 					//07EB 	0000

		//;test_61f02x_SPI.C: 91: if(PA4)
		BCR 	STATUS,5 		//07EC 	1283
		ORG		07EDH
		BCR 	STATUS,6 		//07ED 	1303
		BTSS 	5H,4 			//07EE 	1E05
		LJUMP 	7F2H 			//07EF 	3FF2

		//;test_61f02x_SPI.C: 92: data |= 0x01;
		BSR 	71H,0 			//07F0 	1871
		LJUMP 	7F3H 			//07F1 	3FF3

		//;test_61f02x_SPI.C: 93: else
		//;test_61f02x_SPI.C: 94: data &= 0xFE;
		BCR 	71H,0 			//07F2 	1071

		//;test_61f02x_SPI.C: 95: __nop();
		NOP		 					//07F3 	0000

		//;test_61f02x_SPI.C: 96: PA6 = 0;
		BCR 	STATUS,5 		//07F4 	1283
		ORG		07F5H
		BCR 	STATUS,6 		//07F5 	1303
		BCR 	5H,6 			//07F6 	1305
		LDWI 	8H 			//07F7 	2A08
		INCR	70H,1 			//07F8 	09F0
		SUBWR 	70H,0 			//07F9 	0C70
		BTSS 	STATUS,0 		//07FA 	1C03
		LJUMP 	7E0H 			//07FB 	3FE0

		//;test_61f02x_SPI.C: 97: }
		//;test_61f02x_SPI.C: 98: return data;
		LDR 	71H,0 			//07FC 	0871
		ORG		07FDH
		RET		 					//07FD 	0004
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	793H 			//07FF 	3F93
			END
