#ifndef _I2C_H_
#define _I2C_H_

//I2CCON定义
#define I2CE(N)		(N<<7)
#define I2CIE(N)	(N<<6)
#define STA(N)		(N<<5)
#define STP(N)		(N<<4)
#define CKHD(N)		(N<<3)
#define AAK(N)		(N<<2)
#define CBSE(N)		(N<<1)
#define STFE(N)		(N<<0)

//I2CADR定义
#define   GCE(N)	(N<<7) //N = 0~1

//I2CADM定义
#define   SPFE(N)	(N<<7) //N = 0~1

//I2CFLG定义
#define I2CF		(1<<0)

#endif