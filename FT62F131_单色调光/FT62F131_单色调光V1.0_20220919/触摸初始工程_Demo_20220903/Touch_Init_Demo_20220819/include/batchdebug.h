#ifndef BATCH_DEBUG_H
#define BATCH_DEBUG_H

#define	___mkstr1(x)	#x
#define	___mkstr(x)	___mkstr1(x)

/*************************************************************************/
/*  				Midrange				 */
/*************************************************************************/
#if defined(_RSC14)
#define _EXIT_SIM(exitCode)	do { \
					asm("dw " ___mkstr(0x3000 \
						+ (exitCode & 0xff))); \
					asm("dw 0Fh"); \
				} while(0);

#endif	/* Midrange */

/*************************************************************************/
/*  				Common					 */
/*************************************************************************/

#if defined(_RSC14) 

#define _PASSED_TESTS()	_EXIT_SIM(0);
#define _FAILED_TEST()	_EXIT_SIM(1);

#endif

#endif /* BATCH_DEBUG_H */
