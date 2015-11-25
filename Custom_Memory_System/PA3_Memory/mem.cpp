#include <new>
#include <assert.h>
#include "mem.h"
#include "heapHdr.h"
#include "freeHdr.h"
#include "usedHdr.h"
#include "output.h"

#define ALIGNMENT_PAD (16)
#define MIN_SIZE (sizeof(freeHdr) + 16)


memSystem::~memSystem()
{
	delete [] rawMem;
}


heapHdr *memSystem::getHeap()
{
	return heap;
}

memSystem::memSystem()
{
	// now initialize it.
	heap = 0;
	rawMem = 0;

	// create the memory block for the heap
	char *p_raw = new char[HEAP_SIZE+ALIGNMENT_PAD];

	// update the pointer
	rawMem = p_raw;

	// Correct pointer to make sure it's 16 byte aligned
	char *p_corrected = (char *) ( ((memU32)p_raw + (16-1) ) & ~(16-1) );   

	// instantiate the heap header on the raw memory
	heapHdr *p = new(p_corrected) heapHdr(p_corrected);

	// update it
	heap = p;


}

memVoid memSystem::InitializeSystem( )
{
	freeHdr *pFreeHdr = new(this->heap->stats.heapTopAddr) freeHdr();
	pFreeHdr->blockType = 0xCC;
	pFreeHdr->blockSize = (memU32)this->heap->stats.heapBottomAddr - (memU32)this->heap->stats.heapTopAddr - sizeof(freeHdr);

	this->heap->freeHead = pFreeHdr;
	this->heap->usedHead = 0;
	this->heap->heapInitialize = 1;

	this->heap->stats.peakNumUsed = 0;
	this->heap->stats.peakUsedMemory = 0;

	this->heap->stats.currNumUsedBlocks = 0;
	this->heap->stats.currUsedMem = 0;

	this->heap->stats.currNumFreeBlocks = 1;
	this->heap->stats.currFreeMem = pFreeHdr->blockSize;

	this->heap->stats.sizeHeap = (memU32)this->heap->stats.heapBottomAddr - (memU32)this->heap->stats.heapTopAddr + sizeof(heapHdr);
	this->heap->stats.sizeHeapHeader = sizeof(heapHdr);
}

memVoid memSystem::Free( memVoid * const data )
{
	if (data != 0)
	{
		usedHdr* usedBlock = (usedHdr*)data - 1;
		memBool aFree = usedBlock->aboveBlockFree;
		freeHdr *bottom = (freeHdr*)((char *)usedBlock + sizeof(freeHdr) + usedBlock->blockSize);

		this->privRemoveUsedBlock(usedBlock); //calls helper functions to remove from list

		memU32 tempSize = usedBlock->blockSize;
		freeHdr * block = new(usedBlock)freeHdr();
		block->blockSize = tempSize;

		privInsertFreeBlock(block);

		// Leaving address at the end

		memVoid *topPtr = (char *)block + sizeof(freeHdr) + block->blockSize - sizeof(memU32 *);

		memset(topPtr, 0x00, sizeof(memVoid *));
		memcpy(topPtr, &usedBlock, sizeof(memVoid *));

		//updating stats
		this->heap->stats.currNumUsedBlocks--;
		this->heap->stats.currUsedMem -= block->blockSize;

		this->heap->stats.currNumFreeBlocks++;
		this->heap->stats.currFreeMem += block->blockSize;

		if (this->heap->stats.currNumUsedBlocks > this->heap->stats.peakNumUsed)
		{
			this->heap->stats.peakNumUsed = this->heap->stats.currNumUsedBlocks;
		}

		//update peakUsedMemory if needed
		if (this->heap->stats.currUsedMem > this->heap->stats.peakUsedMemory)
		{
			this->heap->stats.peakUsedMemory = this->heap->stats.currUsedMem;
		}

		if (bottom->blockType == 0xCC)
		{
			if (bottom != this->heap->stats.heapBottomAddr)
			{
				this->privCoalese(block, bottom);
			}

		}
		if (aFree)
		{
			int *aboveAddress = (int*)((char*)block - sizeof(memVoid*));

			int x = *aboveAddress;

			int *topTemp;
			topTemp = reinterpret_cast<int*>(x);

			freeHdr *top = (freeHdr *)topTemp;

			this->privCoalese(top, block);
		}

		//if bottom is free
		if (bottom->blockType == 0xAA)
		{
			if (bottom != this->heap->stats.heapBottomAddr)
			{
				usedHdr *usedBottom = (usedHdr*)bottom;
				usedBottom->aboveBlockFree = 1;
			}
		}

	}

	//printf("Size of Free Head %X\n", sizeof(heap->freeHead));
}

