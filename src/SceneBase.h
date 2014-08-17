#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include "Object.h"

typedef struct xiSceneBase_s	xiSceneBase_t;
typedef void	( * update_t )( xiSceneBase_t * const self );

typedef struct xiSceneBase_s {
	xiObject_t	super;

	struct {
		void *	native;
		void *	drawLayer;
	} pebble;

	struct {
		update_t	Update_f;
		update_t	Draw_f;
	} __vtable;
} xiSceneBase_t;

xiSceneBase_t * SceneBase_Alloc();
xiSceneBase_t *	SceneBase_Init( xiSceneBase_t * const self );
void			SceneBase_Update( xiSceneBase_t * const self );

#endif