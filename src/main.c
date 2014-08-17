#if !defined( WIN32 )
	#include <pebble.h>
#endif

#include "Object.h"
#include "Memory.h"

static uint8_t __heap[0x0400];

static Window *window;
static TextLayer *hello_layer;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  hello_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(hello_layer, "Hello world");
  text_layer_set_text_alignment(hello_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(hello_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(hello_layer);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed watchface helloworld: %p", window);

  Memory_Initialise( &__heap, sizeof( __heap ) );


	xiObject_t * const object = Object_Init( Object_Alloc() );
	if ( object ) {
		Object_Release( object );
	}

  app_event_loop();
  deinit();
}