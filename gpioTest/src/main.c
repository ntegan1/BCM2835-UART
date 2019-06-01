#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <errno.h>

#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define MEM_SIZE				0xFF



int 				enableUART ();
void 				mapMem ();
void 				*mem;
void 				gpioSetup ();


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
	gpioSetup();


}

void mapMem () {
	int errs = 0;
	//printf("Error: %d\n", errno);
	errs += errno;
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	//printf("Error: %d\n", errno);
	errs += errno;
	mem = (void *) mmap (
		NULL,		// don't care address
		MEM_SIZE,	// how much mem i need? Need 0x8C + 32 = 0xAC?
		PROT_READ | PROT_WRITE,	// r/w
		MAP_SHARED,
		fd,
		GPIO_BASE
	);
	//printf("Error: %d\n", errno);
	//printf("uartMem at addr %p\n", uartMem);
	errs += errno;
	printf("Memory map successful, %d errs\n\n", errs);
	close(fd);
	
}

// Want 2 use gpio26
void gpioSetup () {
	volatile uint32_t * GPFSEL2			= (volatile uint32_t *) (mem + 0x08);
	volatile uint32_t * SET0			= (volatile uint32_t *) (mem + 0x1C);
	volatile uint32_t * CLR0 			= (volatile uint32_t *) (mem + 0x28);

	////
	//	GPFSEL2 function select 2
	////
	// gpio26 bits 20:18 0 input, 1 output
	*GPFSEL2 &= ~(7 << 18);		// clear bits 20:18 ( sets as input)
	*GPFSEL2 |= (1 << 18);		// set bit 18 (output)

	////
	//	SET0	GPIO output set reg 0
	////

	////
	// 	CLR0	GPIO output clear reg 0
	////

	for (;;) {
		// turn pin on
		*SET0 |= (1 << 26);
		sleep(2);
		*CLR0 |= (1 << 26);
		sleep(2);
	}


}


