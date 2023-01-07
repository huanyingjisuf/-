/**

  *********************************************************************************

  * @file    	    touch.h

  * @author  	    FMD AE

  * @brief   	    库头文件

  * @version 	    V2.0.1           

  * @data		    2022-03-25

  *********************************************************************************

  * @attention

  * COPYRIGHT (C) 2021 Fremont Micro Devices Corporation All rights reserved.

  *    This software is provided by the copyright holders and contributors,and the

  *software is believed to be accurate and reliable. However, Fremont Micro Devices

  *Corporation assumes no responsibility for the consequences of use of such

  *software or for any infringement of patents of other rights of third parties,

  *which may result from its use. No license is granted by implication or otherwise

  *under any patent rights of Fremont Micro Devices Corporation.

  **********************************************************************************

  */  



  /**********************************************************************************

  * @芯片资源

  * 1. Device: FT62F13X

  * 2. Memory: Flash 3KX14b, SRAM:256X8b EEPROM 128X8b 

  *

  * @触摸按键库使用资源说明:

  * 1. TIMER0、TIMER1

  * 2. LVD中断

  * 3. ROM & SARM (Key= 1,Ks=1不包含led.c)  

  *     库类型            		  ROM *14b       	SRAM*8b			

  * touch_soft.lpp		1,151+3*Key	52+8*Key

  * touch.lpp		1,262+3*Key	55+8*Key

  * touch_cs_ac.lpp		1,400+4*Key	62+8*Key

  * touch_cs_uac.lpp		1,473+4*Key	65+8*Key

  * touch_lp.lpp		1,650+3*Key	59+8*Key+2*Ks

  * touch_cs_lp_ac.lpp	1,790+4*Key	64+8*Key+2*Ks

  * touch_cs_lp_uac.lpp	1,844+4*Key	67+8*Key+2*Ks

  *

  * 4.SRAM指定地址:

  * 	指定地址 特殊变量应用定义：0x20 、0x21、 0x72~ 0x79

  * 	指定地址 按键数据保存区：8BYTE/键 (0x120 ~ 0x120 + 8*Key)

  **********************************************************************************

  */

 
#ifndef	_TOUCH_H
#define	_TOUCH_H

#include "syscfg.h"

#include <string.h>

/////////系统时钟定义//////////////////////////////////////
#define SYS_OSCCON   0B01110001 //16M
/////////按键对应芯片KEYIO映射定义//////////////////////////
#define   KEY0_INDEX_MAP       0

#define   KEY_NUMBER             1  //按键数

unsigned int stTkData[KEY_NUMBER][4] @ 0x120;
const unsigned char ucKeyNumberMax = KEY_NUMBER;

////////按键对应KEYIO映射表/////////////////////////////////////////////
const unsigned char ucKeyIndexMapArray[KEY_NUMBER]=
{
    KEY0_INDEX_MAP,   
};

/////////////按键有效阀值////////////////////////////////////
#define   KEY0_ON					27

const unsigned char ucActiveSensorDeltaArray[KEY_NUMBER]=
{
    KEY0_ON   
};

///////////按键无效阀值//////////////////////////////////////
#define   KEY0_OFF					17

const unsigned char ucInActiveSensorDeltaArray[KEY_NUMBER]=
{
    KEY0_OFF   
};

