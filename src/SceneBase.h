#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "Object.h"

typedef struct xiSceneBase_s {
	xiObject_t	super;

	struct {
		void *	native;
	} pebble;
} xiSceneBase_t;

xiSceneBase_t * SceneBase_Alloc();
xiSceneBase_t *	SceneBase_Init( xiSceneBase_t * const self );

#endif