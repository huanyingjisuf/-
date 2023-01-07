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
uint8_t TX_DATA[200] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
#define TX_Out_Cycle_Num    250     //Ԥ�跢�ʹ���
uint32_t TX_Out_Cycle =0;       //���ʹ���
uint8_t Time_Out_RF_RX_TASKID =INVALID_TASK_ID;         //��ʱ�������ݰ��¼�

uint8_t LED_OP_Read_EXT_TASKID = INVALID_TASK_ID;     //LED����ʱ ��ʱɨ���ⲿ�˿�

#define TimeOut_RX_Close_T   600          //Ԥ����ճ�Ĭʱ�� *0.625   //375ms
#define TimeOut_TX_Open_T   20              //Ԥ����տ���ʱ��*0.625    //12.5ms
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

            RF_RX_Data_Run(rxBuf+2,rxBuf[1]);       //���ݰ����봦����
//            tmos_set_event(taskID, SBP_RF_RF_RX_EVT);  //�����겻��ֱ�����¿�������
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
uint32_t EX_Time =0;        //�ⲿ��ʱɨ��
#define EX_Time_T   10      // * ����״̬ɨ������*0.625ms

uint8_t CH_Num =0;          //��ǰ����Ƶ����

#define ADC_Test_Light_T    2      //����ADC�������

uint8_t ADC_Test_Light_Time=0;       //����ADC�������ֵ

uint8_t LED_OP_T  =0;

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

            Rand_Num =tmos_rand();      //��һ����������

            TX_DATA[0] = 0X55;
            TX_DATA[1] = 0XAA;
            TX_DATA[2] = Rand_Num>>24;
            TX_DATA[3] = Rand_Num>>16%0XFF;
            TX_DATA[4] = Rand_Num>>8&0XFF;
            TX_DATA[5] = Rand_Num&0XFF;
            TX_Out_Cycle = TX_Out_Cycle_Num; //Ԥ�跢�ʹ���

            Data_To_RX_Serial_Num_Buff(Rand_Num);           //��Ҫ���͵����ݰ�ID���浽���ջ��棬���շ���

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
       if((RX_Stop_Flag==0)&&(CH_Num!=0))
       tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open , TimeOut_RX_Close_T);        //�趨����ʱ�����RF����
        else
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);

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

        if((RX_Stop_Flag==0)&&(CH_Num!=0))     //�ж��Ƿ�ʼ��������
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_RX_Open,TimeOut_RX_Close_T);     //��ʼ��������
        else
            tmos_start_task(Time_Out_RF_RX_TASKID,TimeOut_Delay_RX,TimeOut_Delay_RX_T);     //���������ʱɨ��


        return events^TimeOut_Delay_RX;
    }


    return 0;

}




uint16_t Read_EXT_Evnt(tmosTaskID task_id, tmosEvents events)
{

    if(events&LED_OP_Read_EXT)
    {
        GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);  //����ADC���ţ���ֹ©��

        EX_Dat =Ex_Input_Read();        //��ȡ�ⲿ����ֵ


        if(EX_Dat&0X800)
        {



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

        }
        else
        if(LED_OP==1)
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
 */
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
 * �ŵ���ת
 *
 ******************************************************************************/

void CH_Jump()
{

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

}







/******************************** endfile @ main ******************************/
