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
#include "HAL.h"
#include "RF_PHY.h"
#include  "CH57x_timer.h"
#include <PWM_MAIN.h>
#include "CH57x_common.h"


uint8_t  LED_Close_Later_TomsID = INVALID_TASK_ID;

uint8_t LED_OP_CL_PWM_Run_TomsID  = INVALID_TASK_ID;

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   ��ѭ��
 *
 * @return  none
 */
__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();

    }
}


uint32_t LED_OP_PWM_Dat =0;         //Ԥ���LED_����PWMֵ

uint32_t LED_OP_PWM_Dat_In =0;      //��ǰ��LED����ֵ

#define PWM_Dat_ADJ_Div 15          // PWM ADJ ���� �ֶ�ֵ

#define PWM_Dat_ADJ_Time    10      // PWM ADJ ����ʱ����

uint16_t LED_OP_CL_PWM_Run(tmosTaskID task_id, tmosEvents events)
{


    if(events&LED_OP_Run)
    {
        if(LED_OP_PWM_Dat_In<LED_OP_PWM_Dat)
        {
            LED_OP_PWM_Dat_In+=PWM_Dat_ADJ_Div;

            if(LED_OP_PWM_Dat>LED_OP_PWM_Dat)
                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //����1000ms����PIR


        }


        return events^LED_OP_Run;
    }



    if(events&LED_Close_Run)
    {
        if((LED_OP_PWM_Dat_In>1)&&(LED_OP==0))
        {

            if(LED_OP_PWM_Dat_In>PWM_Dat_ADJ_Div)
                LED_OP_PWM_Dat_In-=PWM_Dat_ADJ_Div;
            else
            {
                LED_OP_PWM_Dat_In =1;
            }

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In);
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_Close_Run,PWM_Dat_ADJ_Time);


        }
        else if(LED_OP==0)          //��ֵ����� ����ʱ���ر�
        {
            LED_OP_PWM_Dat_In =0;

            TMR1_Disable();                 //ֹͣPWM���

            GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);
            PRINT("LED_Close_OK!.\r\n");
        }


        return events^LED_Close_Run;
    }


    if(events&LED_OP_1_2_Run)                       //�����ȵ��ڵ�ԭ��1/2
    {
        if(LED_OP_PWM_Dat_In<(LED_OP_PWM_Dat/2))     //���� 1/2ʱ����
        {
            LED_OP_PWM_Dat_In+=PWM_Dat_ADJ_Div;

            if(LED_OP_PWM_Dat>(LED_OP_PWM_Dat/2))
                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/2;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //���������´ε�������


        }
        else if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/2))       //����ԭ��1/2 �½�
        {

            if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/2+PWM_Dat_ADJ_Div))
                LED_OP_PWM_Dat_In-=PWM_Dat_ADJ_Div;
            else
            {

                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/2;           //���ʣ��ֵ< ԭ���趨1/2 ֱ�Ӹ�ֵ ԭ��1/2����

            }

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //���������´ε�������

        }

        return events^LED_OP_1_2_Run;
    }





    return 0;
}



uint8_t LED_OP =0;

void Time1_PWM_Init()
{

        GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);

     //   GPIOA_SetBits(GPIO_Pin_10);         // ��ʹ������GPIO����

        //ʹ��PWM����
        TMR1_PWMInit(High_Level, PWM_Times_1);

        TMR1_PWMCycleCfg(3000); // ���� 100us
        TMR1_Disable();
        TMR1_PWMActDataWidth(0); // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
        TMR1_Enable();
        LED_OP_PWM_Dat =3000;           //Ԥ��Ŀ�������
        LED_OP_PWM_Dat_In =0;           //��յ�ǰֵ

        tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,3);        //��ʼ���������

}

void Time1_PWM_Close()
{
//    TMR1_Disable();                 //ֹͣPWM���
//
//    GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
//    GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);

    //Time3_PWM_Init();

    if(LED_OP_PWM_Dat_In>0)
        tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_Close_Run,3);        //��ʼ��Ϩ�����
    else {
        TMR1_Disable();                 //ֹͣPWM���

        GPIOA_ResetBits(GPIO_Pin_10); // ����PWM�� PA10
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);
        PRINT("Time1_PWM_Close_OK!\r\n");
    }
}




/*******************************************************************
 *
 *  uint16_t LED_Close_Later_Run(tmosTaskID task_id, tmosEvents events)
 *
 *
 *******************************************************************/
