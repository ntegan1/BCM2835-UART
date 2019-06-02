#include "uart.h"





void				clearFIFOs 	() {
	*LCRH &= ~(0x10);
	busyWait();
	*LCRH |= 0x10;
	busyWait();
}


// 16 bit IBRD, 6 bit FBRD
void				setBaudrate	(int i, int f) {
	*IBRD = (i & 0xFFFF);
	*FBRD = (f & 0x3F);
}


void				busyWait 	() {
	printf("Busywait");
	while (*FR & (0x1 << 3)) {
		printf(".");
	}
	printf("\n");

}


void				disableUart	() {
	*CR &= ~(1 << 0);
}


void				enableUart	() {
	// Enable uart
	*CR |= 1 << 0;

}


void mapMem () {
	int errs = 0;
	errs += errno;
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	errs += errno;
	uartMem = (void *) mmap (
		NULL,		// don't care address
		MEM_LEN,	// how much mem i need? Need 0x8C + 32 = 0xAC?
		PROT_READ | PROT_WRITE,	// r/w
		MAP_SHARED,
		fd,
		GPIO_BASE
	);
	errs += errno;
	//printf("Memory map successful, %d errs\n\n", errs);
	close(fd);
}


void 				uartSetup 	() {
    mapMem();
    
    // Disable UART
    *CR = 0;

    // 8 bit word size
	*LCRH |= 0x60;

	// enable fifos
	*LCRH |= 0x10;
	
	// enable two bits
	*LCRH |= 0x08;

	// enable even parity bit 2 is even set, bit 1 is parity set
	*LCRH |= 0x06;

    // Clear IFLS?
    *IFLS = 0;

    //receive fifo lvl sel bits 5:3, b010 1/2 full interrupt RXIFLSEL	
	*IFLS &= ~(5 << 3); // clear bits 5 and 3
	*IFLS |= 1 << 4;	// Set bit 4

	//tx fifo lvl sel bits 2:0, b010 1/2 full
	*IFLS &= ~(5 << 0);	// clear bits 0 and 2
	*IFLS |= 1 << 1;	// set bit 1

	// int mask set/clear 5 TXIM, 4 TXIM
	*IMSC |= 0x30;	// set bits 5 and 4

    // 3MHz / 30 = 100kbps
	setBaudrate(30, 0);

    // disable CTS and RTShardware flow control
	*CR &= ~(0xC000);

	// enable Rx, TX, and loopback
	*CR |= 0x380;

	// Loopback is bit 7, disable for testing
	*CR &= ~(0x080);

    enableUart();

    // Clear int clear reg?
    //*ICR &= ~(3 << 4); // clear bits 5 and 4

    clearFIFOs();
}



