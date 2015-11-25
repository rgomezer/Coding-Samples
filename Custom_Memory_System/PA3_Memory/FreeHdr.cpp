#include "freeHdr.h"

freeHdr::freeHdr()
{

	freeNext = 0;		// next free block
	freePrev = 0;		// prev free block
	blockSize = 1;		// size of block
	blockType = 0xcc;		// block type is used -> 0xAA  if block type is free -> 0xCC
	pad0=0;			// future use
	pad1=0;			// future use
	pad2=0;
}