#ifndef PWM_MAIN_H
#define PWM_MAIN_H

#define NetWork_Mode    1           //表示使能组网模式

#ifndef NetWork_Mode

#define RF_LED_Mode     1           //未使能组网模式，则使能普通模式

#endif



#define OP_LED  1
#define Close_LED 2

#define Close_LED_Time_Out 16000

#define Light_Day_Dat       3200         //定义白天触发值

#define Light_Night_Dat     3300         //定义夜间触发值

#define Light_Night_State   1       //黑夜状态值

#define Light_Day_State   2       //白天状态值


//@uint16_t LED_Close_Later_Run(tmosTaskID task_id, tmosEvents events)

#define Later_Test_Light    1           //在关灯后更新亮度环境  (事件值遵循8421)

#define Later_Disabled_PIR  2           //在关灯后屏蔽PIR

#define Later_Enabled_PIR   4           //在关灯后开启PIR

#define Later_OP_LED        8           //开灯前关闭PIR

#define Later_Close_LED     0X10        //关灯前关闭PIR



#define LED_OP_Dat_Max              3000        //led最大开启亮度

#define LED_OP_Run            1           //运行开启LED

#define LED_Close_Run          2           //运行开启LED

#define LED_OP_1_2_Run          4           //切换到1/2亮度


void ADC_Test_Light_Run(void);      //ADC检测光线强度

extern uint8_t Light_State;            //昼夜状态

uint16_t LED_PWM_Run(tmosTaskID task_id, tmosEvents events);
extern uint8_t  LED_PWM_Run_TomsID;
extern uint8_t LED_OP;

void Time1_PWM_Init(void);

uint32_t Ex_Input_Read(void);

extern uint32_t EX_Dat;        //外部输入值 （PA5输入）


extern uint32_t LED_OP_PWM_Dat_In ;          //用于判断PWM定时器是否仍然开启

#endif
