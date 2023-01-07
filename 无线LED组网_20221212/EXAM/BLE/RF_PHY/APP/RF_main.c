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
 * @brief   主循环
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


uint32_t LED_OP_PWM_Dat =0;         //预设的LED_开启PWM值

uint32_t LED_OP_PWM_Dat_In =0;      //当前的LED开启值

#define PWM_Dat_ADJ_Div 15          // PWM ADJ 调整 分度值

#define PWM_Dat_ADJ_Time    10      // PWM ADJ 调整时间间隔

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
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //开灯1000ms后开启PIR


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
        else if(LED_OP==0)          //数值清零后 将定时器关闭
        {
            LED_OP_PWM_Dat_In =0;

            TMR1_Disable();                 //停止PWM输出

            GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
            GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);
            PRINT("LED_Close_OK!.\r\n");
        }


        return events^LED_Close_Run;
    }


    if(events&LED_OP_1_2_Run)                       //将亮度调节到原有1/2
    {
        if(LED_OP_PWM_Dat_In<(LED_OP_PWM_Dat/2))     //低于 1/2时上升
        {
            LED_OP_PWM_Dat_In+=PWM_Dat_ADJ_Div;

            if(LED_OP_PWM_Dat>(LED_OP_PWM_Dat/2))
                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/2;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //继续开启下次调整周期


        }
        else if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/2))       //高于原有1/2 下降
        {

            if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/2+PWM_Dat_ADJ_Div))
                LED_OP_PWM_Dat_In-=PWM_Dat_ADJ_Div;
            else
            {

                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/2;           //如果剩余值< 原有设定1/2 直接赋值 原有1/2亮度

            }

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //继续开启下次调整周期

        }

        return events^LED_OP_1_2_Run;
    }





    return 0;
}



uint8_t LED_OP =0;

void Time1_PWM_Init()
{

        GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);

     //   GPIOA_SetBits(GPIO_Pin_10);         // 不使用上拉GPIO开灯

        //使用PWM驱动
        TMR1_PWMInit(High_Level, PWM_Times_1);

        TMR1_PWMCycleCfg(3000); // 周期 100us
        TMR1_Disable();
        TMR1_PWMActDataWidth(0); // 占空比 50%, 修改占空比必须暂时关闭定时器
        TMR1_Enable();
        LED_OP_PWM_Dat =3000;           //预设的开启亮度
        LED_OP_PWM_Dat_In =0;           //清空当前值

        tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,3);        //开始逐渐亮起过程

}

void Time1_PWM_Close()
{
//    TMR1_Disable();                 //停止PWM输出
//
//    GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
//    GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeIN_PD);

    //Time3_PWM_Init();

    if(LED_OP_PWM_Dat_In>0)
        tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_Close_Run,3);        //开始逐渐熄灭过程
    else {
        TMR1_Disable();                 //停止PWM输出

        GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
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

    if(events&Later_Disabled_PIR)       //关灯后关闭PIR
    {
        GPIOA_SetBits(GPIO_Pin_15);

        PRINT("\r\nLater_Disabled_PIR.\r\n");

        return events^Later_Disabled_PIR;
    }

    if(events&Later_Enabled_PIR)
    {
        //if(Light_State==Light_Night_State)          //在黑夜状态下再次开启PIR
                GPIOA_ResetBits(GPIO_Pin_15);

         PRINT("\r\nLater_Enabled_PIR.\r\n");

        return events^Later_Enabled_PIR;
    }

    if(events&Later_OP_LED)                 //未亮灯时使能开灯
    {
        if(LED_OP==0)
        {
            Time1_PWM_Init();
            tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //开灯1000ms后开启PIR

        }
        LED_OP =1;

        tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);         //重置 关灯时间

        return events^Later_OP_LED;
    }

    if(events&Later_Close_LED)          //未灭灯时关灯
    {

        if(LED_OP==1)
        {
           Time1_PWM_Close();
           tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //关灯1000ms后开启PIR
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
 *输入： 无
 *输出：无
 *
 *定时器1，PWM输出
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
                GPIOA_SetBits(GPIO_Pin_15);         //关灯前先屏蔽PIR
         //       DelayMs(200);
                tmos_start_task(LED_Close_Later_TomsID,Later_OP_LED,320);        //开灯前200ms先失能PIR

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

        if(NetWork_Mode_Run==0)   //不在组网模式下时
        {
            if(LED_OP==1)           //当灯在开启状态时
            {
                GPIOA_SetBits(GPIO_Pin_15);         //关灯前先屏蔽PIR
             //   DelayMs(200);

                tmos_start_task(LED_Close_Later_TomsID,Later_Close_LED,320);        //开灯前200ms先失能PIR

           //     tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,1600);        //关灯100ms后开启PIR

         //       tmos_start_task(LED_Close_Later_TomsID,Later_Test_Light,500);     //关灯后200ms更新亮度状态


            }
            else
            {
              //  Time1_PWM_Close();
                LED_OP =0;
            }

        }


//       DelayMs(100);
//       ADC_Test_Light_Run();        //关灯后做一次亮度采样
       return events^Close_LED;
    }


    return 0;
}


