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

uint32_t EX_Input_Read_B(void);  //读取外部GPIOB端口


extern uint8_t Host_CH;  //主机通道号

extern uint8_t Host_Slave_Mode;       //主机标志位  1 表示主机  2 表示从机

#define Host_Mode       1       //主机模式
#define Slave_Mode      2       //从机模式

extern uint32_t LED_OP_PWM_Dat_In ;          //用于判断PWM定时器是否仍然开启

extern uint8_t CHIP_UNIQUE_ID[];        //芯片ID缓存

extern uint8_t Flash_Save_Slave_Host_ID[];      // Flash 保存的 主机ID 及其通讯频段  （从机模式下引用）


extern uint8_t NetWork_Mode_Run;        //进入组网模式标志位


extern uint8_t Host_CH;  //主机通道号

extern uint8_t NetWork_Led_Now;     //组网模式下LED开关标志位（不与开关灯公用）

extern uint8_t NetWork_Host_Run_T_Dat;      //组网主机模式下计时


void Jump_to_NetWork_CH(void);          //跳转到组网专用频段

void NetWork_Host_Run(void);            //主机模式下组网

void Flash_Host_ID_Run(uint8_t *Dat);   //将主机ID存到Flash

void Read_Flash_Host_ID_Run(void);      //读取Flash 主机ID

void Data_Flash_Eraes(void);            //清除数据Flash数据


#endif