uint16_t LED_Close_Later_Run(tmosTaskID task_id, tmosEvents events)
{

    if(events&Later_Test_Light)
    {
        ADC_Test_Light_Run();

        PRINT("\r\nLater_Test_Light.\r\n");

        return events^Later_Test_Light;
    }

    if(events&Later_Disabled_PIR)       //�صƺ�ر�PIR
    {
        GPIOA_SetBits(GPIO_Pin_15);

        PRINT("\r\nLater_Disabled_PIR.\r\n");

        return events^Later_Disabled_PIR;
    }

    if(events&Later_Enabled_PIR)
    {
        //if(Light_State==Light_Night_State)          //�ں�ҹ״̬���ٴο���PIR
                GPIOA_ResetBits(GPIO_Pin_15);

         PRINT("\r\nLater_Enabled_PIR.\r\n");

        return events^Later_Enabled_PIR;
    }

    if(events&Later_OP_LED)                 //δ����ʱʹ�ܿ���
    {
        if(LED_OP==0)
        {
            Time1_PWM_Init();
            tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //����1000ms����PIR

        }
        LED_OP =1;

        tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);         //���� �ص�ʱ��

        return events^Later_OP_LED;
    }

    if(events&Later_Close_LED)          //δ���ʱ�ص�
    {

        if(LED_OP==1)
        {
           Time1_PWM_Close();
           tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //�ص�1000ms����PIR
        }

        LED_OP =0;

        return events^Later_Close_LED;
    }

    return 0;

}




/********************************************************************
 *
 *void Time1_PWM_Init()
 *
 *���룺 ��
 *�������
 *
 *��ʱ��1��PWM���
 *
 *
 *
 *********************************************************************/




uint8_t  LED_PWM_Run_TomsID = INVALID_TASK_ID;

uint16_t LED_PWM_Run(tmosTaskID task_id, tmosEvents events)
{

    if(events&OP_LED)
    {
        if((NetWork_Mode_Run==0)&&(!((Host_Slave_Mode==2)&&(Flash_Save_Slave_Host_ID[9]!=1))))
        {
            if(LED_OP==0)
            {
                GPIOA_SetBits(GPIO_Pin_15);         //�ص�ǰ������PIR
         //       DelayMs(200);
                tmos_start_task(LED_Close_Later_TomsID,Later_OP_LED,320);        //����ǰ200ms��ʧ��PIR

            }
            else
            {
               // Time1_PWM_Init();

                LED_OP =1;


                tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);
            }
        }


        return events^OP_LED;
    }

    if(events&Close_LED)
    {

        if(NetWork_Mode_Run==0)   //��������ģʽ��ʱ
        {
            if(LED_OP==1)           //�����ڿ���״̬ʱ
            {
                GPIOA_SetBits(GPIO_Pin_15);         //�ص�ǰ������PIR
             //   DelayMs(200);

                tmos_start_task(LED_Close_Later_TomsID,Later_Close_LED,320);        //����ǰ200ms��ʧ��PIR

           //     tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //�ص�100ms����PIR

         //       tmos_start_task(LED_Close_Later_TomsID,Later_Test_Light,500);     //�صƺ�200ms��������״̬


            }
            else
            {
              //  Time1_PWM_Close();
                LED_OP =0;
            }

        }


//       DelayMs(100);
//       ADC_Test_Light_Run();        //�صƺ���һ�����Ȳ���
       return events^Close_LED;
    }


    return 0;
}


void GPIO_Init()
{

    GPIOA_ModeCfg(GPIO_Pin_11, GPIO_ModeIN_PD);      //������������ �ߵ�ƽ����
    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //������������ �ߵ�ƽ����
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //������������ �ߵ�ƽ����
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);

    GPIOB_ModeCfg(GPIO_Pin_7,GPIO_ModeIN_PU);       //����PB7Ϊ�ⲿ�������� ���ڽ���ƥ��ģʽ

    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeOut_PP_5mA);        //��ʼ�����͵���ƶ�
    GPIOA_ResetBits(GPIO_Pin_15); // ���� PA15Ϊ���� (Ĭ�Ϻ�ҹ�������͵�)

}

uint32_t Ex_Input_Read()
{
    uint32_t EX_Dat;
    EX_Dat = R32_PA_PIN;       //��PA5������˿�

    return EX_Dat;
}

uint32_t EX_Input_Read_B()  //��ȡ�ⲿGPIOB�˿�
{
    uint32_t EX_Dat;

    EX_Dat = R32_PB_PIN;    //��ȡ GPIOB ����˿�

    return EX_Dat;
}