void GPIO_Init()
{

    GPIOA_ModeCfg(GPIO_Pin_11, GPIO_ModeIN_PD);      //设置下拉输入 高电平触发
    GPIOA_ModeCfg(GPIO_Pin_12, GPIO_ModeIN_Floating);      //设置下拉输入 高电平触发
    GPIOA_ModeCfg(GPIO_Pin_13, GPIO_ModeIN_Floating);      //设置下拉输入 高电平触发
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);

    GPIOB_ModeCfg(GPIO_Pin_7,GPIO_ModeIN_PU);       //设置PB7为外部按键输入 用于进入匹配模式

    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeOut_PP_5mA);        //初始化热释电控制端
    GPIOA_ResetBits(GPIO_Pin_15); // 配置 PA15为下拉 (默认黑夜开启热释电)

}

uint32_t Ex_Input_Read()
{
    uint32_t EX_Dat;
    EX_Dat = R32_PA_PIN;       //在PA5口输入端口

    return EX_Dat;
}

uint32_t EX_Input_Read_B()  //读取外部GPIOB端口
{
    uint32_t EX_Dat;

    EX_Dat = R32_PB_PIN;    //读取 GPIOB 整组端口

    return EX_Dat;
}

void ADC_Init()
{
    uint8_t i;
    uint16_t abcBuff[40];
    /* 温度采样并输出 */
    PRINT("\n1.Temperature sampling...\n");
    ADC_InterTSSampInit();
    for(i = 0; i < 20; i++)
    {
        abcBuff[i] = ADC_ExcutSingleConver(); // 连续采样20次
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
    signed short RoughCalib_Value = 0; // ADC粗调偏差值


    /* 单通道采样：选择adc通道4做采样，对应 PA14引脚， 带数据校准功能 */
    PRINT("\n2.Single channel sampling...\n");
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);  //设置采样频率和增益

    RoughCalib_Value = ADC_DataCalib_Rough(); // 用于计算ADC内部偏差，记录到全局变量 RoughCalib_Value中
    PRINT("RoughCalib_Value =%d \n", RoughCalib_Value);

    ADC_ChannelCfg(4);      //选择通道4
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        ADC_Buff[i] = ADC_ExcutSingleConver() + RoughCalib_Value; // 连续采样20次
    }
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        PRINT("%d \n", ADC_Buff[i]); // 注意：由于ADC内部偏差的存在，当采样电压在所选增益范围极限附近的时候，可能会出现数据溢出的现象
    }

}

/********************************************************************
 *
 * ADC_Test_Light_Run()
 *
 *ADC 检测光线强度
 *
 ********************************************************************/



uint8_t Light_State =Light_Night_State;            //昼夜状态     （默认处于黑夜模式）


