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
uint8_t TX_DATA[50] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
#define TX_Out_Cycle_Num    300     //预设发送次数
uint32_t TX_Out_Cycle =0;       //发送次数
uint8_t Time_Out_RF_RX_TASKID =INVALID_TASK_ID;         //定时接受数据包事件

uint8_t LED_OP_Read_EXT_TASKID = INVALID_TASK_ID;     //LED开启时 定时扫描外部端口

#define TimeOut_RX_Close_T   600          //预设接收沉默时间 *0.625   //375ms
#define TimeOut_TX_Open_T   25              //预设接收开启时间*0.625    //12.5ms
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

/**********************************************************************
 *
 *@void NetWork_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)      //带组网模式下接收数据包处理函数
 *
 *
 *********************************************************************/
void NetWork_Mode_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)
{
    uint32_t RX_Serial_Num,RX_Serial_Num1;     //获取到的数据包编号
    uint32_t RF_TX_T;       //根据收到包的编号延迟对应时间避免冲突
    uint8_t IS;     //对比计数
    PRINT("RF_RX_Data_Run!.\r\n");

    RX_Stop_Flag = 1;

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //载入数据包
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

//载入当前数据包的编号

    if(Host_Slave_Mode==1)      //在主机模式时
    {
        //对比收到的数据包是否和自己同组
        if(
            (CHIP_UNIQUE_ID[0]==RX_BUFF[2])&&(CHIP_UNIQUE_ID[1]==RX_BUFF[3])&&
            (CHIP_UNIQUE_ID[2]==RX_BUFF[4])&&(CHIP_UNIQUE_ID[3]==RX_BUFF[5])&&
            (CHIP_UNIQUE_ID[4]==RX_BUFF[6])&&(CHIP_UNIQUE_ID[5]==RX_BUFF[7])&&
            (CHIP_UNIQUE_ID[6]==RX_BUFF[8])&&(CHIP_UNIQUE_ID[7]==RX_BUFF[9])

           )
        {   //数据合法
            PRINT("RX_Buff_Host_ID_OK!\r\n");       //主机模式数据有效打印输出
        }
        else
        {
            RX_Stop_Flag=0;
            RX_Buff_Len =0;
            return;     //数据不合法停止运行
        }
    }
    else if((Host_Slave_Mode==2)&&(Flash_Save_Slave_Host_ID[9]==1)) //在从机模式且绑定过主机时
    {
        //对比收到的数据包是否和自己同组
         if(
            (Flash_Save_Slave_Host_ID[0]==RX_BUFF[2])&&(Flash_Save_Slave_Host_ID[1]==RX_BUFF[3])&&
            (Flash_Save_Slave_Host_ID[2]==RX_BUFF[4])&&(Flash_Save_Slave_Host_ID[3]==RX_BUFF[5])&&
            (Flash_Save_Slave_Host_ID[4]==RX_BUFF[6])&&(Flash_Save_Slave_Host_ID[5]==RX_BUFF[7])&&
            (Flash_Save_Slave_Host_ID[6]==RX_BUFF[8])&&(Flash_Save_Slave_Host_ID[7]==RX_BUFF[9])

             )
            {
                 //数据合法
              PRINT("Slave_RX_Buff_Host_ID_OK!\r\n");  //从机模式数据有效打印输出
            }
            else
            {
                RX_Stop_Flag =0;
                RX_Buff_Len =0;
                return;         //数据不合法停止运行
            }


    }
    else
    {
        RX_Stop_Flag=0;
        RX_Buff_Len =0;
        return;     //状态不合法停止运行
    }

    //判断数据包合法性

    if((RX_BUFF[0]==0xAA)&&(RX_BUFF[1]==0x55)&&(RX_Data_LEN>=20))      //数据包合法时 最小数据长度10
    {


        RX_Serial_Num = RX_BUFF[10];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[11];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[12];
        RX_Serial_Num<<=8;
        RX_Serial_Num|=RX_BUFF[13];

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

    RF_TX_T = RX_BUFF[16];
    RF_TX_T<<=8;
    RF_TX_T|=RX_BUFF[17];

    RF_TX_T+=CHIP_UNIQUE_ID[7];     //发射延迟加上ID号第7位以实现错位

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
 *
 *@void NetWork_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)
 *@组网状态下处理接收到的数据包（从机模式）
 *
 ********************************************************************/

void NetWork_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)
{

    uint8_t i;
    uint8_t RX_Host_ID[10];
    PRINT("NetWork_RF_RX_Data_Run!\r\n");
    PRINT("RX_Data_Len:%d.\r\n",RX_Data_LEN);

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //载入数据包
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

    if(Host_Slave_Mode==2)  //处于从机模式时
    {
        if((RX_BUFF[0]==0xAA)&&(RX_BUFF[1]==0x55)&&(RX_Data_LEN>=20))      //数据包合法时 最小数据长度20
        {

            if(RX_BUFF[19]==1)
            {

//                GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
//                GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//                GPIOA_SetBits(GPIO_Pin_10);         //使用上拉GPIO开灯
                TMR1_Disable();
                TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // 占空比 50%, 修改占空比必须暂时关闭定时器
                TMR1_Enable();

                PRINT("LED_OP!\r\n");
            }
            else if(RX_BUFF[19]==0)
            {
//                GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
//                GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//                GPIOA_ResetBits(GPIO_Pin_10);         //使用下拉GPIO关灯

                TMR1_Disable();
                TMR1_PWMActDataWidth(0); // 占空比 50%, 修改占空比必须暂时关闭定时器
                TMR1_Enable();

                PRINT("LED_Close!\r\n");
            }

            for(i =0;i<8;i++)
            {
                if(Flash_Save_Slave_Host_ID[i]!=RX_BUFF[i+2])  //检测到与ID不符的信息 结束循环
                {
                    break;
                }
            }

            if(i<8)     //说明收到的数据和Flash存储的不一致
            {
                for(uint8_t it =0;it<8;it++)        //将待写入数据放入缓存
                    RX_Host_ID[it] = RX_BUFF[it+2];

                RX_Host_ID[8] = RX_BUFF[18];        //将通讯ID写入缓存
                RX_Host_ID[9] = 0x01;       //最后一位写1 表示已绑定主机
                Flash_Host_ID_Run(RX_Host_ID);      //写入数据
            }
            else
            {
                PRINT("RX_Host_ID_Exist!\r\n");     //说明收到的数据和本地数据一致
            }

        }



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

#ifdef RF_LED_Mode
            RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //数据包引入处理函数
#endif

#ifdef NetWork_Mode

           if(NetWork_Mode_Run==0)
               NetWork_Mode_RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //数据包引入处理函数
           else if(NetWork_Mode_Run==1)
               NetWork_RF_RX_Data_Run(rxBuf+2,rxBuf[1]);        //组网模式下数据包接收处理


            if(NetWork_Mode_Run==1)         //处于正常工作模式时不重新开启接收，避免因为重新开启接收影响发射和周期性开启接收过程
                tmos_set_event(taskID, SBP_RF_RF_RX_EVT);  //接收完再重新开启接收


#endif
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

#ifdef  RF_LED_Mode

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

#endif

#ifdef NetWork_Mode

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

        TX_DATA[14] =0;
        TX_DATA[15] =0;

        TX_DATA[16] = TX_Out_Cycle>>8&0XFF;
        TX_DATA[17] = TX_Out_Cycle&0XFF;

        if(TX_Out_Cycle>0)
        {
            RF_Tx(TX_DATA, 20, 0xFF, 0xFF);
            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);
            TX_Out_Cycle--;
        }
        else
            RX_Stop_Flag =0;        //发送完之后开始使能定时接收


#endif

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
uint32_t EX_Dat_B;      //外部输入 GPIOB

uint8_t NetWork_Mode_Run =0;        //进入组网模式标志位

uint32_t EX_Time =0;        //外部定时扫描
#define EX_Time_T   10      // * 接收状态扫描周期*0.625ms

uint8_t CH_Num =0;          //当前所处频道号

#define ADC_Test_Light_T    2      //定义ADC检测周期

uint8_t ADC_Test_Light_Time=0;       //定义ADC检测周期值

uint8_t LED_OP_T  =0;

uint32_t Slave_Mode_NetWork_T =0;       //记录从机模式下配网时间，一定时间后初始化

#define Slave_Mode_NetWork_Rst_T   16000/Open_NetWork_T

#define Open_NetWork_T  32      //预设 Open_NetWork 运行周期

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

#ifdef RF_LED_Mode
            Rand_Num =tmos_rand();      //用一个随机数封包

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数


            Data_To_RX_Serial_Num_Buff(Rand_Num);           //将要发送的数据包ID保存到接收缓存，接收防冲
#endif


#ifdef  NetWork_Mode

            Rand_Num = tmos_rand();     //生成一个随机数
            Data_To_RX_Serial_Num_Buff(Rand_Num);           //将要发送的数据包ID保存到接收缓存，接收防冲

            TX_DATA[0] = 0XAA;
            TX_DATA[1] = 0X55;

            if(Host_Slave_Mode==1)  //主机状态下
            {
                //通讯ID使用自身ID号
                TX_DATA[2] = CHIP_UNIQUE_ID[0];
                TX_DATA[3] = CHIP_UNIQUE_ID[1];
                TX_DATA[4] = CHIP_UNIQUE_ID[2];
                TX_DATA[5] = CHIP_UNIQUE_ID[3];
                TX_DATA[6] = CHIP_UNIQUE_ID[4];
                TX_DATA[7] = CHIP_UNIQUE_ID[5];
                TX_DATA[8] = CHIP_UNIQUE_ID[6];
                TX_DATA[9] = CHIP_UNIQUE_ID[7];

                TX_DATA[10] = Rand_Num>>24;     //加入随机数
                TX_DATA[11] = Rand_Num>>16%0XFF;
                TX_DATA[12] = Rand_Num>>8&0XFF;
                TX_DATA[13] = Rand_Num&0XFF;

                TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数

            }
            else if(Host_Slave_Mode==2) //从机状态下
            {

                if(Flash_Save_Slave_Host_ID[9]==1)      //当已绑定时
                {
                    TX_DATA[2] =Flash_Save_Slave_Host_ID[0];
                    TX_DATA[3] =Flash_Save_Slave_Host_ID[1];
                    TX_DATA[4] =Flash_Save_Slave_Host_ID[2];
                    TX_DATA[5] =Flash_Save_Slave_Host_ID[3];
                    TX_DATA[6] =Flash_Save_Slave_Host_ID[4];
                    TX_DATA[7] =Flash_Save_Slave_Host_ID[5];
                    TX_DATA[8] =Flash_Save_Slave_Host_ID[6];
                    TX_DATA[9] =Flash_Save_Slave_Host_ID[7];

                    TX_DATA[10] = Rand_Num>>24; //加入随机数
                    TX_DATA[11] = Rand_Num>>16&0xFF; //加入随机数
                    TX_DATA[12] = Rand_Num>>8&0xFF; //加入随机数
                    TX_DATA[13] = Rand_Num&0xFF; //加入随机数

                    TX_Out_Cycle = TX_Out_Cycle_Num;    //预设发送次数

                }
                else    //未绑定时
                {


                    TX_Out_Cycle =0;        //未绑定的从机模式不发送数据
                }

            }

#endif



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

        if(((Host_Slave_Mode==2)&&(Flash_Save_Slave_Host_ID[9]!=1))&&(NetWork_Mode_Run==0))       //不满足 从机模式下未绑定时正常工作
        {
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Close ,600);        //设定多少时间后返回此事件
            GPIOA_SetBits(GPIO_Pin_15); // 配置 PA15为上拉 低功耗状态下关闭热释电

        }
        else        //满足从机模式下未绑定时，进入低功耗轮巡模式
        {

            if((RX_Stop_Flag==0)&&(CH_Num!=0)&&(NetWork_Mode_Run==0))
                  tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //设定多少时间后开启RF接收
                   else if(NetWork_Mode_Run==0)
                       tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);

        }
       //  else
      //      tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //触发组网周期

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

        if((RX_Stop_Flag==0)&&(CH_Num!=0)&&(NetWork_Mode_Run==0))     //判断是否开始接收数据
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //开始接收数据
        else if(NetWork_Mode_Run==0)
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);     //否则继续定时扫描
        else {
            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //触发组网周期

        }

        return events^TimeOut_Delay_RX;
    }
