//Deviec:FT61F13X
//-----------------------Variable---------------------------------
		_IICReadData		EQU		76H
//		IIC_WRITE@address		EQU		75H
//		IIC_WRITE@data		EQU		74H
//		IIC_WRITE@address		EQU		C00000H
//		IIC_READ@address		EQU		74H
//		IIC_READ@iicdata		EQU		75H
//		IIC_READ@address		EQU		C00000H
//		IIC_Wait_Ack@ucErrTime		EQU		72H
//		IIC_Send_Byte@txd		EQU		72H
//		IIC_Send_Byte@t		EQU		73H
//		IIC_Send_Byte@txd		EQU		C00000H
//		IIC_Read_Byte@i		EQU		73H
//		IIC_Read_Byte@receive		EQU		72H
//		DelayUs@Time		EQU		70H
//		DelayUs@a		EQU		71H
//		DelayUs@Time		EQU		C00000H
//-----------------------Variable END---------------------------------
		ORG		0000H
		BCR 	PCLATH,3 		//0000 	118A
		LJUMP 	7FCH 			//0001 	3FFC
		ORG		06EFH

		//;test_61f13x_IIC.C: 43: OSCCON = 0B01110001;
		LDWI 	71H 			//06EF 	2A71
		BSR 	STATUS,5 		//06F0 	1A83
		STR 	FH 			//06F1 	018F

		//;test_61f13x_IIC.C: 44: OPTION = 0B00001000;
		LDWI 	8H 			//06F2 	2A08
		STR 	1H 			//06F3 	0181

		//;test_61f13x_IIC.C: 45: INTCON = 0;
		CLRR 	INTCON 			//06F4 	010B

		//;test_61f13x_IIC.C: 46: PORTA = 0B00000000;
		BCR 	STATUS,5 		//06F5 	1283
		CLRR 	5H 			//06F6 	0105
		ORG		06F7H

		//;test_61f13x_IIC.C: 47: TRISA = 0B00000000;
		BSR 	STATUS,5 		//06F7 	1A83
		CLRR 	5H 			//06F8 	0105

		//;test_61f13x_IIC.C: 50: PORTC = 0B00000000;
		BCR 	STATUS,5 		//06F9 	1283
		CLRR 	7H 			//06FA 	0107

		//;test_61f13x_IIC.C: 51: TRISC = 0B00000000;
		BSR 	STATUS,5 		//06FB 	1A83
		CLRR 	7H 			//06FC 	0107

		//;test_61f13x_IIC.C: 53: WPUA = 0B00000000;
		CLRR 	15H 			//06FD 	0115

		//;test_61f13x_IIC.C: 54: WPUC = 0B00000000;
		CLRR 	13H 			//06FE 	0113
		ORG		06FFH
		RET		 					//06FF 	0004

		//;test_61f13x_IIC.C: 263: POWER_INITIAL();
		BCR 	PCLATH,3 		//0700 	118A
		LCALL 	6EFH 			//0701 	36EF
		BCR 	PCLATH,3 		//0702 	118A

		//;test_61f13x_IIC.C: 265: IIC_WRITE(0x12,0x55);
		LDWI 	55H 			//0703 	2A55
		STR 	74H 			//0704 	01F4
		LDWI 	12H 			//0705 	2A12
		BCR 	PCLATH,3 		//0706 	118A
		ORG		0707H
		LCALL 	755H 			//0707 	3755
		BCR 	PCLATH,3 		//0708 	118A

		//;test_61f13x_IIC.C: 266: IICReadData = IIC_READ(0x12);
		LDWI 	12H 			//0709 	2A12
		BCR 	PCLATH,3 		//070A 	118A
		LCALL 	774H 			//070B 	3774
		BCR 	PCLATH,3 		//070C 	118A
		STR 	76H 			//070D 	01F6

		//;test_61f13x_IIC.C: 267: if(IICReadData==0X55)
		LDWI 	55H 			//070E 	2A55
		ORG		070FH
		XORWR 	76H,0 			//070F 	0476
		BTSS 	STATUS,2 		//0710 	1D03
		LJUMP 	714H 			//0711 	3F14

		//;test_61f13x_IIC.C: 268: {
		//;test_61f13x_IIC.C: 269: IICReadData=0;
		CLRR 	76H 			//0712 	0176

		//;test_61f13x_IIC.C: 270: }
		LJUMP 	716H 			//0713 	3F16

		//;test_61f13x_IIC.C: 271: else{
		//;test_61f13x_IIC.C: 272: IICReadData=1;
		LDWI 	1H 			//0714 	2A01
		STR 	76H 			//0715 	01F6

		//;test_61f13x_IIC.C: 275: {
		//;test_61f13x_IIC.C: 276: __nop();
		NOP		 					//0716 	0000
		ORG		0717H
		LJUMP 	716H 			//0717 	3F16

		//;test_61f13x_IIC.C: 155: PA4=0;
		BCR 	STATUS,5 		//0718 	1283
		BCR 	STATUS,6 		//0719 	1303
		BCR 	5H,4 			//071A 	1205

		//;test_61f13x_IIC.C: 156: TRISA2 =0;
		BSR 	STATUS,5 		//071B 	1A83
		BCR 	5H,2 			//071C 	1105

		//;test_61f13x_IIC.C: 157: PA2=1;
		BCR 	STATUS,5 		//071D 	1283
		BSR 	5H,2 			//071E 	1905
		ORG		071FH

		//;test_61f13x_IIC.C: 158: DelayUs(1);
		LDWI 	1H 			//071F 	2A01
		LCALL 	7B7H 			//0720 	37B7
		BCR 	PCLATH,3 		//0721 	118A

		//;test_61f13x_IIC.C: 159: PA4=1;
		//;test_61f13x_IIC.C: 160: DelayUs(1);
		LCALL 	7F4H 			//0722 	37F4
		BCR 	PCLATH,3 		//0723 	118A
		LCALL 	7B7H 			//0724 	37B7

		//;test_61f13x_IIC.C: 161: PA4=0;
		BCR 	STATUS,5 		//0725 	1283
		BCR 	STATUS,6 		//0726 	1303
		ORG		0727H
		BCR 	5H,4 			//0727 	1205
		RET		 					//0728 	0004

		//;test_61f13x_IIC.C: 95: TRISA2 =0;
		//;test_61f13x_IIC.C: 96: PA4=0;
		LCALL 	7EEH 			//0729 	37EE
		BCR 	PCLATH,3 		//072A 	118A

		//;test_61f13x_IIC.C: 97: PA2=0;
		BCR 	5H,2 			//072B 	1105

		//;test_61f13x_IIC.C: 98: DelayUs(2);
		LDWI 	2H 			//072C 	2A02
		LCALL 	7B7H 			//072D 	37B7
		BCR 	PCLATH,3 		//072E 	118A
		ORG		072FH

		//;test_61f13x_IIC.C: 99: PA4=1;
		BCR 	STATUS,5 		//072F 	1283
		BCR 	STATUS,6 		//0730 	1303
		BSR 	5H,4 			//0731 	1A05

		//;test_61f13x_IIC.C: 100: DelayUs(2);
		LDWI 	2H 			//0732 	2A02
		LCALL 	7B7H 			//0733 	37B7
		BCR 	PCLATH,3 		//0734 	118A

		//;test_61f13x_IIC.C: 101: PA2=1;
		BCR 	STATUS,5 		//0735 	1283
		BCR 	STATUS,6 		//0736 	1303
		ORG		0737H
		BSR 	5H,2 			//0737 	1905

		//;test_61f13x_IIC.C: 102: DelayUs(2);
		LDWI 	2H 			//0738 	2A02
		LJUMP 	7B7H 			//0739 	3FB7

		//;test_61f13x_IIC.C: 196: unsigned char i,receive=0;
		CLRR 	72H 			//073A 	0172

		//;test_61f13x_IIC.C: 197: TRISA2 =1;
		BSR 	STATUS,5 		//073B 	1A83
		BCR 	STATUS,6 		//073C 	1303
		BSR 	5H,2 			//073D 	1905

		//;test_61f13x_IIC.C: 198: for(i=0;i<8;i++ )
		CLRR 	73H 			//073E 	0173
		ORG		073FH

		//;test_61f13x_IIC.C: 199: {
		//;test_61f13x_IIC.C: 200: PA4=0;
		//;test_61f13x_IIC.C: 201: DelayUs(1);
		LCALL 	7F8H 			//073F 	37F8
		BCR 	PCLATH,3 		//0740 	118A
		LCALL 	7B7H 			//0741 	37B7
		BCR 	PCLATH,3 		//0742 	118A

		//;test_61f13x_IIC.C: 202: PA4=1;
		BCR 	STATUS,5 		//0743 	1283
		BCR 	STATUS,6 		//0744 	1303
		BSR 	5H,4 			//0745 	1A05

		//;test_61f13x_IIC.C: 203: receive<<=1;
		BCR 	STATUS,0 		//0746 	1003
		ORG		0747H
		RLR 	72H,1 			//0747 	05F2

		//;test_61f13x_IIC.C: 204: if(PA2)receive++;
		BTSC 	5H,2 			//0748 	1505
		INCR	72H,1 			//0749 	09F2

		//;test_61f13x_IIC.C: 205: DelayUs(1);
		LDWI 	1H 			//074A 	2A01
		LCALL 	7B7H 			//074B 	37B7
		BCR 	PCLATH,3 		//074C 	118A
		LDWI 	8H 			//074D 	2A08
		INCR	73H,1 			//074E 	09F3
		ORG		074FH
		SUBWR 	73H,0 			//074F 	0C73
		BTSS 	STATUS,0 		//0750 	1C03
		LJUMP 	73FH 			//0751 	3F3F

		//;test_61f13x_IIC.C: 206: }
		//;test_61f13x_IIC.C: 207: IIC_NAck();
		LCALL 	718H 			//0752 	3718

		//;test_61f13x_IIC.C: 209: return receive;
		LDR 	72H,0 			//0753 	0872
		RET		 					//0754 	0004
		STR 	75H 			//0755 	01F5
		LJUMP 	759H 			//0756 	3F59
		ORG		0757H
		BSR 	STATUS,5 		//0757 	1A83
		BCR 	STATUS,6 		//0758 	1303

		//;test_61f13x_IIC.C: 241: IIC_WRITE_Begin:
		//;test_61f13x_IIC.C: 242: IIC_Start();
		LCALL 	7DAH 			//0759 	37DA
		BCR 	PCLATH,3 		//075A 	118A

		//;test_61f13x_IIC.C: 243: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//075B 	2AA0
		LCALL 	797H 			//075C 	3797
		BCR 	PCLATH,3 		//075D 	118A

		//;test_61f13x_IIC.C: 244: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	7C0H 			//075E 	37C0
		ORG		075FH
		BCR 	PCLATH,3 		//075F 	118A
		XORWI 	0H 			//0760 	2600
		BTSS 	STATUS,2 		//0761 	1D03
		LJUMP 	757H 			//0762 	3F57

		//;test_61f13x_IIC.C: 246: IIC_Send_Byte(address);
		LDR 	75H,0 			//0763 	0875
		LCALL 	797H 			//0764 	3797
		BCR 	PCLATH,3 		//0765 	118A

		//;test_61f13x_IIC.C: 247: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	7C0H 			//0766 	37C0
		ORG		0767H
		BCR 	PCLATH,3 		//0767 	118A
		XORWI 	0H 			//0768 	2600
		BTSS 	STATUS,2 		//0769 	1D03
		LJUMP 	757H 			//076A 	3F57

		//;test_61f13x_IIC.C: 249: IIC_Send_Byte(data);
		LDR 	74H,0 			//076B 	0874
		LCALL 	797H 			//076C 	3797
		BCR 	PCLATH,3 		//076D 	118A

		//;test_61f13x_IIC.C: 250: if(IIC_Wait_Ack())goto IIC_WRITE_Begin;
		LCALL 	7C0H 			//076E 	37C0
		ORG		076FH
		BCR 	PCLATH,3 		//076F 	118A
		XORWI 	0H 			//0770 	2600
		BTSS 	STATUS,2 		//0771 	1D03
		LJUMP 	757H 			//0772 	3F57

		//;test_61f13x_IIC.C: 252: IIC_Stop();
		LJUMP 	729H 			//0773 	3F29
		STR 	74H 			//0774 	01F4

		//;test_61f13x_IIC.C: 221: IIC_Start();
		LCALL 	7DAH 			//0775 	37DA
		BCR 	PCLATH,3 		//0776 	118A
		ORG		0777H

		//;test_61f13x_IIC.C: 222: IIC_Send_Byte(0xa0);
		LDWI 	A0H 			//0777 	2AA0
		LCALL 	797H 			//0778 	3797
		BCR 	PCLATH,3 		//0779 	118A

		//;test_61f13x_IIC.C: 223: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	7C0H 			//077A 	37C0
		BCR 	PCLATH,3 		//077B 	118A
		XORWI 	0H 			//077C 	2600
		BTSS 	STATUS,2 		//077D 	1D03
		LJUMP 	775H 			//077E 	3F75
		ORG		077FH

		//;test_61f13x_IIC.C: 224: IIC_Send_Byte(address);
		LDR 	74H,0 			//077F 	0874
		LCALL 	797H 			//0780 	3797
		BCR 	PCLATH,3 		//0781 	118A

		//;test_61f13x_IIC.C: 225: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	7C0H 			//0782 	37C0
		BCR 	PCLATH,3 		//0783 	118A
		XORWI 	0H 			//0784 	2600
		BTSS 	STATUS,2 		//0785 	1D03
		LJUMP 	775H 			//0786 	3F75
		ORG		0787H

		//;test_61f13x_IIC.C: 226: IIC_Start();
		LCALL 	7DAH 			//0787 	37DA
		BCR 	PCLATH,3 		//0788 	118A

		//;test_61f13x_IIC.C: 227: IIC_Send_Byte(0xa1);
		LDWI 	A1H 			//0789 	2AA1
		LCALL 	797H 			//078A 	3797
		BCR 	PCLATH,3 		//078B 	118A

		//;test_61f13x_IIC.C: 228: if(IIC_Wait_Ack())goto IIC_READ_Begin;
		LCALL 	7C0H 			//078C 	37C0
		BCR 	PCLATH,3 		//078D 	118A
		XORWI 	0H 			//078E 	2600
		ORG		078FH
		BTSS 	STATUS,2 		//078F 	1D03
		LJUMP 	775H 			//0790 	3F75

		//;test_61f13x_IIC.C: 229: iicdata=IIC_Read_Byte();
		LCALL 	73AH 			//0791 	373A
		BCR 	PCLATH,3 		//0792 	118A
		STR 	75H 			//0793 	01F5

		//;test_61f13x_IIC.C: 230: IIC_Stop();
		LCALL 	729H 			//0794 	3729

		//;test_61f13x_IIC.C: 231: return iicdata;
		LDR 	75H,0 			//0795 	0875
		RET		 					//0796 	0004
		ORG		0797H
		STR 	72H 			//0797 	01F2

		//;test_61f13x_IIC.C: 171: unsigned char t;
		//;test_61f13x_IIC.C: 172: TRISA2 =0;
		//;test_61f13x_IIC.C: 173: PA4=0;
		LCALL 	7EEH 			//0798 	37EE
		BCR 	PCLATH,3 		//0799 	118A

		//;test_61f13x_IIC.C: 174: for(t=0;t<8;t++)
		CLRR 	73H 			//079A 	0173

		//;test_61f13x_IIC.C: 175: {
		//;test_61f13x_IIC.C: 176: if(txd&0x80)
		BTSS 	72H,7 			//079B 	1FF2
		LJUMP 	7A1H 			//079C 	3FA1

		//;test_61f13x_IIC.C: 177: PA2=1;
		BCR 	STATUS,5 		//079D 	1283
		BCR 	STATUS,6 		//079E 	1303
		ORG		079FH
		BSR 	5H,2 			//079F 	1905
		LJUMP 	7A4H 			//07A0 	3FA4

		//;test_61f13x_IIC.C: 178: else
		//;test_61f13x_IIC.C: 179: PA2=0;
		BCR 	STATUS,5 		//07A1 	1283
		BCR 	STATUS,6 		//07A2 	1303
		BCR 	5H,2 			//07A3 	1105
		LDWI 	1H 			//07A4 	2A01

		//;test_61f13x_IIC.C: 180: txd<<=1;
		BCR 	STATUS,0 		//07A5 	1003
		RLR 	72H,1 			//07A6 	05F2
		ORG		07A7H

		//;test_61f13x_IIC.C: 181: DelayUs(1);
		LCALL 	7B7H 			//07A7 	37B7
		BCR 	PCLATH,3 		//07A8 	118A

		//;test_61f13x_IIC.C: 182: PA4=1;
		//;test_61f13x_IIC.C: 183: DelayUs(1);
		LCALL 	7F4H 			//07A9 	37F4
		BCR 	PCLATH,3 		//07AA 	118A
		LCALL 	7B7H 			//07AB 	37B7
		BCR 	PCLATH,3 		//07AC 	118A

		//;test_61f13x_IIC.C: 184: PA4=0;
		//;test_61f13x_IIC.C: 185: DelayUs(1);
		LCALL 	7F8H 			//07AD 	37F8
		BCR 	PCLATH,3 		//07AE 	118A
		ORG		07AFH
		LCALL 	7B7H 			//07AF 	37B7
		BCR 	PCLATH,3 		//07B0 	118A
		LDWI 	8H 			//07B1 	2A08
		INCR	73H,1 			//07B2 	09F3
		SUBWR 	73H,0 			//07B3 	0C73
		BTSC 	STATUS,0 		//07B4 	1403
		RET		 					//07B5 	0004
		LJUMP 	79BH 			//07B6 	3F9B
		ORG		07B7H
		STR 	70H 			//07B7 	01F0

		//;test_61f13x_IIC.C: 64: unsigned char a;
		//;test_61f13x_IIC.C: 65: for(a=0;a<Time;a++)
		CLRR 	71H 			//07B8 	0171
		LDR 	70H,0 			//07B9 	0870
		SUBWR 	71H,0 			//07BA 	0C71
		BTSC 	STATUS,0 		//07BB 	1403
		RET		 					//07BC 	0004

		//;test_61f13x_IIC.C: 66: {
		//;test_61f13x_IIC.C: 67: __nop();
		NOP		 					//07BD 	0000
		INCR	71H,1 			//07BE 	09F1
		ORG		07BFH
		LJUMP 	7B9H 			//07BF 	3FB9

		//;test_61f13x_IIC.C: 113: unsigned char ucErrTime=0;
		CLRR 	72H 			//07C0 	0172

		//;test_61f13x_IIC.C: 114: TRISA2 =1;
		BSR 	STATUS,5 		//07C1 	1A83
		BCR 	STATUS,6 		//07C2 	1303
		BSR 	5H,2 			//07C3 	1905

		//;test_61f13x_IIC.C: 115: PA2=1;
		BCR 	STATUS,5 		//07C4 	1283
		BSR 	5H,2 			//07C5 	1905

		//;test_61f13x_IIC.C: 116: DelayUs(1);
		LDWI 	1H 			//07C6 	2A01
		ORG		07C7H
		LCALL 	7B7H 			//07C7 	37B7
		BCR 	PCLATH,3 		//07C8 	118A

		//;test_61f13x_IIC.C: 117: PA4=1;
		//;test_61f13x_IIC.C: 118: DelayUs(1);
		LCALL 	7F4H 			//07C9 	37F4
		BCR 	PCLATH,3 		//07CA 	118A
		LCALL 	7B7H 			//07CB 	37B7
		BCR 	PCLATH,3 		//07CC 	118A

		//;test_61f13x_IIC.C: 119: while(PA2)
		BCR 	STATUS,5 		//07CD 	1283
		BCR 	STATUS,6 		//07CE 	1303
		ORG		07CFH
		BTSS 	5H,2 			//07CF 	1D05
		LJUMP 	7D8H 			//07D0 	3FD8
		LDWI 	FBH 			//07D1 	2AFB

		//;test_61f13x_IIC.C: 120: {
		//;test_61f13x_IIC.C: 121: ucErrTime++;
		INCR	72H,1 			//07D2 	09F2

		//;test_61f13x_IIC.C: 122: if(ucErrTime>250)
		SUBWR 	72H,0 			//07D3 	0C72
		BTSS 	STATUS,0 		//07D4 	1C03
		LJUMP 	7CDH 			//07D5 	3FCD

		//;test_61f13x_IIC.C: 123: {
		//;test_61f13x_IIC.C: 124: IIC_Stop();
		LCALL 	729H 			//07D6 	3729
		ORG		07D7H

		//;test_61f13x_IIC.C: 125: return 1;
		RETW 	1H 			//07D7 	2101

		//;test_61f13x_IIC.C: 126: }
		//;test_61f13x_IIC.C: 127: }
		//;test_61f13x_IIC.C: 128: PA4=0;
		BCR 	5H,4 			//07D8 	1205

		//;test_61f13x_IIC.C: 129: return 0;
		RETW 	0H 			//07D9 	2100

		//;test_61f13x_IIC.C: 78: TRISA2 =0;
		BSR 	STATUS,5 		//07DA 	1A83
		BCR 	STATUS,6 		//07DB 	1303
		BCR 	5H,2 			//07DC 	1105

		//;test_61f13x_IIC.C: 79: PA2=1;
		BCR 	STATUS,5 		//07DD 	1283
		BSR 	5H,2 			//07DE 	1905
		ORG		07DFH

		//;test_61f13x_IIC.C: 80: PA4=1;
		BSR 	5H,4 			//07DF 	1A05

		//;test_61f13x_IIC.C: 81: DelayUs(2);
		LDWI 	2H 			//07E0 	2A02
		LCALL 	7B7H 			//07E1 	37B7
		BCR 	PCLATH,3 		//07E2 	118A

		//;test_61f13x_IIC.C: 82: PA2=0;
		BCR 	STATUS,5 		//07E3 	1283
		BCR 	STATUS,6 		//07E4 	1303
		BCR 	5H,2 			//07E5 	1105

		//;test_61f13x_IIC.C: 83: DelayUs(2);
		LDWI 	2H 			//07E6 	2A02
		ORG		07E7H
		LCALL 	7B7H 			//07E7 	37B7
		BCR 	PCLATH,3 		//07E8 	118A

		//;test_61f13x_IIC.C: 84: PA4=0;
		BCR 	STATUS,5 		//07E9 	1283
		BCR 	STATUS,6 		//07EA 	1303
		BCR 	5H,4 			//07EB 	1205

		//;test_61f13x_IIC.C: 85: DelayUs(2);
		LDWI 	2H 			//07EC 	2A02
		LJUMP 	7B7H 			//07ED 	3FB7
		BSR 	STATUS,5 		//07EE 	1A83
		ORG		07EFH
		BCR 	STATUS,6 		//07EF 	1303
		BCR 	5H,2 			//07F0 	1105
		BCR 	STATUS,5 		//07F1 	1283
		BCR 	5H,4 			//07F2 	1205
		RET		 					//07F3 	0004
		BCR 	STATUS,5 		//07F4 	1283
		BCR 	STATUS,6 		//07F5 	1303
		BSR 	5H,4 			//07F6 	1A05
		ORG		07F7H
		RETW 	1H 			//07F7 	2101
		BCR 	STATUS,5 		//07F8 	1283
		BCR 	STATUS,6 		//07F9 	1303
		BCR 	5H,4 			//07FA 	1205
		RETW 	1H 			//07FB 	2101
		CLRR 	76H 			//07FC 	0176
		CLRR 	STATUS 			//07FD 	0103
		BCR 	PCLATH,3 		//07FE 	118A
		ORG		07FFH
		LJUMP 	700H 			//07FF 	3F00
			END
