#include <stdio.h>
#include "sbus.h"

void 			printByteBuf 	(void *);
void			byteToBinStr 	(char*,uint8_t);
void			testUart		();
void 			transmit		(uint8_t);
int				numSent			;

int main (int argc, char **argv) {
	uint8_t				byteBuf[25];
	uint16_t			channelBuf[16];
	int 				i;

	
	fillBuf(byteBuf, channelBuf);	
	printByteBuf(byteBuf);
	uartSetup();

	numSent = 0;
	while (1) {
		if (txBufLow()) {
			transmit(byteBuf[numSent++]);	// transmit  4
			busyWait();								// delete me?
			transmit(byteBuf[numSent++]);	// transmit  4
			busyWait();								// delete me?
			transmit(byteBuf[numSent++]);	// transmit  4
			busyWait();								// delete me?
			transmit(byteBuf[numSent++]);	// transmit  4
			busyWait();								// delete me?



			if (numSent == 24) {
				// send the last one
				transmit(0);
				numSent = 0;
			}
			
			
			
		}
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
	// clear Int's (rx < half full)
	clearICRs();
	busyWait();
	printf("is txBufLow?%d\n",txBufLow());
	*DR = 'a';
	printf("is txBufLow?%d\n",txBufLow());
	*DR = 'b';
	printf("is txBufLow?%d\n",txBufLow());
	*DR = 'c';
	printf("is txBufLow?%d\n",txBufLow());
	*DR = 'd';
	printf("is txBufLow?%d\n",txBufLow());
	*DR = 'f';
	printf("is txBufLow?%d\n",txBufLow());

	printf("Writing a,b,c,d\n");
	busyWait();
	printf("\nReading: got \n");
	while ( !(*FR & (0x10))) { 	// bit 4 is 1 if rx empty
		printf("%c\n", *DR);
		printf("txbuflow? huh%d\n", txBufLow());
		busyWait();
	}


}


void 			transmit		(uint8_t byte) {
	*DR = byte;	
}


