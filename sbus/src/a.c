#include <stdio.h>
#include "sbus.h"

void 			printByteBuf 	(void *);
void			byteToBinStr 	(char*,uint8_t);
void			testUart		();
void 			transmit		(void *);

int main (int argc, char **argv) {
	uint8_t				byteBuf[25];
	uint8_t				channelBuf[22];
	int 				i;

	
	fillBuf(byteBuf, channelBuf);	
	printByteBuf(byteBuf);
	uartSetup();

	while (1) {
		transmit(byteBuf);
		busyWait();
	}
	//testUart();

	return 0;
}


void			printByteBuf (void *buf) {
	int 				i;
	char				binBuf[9];

	binBuf[8] = '\0';
	printf("Printing Byte Buffer\n");
	for (i = 0; i < 25; i++) {
		byteToBinStr(binBuf, ((uint8_t*) buf)[i]);
		printf("%s\n", binBuf);
				
	}

}

void			byteToBinStr (char* buf, uint8_t byte) {
	int 				i;
	for (i = 0; i < 8; i++) {
		buf[i] = (char) (((byte << i) & 128) >> 7) + 48;	
	}
}


void			testUart		() {
	*DR = 'a';
	*DR = 'b';
	*DR = 'c';
	*DR = 'd';

	printf("Writing a,b,c,d\n");
	busyWait();
	printf("\nReading: got \n");
	while ( !(*FR & (0x10))) { 	// bit 4 is 1 if rx empty
		printf("%c\n", *DR);
		busyWait();
	}


}


void 			transmit		(void *) {
	// TODO test RIS thing < 4 full, write 4
}

