/*
 * Select device-specific header file
 */


#ifndef _CHIP_SELECT_H_
#define _CHIP_SELECT_H_

#define _HEADER_NOT_FOUND

//#include <DEVICE.h>

#if defined(_FT60F01X)
	#include	<FT60F01X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F02X)
	#include	<FT60F02X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F02X)||defined(_FT61FC2X)
	#include	<FT61F02X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F04X)
	#include	<FT61F04X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F02X)
	#include	<FT62F02X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F02XV)
	#include	<FT60F02XV.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F24X)
	#include	<FT61F24X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F08X)
	#include	<FT62F08X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F12X)
	#include	<FT60F12X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F22X)
	#include	<FT60F22X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F34X)
	#include	<FT61F34X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F11X)
	#include	<FT60F11X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F08X)
	#include	<FT61F08X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F14X)||defined(_FT61FC4X)
	#include	<FT61F14X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT67F0AX)||defined(_ZCR01P)||defined(_71MD3EA)||defined(_71MD3EB)||defined(_71MD3FB)||defined(_71MD3VAH)
	#include	<FT67F0AX.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_71MD3AH)||defined(_ZCR01DH)||defined(_ZCR01D)||defined(_ZCM512P)||defined(_ZCM512DH)||defined(_ZCM512D)||defined(_ZCM512CN)
	#include	<FT67F0AX.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_71MD3VBH)||defined(_71MD3VB)||defined(_71MD3BH)||defined(_71MD3B)||defined(_71MD3BCN)||defined(_71MD3FA)||defined(_71MD3ACN)
	#include	<FT67F0AX.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT64F0AX)
	#include	<FT64F0AX.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F0AX)
	#include	<FT61F0AX.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_71MD3A)
	#include	<FT71MD3A.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_71MD3VA)
	#include	<FT71MD3VA.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60F21X)
	#include	<FT60F21X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F21X)
	#include	<FT62F21X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F13X)||defined(_FT62FC3X)||defined(_FT512D)
	#include	<FT62F13X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61F13X)
	#include	<FT61F13X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F28X)
	#include	<FT62F28X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT62F23X)
	#include	<FT62F23X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT6DL13X)
	#include	<FT6DL13X.h>
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT60FC2X)
	#include	<FT60FC2X.h>
	#undef _HEADER_NOT_FOUND
#endif

#ifdef _TEST_CHIP_
	#undef _HEADER_NOT_FOUND
#endif

#if defined(_FT61FC3X)
	#include	<FT61FC3X.h>
	#undef _HEADER_NOT_FOUND
#endif

#ifdef _HEADER_NOT_FOUND
#error Device-specific header could not be found for target chip
#endif

#endif
