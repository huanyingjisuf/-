#ifndef _TS_API_H
#define _TS_API_H

#ifdef _TK_API_C_
/***************************************************************************************************************/
/***************************************************************************************************************/											
TSState_T 	  idata TS_State;

unsigned char PreKeysFlagSN;	
unsigned char KeysFlagSN;	

unsigned int  TS_Key;	
unsigned char TS_LongKeyTimer;
unsigned char TK_State;	

bit TS_CycleScanDoneFlag;
unsigned char idata 	TS_Cnt;			
unsigned int  idata 	TS_RawData[OPENED_TS_COUNT+1];
unsigned int  idata 	TS_BaseLineData[OPENED_TS_COUNT];
unsigned int  idata 	TS_FirstAreaData[OPENED_TS_COUNT];
unsigned char idata 	TS_AreaConfirmTimer[OPENED_TS_COUNT];
unsigned int  idata 	TS_PostData[OPENED_TS_COUNT+1];
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
unsigned int  idata 	TS_PostData2[OPENED_TS_COUNT+1];
#endif
#if (TS_ACQ_TIMES > 1)
unsigned char idata		TS_Acq_Counter = 0;
unsigned int  idata		TS_DataSum[OPENED_TS_COUNT+1];
#endif
#if SUPPORT_KEY
unsigned int  idata 	TSKey_FingerThd[KEY_CH_COUNT];
unsigned char idata 	TSKey_LongTouchLimitTimer[KEY_CH_COUNT];

#if TK_BASE_TRIM_WHILE_KEY_PRESSED
	unsigned int idata RefChDataBak[KEY_CH_COUNT];
	unsigned int idata TS_BaseLineDataBak[KEY_CH_COUNT];
#endif
#else
unsigned int 	idata 	TSKey_FingerThd[1];
#endif
/***************************************************************************************************************/
/***************************************************************************************************************/
unsigned int  idata TS_FilterBuf[OPENED_TS_COUNT+1][FILTER_COUNT];	
unsigned char idata TS_FilterPosIdx[OPENED_TS_COUNT+1];	


unsigned char TS_Init_Step;
unsigned char TS_Index;

unsigned char idata TS_CH[OPENED_TS_COUNT];	

unsigned char EnterStopScanTimer;

#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
#define REF_CH_DATA_BUF_SIZE		10
unsigned int idata RefChDataBuf[REF_CH_DATA_BUF_SIZE];
unsigned char idata RefChDataBufIdx;
unsigned char idata RefChDataTimer;
#endif
#endif

bit TS_StableFlag;

#if SUPPORT_TOUCH_SLEEP_MODE
bit TS_SleepEn;
bit TS_SleepMode;
#endif

unsigned char idata TS_HalfSecCnt;

#if SUPPORT_KEY
#if DEBUG
unsigned char 			idata 	Key_Cnt_Debug;	
TSState_T 	  			idata 	TS_State_Debug;
unsigned char 			idata 	TS_CH_Debug[OPENED_TS_COUNT];	
unsigned int  			idata 	TS_RefChBaseLineData;
unsigned int 				idata 	TS_RefPostData;
unsigned int   idata 	KeysFlagSN_Debug;
#endif

#if SUPPORT_COVER_PANAL_AFTER_POWERON
unsigned char PanalCoverJudgeTimer;
bit PanalCoverJudgeFlag;
#endif

#endif
#if TOUCH_SENSITIVITY_AUTO_BALANCE_EN
unsigned char SensAutoTrimRefCH;
#endif

#else
/***************************************************************************************************************/
/***************************************************************************************************************/											
extern TSState_T 	  idata TS_State;
#ifndef TS_SERVICE_C
extern unsigned char PreKeysFlagSN;	
extern unsigned char KeysFlagSN;	
#endif
extern unsigned int  TS_Key;	
extern unsigned char TS_LongKeyTimer;
extern unsigned char TK_State;	

extern bit TS_CycleScanDoneFlag;
extern unsigned char 	idata 	TS_Cnt;								  
extern unsigned int 	idata 	TS_RawData[];

extern unsigned int 	idata 	TS_BaseLineData[];
extern unsigned int 	idata 	TS_FirstAreaData[];
extern unsigned char 	idata 	TS_AreaConfirmTimer[];
extern unsigned int 	idata 	TS_PostData[];
extern unsigned int 	idata 	TS_PostData2[];

extern unsigned int 	idata 	TSKey_FingerThd[];
extern unsigned char 	idata 	TSKey_LongTouchLimitTimer[];

/***************************************************************************************************************/
/***************************************************************************************************************/
extern unsigned char TS_Init_Step;
extern unsigned char TS_Index;

extern unsigned char idata TS_CH[];	
extern unsigned char  TS_AcqCnt;
extern unsigned char  EnterStopScanTimer;

extern code unsigned int TS_CH_INFO_SEQ[][2];
extern bit TS_StableFlag;
extern bit TS_SleepEn;
extern bit TS_SleepMode;

extern code unsigned int 	TS_KEY_CH_INFO_SEQ[][2];

extern code unsigned char AREA_CONFIRM_TIME_TAB[];
extern code unsigned int MASK_TAB[];

#endif

void TS_init(void);
void TS_Action(void);
void TS_GetKey(void);
void TS_EnterSleepMode(void);		
void TS_ISR(void);
#endif