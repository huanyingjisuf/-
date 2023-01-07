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
/* ͷ�ļ����� */

#include "CONFIG.h"
#include "RF_PHY.h"
#include <PWM_MAIN.h>
#include "HAL.h"




/*********************************************************************
 * GLOBAL TYPEDEFS
 */
uint8_t taskID;
uint8_t TX_DATA[50] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
#define TX_Out_Cycle_Num    300     //Ԥ�跢�ʹ���
uint32_t TX_Out_Cycle =0;       //���ʹ���
uint8_t Time_Out_RF_RX_TASKID =INVALID_TASK_ID;         //��ʱ�������ݰ��¼�

uint8_t LED_OP_Read_EXT_TASKID = INVALID_TASK_ID;     //LED����ʱ ��ʱɨ���ⲿ�˿�

#define TimeOut_RX_Close_T   600          //Ԥ����ճ�Ĭʱ�� *0.625   //375ms
#define TimeOut_TX_Open_T   25              //Ԥ����տ���ʱ��*0.625    //12.5ms
#define TimeOut_Delay_RX_T  300             //Ԥ��ȴ�����ɨ��ʱ��*0.625

/*****************************************************************************
 *
 *������յ������ݰ�
 *
 ****************************************************************************/

uint8_t RX_Buff_Len;
uint8_t RX_BUFF[50];    //�������ݰ�����
uint8_t RX_Stop_Flag =0;     //RX�������α�־

uint8_t RX_Serial_Num_quantity=0;         //���յ������ݰ���������
#define RX_Serial_Dat_Num   50
uint8_t RX_Serial_Num_Buff[RX_Serial_Dat_Num][4];   //���ݰ���ʷ��Ż��棬����ʷ���һ�µ����ݰ���ת��

void RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)      //�������ݰ�������
{

    uint32_t RX_Serial_Num,RX_Serial_Num1;     //��ȡ�������ݰ����
    uint32_t RF_TX_T;       //�����յ����ı���ӳٶ�Ӧʱ������ͻ
    PRINT("RF_RX_Data_Run!.\r\n");

    RX_Stop_Flag = 1;

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //�������ݰ�
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

//���뵱ǰ���ݰ��ı��

    if((RX_BUFF[0]==0x55)&&(RX_BUFF[1]==0xAA)&&(RX_Data_LEN>=10))      //���ݰ��Ϸ�ʱ ��С���ݳ���10
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
        return;     //���ݲ��Ϸ�ֹͣ����
    }
    RX_Serial_Num1 =0;      //���ó�ʼֵ
    if(RX_Serial_Num_quantity>0)        //����ʷ���ݰ�ʱ��ѯ��ʷ�Ƿ����ظ�ID ����������
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

            if(RX_Serial_Num==RX_Serial_Num1)       //��һ��IDʱֹͣѭ��
                it = RX_Serial_Num_quantity;      //ֹͣ�ȶ�ID��forѭ��


        }
    }

    if(RX_Serial_Num==RX_Serial_Num1) //���յ�һ������ʱ�������գ������
    {

        RX_Stop_Flag=0;             //���ֹͣ���ձ�־
        PRINT("\r\n\r\nRX_Buff_ID_reuse,RX_Buff_ID_reuse,RX_Buff_ID_reuse.\r\n\r\n");     //��ʾ ID�ظ�

        return;     //ֹͣ����

    }


    //���µ�ID���뱾��
    if(RX_Serial_Num_quantity<(RX_Serial_Dat_Num-1))     //����������û��ʱ
    {

        RX_Serial_Num_Buff[RX_Serial_Num_quantity][0] = RX_Serial_Num&0xff;             //��Ӧ�ռ��������
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][1] = RX_Serial_Num>>8&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][2] = RX_Serial_Num>>16&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][0]);   //�����ȡ����ֵ
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][3]);
        RX_Serial_Num_quantity++;       //λ��+1

    }
    else        //��ȥ��һ�����µķ������һ��
    {
        for (uint8_t i= 1;  i<RX_Serial_Dat_Num; i++)
        {
            RX_Serial_Num_Buff[i-1][0] = RX_Serial_Num_Buff[i][0];
            RX_Serial_Num_Buff[i-1][1] = RX_Serial_Num_Buff[i][1];
            RX_Serial_Num_Buff[i-1][2] = RX_Serial_Num_Buff[i][2];
            RX_Serial_Num_Buff[i-1][3] = RX_Serial_Num_Buff[i][3];
        }
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0] = RX_Serial_Num&0XFF;        //���λ�ø����µ�ֵ
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1] = RX_Serial_Num>>8&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2] = RX_Serial_Num>>16&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0]);  //�����ȡ����ֵ
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

//����

    if(LED_OP==0)       //��δ����ʱ
        tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //���ƺ�����ʱɨ�� �ⲿ����


    tmos_set_event( LED_PWM_Run_TomsID , OP_LED );


    tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5*RF_TX_T);



    //RX_Stop_Flag =0; //���������������̽��Ƶ����

}

/**********************************************************************
 *
 *@void NetWork_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)      //������ģʽ�½������ݰ�������
 *
 *
 *********************************************************************/
