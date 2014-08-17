#include <pebble.h>

static Window * window;
static TextLayer *hello_layer;

static void Window_Load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

	hello_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
	text_layer_set_text(hello_layer, "Hello world");
	text_layer_set_text_alignment(hello_layer, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(hello_layer));
}

static void Window_Unload(Window *window) {
	text_layer_destroy(hello_layer);
}

static void Init() {
	window = window_create();
	window_set_window_handlers( window, ( WindowHandlers ){ .load = Window_Load, .unload = Window_Unload } );
	
	const bool animated = true;
	window_stack_push(window, animated);
}

static void Deinit() {
  window_destroy(window);
}

void main() {
	Init();

	APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed watchface helloworld: %p", window);

	app_event_loop();
	Deinit();
}