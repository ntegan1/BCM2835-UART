	// first byte is bits 0-7 of chan0
	bytes[1] = 0;
	printf("Before: ch0 0x%X, bytes1 0x%X\n", channels[0], bytes[1]);
	getBits(channels[0]	, 0	, 7 , tmp);
	setBits(bytes[1]	, 0	, 7	, tmp); 
	printf("Before: ch0 0x%X, bytes1 0x%X\n", channels[0], bytes[1]);
	
	bytes[2] = 0;
	getBits(channels[0], 8, 10, tmp);
	setBits(bytes[2], 0, 2, tmp);
	getBits(channels[1], 0, 4, tmp);
	setBits(bytes[2], 3, 7, tmp);

	
	bytes[3] = 0;
	getBits(channels[1], 5, 10, tmp);
	setBits(bytes[3], 0, 5, tmp);
	getBits(channels[2], 0, 1, tmp);
	setBits(bytes[3], 6, 7, tmp);


	bytes[4] = 0;
	getBits(channels[2], 2, 9, tmp);
	setBits(bytes[4], 0, 7, tmp);
	

	bytes[5] = 0;
	getBits(channels[2], 10, 10, tmp);
	setBits(bytes[5], 0, 0, tmp);
	getBits(channels[3], 0, 6, tmp);
	setBits(bytes[5], 1, 7, tmp);


	bytes[6] = 0;
	getBits(channels[3], 7, 10, tmp);
	setBits(bytes[6], 0, 3, tmp);
	getBits(channels[4], 0, 3, tmp);
	setBits(bytes[6], 4, 7, tmp);


	bytes[7] = 0;
	getBits(channels[4], 4, 10, tmp);
	setBits(bytes[7], 0, 6, tmp);
	getBits(channels[5], 0, 0, tmp);
	setBits(bytes[7], 7, 7, tmp);


	bytes[8] = 0;
	getBits(channels[5], 1, 8, tmp);
	setBits(bytes[8], 0, 7, tmp);

	bytes[9] = 0;
	getBits(channels[5], 9, 10, tmp);
	setBits(bytes[9], 0, 1, tmp);
	getBits(channels[6], 0, 5, tmp);
	setBits(bytes[9], 2, 7, tmp);


	bytes[10] = 0;
	getBits(channels[6], 6, 10, tmp);
	setBits(bytes[10], 0, 4, tmp);
	getBits(channels[7], 0, 2, tmp);
	setBits(bytes[10], 5, 7, tmp);


	bytes[11] = 0;
	getBits(channel[7], 3, 10, tmp);
	setBits(bytes[11], 0, 7, tmp);

	bytes[12] = 0;
	getBits(channels[8], 0, 7, tmp);
	setBits(bytes[12], 0, 7, tmp);

	bytes[13] = 0;
	getBits(channels[8], 8, 10, tmp);
	setBits(bytes[13], 0, 2, tmp);
	getBits(channels[9], 0, 4, tmp);
	setBits(bytes[13], 3, 7, tmp);


	bytes[14] = 0;
	getBits(channels[9], 5, 10, tmp);
	setBits(bytes[14], 0, 5, tmp);
	getBits(channels[10], 0, 1, tmp);
	setBits(bytes[14], 6, 7, tmp);


	bytes[15] = 0;
	getBits(channels[10], 2, 9, tmp);
	setBits(bytes[15], 0, 7, tmp);

	bytes[16] = 0;
	getBits(channels[10], 10, 10, tmp);
	setBits(bytes[16], 0, 0, tmp);
	getBits(channels[11], 0, 6, tmp);
	setBits(bytes[16], 1, 7, tmp);


	bytes[17] = 0;
	getBits(channels[11], 7, 10, tmp);
	setBits(bytes[17], 0, 3, tmp);
	getBits(channels[12], 0, 3, tmp);
	setBits(bytes[17], 4, 7, tmp);


	bytes[18] = 0;
	getBits(channels[12], 4, 10, tmp);
	setBits(bytes[18], 0, 6, tmp);
	getBits(channels[13], 0, 0, tmp);
	setBits(bytes[18], 7, 7, tmp);


	bytes[19] = 0;
	getBits(channels[13], 1, 8, tmp);
	setBits(bytes[19], 0, 7, tmp);

	bytes[20] = 0;
	getBits(channels[13], 9, 10, tmp);
	setBits(bytes[20], 0, 1, tmp);
	getBits(channels[14], 0, 5, tmp);
	setBits(bytes[20], 2, 7, tmp);


	bytes[21] = 0;
	getBits(channels[14], 6, 10, tmp);
	setBits(bytes[21], 0, 4, tmp);
	getBits(channels[15], 0, 2, tmp);
	setBits(bytes[21], 5, 7, tmp);


	bytes[22] = 0;
	getBits(channels[15], 3, 10, tmp);
	setBits(bytes[22], 0, 7, tmp);

