#include <inttypes.h>


////
//	Info
////
/*
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

	flags:
	bit7 => ch17 is digital
	bit6 => ch18 is digital
	bit5 => frame lost (red LED on rx)
	bit4 => failsafe activated
	bits3-1 not used
*/

////
//	Definitions
////
#define START_BYTE				0xF0	// 11110000b
#define END_BYTE				0x00	// 00000000b
#define NUM_CHANNELS			22


////
//	# Do stuff
//
//	## buf: 		place data to send here
//					should be 3 + (22 *data) = 25 byte
//	## channels:	22 bytes of (throttle percentages?)
////
void fillBuf 	(void *buf, uint8_t *channels);
