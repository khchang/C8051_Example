#include "c8051f340.h"
#include "main.h"

void main(void)
{
	unsigned char table_size = 0;
	unsigned char speed_grade = 0;
	unsigned char pattern_select = 0;	// 表示LED要顯示的燈號樣式。
	unsigned int i = 0, j = 0;
	
	Init_Device();
	
	P0 = 0xff;
	while(1)
	{
		pattern_select = P0 >> 6;
		speed_grade = ((P0 >> 4) & 0x03) + 1;
		
		switch(pattern_select)
		{
			case 0:
				table_size = sizeof(table_0);
				for(i = 0; i < table_size; i++)
				{
					P3 = table_0[i];
					
					for(j = 0;j < (speed_grade*10000);j++);	// Delay 40000 Loop
				}
			break;
			case 1:
				table_size = sizeof(table_1);
				for(i = 0; i < table_size; i++)
				{
					P3 = table_1[i];
					
					for(j = 0;j < (speed_grade*10000);j++);	// Delay 40000 Loop
				}
			break;
			case 2:
				table_size = sizeof(table_2);
				for(i = 0; i < table_size; i++)
				{
					P3 = table_2[i];
					
					for(j = 0;j < (speed_grade*10000);j++);	// Delay 40000 Loop
				}
			break;
			case 3:
				table_size = sizeof(table_3);
				for(i = 0; i < table_size; i++)
				{
					P3 = table_3[i];
					
					for(j = 0;j < (speed_grade*10000);j++);	// Delay 40000 Loop
				}
			break;
		}
		
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
    OSCICN    = 0x83;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    PCA_Init();
    Port_IO_Init();
    Oscillator_Init();
}
