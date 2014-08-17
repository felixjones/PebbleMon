#include <pebble.h>
#include "Memory.h"
#include "SceneManager.h"
#include "SceneBase.h"

static uint8_t __heap[0x0400];

void Update( struct tm * tick_time, TimeUnits units_changed ) {
	if ( SceneManager_Scene() == NULLPTR ) {
		xiSceneBase_t * const sceneBase = SceneBase_Init( SceneBase_Alloc() );
		if ( sceneBase ) {
			SceneManager_Goto( sceneBase );
			Object_Release( sceneBase );
		}
	}

	SceneManager_Run();
}

int main() {
	Memory_Initialise( &__heap, sizeof( __heap ) );
	
	tick_timer_service_subscribe( SECOND_UNIT, &Update );

	app_event_loop();
	
	tick_timer_service_unsubscribe();
	
	return 0;
}