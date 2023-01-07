#ifndef _FMD_H_
#define _FMD_H_

#if defined(__CCI__) && !defined(_XC_H_)
#warning "CCI projects should use the top-level support file xc.h\nIncluding xc.h instead"
#include <xc.h>
#endif

#if !defined(__CCI__) && !defined(__IAR__)
/* allow CCI definitions even when CCI option is not turned on */
#include <cci.h>
#endif

/* Definitions for _HTC_EDITION_ values */
#define __LITE__ 0
#define __STD__ 1
#define __PRO__ 2

/* common definitions */

#define	___mkstr1(x)	#x
#define	___mkstr(x)	___mkstr1(x)

#define _OMNITARGET	((void *)0xFFFFFFFF)

extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);

#include <GCC8debug.h>


#endif
