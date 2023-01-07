#ifndef __CA51F1_XDATA_H__
#define __CA51F1_XDATA_H__

#ifdef _MAIN_C_
#define XRAM_U8										volatile unsigned char xdata
#define XRAM_AT_(x)								_at_ x		
#else
#define XRAM_U8										extern volatile unsigned char xdata
#define XRAM_AT_(x)
#endif


XRAM_U8 	P01F        XRAM_AT_(0x8001);



XRAM_U8 	P30F        XRAM_AT_(0x8018);
XRAM_U8 	P31F        XRAM_AT_(0x8019);
XRAM_U8 	P32F        XRAM_AT_(0x801a);
XRAM_U8 	P34F        XRAM_AT_(0x801c);
XRAM_U8 	P35F        XRAM_AT_(0x801d);


XRAM_U8 	ADCON      XRAM_AT_(0x8060);
XRAM_U8 	ADCFGL     XRAM_AT_(0x8061);
XRAM_U8 	ADCDL       XRAM_AT_(0x8062);
XRAM_U8 	ADCDH       XRAM_AT_(0x8063);
XRAM_U8 	ADCALL      XRAM_AT_(0x8064);
XRAM_U8 	ADCALH      XRAM_AT_(0x8065);


XRAM_U8 	SRELL      	XRAM_AT_(0x8068);
XRAM_U8 	SRELH      	XRAM_AT_(0x8069);

XRAM_U8 	P01C        XRAM_AT_(0x8121);

XRAM_U8 	P30C        XRAM_AT_(0x8138);
XRAM_U8 	P31C        XRAM_AT_(0x8139);
XRAM_U8 	P32C        XRAM_AT_(0x813a);
XRAM_U8 	P34C        XRAM_AT_(0x813c);
XRAM_U8 	P35C        XRAM_AT_(0x813d);

XRAM_U8 	MECON       XRAM_AT_(0xfc00);
XRAM_U8 	FSCMD       XRAM_AT_(0xfc01);
XRAM_U8 	FSDAT       XRAM_AT_(0xfc02);
XRAM_U8 	LOCK        XRAM_AT_(0xfc03);
XRAM_U8 	PADRD       XRAM_AT_(0xfc04);
XRAM_U8 	PTSL        XRAM_AT_(0xfc05);
XRAM_U8 	PTSH        XRAM_AT_(0xfc06);


#endif  
