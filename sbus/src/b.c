#include <stdio.h>
#include <inttypes.h>
#include "payload.h"

void 			printByteBuf 	(void *);
void			byteToBinStr (char* buf, uint8_t byte);

int main (int argc, char **argv) {
	uint16_t 		channels[16];
	uint8_t 		byteBuf[25];	// 0-start, 1-22 data, 23 flags, 24 stop
	int				i;				// iterator

  // Constant Bytes
  byteBuf[0] = (uint8_t) 0x0F;
  byteBuf[23] = (uint8_t) 0x00;
  byteBuf[24] = (uint8_t) 0x00;

	for (i = 0; i < 16; i++) channels[i] = 192;

	channelsToBytes (channels, byteBuf);
  printByteBuf(byteBuf);
  printf("\nPrinting Channel buffers\n");
  for (i = 0; i < 16; i++) {
    printf("channels[%02d] = 0x%X\n", i, channels[i] & /*11 bits*/ ((1 << 11) - 1));
  }

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
  // Prints [MSB,bit6,bit5,bit4,bit3,bit2,bit1,LSB]
	for (i = 0; i < 8; i++) {
		//buf[i] = (char) (((byte << i) & 128) >> 7) + 48;	
	}

  // Prints [LSB,bit1,bit2,bit3,bit4,bit5,bit6,MSB]
	for (i = 0; i < 8; i++) {
		buf[i] = (char) (((byte >> i) & 1) ) + 48;	
	}
}


