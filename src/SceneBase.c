#include "SceneBase.h"

#include <pebble.h>
#include "Memory.h"

static void SceneBase_Dealloc( xiSceneBase_t * const self ) {
	window_destroy( ( Window * )self->pebble.native );

	Object_Dealloc( ( xiObject_t * )self );
}

xiSceneBase_t * SceneBase_Alloc() {
	return Memory_Alloc( sizeof( xiSceneBase_t ) );
}

xiSceneBase_t * SceneBase_Init( xiSceneBase_t * const self ) {
	Object_Init( ( xiObject_t * )self );

	self->pebble.native = window_create();
	self->__vtable.Update_f = NULLPTR;

	return self;
}

void SceneBase_Update( xiSceneBase_t * const self ) {
	if ( self->__vtable.Update_f ) {
		self->__vtable.Update_f( self );
	}
}