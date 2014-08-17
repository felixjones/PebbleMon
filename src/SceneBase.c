#include "SceneBase.h"

#include <pebble.h>
#include "Memory.h"

static void SceneBase_Draw( xiSceneBase_t * const self, GContext * ctx ) {
	if ( self->__vtable.Draw_f ) {
		self->__vtable.Draw_f( self, ctx );
	}
}

static void SceneBase_LayerUpdate( Layer * me, GContext * ctx ) {
	xiSceneBase_t * const self = ( xiSceneBase_t * )layer_get_data( me );
	SceneBase_Draw( self, ctx );
}

void SceneBase_Dealloc( xiSceneBase_t * const self ) {
	layer_destroy( ( Layer * )self->pebble.drawLayer );
	window_destroy( ( Window * )self->pebble.native );

	Object_Dealloc( ( xiObject_t * )self );
}

xiSceneBase_t * SceneBase_Alloc() {
	return Memory_Alloc( sizeof( xiSceneBase_t ) );
}

xiSceneBase_t * SceneBase_Init( xiSceneBase_t * const self ) {
	Object_Init( ( xiObject_t * )self );
	
	APP_LOG( APP_LOG_LEVEL_INFO, "SceneBase_Init" );

	self->pebble.native = window_create();

	Layer * const nativeLayer = window_get_root_layer( ( Window * )self->pebble.native );
	const GRect bounds = layer_get_frame( nativeLayer );
	
	Layer * const drawLayer = layer_create_with_data( bounds, sizeof( self ) );
	memcpy( layer_get_data( drawLayer ), self, sizeof( self ) );
	
	layer_set_update_proc( drawLayer, SceneBase_LayerUpdate );
	layer_add_child( nativeLayer, drawLayer );
	
	self->pebble.drawLayer = drawLayer;

	self->__vtable.Update_f = NULLPTR;
	self->__vtable.Draw_f = NULLPTR;

	return self;
}

void SceneBase_Update( xiSceneBase_t * const self ) {
	APP_LOG( APP_LOG_LEVEL_INFO, "SceneBase_Update called" );

	if ( self->__vtable.Update_f ) {
		self->__vtable.Update_f( self );
	}
}
