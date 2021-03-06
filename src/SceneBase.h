#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "Object.h"

struct GContext;
typedef struct GContext GContext;
typedef struct xiSceneBase_s	xiSceneBase_t;
typedef void	( * sceneUpdate_t )( xiSceneBase_t * const self );
typedef void	( * sceneDraw_t )( xiSceneBase_t * const self, GContext * ctx );

typedef struct xiSceneBase_s {
	xiObject_t	super;

	struct {
		void *	native;
		void *	drawLayer;
	} pebble;

	struct {
		sceneUpdate_t	Update_f;
		sceneDraw_t		Draw_f;
	} __vtable;
} xiSceneBase_t;

xiSceneBase_t * SceneBase_Alloc();
void			SceneBase_Dealloc( xiSceneBase_t * const self );
xiSceneBase_t *	SceneBase_Init( xiSceneBase_t * const self );
void			SceneBase_Update( xiSceneBase_t * const self );
void			SceneBase_Invalidate( xiSceneBase_t * const self );

#endif