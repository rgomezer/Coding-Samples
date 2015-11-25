#include "UnitTest.h"
#include "output.h"
#include "mem.h"
#include "usedHdr.h"
#include "freeHdr.h"

#define PTR_FIX(x)  (x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 



TEST( Allocate_3_100_Top_Down_free , MemoryShakeOut )
{
	io::create("Rodolfo Gomez", "Test13.txt");

	fprintf(io::getHandle(),"Test13: \n\n");

	fprintf(io::getHandle()," 1) used                                              \n");
	fprintf(io::getHandle()," 2) used                                              \n");
	fprintf(io::getHandle()," 3) used     (make sure it's consumes 100 percent of heap)             \n");

   	fprintf(io::getHandle()," 4) top down   \n\n");


	fprintf(io::getHandle(),"     memSystem mem;                     \n");
	fprintf(io::getHandle(),"     mem.InitializeSystem();            \n");

   	fprintf(io::getHandle(),"     void *a = mem.Malloc( 0x4280 );       \n");
   	fprintf(io::getHandle(),"     void *b = mem.Malloc( 0x4280 );       \n");
	fprintf(io::getHandle(),"     void *c = mem.Malloc( 0x4290 );       \n");
       
	fprintf(io::getHandle(),"     mem.dump();                        \n");
	fprintf(io::getHandle(),"     mem.Free( a );                     \n");
	fprintf(io::getHandle(),"     mem.dump();                        \n");
	fprintf(io::getHandle(),"     mem.Free( b );                     \n");
	fprintf(io::getHandle(),"     mem.dump();                        \n");
	fprintf(io::getHandle(),"     mem.Free( c );                     \n");
	fprintf(io::getHandle(),"     mem.dump();                        \n");

	// Part A:
	memSystem mem1;
	mem1.InitializeSystem();

   	void *a1 = mem1.Malloc( 0x4280 );
   	void *b1 = mem1.Malloc( 0x4280 );
	void *c1 = mem1.Malloc( 0x4290 );

	mem1.dump();

	// Part B:
	mem1.Free( a1 );
	mem1.dump();

	// Part C:
	mem1.Free( b1 );
	mem1.dump();

	// Part D:
	mem1.Free( c1 );
	mem1.dump();

	io::destroy();



	// ----  GENERAL CHECK ------------------------------------------------------

	// ---- Part A: -------------------------------------------------------------
	
	memSystem mem;
	mem.InitializeSystem();

   	void *a = mem.Malloc( 0x4280 );
   	void *b = mem.Malloc( 0x4280 );
	void *c = mem.Malloc( 0x4290 );


	// ---- Verify A: -----------------------------------------------------------

		heapHdr *h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), HEAP_SIZE );

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->freeHead), 0x0);
		CHECK_EQUAL( PTR_FIX(h->usedHead), 0x8560 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->stats.peakNumUsed, 3 );
		CHECK_EQUAL( h->stats.peakUsedMemory, 0xc790);

		CHECK_EQUAL( h->stats.currNumUsedBlocks, 3);
		CHECK_EQUAL( h->stats.currUsedMem, 0xc790);
		
		CHECK_EQUAL( h->stats.currNumFreeBlocks, 0 );
		CHECK_EQUAL( h->stats.currFreeMem, 0x0 );

		CHECK_EQUAL( h->stats.sizeHeap, 0xc800 );
		CHECK_EQUAL( h->stats.sizeHeapHeader, 0x40 );

		CHECK_EQUAL( PTR_FIX( h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), 0xc800 );


	// ---- Heap Walk ------------------------------------------------------

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (memU32)h->stats.heapTopAddr-sizeof(heapHdr) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), h->stats.sizeHeapHeader );
		// HeapHdr Size
		CHECK_EQUAL( h->stats.sizeHeapHeader, sizeof(heapHdr) );

	// ----  Block walk ------------------------------------------------------
		
		memU32 hdrStart;
		memU32 hdrEnd;
		memU32 blkStart;
		memU32 blkEnd; 

	// ---- USED HDR 1 -------------------------------------------

		// Check type
		usedHdr *used = (usedHdr *) h->stats.heapTopAddr;
		// Should be USED
		CHECK_EQUAL( (int)used->blockType, 0xAA );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x40  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x50 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0x42d0);
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- USED BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x42d0);
		CHECK_EQUAL( used->blockSize, 0x4280 );
	
	// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (usedHdr *) blkEnd;
		// Should be USED
		CHECK_EQUAL( (int)used->blockType, 0xAA );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x42d0 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x42e0 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0x8560 );
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0x40 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- used BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x8560);
		CHECK_EQUAL( used->blockSize, 0x4280 );

	// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (usedHdr *) blkEnd;
		// Should be USED
		CHECK_EQUAL( (int)used->blockType, 0xAA );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x8560 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x8570 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0);
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0x42d0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- used BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( used->blockSize, 0x4290 );

	// ---- Part B: -------------------------------------------------------------
	
	mem.Free( a );
	
	// ---- Verify B: -----------------------------------------------------------


		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), HEAP_SIZE );

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->freeHead), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->usedHead), 0x8560 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->stats.peakNumUsed, 3 );
		CHECK_EQUAL( h->stats.peakUsedMemory, 0xc790);

		CHECK_EQUAL( h->stats.currNumUsedBlocks, 2);
		CHECK_EQUAL( h->stats.currUsedMem, 0xc790 - 0x4280 );
		
		CHECK_EQUAL( h->stats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->stats.currFreeMem, 0x4280 );

		CHECK_EQUAL( h->stats.sizeHeap, 0xc800 );
		CHECK_EQUAL( h->stats.sizeHeapHeader, 0x40 );

		CHECK_EQUAL( PTR_FIX( h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), 0xc800 );


	// ---- Heap Walk ------------------------------------------------------

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (memU32)h->stats.heapTopAddr-sizeof(heapHdr) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), h->stats.sizeHeapHeader );
		// HeapHdr Size
		CHECK_EQUAL( h->stats.sizeHeapHeader, sizeof(heapHdr) );

	// ----  Block walk ------------------------------------------------------


	// ---- HDR 1 -------------------------------------------

		// Check type
		freeHdr *free = (freeHdr *) h->stats.heapTopAddr;
		CHECK_EQUAL( (int)free->blockType, 0xcc );
		
		hdrStart = (memU32)free;
		hdrEnd   = (memU32)free + sizeof(freeHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x40  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x50 );
		// Prev
		CHECK_EQUAL( PTR_FIX(free->freePrev), 0x0 );
		// Next
		CHECK_EQUAL( PTR_FIX(free->freeNext), 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(freeHdr) );
	
	// ---- BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + free->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x42d0 );
		CHECK_EQUAL( free->blockSize, 0x4280 );
	
	// ---- HDR 2 -------------------------------------------

		// Check type
		used = (usedHdr *) blkEnd;
		// Should be USED
		CHECK_EQUAL( (int)used->blockType, 0xaa );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x42d0 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x42e0 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0x8560 );
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- Free BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x8560 );
		CHECK_EQUAL( used->blockSize, 0x4280 );

	// ---- Hdr 3 -------------------------------------------

		// Check type
		used = (usedHdr *) blkEnd;
		// Should be free
		CHECK_EQUAL( (int)used->blockType, 0xaa );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x8560 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x8570 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0x0 );
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0x42d0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- Used Block ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( used->blockSize, 0x4290 );
	
	
	// ---- Part C: -------------------------------------------------------------
	
	mem.Free( b );
	
	// ---- Verify C: -----------------------------------------------------------


		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), HEAP_SIZE );

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->freeHead), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->usedHead), 0x8560 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->stats.peakNumUsed, 3 );
		CHECK_EQUAL( h->stats.peakUsedMemory, 0xc790);

		CHECK_EQUAL( h->stats.currNumUsedBlocks, 1);
		CHECK_EQUAL( h->stats.currUsedMem, 0x4290);
		
		CHECK_EQUAL( h->stats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->stats.currFreeMem, 0x8510 );

		CHECK_EQUAL( h->stats.sizeHeap, 0xc800 );
		CHECK_EQUAL( h->stats.sizeHeapHeader, 0x40 );

		CHECK_EQUAL( PTR_FIX( h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), 0xc800 );


		// ---- Heap Walk ------------------------------------------------------

		// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (memU32)h->stats.heapTopAddr-sizeof(heapHdr) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), h->stats.sizeHeapHeader );
		// HeapHdr Size
		CHECK_EQUAL( h->stats.sizeHeapHeader, sizeof(heapHdr) );

	// ----  Block walk ------------------------------------------------------


	// ---- HDR 1 -------------------------------------------

		// Check type
		free = (freeHdr *) h->stats.heapTopAddr;
		CHECK_EQUAL( (int)free->blockType, 0xcc );
		
		hdrStart = (memU32)free;
		hdrEnd   = (memU32)free + sizeof(freeHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x40  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x50 );
		// Prev
		CHECK_EQUAL( PTR_FIX(free->freePrev), 0x0 );
		// Next
		CHECK_EQUAL( PTR_FIX(free->freeNext), 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(freeHdr) );
	
	// ---- BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + free->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x8560 );
		CHECK_EQUAL( free->blockSize, 0x8510 );
	
	// ---- HDR 2 -------------------------------------------

		// Check type
		used = (usedHdr *) blkEnd;
		CHECK_EQUAL( (int)used->blockType, 0xaa );
		
		hdrStart = (memU32)used;
		hdrEnd   = (memU32)used + sizeof(usedHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x8560 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x8570 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->usedPrev), 0);
		// Next
		CHECK_EQUAL( PTR_FIX(used->usedNext), 0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(usedHdr) );
	
	// ---- Used Block ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( used->blockSize, 0x4290 );
	
	
	// ---- Part D: -------------------------------------------------------------
	
	mem.Free( c );
	
	// ---- Verify D: -----------------------------------------------------------


		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), HEAP_SIZE );

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->freeHead), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->usedHead), 0x0 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->stats.peakNumUsed, 3 );
		CHECK_EQUAL( h->stats.peakUsedMemory, 0xc790 );

		CHECK_EQUAL( h->stats.currNumUsedBlocks, 0);
		CHECK_EQUAL( h->stats.currUsedMem, 0x0 );
		
		CHECK_EQUAL( h->stats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->stats.currFreeMem, 0xc7b0 );

		CHECK_EQUAL( h->stats.sizeHeap, 0xc800 );
		CHECK_EQUAL( h->stats.sizeHeapHeader, 0x40 );

		CHECK_EQUAL( PTR_FIX( h->stats.heapTopAddr), 0x40 );
		CHECK_EQUAL( PTR_FIX(h->stats.heapBottomAddr), 0xc800 );


	// ---- Heap Walk ------------------------------------------------------

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (memU32)h->stats.heapTopAddr-sizeof(heapHdr) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->stats.heapTopAddr), h->stats.sizeHeapHeader );
		// HeapHdr Size
		CHECK_EQUAL( h->stats.sizeHeapHeader, sizeof(heapHdr) );

	// ----  Block walk ------------------------------------------------------


	// ---- FREE HDR 1 -------------------------------------------

		// Check type
		free = (freeHdr *) h->stats.heapTopAddr;
		// Should be free
		CHECK_EQUAL( (int)free->blockType, 0xCC );
		
		hdrStart = (memU32)free;
		hdrEnd   = (memU32)free + sizeof(freeHdr);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x40  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x50 );
		// Prev
		CHECK_EQUAL( PTR_FIX(free->freePrev), 0x0 );
		// Next
		CHECK_EQUAL( PTR_FIX(free->freeNext), 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(freeHdr) );
	
	// ---- free BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + free->blockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x40 + 0x10 + 0xc7b0);
		CHECK_EQUAL( free->blockSize, 0xc7b0 );
	

}