void NetWork_Mode_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)
{
    uint32_t RX_Serial_Num,RX_Serial_Num1;     //��ȡ�������ݰ����
    uint32_t RF_TX_T;       //�����յ����ı���ӳٶ�Ӧʱ������ͻ
    uint8_t IS;     //�Աȼ���
    PRINT("RF_RX_Data_Run!.\r\n");

    RX_Stop_Flag = 1;

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //�������ݰ�
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

//���뵱ǰ���ݰ��ı��

    if(Host_Slave_Mode==1)      //������ģʽʱ
    {
        //�Ա��յ������ݰ��Ƿ���Լ�ͬ��
        if(
            (CHIP_UNIQUE_ID[0]==RX_BUFF[2])&&(CHIP_UNIQUE_ID[1]==RX_BUFF[3])&&
            (CHIP_UNIQUE_ID[2]==RX_BUFF[4])&&(CHIP_UNIQUE_ID[3]==RX_BUFF[5])&&
            (CHIP_UNIQUE_ID[4]==RX_BUFF[6])&&(CHIP_UNIQUE_ID[5]==RX_BUFF[7])&&
            (CHIP_UNIQUE_ID[6]==RX_BUFF[8])&&(CHIP_UNIQUE_ID[7]==RX_BUFF[9])

           )
        {   //���ݺϷ�
            PRINT("RX_Buff_Host_ID_OK!\r\n");       //����ģʽ������Ч��ӡ���
        }
        else
        {
            RX_Stop_Flag=0;
            RX_Buff_Len =0;
            return;     //���ݲ��Ϸ�ֹͣ����
        }
    }
    else if((Host_Slave_Mode==2)&&(Flash_Save_Slave_Host_ID[9]==1)) //�ڴӻ�ģʽ�Ұ󶨹�����ʱ
    {
        //�Ա��յ������ݰ��Ƿ���Լ�ͬ��
         if(
            (Flash_Save_Slave_Host_ID[0]==RX_BUFF[2])&&(Flash_Save_Slave_Host_ID[1]==RX_BUFF[3])&&
            (Flash_Save_Slave_Host_ID[2]==RX_BUFF[4])&&(Flash_Save_Slave_Host_ID[3]==RX_BUFF[5])&&
            (Flash_Save_Slave_Host_ID[4]==RX_BUFF[6])&&(Flash_Save_Slave_Host_ID[5]==RX_BUFF[7])&&
            (Flash_Save_Slave_Host_ID[6]==RX_BUFF[8])&&(Flash_Save_Slave_Host_ID[7]==RX_BUFF[9])

             )
            {
                 //���ݺϷ�
              PRINT("Slave_RX_Buff_Host_ID_OK!\r\n");  //�ӻ�ģʽ������Ч��ӡ���
            }
            else
            {
                RX_Stop_Flag =0;
                RX_Buff_Len =0;
                return;         //���ݲ��Ϸ�ֹͣ����
            }


    }
    else
    {
        RX_Stop_Flag=0;
        RX_Buff_Len =0;
        return;     //״̬���Ϸ�ֹͣ����
    }

    //�ж����ݰ��Ϸ���

    if((RX_BUFF[0]==0xAA)&&(RX_BUFF[1]==0x55)&&(RX_Data_LEN>=20))      //���ݰ��Ϸ�ʱ ��С���ݳ���10
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
        return;     //���ݲ��Ϸ�ֹͣ����
    }
    RX_Serial_Num1 =0;      //���ó�ʼֵ
    if(RX_Serial_Num_quantity>0)        //����ʷ���ݰ�ʱ��ѯ��ʷ�Ƿ����ظ�ID ����������
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

            if(RX_Serial_Num==RX_Serial_Num1)       //��һ��IDʱֹͣѭ��
                it = RX_Serial_Num_quantity;      //ֹͣ�ȶ�ID��forѭ��


        }
    }




    if(RX_Serial_Num==RX_Serial_Num1) //���յ�һ������ʱ�������գ������
    {

        RX_Stop_Flag=0;             //���ֹͣ���ձ�־
        PRINT("\r\n\r\nRX_Buff_ID_reuse,RX_Buff_ID_reuse,RX_Buff_ID_reuse.\r\n\r\n");     //��ʾ ID�ظ�

        return;     //ֹͣ����

    }


    //���µ�ID���뱾��
    if(RX_Serial_Num_quantity<(RX_Serial_Dat_Num-1))     //����������û��ʱ
    {

        RX_Serial_Num_Buff[RX_Serial_Num_quantity][0] = RX_Serial_Num&0xff;             //��Ӧ�ռ��������
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][1] = RX_Serial_Num>>8&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][2] = RX_Serial_Num>>16&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][0]);   //�����ȡ����ֵ
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][3]);
        RX_Serial_Num_quantity++;       //λ��+1

    }
    else        //��ȥ��һ�����µķ������һ��
    {
        for (uint8_t i= 1;  i<RX_Serial_Dat_Num; i++)
        {
            RX_Serial_Num_Buff[i-1][0] = RX_Serial_Num_Buff[i][0];
            RX_Serial_Num_Buff[i-1][1] = RX_Serial_Num_Buff[i][1];
            RX_Serial_Num_Buff[i-1][2] = RX_Serial_Num_Buff[i][2];
            RX_Serial_Num_Buff[i-1][3] = RX_Serial_Num_Buff[i][3];
        }
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0] = RX_Serial_Num&0XFF;        //���λ�ø����µ�ֵ
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][1] = RX_Serial_Num>>8&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][2] = RX_Serial_Num>>16&0XFF;
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][3] = RX_Serial_Num>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Dat_Num-1,RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0]);  //�����ȡ����ֵ
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

    RF_TX_T+=CHIP_UNIQUE_ID[7];     //�����ӳټ���ID�ŵ�7λ��ʵ�ִ�λ

    TX_Out_Cycle = TX_Out_Cycle_Num;