////////正常状态或CS模式下的条件判定///////////////////////////////////////////
#define RESONANCE_CHANGER_FREQ_COUNT_FILTER     1000   //CS处理时长
const unsigned int uiResonanceChangerFreqCountFilter = RESONANCE_CHANGER_FREQ_COUNT_FILTER;	
#define RESONANCE_DATA_FILTER                   19    //CS判断条件
const unsigned char ucResonanceDataFilter = RESONANCE_DATA_FILTER; 
////////CS状态下多键处理定义///////////////////////////////////////////////////////////////
#define ABNORMAL_WAIT_COUNT_FILTER              1000 	//异常状态下多键无效的时长：12s~15s
const unsigned int uiAbnormalWaitCountFilter = ABNORMAL_WAIT_COUNT_FILTER; 
#define NORMAL_COUNT_FILTER                     200  	//数据正常判断次数，连续200次就恢复正常模式
const unsigned char ucNormalCountFilter = NORMAL_COUNT_FILTER; 
#define ABNORMAL_COUNT_FILTER                   3   	//数据异常判断次数，连续3次就进CS模式
const unsigned char ucAbnormalCountFilter = ABNORMAL_COUNT_FILTER; 
#define KEY_OFF_ABNORMAL_UP_FILTER              5  		//按键非按下值的异常上限值
const unsigned char ucKeyOffAbnormalUpFilter = KEY_OFF_ABNORMAL_UP_FILTER; 
#define KEY_ON_ABNORMAL_UP_FILTER            	5 		//按键按下值的异常上限
const unsigned char ucKeyOnAbnormalUpFilter = KEY_ON_ABNORMAL_UP_FILTER; 
#define KEY_ON_ABNORMAL_DOWN_FILTER             19 		//按键按下值的异常下限
const unsigned char ucKeyOnAbnormalDownFilter = KEY_ON_ABNORMAL_DOWN_FILTER; 
////////采集数据处理相关定义///////////////////////////////////////////
#define MULTIPLE_1  								80    //放大倍数
#define STRONG_FILTER_1   							4		//滤波次数
#define SINGLE_FILTER_1   							4		//防抖次数
#define BASE_LINE_DOWN_SPEED_1   				65    //基线向下更新速度
#define BASE_LINE_UP_SPEED_1  					65	  //基线向上更新速度
#define BASE_LINE_EQUAL_DOWN_SPEED_1   	200    //基线复位向下速度
#define BASE_LINE_EQUAL_UP_SPEED_1   		100	  //基线复位向上速度
#define SIGNAL_NOISE_RATIO_1  					30  	//整体信噪比
#define MEANTIME_MAX_KEY_NUM_1  		   	 	8		//最大按键数
#define BASE_UPDATA_FILTER_1                    	2 	//快速更新条件

const unsigned char ucMultiple = MULTIPLE_1;
const unsigned char ucStrongFilter = STRONG_FILTER_1;
const unsigned char ucSingleFilter = SINGLE_FILTER_1;
const unsigned char ucBaselineDownSpeed = 128 + BASE_LINE_DOWN_SPEED_1;
const unsigned char ucBaselineUpSpeed = 128 - BASE_LINE_UP_SPEED_1;
const unsigned char ucBaselineEqualUpSpeed = BASE_LINE_EQUAL_UP_SPEED_1;
const unsigned char ucBaselineEqualDownSpeed = BASE_LINE_EQUAL_DOWN_SPEED_1;
const unsigned char ucSignalNoiseRatio = SIGNAL_NOISE_RATIO_1;
const unsigned char ucMeantimeMaxKeyNum = MEANTIME_MAX_KEY_NUM_1;
const unsigned char ucBaseUpdataFilter = BASE_UPDATA_FILTER_1;;

////////频率微调定义///////////////////////////////////////////////////
#define FREQ_CHANGER_1 						0xE0		//扫描频率
#define FREQ_CHANGER_2 						0x20		//扫描频率
#define FREQ_CHANGER_3 						0X00	    //扫描频率

const unsigned char ucFreqChangerBase = FREQ_CHANGER_2;
const unsigned char ucFreachooseArray[3] = {
	FREQ_CHANGER_1,
	FREQ_CHANGER_2,
	FREQ_CHANGER_3
};

///////////功能函数定义/////////////////////////////////////
void TOUCH_INITIAL(void);  //触摸按键配置初始化
void TSC_Start(void); //按键扫描结果处理，每次只做一个按键的一次扫描处理
void TSC_Reset(void); //复位触摸. 长按保护可使用
unsigned char TSC_DataProcessing(void);//所有按键数据处理状态: 1表示所有按键数据处理完成 0表示未处理按键数据
unsigned char TSC_GetStrongest(void);  //获取最强按键值
unsigned char TSC_GetSingle(void); //获取按键有效标志，每bit表示一个键，1为有按键按下，0为无按键按下
unsigned char TSC_GetDelta(unsigned char KeyNum); //获取变化量, >最大按键数KEY_NUMBER则获取最大值
unsigned int TSC_GetPrevData(unsigned char KeyNum); //当前按键采集数据值
#endif	
