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

uint8_t LED_OP_Light_2_1 =0;            //二分之一亮度标志位

#define PWM_Dat_ADJ_Div 45          // PWM ADJ 调整 分度值

#define PWM_Dat_ADJ_Time    30      // PWM ADJ 调整时间间隔

uint16_t LED_OP_CL_PWM_Run(tmosTaskID task_id, tmosEvents events)
{


    if(events&LED_OP_Run)
    {
        if((LED_OP_PWM_Dat_In<LED_OP_PWM_Dat)&&(LED_OP==1)&&(LED_OP_Light_2_1==0))
        {
            LED_OP_PWM_Dat_In+=PWM_Dat_ADJ_Div;

            if(LED_OP_PWM_Dat>LED_OP_PWM_Dat)
                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,PWM_Dat_ADJ_Time);        //开启下一个扫描周期


        }
        else if(LED_OP_Run==1)
        {
            LED_OP_PWM_Dat_In = LED_OP_PWM_Dat;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();
            tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,50);        //开灯后开启PIR


        }

        PRINT("LED_OP_PWM_Dat_In:%d.\r\n",LED_OP_PWM_Dat_In);

        return events^LED_OP_Run;
    }



    if(events&LED_Close_Run)
    {
        if((LED_OP_PWM_Dat_In>1)&&(LED_OP==0))
        {

            if(LED_OP_PWM_Dat_In>PWM_Dat_ADJ_Div)
                LED_OP_PWM_Dat_In-=PWM_Dat_ADJ_Div;
            else {
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
        }


        return events^LED_Close_Run;
    }


    if(events&LED_OP_1_2_Run)                       //将亮度调节到原有1/2
    {

        PRINT("\r\nLED_OP_1_2_Run.\r\n");

        if((LED_OP_PWM_Dat_In<(LED_OP_PWM_Dat/3))&&(LED_OP==1)&&(LED_OP_Light_2_1==1))     //低于 1/2时上升
        {
            LED_OP_PWM_Dat_In+=PWM_Dat_ADJ_Div;

            if(LED_OP_PWM_Dat>(LED_OP_PWM_Dat/3))
                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/3;

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_1_2_Run,PWM_Dat_ADJ_Time);        //继续开启下次调整周期


        }
        else if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/3)&&(LED_OP==1)&&(LED_OP_Light_2_1==1))       //高于原有1/2 下降
        {

            if(LED_OP_PWM_Dat_In>(LED_OP_PWM_Dat/3+PWM_Dat_ADJ_Div))
                LED_OP_PWM_Dat_In-=PWM_Dat_ADJ_Div;
            else
            {

                LED_OP_PWM_Dat_In = LED_OP_PWM_Dat/3;           //如果剩余值< 原有设定1/2 直接赋值 原有1/2亮度

            }

            TMR1_Disable();
            TMR1_PWMActDataWidth(LED_OP_PWM_Dat_In); // 占空比 50%, 修改占空比必须暂时关闭定时器
            TMR1_Enable();

            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_1_2_Run,PWM_Dat_ADJ_Time);        //继续开启下次调整周期

        }
        else if((LED_OP==1)&&(LED_OP_Light_2_1==1))
        {
            tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,50);        //开灯后开启PIR

        }

        PRINT("LED_OP_PWM_Dat_In:%d.\r\n",LED_OP_PWM_Dat_In);

        return events^LED_OP_1_2_Run;
    }


    return 0;
}



uint8_t LED_OP =0;

