#include <pebble.h>
#include "Memory.h"
#include "SceneManager.h"
#include "SceneBase.h"

static uint8_t __heap[0x0400];

void Update( struct tm * tick_time, TimeUnits units_changed ) {
	if ( SceneManager_Scene() == NULLPTR ) {
		APP_LOG( APP_LOG_LEVEL_INFO, "Starting base scene" );
		xiSceneBase_t * const sceneBase = SceneBase_Init( SceneBase_Alloc() );
		if ( sceneBase ) {
			SceneManager_Goto( sceneBase );
			Object_Release( sceneBase );
		}
	}

	APP_LOG( APP_LOG_LEVEL_INFO, "Update called" );

	SceneManager_Run();
}

int main() {
	Memory_Initialise( &__heap, sizeof( __heap ) );
	APP_LOG( APP_LOG_LEVEL_INFO, "Initialised memory" );

	tick_timer_service_subscribe( SECOND_UNIT, &Update );

	app_event_loop();
	
	tick_timer_service_unsubscribe();
	
	APP_LOG( APP_LOG_LEVEL_INFO, "Shutting down" );

	return 0;
}