void ADC_Init()
{
    uint8_t i;
    uint16_t abcBuff[40];
    /* �¶Ȳ�������� */
    PRINT("\n1.Temperature sampling...\n");
    ADC_InterTSSampInit();
    for(i = 0; i < 20; i++)
    {
        abcBuff[i] = ADC_ExcutSingleConver(); // ��������20��
    }
    for(i = 0; i < 20; i++)
    {
        PRINT("%d \n", adc_to_temperature_celsius(abcBuff[i]));
    }
}

#define ADC_Buff_Len    5

int ADC_Buff[ADC_Buff_Len];

void ADC_CH4_Run()
{
    uint8_t      i;
    signed short RoughCalib_Value = 0; // ADC�ֵ�ƫ��ֵ


    /* ��ͨ��������ѡ��adcͨ��4����������Ӧ PA14���ţ� ������У׼���� */
    PRINT("\n2.Single channel sampling...\n");
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);  //���ò���Ƶ�ʺ�����

    RoughCalib_Value = ADC_DataCalib_Rough(); // ���ڼ���ADC�ڲ�ƫ���¼��ȫ�ֱ��� RoughCalib_Value��
    PRINT("RoughCalib_Value =%d \n", RoughCalib_Value);

    ADC_ChannelCfg(4);      //ѡ��ͨ��4
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        ADC_Buff[i] = ADC_ExcutSingleConver() + RoughCalib_Value; // ��������20��
    }
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        PRINT("%d \n", ADC_Buff[i]); // ע�⣺����ADC�ڲ�ƫ��Ĵ��ڣ���������ѹ����ѡ���淶Χ���޸�����ʱ�򣬿��ܻ�����������������
    }

}

/********************************************************************
 *
 * ADC_Test_Light_Run()
 *
 *ADC ������ǿ��
 *
 ********************************************************************/



uint8_t Light_State =Light_Night_State;            //��ҹ״̬     ��Ĭ�ϴ��ں�ҹģʽ��


void ADC_Test_Light_Run()
{
    uint8_t      i;
    long ADC_Average;      //����ADCƽ��ֵ

    signed short RoughCalib_Value = 0; // ADC�ֵ�ƫ��ֵ


    /* ��ͨ��������ѡ��adcͨ��4����������Ӧ PA14���ţ� ������У׼���� */
    PRINT("\n2.Single channel sampling...\n");
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);  //���ò���Ƶ�ʺ�����

    RoughCalib_Value = ADC_DataCalib_Rough(); // ���ڼ���ADC�ڲ�ƫ���¼��ȫ�ֱ��� RoughCalib_Value��
    PRINT("RoughCalib_Value =%d \n", RoughCalib_Value);

    ADC_ChannelCfg(4);      //ѡ��ͨ��4

    for(i = 0; i < ADC_Buff_Len; i++)
    {
        ADC_Buff[i] = ADC_ExcutSingleConver() + RoughCalib_Value; // ��������ADC_Buff_Len��

        if(ADC_Buff[i]<0)           //��<0����������
            ADC_Buff[i] =0;
    }

    R8_ADC_CFG =0;          //�ر�ADC��Դ
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        PRINT("%d \n", ADC_Buff[i]); // ע�⣺����ADC�ڲ�ƫ��Ĵ��ڣ���������ѹ����ѡ���淶Χ���޸�����ʱ�򣬿��ܻ�����������������
    }

    ADC_Average =0;

    for(i =0;i<ADC_Buff_Len;i++)
    {
        ADC_Average+=ADC_Buff[i];
    }

    ADC_Average/=ADC_Buff_Len;

    PRINT("\r\n\r\nADC_Average = %d.\r\n\r\n",ADC_Average);    //���ADC���

//    if(Light_State==Light_Night_State)          //���ں�ҹ״̬ʱ
//    {
        if(ADC_Average<Light_Day_Dat)
        {
            Light_State=Light_Day_State;      //ADֵ���ڴ���ֵ�л�������ģʽ
            GPIOA_SetBits(GPIO_Pin_15); // ���� PA15Ϊ���� (����ر����͵�)

//            Light_State =Light_Night_State;     //ADֵС�ڴ���ֵ�л�����ҹģʽ
//            GPIOA_ResetBits(GPIO_Pin_15); // ���� PA15Ϊ���� (��ҹ�������͵�)

            PRINT("Light_State = Light_Day_State.!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
        }
 //   }
    else        //���ڰ���״̬ʱ
//    {
        if(ADC_Average>Light_Night_Dat)
        {
            Light_State =Light_Night_State;     //ADֵС�ڴ���ֵ�л�����ҹģʽ
            GPIOA_ResetBits(GPIO_Pin_15); // ���� PA15Ϊ���� (��ҹ�������͵�)

            PRINT("Light_State = Light_Night_State.???????????????????????????\r\n");

        }

//    }

}