//����

    if(LED_OP==0)       //��δ����ʱ
        tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //���ƺ�����ʱɨ�� �ⲿ����


    tmos_set_event( LED_PWM_Run_TomsID , OP_LED );


    tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5*RF_TX_T);



    //RX_Stop_Flag =0; //���������������̽��Ƶ����


}



/***********************************************************************
 *
 * �����µ����ݰ�ʱ�Ƚ����ݰ��ŵ����ػ��� (���շ���)
 *
 *
 **********************************************************************/

void Data_To_RX_Serial_Num_Buff(uint32_t Serial_Data)
{

    //���µ�ID���뱾��
    if(RX_Serial_Num_quantity<(RX_Serial_Dat_Num-1))     //����������û��ʱ
    {
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][0] = Serial_Data&0xff;             //��Ӧ�ռ��������
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][1] = Serial_Data>>8&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][2] = Serial_Data>>16&0xff;
        RX_Serial_Num_Buff[RX_Serial_Num_quantity][3] = Serial_Data>>24;

        PRINT("RX_Serial_Num_Buff[%d][0]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][0]);
        PRINT("RX_Serial_Num_Buff[%d][1]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][1]);
        PRINT("RX_Serial_Num_Buff[%d][2]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][2]);
        PRINT("RX_Serial_Num_Buff[%d][3]=%X.\r\n",RX_Serial_Num_quantity,RX_Serial_Num_Buff[RX_Serial_Num_quantity][3]);
        RX_Serial_Num_quantity++;       //λ��+1

    }
    else        //��ȥ��һ�����µķ������һ��
    {
        for (uint8_t i= 1;  i<RX_Serial_Dat_Num; i++)
        {
            RX_Serial_Num_Buff[i-1][0] = RX_Serial_Num_Buff[i][0];
            RX_Serial_Num_Buff[i-1][1] = RX_Serial_Num_Buff[i][1];
            RX_Serial_Num_Buff[i-1][2] = RX_Serial_Num_Buff[i][2];
            RX_Serial_Num_Buff[i-1][3] = RX_Serial_Num_Buff[i][3];
        }
        RX_Serial_Num_Buff[RX_Serial_Dat_Num-1][0] = Serial_Data&0XFF;        //���λ�ø����µ�ֵ
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
 *@����״̬�´�����յ������ݰ����ӻ�ģʽ��
 *
 ********************************************************************/

void NetWork_RF_RX_Data_Run(uint8_t *RX_DATAS,uint8_t RX_Data_LEN)
{

    uint8_t i;
    uint8_t RX_Host_ID[10];
    PRINT("NetWork_RF_RX_Data_Run!\r\n");
    PRINT("RX_Data_Len:%d.\r\n",RX_Data_LEN);

    for(uint8_t i=0;i<RX_Data_LEN;i++)          //�������ݰ�
    {

        RX_BUFF[i] =*RX_DATAS++;

    }

    if(Host_Slave_Mode==2)  //���ڴӻ�ģʽʱ
    {
        if((RX_BUFF[0]==0xAA)&&(RX_BUFF[1]==0x55)&&(RX_Data_LEN>=20))      //���ݰ��Ϸ�ʱ ��С���ݳ���20
        {

            if(RX_BUFF[19]==1)
            {

//                GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
//                GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//                GPIOA_SetBits(GPIO_Pin_10);         //ʹ������GPIO����
                TMR1_Disable();
                TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
                TMR1_Enable();

                PRINT("LED_OP!\r\n");
            }
            else if(RX_BUFF[19]==0)
            {
//                GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
//                GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//                GPIOA_ResetBits(GPIO_Pin_10);         //ʹ������GPIO�ص�

                TMR1_Disable();
                TMR1_PWMActDataWidth(0); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
                TMR1_Enable();

                PRINT("LED_Close!\r\n");
            }

            for(i =0;i<8;i++)
            {
                if(Flash_Save_Slave_Host_ID[i]!=RX_BUFF[i+2])  //��⵽��ID��������Ϣ ����ѭ��
                {
                    break;
                }
            }

            if(i<8)     //˵���յ������ݺ�Flash�洢�Ĳ�һ��
            {
                for(uint8_t it =0;it<8;it++)        //����д�����ݷ��뻺��
                    RX_Host_ID[it] = RX_BUFF[it+2];

                RX_Host_ID[8] = RX_BUFF[18];        //��ͨѶIDд�뻺��
                RX_Host_ID[9] = 0x01;       //���һλд1 ��ʾ�Ѱ�����
                Flash_Host_ID_Run(RX_Host_ID);      //д������
            }
            else
            {
                PRINT("RX_Host_ID_Exist!\r\n");     //˵���յ������ݺͱ�������һ��
            }

        }



    }

}



/*********************************************************************
 * @fn      RF_2G4StatusCallBack
 *
 * @brief   RF ״̬�ص���ע�⣺�����ڴ˺�����ֱ�ӵ���RF���ջ��߷���API����Ҫʹ���¼��ķ�ʽ����
 *
 * @param   sta     - ״̬����
 * @param   crc     - crcУ����
 * @param   rxBuf   - ����bufָ��
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
            RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //���ݰ����봦����
#endif

#ifdef NetWork_Mode

           if(NetWork_Mode_Run==0)
               NetWork_Mode_RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //���ݰ����봦����
           else if(NetWork_Mode_Run==1)
               NetWork_RF_RX_Data_Run(rxBuf+2,rxBuf[1]);        //����ģʽ�����ݰ����մ���


            if(NetWork_Mode_Run==1)         //������������ģʽʱ�����¿������գ�������Ϊ���¿�������Ӱ�췢��������Կ������չ���
                tmos_set_event(taskID, SBP_RF_RF_RX_EVT);  //�����������¿�������


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
 * @brief   RF �¼�����
 *
 * @param   task_id - ����ID
 * @param   events  - �¼���־
 *
 * @return  δ����¼�
 ************************************************************************/
uint32_t TX_Dat_Num =10;       //�������ݰ����

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
    if(events & SBP_RF_PERIODIC_EVT)        //���ݰ������¼�
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
            RX_Stop_Flag =0;        //������֮��ʼʹ�ܶ�ʱ����

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
            RX_Stop_Flag =0;        //������֮��ʼʹ�ܶ�ʱ����


#endif

        return events ^ SBP_RF_PERIODIC_EVT;
    }
    if(events & SBP_RF_RF_RX_EVT)
    {
        uint8_t state;
        RF_Shut();
        TX_DATA[0]++;
        state = RF_Rx(TX_DATA, 10, 0xFF, 0xFF);  //�����ڽ����¼������д򿪽���
        PRINT("RX mode.state = %x\n", state);

        Rand_Num = tmos_rand();
        PRINT("Rand_Num:%x.\r\n",Rand_Num);

        return events ^ SBP_RF_RF_RX_EVT;
    }
    return 0;
}

/*********************************************************************
 *
 *  @������ʱɨ��RF����
 *
 *
 ********************************************************************/
uint8_t   EX_Null_Flag =0;      // �ⲿ�ͷű�־
uint32_t EX_Dat;        //�ⲿ����ֵ ��PA5���룩
uint32_t EX_Dat_B;      //�ⲿ���� GPIOB

uint8_t NetWork_Mode_Run =0;        //��������ģʽ��־λ

uint32_t EX_Time =0;        //�ⲿ��ʱɨ��
#define EX_Time_T   10      // * ����״̬ɨ������*0.625ms

uint8_t CH_Num =0;          //��ǰ����Ƶ����

#define ADC_Test_Light_T    2      //����ADC�������

uint8_t ADC_Test_Light_Time=0;       //����ADC�������ֵ

uint8_t LED_OP_T  =0;

uint32_t Slave_Mode_NetWork_T =0;       //��¼�ӻ�ģʽ������ʱ�䣬һ��ʱ����ʼ��

#define Slave_Mode_NetWork_Rst_T   16000/Open_NetWork_T

#define Open_NetWork_T  32      //Ԥ�� Open_NetWork ��������

uint16_t Time_Out_RF_RX_Evnt(tmosTaskID task_id, tmosEvents events)
{
    uint8_t state;

   // PRINT("Time_Out_RF_RX_Evnt_events:%x.\r\n",events);
    if(events&TimeOut_RX_Open)      //��������
    {

        if((ADC_Test_Light_Time<ADC_Test_Light_T)&&(LED_OP==0))    //ADC������ڼ�ʱ
        {

            ADC_Test_Light_Time++;

        }
        else if(LED_OP==0)  //ֻ�������ʱ����
        {
            ADC_Test_Light_Time =0;
            ADC_Test_Light_Run();           //���һ������
        }
        else    //����ʱ�������������ʱ����
        {
            ADC_Test_Light_Time =0;
        }

        EX_Dat =Ex_Input_Read();        //��ȡ�ⲿ����ֵ

      //  EX_Dat =0;

        PRINT("EXDAT:%X.\r\n",EX_Dat);
        if((EX_Dat&0x800)&&(LED_OP==0)&&(Light_State!=Light_Day_State))        //��Ϊ����PA5Ϊ�ߵ�ƽʱ  ���������ɿ����ⲿ����ʱ ����һ���µ����ݰ�
        {
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //����

            RX_Stop_Flag =1;
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //ֹͣ����

#ifdef RF_LED_Mode
            Rand_Num =tmos_rand();      //��һ����������

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���


            Data_To_RX_Serial_Num_Buff(Rand_Num);           //��Ҫ���͵����ݰ�ID���浽���ջ��棬���շ���
#endif


#ifdef  NetWork_Mode

            Rand_Num = tmos_rand();     //����һ�������
            Data_To_RX_Serial_Num_Buff(Rand_Num);           //��Ҫ���͵����ݰ�ID���浽���ջ��棬���շ���

            TX_DATA[0] = 0XAA;
            TX_DATA[1] = 0X55;

            if(Host_Slave_Mode==1)  //����״̬��
            {
                //ͨѶIDʹ������ID��
                TX_DATA[2] = CHIP_UNIQUE_ID[0];
                TX_DATA[3] = CHIP_UNIQUE_ID[1];
                TX_DATA[4] = CHIP_UNIQUE_ID[2];
                TX_DATA[5] = CHIP_UNIQUE_ID[3];
                TX_DATA[6] = CHIP_UNIQUE_ID[4];
                TX_DATA[7] = CHIP_UNIQUE_ID[5];
                TX_DATA[8] = CHIP_UNIQUE_ID[6];
                TX_DATA[9] = CHIP_UNIQUE_ID[7];

                TX_DATA[10] = Rand_Num>>24;     //���������
                TX_DATA[11] = Rand_Num>>16%0XFF;
                TX_DATA[12] = Rand_Num>>8&0XFF;
                TX_DATA[13] = Rand_Num&0XFF;

                TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���

            }
            else if(Host_Slave_Mode==2) //�ӻ�״̬��
            {

                if(Flash_Save_Slave_Host_ID[9]==1)      //���Ѱ�ʱ
                {
                    TX_DATA[2] =Flash_Save_Slave_Host_ID[0];
                    TX_DATA[3] =Flash_Save_Slave_Host_ID[1];
                    TX_DATA[4] =Flash_Save_Slave_Host_ID[2];
                    TX_DATA[5] =Flash_Save_Slave_Host_ID[3];
                    TX_DATA[6] =Flash_Save_Slave_Host_ID[4];
                    TX_DATA[7] =Flash_Save_Slave_Host_ID[5];
                    TX_DATA[8] =Flash_Save_Slave_Host_ID[6];
                    TX_DATA[9] =Flash_Save_Slave_Host_ID[7];

                    TX_DATA[10] = Rand_Num>>24; //���������
                    TX_DATA[11] = Rand_Num>>16&0xFF; //���������
                    TX_DATA[12] = Rand_Num>>8&0xFF; //���������
                    TX_DATA[13] = Rand_Num&0xFF; //���������

                    TX_Out_Cycle = TX_Out_Cycle_Num;    //Ԥ�跢�ʹ���

                }
                else    //δ��ʱ
                {


                    TX_Out_Cycle =0;        //δ�󶨵Ĵӻ�ģʽ����������
                }

            }

#endif



            tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //��ʱɨ�� �ⲿ����

            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //�������ݵ�����
        }
//        else if((TX_Out_Cycle==0)&&(EX_Dat&0X800)&&(LED_OP==1))         //�ж��Ƿ��и�Ӧ ��ʱ����
//        {
//
//            EX_Time++;
//            if(EX_Time>=EX_Time_T)        //���ʱ
//            {
//                RX_Stop_Flag =1;
//                EX_Time =0;
//                //�����µ�ֵ ���ⷢ��
//                tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //����
//
//                RX_Stop_Flag =1;
//                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //ֹͣ����
//
//                Rand_Num =tmos_rand();      //��һ����������
//
//                TX_DATA[0] = 0X55;
//                TX_DATA[1] = 0XAA;
//                TX_DATA[2] = Rand_Num>>24;
//                TX_DATA[3] = Rand_Num>>16%0XFF;
//                TX_DATA[4] = Rand_Num>>8&0XFF;
//                TX_DATA[5] = Rand_Num&0XFF;
//                TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���
//
//                tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //�������ݵ�����
//            }
//            else
//            {
//                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //�趨����ʱ�����RF����
//            }
//        }
        else
        {
//            if(LED_OP==1)
//                EX_Time =EX_Time_T+1;     //ƽʱ����ⲿɨ���ʱ
//            else
//            {
//                EX_Time =0;
//            }


            RF_Shut();      //ֹͣRF�շ�״̬

            if(Light_State!=Light_Day_State)            //�������ڰ���ʱ��������
            {
                state = RF_Rx(TX_DATA, 10, 0XFF,0XFF);
                PRINT("RX mode.state = %x\n", state);
            }
            if((RX_Stop_Flag==0)&&(CH_Num!=0))
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Close ,TimeOut_TX_Open_T);        //�趨����ʱ���ر�RF����
             else
                tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //ֹͣ����
        }
        return events^TimeOut_RX_Open;
    }

    if(events&TimeOut_RX_Close)     //�رս���
    {

       // if(LED_OP==0)
        RF_Shut();      //�ص�ʱֹͣRF�շ�״̬

        CH_Jump();          //���Ԥ��Ƶ��

        PRINT("tIMEOut_RX_Close.\r\n");

        if(((Host_Slave_Mode==2)&&(Flash_Save_Slave_Host_ID[9]!=1))&&(NetWork_Mode_Run==0))       //������ �ӻ�ģʽ��δ��ʱ��������
        {
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Close ,600);        //�趨����ʱ��󷵻ش��¼�
            GPIOA_SetBits(GPIO_Pin_15); // ���� PA15Ϊ���� �͹���״̬�¹ر����͵�

        }
        else        //����ӻ�ģʽ��δ��ʱ������͹�����Ѳģʽ
        {

            if((RX_Stop_Flag==0)&&(CH_Num!=0)&&(NetWork_Mode_Run==0))
                  tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //�趨����ʱ�����RF����
                   else if(NetWork_Mode_Run==0)
                       tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);

        }
       //  else
      //      tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //������������

       return events^TimeOut_RX_Close;
    }

    if(events&TimeOut_Delay_RX)         //������Ƶ������
    {
        CH_Jump();          //���Ԥ��Ƶ��

        if((LED_OP==0)&&(CH_Num!=0))       //�ص�ʱ��ձ�־λ
        {
            LED_OP_T++;
            if(LED_OP_T>5)      //�صƳ���5* TimeOut_Delay_RX_T ��ձ�־λ
            {
                RX_Stop_Flag =0;
                LED_OP_T =0;
            }
        }
        else {
            LED_OP_T =0;
        }

        if((RX_Stop_Flag==0)&&(CH_Num!=0)&&(NetWork_Mode_Run==0))     //�ж��Ƿ�ʼ��������
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //��ʼ��������
        else if(NetWork_Mode_Run==0)
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);     //���������ʱɨ��
        else {
            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //������������

        }

        return events^TimeOut_Delay_RX;
    }
