#include "payload.h"
#include <stdio.h>

////
//					GETBITS
//
//	x is channel[1] or so, y is start bit, z is stop bit
// save result in w tmp (uint8_t)
////
#define getBits(x, y, z, w) {							\
		w = (x & (((1 << (z - y + 1)) - 1) << y)) >> y;	\
	}

////
//					SETBITS
//
// x is byte uint8_t , y start, z stop, w is uint8_t bits
//
// FIrst clear byts y-z of x
// second, set bits y-z to (w & y-z+1 bits) << y, in x
////
#define setBits(x, y, z, w) {							\
		x &= ~(((1 << (z - y + 1)) - 1) << y);			\
		x |= (w & ((1 << (z-y+1)) - 1)) << y;			\
	}
		


// bytes[1] to bytes[22]
void channelsToBytes (uint16_t * channels, uint8_t *bytes) {

	uint8_t 			tmp;

	// first byte is bits 0-7 of chan0
	bytes[1] = 0;
	printf("Before: ch0 0x%X, bytes1 0x%X\n", channels[0], bytes[1]);
	getBits(channels[0]	, 0	, 7 , tmp);
	setBits(bytes[1]	, 0	, 7	, tmp); 
	printf("Before: ch0 0x%X, bytes1 0x%X\n", channels[0], bytes[1]);
	
	// second 8-10 of ch0, 1-l``	
	

	
}