#define Flash_Buf_Len   100
uint8_t FlashBuf[Flash_Buf_Len];




/******************************************************************************
 *
 *  void Data_Flash_Read()
 *  @ ��ȡData��Flash���� ʹ�� 0���� 0ҳ �� FlashBuf
 *
 ******************************************************************************/

void Data_Flash_Read()
{
    uint32_t i;
    EEPROM_READ(0, FlashBuf, Flash_Buf_Len);

    for(i = 0; i < Flash_Buf_Len; i++)
    {
        PRINT("%02x ", FlashBuf[i]);
    }
    PRINT("\n");

}

/****************************************************************************
 *
 * void Data_Flash_Eraes()
 * @ ����Data��Flash��0����
 *
 ****************************************************************************/

void Data_Flash_Eraes()
{
    uint8_t s;

    s = EEPROM_ERASE(0, EEPROM_BLOCK_SIZE);
    PRINT("EEPROM_ERASE=%02x\n", s);

}

/***************************************************************************
 *
 * void Data_Flash_Write()
 * @��FlashBuf ����ֵд�� Data Flash��0����0ҳ
 *
 **************************************************************************/

void Data_Flash_Write()
{
    uint8_t s;

    s = EEPROM_WRITE(0, FlashBuf, Flash_Buf_Len);

    PRINT("EEPROM_WRITE=%02x\n", s);

}

/***********************************************************************
 *
 *void Get_CHIP_UNIQUE_ID()
 *
 * @��ȡоƬID
 *
 **********************************************************************/
uint8_t CHIP_UNIQUE_ID[8];

void Get_CHIP_UNIQUE_ID()
{
    uint8_t i;
    GET_UNIQUE_ID(CHIP_UNIQUE_ID);

    PRINT("\r\n\r\nCHIP_QUIQUE_ID:\r\n");

    for(i = 0; i < 8; i++)
    {
        PRINT("%02x ", CHIP_UNIQUE_ID[i]);
    }
    PRINT("\r\n\r\n");
}

/*********************************************************************
 *
 * CHIP_UNIQUE_to_CH()
 *
 * @��оƬIDת����Ƶ��
 *
 *******************************************************************/

uint8_t CHIP_UNIQUE_to_CH()
{
    Get_CHIP_UNIQUE_ID();       //�Ȼ�ȡID��Ȼ��õ���Ӧ�ŵ���
    uint32_t CH_Dat;
    uint32_t CHIP_ID_ACC;

//    CH_Dat[0] = CHIP_UNIQUE_ID[0]%38;
//    CH_Dat[1] = CHIP_UNIQUE_ID[1]%38;
//    CH_Dat[2] = CHIP_UNIQUE_ID[2]%38;
//    CH_Dat[3] = CHIP_UNIQUE_ID[3]%38;
//    CH_Dat[4] = CHIP_UNIQUE_ID[4]%38;
//    CH_Dat[5] = CHIP_UNIQUE_ID[5]%38;
//    CH_Dat[6] = CHIP_UNIQUE_ID[6]%38;
//    CH_Dat[7] = CHIP_UNIQUE_ID[7]%38;

    CHIP_ID_ACC = CHIP_UNIQUE_ID[0];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[1];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[2];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[3];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[4];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[5];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[6];
    CHIP_ID_ACC += CHIP_UNIQUE_ID[7];

    CH_Dat = CHIP_ID_ACC%38;    //ʹ��ID�ŵĺ�38������������Ƶ����

    PRINT("CH_Dat:%d.\r\n",CH_Dat);

    return CH_Dat;

}


uint8_t Flash_Save_Slave_Host_ID[10];      // Flash ����� ����ID ����ͨѶƵ��  ���ӻ�ģʽ�����ã�

/******************************************************************************
 *
 *@ Flash ��������
 *@ ������ID�洢��Flash��
 *@ ���ݸ�ʽ�� 8�ֽ�Host ID + 1�ֽ��ŵ� + ����
 *
 ******************************************************************************/

