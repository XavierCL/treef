#include "isr.h"

void loadISR()
{
	setIdtGate(0, (uint32)isr0);
	setIdtGate(1, (uint32)isr0);
	setIdtGate(2, (uint32)isr0);
	setIdtGate(3, (uint32)isr0);
	setIdtGate(4, (uint32)isr0);
	setIdtGate(5, (uint32)isr0);
	setIdtGate(6, (uint32)isr0);
	setIdtGate(7, (uint32)isr0);
	setIdtGate(8, (uint32)isr0);
	setIdtGate(9, (uint32)isr0);
	setIdtGate(10, (uint32)isr0);
	setIdtGate(11, (uint32)isr0);
	setIdtGate(12, (uint32)isr0);
	setIdtGate(13, (uint32)isr0);
	setIdtGate(14, (uint32)isr0);
	setIdtGate(15, (uint32)isr0);
	setIdtGate(16, (uint32)isr0);
	setIdtGate(17, (uint32)isr0);
	setIdtGate(18, (uint32)isr0);
	setIdtGate(19, (uint32)isr0);
	setIdtGate(20, (uint32)isr0);
	setIdtGate(21, (uint32)isr0);
	setIdtGate(22, (uint32)isr0);
	setIdtGate(23, (uint32)isr0);
	setIdtGate(24, (uint32)isr0);
	setIdtGate(25, (uint32)isr0);
	setIdtGate(26, (uint32)isr0);
	setIdtGate(27, (uint32)isr0);
	setIdtGate(28, (uint32)isr0);
	setIdtGate(29, (uint32)isr0);
	setIdtGate(30, (uint32)isr0);
	setIdtGate(31, (uint32)isr0);
	setIdtRegister();
}

void isr0()
{
	csString("0");
	asm("hlt");
}

void isr1()
{
	csString("0");
	asm("hlt");
}
void isr2()
{
	csString("0");
	asm("hlt");
}
void isr3()
{
	csString("0");
	asm("hlt");
}
void isr4()
{
	csString("0");
	asm("hlt");
}
void isr5()
{
	csString("0");
}
void isr6()
{
	csString("0");
}
void isr7()
{
	csString("0");
}
void isr8()
{
	csString("0");
}
void isr9()
{
	csString("0");
}
void isr10()
{
	csString("0");
}
void isr11()
{
	csString("0");
}
void isr12()
{
	csString("0");
}
void isr13()
{
	csString("0");
}
void isr14()
{
	csString("0");
}
void isr15()
{
	csString("0");
}
void isr16()
{
	csString("0");
}
void isr17()
{
	csString("0");
}
void isr18()
{
	csString("0");
}
void isr19()
{
	csString("0");
}
void isr20()
{
	csString("0");
}
void isr21()
{
	csString("0");
}
void isr22()
{
	csString("0");
}
void isr23()
{
	csString("0");
}
void isr24()
{
	csString("0");
}
void isr25()
{
	csString("0");
}
void isr26()
{
	csString("0");
}
void isr27()
{
	csString("0");
}
void isr28()
{
	csString("0");
}
void isr29()
{
	csString("0");
}
void isr30()
{
	csString("0");
}
void isr31()
{
	csString("0");
}
