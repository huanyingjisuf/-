/**

  *********************************************************************************

  * @file    	    touch.h

  * @author  	    FMD AE

  * @brief   	    ��ͷ�ļ�

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

  * @оƬ��Դ

  * 1. Device: FT62F13X

  * 2. Memory: Flash 3KX14b, SRAM:256X8b EEPROM 128X8b 

  *

  * @����������ʹ����Դ˵��:

  * 1. TIMER0��TIMER1

  * 2. LVD�ж�

  * 3. ROM & SARM (Key= 1,Ks=1������led.c)  

  *     ������            		  ROM *14b       	SRAM*8b			

  * touch_soft.lpp		1,151+3*Key	52+8*Key

  * touch.lpp		1,262+3*Key	55+8*Key

  * touch_cs_ac.lpp		1,400+4*Key	62+8*Key

  * touch_cs_uac.lpp		1,473+4*Key	65+8*Key

  * touch_lp.lpp		1,650+3*Key	59+8*Key+2*Ks

  * touch_cs_lp_ac.lpp	1,790+4*Key	64+8*Key+2*Ks

  * touch_cs_lp_uac.lpp	1,844+4*Key	67+8*Key+2*Ks

  *

  * 4.SRAMָ����ַ:

  * 	ָ����ַ �������Ӧ�ö��壺0x20 ��0x21�� 0x72~ 0x79

  * 	ָ����ַ �������ݱ�������8BYTE/�� (0x120 ~ 0x120 + 8*Key)

  **********************************************************************************

  */

 
#ifndef	_TOUCH_H
#define	_TOUCH_H

#include "syscfg.h"

#include <string.h>

/////////ϵͳʱ�Ӷ���//////////////////////////////////////
#define SYS_OSCCON   0B01110001 //16M
/////////������ӦоƬKEYIOӳ�䶨��//////////////////////////
#define   KEY0_INDEX_MAP       0

#define   KEY_NUMBER             1  //������

unsigned int stTkData[KEY_NUMBER][4] @ 0x120;
const unsigned char ucKeyNumberMax = KEY_NUMBER;

////////������ӦKEYIOӳ���/////////////////////////////////////////////
const unsigned char ucKeyIndexMapArray[KEY_NUMBER]=
{
    KEY0_INDEX_MAP,   
};

/////////////������Ч��ֵ////////////////////////////////////
#define   KEY0_ON					27

const unsigned char ucActiveSensorDeltaArray[KEY_NUMBER]=
{
    KEY0_ON   
};

///////////������Ч��ֵ//////////////////////////////////////
#define   KEY0_OFF					17

const unsigned char ucInActiveSensorDeltaArray[KEY_NUMBER]=
{
    KEY0_OFF   
};

////////����״̬��CSģʽ�µ������ж�///////////////////////////////////////////
#define RESONANCE_CHANGER_FREQ_COUNT_FILTER     1000   //CS����ʱ��
const unsigned int uiResonanceChangerFreqCountFilter = RESONANCE_CHANGER_FREQ_COUNT_FILTER;	
#define RESONANCE_DATA_FILTER                   19    //CS�ж�����
const unsigned char ucResonanceDataFilter = RESONANCE_DATA_FILTER; 
////////CS״̬�¶��������///////////////////////////////////////////////////////////////
#define ABNORMAL_WAIT_COUNT_FILTER              1000 	//�쳣״̬�¶����Ч��ʱ����12s~15s
const unsigned int uiAbnormalWaitCountFilter = ABNORMAL_WAIT_COUNT_FILTER; 
#define NORMAL_COUNT_FILTER                     200  	//���������жϴ���������200�ξͻָ�����ģʽ
const unsigned char ucNormalCountFilter = NORMAL_COUNT_FILTER; 
#define ABNORMAL_COUNT_FILTER                   3   	//�����쳣�жϴ���������3�ξͽ�CSģʽ
const unsigned char ucAbnormalCountFilter = ABNORMAL_COUNT_FILTER; 
#define KEY_OFF_ABNORMAL_UP_FILTER              5  		//�����ǰ���ֵ���쳣����ֵ
const unsigned char ucKeyOffAbnormalUpFilter = KEY_OFF_ABNORMAL_UP_FILTER; 
#define KEY_ON_ABNORMAL_UP_FILTER            	5 		//��������ֵ���쳣����
const unsigned char ucKeyOnAbnormalUpFilter = KEY_ON_ABNORMAL_UP_FILTER; 
#define KEY_ON_ABNORMAL_DOWN_FILTER             19 		//��������ֵ���쳣����
const unsigned char ucKeyOnAbnormalDownFilter = KEY_ON_ABNORMAL_DOWN_FILTER; 
////////�ɼ����ݴ�����ض���///////////////////////////////////////////
#define MULTIPLE_1  								80    //�Ŵ���
#define STRONG_FILTER_1   							4		//�˲�����
#define SINGLE_FILTER_1   							4		//��������
#define BASE_LINE_DOWN_SPEED_1   				65    //�������¸����ٶ�
#define BASE_LINE_UP_SPEED_1  					65	  //�������ϸ����ٶ�
#define BASE_LINE_EQUAL_DOWN_SPEED_1   	200    //���߸�λ�����ٶ�
#define BASE_LINE_EQUAL_UP_SPEED_1   		100	  //���߸�λ�����ٶ�
#define SIGNAL_NOISE_RATIO_1  					30  	//���������
#define MEANTIME_MAX_KEY_NUM_1  		   	 	8		//��󰴼���
#define BASE_UPDATA_FILTER_1                    	2 	//���ٸ�������

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

////////Ƶ��΢������///////////////////////////////////////////////////
#define FREQ_CHANGER_1 						0xE0		//ɨ��Ƶ��
#define FREQ_CHANGER_2 						0x20		//ɨ��Ƶ��
#define FREQ_CHANGER_3 						0X00	    //ɨ��Ƶ��

const unsigned char ucFreqChangerBase = FREQ_CHANGER_2;
const unsigned char ucFreachooseArray[3] = {
	FREQ_CHANGER_1,
	FREQ_CHANGER_2,
	FREQ_CHANGER_3
};

///////////���ܺ�������/////////////////////////////////////
void TOUCH_INITIAL(void);  //�����������ó�ʼ��
void TSC_Start(void); //����ɨ��������ÿ��ֻ��һ��������һ��ɨ�账��
void TSC_Reset(void); //��λ����. ����������ʹ��
unsigned char TSC_DataProcessing(void);//���а������ݴ���״̬: 1��ʾ���а������ݴ������ 0��ʾδ����������
unsigned char TSC_GetStrongest(void);  //��ȡ��ǿ����ֵ
unsigned char TSC_GetSingle(void); //��ȡ������Ч��־��ÿbit��ʾһ������1Ϊ�а������£�0Ϊ�ް�������
unsigned char TSC_GetDelta(unsigned char KeyNum); //��ȡ�仯��, >��󰴼���KEY_NUMBER���ȡ���ֵ
unsigned int TSC_GetPrevData(unsigned char KeyNum); //��ǰ�����ɼ�����ֵ
#endif	
