#include "C8051F340.h"
#include "main.h"

void main(void)
{
	unsigned char i=0;
	char Hello_World[] = "Hello World, NFU!\n\r";
	
	Init_Device();
	
	TR1 = 1;	// Enable Timer1 to generate baud rate.

	
	while(1)
	{
		for(i=0;i<sizeof(Hello_World);i++)
		{
			SBUF0 = Hello_World[i];
			// TI0 == 1, 當傳送完成。
			while(TI0==0);
			
			TI0 = 0;
		}
		
		Timer0_Delay1ms(1000);
	}
	
}

void Timer0_Delay1ms(unsigned int i)
{
	unsigned int j=0;

	for(j=0;j<i;j++)
	{
		TH0 = (65536-1000)/256;		// Set Timer0 TH0
		TL0 = (65536-1000)%256;		// Set Timer0 TL0
		TF0 = 0;					// Clear Overflag
		TR0 = 1;					// Start Timer0
		while(TF0==0);				// Check Overflag
		TR0 = 0;					// Stop Timer0
	}
}

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void PCA_Init()
{
    PCA0MD    &= ~0x40;
    PCA0MD    = 0x00;
}

void Timer_Init()
{
    TMOD      = 0x21;
    CKCON     = 0x08;
    TH1       = 0xCC;
}

void UART_Init()
{
    SCON0     = 0x10;
}

void Port_IO_Init()
{
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Unassigned,  Open-Drain, Digital
    // P0.2  -  Unassigned,  Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  TX0 (UART0), Open-Drain, Digital
    // P0.5  -  RX0 (UART0), Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital

    XBR0      = 0x01;
    XBR1      = 0x40;
}

void Oscillator_Init()
{
    OSCICN    = 0x83;
}

void Interrupts_Init()
{
    IE        = 0x10;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    PCA_Init();
    Timer_Init();
    UART_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
