#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

#include "SceneBase.h"
#include "WindowBase.h"

typedef struct xiSceneTitle_s {
	xiSceneBase_t	super;

	xiWindowBase_t	windowBase;
} xiSceneTitle_t;

xiSceneTitle_t *	SceneTitle_Alloc();
void				SceneTitle_Dealloc( xiSceneTitle_t * const self )
xiSceneTitle_t *	SceneTitle_Init( xiSceneTitle_t * const self );

#endif