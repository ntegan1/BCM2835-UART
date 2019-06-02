#include "sbus.h"


////
// 	Notes /TO DO
////
/*
	# May eventually have to reverse bits?
*/

void fillBuf 	(void *buf, uint8_t *channels) {
	uint8_t 			*bufBytes;

	// Setup
	bufBytes = (uint8_t *) buf;

	// start byte
	bufBytes[0] = START_BYTE;	

	// data

	// flags
	
	// endbyte
	
}
