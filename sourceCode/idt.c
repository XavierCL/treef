#include "idt.h"

void setIdtGate(int32 index, uint32 address)
{
	idtGates[index].lowOffset=low16(address);
	idtGates[index].selector=KERNEL_CS;
	idtGates[index].flags=0x8E;
	idtGates[index].zReserved=0;
	idtGates[index].highOffset=high16(address);
}

void setIdtRegister()
{
	idtRegister.base=(uint32) &idtGates;
	idtRegister.size=IDT_ENTRIES*sizeof(IdtGate)-1;
	__asm__ __volatile__("lidtl (%0)"::"r"(&idtRegister));
}