memVoid * memSystem::Malloc( const memU32 size )
{
	memVoid *out = 0; // single exit return
	memU32 cSize = ((size + (16 - 1)) & ~(16 - 1));   //adjust to 16 byte align

	//early out if given size 0 or if the size is too big
	if (cSize <= 0 || cSize > this->heap->stats.currFreeMem)
	{
		out = 0;
	}
	else
	{
		freeHdr *pFreeHdr = this->heap->freeHead;
		while (pFreeHdr != 0)
		{
			if (pFreeHdr->blockSize >= size)
			{
				out = pFreeHdr + 1;// + sizeof(freeHdr);

				this->privRemoveFreeBlock(pFreeHdr);

				break;
				//make a split function later
			}
			pFreeHdr = pFreeHdr->freeNext;
		}

		
		if (out)
		{
			//split returns the use header, get the address of the block to return
			usedHdr *temp = this->privSplitUsedBlock(pFreeHdr, cSize);
			out = (char *)((char *)temp + sizeof(usedHdr));
		}
	}

	return out;
}

memVoid memSystem::dump()
{

	fprintf(io::getHandle(),"\n------- DUMP -------------\n\n");

	fprintf(io::getHandle(),"heapStart: 0x%p     \nheapEnd:   0x%p \n\n",heap, heap->stats.heapBottomAddr);
	fprintf(io::getHandle(),"usedHead:  0x%p     \nfreeHead:  0x%p \n\n", heap->usedHead, heap->freeHead );

	fprintf(io::getHandle(),"Heap Hdr   s: %p  e: %p                            size: 0x%x \n",(memU32)heap->stats.heapTopAddr-sizeof(heapHdr), heap->stats.heapTopAddr, heap->stats.sizeHeapHeader);

	memU32 p = (memU32) heap->stats.heapTopAddr;

	char *type;
	char *typeHdr;

	while( p < (memU32)heap->stats.heapBottomAddr )
	{
		usedHdr *used = (usedHdr *)p;
		if( used->blockType == 0xAA )
		{
			typeHdr = "USED HDR ";
			type    = "USED     ";
		}
		else
		{
			typeHdr = "FREE HDR ";
			type    = "FREE     ";
		}

		memU32 hdrStart = (memU32)used;
		memU32 hdrEnd   = (memU32)used + sizeof(usedHdr);
		fprintf(io::getHandle(),"%s  s: %p  e: %p  p: %p  n: %p  size: 0x%x    AF: %d \n",typeHdr, hdrStart, hdrEnd, used->usedPrev, used->usedNext, sizeof(usedHdr), used->aboveBlockFree );
		memU32 blkStart = hdrEnd;
		memU32 blkEnd   = blkStart + used->blockSize; 
		fprintf(io::getHandle(),"%s  s: %p  e: %p                            size: 0x%x \n",type, blkStart, blkEnd, used->blockSize );

		p = blkEnd;
	
	}
}

memVoid memSystem::privRemoveFreeBlock(freeHdr *block)
{
	//Only item in list
	if (this->heap->freeHead->freeNext == 0 && this->heap->freeHead == block)
	{
		this->privRemoveOnlyFree(block);
	}
	//if it is the middle case
	else if (block->freeNext != 0 && block->freePrev != 0)
	{
		this->privRemoveFree(block);
	}

	//Head case
	else if (block == this->heap->freeHead)
	{
		this->privRemoveFreeHead(block);
	}

	//Tail case
	else if (block->freeNext == 0 && block->freePrev)
	{
		this->privRemoveFreeTail(block);
	}
}

