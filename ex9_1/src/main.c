#include "c8051f340.h"
#include "main.h"
#include <stdio.h>

void main(void)
{
	unsigned int ADC0_Digital_Value;
	float ADC0_Analog_Value;
	
	Init_Device();
	TR1 = 1;					// Enable Timer1 to generate baud rate.
	TI0 = 1;					// Use printf function for UART
	
	while(1)
	{
		AD0BUSY = 1;			// Start Conversion
		while(AD0BUSY==1);		// Check Conversion Complete
		ADC0_Digital_Value = (ADC0H<<8)|ADC0L;
		ADC0_Analog_Value = (float)ADC0_Digital_Value*(3.3/1024);
		printf("ADC0 Digital Value is %u\n\r",ADC0_Digital_Value);
		printf("ADC0 Analog Value is %6.4fV\n\r\n\r",ADC0_Analog_Value);
		Timer0_Delay1ms(500);
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

void ADC_Init()
{
    AMX0P     = 0x04;
    AMX0N     = 0x1F;
    ADC0CN    = 0x80;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x08;
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
    // P2.5  -  Unassigned,  Open-Drain, Analog
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

    P2MDIN    = 0xDF;
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
    ADC_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
