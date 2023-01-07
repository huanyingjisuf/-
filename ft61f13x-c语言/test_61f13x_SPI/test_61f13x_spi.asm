//Deviec:FT61F13X
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
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FCH 			//0001 	3FFC
		ORG		076AH

		//;test_61f13x_SPI.C: 63: PA7 = 1;
		BCR 	STATUS,5 		//076A 	1283
		BSR 	5H,7 			//076B 	1B85

		//;test_61f13x_SPI.C: 64: PA6 = 0;
		BCR 	5H,6 			//076C 	1305

		//;test_61f13x_SPI.C: 65: PA2 = 0;
		BCR 	5H,2 			//076D 	1105
		RET		 					//076E 	0004

		//;test_61f13x_SPI.C: 43: OSCCON = 0B01110001;
		LDWI 	71H 			//076F 	2A71
		BSR 	STATUS,5 		//0770 	1A83
		STR 	FH 			//0771 	018F
		ORG		0772H

		//;test_61f13x_SPI.C: 44: OPTION = 0B00001000;
		LDWI 	8H 			//0772 	2A08
		STR 	1H 			//0773 	0181

		//;test_61f13x_SPI.C: 45: INTCON = 0;
		CLRR 	INTCON 			//0774 	010B

		//;test_61f13x_SPI.C: 46: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0775 	1283
		CLRR 	5H 			//0776 	0105

		//;test_61f13x_SPI.C: 47: TRISA = 0B00010000;
		LDWI 	10H 			//0777 	2A10
		BSR 	STATUS,5 		//0778 	1A83
		STR 	5H 			//0779 	0185
		ORG		077AH

		//;test_61f13x_SPI.C: 49: PORTC = 0B00000000;
		BCR 	STATUS,5 		//077A 	1283
		CLRR 	7H 			//077B 	0107

		//;test_61f13x_SPI.C: 50: TRISC = 0B00000000;
		BSR 	STATUS,5 		//077C 	1A83
		CLRR 	7H 			//077D 	0107

		//;test_61f13x_SPI.C: 52: WPUA = 0B00010000;
		STR 	15H 			//077E 	0195

		//;test_61f13x_SPI.C: 53: WPUC = 0B00000000;
		CLRR 	13H 			//077F 	0113
		RET		 					//0780 	0004

		//;test_61f13x_SPI.C: 188: POWER_INITIAL();
		BCR 	PCLATH,3 		//0781 	118A
		ORG		0782H
		LCALL 	76FH 			//0782 	376F
		BCR 	PCLATH,3 		//0783 	118A

		//;test_61f13x_SPI.C: 189: init_25c64_io();
		BCR 	PCLATH,3 		//0784 	118A
		LCALL 	76AH 			//0785 	376A
		BCR 	PCLATH,3 		//0786 	118A

		//;test_61f13x_SPI.C: 190: SPI_Write(0x0013,0x55);
		LDWI 	13H 			//0787 	2A13
		STR 	73H 			//0788 	01F3
		LDWI 	55H 			//0789 	2A55
		ORG		078AH
		CLRR 	74H 			//078A 	0174
		STR 	75H 			//078B 	01F5
		BCR 	PCLATH,3 		//078C 	118A
		LCALL 	7ACH 			//078D 	37AC
		BCR 	PCLATH,3 		//078E 	118A

		//;test_61f13x_SPI.C: 191: SPIReadData = SPI_Read(0x0013);
		LDWI 	13H 			//078F 	2A13
		STR 	73H 			//0790 	01F3
		CLRR 	74H 			//0791 	0174
		ORG		0792H
		BCR 	PCLATH,3 		//0792 	118A
		LCALL 	798H 			//0793 	3798
		BCR 	PCLATH,3 		//0794 	118A
		STR 	76H 			//0795 	01F6

		//;test_61f13x_SPI.C: 194: {
		//;test_61f13x_SPI.C: 195: __nop();
		NOP		 					//0796 	0000
		LJUMP 	796H 			//0797 	3F96

		//;test_61f13x_SPI.C: 151: unsigned char spidata;
		//;test_61f13x_SPI.C: 152: while(SPI_ReadStatus()&0x01);
		LCALL 	7E9H 			//0798 	37E9
		BCR 	PCLATH,3 		//0799 	118A
		ORG		079AH
		ANDWI 	1H 			//079A 	2401
		BTSS 	STATUS,2 		//079B 	1D03
		LJUMP 	798H 			//079C 	3F98

		//;test_61f13x_SPI.C: 153: PA7=0;
		BCR 	5H,7 			//079D 	1385

		//;test_61f13x_SPI.C: 154: SPI_RW(0x03);
		LDWI 	3H 			//079E 	2A03
		LCALL 	7C9H 			//079F 	37C9
		BCR 	PCLATH,3 		//07A0 	118A

		//;test_61f13x_SPI.C: 155: SPI_RW((unsigned char)((addr)>>8));
		LDR 	74H,0 			//07A1 	0874
		ORG		07A2H
		LCALL 	7C9H 			//07A2 	37C9
		BCR 	PCLATH,3 		//07A3 	118A

		//;test_61f13x_SPI.C: 156: SPI_RW((unsigned char)addr);
		LDR 	73H,0 			//07A4 	0873
		LCALL 	7C9H 			//07A5 	37C9
		BCR 	PCLATH,3 		//07A6 	118A

		//;test_61f13x_SPI.C: 157: spidata = SPI_RW(0x00);
		LDWI 	0H 			//07A7 	2A00
		LCALL 	7C9H 			//07A8 	37C9
		STR 	75H 			//07A9 	01F5
		ORG		07AAH

		//;test_61f13x_SPI.C: 158: PA7=1;
		BSR 	5H,7 			//07AA 	1B85

		//;test_61f13x_SPI.C: 159: return spidata;
		RET		 					//07AB 	0004

		//;test_61f13x_SPI.C: 168: while(SPI_ReadStatus()&0x01);
		LCALL 	7E9H 			//07AC 	37E9
		BCR 	PCLATH,3 		//07AD 	118A
		ANDWI 	1H 			//07AE 	2401
		BTSS 	STATUS,2 		//07AF 	1D03
		LJUMP 	7ACH 			//07B0 	3FAC

		//;test_61f13x_SPI.C: 169: WriteEnable();
		LCALL 	7F7H 			//07B1 	37F7
		ORG		07B2H
		BCR 	PCLATH,3 		//07B2 	118A

		//;test_61f13x_SPI.C: 170: PA7=0;
		BCR 	5H,7 			//07B3 	1385

		//;test_61f13x_SPI.C: 171: SPI_RW(0x02);
		LDWI 	2H 			//07B4 	2A02
		LCALL 	7C9H 			//07B5 	37C9
		BCR 	PCLATH,3 		//07B6 	118A

		//;test_61f13x_SPI.C: 172: SPI_RW((unsigned char)((addr)>>8));
		LDR 	74H,0 			//07B7 	0874
		LCALL 	7C9H 			//07B8 	37C9
		BCR 	PCLATH,3 		//07B9 	118A
		ORG		07BAH

		//;test_61f13x_SPI.C: 173: SPI_RW((unsigned char)addr);
		LDR 	73H,0 			//07BA 	0873
		LCALL 	7C9H 			//07BB 	37C9
		BCR 	PCLATH,3 		//07BC 	118A

		//;test_61f13x_SPI.C: 175: SPI_RW(dat);
		LDR 	75H,0 			//07BD 	0875
		LCALL 	7C9H 			//07BE 	37C9
		BCR 	PCLATH,3 		//07BF 	118A

		//;test_61f13x_SPI.C: 176: PA7=1;
		BSR 	5H,7 			//07C0 	1B85

		//;test_61f13x_SPI.C: 177: WriteDisable();
		LCALL 	7F2H 			//07C1 	37F2
		ORG		07C2H
		BCR 	PCLATH,3 		//07C2 	118A

		//;test_61f13x_SPI.C: 178: while(SPI_ReadStatus()&0x01);
		LCALL 	7E9H 			//07C3 	37E9
		BCR 	PCLATH,3 		//07C4 	118A
		ANDWI 	1H 			//07C5 	2401
		BTSC 	STATUS,2 		//07C6 	1503
		RET		 					//07C7 	0004
		LJUMP 	7C3H 			//07C8 	3FC3
		STR 	71H 			//07C9 	01F1
		ORG		07CAH

		//;test_61f13x_SPI.C: 75: unsigned char i;
		//;test_61f13x_SPI.C: 76: for(i=0;i<8;i++)
		CLRR 	70H 			//07CA 	0170

		//;test_61f13x_SPI.C: 77: {
		//;test_61f13x_SPI.C: 78: if(data&0x80)
		BTSS 	71H,7 			//07CB 	1FF1
		LJUMP 	7CFH 			//07CC 	3FCF

		//;test_61f13x_SPI.C: 79: PA2 = 1;
		BSR 	5H,2 			//07CD 	1905
		LJUMP 	7D0H 			//07CE 	3FD0

		//;test_61f13x_SPI.C: 80: else
		//;test_61f13x_SPI.C: 81: PA2 = 0;
		BCR 	5H,2 			//07CF 	1105

		//;test_61f13x_SPI.C: 82: __nop();
		NOP		 					//07D0 	0000

		//;test_61f13x_SPI.C: 83: data<<=1;
		BCR 	STATUS,0 		//07D1 	1003
		ORG		07D2H
		RLR 	71H,1 			//07D2 	05F1

		//;test_61f13x_SPI.C: 84: PA6 = 1;
		BCR 	STATUS,5 		//07D3 	1283
		BCR 	STATUS,6 		//07D4 	1303
		BSR 	5H,6 			//07D5 	1B05

		//;test_61f13x_SPI.C: 85: __nop();
		NOP		 					//07D6 	0000

		//;test_61f13x_SPI.C: 86: if(PA4)
		BCR 	STATUS,5 		//07D7 	1283
		BCR 	STATUS,6 		//07D8 	1303
		BTSS 	5H,4 			//07D9 	1E05
		ORG		07DAH
		LJUMP 	7DDH 			//07DA 	3FDD

		//;test_61f13x_SPI.C: 87: data |= 0x01;
		BSR 	71H,0 			//07DB 	1871
		LJUMP 	7DEH 			//07DC 	3FDE

		//;test_61f13x_SPI.C: 88: else
		//;test_61f13x_SPI.C: 89: data &= 0xFE;
		BCR 	71H,0 			//07DD 	1071

		//;test_61f13x_SPI.C: 90: __nop();
		NOP		 					//07DE 	0000

		//;test_61f13x_SPI.C: 91: PA6 = 0;
		BCR 	STATUS,5 		//07DF 	1283
		BCR 	STATUS,6 		//07E0 	1303
		BCR 	5H,6 			//07E1 	1305
		ORG		07E2H
		LDWI 	8H 			//07E2 	2A08
		INCR	70H,1 			//07E3 	09F0
		SUBWR 	70H,0 			//07E4 	0C70
		BTSS 	STATUS,0 		//07E5 	1C03
		LJUMP 	7CBH 			//07E6 	3FCB

		//;test_61f13x_SPI.C: 92: }
		//;test_61f13x_SPI.C: 93: return data;
		LDR 	71H,0 			//07E7 	0871
		RET		 					//07E8 	0004

		//;test_61f13x_SPI.C: 124: PA7=0;
		BCR 	5H,7 			//07E9 	1385
		ORG		07EAH

		//;test_61f13x_SPI.C: 125: SPI_RW(0x05);
		LDWI 	5H 			//07EA 	2A05
		LCALL 	7C9H 			//07EB 	37C9
		BCR 	PCLATH,3 		//07EC 	118A

		//;test_61f13x_SPI.C: 126: status = SPI_RW(0x00);
		LDWI 	0H 			//07ED 	2A00
		LCALL 	7C9H 			//07EE 	37C9
		STR 	72H 			//07EF 	01F2

		//;test_61f13x_SPI.C: 127: PA7=1;
		BSR 	5H,7 			//07F0 	1B85

		//;test_61f13x_SPI.C: 128: return status;
		RET		 					//07F1 	0004
		ORG		07F2H

		//;test_61f13x_SPI.C: 111: PA7=0;
		BCR 	5H,7 			//07F2 	1385

		//;test_61f13x_SPI.C: 112: SPI_RW(0x04);
		LDWI 	4H 			//07F3 	2A04
		LCALL 	7C9H 			//07F4 	37C9

		//;test_61f13x_SPI.C: 113: PA7=1;
		BSR 	5H,7 			//07F5 	1B85
		RET		 					//07F6 	0004

		//;test_61f13x_SPI.C: 101: PA7=0;
		BCR 	5H,7 			//07F7 	1385

		//;test_61f13x_SPI.C: 102: SPI_RW(0x06);
		LDWI 	6H 			//07F8 	2A06
		LCALL 	7C9H 			//07F9 	37C9
		ORG		07FAH

		//;test_61f13x_SPI.C: 103: PA7=1;
		BSR 	5H,7 			//07FA 	1B85
		RET		 					//07FB 	0004
		CLRR 	76H 			//07FC 	0176
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		LJUMP 	781H 			//07FF 	3F81
			END
