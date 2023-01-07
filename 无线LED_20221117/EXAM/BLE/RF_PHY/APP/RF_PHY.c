/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */

#include "CONFIG.h"
#include "RF_PHY.h"
#include <PWM_MAIN.h>
#include "HAL.h"


/*********************************************************************
 * GLOBAL TYPEDEFS
 */
uint8_t taskID;
uint8_t TX_DATA[200] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
#define TX_Out_Cycle_Num    250     //预设发送次数
uint32_t TX_Out_Cycle =0;       //发送次数
uint8_t Time_Out_RF_RX_TASKID =INVALID_TASK_ID;         //定时接受数据包事件

uint8_t LED_OP_Read_EXT_TASKID = INVALID_TASK_ID;     //LED开启时 定时扫描外部端口

#define TimeOut_RX_Close_T   600          //预设接收沉默时间 *0.625   //375ms
#define TimeOut_TX_Open_T   20              //预设接收开启时间*0.625    //12.5ms
#define TimeOut_Delay_RX_T  300             //预设等待接收扫描时间*0.625

/*****************************************************************************
 *
 *处理接收到的数据包
 *
 ****************************************************************************/

uint8_t RX_Buff_Len;
uint8_t RX_BUFF[50];    //接收数据包缓存
uint8_t RX_Stop_Flag =0;     //RX运行屏蔽标志

uint8_t RX_Serial_Num_quantity=0;         //接收到的数据包缓存数量
#define RX_Serial_Dat_Num   50
uint8_t RX_Serial_Num_Buff[RX_Serial_Dat_Num][4];   //数据包历史编号缓存，与历史编号一致的数据包不转发

void RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)      //接收数据包处理函数
{
    uint32_t RX_Serial_Num,RX_Serial_Num1;     //获取到的数据包编号
    uint32_t RF_TX_T;       //根据收到包的编号延迟对应时间避免冲突
    PRINT("RF_RX_Data_Run!.\r\n");

    RX_Stop_Flag = 1;

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //载入数据包
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

//载入当前数据包的编号

    if((RX_BUFF[0]==0x55)&&(RX_BUFF[1]==0xAA)&&(RX_Data_LEN>=10))      //数据包合法时 最小数据长度10
    {


        RX_Serial_Num = RX_BUFF[2];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[3];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[4];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[5];

        PRINT("RX_Serial_Num:%x\r\n",RX_Serial_Num);
        RX_Buff_Len = RX_Data_LEN;

    }
    else
    {
        RX_Stop_Flag=0;
        RX_Buff_Len =0;
        return;     //数据不合法停止运行
    }
    RX_Serial_Num1 =0;      //重置初始值
    if(RX_Serial_Num_quantity>0)        //有历史数据包时查询历史是否有重复ID 有则不做处理
    {
        for (uint8_t it = 0; it <=RX_Serial_Num_quantity; it++)
        {
            RX_Serial_Num1 = RX_Serial_Num_Buff[it][3];
            RX_Serial_Num1<<=8;
            RX_Serial_Num1 |= RX_Serial_Num_Buff[it][2];
            RX_Serial_Num1<<=8;
            RX_Serial_Num1 |= RX_Serial_Num_Buff[it][1];
            RX_Serial_Num1<<=8;
            RX_Serial_Num1 |= RX_Serial_Num_Buff[it][0];

            PRINT("\r\nit = %d.\r\n",it);
            PRINT("RX_Serial_Num1:%x.\r\n\r\n",RX_Serial_Num1);

            if(RX_Serial_Num==RX_Serial_Num1)       //有一样ID时停止循环
                it = RX_Serial_Num_quantity;      //停止比对ID号for循环


        }
    }




    if(RX_Serial_Num==RX_Serial_Num1) //当收到一致数据时继续接收，不理会
    {

        RX_Stop_Flag=0;             //清除停止接收标志
        PRINT("\r\n\r\nRX_Buff_ID_reuse,RX_Buff_ID_reuse,RX_Buff_ID_reuse.\r\n\r\n");     //提示 ID重复

        return;     //停止运行

    }


    //将新的ID存入本地
    if(RX_Serial_Num_quantity<(RX_Serial_Dat_Num-1))     //当本地数据没满时
    {
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][0] = RX_Serial_Num&0xff;             //对应空间放入数据
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][1] = RX_Serial_Num>>8&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][2] = RX_Serial_Num>>16&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][0]);   //输出获取到的值
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][3]);
        RX_Serial_Num_quantity++;       //位置+1

    }
    else        //除去第一个将新的放在最后一个
    {
        for (uint8_t i= 1;  i<RX_Serial_Dat_Num; i++)
        {
            RX_Serial_Num_Buff[i-1][0] = RX_Serial_Num_Buff[i][0];
            RX_Serial_Num_Buff[i-1][1] = RX_Serial_Num_Buff[i][1];
            RX_Serial_Num_Buff[i-1][2] = RX_Serial_Num_Buff[i][2];
            RX_Serial_Num_Buff[i-1][3] = RX_Serial_Num_Buff[i][3];
        }
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0] = RX_Serial_Num&0XFF;        //最后位置赋予新的值
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1] = RX_Serial_Num>>8&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2] = RX_Serial_Num>>16&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0]);  //输出获取到的值
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3]);

    }


    for (int it = 0; it < RX_Data_LEN; it++)
    {
        TX_DATA[it] = RX_BUFF[it];
    }

    RF_TX_T = RX_BUFF[8];
    RF_TX_T<<=8;
    RF_TX_T|=RX_BUFF[9];

    TX_Out_Cycle = TX_Out_Cycle_Num;

