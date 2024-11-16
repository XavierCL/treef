#include "screen.h"

void csInit()
{
	csColor=csMakeColor(COLOR_LIGHT_GREY, COLOR_BLACK);
	csBuffer=(short*)0xB8000;
	csClear();
}

char csMakeColor(const char font, const char back)
{
	return font | (back << 4);
}

short csMakeEntry(const char character, const char color)
{
	return (short)character | ((short)color << 8);
}

void csSetColor(char color)
{
	csColor=color;
}

void csClear()
{
	csRow=0;
	csColumn=0;
	int bufferCounter=0;
	const short emptyEntry=csMakeEntry(' ', csColor);
	const int bufferTotalSize=CS_WIDTH*CS_HEIGHT;
	while(bufferCounter<bufferTotalSize)
	{
		csBuffer[bufferCounter]=emptyEntry;
		++bufferCounter;
	}
}

void csHelp()
{
	csString("reboot: reboot computer\n");
	csString("halt: stop processor\n");
	csString("clear: clear console\n");
	csString("help: display help\n");
}

void csScrollDown()
{
	int counter=0;
	const int bufferTotalSize=CS_WIDTH*(CS_HEIGHT-1);
	while(counter<bufferTotalSize)
	{
		csBuffer[counter]=csBuffer[counter+CS_WIDTH];
		++counter;
	}
	while(counter<bufferTotalSize+CS_WIDTH)
	{
		csBuffer[counter]=' ';
		++counter;
	}
}

void csUpdateCursor()
{
	uint32 cursorBuffer=csRow*CS_WIDTH+csColumn;
	outport(0x3D4, 14);
	outport(0x3D5, cursorBuffer>>8);
	outport(0x3D4, 15);
	outport(0x3D5, cursorBuffer);
}

void csCharAt(const char character, const int x, const int y)
{
	csBuffer[y*CS_WIDTH+x]=csMakeEntry(character, csColor);
}

char csGetCharAt(const int x, const int y)
{
	return csBuffer[y*CS_WIDTH+x];
}

void csChar(const char character)
{
	if(character==8)
	{
		if(csRow*CS_WIDTH+csColumn!=csBackLimit)
		{
			if(csColumn!=0)
			{
				--csColumn;
				csCharAt(' ', csColumn, csRow);
			}
			else if(csRow!=0)
			{
				csColumn=CS_WIDTH-1;
				--csRow;
				while(csGetCharAt(csColumn, csRow)==' ')--csColumn;
				csCharAt(' ', csColumn, csRow);
			}
		}
	}
	else if(character=='\n')
	{
		csCharAt(0, csColumn, csRow);
		csColumn=0;
		++csRow;
		if(csRow==CS_HEIGHT)
		{
			csScrollDown();
			--csRow;
		}
	}
	else
	{
		csCharAt(character, csColumn, csRow);
		++csColumn;
		if(csColumn==CS_WIDTH)
		{
			csColumn=0;
			++csRow;
			if(csRow==CS_HEIGHT)
			{
				csScrollDown();
				--csRow;
			}
		}
	}
	csUpdateCursor();
}

void csString(const char* data)
{
	int counter=0;
	while(data[counter]!=0)
	{
		csChar(data[counter]);
		++counter;
	}
}

void csStringConst(const char* data)
{
	csString(data);
	csBackLimit=csRow*CS_WIDTH+csColumn;
}
