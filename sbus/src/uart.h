#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <errno.h>


////
//  Definitions
////
#define MEM_LEN (8192)
#define BCM2708_PERI_BASE       0x20000000
#define GPIO_BASE            	(BCM2708_PERI_BASE + 0x200000) /* GPIO controller */
#define MEM_PTR					(uartMem)
#define CR						((volatile uint32_t *) (MEM_PTR + 0x30 + 0x1000))
#define LCRH					((volatile uint32_t *) (MEM_PTR + 0x2C + 0x1000))
#define IFLS					((volatile uint32_t *) (MEM_PTR + 0x34 + 0x1000))
#define RIS						((volatile uint32_t *) (MEM_PTR + 0x3C + 0x1000))
#define IMSC					((volatile uint32_t *) (MEM_PTR + 0x38 + 0x1000))
#define IBRD					((volatile uint32_t *) (MEM_PTR + 0x24 + 0x1000))
#define FBRD					((volatile uint32_t *) (MEM_PTR + 0x28 + 0x1000))
#define ICR						((volatile uint32_t *) (MEM_PTR + 0x44 + 0x1000))
#define DR						((volatile uint32_t *) (MEM_PTR + 0x00 + 0x1000))
#define FR						((volatile uint32_t *) (MEM_PTR + 0x18 + 0x1000))


////
//  Functions
////
void 				uartSetup 	();
void				enableUart	();
void				disableUart	();
void 				mapMem 		();
void				busyWait 	();
void				clearFIFOs 	();
void				setBaudrate	(int,int);
void				clearICRs	();
int					txBufLow	();


////
//  Variables
////
void *				uartMem;