#ifdef NetWork_Mode

    if(events&Open_NetWork)     //����ƥ��ģʽ
    {

        EX_Dat_B = EX_Input_Read_B();       //��ȡGPIOB ��ֵ  �ж����������Ƿ���


        if((EX_Dat_B&0X80)==0)      //�ж�PB7�Ƿ�����
        {
            //PB7������ʱ˵����Ȼ��ƥ��ģʽ
            if(Host_Slave_Mode==1)  //����ģʽ
            {
                PRINT("Host_Slave_Mode_Run!\r\n");
                NetWork_Host_Run();
            }
            else if(Host_Slave_Mode==2) //�ӻ�ģʽ
            {
                Slave_Mode_NetWork_T ++;
                if(Slave_Mode_NetWork_T==Slave_Mode_NetWork_Rst_T)     //�ӻ�ģʽ����ʱ�������趨ֵ ��ձ�������� ֻ����һ������ʹ�õ���
                {
                    Data_Flash_Eraes();             //��ʼ��ֵ
                    Read_Flash_Host_ID_Run();       //������������
                    RF_Shut();          //ֹͣRF����
                    RF_SetChannel(2402000+(Host_CH*2000));         //��պ�������Ƶ��ʹ������Ƶ��
                    TMR1_Disable();
                    TMR1_PWMActDataWidth(0); // ռ�ձ� 0%�ص�, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
                    TMR1_Enable();
                    GPIOA_SetBits(GPIO_Pin_15); // ���� PA15Ϊ���� �͹���״̬�¹ر����͵�

                }
            }

            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,Open_NetWork_T);  //�ٴδ�������20ms

        }
        else
        {
            /************************��ת������Ƶ��
            ***********************************/
            Slave_Mode_NetWork_T =0;        //��մӻ�ģʽ����ʱ��
            NetWork_Mode_Run =0;

            TMR1_Disable();                 //ֹͣPWM���
            GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);

            PRINT("Time1_PWM_Close_OK!\r\n");           //�˳�����ģʽʱ���
            LED_OP =0;

            if(Host_Slave_Mode==1)      //����ģʽ��
            {
                PRINT("Host_Mode_TO_Host_CH:Host_CH:%d.",Host_CH);
                RF_Shut();          //��ת������Ƶ��
                RF_SetChannel(2402000+(Host_CH*2000));

            }
            else if(Host_Slave_Mode==2)  //�ӻ�ģʽ��
            {
                RF_Shut();      //��ת������Ƶ��
                if(Flash_Save_Slave_Host_ID[9]==1)      //��������ЧƵ��ʱ
                {

                    PRINT("Slave_Host_CH:%d.\r\n",Flash_Save_Slave_Host_ID[8]);     //�����תƵ��

                    RF_Shut();
                    RF_SetChannel(2402000+(Flash_Save_Slave_Host_ID[8]*2000));      //��ת������Ƶ��

                }
                else    //δƥ������ʱʹ������Ƶ��
                {

                    PRINT("Slave_Host_CH_Null!\r\n");
                    PRINT("Host_CH:%d.\r\n",Host_CH);

                    RF_Shut();
                    RF_SetChannel(2402000+(Host_CH*2000));

                }
            }



            //NetWork_Mode_Run();
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //��ʼ��������

        }


    }