void Flash_Host_ID_Run(uint8_t *Dat)
{
    uint8_t Slave_Host_ID[10];
    uint8_t i;
    uint8_t s;

    for(i =0;i<10;i++)
        Slave_Host_ID[i] =0;     //���ID

    for(i =0;i<10;i++)
    {

        Slave_Host_ID[i] = *Dat;
        Dat++;
    }

    s = EEPROM_ERASE(0, EEPROM_BLOCK_SIZE);             //�Ȳ���Data Flash 0����
    PRINT("EEPROM_ERASE=%02x\n", s);

    s = EEPROM_WRITE(0, Slave_Host_ID,10);       //�ٽ�����д�� Data Flash 0����
    PRINT("EEPROM_WRITE=%02x\n", s);


    EEPROM_READ(0, Flash_Save_Slave_Host_ID,10);        //��ȡ Data Flash ����0 �� Flash_Save_Slave_Host_ID

    PRINT("\r\nFlash_Save_Slave_Host_ID:\r\n");
    for(i = 0; i < 10; i++)         //�����ȡ���� ID
    {

        PRINT("%02x ", Flash_Save_Slave_Host_ID[i]);

    }

    PRINT("\n");

}

/*************************************************************************************************
 *
 * @void Read_Flash_Host_ID_Run()
 * @��Flash�б���� Host ID �ŵ�Flash_Save_Slave_Host_ID��
 *
 *************************************************************************************************/

void Read_Flash_Host_ID_Run()
{

    uint8_t i;
    EEPROM_READ(0, Flash_Save_Slave_Host_ID,10);        //��ȡ Data Flash ����0 �� Flash_Save_Slave_Host_ID

    PRINT("\r\nFlash_Save_Slave_Host_ID:\r\n");
    for(i = 0; i < 10; i++)         //�����ȡ���� ID
    {

        PRINT("%02x ", Flash_Save_Slave_Host_ID[i]);

    }

    PRINT("\n");

    if(Flash_Save_Slave_Host_ID[9]==1)      //�ж��Ƿ�󶨹�
    {
        //�󶨹�
        PRINT("Slave_Mode_Host_ID_IS_Valid.\r\n");

    }
    else
    {
        //δ�󶨹�
        PRINT("Slave_Mode_Host_ID_IS_Error!.\r\n");

    }

}



/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 *********************************************************************/

uint8_t Host_CH =0;  //����ͨ����


int main(void)
{

    #if(defined(DCDC_ENABLE)) && (DCDC_ENABLE == TRUE)
        PWR_DCDCCfg(ENABLE);
    #endif
        SetSysClock(CLK_SOURCE_PLL_60MHz);
    #if(defined(HAL_SLEEP)) && (HAL_SLEEP == TRUE)
        GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
        GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PU);
    #endif
    #ifdef DEBUG
        GPIOA_SetBits(bTXD1);
        GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
        UART1_DefInit();
    #endif
    //    Time1_PWM_Init();
        Time1_PWM_Close();          // ����PWMʵ�ֿ��ص�
        PRINT("start.\n");
        PRINT("%s\n", VER_LIB);
    //    ADC_Init();
    //    while(1)
    //    ADC_CH4_Run();

        Get_CHIP_UNIQUE_ID();       //��ȡid��
        Host_CH = CHIP_UNIQUE_to_CH();     //��ȡ����Ƶ��
        Read_Flash_Host_ID_Run();       //��ȡ���صİ�����


        GPIO_Init();
        CH57X_BLEInit();
        HAL_Init();
        RF_RoleInit();
        RF_Init();
      //  CH_Jump();          //���Ԥ��Ƶ��

        LED_PWM_Run_TomsID =TMOS_ProcessEventRegister(LED_PWM_Run);         //ע�� LED�����¼�
        LED_Close_Later_TomsID = TMOS_ProcessEventRegister(LED_Close_Later_Run);    //ע�� �صƺ����¼�
        LED_OP_CL_PWM_Run_TomsID = TMOS_ProcessEventRegister(LED_OP_CL_PWM_Run);    //ע�Ὺ�صƴ����¼�

       // tmos_set_event( LED_PWM_Run_TomsID , OP_LED );

        // Flash Test

//        FlashBuf[0] = 0X53;
//        FlashBuf[1] = 0X56;
//        FlashBuf[2] = 0X57;
//        FlashBuf[3] = 0X58;
//        FlashBuf[4] = 0X59;
//
//        Data_Flash_Eraes();
//        Data_Flash_Read();
//
//        FlashBuf[0] = 0X53;
//        FlashBuf[1] = 0X56;
//        FlashBuf[2] = 0X57;
//        FlashBuf[3] = 0X58;
//        FlashBuf[4] = 0X59;
//
//        Data_Flash_Write();
//
//        Data_Flash_Read();


        Main_Circulation();

}

/******************************** endfile @ main ******************************/
