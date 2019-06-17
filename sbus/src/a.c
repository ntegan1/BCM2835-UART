#include <stdio.h>
#include "sbus.h"

void 			printByteBuf 	(void *);
void			byteToBinStr 	(char*,uint8_t);
void			testUart		();
void 			transmit		(uint8_t);
int				numSent			;
void			sendByteBuf		(uint8_t *);

int main (int argc, char **argv) {
	uint8_t				byteBuf[25];
	uint16_t			channelBuf[16];
	int 				i;
  int         j;

	// Zero out chanelBuf
	for (i = 0; i < 16; i++) channelBuf[i] = 192;
	//fillBuf(byteBuf, channelBuf);	
	//printByteBuf(byteBuf);
	uartSetup();

	printf("Enter a char\n");
	int a;
	system("/bin/stty raw");
	for (;;) {
		//a = getchar();
		//https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar#1798833

		a = fgetc(stdin);
		if (a == 'w' && channelBuf[0] < 1792) {
			channelBuf[0] = channelBuf[0] + 1;
			fillBuf(byteBuf, channelBuf);
		}
		else if (a == 's' && channelBuf[0] > 192) {
			channelBuf[0] = channelBuf[0] - 1;
			fillBuf(byteBuf, channelBuf);
		}
		else if (a == '.') {
			system("/bin/stty cooked");
			exit(-1);
		}
		else {
			printf("No char pressed\n");
		}
		/*
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
		*/
		sendByteBuf(byteBuf);
		usleep(SBUS_PACKET_SLEEP);


	}
	

	//transmit(0xAA);
	busyWait();
	exit(-1);

	numSent = 0;
	
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


void			sendByteBuf		(uint8_t *byteBuf) {
	// write 16
	*DR = byteBuf[0];
	*DR = byteBuf[1];
	*DR = byteBuf[2];
	*DR = byteBuf[3];
	*DR = byteBuf[4];
	*DR = byteBuf[5];
	*DR = byteBuf[6];
	*DR = byteBuf[7];
	*DR = byteBuf[8];
	*DR = byteBuf[9];
	*DR = byteBuf[10];
	*DR = byteBuf[11];
	*DR = byteBuf[12];
	*DR = byteBuf[13];
	*DR = byteBuf[14];
	*DR = byteBuf[15];
	while (!txBufLow());

	// write 8
	*DR = byteBuf[16];
	*DR = byteBuf[17];
	*DR = byteBuf[18];
	*DR = byteBuf[19];
	*DR = byteBuf[20];
	*DR = byteBuf[21];
	*DR = byteBuf[22];
	*DR = byteBuf[23];
	while (!txBufLow());

	// write 1
	*DR = byteBuf[24];
}


