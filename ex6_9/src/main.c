#include "C8051F340.h"
#include "main.h"


void main(void)
{
	Init_Device();
	
	SPI_Init();
	
	P3 = 0x00;					// Clear P3
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (65536-50000) >> 8;	// Set Timer0 TH0
	TL0 = (65536-50000) & 0xff;	// Set Timer0 TL0
	// 1us * 50000 = 50 ms
	
	TR0 = 1;					// Start Timer0
	
	while(1)
	{
		// Coding here.
	}
	
}

void Timer0_INT(void) interrupt INTERRUPT_TIMER0
{	// 50 ms
	static unsigned char Interrupt_Counter = 0;
	static unsigned int Timer_Counter = 0;
	unsigned char Second = 0;
	unsigned char Second_BCD = 0;
	unsigned char Minute = 0;
	unsigned int i = 0;

	TR0 = 0;					// Stop Timer0
	TF0 = 0;					// Clear Timer0 overflag
	TH0 = (65536-50000) >> 8;	// Set Timer0
	TL0 = (65536-50000) & 0xff;
	TR0 = 1;					// Start Timer0
	
	Interrupt_Counter++;

	if(Interrupt_Counter>=20)
	{	// 50ms * 20 = 1000 ms = 1 Second
		Second = Timer_Counter % 60;
		Minute = Timer_Counter / 60;
			
		Second_BCD = ((Second/10)<<4|(Second%10));	// 二進制轉BCD碼
		SPI_Write(Second_BCD);	// 寫入秒
		
		P3 = Minute;			// 寫入分
		
		Timer_Counter++;
		Interrupt_Counter = 0;
	}
}


void SPI_Init(void)
{
	unsigned char i=0;
	
	P4 &= ~(SPI_nReset+SPI_Din+SPI_CLK);
	for(i=0;i<100;i++);
	P4 |= SPI_nReset;
}

void SPI_Write(unsigned char SPI_Data)
{	// 00010101
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
		
		for(j=0; j<10; j++);
		
		P4 |= SPI_CLK;
		//SPI_CLK = 1;
		
		for(j=0; j<10; j++);
		
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
