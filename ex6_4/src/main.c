#include "C8051F340.h"
#include "main.h"

void main(void)
{
	Init_Device();
	P3 = 0x01;					// Clear P3
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (8192-5000)/32;		// Set Timer0
	TL0 = (8192-5000)%32;
	TR0 = 1;					// Start Timer0

	while(1)
	{
		// Coding here.
	}
}

void Timer0_Interrupt(void) interrupt INTERRUPT_TIMER0
{	// 5000 clocks = 5000 us = 5ms
	static unsigned char Interrupt_Counter=0;
	static unsigned char Led=0x01;
	static unsigned char direction=0;

	TR0 = 0;					// Stop Timer0
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (8192-5000)/32;				// Set Timer0
	TL0 = (8192-5000)%32;
	TR0 = 1;					// Start Timer0
	
	Interrupt_Counter++;

	if(Interrupt_Counter>=20)
	{	// 0.1 sec
		if (direction==0)
		{
			Led = Led<<1;
		}
		else
		{
			Led = Led>>1;
		}
		
		if (Led==0x01)
		{
			direction=0;
		}
		else
		{
			if (Led==0x80)
			{
				direction=1;
			}
		}
		
		P3 = Led;
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
    OSCICN    = 0xC3;
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
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
