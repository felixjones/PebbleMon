#include <pebble.h>
#include "Memory.h"
#include "Process.h"

static uint8_t __heap[0x0400];

int main(void) {
	Memory_Initialise( &__heap, sizeof( __heap ) );

	xiProcess_t * const process = Process_Init( Process_Alloc() );
	if ( process ) {
		app_event_loop();

		Object_Release( process );
	}
}