#endif

    return 0;

}




uint16_t Read_EXT_Evnt(tmosTaskID task_id, tmosEvents events)
{

    if(events&LED_OP_Read_EXT)
    {
        GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);  //����ADC���ţ���ֹ©��

        EX_Dat =Ex_Input_Read();        //��ȡ�ⲿ����ֵ


        if((EX_Dat&0X800)&&(NetWork_Mode_Run==0))
        {
#ifdef RF_LED_Mode
           // RX_Stop_Flag =1;
            //�����µ�ֵ ���ⷢ��
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //����

            RX_Stop_Flag =1;
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);      //ֹͣ����

            Rand_Num =tmos_rand();      //��һ����������

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���

            Data_To_RX_Serial_Num_Buff(Rand_Num);           //��Ҫ���͵����ݰ�ID���浽���ջ��棬���շ���


            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //�������ݵ�����

            if(LED_OP==1)       //����ʱ��������ɨ��
            {
                tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //��ʱɨ�� �ⲿ����
             //   GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10


            }
#endif

#ifdef NetWork_Mode
            tmos_set_event( LED_PWM_Run_TomsID , OP_LED );      //����

            Rand_Num = tmos_rand();     //����һ�������
            Data_To_RX_Serial_Num_Buff(Rand_Num);           //��Ҫ���͵����ݰ�ID���浽���ջ��棬���շ���

            TX_DATA[0] = 0XAA;
            TX_DATA[1] = 0X55;

            if(Host_Slave_Mode==1)  //����״̬��
            {
                //ͨѶIDʹ������ID��
                TX_DATA[2] = CHIP_UNIQUE_ID[0];
                TX_DATA[3] = CHIP_UNIQUE_ID[1];
                TX_DATA[4] = CHIP_UNIQUE_ID[2];
                TX_DATA[5] = CHIP_UNIQUE_ID[3];
                TX_DATA[6] = CHIP_UNIQUE_ID[4];
                TX_DATA[7] = CHIP_UNIQUE_ID[5];
                TX_DATA[8] = CHIP_UNIQUE_ID[6];
                TX_DATA[9] = CHIP_UNIQUE_ID[7];

                TX_DATA[10] = Rand_Num>>24;     //���������
                TX_DATA[11] = Rand_Num>>16%0XFF;
                TX_DATA[12] = Rand_Num>>8&0XFF;
                TX_DATA[13] = Rand_Num&0XFF;

                TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���

            }
            else if(Host_Slave_Mode==2) //�ӻ�״̬��
            {

                if(Flash_Save_Slave_Host_ID[9]==1)      //���Ѱ�ʱ
                {
                    TX_DATA[2] =Flash_Save_Slave_Host_ID[0];
                    TX_DATA[3] =Flash_Save_Slave_Host_ID[1];
                    TX_DATA[4] =Flash_Save_Slave_Host_ID[2];
                    TX_DATA[5] =Flash_Save_Slave_Host_ID[3];
                    TX_DATA[6] =Flash_Save_Slave_Host_ID[4];
                    TX_DATA[7] =Flash_Save_Slave_Host_ID[5];
                    TX_DATA[8] =Flash_Save_Slave_Host_ID[6];
                    TX_DATA[9] =Flash_Save_Slave_Host_ID[7];

                    TX_DATA[10] = Rand_Num>>24; //���������
                    TX_DATA[11] = Rand_Num>>16&0xFF; //���������
                    TX_DATA[12] = Rand_Num>>8&0xFF; //���������
                    TX_DATA[13] = Rand_Num&0xFF; //���������

                    TX_Out_Cycle = TX_Out_Cycle_Num;    //Ԥ�跢�ʹ���

                }
                else    //δ��ʱ
                {


                    TX_Out_Cycle =0;        //δ�󶨵Ĵӻ�ģʽ����������
                }

            }


            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);        //�������ݵ�����


            if(LED_OP==1)       //����ʱ��������ɨ��
            {
                tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,6000);      //��ʱɨ�� �ⲿ����
             //   GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10


            }
