#ifndef __WINDOW_BASE_H__
#define __WINDOW_BASE_H__

#include "Object.h"

typedef struct xiProcess_s {
	xiObject_t	super;
} xiProcess_t;

xiProcess_t *	Process_Alloc();
xiProcess_t *	Process_Init( xiProcess_t * const self );

#endif