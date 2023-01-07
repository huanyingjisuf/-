/********************************** (C) COPYRIGHT *******************************
 * File Name          : rf_phy.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/11/12
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef CENTRAL_H
#define CENTRAL_H

#ifdef __cplusplus
extern "C" {
#endif

#define SBP_RF_START_DEVICE_EVT    1
#define SBP_RF_PERIODIC_EVT        2
#define SBP_RF_RF_RX_EVT           4


//Time_Out_RF_RX_Evnt

#define TimeOut_RX_Open    1
#define TimeOut_RX_Close   2
#define TimeOut_Delay_RX   4       //�ȴ�����״̬(��Ƶ������ռ��ʱ)

#define Open_NetWork       8       //����ƥ��ģʽ

//Time_Out_Read_EXT_Evnt

#define LED_OP_Read_EXT    1        //����ʱ��ȡ�ⲿ����

#define LLE_MODE_ORIGINAL_RX       (0x80) //�������LLEMODEʱ���ϴ˺꣬����յ�һ�ֽ�Ϊԭʼ���ݣ�ԭ��ΪRSSI��

extern void RF_Init(void);

extern void CH_Jump(void);

#ifdef __cplusplus
}
#endif

#endif