#ifdef NetWork_Mode

    if(events&Open_NetWork)     //进入匹配模式
    {

        EX_Dat_B = EX_Input_Read_B();       //读取GPIOB 数值  判断组网按键是否按下


        if((EX_Dat_B&0X80)==0)      //判断PB7是否被下拉
        {
            //PB7被下拉时说明仍然在匹配模式
            if(Host_Slave_Mode==1)  //主机模式
            {
                PRINT("Host_Slave_Mode_Run!\r\n");
                NetWork_Host_Run();
            }
            else if(Host_Slave_Mode==2) //从机模式
            {
                Slave_Mode_NetWork_T ++;
                if(Slave_Mode_NetWork_T==Slave_Mode_NetWork_Rst_T)     //从机模式按下时长超过设定值 清空保存的数据 只进入一次所以使用等于
                {
                    Data_Flash_Eraes();             //初始化值
                    Read_Flash_Host_ID_Run();       //更新数据区域
                    RF_Shut();          //停止RF工作
                    RF_SetChannel(2402000+(Host_CH*2000));         //清空后无适配频段使用自身频段
                    TMR1_Disable();
                    TMR1_PWMActDataWidth(0); // 占空比 0%关灯, 修改占空比必须暂时关闭定时器
                    TMR1_Enable();
                    GPIOA_SetBits(GPIO_Pin_15); // 配置 PA15为上拉 低功耗状态下关闭热释电

                }
            }

            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //再次触发周期20ms

        }
        else
        {
            /************************跳转到工作频段
            ***********************************/
            Slave_Mode_NetWork_T =0;        //清空从机模式按下时间
            NetWork_Mode_Run =0;

            TMR1_Disable();                 //停止PWM输出
            GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);

            PRINT("Time1_PWM_Close_OK!\r\n");           //退出组网模式时灭灯
            LED_OP =0;

            if(Host_Slave_Mode==1)      //主机模式下
            {
                PRINT("Host_Mode_TO_Host_CH:Host_CH:%d.",Host_CH);
                RF_Shut();          //跳转到工作频率
                RF_SetChannel(2402000+(Host_CH*2000));

            }
            else if(Host_Slave_Mode==2)  //从机模式下
            {
                RF_Shut();      //跳转到工作频率
                if(Flash_Save_Slave_Host_ID[9]==1)      //保存有有效频段时
                {

                    PRINT("Slave_Host_CH:%d.\r\n",Flash_Save_Slave_Host_ID[8]);     //输出跳转频率

                    RF_Shut();
                    RF_SetChannel(2402000+(Flash_Save_Slave_Host_ID[8]*2000));      //跳转到主机频率

                }
                else    //未匹配主机时使用自身频率
                {

                    PRINT("Slave_Host_CH_Null!\r\n");
                    PRINT("Host_CH:%d.\r\n",Host_CH);

                    RF_Shut();
                    RF_SetChannel(2402000+(Host_CH*2000));

                }
            }



            //NetWork_Mode_Run();
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //开始接收数据

        }


    }

