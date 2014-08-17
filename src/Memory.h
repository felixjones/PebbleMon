#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "Bool.h"

#define NULLPTR	( ( void * )0 )

void	Memory_Initialise( void * const memoryBlock, const size_t memoryLength );
bool_t	Memory_IsAllocated( const void * const ptr );
void *	Memory_Calloc( const size_t num, const size_t size );
void	Memory_Free( const void * ptr );
void *	Memory_Alloc( size_t size );
void *	Memory_Realloc( void * ptr, size_t size );

#endif