#include "C8051F340.h"
#include "main.h"

void main(void)
{
	unsigned char Frequency_Select = 0;
	
	Init_Device();
	
	TL0 = 256-100;
	TH0 = 256-100; //100us = 0.1ms = 0.0001sec
	TR0 = 1;
	
	P0 |= 0xf0;		// Set P0.4 ~ P0.7 are input mode.
	
	while(1)
	{
		Frequency_Select = P0 >> 4;
		
		switch(Frequency_Select)
		{
			case 0:
				TR0 = 0;				// Stop Timer0
				P3 = 0;
			break;
			case 1:						// 1 Hz
				Frequency_Interrupt_Value = 5000;
				TR0 = 1;
			break;
			case 2:						// 2 Hz
				Frequency_Interrupt_Value = 2500;
				TR0 = 1;
			break;
			case 3:						// 3 Hz
				Frequency_Interrupt_Value = 1667;
				TR0 = 1;
			break;
			case 4:						// 4 Hz
				Frequency_Interrupt_Value = 1250;
				TR0 = 1;
			break;
			case 5:						// 5 Hz
				Frequency_Interrupt_Value = 1000;
				TR0 = 1;
			break;
			case 6:						// 6 Hz
				Frequency_Interrupt_Value = 833;
				TR0 = 1;
			break;
			case 7:						// 7 Hz
				Frequency_Interrupt_Value = 714;
				TR0 = 1;
			break;
			case 8:						// 8 Hz
				Frequency_Interrupt_Value = 625;
				TR0 = 1;
			break;
			case 9:						// 9 Hz
				Frequency_Interrupt_Value = 556;
				TR0 = 1;
			break;
			case 10:					// 10 Hz
				Frequency_Interrupt_Value = 500;
				TR0 = 1;
			break;
			case 11:					// 11 Hz
				Frequency_Interrupt_Value = 455;
				TR0 = 1;
			break;
			case 12:					// 12 Hz
				Frequency_Interrupt_Value = 417;
				TR0 = 1;
			break;
			case 13:					// 13 Hz
				Frequency_Interrupt_Value = 385;
				TR0 = 1;
			break;
			case 14:					// 14 Hz
				Frequency_Interrupt_Value = 357;
				TR0 = 1;
			break;
			case 15:					// 15 Hz
				Frequency_Interrupt_Value = 333;
				TR0 = 1;
			break;
			default:
			break;
		}
	}
	
}

void Timer0_Interrupt(void) interrupt INTERRUPT_TIMER0
{	// 100us
	static unsigned int Interrupt_Counter=0;
	
	Interrupt_Counter++;
	
	if(Interrupt_Counter >= Frequency_Interrupt_Value)
	{
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
    TMOD      = 0x02;
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
    Timer_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}