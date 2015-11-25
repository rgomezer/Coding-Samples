#ifndef MEM_H
#define MEM_H

// forward declare
struct headHdr;

#include "heapHdr.h"

#define HEAP_SIZE ( (50 * 1024) )  //50K


class memSystem
{
public:
	memSystem();	
	~memSystem();
	heapHdr *getHeap();
	memVoid dump();

	// implement these functions
	memVoid Free( memVoid * const data );
	memVoid *Malloc(const memU32 size );
	memVoid InitializeSystem( );

private:
	heapHdr	*heap;
	char	*rawMem;

	//Helper functions for dealing with Free

	//helper functions for inserting a free 
	memVoid privInsertFreeBlock(freeHdr *block);
	memVoid privInsertFree(freeHdr *block, freeHdr *next);			//insert free block in middle
	memVoid privInsertOnlyFree(freeHdr * block);						//insert to empty list
	memVoid privInsertFreeHead(freeHdr * block);						//insert free block in begining
	memVoid privInsertFreeTail(freeHdr * block, freeHdr *tail);		//insert free block in end

	//helper functions for removing from a free 
	memVoid privRemoveFreeBlock(freeHdr * p);				
	memVoid privRemoveFree(freeHdr * block);							//remove free block in middle
	memVoid privRemoveOnlyFree(freeHdr * block);						//remove last free block
	memVoid privRemoveFreeHead(freeHdr * block);						//remove free block in begining
	memVoid privRemoveFreeTail(freeHdr * block);						//remove free block in end


	//Helper functions for dealing with Used

	//helper functions for inserting a used 
	memVoid privInsertUsedBlock(usedHdr *block);
	memVoid privInsertUsed(usedHdr *block, usedHdr *next);			//insert free block in middle
	memVoid privInsertOnlyUsed(usedHdr * block);						//insert to empty list
	memVoid privInsertUsedHead(usedHdr * block);						//insert free block in begining
	memVoid privInsertUsedTail(usedHdr * block, usedHdr *tail);		//insert free block in end

	//helper functions for removing from a used
	memVoid privRemoveUsedBlock(usedHdr * block);
	memVoid privRemoveUsed(usedHdr * block);						//remove used block in middle
	memVoid privRemoveOnlyUsed(usedHdr * block);					//remove last used block
	memVoid privRemoveUsedHead(usedHdr * block);					//remove used block in begining
	memVoid privRemoveUsedTail(usedHdr * block);					//remove used block in end

	//Special functions
	usedHdr *privSplitUsedBlock(freeHdr *block, memU32 size);

	memVoid privCoalese(freeHdr* top, freeHdr* bottom);

};

#endif // mem.h