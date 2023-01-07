//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_IICReadData		EQU		77H
//		IIC_WRITE@address		EQU		76H
//		IIC_WRITE@data		EQU		75H
//		IIC_WRITE@address		EQU		C00000H
//		IIC_READ@address		EQU		75H
//		IIC_READ@iicdata		EQU		76H
//		IIC_READ@address		EQU		C00000H
//		IIC_Wait_Ack@ucErrTime		EQU		72H
//		IIC_Send_Byte@txd		EQU		73H
//		IIC_Send_Byte@t		EQU		74H
//		IIC_Send_Byte@txd		EQU		C00000H
//		IIC_Read_Byte@i		EQU		73H
//		IIC_Read_Byte@receive		EQU		72H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	3FEH 			//0000 	3BFE
		ORG		032BH
		STR 	70H 			//032B 	01F0

		//;test_60f01x_IIC.C: 60: unsigned char a;
		//;test_60f01x_IIC.C: 61: for(a=0;a<Time;a++)
		CLRR 	71H 			//032C 	0171
		LDR 	70H,0 			//032D 	0870
		SUBWR 	71H,0 			//032E 	0C71
		BTSC 	STATUS,0 		//032F 	1403
		RET		 					//0330 	0004

		//;test_60f01x_IIC.C: 62: {
		//;test_60f01x_IIC.C: 63: __nop();
		NOP		 					//0331 	0000
		INCR	71H,1 			//0332 	09F1
		ORG		0333H
		LJUMP 	32DH 			//0333 	3B2D

		//;test_60f01x_IIC.C: 259: POWER_INITIAL();
		LCALL 	33EH 			//0334 	333E

		//;test_60f01x_IIC.C: 261: IICReadData = IIC_READ(0x12);
		LDWI 	12H 			//0335 	2A12
		LCALL 	3BDH 			//0336 	33BD
		STR 	77H 			//0337 	01F7

		//;test_60f01x_IIC.C: 262: IIC_WRITE(0x13,~IICReadData);
		COMR 	77H,0 			//0338 	0F77
		STR 	75H 			//0339 	01F5
		LDWI 	13H 			//033A 	2A13
		ORG		033BH
		LCALL 	379H 			//033B 	3379

		//;test_60f01x_IIC.C: 264: {
		//;test_60f01x_IIC.C: 265: __nop();
		NOP		 					//033C 	0000
		LJUMP 	33CH 			//033D 	3B3C

		//;test_60f01x_IIC.C: 38: OSCCON = 0B01110000;
		LDWI 	70H 			//033E 	2A70
		BSR 	STATUS,5 		//033F 	1A83
		STR 	FH 			//0340 	018F

		//;test_60f01x_IIC.C: 40: INTCON = 0;
		CLRR 	INTCON 			//0341 	010B

		//;test_60f01x_IIC.C: 41: OPTION = 0B00001000;
		LDWI 	8H 			//0342 	2A08
		ORG		0343H
		STR 	1H 			//0343 	0181

		//;test_60f01x_IIC.C: 43: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0344 	1283
		CLRR 	5H 			//0345 	0105

		//;test_60f01x_IIC.C: 44: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0346 	1A83
		CLRR 	5H 			//0347 	0105

		//;test_60f01x_IIC.C: 46: WPUA = 0B00000000;
		CLRR 	15H 			//0348 	0115

		//;test_60f01x_IIC.C: 47: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0349 	1283
		CLRR 	1BH 			//034A 	011B
		ORG		034BH
		RET		 					//034B 	0004

		//;test_60f01x_IIC.C: 151: PA4=0;
		BCR 	STATUS,5 		//034C 	1283
		BCR 	5H,4 			//034D 	1205

		//;test_60f01x_IIC.C: 152: TRISA2 =0;
		BSR 	STATUS,5 		//034E 	1A83
		BCR 	5H,2 			//034F 	1105

		//;test_60f01x_IIC.C: 153: PA2=1;
		BCR 	STATUS,5 		//0350 	1283
		BSR 	5H,2 			//0351 	1905

		//;test_60f01x_IIC.C: 154: DelayUs(5);
		LDWI 	5H 			//0352 	2A05
		ORG		0353H
		LCALL 	32BH 			//0353 	332B

		//;test_60f01x_IIC.C: 155: PA4=1;
		BCR 	STATUS,5 		//0354 	1283
		BSR 	5H,4 			//0355 	1A05

		//;test_60f01x_IIC.C: 156: DelayUs(5);
		LDWI 	5H 			//0356 	2A05
		LCALL 	32BH 			//0357 	332B

		//;test_60f01x_IIC.C: 157: PA4=0;
		BCR 	STATUS,5 		//0358 	1283
		BCR 	5H,4 			//0359 	1205
		RET		 					//035A 	0004
		ORG		035BH

		//;test_60f01x_IIC.C: 74: TRISA2 =0;
		BSR 	STATUS,5 		//035B 	1A83
		BCR 	5H,2 			//035C 	1105

		//;test_60f01x_IIC.C: 75: PA2=1;
		BCR 	STATUS,5 		//035D 	1283
		BSR 	5H,2 			//035E 	1905

		//;test_60f01x_IIC.C: 76: PA4=1;
		BSR 	5H,4 			//035F 	1A05

		//;test_60f01x_IIC.C: 77: DelayUs(10);
		LDWI 	AH 			//0360 	2A0A
		LCALL 	32BH 			//0361 	332B

		//;test_60f01x_IIC.C: 78: PA2=0;
		BCR 	STATUS,5 		//0362 	1283
		ORG		0363H
		BCR 	5H,2 			//0363 	1105

		//;test_60f01x_IIC.C: 79: DelayUs(10);
		LDWI 	AH 			//0364 	2A0A
		LCALL 	32BH 			//0365 	332B

		//;test_60f01x_IIC.C: 80: PA4=0;
		BCR 	STATUS,5 		//0366 	1283
		BCR 	5H,4 			//0367 	1205

		//;test_60f01x_IIC.C: 81: DelayUs(10);
		LDWI 	AH 			//0368 	2A0A
		LJUMP 	32BH 			//0369 	3B2B

		//;test_60f01x_IIC.C: 91: TRISA2 =0;
		BSR 	STATUS,5 		//036A 	1A83
		ORG		036BH
		BCR 	5H,2 			//036B 	1105

		//;test_60f01x_IIC.C: 92: PA4=0;
		BCR 	STATUS,5 		//036C 	1283
		BCR 	5H,4 			//036D 	1205

		//;test_60f01x_IIC.C: 93: PA2=0;
		BCR 	5H,2 			//036E 	1105

		//;test_60f01x_IIC.C: 94: DelayUs(10);
		LDWI 	AH 			//036F 	2A0A
		LCALL 	32BH 			//0370 	332B

		//;test_60f01x_IIC.C: 95: PA4=1;
		BCR 	STATUS,5 		//0371 	1283
		BSR 	5H,4 			//0372 	1A05
		ORG		0373H

		//;test_60f01x_IIC.C: 96: DelayUs(10);
		LDWI 	AH 			//0373 	2A0A
		LCALL 	32BH 			//0374 	332B

		//;test_60f01x_IIC.C: 97: PA2=1;
		BCR 	STATUS,5 		//0375 	1283
		BSR 	5H,2 			//0376 	1905

		//;test_60f01x_IIC.C: 98: DelayUs(10);
		LDWI 	AH 			//0377 	2A0A
		LJUMP 	32BH 			//0378 	3B2B
		STR 	76H 			//0379 	01F6

		//;test_60f01x_IIC.C: 237: IIC_WRITE_Begin:
		//;test_60f01x_IIC.C: 238: IIC_Start();
		LCALL 	35BH 			//037A 	335B
		ORG		037BH

		//;test_60f01x_IIC.C: 239: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//037B 	2AA0
		LCALL 	3D7H 			//037C 	33D7

		//;test_60f01x_IIC.C: 240: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	38EH 			//037D 	338E
		XORWI 	0H 			//037E 	2600
		BTSS 	STATUS,2 		//037F 	1D03
		LJUMP 	37AH 			//0380 	3B7A

		//;test_60f01x_IIC.C: 242: IIC_Send_Byte(address);
		LDR 	76H,0 			//0381 	0876
		LCALL 	3D7H 			//0382 	33D7
		ORG		0383H

		//;test_60f01x_IIC.C: 243: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	38EH 			//0383 	338E
		XORWI 	0H 			//0384 	2600
		BTSS 	STATUS,2 		//0385 	1D03
		LJUMP 	37AH 			//0386 	3B7A

		//;test_60f01x_IIC.C: 245: IIC_Send_Byte(data);
		LDR 	75H,0 			//0387 	0875
		LCALL 	3D7H 			//0388 	33D7

		//;test_60f01x_IIC.C: 246: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	38EH 			//0389 	338E
		XORWI 	0H 			//038A 	2600
		ORG		038BH
		BTSS 	STATUS,2 		//038B 	1D03
		LJUMP 	37AH 			//038C 	3B7A

		//;test_60f01x_IIC.C: 248: IIC_Stop();
		LJUMP 	36AH 			//038D 	3B6A

		//;test_60f01x_IIC.C: 109: unsigned char ucErrTime=0;
		CLRR 	72H 			//038E 	0172

		//;test_60f01x_IIC.C: 110: TRISA2 =1;
		BSR 	STATUS,5 		//038F 	1A83
		BSR 	5H,2 			//0390 	1905

		//;test_60f01x_IIC.C: 111: PA2=1;
		BCR 	STATUS,5 		//0391 	1283
		BSR 	5H,2 			//0392 	1905
		ORG		0393H

		//;test_60f01x_IIC.C: 112: DelayUs(5);
		LDWI 	5H 			//0393 	2A05
		LCALL 	32BH 			//0394 	332B

		//;test_60f01x_IIC.C: 113: PA4=1;
		BCR 	STATUS,5 		//0395 	1283
		BSR 	5H,4 			//0396 	1A05

		//;test_60f01x_IIC.C: 114: DelayUs(5);
		LDWI 	5H 			//0397 	2A05
		LCALL 	32BH 			//0398 	332B

		//;test_60f01x_IIC.C: 115: while(PA2)
		BCR 	STATUS,5 		//0399 	1283
		BTSS 	5H,2 			//039A 	1D05
		ORG		039BH
		LJUMP 	3A3H 			//039B 	3BA3
		LDWI 	FBH 			//039C 	2AFB

		//;test_60f01x_IIC.C: 116: {
		//;test_60f01x_IIC.C: 117: ucErrTime++;
		INCR	72H,1 			//039D 	09F2

		//;test_60f01x_IIC.C: 118: if(ucErrTime>250)
		SUBWR 	72H,0 			//039E 	0C72
		BTSS 	STATUS,0 		//039F 	1C03
		LJUMP 	399H 			//03A0 	3B99

		//;test_60f01x_IIC.C: 119: {
		//;test_60f01x_IIC.C: 120: IIC_Stop();
		LCALL 	36AH 			//03A1 	336A

		//;test_60f01x_IIC.C: 121: return 1;
		RETW 	1H 			//03A2 	2101
		ORG		03A3H

		//;test_60f01x_IIC.C: 122: }
		//;test_60f01x_IIC.C: 123: }
		//;test_60f01x_IIC.C: 124: PA4=0;
		BCR 	5H,4 			//03A3 	1205

		//;test_60f01x_IIC.C: 125: return 0;
		RETW 	0H 			//03A4 	2100

		//;test_60f01x_IIC.C: 192: unsigned char i,receive=0;
		CLRR 	72H 			//03A5 	0172

		//;test_60f01x_IIC.C: 193: TRISA2 =1;
		BSR 	STATUS,5 		//03A6 	1A83
		BSR 	5H,2 			//03A7 	1905

		//;test_60f01x_IIC.C: 194: for(i=0;i<8;i++ )
		CLRR 	73H 			//03A8 	0173

		//;test_60f01x_IIC.C: 195: {
		//;test_60f01x_IIC.C: 196: PA4=0;
		BCR 	STATUS,5 		//03A9 	1283
		BCR 	5H,4 			//03AA 	1205
		ORG		03ABH

		//;test_60f01x_IIC.C: 197: DelayUs(5);
		LDWI 	5H 			//03AB 	2A05
		LCALL 	32BH 			//03AC 	332B

		//;test_60f01x_IIC.C: 198: PA4=1;
		BCR 	STATUS,5 		//03AD 	1283
		BSR 	5H,4 			//03AE 	1A05

		//;test_60f01x_IIC.C: 199: receive<<=1;
		BCR 	STATUS,0 		//03AF 	1003
		RLR 	72H,1 			//03B0 	05F2

		//;test_60f01x_IIC.C: 200: if(PA2)receive++;
		BTSC 	5H,2 			//03B1 	1505
		INCR	72H,1 			//03B2 	09F2
		ORG		03B3H

		//;test_60f01x_IIC.C: 201: DelayUs(5);
		LDWI 	5H 			//03B3 	2A05
		LCALL 	32BH 			//03B4 	332B
		LDWI 	8H 			//03B5 	2A08
		INCR	73H,1 			//03B6 	09F3
		SUBWR 	73H,0 			//03B7 	0C73
		BTSS 	STATUS,0 		//03B8 	1C03
		LJUMP 	3A9H 			//03B9 	3BA9

		//;test_60f01x_IIC.C: 202: }
		//;test_60f01x_IIC.C: 203: IIC_NAck();
		LCALL 	34CH 			//03BA 	334C
		ORG		03BBH

		//;test_60f01x_IIC.C: 205: return receive;
		LDR 	72H,0 			//03BB 	0872
		RET		 					//03BC 	0004
		STR 	75H 			//03BD 	01F5

		//;test_60f01x_IIC.C: 217: IIC_Start();
		LCALL 	35BH 			//03BE 	335B

		//;test_60f01x_IIC.C: 218: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//03BF 	2AA0
		LCALL 	3D7H 			//03C0 	33D7

		//;test_60f01x_IIC.C: 219: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	38EH 			//03C1 	338E
		XORWI 	0H 			//03C2 	2600
		ORG		03C3H
		BTSS 	STATUS,2 		//03C3 	1D03
		LJUMP 	3BEH 			//03C4 	3BBE

		//;test_60f01x_IIC.C: 220: IIC_Send_Byte(address);
		LDR 	75H,0 			//03C5 	0875
		LCALL 	3D7H 			//03C6 	33D7

		//;test_60f01x_IIC.C: 221: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	38EH 			//03C7 	338E
		XORWI 	0H 			//03C8 	2600
		BTSS 	STATUS,2 		//03C9 	1D03
		LJUMP 	3BEH 			//03CA 	3BBE
		ORG		03CBH

		//;test_60f01x_IIC.C: 222: IIC_Start();
		LCALL 	35BH 			//03CB 	335B

		//;test_60f01x_IIC.C: 223: IIC_Send_Byte(0xa1);
		LDWI 	A1H 			//03CC 	2AA1
		LCALL 	3D7H 			//03CD 	33D7

		//;test_60f01x_IIC.C: 224: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	38EH 			//03CE 	338E
		XORWI 	0H 			//03CF 	2600
		BTSS 	STATUS,2 		//03D0 	1D03
		LJUMP 	3BEH 			//03D1 	3BBE

		//;test_60f01x_IIC.C: 225: iicdata=IIC_Read_Byte();
		LCALL 	3A5H 			//03D2 	33A5
		ORG		03D3H
		STR 	76H 			//03D3 	01F6

		//;test_60f01x_IIC.C: 226: IIC_Stop();
		LCALL 	36AH 			//03D4 	336A

		//;test_60f01x_IIC.C: 227: return iicdata;
		LDR 	76H,0 			//03D5 	0876
		RET		 					//03D6 	0004
		STR 	73H 			//03D7 	01F3

		//;test_60f01x_IIC.C: 167: unsigned char t;
		//;test_60f01x_IIC.C: 168: TRISA2 =0;
		BSR 	STATUS,5 		//03D8 	1A83
		BCR 	5H,2 			//03D9 	1105

		//;test_60f01x_IIC.C: 169: PA4=0;
		BCR 	STATUS,5 		//03DA 	1283
		ORG		03DBH
		BCR 	5H,4 			//03DB 	1205

		//;test_60f01x_IIC.C: 170: for(t=0;t<8;t++)
		CLRR 	74H 			//03DC 	0174

		//;test_60f01x_IIC.C: 171: {
		//;test_60f01x_IIC.C: 172: if((txd&0x80)>>7)
		LDR 	73H,0 			//03DD 	0873
		STR 	72H 			//03DE 	01F2
		LDWI 	7H 			//03DF 	2A07
		BCR 	STATUS,0 		//03E0 	1003
		RRR	72H,1 			//03E1 	06F2
		ADDWI 	FFH 			//03E2 	27FF
		ORG		03E3H
		BTSS 	STATUS,2 		//03E3 	1D03
		LJUMP 	3E0H 			//03E4 	3BE0
		BTSS 	72H,0 			//03E5 	1C72
		LJUMP 	3EAH 			//03E6 	3BEA

		//;test_60f01x_IIC.C: 173: PA2=1;
		BCR 	STATUS,5 		//03E7 	1283
		BSR 	5H,2 			//03E8 	1905
		LJUMP 	3ECH 			//03E9 	3BEC

		//;test_60f01x_IIC.C: 174: else
		//;test_60f01x_IIC.C: 175: PA2=0;
		BCR 	STATUS,5 		//03EA 	1283
		ORG		03EBH
		BCR 	5H,2 			//03EB 	1105
		LDWI 	5H 			//03EC 	2A05

		//;test_60f01x_IIC.C: 176: txd<<=1;
		BCR 	STATUS,0 		//03ED 	1003
		RLR 	73H,1 			//03EE 	05F3

		//;test_60f01x_IIC.C: 177: DelayUs(5);
		LCALL 	32BH 			//03EF 	332B

		//;test_60f01x_IIC.C: 178: PA4=1;
		BCR 	STATUS,5 		//03F0 	1283
		BSR 	5H,4 			//03F1 	1A05

		//;test_60f01x_IIC.C: 179: DelayUs(5);
		LDWI 	5H 			//03F2 	2A05
		ORG		03F3H
		LCALL 	32BH 			//03F3 	332B

		//;test_60f01x_IIC.C: 180: PA4=0;
		BCR 	STATUS,5 		//03F4 	1283
		BCR 	5H,4 			//03F5 	1205

		//;test_60f01x_IIC.C: 181: DelayUs(5);
		LDWI 	5H 			//03F6 	2A05
		LCALL 	32BH 			//03F7 	332B
		LDWI 	8H 			//03F8 	2A08
		INCR	74H,1 			//03F9 	09F4
		SUBWR 	74H,0 			//03FA 	0C74
		ORG		03FBH
		BTSC 	STATUS,0 		//03FB 	1403
		RET		 					//03FC 	0004
		LJUMP 	3DDH 			//03FD 	3BDD
		CLRR 	STATUS 			//03FE 	0103
		LJUMP 	334H 			//03FF 	3B34
			END