#endif

    return 0;

}




uint16_t Read_EXT_Evnt(tmosTaskID task_id, tmosEvents events)
{

    if(events&LED_OP_Read_EXT)
    {
        GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);  //配置ADC引脚，防止漏电

        EX_Dat =Ex_Input_Read();        //读取外部输入值


        if((EX_Dat&0X800)&&(NetWork_Mode_Run==0))
        {
#ifdef RF_LED_Mode
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
#endif

#ifdef NetWork_Mode
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //开灯

            Rand_Num = tmos_rand();     //生成一个随机数
            Data_To_RX_Serial_Num_Buff(Rand_Num);           //将要发送的数据包ID保存到接收缓存，接收防冲

            TX_DATA[0] = 0XAA;
            TX_DATA[1] = 0X55;

            if(Host_Slave_Mode==1)  //主机状态下
            {
                //通讯ID使用自身ID号
                TX_DATA[2] = CHIP_UNIQUE_ID[0];
                TX_DATA[3] = CHIP_UNIQUE_ID[1];
                TX_DATA[4] = CHIP_UNIQUE_ID[2];
                TX_DATA[5] = CHIP_UNIQUE_ID[3];
                TX_DATA[6] = CHIP_UNIQUE_ID[4];
                TX_DATA[7] = CHIP_UNIQUE_ID[5];
                TX_DATA[8] = CHIP_UNIQUE_ID[6];
                TX_DATA[9] = CHIP_UNIQUE_ID[7];

                TX_DATA[10] = Rand_Num>>24;     //加入随机数
                TX_DATA[11] = Rand_Num>>16%0XFF;
                TX_DATA[12] = Rand_Num>>8&0XFF;
                TX_DATA[13] = Rand_Num&0XFF;

                TX_Out_Cycle = TX_Out_Cycle_Num; //预设发送次数

            }
            else if(Host_Slave_Mode==2) //从机状态下
            {

                if(Flash_Save_Slave_Host_ID[9]==1)      //当已绑定时
                {
                    TX_DATA[2] =Flash_Save_Slave_Host_ID[0];
                    TX_DATA[3] =Flash_Save_Slave_Host_ID[1];
                    TX_DATA[4] =Flash_Save_Slave_Host_ID[2];
                    TX_DATA[5] =Flash_Save_Slave_Host_ID[3];
                    TX_DATA[6] =Flash_Save_Slave_Host_ID[4];
                    TX_DATA[7] =Flash_Save_Slave_Host_ID[5];
                    TX_DATA[8] =Flash_Save_Slave_Host_ID[6];
                    TX_DATA[9] =Flash_Save_Slave_Host_ID[7];

                    TX_DATA[10] = Rand_Num>>24; //加入随机数
                    TX_DATA[11] = Rand_Num>>16&0xFF; //加入随机数
                    TX_DATA[12] = Rand_Num>>8&0xFF; //加入随机数
                    TX_DATA[13] = Rand_Num&0xFF; //加入随机数

                    TX_Out_Cycle = TX_Out_Cycle_Num;    //预设发送次数

                }
                else    //未绑定时
                {


                    TX_Out_Cycle =0;        //未绑定的从机模式不发送数据
                }

            }


            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //发送数据到无线


            if(LED_OP==1)       //开灯时继续开启扫描
            {
                tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //定时扫描 外部输入
             //   GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10


            }
#endif
        }
        else
        if((LED_OP==1)&&(NetWork_Mode_Run==0))
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
 ********************************************************************/
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
 * 信道跳转  //或者被用来切换主机从机模式
 *
 ******************************************************************************/

uint8_t Host_Slave_Mode =0;       //主机标志位  1 表示主机  2 表示从机

uint8_t NetWork_EX_Delay =0;        //组网外部信号输入消抖
#define NetWork_EX_Delay_DAT   6    //组网外部信号输入消抖值

uint8_t NetWork_Run =0;     //判断是否在组网模式下

void CH_Jump()
{

#ifdef RF_LED_Mode
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
#endif

#ifdef NetWork_Mode

    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_PD);      //设置下拉输入 高电平触发
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_PD);      //设置下拉输入 高电平触发

    CH_Num =3;      //组网模式运行下，使用3作为信道值
    EX_Dat =Ex_Input_Read();        //读取外部输入值

    PRINT("\r\nRead_Host_or_Slave.\r\n",EX_Dat);
    PRINT("NetWork_Mode_Run:%d.\r\n",NetWork_Mode_Run);

    if((EX_Dat&0x1000)&&(Host_Slave_Mode!=1)&&((EX_Dat&0x2000)==0))      // PA12上拉时切换到主机模式
    {
        Host_Slave_Mode =1;

        PRINT("\r\nIs In Host Mode!\r\n");
        //跳转到对应频段
        RF_Shut();          //主机模式下使用自身频段
        RF_SetChannel(2402000+(Host_CH*2000));


    }
    else if((EX_Dat&0X2000)&&(Host_Slave_Mode!=2)&&((EX_Dat&0X1000)==0))     //PA13上拉时切换到从机模式
    {
        Host_Slave_Mode =2;

        PRINT("\r\nIs In Slave Mode!\r\n");

        RF_Shut();
        if(Flash_Save_Slave_Host_ID[9]==1)      //保存有有效频段时
        {

            PRINT("Slave_Host_CH:%d.\r\n",Flash_Save_Slave_Host_ID[8]);     //输出跳转频率

            RF_Shut();
            RF_SetChannel(2402000+(Flash_Save_Slave_Host_ID[8]*2000));      //跳转到主机频率

        }
        else    //未匹配主机时使用自身频率
        {

            PRINT("Slave_Host_CH_Null!\r\n");
            PRINT("Host_CH:%d.\r\n",Host_CH);

            RF_Shut();
            RF_SetChannel(2402000+(Host_CH*2000));

        }

    }

    if(Host_Slave_Mode==0)
    {

        PRINT("nRead_Host_or_Slave_Error!\r\n");

    }

    EX_Dat_B = EX_Input_Read_B();       //读取GPIOB 数值  判断组网按键是否按下

    PRINT("EX_Dat_B:%x.\r\n",EX_Dat_B);

    if(((EX_Dat_B&0x80)==0)&&(NetWork_Mode_Run==0)&&(RX_Stop_Flag==0)&&(TX_Out_Cycle==0))           //当匹配按键按下时 且无线不在发射时
    {
        PRINT("EX_Dat_B7_EN!\r\n");
        NetWork_EX_Delay++;             //消抖确认按下
        if(NetWork_EX_Delay>NetWork_EX_Delay_DAT)
        {
            NetWork_EX_Delay =0;
            Jump_to_NetWork_CH();

         //   GPIOA_SetBits(GPIO_Pin_10);         // 不使用上拉GPIO开灯

            NetWork_Led_Now =0;         //设置LED初值为无效值
            NetWork_Host_Run_T_Dat =200;        //预设一个必然触发的初始值
            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,30);  //一定时间后进入配网事件

        }

    }
    else if((EX_Dat_B&0X80))
    {
        NetWork_EX_Delay =0;
    }

    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //设置高阻输入
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //设置高阻输入

