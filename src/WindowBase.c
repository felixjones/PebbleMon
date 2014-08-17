#include "WindowBase.h"

#include <string.h>
#include <pebble.h>
#include "Memory.h"

static GBitmap *	windowSkin = NULLPTR;
static uint8_t		windowSkinReferences = 0;

static void WindowBase_Dealloc( xiWindowBase_t * const self ) {
	windowSkinReferences--;
	if ( windowSkinReferences == 0 ) {
		gbitmap_destroy( windowSkin );
	}

	Object_Dealloc( ( xiObject_t * )self );
}

xiWindowBase_t * WindowBase_Alloc() {
	return Memory_Alloc( sizeof( xiWindowBase_t ) );
}

xiWindowBase_t * WindowBase_Init( xiWindowBase_t * const self, const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height ) {
	Object_Init( ( xiObject_t * )self );
	
	self->rect.x = x;
	self->rect.y = y;
	self->rect.width = width;
	self->rect.height = height;

	if ( windowSkinReferences == 0 ) {
		windowSkin = gbitmap_create_with_resource( RESOURCE_WINDOW_SKIN );
	}
	windowSkinReferences++;

	return self;
}
