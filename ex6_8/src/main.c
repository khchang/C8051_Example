#include "C8051F340.h"
#include "main.h"

void main(void)
{
	Init_Device();
	
	SPI_Init();
	
	while(1)
	{
		// Coding here.
	}
}

void INT0_Interrupt(void) interrupt INTERRUPT_INT0
{
	unsigned int i=0;
	unsigned char Counter_BCD=0;
	
	for(i=0;i<50000;i++);
	
	if ((P0&0x01)==0x00)	// P0.0
	{
		if (Counter<99)
		{
			Counter++;
		}
		
		Counter_BCD = ((Counter/10)<<4|(Counter%10));
		
		SPI_Write(Counter_BCD);
	}		
}

void INT1_Interrupt(void) interrupt INTERRUPT_INT1
{
	unsigned int i=0;
	unsigned char Counter_BCD=0;
	
	for(i=0;i<50000;i++);

	if ((P0&0x02)==0x00)	// P0.1
	{	
		if (Counter>0)
		{
			Counter--;
		}

		Counter_BCD = ((Counter/10)<<4|(Counter%10));
		
		SPI_Write(Counter_BCD);
	}
}

void SPI_Init(void)
{
	unsigned char i=0;
	
	P4 &= ~(SPI_nReset+SPI_Din+SPI_CLK);
	// 0x20+0x08+0x10 = 0x38 = 0b00111000

	for(i=0;i<100;i++);
	
	P4 |= SPI_nReset;
	
}

void SPI_Write(unsigned char SPI_Data)
{	// SPI_Data = 0x15 = 0b00010101
	// LSB first
	unsigned char i=0,j=0;
	
	for(i=0;i<8;i++)
	{
		if((SPI_Data&0x01)==0x01)
		{
			P4 |= SPI_Din;
			//SPI_Din = 1;
		}
		else
		{
			P4 &= ~SPI_Din;
			//SPI_Din = 0;
		}
		
		for(j=0; j<5; j++);
		
		P4 |= SPI_CLK;
		//SPI_CLK = 1;
		
		for(j=0; j<5; j++);
		
		P4 &= ~SPI_CLK;
		//SPI_CLK = 0;
		
		SPI_Data = SPI_Data>>1;
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
    TCON      = 0x05;
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

    P4MDOUT   = 0x38;
    XBR1      = 0x40;
}

void Oscillator_Init()
{
    OSCICN    = 0x83;
}

void Interrupts_Init()
{
    IT01CF    = 0x10;
    IE        = 0x85;
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
