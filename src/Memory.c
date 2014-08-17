#include "Memory.h"

#include <string.h>
#include <pebble.h>

typedef struct allocator_s {
	void *	start;
	size_t	size;
	size_t	usedMemory;
	size_t	numAllocations;
} allocator_t;

typedef struct allocationHeader_s {
	size_t	size;
	uint8_t	adjustment;
	void *	selfPtr;
} allocationHeader_t;

typedef struct freeBlock_s	freeBlock_t;
typedef struct freeBlock_s {
	size_t			size;
	freeBlock_t *	next;
} freeBlock_t;

typedef struct freeListAllocator_s {
	allocator_t		super;
	freeBlock_t *	freeBlocks;
	size_t			alignment;
} freeListAllocator_t;

static freeListAllocator_t	allocator;

static __inline void * AlignForward( void * const address, const uint8_t alignment ) {
	const uintptr_t ptrUInt = ( uintptr_t )address;
	const uintptr_t algnUInt = ( uintptr_t )( alignment - 1 );
	const uintptr_t nalgnUInt = ( uintptr_t )( ~( alignment - 1 ) );

	return ( void * )( ( ptrUInt + algnUInt ) & ( nalgnUInt ) );
}

static __inline uint8_t AlignForwardAdjustment( const void * const address, const uint8_t alignment ) {
	const uintptr_t ptrUInt = ( uintptr_t )address;
	const uintptr_t algnUInt = ( uintptr_t )( alignment - 1 );
    const uint8_t adjustment =  alignment - ( ptrUInt & algnUInt );
    
    if ( adjustment == alignment ) {
        return 0; // Already aligned
	}
    
    return adjustment;
}

static __inline uint8_t AlignForwardAdjustmentWithHeader( const void * const address, const uint8_t alignment, const uint8_t headerSize ) {
	uint8_t adjustment = AlignForwardAdjustment( address, alignment );
	uint8_t neededSpace = headerSize;
    
	if ( adjustment < neededSpace )	{
		neededSpace -= adjustment;
		
		// Increase adjustment to fit header
		adjustment += alignment * ( neededSpace / alignment );
		
		if ( neededSpace % alignment > 0 ) {
			adjustment += alignment;
		}
	}

	return adjustment;
}

static size_t Memory_SizeOf( const void * const ptr ) {
	if ( ptr == NULLPTR ) {
		return 0;
	}

	uintptr_t p = ( uintptr_t )ptr;
	allocationHeader_t * header = ( allocationHeader_t * )( p - sizeof( allocationHeader_t ) );

	return header->size;
}

void Memory_Initialise( void * const memoryBlock, const size_t memoryLength ) {
	allocator.super.start = memoryBlock;
	allocator.super.size = memoryLength;
	allocator.super.usedMemory = 0;
	allocator.super.numAllocations = 0;

	allocator.alignment = sizeof( void * );
	allocator.freeBlocks = memoryBlock;
	allocator.freeBlocks->size = memoryLength;
	allocator.freeBlocks->next = NULLPTR;
}

bool_t Memory_IsAllocated( const void * const ptr ) {
	if ( ptr == NULLPTR ) {
		return FALSE;
	}

	uintptr_t p = ( uintptr_t )ptr;
	allocationHeader_t * header = ( allocationHeader_t * )( p - sizeof( allocationHeader_t ) );

	return ( header->selfPtr == ptr );
}

