#include "Object.h"

#include <string.h>
#include "Memory.h"

xiObject_t * Object_Alloc() {
	return ( xiObject_t * )Memory_Alloc( sizeof( xiObject_t ) );
}

void Object_Dealloc( const xiObject_t * const self ) {
	if ( self->__vtable.Dealloc_f ) {
		xiObject_t * const mutableSelf = ( xiObject_t * )self;

		mutableSelf->__vtable.Dealloc_f( self );
		mutableSelf->__vtable.Dealloc_f = NULLPTR;
	} else {
		Memory_Free( self );
	}
}

xiObject_t * Object_Init( xiObject_t * const self ) {
	if ( self ) {
		memset( self, 0, sizeof( *self ) );
		
		Object_Retain( self );
	}

	return self;
}

void Object_Retain( const xiObject_t * const self ) {
	xiObject_t * const mutableSelf = ( xiObject_t * )self;
	mutableSelf->retainCount++;
}

void Object_Release( const xiObject_t * const self ) {
	xiObject_t * const mutableSelf = ( xiObject_t * )self;
	mutableSelf->retainCount--;

	if ( self->retainCount == 0 ) {
		Object_Dealloc( self );
	}
}
