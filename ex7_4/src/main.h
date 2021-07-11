#define		Received_String		0x01

unsigned char Receive_String_Index=0;
char Receive_String[40];

unsigned char UART_Flag=0x00;

void Timer0_Delay1ms(unsigned int);
void Init_Device(void);
