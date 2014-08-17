#include "Object.h"
#include "Memory.h"

uint8_t heap[0x100000];

int main() {
	Memory_Initialise( &heap, sizeof( heap ) );

	/*xiObject_t stack;
	xiObject_t * const object = Object_Init( &stack );
	Object_Release( object );*/

	xiObject_t * const object = Object_Init( Object_Alloc() );
	Object_Release( object );

	return 1;
}