#endif
        }
        else
        if((LED_OP==1)&&(NetWork_Mode_Run==0))
            tmos_start_task(LED_OP_Read_EXT_TASKID,LED_OP_Read_EXT,1000);        //����ʱ����ɨ��Ƶ��

        return events^LED_OP_Read_EXT;
    }

    return 0;
}



/*********************************************************************
 * @fn      RF_Init
 *
 * @brief   RF ��ʼ��
 *
 * @return  none
 ********************************************************************/
void RF_Init(void)
{

    uint8_t    state;
    rfConfig_t rfConfig;

    tmos_memset(&rfConfig, 0, sizeof(rfConfig_t));
    taskID = TMOS_ProcessEventRegister(RF_ProcessEvent);
    rfConfig.accessAddress = 0x71764129; // ��ֹʹ��0x55555555�Լ�0xAAAAAAAA ( ���鲻����24��λ��ת���Ҳ�����������6��0��1 )
    rfConfig.CRCInit = 0x555555;
    rfConfig.Channel = 8;
    rfConfig.Frequency = 2450000;
    rfConfig.LLEMode = LLE_MODE_BASIC | LLE_MODE_EX_CHANNEL; // ʹ�� LLE_MODE_EX_CHANNEL ��ʾ ѡ�� rfConfig.Frequency ��Ϊͨ��Ƶ��
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
 *  RF�ŵ�����Ϊ CH1
 *
 **********************************************************************************/

void RF_Set_CH1()
{
    uint8_t state;
    rfConfig_t rfConfig;
    RX_Stop_Flag =1;        //ֹͣ����
    RF_Shut();

    RF_SetChannel(2460000);
    PRINT("RF 2.4G SET CH1:%x\r\n.",state);
    RX_Stop_Flag =0;        //��������

}


/***********************************************************************************
 *
 *  RF_Set_CH2
 *  RF�ŵ�����Ϊ CH1
 *
 **********************************************************************************/

void RF_Set_CH2()
{
    uint8_t state;
    rfConfig_t rfConfig;
    RX_Stop_Flag =1;        //ֹͣ����
    RF_Shut();
    RF_SetChannel(2470000);

    PRINT("RF 2.4G SET CH2:%x\r\n.",state);
    RX_Stop_Flag =0;        //��������

}

/******************************************************************************
 *
 * �ŵ���ת  //���߱������л������ӻ�ģʽ
 *
 ******************************************************************************/

uint8_t Host_Slave_Mode =0;       //������־λ  1 ��ʾ����  2 ��ʾ�ӻ�

uint8_t NetWork_EX_Delay =0;        //�����ⲿ�ź���������
#define NetWork_EX_Delay_DAT   6    //�����ⲿ�ź���������ֵ

uint8_t NetWork_Run =0;     //�ж��Ƿ�������ģʽ��

void CH_Jump()
{

#ifdef RF_LED_Mode
    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_PD);      //������������ �ߵ�ƽ����
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_PD);      //������������ �ߵ�ƽ����


    EX_Dat =Ex_Input_Read();        //��ȡ�ⲿ����ֵ

    PRINT("RF 2.4G SET EX_Dat:%x\r\n.",EX_Dat);

    if((EX_Dat&0x1000)&&(CH_Num!=1)&&((EX_Dat&0x2000)==0))      // PA12����ʱ�л���CH1
    {
        RF_Set_CH1();
        CH_Num =1;      //�趨Ƶ���ű�־λ

    }
    else if((EX_Dat&0X2000)&&(CH_Num!=2)&&((EX_Dat&0X1000)==0))     //PA13����ʱ�л���CH2
    {
        RF_Set_CH2();
        CH_Num =2;      //�趨Ƶ���ű�־λ

    }

    if(CH_Num==0)
    {
        RF_Shut();
        PRINT("RF_Set_CH_Error!\r\n");

    }
    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //���ø�������
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //���ø�������
#endif

