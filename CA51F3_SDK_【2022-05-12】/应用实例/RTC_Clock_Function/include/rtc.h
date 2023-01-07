#ifndef RTC_H
#define RTC_H
//RTCON定义
#define RTCE(N)		(N<<7) 
#define MSE(N)		(N<<6) 
#define HSE(N)		(N<<5)
#define SCE(N)		(N<<4)
#define MCE(N)		(N<<3)
#define HCE(N)		(N<<2)
#define RTCWE(N)	(N<<1)


//RTCIF定义
#define RTC_MF		(1<<2)
#define RTC_HF		(1<<1)
#define RTC_AF		(1<<0)

void RTC_WriteSecond(unsigned char second);
void RTC_WriteMinute(unsigned char minute);
void RTC_WriteHour(unsigned char hour);
void RTC_WriteWeek(unsigned char week);

#endif