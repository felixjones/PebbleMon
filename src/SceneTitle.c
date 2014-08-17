#include "SceneTitle.h"

#include <pebble.h>
#include "Memory.h"

static void SceneTitle_Draw( xiSceneTitle_t * const self, GContext * ctx ) {
	APP_LOG( APP_LOG_LEVEL_INFO, "Drawing window" );
	WindowBase_Draw( &self->windowBase, self->super.pebble.drawLayer );
}

static void SceneTitle_Update( xiSceneTitle_t * const self ) {
}

void SceneTitle_Dealloc( xiSceneTitle_t * const self ) {
	Object_Release( &self->windowBase );

	SceneBase_Dealloc( ( xiSceneBase_t * )self );
}

xiSceneTitle_t * SceneTitle_Alloc() {
	return Memory_Alloc( sizeof( xiSceneTitle_t ) );
}

xiSceneTitle_t * SceneTitle_Init( xiSceneTitle_t * const self ) {
	SceneBase_Init( ( xiSceneBase_t * )self );
	
	APP_LOG( APP_LOG_LEVEL_INFO, "SceneTitle_Init" );

	WindowBase_Init( &self->windowBase, 32, 32, 64, 64 );

	self->super.__vtable.Draw_f = ( sceneDraw_t )SceneTitle_Draw;
	self->super.__vtable.Update_f = ( sceneUpdate_t )SceneTitle_Update;

	return self;
}