#ifdef NetWork_Mode

    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_PD);      //������������ �ߵ�ƽ����
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_PD);      //������������ �ߵ�ƽ����

    CH_Num =3;      //����ģʽ�����£�ʹ��3��Ϊ�ŵ�ֵ
    EX_Dat =Ex_Input_Read();        //��ȡ�ⲿ����ֵ

    PRINT("\r\nRead_Host_or_Slave.\r\n",EX_Dat);
    PRINT("NetWork_Mode_Run:%d.\r\n",NetWork_Mode_Run);

    if((EX_Dat&0x1000)&&(Host_Slave_Mode!=1)&&((EX_Dat&0x2000)==0))      // PA12����ʱ�л�������ģʽ
    {
        Host_Slave_Mode =1;

        PRINT("\r\nIs In Host Mode!\r\n");
        //��ת����ӦƵ��
        RF_Shut();          //����ģʽ��ʹ������Ƶ��
        RF_SetChannel(2402000+(Host_CH*2000));


    }
    else if((EX_Dat&0X2000)&&(Host_Slave_Mode!=2)&&((EX_Dat&0X1000)==0))     //PA13����ʱ�л����ӻ�ģʽ
    {
        Host_Slave_Mode =2;

        PRINT("\r\nIs In Slave Mode!\r\n");

        RF_Shut();
        if(Flash_Save_Slave_Host_ID[9]==1)      //��������ЧƵ��ʱ
        {

            PRINT("Slave_Host_CH:%d.\r\n",Flash_Save_Slave_Host_ID[8]);     //�����תƵ��

            RF_Shut();
            RF_SetChannel(2402000+(Flash_Save_Slave_Host_ID[8]*2000));      //��ת������Ƶ��

        }
        else    //δƥ������ʱʹ������Ƶ��
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

    EX_Dat_B = EX_Input_Read_B();       //��ȡGPIOB ��ֵ  �ж����������Ƿ���

    PRINT("EX_Dat_B:%x.\r\n",EX_Dat_B);

    if(((EX_Dat_B&0x80)==0)&&(NetWork_Mode_Run==0)&&(RX_Stop_Flag==0)&&(TX_Out_Cycle==0))           //��ƥ�䰴������ʱ �����߲��ڷ���ʱ
    {
        PRINT("EX_Dat_B7_EN!\r\n");
        NetWork_EX_Delay++;             //����ȷ�ϰ���
        if(NetWork_EX_Delay>NetWork_EX_Delay_DAT)
        {
            NetWork_EX_Delay =0;
            Jump_to_NetWork_CH();

         //   GPIOA_SetBits(GPIO_Pin_10);         // ��ʹ������GPIO����

            NetWork_Led_Now =0;         //����LED��ֵΪ��Чֵ
            NetWork_Host_Run_T_Dat =200;        //Ԥ��һ����Ȼ�����ĳ�ʼֵ
            tmos_start_task(Time_Out_RF_RX_TASKID,Open_NetWork,30);  //һ��ʱ�����������¼�

        }

    }
    else if((EX_Dat_B&0X80))
    {
        NetWork_EX_Delay =0;
    }

    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //���ø�������
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //���ø�������

#endif

}