//开灯

    if(LED_OP==0)       //灯未开启时
        tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //开灯后开启定时扫描 外部输入


    tmos_set_event( LED_PWM_Run_TomsID , OP_LED );


    tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5*RF_TX_T);



    //RX_Stop_Flag =0; //其他情况，继续嗅探射频输入

}


/***********************************************************************
 *
 * 发射新的数据包时先将数据包放到本地缓存 (接收防重)
 *
 *
 **********************************************************************/

void Data_To_RX_Serial_Num_Buff(uint32_t Serial_Data)
{

    //将新的ID存入本地
    if(RX_Serial_Num_quantity<(RX_Serial_Dat_Num-1))     //当本地数据没满时
    {
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][0] = Serial_Data&0xff;             //对应空间放入数据
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][1] = Serial_Data>>8&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][2] = Serial_Data>>16&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][3] = Serial_Data>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][0]);
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][3]);
        RX_Serial_Num_quantity++;       //位置+1

    }
    else        //除去第一个将新的放在最后一个
    {
        for (uint8_t i= 1;  i<RX_Serial_Dat_Num; i++)
        {
            RX_Serial_Num_Buff[i-1][0] = RX_Serial_Num_Buff[i][0];
            RX_Serial_Num_Buff[i-1][1] = RX_Serial_Num_Buff[i][1];
            RX_Serial_Num_Buff[i-1][2] = RX_Serial_Num_Buff[i][2];
            RX_Serial_Num_Buff[i-1][3] = RX_Serial_Num_Buff[i][3];
        }
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0] = Serial_Data&0XFF;        //最后位置赋予新的值
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1] = Serial_Data>>8&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2] = Serial_Data>>16&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3] = Serial_Data>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0]);
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3]);

    }

}



/*********************************************************************
 * @fn      RF_2G4StatusCallBack
 *
 * @brief   RF 状态回调，注意：不可在此函数中直接调用RF接收或者发送API，需要使用事件的方式调用
 *
 * @param   sta     - 状态类型
 * @param   crc     - crc校验结果
 * @param   rxBuf   - 数据buf指针
 *
 * @return  none
 *********************************************************************/
uint32_t  Rand_Num =0;

void RF_2G4StatusCallBack(uint8_t sta, uint8_t crc, uint8_t *rxBuf)
{
    switch(sta)
    {
        case TX_MODE_TX_FINISH:
        {
            break;
        }
        case TX_MODE_TX_FAIL:
        {
            break;
        }
        case TX_MODE_RX_DATA:
        {
            RF_Shut();
            if(crc == 1)
            {
                PRINT("crc error\n");
            }
            else if(crc == 2)
            {
                PRINT("match type error\n");
            }
            else
            {
                uint8_t i;
                PRINT("tx recv,rssi:%d\n", (int8_t)rxBuf[0]);
                PRINT("len:%d-", rxBuf[1]);
                for(i = 0; i < rxBuf[1]; i++)
                    PRINT("%x ", rxBuf[i + 2]);
                PRINT("\n");
            }
            break;
        }
        case TX_MODE_RX_TIMEOUT: // Timeout is about 200us
        {
            break;
        }
        case RX_MODE_RX_DATA:
        {
            if(crc == 1)
            {
                PRINT("crc error\n");
            }
            else if(crc == 2)
            {
                PRINT("match type error\n");
            }
            else
            {
                uint8_t i;
                PRINT("rx recv, rssi: %d\n", (int8_t)rxBuf[0]);
                PRINT("len: %d-\r\n", rxBuf[1]);
                for(i = 0; i < rxBuf[1]; i++)
                    PRINT("%x ", rxBuf[i + 2]);
                PRINT("\n");
            }
            Rand_Num = tmos_rand();
            PRINT("Rand_Num:%x.\r\n",Rand_Num);

            RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //数据包引入处理函数
//            tmos_set_event(taskID, SBP_RF_RF_RX_EVT);  //接收完不再直接重新开启接收
            break;
        }
        case RX_MODE_TX_FINISH:
        {
            tmos_set_event(taskID, SBP_RF_RF_RX_EVT);
            break;
        }
        case RX_MODE_TX_FAIL:
        {
            break;
        }
    }
    PRINT("STA: %x\n", sta);
}

