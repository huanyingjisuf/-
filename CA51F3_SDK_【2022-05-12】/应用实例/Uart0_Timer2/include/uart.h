
#define UART0_TX_BUF_SIZE		20
#define UART0_RX_BUF_SIZE		100

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;


#ifdef _UART_C_
	T_Buf_Info xdata	uart0_send;
	T_Buf_Info xdata	uart0_rev;
	unsigned char xdata uart0_tx_buf[UART0_TX_BUF_SIZE];
	unsigned char xdata uart0_rx_buf[UART0_RX_BUF_SIZE];
	bit uart0_tx_flag;
#else
	extern T_Buf_Info xdata	uart0_send;
	extern T_Buf_Info xdata	uart0_rev;
	extern unsigned char xdata uart0_tx_buf[UART0_TX_BUF_SIZE];
	extern unsigned char xdata uart0_rx_buf[UART0_RX_BUF_SIZE];
	extern bit uart0_tx_flag;	
#endif


void Uart0_PutChar(unsigned char bdat);
void Uart0_Initial_Timer2(unsigned long int baudrate);

void uart_printf(char *fmt,...);
