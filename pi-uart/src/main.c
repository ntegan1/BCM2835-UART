#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <errno.h>

#define MEM_LEN (0xAC)


int 				enableUART ();
void 				mapMem ();
void *				uartMem;


int main ( int argc, char **argv) {
	if (argc != 1) {
		fprintf(stderr, "Usage: ./uart\n");
		exit(-1);
	}
	/*
	printf("Enter a char\n");
	int a;
	system("/bin/stty raw");
	for (;;) {
		a = getchar();
		//https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar#1798833
		if (a == '.') {
			system("/bin/stty cooked");
			exit(-1);
		}
		if (a == 0x1B) {
			a = getchar();	
			a = getchar();
			switch (a) {
				case 0x41:
					printf("UP\n");
					break;
				case 0x42:
					printf("DOWN\n");
					break;
				case 0x43:
					printf("RIGHT\n");
					break;
				case 0x44:
					printf("LEFT\n");
					break;
			}
		}
	}
	*/

	mapMem();
	enableUART();


}

void mapMem () {
	int errs = 0;
	//printf("Error: %d\n", errno);
	errs += errno;
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	//printf("Error: %d\n", errno);
	errs += errno;
	uartMem = (void *) mmap (
		NULL,		// don't care address
		MEM_LEN,	// how much mem i need? Need 0x8C + 32 = 0xAC?
		PROT_READ | PROT_WRITE,	// r/w
		MAP_SHARED,
		fd,
		0x7E20000	// offset: PL011 UART mapped on 0x7E20100
	);
	//printf("Error: %d\n", errno);
	//printf("uartMem at addr %p\n", uartMem);
	errs += errno;
	printf("Memory map successful, %d errs\n\n", errs);
	
}


int enableUART () {

	////
	// Control Register
	////
	volatile uint32_t * CR = (volatile uint32_t *) (uartMem + 0x30 + 0x100);	// CR @ 0x30, + 100 b/c page aligned
	
	// Enable uart
	//printf("Before: %X, bit 0 = %d\n", *CR, *CR & 1);
	*CR |= 1 << 0;
	//printf("After: %X, bit 0 = %d\n", *CR, *CR & 1);

	// disable CTS and RTShardware flow control
	//printf("Before: %X\n", *CR & 0xC000);
	*CR &= ~(0xC000);
	//printf("After: %X\n",*CR & 0xC000);




	// enable Rx, TX, and loopback
	//printf("rx, tx, loopback Before: %X\n", *CR & 0x0380);
	*CR |= 0x380;




	////
	// LCRH Line control reeg
	////
	volatile uint32_t * LCRH = (volatile uint32_t *) (uartMem + 0x2C + 0x100);	// LCRH @ 0x2C, + 100 page align

	// 8 bit word size
	//printf("before: %X\n", *LCRH & 0x60);
	*LCRH |= 0x60;
	//printf("after: %X\n", *LCRH & 0x60);

	// enable fifos
	//printf("before: %X\n", *LCRH & 0x10);
	*LCRH |= 0x10;
	//printf("after: %X\n", *LCRH & 0x10);
	
	// enable two bits
	//printf("before: %X\n", *LCRH & 0x08);
	*LCRH |= 0x08;

	//printf("after: %X\n", *LCRH & 0x08);

	// enable even parity bit 2 is even set, bit 1 is parity set
	//printf("before: %X\n", *LCRH & 0x04);
	*LCRH |= 0x06;
	//printf("after: %X\n", *LCRH & 0x04);

	// enable break. low level on txd after tx? Idk if need TODO
	//printf("before: %X\n", *LCRH & 0x01);


	////
	// IFLS Int FIFO Lvl Sel
	////
	printf("Reg\t\tB4\t\tAfter\t\t\n");
	volatile uint32_t * IFLS = (volatile uint32_t *) (uartMem + 0x34 + 0x100);	// IFLS @ 0x34, + 100 page align
	printf("IFLS\t\t0x%X\t", *IFLS);

	//receive fifo lvl sel bits 5:3, b010 1/2 full interrupt RXIFLSEL	
	
	*IFLS &= ~(5 << 3); // clear bits 5 and 3
	*IFLS |= 1 << 4;	// Set bit 4

	//tx fifo lvl sel bits 2:0, b010 1/2 full
	*IFLS &= ~(5 << 0);	// clear bits 0 and 2

	*IFLS |= 1 << 1;	// set bit 1


	printf("0x%X\n", *IFLS);// after


	////
	// RIS Raw interrupt status register
	////
	volatile uint32_t * RIS = (volatile uint32_t *) (uartMem + 0x3C + 0x100);	// RIS @ 0x3C, + 100 page align
	// rx int bit 4, tx bit 5
	printf("RIS REG IS 0x%X\n", *RIS);


	////
	// IMSC int mask set clear reg
	//// 
	volatile uint32_t * IMSC = (volatile uint32_t *) (uartMem + 0x38 + 0x100);	// IMSC @ 0x38, + 100 page align 
	// 5 TXIM, 4 TXIM
	printf("IMSC\t\t0x%X\t", *IMSC); // before
	*IMSC |= 0x30;	// set bits 5 and 4
		
	printf("0x%X\n", *IMSC); // after


	////
	//	ICR int clear reg 0x44
	////
	volatile uint32_t * ICR = (volatile uint32_t *) (uartMem + 0x44 + 0x100);	


	////
	//	DR Data register 0x00
	////
	volatile uint32_t * DR = (volatile uint32_t *) (uartMem + 0x0 + 0x100);	




	////
	// TESTING
	////
	printf("\nRXINT: %d, TXINT: %d\n", *RIS & (1 << 4), *RIS & (1 << 5));
	printf("Clearing\n");
	*ICR &= ~(3 << 4); // clear bits 5 and 4
	printf("RXINT: %d, TXINT: %d\n", *RIS & (1 << 4), *RIS & (1 << 5));
	printf("\nTransmitting 4 'x' chars\n");

	// Push 4  'x's to tx fifo
	printf("%d DR is\n", *DR);
	*DR = 'x';
	printf("%d DR is\n", *DR);
	*DR = 'x';
	printf("%d DR is\n", *DR);
	*DR = 'x';
	*DR = 'x';
	printf("%d DR is\n", *DR);
	*DR = 'x';
	*DR = 'x';
		sleep(2);
	
	printf("%d DR is\n", *DR);

	printf("\nRXINT: %d, TXINT: %d\n", *RIS & (1 << 4), *RIS & (1 << 5));
	printf("Clearing\n");
	*ICR &= ~(3 << 4); // clear bits 5 and 4
	printf("RXINT: %d, TXINT: %d\n", *RIS & (1 << 4), *RIS & (1 << 5));
	printf("\nTransmitting 4 'x' chars\n");



	

}
