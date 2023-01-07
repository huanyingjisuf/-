//Deviec:FT61F02X
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
		LJUMP 	7FEH 			//0000 	3FFE
		ORG		0718H
		STR 	70H 			//0718 	01F0

		//;test_61f02x_IIC.C: 66: unsigned char a;
		//;test_61f02x_IIC.C: 67: for(a=0;a<Time;a++)
		CLRR 	71H 			//0719 	0171
		LDR 	70H,0 			//071A 	0870
		SUBWR 	71H,0 			//071B 	0C71
		BTSC 	STATUS,0 		//071C 	1403
		RET		 					//071D 	0004

		//;test_61f02x_IIC.C: 68: {
		//;test_61f02x_IIC.C: 69: __nop();
		NOP		 					//071E 	0000
		INCR	71H,1 			//071F 	09F1
		ORG		0720H
		LJUMP 	71AH 			//0720 	3F1A

		//;test_61f02x_IIC.C: 265: POWER_INITIAL();
		LCALL 	76FH 			//0721 	376F

		//;test_61f02x_IIC.C: 266: IICReadData = IIC_READ(0x12);
		LDWI 	12H 			//0722 	2A12
		LCALL 	79CH 			//0723 	379C
		STR 	77H 			//0724 	01F7

		//;test_61f02x_IIC.C: 267: IIC_WRITE(0x13,~IICReadData);
		COMR 	77H,0 			//0725 	0F77
		STR 	75H 			//0726 	01F5
		LDWI 	13H 			//0727 	2A13
		ORG		0728H
		LCALL 	75AH 			//0728 	375A

		//;test_61f02x_IIC.C: 269: {
		//;test_61f02x_IIC.C: 270: __nop();
		NOP		 					//0729 	0000
		LJUMP 	729H 			//072A 	3F29

		//;test_61f02x_IIC.C: 97: TRISA2 = 0;
		//;test_61f02x_IIC.C: 98: PA4=0;
		LCALL 	7F4H 			//072B 	37F4

		//;test_61f02x_IIC.C: 99: PA2=0;
		BCR 	5H,2 			//072C 	1105

		//;test_61f02x_IIC.C: 100: DelayUs(10);
		LDWI 	AH 			//072D 	2A0A
		LCALL 	718H 			//072E 	3718

		//;test_61f02x_IIC.C: 101: PA4=1;
		BCR 	STATUS,5 		//072F 	1283
		ORG		0730H
		BCR 	STATUS,6 		//0730 	1303
		BSR 	5H,4 			//0731 	1A05

		//;test_61f02x_IIC.C: 102: DelayUs(10);
		LDWI 	AH 			//0732 	2A0A
		LCALL 	718H 			//0733 	3718

		//;test_61f02x_IIC.C: 103: PA2=1;
		BCR 	STATUS,5 		//0734 	1283
		BCR 	STATUS,6 		//0735 	1303
		BSR 	5H,2 			//0736 	1905

		//;test_61f02x_IIC.C: 104: DelayUs(10);
		LDWI 	AH 			//0737 	2A0A
		ORG		0738H
		LJUMP 	718H 			//0738 	3F18

		//;test_61f02x_IIC.C: 157: PA4=0;
		BCR 	STATUS,5 		//0739 	1283
		BCR 	STATUS,6 		//073A 	1303
		BCR 	5H,4 			//073B 	1205

		//;test_61f02x_IIC.C: 158: TRISA2 = 0;
		BSR 	STATUS,5 		//073C 	1A83
		BCR 	5H,2 			//073D 	1105

		//;test_61f02x_IIC.C: 159: PA2=1;
		BCR 	STATUS,5 		//073E 	1283
		BSR 	5H,2 			//073F 	1905
		ORG		0740H

		//;test_61f02x_IIC.C: 160: DelayUs(5);
		LDWI 	5H 			//0740 	2A05
		LCALL 	718H 			//0741 	3718

		//;test_61f02x_IIC.C: 161: PA4=1;
		//;test_61f02x_IIC.C: 162: DelayUs(5);
		LCALL 	7FAH 			//0742 	37FA
		LCALL 	718H 			//0743 	3718

		//;test_61f02x_IIC.C: 163: PA4=0;
		BCR 	STATUS,5 		//0744 	1283
		BCR 	STATUS,6 		//0745 	1303
		BCR 	5H,4 			//0746 	1205
		RET		 					//0747 	0004
		ORG		0748H

		//;test_61f02x_IIC.C: 80: TRISA2 = 0;
		BSR 	STATUS,5 		//0748 	1A83
		BCR 	STATUS,6 		//0749 	1303
		BCR 	5H,2 			//074A 	1105

		//;test_61f02x_IIC.C: 81: PA2=1;
		BCR 	STATUS,5 		//074B 	1283
		BSR 	5H,2 			//074C 	1905

		//;test_61f02x_IIC.C: 82: PA4=1;
		BSR 	5H,4 			//074D 	1A05

		//;test_61f02x_IIC.C: 83: DelayUs(10);
		LDWI 	AH 			//074E 	2A0A
		LCALL 	718H 			//074F 	3718
		ORG		0750H

		//;test_61f02x_IIC.C: 84: PA2=0;
		BCR 	STATUS,5 		//0750 	1283
		BCR 	STATUS,6 		//0751 	1303
		BCR 	5H,2 			//0752 	1105

		//;test_61f02x_IIC.C: 85: DelayUs(10);
		LDWI 	AH 			//0753 	2A0A
		LCALL 	718H 			//0754 	3718

		//;test_61f02x_IIC.C: 86: PA4=0;
		BCR 	STATUS,5 		//0755 	1283
		BCR 	STATUS,6 		//0756 	1303
		BCR 	5H,4 			//0757 	1205
		ORG		0758H

		//;test_61f02x_IIC.C: 87: DelayUs(10);
		LDWI 	AH 			//0758 	2A0A
		LJUMP 	718H 			//0759 	3F18
		STR 	76H 			//075A 	01F6

		//;test_61f02x_IIC.C: 243: IIC_WRITE_Begin:
		//;test_61f02x_IIC.C: 244: IIC_Start();
		LCALL 	748H 			//075B 	3748

		//;test_61f02x_IIC.C: 245: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//075C 	2AA0
		LCALL 	7D2H 			//075D 	37D2

		//;test_61f02x_IIC.C: 246: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	785H 			//075E 	3785
		XORWI 	0H 			//075F 	2600
		ORG		0760H
		BTSS 	STATUS,2 		//0760 	1D03
		LJUMP 	75BH 			//0761 	3F5B

		//;test_61f02x_IIC.C: 248: IIC_Send_Byte(address);
		LDR 	76H,0 			//0762 	0876
		LCALL 	7D2H 			//0763 	37D2

		//;test_61f02x_IIC.C: 249: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	785H 			//0764 	3785
		XORWI 	0H 			//0765 	2600
		BTSS 	STATUS,2 		//0766 	1D03
		LJUMP 	75BH 			//0767 	3F5B
		ORG		0768H

		//;test_61f02x_IIC.C: 251: IIC_Send_Byte(data);
		LDR 	75H,0 			//0768 	0875
		LCALL 	7D2H 			//0769 	37D2

		//;test_61f02x_IIC.C: 252: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	785H 			//076A 	3785
		XORWI 	0H 			//076B 	2600
		BTSS 	STATUS,2 		//076C 	1D03
		LJUMP 	75BH 			//076D 	3F5B

		//;test_61f02x_IIC.C: 254: IIC_Stop();
		LJUMP 	72BH 			//076E 	3F2B

		//;test_61f02x_IIC.C: 41: OSCCON = 0B01110001;
		LDWI 	71H 			//076F 	2A71
		ORG		0770H
		BSR 	STATUS,5 		//0770 	1A83
		STR 	FH 			//0771 	018F

		//;test_61f02x_IIC.C: 42: INTCON = 0;
		CLRR 	INTCON 			//0772 	010B

		//;test_61f02x_IIC.C: 43: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0773 	1283
		CLRR 	5H 			//0774 	0105

		//;test_61f02x_IIC.C: 44: TRISA = 0B00000000;
		BSR 	STATUS,5 		//0775 	1A83
		CLRR 	5H 			//0776 	0105

		//;test_61f02x_IIC.C: 45: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0777 	1283
		ORG		0778H
		CLRR 	7H 			//0778 	0107

		//;test_61f02x_IIC.C: 46: TRISC = 0B00000000;
		BSR 	STATUS,5 		//0779 	1A83
		CLRR 	7H 			//077A 	0107

		//;test_61f02x_IIC.C: 47: WPUA = 0B00000000;
		CLRR 	15H 			//077B 	0115

		//;test_61f02x_IIC.C: 48: WPUC = 0B00000000;
		CLRR 	8H 			//077C 	0108

		//;test_61f02x_IIC.C: 50: ANSEL = 0B00000000;
		CLRR 	11H 			//077D 	0111

		//;test_61f02x_IIC.C: 51: OPTION = 0B00001000;
		LDWI 	8H 			//077E 	2A08
		STR 	1H 			//077F 	0181
		ORG		0780H

		//;test_61f02x_IIC.C: 52: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//0780 	1283
		CLRR 	1BH 			//0781 	011B

		//;test_61f02x_IIC.C: 56: CMCON0 = 0B00000111;
		LDWI 	7H 			//0782 	2A07
		STR 	19H 			//0783 	0199
		RET		 					//0784 	0004

		//;test_61f02x_IIC.C: 115: unsigned char ucErrTime=0;
		CLRR 	72H 			//0785 	0172

		//;test_61f02x_IIC.C: 116: TRISA2 = 1;
		BSR 	STATUS,5 		//0786 	1A83
		BCR 	STATUS,6 		//0787 	1303
		ORG		0788H
		BSR 	5H,2 			//0788 	1905

		//;test_61f02x_IIC.C: 117: PA2=1;
		BCR 	STATUS,5 		//0789 	1283
		BSR 	5H,2 			//078A 	1905

		//;test_61f02x_IIC.C: 118: DelayUs(5);
		LDWI 	5H 			//078B 	2A05
		LCALL 	718H 			//078C 	3718

		//;test_61f02x_IIC.C: 119: PA4=1;
		//;test_61f02x_IIC.C: 120: DelayUs(5);
		LCALL 	7FAH 			//078D 	37FA
		LCALL 	718H 			//078E 	3718

		//;test_61f02x_IIC.C: 121: while(PA2)
		BCR 	STATUS,5 		//078F 	1283
		ORG		0790H
		BCR 	STATUS,6 		//0790 	1303
		BTSS 	5H,2 			//0791 	1D05
		LJUMP 	79AH 			//0792 	3F9A
		LDWI 	FBH 			//0793 	2AFB

		//;test_61f02x_IIC.C: 122: {
		//;test_61f02x_IIC.C: 123: ucErrTime++;
		INCR	72H,1 			//0794 	09F2

		//;test_61f02x_IIC.C: 124: if(ucErrTime>250)
		SUBWR 	72H,0 			//0795 	0C72
		BTSS 	STATUS,0 		//0796 	1C03
		LJUMP 	78FH 			//0797 	3F8F
		ORG		0798H

		//;test_61f02x_IIC.C: 125: {
		//;test_61f02x_IIC.C: 126: IIC_Stop();
		LCALL 	72BH 			//0798 	372B

		//;test_61f02x_IIC.C: 127: return 1;
		RETW 	1H 			//0799 	2101

		//;test_61f02x_IIC.C: 128: }
		//;test_61f02x_IIC.C: 129: }
		//;test_61f02x_IIC.C: 130: PA4=0;
		BCR 	5H,4 			//079A 	1205

		//;test_61f02x_IIC.C: 131: return 0;
		RETW 	0H 			//079B 	2100
		STR 	75H 			//079C 	01F5

		//;test_61f02x_IIC.C: 223: IIC_Start();
		LCALL 	748H 			//079D 	3748

		//;test_61f02x_IIC.C: 224: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//079E 	2AA0
		LCALL 	7D2H 			//079F 	37D2
		ORG		07A0H

		//;test_61f02x_IIC.C: 225: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	785H 			//07A0 	3785
		XORWI 	0H 			//07A1 	2600
		BTSS 	STATUS,2 		//07A2 	1D03
		LJUMP 	79DH 			//07A3 	3F9D

		//;test_61f02x_IIC.C: 226: IIC_Send_Byte(address);
		LDR 	75H,0 			//07A4 	0875
		LCALL 	7D2H 			//07A5 	37D2

		//;test_61f02x_IIC.C: 227: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	785H 			//07A6 	3785
		XORWI 	0H 			//07A7 	2600
		ORG		07A8H
		BTSS 	STATUS,2 		//07A8 	1D03
		LJUMP 	79DH 			//07A9 	3F9D

		//;test_61f02x_IIC.C: 228: IIC_Start();
		LCALL 	748H 			//07AA 	3748

		//;test_61f02x_IIC.C: 229: IIC_Send_Byte(0xa1);
		LDWI 	A1H 			//07AB 	2AA1
		LCALL 	7D2H 			//07AC 	37D2

		//;test_61f02x_IIC.C: 230: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	785H 			//07AD 	3785
		XORWI 	0H 			//07AE 	2600
		BTSS 	STATUS,2 		//07AF 	1D03
		ORG		07B0H
		LJUMP 	79DH 			//07B0 	3F9D

		//;test_61f02x_IIC.C: 231: iicdata=IIC_Read_Byte();
		LCALL 	7B6H 			//07B1 	37B6
		STR 	76H 			//07B2 	01F6

		//;test_61f02x_IIC.C: 232: IIC_Stop();
		LCALL 	72BH 			//07B3 	372B

		//;test_61f02x_IIC.C: 233: return iicdata;
		LDR 	76H,0 			//07B4 	0876
		RET		 					//07B5 	0004

		//;test_61f02x_IIC.C: 198: unsigned char i,receive=0;
		CLRR 	72H 			//07B6 	0172

		//;test_61f02x_IIC.C: 199: TRISA2 = 1;
		BSR 	STATUS,5 		//07B7 	1A83
		ORG		07B8H
		BCR 	STATUS,6 		//07B8 	1303
		BSR 	5H,2 			//07B9 	1905

		//;test_61f02x_IIC.C: 200: for(i=0;i<8;i++ )
		CLRR 	73H 			//07BA 	0173

		//;test_61f02x_IIC.C: 201: {
		//;test_61f02x_IIC.C: 202: PA4=0;
		//;test_61f02x_IIC.C: 203: DelayUs(5);
		LCALL 	7CEH 			//07BB 	37CE
		LCALL 	718H 			//07BC 	3718

		//;test_61f02x_IIC.C: 204: PA4=1;
		BCR 	STATUS,5 		//07BD 	1283
		BCR 	STATUS,6 		//07BE 	1303
		BSR 	5H,4 			//07BF 	1A05
		ORG		07C0H

		//;test_61f02x_IIC.C: 205: receive<<=1;
		BCR 	STATUS,0 		//07C0 	1003
		RLR 	72H,1 			//07C1 	05F2

		//;test_61f02x_IIC.C: 206: if(PA2)receive++;
		BTSC 	5H,2 			//07C2 	1505
		INCR	72H,1 			//07C3 	09F2

		//;test_61f02x_IIC.C: 207: DelayUs(5);
		LDWI 	5H 			//07C4 	2A05
		LCALL 	718H 			//07C5 	3718
		LDWI 	8H 			//07C6 	2A08
		INCR	73H,1 			//07C7 	09F3
		ORG		07C8H
		SUBWR 	73H,0 			//07C8 	0C73
		BTSS 	STATUS,0 		//07C9 	1C03
		LJUMP 	7BBH 			//07CA 	3FBB

		//;test_61f02x_IIC.C: 208: }
		//;test_61f02x_IIC.C: 209: IIC_NAck();
		LCALL 	739H 			//07CB 	3739

		//;test_61f02x_IIC.C: 211: return receive;
		LDR 	72H,0 			//07CC 	0872
		RET		 					//07CD 	0004
		BCR 	STATUS,5 		//07CE 	1283
		BCR 	STATUS,6 		//07CF 	1303
		ORG		07D0H
		BCR 	5H,4 			//07D0 	1205
		RETW 	5H 			//07D1 	2105
		STR 	73H 			//07D2 	01F3

		//;test_61f02x_IIC.C: 173: unsigned char t;
		//;test_61f02x_IIC.C: 174: TRISA2 = 0;
		//;test_61f02x_IIC.C: 175: PA4=0;
		LCALL 	7F4H 			//07D3 	37F4

		//;test_61f02x_IIC.C: 176: for(t=0;t<8;t++)
		CLRR 	74H 			//07D4 	0174

		//;test_61f02x_IIC.C: 177: {
		//;test_61f02x_IIC.C: 178: if((txd&0x80)>>7)
		LDR 	73H,0 			//07D5 	0873
		STR 	72H 			//07D6 	01F2
		LDWI 	7H 			//07D7 	2A07
		ORG		07D8H
		BCR 	STATUS,0 		//07D8 	1003
		RRR	72H,1 			//07D9 	06F2
		ADDWI 	FFH 			//07DA 	27FF
		BTSS 	STATUS,2 		//07DB 	1D03
		LJUMP 	7D8H 			//07DC 	3FD8
		BTSS 	72H,0 			//07DD 	1C72
		LJUMP 	7E3H 			//07DE 	3FE3

		//;test_61f02x_IIC.C: 179: PA2=1;
		BCR 	STATUS,5 		//07DF 	1283
		ORG		07E0H
		BCR 	STATUS,6 		//07E0 	1303
		BSR 	5H,2 			//07E1 	1905
		LJUMP 	7E6H 			//07E2 	3FE6

		//;test_61f02x_IIC.C: 180: else
		//;test_61f02x_IIC.C: 181: PA2=0;
		BCR 	STATUS,5 		//07E3 	1283
		BCR 	STATUS,6 		//07E4 	1303
		BCR 	5H,2 			//07E5 	1105
		LDWI 	5H 			//07E6 	2A05

		//;test_61f02x_IIC.C: 182: txd<<=1;
		BCR 	STATUS,0 		//07E7 	1003
		ORG		07E8H
		RLR 	73H,1 			//07E8 	05F3

		//;test_61f02x_IIC.C: 183: DelayUs(5);
		LCALL 	718H 			//07E9 	3718

		//;test_61f02x_IIC.C: 184: PA4=1;
		//;test_61f02x_IIC.C: 185: DelayUs(5);
		LCALL 	7FAH 			//07EA 	37FA
		LCALL 	718H 			//07EB 	3718

		//;test_61f02x_IIC.C: 186: PA4=0;
		//;test_61f02x_IIC.C: 187: DelayUs(5);
		LCALL 	7CEH 			//07EC 	37CE
		LCALL 	718H 			//07ED 	3718
		LDWI 	8H 			//07EE 	2A08
		INCR	74H,1 			//07EF 	09F4
		ORG		07F0H
		SUBWR 	74H,0 			//07F0 	0C74
		BTSC 	STATUS,0 		//07F1 	1403
		RET		 					//07F2 	0004
		LJUMP 	7D5H 			//07F3 	3FD5
		BSR 	STATUS,5 		//07F4 	1A83
		BCR 	STATUS,6 		//07F5 	1303
		BCR 	5H,2 			//07F6 	1105
		BCR 	STATUS,5 		//07F7 	1283
		ORG		07F8H
		BCR 	5H,4 			//07F8 	1205
		RET		 					//07F9 	0004
		BCR 	STATUS,5 		//07FA 	1283
		BCR 	STATUS,6 		//07FB 	1303
		BSR 	5H,4 			//07FC 	1A05
		RETW 	5H 			//07FD 	2105
		CLRR 	STATUS 			//07FE 	0103
		LJUMP 	721H 			//07FF 	3F21
			END