void ADC_Test_Light_Run()
{
    uint8_t      i;
    long ADC_Average;      //保存ADC平均值

    signed short RoughCalib_Value = 0; // ADC粗调偏差值


    /* 单通道采样：选择adc通道4做采样，对应 PA14引脚， 带数据校准功能 */
    PRINT("\n2.Single channel sampling...\n");
    GPIOA_ModeCfg(GPIO_Pin_14, GPIO_ModeIN_Floating);
    ADC_ExtSingleChSampInit(SampleFreq_3_2, ADC_PGA_0);  //设置采样频率和增益

    RoughCalib_Value = ADC_DataCalib_Rough(); // 用于计算ADC内部偏差，记录到全局变量 RoughCalib_Value中
    PRINT("RoughCalib_Value =%d \n", RoughCalib_Value);

    ADC_ChannelCfg(4);      //选择通道4

    for(i = 0; i < ADC_Buff_Len; i++)
    {
        ADC_Buff[i] = ADC_ExcutSingleConver() + RoughCalib_Value; // 连续采样ADC_Buff_Len次

        if(ADC_Buff[i]<0)           //对<0的数据清零
            ADC_Buff[i] =0;
    }

    R8_ADC_CFG =0;          //关闭ADC电源
    for(i = 0; i < ADC_Buff_Len; i++)
    {
        PRINT("%d \n", ADC_Buff[i]); // 注意：由于ADC内部偏差的存在，当采样电压在所选增益范围极限附近的时候，可能会出现数据溢出的现象
    }

    ADC_Average =0;

    for(i =0;i<ADC_Buff_Len;i++)
    {
        ADC_Average+=ADC_Buff[i];
    }

    ADC_Average/=ADC_Buff_Len;

    PRINT("\r\n\r\nADC_Average = %d.\r\n\r\n",ADC_Average);    //输出ADC结果

//    if(Light_State==Light_Night_State)          //处在黑夜状态时
//    {
        if(ADC_Average<Light_Day_Dat)
        {
            Light_State=Light_Day_State;      //AD值大于触发值切换到白天模式
            GPIOA_SetBits(GPIO_Pin_15); // 配置 PA15为上拉 (白天关闭热释电)

//            Light_State =Light_Night_State;     //AD值小于触发值切换到黑夜模式
//            GPIOA_ResetBits(GPIO_Pin_15); // 配置 PA15为下拉 (黑夜开启热释电)

            PRINT("Light_State = Light_Day_State.!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
        }
 //   }
    else        //处于白天状态时
//    {
        if(ADC_Average>Light_Night_Dat)
        {
            Light_State =Light_Night_State;     //AD值小于触发值切换到黑夜模式
            GPIOA_ResetBits(GPIO_Pin_15); // 配置 PA15为下拉 (黑夜开启热释电)

            PRINT("Light_State = Light_Night_State.???????????????????????????\r\n");

        }

//    }

}



#define Flash_Buf_Len   100
uint8_t FlashBuf[Flash_Buf_Len];




/******************************************************************************
 *
 *  void Data_Flash_Read()
 *  @ 读取Data区Flash数据 使用 0扇区 0页 到 FlashBuf
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
 * @ 擦除Data区Flash的0扇区
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
 * @将FlashBuf 的数值写入 Data Flash的0扇区0页
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
 * @获取芯片ID
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
 * @将芯片ID转换成频道
 *
 *******************************************************************/

uint8_t CHIP_UNIQUE_to_CH()
{
    Get_CHIP_UNIQUE_ID();       //先获取ID，然后得到对应信道号
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

    CH_Dat = CHIP_ID_ACC%38;    //使用ID号的和38的余数来计算频道号

    PRINT("CH_Dat:%d.\r\n",CH_Dat);

    return CH_Dat;

}


uint8_t Flash_Save_Slave_Host_ID[10];      // Flash 保存的 主机ID 及其通讯频段  （从机模式下引用）

/******************************************************************************
 *
 *@ Flash 操作函数
 *@ 将主机ID存储到Flash中
 *@ 数据格式： 8字节Host ID + 1字节信道 + 保留
 *
 ******************************************************************************/

void Flash_Host_ID_Run(uint8_t *Dat)
{
    uint8_t Slave_Host_ID[10];
    uint8_t i;
    uint8_t s;

    for(i =0;i<10;i++)
        Slave_Host_ID[i] =0;     //清空ID

    for(i =0;i<10;i++)
    {

        Slave_Host_ID[i] = *Dat;
        Dat++;
    }

    s = EEPROM_ERASE(0, EEPROM_BLOCK_SIZE);             //先擦除Data Flash 0扇区
    PRINT("EEPROM_ERASE=%02x\n", s);

    s = EEPROM_WRITE(0, Slave_Host_ID,10);       //再将数据写入 Data Flash 0扇区
    PRINT("EEPROM_WRITE=%02x\n", s);


    EEPROM_READ(0, Flash_Save_Slave_Host_ID,10);        //读取 Data Flash 扇区0 到 Flash_Save_Slave_Host_ID

    PRINT("\r\nFlash_Save_Slave_Host_ID:\r\n");
    for(i = 0; i < 10; i++)         //输出读取到的 ID
    {

        PRINT("%02x ", Flash_Save_Slave_Host_ID[i]);

    }

    PRINT("\n");

}

/*************************************************************************************************
 *
 * @void Read_Flash_Host_ID_Run()
 * @将Flash中保存的 Host ID 放到Flash_Save_Slave_Host_ID中
 *
 *************************************************************************************************/

void Read_Flash_Host_ID_Run()
{

    uint8_t i;
    EEPROM_READ(0, Flash_Save_Slave_Host_ID,10);        //读取 Data Flash 扇区0 到 Flash_Save_Slave_Host_ID

    PRINT("\r\nFlash_Save_Slave_Host_ID:\r\n");
    for(i = 0; i < 10; i++)         //输出读取到的 ID
    {

        PRINT("%02x ", Flash_Save_Slave_Host_ID[i]);

    }

    PRINT("\n");

    if(Flash_Save_Slave_Host_ID[9]==1)      //判断是否绑定过
    {
        //绑定过
        PRINT("Slave_Mode_Host_ID_IS_Valid.\r\n");

    }
    else
    {
        //未绑定过
        PRINT("Slave_Mode_Host_ID_IS_Error!.\r\n");

    }

}



/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 *********************************************************************/

uint8_t Host_CH =0;  //主机通道号


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
        Time1_PWM_Close();          // 开关PWM实现开关灯
        PRINT("start.\n");
        PRINT("%s\n", VER_LIB);
    //    ADC_Init();
    //    while(1)
    //    ADC_CH4_Run();

        Get_CHIP_UNIQUE_ID();       //获取id号
        Host_CH = CHIP_UNIQUE_to_CH();     //获取主机频段
        Read_Flash_Host_ID_Run();       //读取本地的绑定数据


        GPIO_Init();
        CH57X_BLEInit();
        HAL_Init();
        RF_RoleInit();
        RF_Init();
      //  CH_Jump();          //检测预设频道

        LED_PWM_Run_TomsID =TMOS_ProcessEventRegister(LED_PWM_Run);         //注册 LED开关事件
        LED_Close_Later_TomsID = TMOS_ProcessEventRegister(LED_Close_Later_Run);    //注册 关灯后处理事件
        LED_OP_CL_PWM_Run_TomsID = TMOS_ProcessEventRegister(LED_OP_CL_PWM_Run);    //注册开关灯处理事件

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
