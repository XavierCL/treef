#include "string.h"

bool stringToInteger(char* charArray, int* integer)
{
	bool sign=1;
	*integer=0;
	if(*charArray=='-')
	{
		sign=0;
		++charArray;
	}
	while(*charArray)
	{
		if(*charArray>'9' || *charArray<'0')return false;
		*integer*=10;
		*integer+=((*charArray)-48);
		++charArray;
	}
	*integer*=sign*2-1;
	return true;
}

char* integerToString(int integer, char* charArray)
{
	if(integer==0)
	{
		charArray[0]='0';
		charArray[1]='\0';
		return charArray;
	}
	int index=0;
	if(integer<0)
	{
		charArray[0]='-';
		integer=-integer;
		++index;
	}
	int saveInt=integer;
	while(integer)
	{
		integer/=10;
		++index;
	}
	charArray[index]='\0';
	while(saveInt)
	{
		--index;
		charArray[index]=saveInt%10+48;
		saveInt/=10;
	}
	return charArray;
}

char* uintegerToString(uint32 integer, char* charArray)
{
	if(integer==0)
	{
		charArray[0]='0';
		charArray[1]='\0';
		return charArray;
	}
	uint32 index=0;
	uint32 saveInt=integer;
	while(integer)
	{
		integer/=10;
		++index;
	}
	charArray[index]='\0';
	while(saveInt)
	{
		--index;
		charArray[index]=saveInt%10+48;
		saveInt/=10;
	}
	return charArray;
}
