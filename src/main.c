#include "Object.h"
#include "Memory.h"

static unsigned char heap[0x100];

int main() {
	Memory_Initialise( &heap, sizeof( heap ) );

	/*xiObject_t stack;
	xiObject_t * const object = Object_Init( &stack );
	Object_Release( object );*/

	xiObject_t * const object = Object_Init( Object_Alloc() );
	if ( object ) {
		Object_Release( object );
	}

	return 1;
}