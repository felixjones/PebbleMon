#include <pebble.h>
#include "Memory.h"
#include "SceneManager.h"
#include "SceneBase.h"

static uint8_t		__heap[0x0400];

int main() {
	Memory_Initialise( &__heap, sizeof( __heap ) );
	APP_LOG( APP_LOG_LEVEL_INFO, "Initialised memory" );
	
	APP_LOG( APP_LOG_LEVEL_INFO, "Starting base scene" );
	xiSceneBase_t * const sceneBase = SceneBase_Init( SceneBase_Alloc() );
	if ( sceneBase ) {
		SceneManager_Call( sceneBase );
		Object_Release( sceneBase );
	}

	app_event_loop();
	
	APP_LOG( APP_LOG_LEVEL_INFO, "Shutting down" );
	SceneManager_Exit();

	Memory_DetectLeaks();
	return 0;
}
