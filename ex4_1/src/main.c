#include "c8051f340.h"

void main(void)
{
	unsigned int i = 0;

	
	P2MDOUT = 0x0C;		// Set the P2.2 and the P2.3 are the push-pull mode.
	PCA0MD = 0x00;
	XBR1 = 0x40;
	
	while(1)
	{
		P2 |= 0x0c;
		for(i=0;i<10000;i++);
		P2 &= ~0x0c;
		for(i=0;i<10000;i++);
	}
}