memVoid memSystem::privRemoveFree(freeHdr * block)
{
	block->freePrev->freeNext = block->freeNext;
	block->freeNext->freePrev = block->freePrev;
	block->freePrev = 0;
	block->freeNext = 0;
}

memVoid memSystem::privRemoveOnlyFree(freeHdr * block)
{
	//this->heap->freeHead->freePrev = 0;
	//this->heap->freeHead->freeNext = 0;
	this->heap->freeHead = 0;
	block->freePrev = 0;
	block->freeNext = 0;
}

memVoid memSystem::privRemoveFreeHead(freeHdr * block)
{
	this->heap->freeHead = block->freeNext;
	this->heap->freeHead->freePrev = 0;
	block->freePrev = 0;
	block->freeNext = 0;
}

memVoid memSystem::privRemoveFreeTail(freeHdr * block)
{
	block->freePrev->freeNext = 0;
	block->freePrev = 0;
	block->freeNext = 0;
}

/************************ END: HELPERS TO REMOVE FROM FREE LIST *************************/



/************************ HELPERS TO ADD TO FREE LIST **********************************/

memVoid memSystem::privInsertFreeBlock(freeHdr *block)
{
	freeHdr *iterator = this->heap->freeHead;
	freeHdr *itPrev = 0;
	freeHdr *next = 0;
	//add to free list
	if (this->heap->stats.currNumFreeBlocks == 0 || iterator == 0)
	{
		this->privInsertOnlyFree(block);
	}
	else
	{
		while (iterator)
		{
			if (block < iterator)
			{
				next = iterator;
				break;
			}
			itPrev = iterator;
			iterator = iterator->freeNext;
		}

		if (iterator == this->heap->freeHead)
		{
			this->privInsertFreeHead(block);
		}
		else if (iterator == 0)
		{
			this->privInsertFreeTail(block, itPrev);
		}
		else if (iterator->freePrev)
		{
			this->privInsertFree(block, iterator);
		}


	}
}

memVoid memSystem::privInsertFree(freeHdr * block, freeHdr *next)
{
	block->freePrev = next->freePrev;
	block->freeNext = next;
	next->freePrev = block;
	block->freePrev->freeNext = block;
}

memVoid memSystem::privInsertOnlyFree(freeHdr * block)
{
	block->freeNext = 0;
	block->freePrev = 0;
	this->heap->freeHead = block;

}

memVoid memSystem::privInsertFreeHead(freeHdr * block)
{
	block->freeNext = this->heap->freeHead;
	block->freePrev = 0;
	block->freeNext->freePrev = block;
	this->heap->freeHead = block;
}

memVoid memSystem::privInsertFreeTail(freeHdr * block, freeHdr *tail)
{
	block->freeNext = 0;
	block->freePrev = tail;
	tail->freeNext = block;
}

/********************** END: HELPERS TO ADD TO FREE LIST ***************************************/



/********************** HELPERS TO REMOVE FROM USED LIST **************************************/

memVoid memSystem::privRemoveUsedBlock(usedHdr * block)
{
	//removed from used lsit
	if (this->heap->usedHead == block && block->usedNext == 0)
	{
		this->privRemoveOnlyUsed(block);
	}
	else if (block->usedPrev == 0)
	{
		this->privRemoveUsedHead(block);
	}
	else if (block->usedNext == 0)
	{
		this->privRemoveUsedTail(block);
	}
	else if (block->usedNext != 0 && block->usedPrev != 0)
	{
		this->privRemoveUsed(block);
	}
}

memVoid memSystem::privRemoveUsed(usedHdr * block)
{
	block->usedPrev->usedNext = block->usedNext;
	block->usedNext->usedPrev = block->usedPrev;
	block->usedNext = 0;
	block->usedPrev = 0;
}

