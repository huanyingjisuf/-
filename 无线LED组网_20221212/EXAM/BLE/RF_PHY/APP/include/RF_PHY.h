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
#define TimeOut_Delay_RX   4       //等待接收状态(射频被发射占用时)

#define Open_NetWork       8       //进入匹配模式

//Time_Out_Read_EXT_Evnt

#define LED_OP_Read_EXT    1        //开灯时读取外部输入

#define LLE_MODE_ORIGINAL_RX       (0x80) //如果配置LLEMODE时加上此宏，则接收第一字节为原始数据（原来为RSSI）

extern void RF_Init(void);

extern void CH_Jump(void);

#ifdef __cplusplus
}
#endif

#endif
