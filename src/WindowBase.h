#ifndef __WINDOW_BASE_H__
#define __WINDOW_BASE_H__

#include "Object.h"

typedef struct xiWindowBase_s {
	xiObject_t	super;

	struct {
		uint8_t	x;
		uint8_t	y;
		uint8_t	width;
		uint8_t	height;
	} rect;
} xiWindowBase_t;

xiWindowBase_t *	WindowBase_Alloc();
xiWindowBase_t *	WindowBase_Init( xiWindowBase_t * const self, const uint8_t x, const uint8_t y, const uint8_t width, const uint8_t height );

#endif