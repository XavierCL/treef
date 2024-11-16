#ifndef IDT_H
#define IDT_H

#include "utils.h"
#include "screen.h"

#define KERNEL_CS 0x08

typedef struct
{
	uint16 lowOffset;
	uint16 selector;
	uint8 flags;
	uint8 zReserved;
	uint16 highOffset;
} __attribute__((packed)) IdtGate;

typedef struct
{
	uint16 size;
	uint32 base;
} __attribute__((packed)) IdtRegister;

#define IDT_ENTRIES 256

IdtGate idtGates[IDT_ENTRIES];
IdtRegister idtRegister;

void setIdtGate(int32 index, uint32 address);
void setIdtRegister();

#endif
