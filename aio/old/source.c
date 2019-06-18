#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
void writeKeysToKeys	(int * fileDes);
int main () {
	// stdout
	int fd = 1;
	usleep(1000);
	writeKeysToKeys(&fd);
}

////
//  Set *fileDes = to file descriptor of where send keys to ('./keys.keys' currently)
////
void writeKeysToKeys	(int * fileDes) {
	printf("Enter a char\n");
	char *byteBuf;
	int a;
	system("/bin/stty raw");
	for (;;) {
		a = getchar();
		//https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar#1798833

		if (a == 'w' /*&& channelBuf[0] < 1792*/) {
			//channelBuf[0] = channelBuf[0] + W_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
			//*byteBuf = 'w';
			//write(*fileDes, byteBuf, 1); 

		}
		else if (a == 'a' /*&& channelBuf[1] > 192*/) {
			//channelBuf[1] = channelBuf[1] - A_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 's' /*&& channelBuf[0] > 192*/) {
			//channelBuf[0] = channelBuf[0] - S_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 'd' /*&& channelBuf[1] < 1792*/) {
			//channelBuf[1] = channelBuf[1] + D_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 'q' /*&& channelBuf[2] > 192*/) {
			//channelBuf[2] = channelBuf[2] - Q_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 'e' /*&& channelBuf[2] < 1792*/) {
			//channelBuf[2] = channelBuf[2] + E_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 'z' /*&& channelBuf[3] > 192*/) {
			//channelBuf[3] = channelBuf[3] - Z_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == 'c' /*&& channelBuf[3] < 1792*/) {
			//channelBuf[3] = channelBuf[3] + C_ACCELERATION;
			//fillBuf(byteBuf, channelBuf);
		}
		else if (a == '.') {
			system("/bin/stty cooked");
			exit(-1);
		}
		else {
			//printf("No char pressed\n");
		}
		//fflush(*fileDes);
		/*
		if (a == 0x1B) {
			a = getchar();	
			a = getchar();
			switch (a) {
				case 0x41:
					printf("UP\n");
					break;
				case 0x42:
					printf("DOWN\n");
					break;
				case 0x43:
					printf("RIGHT\n");
					break;
				case 0x44:
					printf("LEFT\n");
					break;
			}
		}
		*/
		usleep(3000);
	}

	return;

}


