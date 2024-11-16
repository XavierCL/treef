#include "keyboard.h"

int stringLength(char* charString)
{
	int numberChar=0;
	while(charString[numberChar])++numberChar;
	return numberChar;
}

bool stringEquals(char* charString1, char* charString2)
{
	int charCounter=0;
	while(charString1[charCounter]!=0 && charString2[charCounter]!=0)
	{
		if(charString1[charCounter]!=charString2[charCounter])return false;
		++charCounter;
	}
	return charString1[charCounter]==charString2[charCounter];
}

unsigned char getScanCode()
{
	char character=0;
	while(1)
	{
		character=inport(0x60);
		if(character!=csLastChar)
		{
			csLastChar=character;
			if(character>0)
			{
				return character;
			}
		}
	}
}

char getChar()
{
	return scanCode[getScanCode()];
}

char* getString()
{
	int length=0;
	char* charString;
	do
	{
		charString[length]=getChar();
		csChar(charString[length]);
		++length;
	}while(charString[length-1]!='\n');
	charString[length-1]=0;
	csString(charString);
	return charString;
}
