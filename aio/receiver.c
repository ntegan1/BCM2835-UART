/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: fifoserver.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <linux/stat.h>

#define FIFO_FILE       ".fifo"

int main(void)
{
        FILE *fp;
        char readbuf[80];
	char outStr[60];
	int bytes;
	system("rm -rf .fifo");
	
        /* Create the FIFO if it does not exist */
        umask(0);
        mknod(FIFO_FILE, S_IFIFO|0666, 0);

	int fd = open(".fifo", O_RDONLY);

	int ret = fcntl(fd,F_SETFL, O_NONBLOCK);
	//close(fd);
	printf("Return code is %d\n", ret);


	
        while(1)
        {
		readbuf[0] = '\0';
		outStr[0] = '\0';
		while (!(bytes = read(fd, readbuf, 50))) {
			usleep(10000);	
		}
		strncpy(outStr, readbuf, bytes);
		outStr[bytes] = '\0';
		printf("Received controls: %s\n", outStr);
		if (outStr[0] == '.') {
			system("clear");
			system("echo Receiver closed");
			return(0);
		}
		usleep(100000);
		
        }

        return(0);
}
