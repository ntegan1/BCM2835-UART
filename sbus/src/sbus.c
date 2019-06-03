#include "sbus.h"
25 byte protocol, 100kbps baudrate
	one byte = 1startbit + 8databit + 1paritybit + 2stopbit
	Highest bit sent first (receive 000000000001 = 1024)
	highest bit arrives first?

	1 protocol "packet" consists of:
	[startbyte][data1][data2]...[data22][flags][endbyte]

	data1-22:
	each channel is 11 bits
	chan1 8 bits from data1, 3 bits data2
	chan2 last 5 bits data2, 6 bits data3


////
// 	Notes /TO DO
////
/*
	# May eventually have to reverse bits?
	# Might need 5V level shifter for flight control input
*/

void fillBuf 	(void *buf, uint16_t *channels) {
	uint8_t 			*bufBytes;
	int					i;		//iterator

	// Setup
	bufBytes = (uint8_t *) buf;

	// start byte (byte 0)
	bufBytes[0] = START_BYTE;	

	// data (bytes 1->22)
	/*
	for (i = 0; i < NUM_CHANNELS; i++) {
		// convert channel (0-100) to (0->11 bits/2047)	
		bufBytes[i + 1] = 300;	//TODO (actually implement)
		
	}
	*/
	// Hardcode like fuck
	bufBytes[1] = channels[0] & 0xFF;
	bufBytes[2] = ((channels[0] & 0x700) >> 0x700) | ((channels[1] & 0x1F) << 3);
	bufBytes[3] = ((channels[1] & 0x700) >> 0x700) | ((channels[1] & 0x1F) << 3);
	// TODO
	// // TODO
	// // TODO Here
	


	// flags (byte 23)
	bufBytes[23] = 0;
	
	// endbyte (byte 24)
	bufBytes[24] = END_BYTE;
	
}