/******************************************
 *
 * void Jump_to_NetWork_CH()
 *
 *@��ת������ר��Ƶ��
 *@��������Ƶ��Ϊ2480000
 *
 ****************************************/

void Jump_to_NetWork_CH()
{

    uint8_t state;

#ifdef NetWork_Mode

    if(NetWork_Mode_Run==0)
    {
        RX_Stop_Flag =1;        //ֹͣ����
        RF_Shut();
        RF_SetChannel(2480000);

        PRINT("RF 2.4G SET CH2:%x\r\n.",state);
        RX_Stop_Flag =0;        //��������

        NetWork_Mode_Run =1;            // ��ת����ӦƵ�κ� ������־λ��λ

        RF_Shut();

        state = RF_Rx(TX_DATA, 10, 0XFF,0XFF);      //������ģʽ��������
        PRINT("RX mode.state = %x\n", state);

        //����PWM��
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
        GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10

     //   GPIOA_SetBits(GPIO_Pin_10);         // ��ʹ������GPIO����

        //ʹ��PWM����
        //TMR1_PWMInit(High_Level, PWM_Times_1);

        if(Host_Slave_Mode==2)
        {
            TMR1_Disable();

            TMR1_PWMCycleCfg(3000); // ���� 100us
            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
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
 *@����ģʽ�·����������ݰ����
 *@LED_State  LED״̬
 *
 *  �����ʽ��
 *  0XAA+0X55+8�ֽ�ID��+4�ֽ�0X00��Ԥ���������+4�ֽ����ݰ���� ����18�ֽ�+�ŵ���+LED״̬
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
 *@����״̬��������ģʽ
 *
 *
 ********************************************/
#define NetWork_Host_Run_T      60      //����ģʽ���������ͼ��

uint8_t NetWork_Host_Run_T_Dat =0;

uint8_t NetWork_Led_Now =0;     //����ģʽ��LED���ر�־λ�����뿪�صƹ��ã�

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

                TMR1_PWMCycleCfg(3000); // ���� 100us
                TMR1_Disable();
                TMR1_PWMActDataWidth(LED_OP_Dat_Max/2); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
                TMR1_Enable();

            }

            NetWork_Led_Now =1;

//            GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
//            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//
//            GPIOA_SetBits(GPIO_Pin_10);         //ʹ������GPIO����



            NetWork_Dat_Packet_Run(NetWork_Led_Now);        //�������ݰ�
            TX_Out_Cycle = 20;  //�趨���ʹ���
            tmos_start_task(taskID, SBP_RF_PERIODIC_EVT, 5);

            PRINT("NetWork_LED_OP!\r\n");
        }
        else if(NetWork_Led_Now==1)
        {
            if(NetWork_Led_Now==1)
            {

                TMR1_Disable();
                TMR1_PWMActDataWidth(0); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
                TMR1_Enable();
            }

            NetWork_Led_Now =0;

//            GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
//            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);
//            GPIOA_ResetBits(GPIO_Pin_10);         //����GPIO�Թص�



            NetWork_Dat_Packet_Run(NetWork_Led_Now);        //�������ݰ�
            TX_Out_Cycle = 20; //�趨���ʹ���
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
