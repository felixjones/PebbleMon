#if !defined( WIN32 )
	#include <pebble.h>
#endif

#include "Object.h"
#include "Memory.h"

static uint8_t __heap[0x0400];

int main() {
	Memory_Initialise( &__heap, sizeof( __heap ) );

	/*xiObject_t stack;
	xiObject_t * const object = Object_Init( &stack );
	Object_Release( object );*/

	xiObject_t * const object = Object_Init( Object_Alloc() );
	if ( object ) {
		Object_Release( object );
	}

	return 1;
}