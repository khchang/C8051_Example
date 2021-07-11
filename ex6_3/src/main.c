#include "c8051f340.h"
#include "main.h"

void main(void)
{
	Init_Device();
	
	P3 = 0x00;					// Clear P3
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (65536-50000) >> 8;	// Set Timer0 TH0
	TL0 = (65536-50000) & 0xff;	// Set Timer0 TL0
	// 50ms
	
	TR0 = 1;					// Start Timer0

	while(1)
	{

		// Coding here.
	}
}

void Timer0_INT(void) interrupt INTERRUPT_TIMER0
{
	static char Interrupt_Counter=0;

	TR0 = 0;					// Stop Timer0
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (65536-50000) >> 8;	// Set Timer0
	TL0 = (65536-50000) & 0xff;
	TR0 = 1;					// Start Timer0
	
	Interrupt_Counter++;

	if(Interrupt_Counter>=10)
	{	// 500 ms
		P3 = ~P3;
		Interrupt_Counter = 0;
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
    TMOD      = 0x01;
}

void Port_IO_Init()
{
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Unassigned,  Open-Drain, Digital
    // P0.2  -  Unassigned,  Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  Unassigned,  Open-Drain, Digital
    // P0.5  -  Unassigned,  Open-Drain, Digital
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

    XBR1      = 0x40;
}

void Oscillator_Init()
{
    OSCICN    = 0x83;
}

void Interrupts_Init()
{
    IE        = 0x82;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    PCA_Init();
    Timer_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
