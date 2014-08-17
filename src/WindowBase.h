#ifndef __WINDOW_BASE_H__
#define __WINDOW_BASE_H__

#include "Object.h"

struct GContext;
typedef struct GContext GContext;
typedef struct xiWindowBase_s	xiWindowBase_t;
typedef void ( * draw_t )( xiWindowBase_t * const self, GContext * const ctx );

typedef struct xiWindowBase_s {
	xiObject_t	super;

	struct {
		uint8_t	x;
		uint8_t	y;
		uint8_t	width;
		uint8_t	height;
	} rect;
	
	struct {
		draw_t	Draw_f;
	} __vtable;
} xiWindowBase_t;

xiWindowBase_t *	WindowBase_Alloc();
xiWindowBase_t *	WindowBase_Init( xiWindowBase_t * const self, const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height );
void				WindowBase_Draw( xiWindowBase_t * const self, GContext * const ctx );

#endif