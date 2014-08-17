#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

typedef struct xiSceneBase_s	xiSceneBase_t;

void			SceneManager_Return(); // Pops scene
void			SceneManager_Goto( xiSceneBase_t * const scene ); // Clears stack, pushes scene
void			SceneManager_Call( xiSceneBase_t * const scene ); // Pushes scene
void			SceneManager_Exit(); // Clears stack
xiSceneBase_t *	SceneManager_Scene(); // Returns top scene

#endif