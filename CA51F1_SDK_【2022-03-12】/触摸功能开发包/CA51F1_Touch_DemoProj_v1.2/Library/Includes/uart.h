#ifndef _UART_H_
#define _UART_H_
/*********************************************************************************************************************/
#define UART_TX_BUF_SIZE		10
#define UART_RX_BUF_SIZE		10

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;


#ifdef _UART_C_
#ifdef UART_EN
	T_Buf_Info idata	uart_send;
	T_Buf_Info idata	uart_rev;
	unsigned char idata uart_tx_buf[UART_TX_BUF_SIZE];
	unsigned char idata uart_rx_buf[UART_RX_BUF_SIZE];
	bit uart_tx_flag;
#endif
#else
#ifdef UART_EN
	extern T_Buf_Info idata	uart_send;
	extern T_Buf_Info idata	uart_rev;
	extern unsigned char idata uart_tx_buf[UART_TX_BUF_SIZE];
	extern unsigned char idata uart_rx_buf[UART_RX_BUF_SIZE];
	extern bit uart_tx_flag;	
#endif

#endif
#ifndef UART_EN
	#define Uart_PutChar(n)
#endif

#ifdef UART_EN
void Uart_PutChar(unsigned char bdat);
void Uart_Initial(unsigned long int baudrate);
#endif	

/*********************************************************************************************************************/
#endif