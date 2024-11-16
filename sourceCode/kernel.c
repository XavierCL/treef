#include "isr.h"
#include "keyboard.h"
#include "asmFunctions.h"
#include "ram.h"
#include "string.h"

void kernelMain()
{
	csStringConst("Loading...\n");
	csString("maxRam:\n");
	csString(uintegerToString(maxRam, (char*)0x1000));
	csChar('\n');
	loadISR();
	csStringConst("Welcome to Treef!\n");
	char* command;
	while(1)
	{
		csStringConst("treef/root>");
		command=getString();
		if(stringEquals(command, "halt"))
		{
			csStringConst("Computer halting...\n");
			asm("hlt");
		}
		else if(stringEquals(command, "clear"))
		{
			csClear();
		}
		else if(stringEquals(command, "reboot"))
		{
			csStringConst("Computer rebooting...\n");
			reboot();
		}
		else if(stringEquals(command, "help"))
		{
			csHelp();
		}
		else
		{
			csStringConst("Command not found\n");
		}
	}
}
