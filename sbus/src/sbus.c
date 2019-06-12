#include "sbus.h"


////
// Lookup table for fast reversing
////
uint8_t table[256] = {0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255};


////
// 	Notes /TO DO
////
/*
	# May eventually have to reverse bits?
	# Might need 5V level shifter for flight control input
*/

void fillBuf 		(void *buf, uint16_t *channels) {
	uint8_t 			*bufBytes;
	int					i;		//iterator
	int 				bytesDone = 0;

	// Setup
	bufBytes = (uint8_t *) buf;

	// start byte (byte 0)
	bufBytes[0] = START_BYTE;	

	// data (bytes 1->22)
	for (i = 0; i < NUM_DATA_BYTES; i++) {
		// convert channel (0-100) to (0->11 bits/2047)	
		bufBytes[i + 1] = channels[3];	//TODO (actually implement)

	}


	// flags (byte 23)
	bufBytes[23] = 0;
	
	// endbyte (byte 24)
	bufBytes[24] = END_BYTE;

	// flip all bytes
	reverseBits(bufBytes);
	
}


////
//		reverse bits using lookup table	
////
void reverseBits	(uint8_t *buf) {
	// Reverse all 25 (0-24) bytes
	int 			i;
	
	//printf("Before\t\tAfter\n");
	for (i = 0; i < 25; i++) {
		//printf("%d\t\t", buf[i]);
		buf[i] = table[buf[i]];
		//printf("%d\n", buf[i]);
	}
	




}

////
//	Reverse and print out for storage in lookup table
//	DEPRECATED DON"T USE
////
void reverse		(uint8_t* num) {
	uint8_t 		tmp;
	int				i;
	int				curBit;

	tmp = 			*num;

	for (i = 0; i < 8; i++) {
		// bit i
		curBit = (tmp & (1 << i)) != 0;

		// bit 7-0 of num2 should be tmp 0-7
		if (curBit) {
			// num2 bit 7 - i should be 1
			*num |= (1 << (7 - i));
			
		}
		else {
			// num2 bit 7 - i should be 0
			*num &= ~(1 << (7 - i));

		}
	}


		


}