#endif

}

/******************************************
 *
 * void Jump_to_NetWork_CH()
 *
 *@跳转到组网专用频段
 *@设置组网频段为2480000
 *
 ****************************************/

void Jump_to_NetWork_CH()
{

    uint8_t state;

#ifdef NetWork_Mode

    if(NetWork_Mode_Run==0)
    {
        RX_Stop_Flag =1;        //停止接收
        RF_Shut();
        RF_SetChannel(2480000);

        PRINT("RF 2.4G SET CH2:%x\r\n.",state);
        RX_Stop_Flag =0;        //开启接收

        NetWork_Mode_Run =1;            // 跳转到对应频段后 配网标志位置位

        RF_Shut();

        state = RF_Rx(TX_DATA, 10, 0XFF,0XFF);      //在组网模式开启接收
        PRINT("RX mode.state = %x\n", state);

        //配置PWM口
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
        GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10

     //   GPIOA_SetBits(GPIO_Pin_10);         // 不使用上拉GPIO开灯

        //使用PWM驱动
        //TMR1_PWMInit(High_Level, PWM_Times_1);

        if(Host_Slave_Mode==2)
        {
            TMR1_Disable();

            TMR1_PWMCycleCfg(3000); // 周期 100us
            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();
            LED_OP =1;

        }
//
    }

#endif

}


