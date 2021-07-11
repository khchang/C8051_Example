/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F380.h"
#include "main.h"
#include <stdio.h>

void main(void)
{

	unsigned char i;
	
	Init_Device();
	
	TR1 = 1;			// Enable Timer1 to generate baud rate.
	TI0 = 1;			// Use printf function for UART
	
	printf("Please enter any string and press 'enter'.\n");
	
	EA =1;				// Enable all interrupt

	Timer0_Delay1ms(100);
	
	while(1)
	{

		if ((UART_Flag&Received_String)==Received_String)
		{
			printf("\n");
			printf("You just enter the string is: %s\n", Receive_String);
		
			for(i=0;i<sizeof(Receive_String);i++)
				Receive_String[i]=0x00;

			Receive_String_Index = 0;
			
			UART_Flag &= ~Received_String;
		}
	}
	
}

void UART_Interrupt(void) interrupt INTERRUPT_UART0
{

	if (RI0==1)
	{
		Receive_String[Receive_String_Index] = SBUF0;
		Receive_String_Index++;
		
		if (SBUF0=='\r')
		{
			UART_Flag |= Received_String;
		}
		
		RI0=0;
	}
}

void Timer0_Delay1ms(unsigned int i)
{
	unsigned int j=0;

	for(j=0;j<i;j++)
	{
		TH0 = (65536-1000)/256;		// Set Timer0 TH0
		TL0 = (65536-1000)%256;		// Set Timer0 TL0
		TF0 = 0;			// Clear Overflag
		TR0 = 1;			// Start Timer0
		while(TF0==0);			// Check Overflag
		TR0 = 0;			// Stop Timer0
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
    // P0.0  -  Skipped,     Open-Drain, Digital
    // P0.1  -  Skipped,     Open-Drain, Digital
    // P0.2  -  Skipped,     Open-Drain, Digital
    // P0.3  -  Skipped,     Open-Drain, Digital
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

    P0SKIP    = 0x0F;
    XBR0      = 0x01;
    XBR1      = 0x40;
}

void Oscillator_Init()
{
    OSCICN    = 0xC3;
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
