/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: fifoclient.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE       ".fifo"
#define POLL_RATE	3000 // in uS

void writeChar(char c);

int main(int argc, char *argv[])
{
	// redirect 1 to /dev/null?

	// NEW USAGE
	system("/bin/stty raw");
	char a;
	printf("a%d\nz%d\n", 'a', 'z');

	for (;;) {
		a = getchar();

		// ascii 97a 122z
		if (a == '.') {
			writeChar(a);
			system("/bin/stty cooked");
			system("clear");
			system("echo Sender closed");
			return(0);
		}
		else if (a > 96 && a < 123) writeChar(a);
		
		
		usleep(POLL_RATE);
	}

	system("/bin/stty cooked");
        return(0);
}



void writeChar(char c) {
	int fd = open(".fifo", O_WRONLY);
	write(fd, &c, 1);
	close(fd);
}
