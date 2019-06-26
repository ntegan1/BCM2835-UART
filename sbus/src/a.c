#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <linux/stat.h>

#define FIFO_FILE       ".fifo"

#include "sbus.h"

void 			printByteBuf 	(void *);
void			byteToBinStr 	(char*,uint8_t);
void			testUart		();
void 			transmit		(uint8_t);
int				numSent			;
void			sendByteBuf		(uint8_t *);
void			sendChannelControl(uint16_t *, char);
void			decrementChannelBuf(uint16_t * channelBuf);

int armed;

int main (int argc, char **argv) {
	uint8_t				byteBuf[25];
	uint16_t			channelBuf[16];
	int 				i;
  	int         			j;

	// FIFO_SETUP
	int				fd;	// fifo fd
	int				bytes;	//bytes read
	char 				readbuf[80];
	char				outStr[60];
	
	system("rm -rf .fifo");
	umask(0);
	mknod(FIFO_FILE, S_IFIFO|0666,0);
	fd = open(".fifo", O_RDONLY);
	int ret = fcntl(fd, F_SETFL, O_NONBLOCK);
	printf("async fifo fcntl returned: %X\n", ret);
	armed = 0;

	// Middle out channelBuf
	for (i = 0; i < 16; i++) channelBuf[i] = 0; // = (1792 - 192) / 2;
	channelBuf[0] = 992;

	channelBuf[1] = 992;

	channelBuf[3] = 992;
	channelBuf[2] = 192;
	uartSetup();

	for (;;) {
		// while no bytes to read

		while (!(bytes = read(fd, readbuf, 50))) {
			
			decrementChannelBuf(channelBuf);
			fillBuf(byteBuf, channelBuf);
			sendByteBuf(byteBuf);
			usleep(SBUS_PACKET_SLEEP);
		}
		for (i = 0; i < bytes; i++) {
			sendChannelControl(channelBuf, readbuf[i]);
		}
		if (readbuf[0] == '.') {
			system("clear");
			system("echo Receiver closed");
			return(0);
		}
				fillBuf(byteBuf, channelBuf);
		sendByteBuf(byteBuf);
		usleep(SBUS_PACKET_SLEEP);
		//printf("channelBuf %d\n", channelBuf[0]);
		/*
		while (!(bytes = read(fd, readbuf, 50))) {
//			decrementChannelBuf(channelBuf);
//			fillBuf(byteBuf, channelBuf);
			sendByteBuf(byteBuf);
			usleep(SBUS_PACKET_SLEEP);
		}
		
		// bytes to read
		for (i = 0; i < bytes; i++) {
			sendChannelControl(channelBuf, readbuf[i]);
			fillBuf(byteBuf, channelBuf);
		}
		if (readbuf[0] == '.') {
			system("clear");
			system("echo Receiver closed");
			return(0);
		}
		*/

	}
	

	busyWait();
	exit(0);



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



#define ACCEL 10
void			sendChannelControl(uint16_t *chanBuf, char cmd) {
	if (cmd == 'q' && (chanBuf[2] - ACCEL > 192)) {
		chanBuf[2] -= ACCEL;
	}
	else if (cmd == 'e' && (chanBuf[2] + ACCEL < 1792)) {
		chanBuf[2] += ACCEL;
	}
	else if (cmd == 's' && (chanBuf[0] - ACCEL > 192)) {
		chanBuf[0] -= ACCEL;
	}
	else if (cmd == 'w' && (chanBuf[0] + ACCEL < 1792)) {
		chanBuf[0] += ACCEL;
	}
	else if (cmd == 'a' && (chanBuf[1] - ACCEL > 192)) {
		chanBuf[1] -= ACCEL;
	}
	else if (cmd == 'd' && (chanBuf[1] + ACCEL < 1792)) {
		chanBuf[1] += ACCEL;
	}
	else if (cmd == 'z' && (chanBuf[3] - ACCEL > 192)) {
		chanBuf[3] -= ACCEL;
	}
	else if (cmd == 'c' && (chanBuf[3] + ACCEL < 1792)) {
		chanBuf[3] += ACCEL;
	}
	if (cmd == 'p') {
		if (!armed) {
			chanBuf[4] = 1792;	
			armed = 1;
			printf("ARMED\n");
		}
		else {
			printf("DEARMED\n");
			armed = 0;
			chanBuf[4] = 800;
		}
	}
}


void			decrementChannelBuf(uint16_t * channelBuf) {
	int i;
	for (i = 0; i < 4; i++) {
		if (i == 2) {
			if (channelBuf[2] > 192) {
				channelBuf[2] -= 2;
			}
		}
		else {
			if (channelBuf[i] > 992) {
				channelBuf[i] -= 1;
			}
			else if (channelBuf[i] < 992) {
				channelBuf[i] += 1;
			}
		}
	}
}