/*********************************************
 *
 *@void NetWork_Dat_Packet_Run(uint8_t LED_State)
 *
 *@主机模式下发送组网数据包封包
 *@LED_State  LED状态
 *
 *  封包格式：
 *  0XAA+0X55+8字节ID号+4字节0X00（预留随机数）+4字节数据包编号 共计18字节+信道号+LED状态
 *
 *********************************************/

void NetWork_Dat_Packet_Run(uint8_t LED_State)
{

    TX_DATA[0] = 0XAA;
    TX_DATA[1] = 0X55;

    TX_DATA[2] = CHIP_UNIQUE_ID[0];
    TX_DATA[3] = CHIP_UNIQUE_ID[1];
    TX_DATA[4] = CHIP_UNIQUE_ID[2];
    TX_DATA[5] = CHIP_UNIQUE_ID[3];
    TX_DATA[6] = CHIP_UNIQUE_ID[4];
    TX_DATA[7] = CHIP_UNIQUE_ID[5];
    TX_DATA[8] = CHIP_UNIQUE_ID[6];
    TX_DATA[9] = CHIP_UNIQUE_ID[7];

    TX_DATA[10] = 0;
    TX_DATA[11] = 0;
    TX_DATA[12] = 0;
    TX_DATA[13] = 0;

    TX_DATA[14] = 0;
    TX_DATA[15] = 0;
    TX_DATA[16] = 0;
    TX_DATA[17] = 0;

    TX_DATA[18] = Host_CH;
    TX_DATA[19] = LED_State;

}


