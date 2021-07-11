#define		SPI_nReset		0x20	// P4.5
#define		SPI_Din			0x08	// P4.3
#define		SPI_CLK			0x10	// P4.4


void Init_Device(void);
unsigned char Counter=0;

void SPI_Init(void);
void SPI_Write(unsigned char);