void Time1_PWM_Init()
{

    if(LED_OP==0)       //判断灯是否打开
    {
        GPIOA_ResetBits(GPIO_Pin_10); // 配置PWM口 PA10
        GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA);

     //   GPIOA_SetBits(GPIO_Pin_10);         // 不使用上拉GPIO开灯

        //使用PWM驱动
        TMR1_PWMInit(High_Level, PWM_Times_1);

        TMR1_PWMCycleCfg(LED_OP_Dat_Max); // 周期 100us
        TMR1_Disable();
        TMR1_PWMActDataWidth(0); // 占空比 50%, 修改占空比必须暂时关闭定时器
        TMR1_Enable();
        LED_OP_PWM_Dat =LED_OP_Dat_Max;           //预设的开启亮度
        LED_OP_PWM_Dat_In =0;           //清空当前值

        EX_Dat =Ex_Input_Read();        //读取外部输入值

        PRINT("EXDAT:%X.\r\n",EX_Dat);

        if(EX_Dat&0x800)        //热释电有信号时
        {
            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,3);        //开始逐渐亮起过程

            PRINT("\r\nOP_LED_100%\r\n");
            tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out+3200);  //有热释电信号的情况下比延迟多两秒
            LED_OP_Light_2_1 =0;        //表示全亮度

        }
        else
        {
            tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_1_2_Run,3);        //开始逐渐亮起过程

            PRINT("\r\nOP_LED_50%\r\n");
            tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);
            LED_OP_Light_2_1 =1;        //表示二分之一亮度

        }
    }       //开灯时需要初始化
    else
    {
            EX_Dat =Ex_Input_Read();        //读取外部输入值
            PRINT("EXDAT:%X.\r\n",EX_Dat);

            //EX_Dat =0;      //测试50%

            if(EX_Dat&0x800)        //热释电有信号时
            {
                tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_Run,3);        //开始逐渐亮起过程

                PRINT("\r\nOP_LED_100%\r\n");
                tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out+3200);    ////有热释电信号的情况下比延迟多两秒
                LED_OP_Light_2_1 =0;    //表示全亮度
            }
            else
            {
                tmos_start_task(LED_OP_CL_PWM_Run_TomsID,LED_OP_1_2_Run,3);        //开始逐渐亮起过程

                PRINT("\r\nOP_LED_50%\r\n");
                tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);
                LED_OP_Light_2_1 =1;        //表示二分之一亮度

            }

    }



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
//        if(LED_OP==0)
//        {


            Time1_PWM_Init();
            tmos_start_task(LED_Close_Later_TomsID,Later_Enabled_PIR,2200);        //开灯1500后开启PIR

//        }


        LED_OP =1;

       // tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);         //重置 关灯时间

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
        if(LED_OP==0)
        {
            GPIOA_SetBits(GPIO_Pin_15);         //关灯前先屏蔽PIR
     //       DelayMs(200);
            tmos_start_task(LED_Close_Later_TomsID,Later_OP_LED,320);        //开灯前200ms先失能PIR

        }
        else
        {
          //  Time1_PWM_Init();

            LED_OP =1;

            EX_Dat =Ex_Input_Read();        //读取外部输入值

            //tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);

            if(((LED_OP_Light_2_1==1)&&(EX_Dat&0x800))||((LED_OP_Light_2_1==0)&&(!(EX_Dat&0X800))))
            {
                GPIOA_SetBits(GPIO_Pin_15);         //关灯前先屏蔽PIR
         //       DelayMs(200);
                tmos_start_task(LED_Close_Later_TomsID,Later_OP_LED,320);        //开灯前200ms先失能PIR
            }
            else if(LED_OP_Light_2_1==1)
            {
                tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out);  //有热释电信号的情况下比延迟多两秒

            }
            else if(LED_OP_Light_2_1==0)
            {
                tmos_start_task(LED_PWM_Run_TomsID, Close_LED, Close_LED_Time_Out+3200);  //有热释电信号的情况下比延迟多两秒

            }



        }



        return events^OP_LED;
    }

    if(events&Close_LED)
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

    GPIOA_ModeCfg(GPIO_Pin_15, GPIO_ModeOut_PP_5mA);        //初始化热释电控制端
    GPIOA_ResetBits(GPIO_Pin_15); // 配置 PA15为下拉 (默认黑夜开启热释电)

}

uint32_t Ex_Input_Read()
{
    uint32_t EX_Dat;
    EX_Dat = R32_PA_PIN;       //在PA5口输入端口

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


/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 *********************************************************************/
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
    GPIO_Init();
    CH57X_BLEInit();
    HAL_Init();
    RF_RoleInit();
    RF_Init();

    LED_PWM_Run_TomsID =TMOS_ProcessEventRegister(LED_PWM_Run);         //注册 LED开关事件
    LED_Close_Later_TomsID = TMOS_ProcessEventRegister(LED_Close_Later_Run);    //注册 关灯后处理事件
    LED_OP_CL_PWM_Run_TomsID = TMOS_ProcessEventRegister(LED_OP_CL_PWM_Run);    //注册开关灯处理事件

   // tmos_set_event( LED_PWM_Run_TomsID , OP_LED );

    Main_Circulation();

}

/******************************** endfile @ main ******************************/
