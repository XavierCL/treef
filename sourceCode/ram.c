#include "ram.h"

uint32 ramSetup(multibootInfo* biosInfo)
{
	maxRam=biosInfo->mem_upper;
	ramDscTableSize=maxRam*sizeof(ramPageDsc)/PAGE_SIZE;
	uint32 freeSize=0;
	multibootMemoryMap* mmap = (multibootMemoryMap*)biosInfo->mmap_addr;
	while(mmap<(multibootMemoryMap*)(biosInfo->mmap_addr+biosInfo->mmap_length))
	{
		/*csString(uintegerToString(mmap->base_addr_low, (char*)0x1000));
		csString("->");
		csString(uintegerToString(mmap->length_low, (char*)0x1000));
		csChar(':');
		csString(uintegerToString(mmap->type, (char*)0x1000));
		csChar(' ');*/
		if(mmap->type==1)
		{
			if(freeSize+mmap->length_low>=STACK_SIZE)
			{
				mmap = (multibootMemoryMap*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
				stackEnd=mmap->base_addr_low;
				break;
			}
			freeSize+=mmap->length_low;
		}
		else freeSize=0;
		mmap=(multibootMemoryMap*)((unsigned int)mmap+mmap->size+sizeof(unsigned int));
	}
	freeSize=0;
	while(mmap<(multibootMemoryMap*)(biosInfo->mmap_addr+biosInfo->mmap_length))
	{
		if(mmap->type==1)
		{
			if(freeSize+mmap->length_low>=ramDscTableSize)
			{
				mmap=(multibootMemoryMap*)((unsigned int)mmap+mmap->size+sizeof(unsigned int));
				ramDscTable=(ramPageDsc*)(mmap->base_addr_low-ramDscTableSize);
				break;
			}
			freeSize+=mmap->length_low;
		}
		else freeSize=0;
		mmap = (multibootMemoryMap*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
	}
	return stackEnd;
}

void ramInit(multibootInfo* biosInfo)
{
	//initialize the memory manager to right value by iterating in the biosinfos
	uint32 pageIndex=0;
	while(pageIndex*PAGE_SIZE<((multibootMemoryMap*)biosInfo->mmap_addr)->base_addr_low)
	{
		ramDscTable[pageIndex].size=0;
		++pageIndex;
	}
	multibootMemoryMap* mmap=(multibootMemoryMap*)(biosInfo->mmap_addr);
	while(mmap<(multibootMemoryMap*)(biosInfo->mmap_addr+biosInfo->mmap_length))
	{
		while(pageIndex*PAGE_SIZE>mmap->base_addr_low)
		{
			mmap = (multibootMemoryMap*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
		}
		if(mmap->type!=1)
		{
			ramDscTable[pageIndex].size=0;
			++pageIndex;
			while(pageIndex*PAGE_SIZE<mmap->base_addr_low+mmap->length_low)
			{
				ramDscTable[pageIndex].size=0;
				++pageIndex;
			}
		}
		else
		{
			uint32 upperLimit=mmap->base_addr_low+mmap->length_low;
			while(pageIndex<upperLimit)
			{
				//beacoup trop lent
				ramDscTable[pageIndex].size=1;
				pageIndex+=PAGE_SIZE;
			}
		}
	}
	csString("\ninit done");
	asm("hlt");
	int32 pageCount;
	while(pageIndex-->1)
	{
		pageCount=0;
		while(pageIndex>0 && ramDscTable[pageIndex].size==ramDscTable[pageIndex-1].size)
		{
			--pageIndex;
			++pageCount;
		}
		ramDscTable[pageIndex].size=pageCount*(ramDscTable[pageIndex].size*2-1);
	}
	
	ramNewAt((uint32)ramDscTable, ramDscTableSize);
	ramNewAt(stackEnd-STACK_SIZE, STACK_SIZE);
}

uint32 ramNew(uint32 bytes)
{
	if(bytes==0)return null;
	uint32 index=0;
	int32 pages=(bytes-1)/PAGE_SIZE+1;
	while(index<ramDscTableSize)
	{
		//if(ramDscTable[index].size==0)csString("\n\nlol, segmentation fault!\nPas supposé, ram.c ligne ~106\n\n");
		if(ramDscTable[index].size>=pages)
		{
			if(ramDscTable[index].size!=pages)ramDscTable[index+ramDscTable[index].size*sizeof(ramPageDsc)].size=ramDscTable[index].size-pages;//set next descriptor to point on the remaining free space
			ramDscTable[index].size=pages;
			return PAGE_SIZE*index;
		}
		index+=abs(ramDscTable[index].size);
	}
	return null;
}

//merge allocated as if it was free, bypass rights
void ramNewAt(uint32 address, uint32 bytes)
{
	uint32 index=address/PAGE_SIZE;
	address=index;
	int32 pages=(bytes-1)/PAGE_SIZE+1;
	int32 previousIndex;
	while(ramDscTable[index--].size==0);
	if(ramDscTable[index].size<0)
	{
		previousIndex=index;
		ramDscTable[index].size=-address-pages+index;
		ramDscTable[address].size=0;
	}
	else
	{
		previousIndex=address;
		ramDscTable[index].size=address-index;
		ramDscTable[address].size=pages;
	}
	index=address+pages;
	while(ramDscTable[index--].size==0);
	if(ramDscTable[index].size>0)ramDscTable[address+pages].size=ramDscTable[index].size+index-address-pages;
	else ramDscTable[previousIndex].size-=index-address-pages;
	while(index++>address)ramDscTable[index].size=0;
}

void ramDel(uint32 address)
{
	//change 0s for whatever and iterate from first element to look for reconstitution
	uint32 index=address/PAGE_SIZE;
	if(ramDscTable[index].size>0)
	{
		int32 afterSize=0;
		if(ramDscTable[index+ramDscTable[index].size*sizeof(ramPageDsc)].size>0)
		{
			afterSize=ramDscTable[index+ramDscTable[index].size*sizeof(ramPageDsc)].size;
			ramDscTable[index+ramDscTable[index].size*sizeof(ramPageDsc)].size=0;
		}
		uint32 seekPrevious=index-1;
		if(index==stackEnd)
		{
			index=ramDscTable[index].size+afterSize;
		}
		else
		{
			while(ramDscTable[seekPrevious].size==0)--seekPrevious;
			if(ramDscTable[seekPrevious].size>0)
			{
				ramDscTable[seekPrevious].size=ramDscTable[seekPrevious].size+ramDscTable[index].size+afterSize;
			}
			else
			{
				ramDscTable[index].size=ramDscTable[index].size+afterSize;
			}
		}
	}
}