/*********************************************************************
 * @fn      RF_ProcessEvent
 *
 * @brief   RF 事件处理
 *
 * @param   task_id - 任务ID
 * @param   events  - 事件标志
 *
 * @return  未完成事件
 ************************************************************************/
uint32_t TX_Dat_Num =10;       //发送数据包编号

uint16_t RF_ProcessEvent(uint8_t task_id, uint16_t events)
{
    if(events & SYS_EVENT_MSG)
    {
        uint8_t *pMsg;

        if((pMsg = tmos_msg_receive(task_id)) != NULL)
        {
            // Release the TMOS message
            tmos_msg_deallocate(pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }
    if(events & SBP_RF_START_DEVICE_EVT)
    {
        tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 1000);
        PRINT("sbp_rf_periodic_evt_Run.\r\n");
        return events ^ SBP_RF_START_DEVICE_EVT;
    }
    if(events & SBP_RF_PERIODIC_EVT)        //数据包发送事件
    {
        RF_Shut();
      //  Rand_Num =tmos_rand();

//        TX_DATA[0] = 0X55;
//        TX_DATA[1] = 0XAA;
//        TX_DATA[2] = Rand_Num>>24;
//        TX_DATA[3] = Rand_Num>>16%0XFF;
//        TX_DATA[4] = Rand_Num>>8&0XFF;
//        TX_DATA[5] = Rand_Num&0XFF;

       // Rand_Num = TX_Dat_Num++;//tmos_rand();
//        TX_DATA[6] = 0xef;//TX_Out_Cycle>>24;
//        TX_DATA[7] = 0xab;//TX_Out_Cycle>>16%0XFF;


        TX_DATA[8] = TX_Out_Cycle>>8&0XFF;
        TX_DATA[9] = TX_Out_Cycle&0XFF;

        if(TX_Out_Cycle>0)
        {
            RF_Tx(TX_DATA, 10, 0xFF, 0xFF);
            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);
            TX_Out_Cycle--;
        }
        else
            RX_Stop_Flag =0;        //发送完之后开始使能定时接收

        return events ^ SBP_RF_PERIODIC_EVT;
    }
    if(events & SBP_RF_RF_RX_EVT)
    {
        uint8_t state;
        RF_Shut();
        TX_DATA[0]++;
        state = RF_Rx(TX_DATA, 10, 0xFF, 0xFF);  //不再在接收事件函数中打开接收
        PRINT("RX mode.state = %x\n", state);

        Rand_Num = tmos_rand();
        PRINT("Rand_Num:%x.\r\n",Rand_Num);

        return events ^ SBP_RF_RF_RX_EVT;
    }
    return 0;
}

/*********************************************************************
 *
 *  @开启定时扫描RF接收
 *
 *
 ********************************************************************/
uint8_t   EX_Null_Flag =0;      // 外部释放标志
uint32_t EX_Dat;        //外部输入值 （PA5输入）
uint32_t EX_Time =0;        //外部定时扫描
#define EX_Time_T   10      // * 接收状态扫描周期*0.625ms

uint8_t CH_Num =0;          //当前所处频道号

#define ADC_Test_Light_T    2      //定义ADC检测周期

uint8_t ADC_Test_Light_Time=0;       //定义ADC检测周期值

uint8_t LED_OP_T  =0;

