
#define UART1_TX_BUF_SIZE		20
#define UART1_RX_BUF_SIZE		100

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;


#ifdef _UART_C_
	T_Buf_Info xdata	uart1_send;
	T_Buf_Info xdata	uart1_rev;
	unsigned char xdata uart1_tx_buf[UART1_TX_BUF_SIZE];
	unsigned char xdata uart1_rx_buf[UART1_RX_BUF_SIZE];
	bit uart1_tx_flag;
#else
	extern T_Buf_Info xdata	uart1_send;
	extern T_Buf_Info xdata	uart1_rev;
	extern unsigned char xdata uart1_tx_buf[UART1_TX_BUF_SIZE];
	extern unsigned char xdata uart1_rx_buf[UART1_RX_BUF_SIZE];
	extern bit uart1_tx_flag;	
#endif



void Uart1_PutChar(unsigned char bdat);
void Uart1_Initial(unsigned long int baudrate);



void uart_printf(char *fmt,...);
