#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <aio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define BUFSIZE 2500

int main (int argc, char **argv) {
	int 			fd;
	int			ret;
        struct aiocb 		aioinfo;



	if (argc != 1) {
		printf("Usage: ./sink\n");
		
		return(-1);
	}

	// Open pipe r/only
	fd = 0;
        if (fd < 0) perror("open");

        /* Zero out the aiocb structure (recommended) */
        bzero( (char *)&aioinfo, sizeof(struct aiocb) );

        /* Allocate a data buffer for the aiocb request */
        aioinfo.aio_buf = malloc(BUFSIZE+1);
        if (!aioinfo.aio_buf) perror("malloc");

        /* Initialize the necessary fields in the aiocb */
        aioinfo.aio_fildes = fd;
        aioinfo.aio_nbytes = BUFSIZE;
        aioinfo.aio_offset = 0;



	do {
		ret = aio_read( &aioinfo );
		if (ret < 0) perror("aio_read");

		
		// wait for i/o
		//for (;aio_error(&aioinfo) == EINPROGRESS;);
		
		// Loop for i/o
		while (aio_error(&aioinfo) == EINPROGRESS) {
			
			// sleep .5s
			usleep(50000);
		}
			fprintf(stdout, "Got %s\n", (char *)aioinfo.aio_buf);
			if (*(char *)aioinfo.aio_buf == '.') {
				
			exit(0);
			}
			usleep(50000);


	} while (1);


	return 0;
	// Wait for aio to occur
        uint64_t count =0;
	for (;aio_error(&aioinfo) == EINPROGRESS;count++);

        printf("Counted to %lu while waiting\n",count);
        if ((ret = aio_return( &aioinfo )) > 0) {
                printf("Got %d bytes:\n",ret);

                //printf("Bytes: %s\n",(char *)aioinfo.aio_buf);
        } else {
                printf("READ FAILED!!!\n");
        }


	
	
}


