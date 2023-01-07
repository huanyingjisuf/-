#ifndef _GPIODEF_H_
#define _GPIODEF_H_
enum
{
	HIGH_Z		= 0,					
	INPUT			= 1,          
	OUTPUT		= 2,          
                                             
	P31_ADC0_SETTING			= 3,
	P35_ADC1_SETTING			= 3,
	P32_ADC2_SETTING			= 3,
	P34_ADC3_SETTING			= 3,
	P01_ADC4_SETTING			= 3,
	P30_ADC5_SETTING			= 3,

	
	P31_TK0_SETTING			= 4,
	P32_TK1_SETTING			= 4,
	P34_TK2_SETTING			= 4,
	P01_TK3_SETTING			= 4,
	P30_TK4_SETTING			= 4,
	P35_CAP_SETTING			= 4,
                       
	P30_UART_TX_SETTING		= 5,      
	P31_UART_RX_SETTING		= 5,      
                         
	P30_I2C_SDA_SETTING			= 6,      
	P31_I2C_SCL_SETTING			= 6,      
 
	P16_I2C_SDA_SETTING			= 6,      
	P17_I2C_SCL_SETTING			= 6,     
                        
	P35_T0_SETTING				= 5,        
	P01_T1_SETTING				= 5,            
                        
	P32_RESET_SETTING			= 7,	

	P32_PWM0_SETTING			= 6,	
	P34_PWM1_SETTING			= 6,	
	P01_PWM2_SETTING			= 6,	
 
	PU_EN				= 0x80,
	PD_EN				= 0x40,
	OP_EN				= 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val


/******************************************************************************/

#endif
