#include <stdio.h>
#include <inttypes.h>
#include "payload.h"

int main (int argc, char **argv) {
	uint16_t 		channels[16];
	uint8_t 		byteBuf[25];	// 0-start, 1-22 data, 23 flags, 24 stop
	int				i;				// iterator

	for (i = 0; i < 16; i++) channels[i] = (i + 2) * 10;

	channelsToBytes (channels, byteBuf);

	return 0;

}
