#include <pebble.h>
#include "Memory.h"
#include "SceneBase.h"

static uint8_t __heap[0x0400];

int main(void) {
	Memory_Initialise( &__heap, sizeof( __heap ) );

	xiSceneBase_t * const sceneBase = SceneBase_Init( SceneBase_Alloc() );
	if ( sceneBase ) {
		app_event_loop();

		Object_Release( sceneBase );
	}
	
	return 0;
}