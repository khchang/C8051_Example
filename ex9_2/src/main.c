#include "c8051f340.h"
#include "main.h"
#include <stdio.h>

void main(void)
{
	float Temp=0;
	
	Init_Device();
	
	TH0 = (65536-50000)/256;	// Set Timer0 TH0
	TL0 = (65536-50000)%256;	// Set Timer0 TL0
	// 50 ms
	TF0 = 0;					// Clear Overflag
	TR0 = 1;					// Start Timer0
	
	TR1 = 1;					// Enable Timer1 to generate baud rate.
	TI0 = 1;					// Use printf function for UART
	
	EA = 1;

	
	while(1)
	{
		
		if((ADC0_Flag&ADC0_Value_Update)==ADC0_Value_Update)
		{
			Temp = ((ADC0_Analog_Value*1000)-764)/2.87;
			printf("ADC0 Digital Value is %u\n\r",ADC0_Digital_Value);
			printf("ADC0 Analog Value is %2.4f\n\r\n\r",ADC0_Analog_Value);
			printf("Temperature is %3.4f\n\r\n\r", Temp);
			ADC0_Flag &= ~ADC0_Value_Update;
		}
	}
}


void Timer0_Interrupt(void) interrupt INTERRUPT_TIMER0
{	// 50 ms
	static unsigned char Interrupt_Counter=0;
	unsigned int j=0;

	TR0 = 0;
	TH0 = (65536-50000)/256;	// Set Timer0 TH0
	TL0 = (65536-50000)%256;	// Set Timer0 TL0
	TF0 = 0;					// Clear Overflag
	TR0 = 1;					// Start Timer0
	
	Interrupt_Counter++;
	
	if(Interrupt_Counter>=10)
	{
		while(AD0BUSY==1);						// Check Conversion Complete
		ADC0_Digital_Value = (ADC0H<<8)|ADC0L;
		ADC0_Analog_Value = (float)ADC0_Digital_Value*3.3/1024;
	
		ADC0_Flag |= ADC0_Value_Update;
		Interrupt_Counter=0;
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
    AMX0P     = 0x1E;
    AMX0N     = 0x1F;
    ADC0CN    = 0x81;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x0C;
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
    IE        = 0x82;
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