/********************************************
 *
 *@主机状态运行配网模式
 *
 *
 ********************************************/
#define NetWork_Host_Run_T      60      //主机模式下组网发送间隔

uint8_t NetWork_Host_Run_T_Dat =0;

uint8_t NetWork_Led_Now =0;     //组网模式下LED开关标志位（不与开关灯公用）

void NetWork_Host_Run()
{
    NetWork_Host_Run_T_Dat++;
    if(NetWork_Host_Run_T_Dat>NetWork_Host_Run_T)
    {
        NetWork_Host_Run_T_Dat =0;
        if(NetWork_Led_Now==0)
        {

            if(NetWork_Led_Now==0)
            {
                LED_OP =1;

                TMR1_Disable();

                TMR1_PWMCycleCfg(3000); // 周期 100us
                TMR1_Disable();
                TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // 占空比 50%, 修改占空比必须暂时关闭定时器
                TMR1_Enable();

            }

            NetWork_Led_Now =1;

//            GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
//            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//            GPIOA_SetBits(GPIO_Pin_10);         //使用上拉GPIO开灯



            NetWork_Dat_Packet_Run(NetWork_Led_Now);        //生成数据包
            TX_Out_Cycle = 20;  //设定发送次数
            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);

            PRINT("NetWork_LED_OP!\r\n");
        }
        else if(NetWork_Led_Now==1)
        {
            if(NetWork_Led_Now==1)
            {

                TMR1_Disable();
                TMR1_PWMActDataWidth(0); // 占空比 50%, 修改占空比必须暂时关闭定时器
                TMR1_Enable();
            }

            NetWork_Led_Now =0;

//            GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
//            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//            GPIOA_ResetBits(GPIO_Pin_10);         //下拉GPIO以关灯



            NetWork_Dat_Packet_Run(NetWork_Led_Now);        //生成数据包
            TX_Out_Cycle = 20; //设定发送次数
            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);


            PRINT("NetWork_LED_Close!\r\n");
        }
        else
        {
            NetWork_Led_Now =0;
        }

    }
}





/******************************** endfile @ main ******************************/