void * Memory_Alloc( size_t size ) {
	if ( size == 0 ) { 
		return NULLPTR;
	}

	freeBlock_t * prevFreeBlock = NULLPTR;
	freeBlock_t * freeBlock = allocator.freeBlocks;

	while ( freeBlock != NULLPTR ) {
		// Calculate adjustment needed to keep object correctly aligned
		uint8_t adjustment = AlignForwardAdjustmentWithHeader( freeBlock, allocator.alignment, sizeof( allocationHeader_t ) );

		size_t totalSize = size + adjustment;

		// If allocation doesn't fit in this FreeBlock, try the next
		if ( freeBlock->size < totalSize ) {
			prevFreeBlock = freeBlock;
			freeBlock = freeBlock->next;
			continue;
		}
		
		// If allocations in the remaining memory will be impossible
		if ( freeBlock->size - totalSize <= sizeof( allocationHeader_t ) ) {
			// Increase allocation size instead of creating a new FreeBlock
			totalSize = freeBlock->size;

			if ( prevFreeBlock != NULLPTR ) {
				prevFreeBlock->next = freeBlock->next;
			} else {
				allocator.freeBlocks = freeBlock->next;
			}
		} else {
			// Else create a new FreeBlock containing remaining memory
			freeBlock_t * nextBlock = ( freeBlock_t * )( freeBlock + ( ptrdiff_t )totalSize );
			nextBlock->size = freeBlock->size - totalSize;
			nextBlock->next = freeBlock->next;
			
			if ( prevFreeBlock != NULLPTR ) {
				prevFreeBlock->next = nextBlock;
			} else {
				allocator.freeBlocks = nextBlock;
			}
		}

		uintptr_t alignedAddress = ( uintptr_t )freeBlock + ( ptrdiff_t )adjustment;
	
		allocationHeader_t * header = ( allocationHeader_t * )( alignedAddress - sizeof( allocationHeader_t ) );
		header->size = totalSize;
		header->adjustment = adjustment;
		header->selfPtr = ( void * )alignedAddress;

		allocator.super.usedMemory += totalSize;
		allocator.super.numAllocations++;

		return ( void * )alignedAddress;
	}

	return NULLPTR;
}

void Memory_Free( const void * ptr ) {
	if ( ptr == NULLPTR ) {
		return;
	}

	app_log( APP_LOG_LEVEL_INFO, __FILE__, __LINE__, "Freeing pointer %p", ptr );

	uintptr_t p = ( uintptr_t )ptr;
	allocationHeader_t * header = ( allocationHeader_t * )( p - sizeof( allocationHeader_t ) );
	
	app_log( APP_LOG_LEVEL_INFO, __FILE__, __LINE__, "Pointer ID'd as %p", header->selfPtr );

	if ( header->selfPtr != ptr ) {
		// Error attempting to free non existant pointer???
		return;
	}
	app_log( APP_LOG_LEVEL_INFO, __FILE__, __LINE__, "Removing self reference" );
	header->selfPtr = NULLPTR;
	
	uintptr_t blockStart = p - header->adjustment;
	size_t blockSize = header->size;
	uintptr_t blockEnd = blockStart + blockSize;

	freeBlock_t * prevFreeBlock = NULLPTR;
	freeBlock_t * freeBlock = allocator.freeBlocks;

	while ( freeBlock != NULLPTR ) {
		if ( ( uintptr_t )freeBlock >= blockEnd ) {
			break;
		}

		prevFreeBlock = freeBlock;
		freeBlock = freeBlock->next;
	}

	if ( prevFreeBlock == NULLPTR ) {
		prevFreeBlock = ( freeBlock_t * )blockStart;
		prevFreeBlock->size = blockSize;
		prevFreeBlock->next = allocator.freeBlocks;

		allocator.freeBlocks = prevFreeBlock;
	} else if ( ( uintptr_t )prevFreeBlock + prevFreeBlock->size == blockStart ) {
		prevFreeBlock->size += blockSize;
	} else {
		freeBlock_t * temp = ( freeBlock_t * )blockStart;
		temp->size = blockSize;
		temp->next = prevFreeBlock->next;
		prevFreeBlock->next = temp;

		prevFreeBlock = temp;
	}

	if ( freeBlock != NULLPTR && ( uintptr_t )freeBlock == blockEnd ) {
		prevFreeBlock->size += freeBlock->size;
		prevFreeBlock->next = freeBlock->next;
	}

	allocator.super.numAllocations--;
	allocator.super.usedMemory -= blockSize;
}

void * Memory_Calloc( const size_t num, const size_t size ) {
	const size_t allocLen = num * size;

	void * const ptr = Memory_Alloc( allocLen );
	memset( ptr, 0, allocLen );

	return ptr;
}

void * Memory_Realloc( void * ptr, size_t size ) {
	if ( !ptr || size == 0 || Memory_IsAllocated( ptr ) == FALSE ) {
		return NULLPTR;
	}
	
	const size_t oldLen = Memory_SizeOf( ptr );
	if ( oldLen == 0 ) {
		return NULLPTR;
	}

	void * const newPtr = Memory_Alloc( size );

	memcpy( newPtr, ptr, oldLen );

	Memory_Free( ptr );

	return newPtr;
}