uint16_t Time_Out_RF_RX_Evnt(tmosTaskID task_id, tmosEvents events)
{
    uint8_t state;

   // PRINT("Time_Out_RF_RX_Evnt_events:%x.\r\n",events);
    if(events&TimeOut_RX_Open)      //开启接收
    {

        if((ADC_Test_Light_Time<ADC_Test_Light_T)&&(LED_OP==0))    //ADC检测周期计时
        {
            ADC_Test_Light_Time++;
        }
        else if(LED_OP==0)  //只允许灯灭时采样
        {
            ADC_Test_Light_Time =0;
            ADC_Test_Light_Run();           //检测一次亮度
        }
        else    //亮灯时光敏电阻采样计时清零
        {
            ADC_Test_Light_Time =0;
        }

        EX_Dat =Ex_Input_Read();        //读取外部输入值

      //  EX_Dat =0;

        PRINT("EXDAT:%X.\r\n",EX_Dat);
        if((EX_Dat&0x800)&&(LED_OP==0)&&(Light_State!=Light_Day_State))        //不为白天PA5为高电平时  当开灯且松开过外部输入时 发送一次新的数据包
        {
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //开灯

            RX_Stop_Flag =1;
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //停止接收

            Rand_Num =tmos_rand();      //用一个随机数封包

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数

            Data_To_RX_Serial_Num_Buff(Rand_Num);           //将要发送的数据包ID保存到接收缓存，接收防冲

            tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //定时扫描 外部输入

            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //发送数据到无线
        }
//        else if((TX_Out_Cycle==0)&&(EX_Dat&0X800)&&(LED_OP==1))         //判断是否还有感应 定时触发
//        {
//
//            EX_Time++;
//            if(EX_Time>=EX_Time_T)        //溢出时
//            {
//                RX_Stop_Flag =1;
//                EX_Time =0;
//                //生成新的值 向外发送
//                tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //开灯
//
//                RX_Stop_Flag =1;
//                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //停止接收
//
//                Rand_Num =tmos_rand();      //用一个随机数封包
//
//                TX_DATA[0] = 0X55;
//                TX_DATA[1] = 0XAA;
//                TX_DATA[2] = Rand_Num>>24;
//                TX_DATA[3] = Rand_Num>>16%0XFF;
//                TX_DATA[4] = Rand_Num>>8&0XFF;
//                TX_DATA[5] = Rand_Num&0XFF;
//                TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数
//
//                tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //发送数据到无线
//            }
//            else
//            {
//                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //设定多少时间后开启RF接收
//            }
//        }
        else
        {
//            if(LED_OP==1)
//                EX_Time =EX_Time_T+1;     //平时清空外部扫描计时
//            else
//            {
//                EX_Time =0;
//            }


        RF_Shut();      //停止RF收发状态

            if(Light_State!=Light_Day_State)            //当不处于白天时开启接收
            {
                state = RF_Rx(TX_DATA, 10, 0XFF,0XFF);
                PRINT("RX mode.state = %x\n", state);
            }
            if((RX_Stop_Flag==0)&&(CH_Num!=0))
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Close ,TimeOut_TX_Open_T);        //设定多少时间后关闭RF接收
             else
                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //停止接收
        }
        return events^TimeOut_RX_Open;
    }

    if(events&TimeOut_RX_Close)     //关闭接收
    {

       // if(LED_OP==0)
        RF_Shut();      //关灯时停止RF收发状态

        CH_Jump();          //检测预设频道

        PRINT("tIMEOut_RX_Close.\r\n");
       if((RX_Stop_Flag==0)&&(CH_Num!=0))
       tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //设定多少时间后开启RF接收
        else
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);

       return events^TimeOut_RX_Close;
    }

    if(events&TimeOut_Delay_RX)         //不对射频做干涉
    {
        CH_Jump();          //检测预设频道

        if((LED_OP==0)&&(CH_Num!=0))       //关灯时清空标志位
        {
            LED_OP_T++;
            if(LED_OP_T>5)      //关灯超过5* TimeOut_Delay_RX_T 清空标志位
            {
                RX_Stop_Flag =0;
                LED_OP_T =0;
            }
        }
        else {
            LED_OP_T =0;
        }

        if((RX_Stop_Flag==0)&&(CH_Num!=0))     //判断是否开始接收数据
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //开始接收数据
        else
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);     //否则继续定时扫描


        return events^TimeOut_Delay_RX;
    }


    return 0;

}