memVoid memSystem::privRemoveOnlyUsed(usedHdr * block)
{
	this->heap->usedHead = 0;
	block->usedNext = 0;
	block->usedPrev = 0;
}

memVoid memSystem::privRemoveUsedHead(usedHdr * block)
{
	if (block)
	{
		this->heap->usedHead = block->usedNext;
		this->heap->usedHead->usedPrev = 0;
		block->usedNext = 0;
		block->usedPrev = 0;
	}
}

memVoid memSystem::privRemoveUsedTail(usedHdr * block)
{
	block->usedPrev->usedNext = 0;
	block->usedNext = 0;
	block->usedPrev = 0;
}

/************************** END: HELPERS TO REMOVE FROM USED LIST ****************************/

//This function adds a used block into the front
memVoid memSystem::privInsertUsedHead(usedHdr * block)
{
	block->usedPrev = 0;
	block->usedNext = this->heap->usedHead;
	if (block->usedNext)
	{
		block->usedNext->usedPrev = block;
	}
	this->heap->usedHead = block;
}

//This function combines two free blocks if they are adjacent to each other
memVoid memSystem::privCoalese(freeHdr* top, freeHdr* bottom)
{
	this->privRemoveFreeBlock(top);
	this->privRemoveFreeBlock(bottom);

	this->heap->stats.currNumFreeBlocks -= 2;

	top->blockSize += bottom->blockSize;
	top->blockSize += sizeof(freeHdr);

	memVoid *topPtr = (char *)top + sizeof(freeHdr) + top->blockSize - sizeof(memU32 *);

	memset(topPtr, 0x00, sizeof(memVoid *));
	memcpy(topPtr, &top, sizeof(memVoid *));

	this->privInsertFreeBlock(top);
	this->heap->stats.currNumFreeBlocks += 1;
	this->heap->stats.currFreeMem += sizeof(freeHdr);
}


usedHdr * memSystem::privSplitUsedBlock(freeHdr *block, memU32 size)
{
	usedHdr *blockOut = 0;
	memU32 nSize;

	if ((block->blockSize - size) > MIN_SIZE) // theres enough space to make a free block so split it
	{
		nSize = block->blockSize - size;

		usedHdr *uBlock = new(block)usedHdr(); // create header for first block
		uBlock->blockSize = size;
		this->privInsertUsedHead(uBlock);

		//create header for the free block

		char *dist = (char*)(uBlock)+sizeof(usedHdr) + uBlock->blockSize;
		freeHdr *nBlock = new(dist)freeHdr();
		nBlock->blockSize = nSize - sizeof(freeHdr);
		this->privInsertFreeBlock(nBlock);

		this->heap->stats.currNumUsedBlocks++;
		this->heap->stats.currUsedMem += uBlock->blockSize;

		this->heap->stats.currFreeMem = this->heap->stats.currFreeMem - uBlock->blockSize - sizeof(freeHdr);
		//this->heap->stats.currNumFreeBlocks++;

		blockOut = uBlock;
	}
	else //otherwise just create the used block
	{
		usedHdr *uBlock = new(block)usedHdr(); // create header for first block
		uBlock->blockSize = size;
		this->privInsertUsedHead(uBlock);

		//update stats
		this->heap->stats.currNumUsedBlocks++;
		this->heap->stats.currUsedMem += uBlock->blockSize;

		this->heap->stats.currNumFreeBlocks--;
		this->heap->stats.currFreeMem -= uBlock->blockSize;
		blockOut = uBlock;

	}

	//update peakNumber used if needed
	if (this->heap->stats.currNumUsedBlocks > this->heap->stats.peakNumUsed)
	{
		this->heap->stats.peakNumUsed = this->heap->stats.currNumUsedBlocks;
	}

	//update peakUsedMemory if needed
	if (this->heap->stats.currUsedMem > this->heap->stats.peakUsedMemory)
	{
		this->heap->stats.peakUsedMemory = this->heap->stats.currUsedMem;
	}
	return blockOut;
}
