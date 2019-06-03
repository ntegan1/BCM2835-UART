#include "sbus.h"
#include "uart.h"


////
// 	Notes /TO DO
////
/*
	# May eventually have to reverse bits?
	# Might need 5V level shifter for flight control input
*/

void fillBuf 	(void *buf, uint8_t *channels) {
	uint8_t 			*bufBytes;
	int					i;		//iterator

	// Setup
	bufBytes = (uint8_t *) buf;

	// start byte (byte 0)
	bufBytes[0] = START_BYTE;	

	// data (bytes 1->22)
	for (i = 0; i < NUM_CHANNELS; i++) {
		// convert channel (0-100) to (0->11 bits/2047)	
		bufBytes[i + 1] = 100;	//TODO (actually implement)
	}


	// flags (byte 23)
	bufBytes[23] = 0;
	
	// endbyte (byte 24)
	bufBytes[24] = END_BYTE;
	
}