uint16_t Read_EXT_Evnt(tmosTaskID task_id, tmosEvents events)
{

    if(events&LED_OP_Read_EXT)
    {
        GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);  //配置ADC引脚，防止漏电

        EX_Dat =Ex_Input_Read();        //读取外部输入值


        if(EX_Dat&0X800)
        {



           // RX_Stop_Flag =1;
            //生成新的值 向外发送
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //开灯

            RX_Stop_Flag =1;
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //停止接收

            Rand_Num =tmos_rand();      //用一个随机数封包

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数

            Data_To_RX_Serial_Num_Buff(Rand_Num);           //将要发送的数据包ID保存到接收缓存，接收防冲


            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //发送数据到无线

            if(LED_OP==1)       //开灯时继续开启扫描
            {
                tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //定时扫描 外部输入
             //   GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10


            }

        }
        else
        if(LED_OP==1)
            tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,1000);        //开灯时增加扫描频率

        return events^LED_OP_Read_EXT;
    }

    return 0;
}



/*********************************************************************
 * @fn      RF_Init
 *
 * @brief   RF 初始化
 *
 * @return  none
 */
void RF_Init(void)
{

    uint8_t    state;
    rfConfig_t rfConfig;

    tmos_memset(&rfConfig, 0, sizeof(rfConfig_t));
    taskID = TMOS_ProcessEventRegister(RF_ProcessEvent);
    rfConfig.accessAddress = 0x71764129; // 禁止使用0x55555555以及0xAAAAAAAA ( 建议不超过24次位反转，且不超过连续的6个0或1 )
    rfConfig.CRCInit = 0x555555;
    rfConfig.Channel = 8;
    rfConfig.Frequency = 2450000;
    rfConfig.LLEMode = LLE_MODE_BASIC | LLE_MODE_EX_CHANNEL; // 使能 LLE_MODE_EX_CHANNEL 表示 选择 rfConfig.Frequency 作为通信频点
    rfConfig.rfStatusCB = RF_2G4StatusCallBack;
    rfConfig.RxMaxlen = 251;
    state = RF_Config(&rfConfig);
    PRINT("rf 2.4g init: %x\n", state);

    Time_Out_RF_RX_TASKID =TMOS_ProcessEventRegister(Time_Out_RF_RX_Evnt);
    tmos_set_event( Time_Out_RF_RX_TASKID , TimeOut_RX_Open );

    LED_OP_Read_EXT_TASKID = TMOS_ProcessEventRegister(Read_EXT_Evnt);

//
//        { // RX mode
//            state = RF_Rx(TX_DATA, 0, 0xFF, 0xFF);
//            PRINT("RX mode.state = %x\n", state);
//        }

//    	{ // TX mode
//    		tmos_set_event( taskID , SBP_RF_PERIODIC_EVT );
//    	}

}

/***********************************************************************************
 *
 *  RF_Set_CH1
 *  RF信道设置为 CH1
 *
 **********************************************************************************/

void RF_Set_CH1()
{
    uint8_t state;
    rfConfig_t rfConfig;
    RX_Stop_Flag =1;        //停止接收
    RF_Shut();

    RF_SetChannel(2460000);
    PRINT("RF 2.4G SET CH1:%x\r\n.",state);
    RX_Stop_Flag =0;        //开启接收

}


/***********************************************************************************
 *
 *  RF_Set_CH2
 *  RF信道设置为 CH1
 *
 **********************************************************************************/

void RF_Set_CH2()
{
    uint8_t state;
    rfConfig_t rfConfig;
    RX_Stop_Flag =1;        //停止接收
    RF_Shut();
    RF_SetChannel(2470000);

    PRINT("RF 2.4G SET CH2:%x\r\n.",state);
    RX_Stop_Flag =0;        //开启接收

}

/******************************************************************************
 *
 * 信道跳转
 *
 ******************************************************************************/

void CH_Jump()
{

    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_PD);      //设置下拉输入 高电平触发
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_PD);      //设置下拉输入 高电平触发


    EX_Dat =Ex_Input_Read();        //读取外部输入值

    PRINT("RF 2.4G SET EX_Dat:%x\r\n.",EX_Dat);

    if((EX_Dat&0x1000)&&(CH_Num!=1)&&((EX_Dat&0x2000)==0))      // PA12上拉时切换到CH1
    {
        RF_Set_CH1();
        CH_Num =1;      //设定频道号标志位

    }
    else if((EX_Dat&0X2000)&&(CH_Num!=2)&&((EX_Dat&0X1000)==0))     //PA13上拉时切换到CH2
    {
        RF_Set_CH2();
        CH_Num =2;      //设定频道号标志位

    }

    if(CH_Num==0)
    {
        RF_Shut();
        PRINT("RF_Set_CH_Error!\r\n");

    }
    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //设置高阻输入
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //设置高阻输入

}







/******************************** endfile @ main ******************************/
