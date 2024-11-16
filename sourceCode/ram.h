#ifndef RAM
#define RAM

#include "utils.h"
#include "screen.h"
#include "string.h"
#include "multiboot.h"

/*
RAM scheme:

0x0
	.
	call stack
	.
0x4000~
	.
	RAM manager
	.
0x2D701B~
	.
	.
	.
	Heap
	.
	.
	.
0x5B8D8000~
*/

/*
Page Descriptor:

1 bit: 0=free, 1=taken
31 bits: contigus size of free or taken
*/

typedef struct ramPageDscS
{
	int32 size;
}__attribute__((packed)) ramPageDsc;


uint32 maxRam;
uint32 stackEnd;
uint32 ramDscTableSize;
static const uint32 STACK_SIZE=0x4000;
static const uint32 PAGE_SIZE=0x1000;//bytes
ramPageDsc* ramDscTable;

uint32 ramSetup(multibootInfo* biosInfo);
void ramInit(multibootInfo* biosInfo);
uint32 ramNew(uint32 bytes);
void ramNewAt(uint32 address, uint32 bytes);
void ramDel(uint32 address);

#endif
