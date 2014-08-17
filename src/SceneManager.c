#include "SceneManager.h"

#include <pebble.h>
#include "SceneBase.h"
#include "Memory.h"

typedef struct sceneList_s	sceneList_t;
typedef struct sceneList_s {
	xiSceneBase_t *	scene;
	sceneList_t *	previous;
} sceneList_t;

static sceneList_t *	stackTop = NULLPTR;

void SceneManager_Run() {
	if ( stackTop ) {
		SceneBase_Update( stackTop->scene );
	}
}

void SceneManager_Return() {
	window_stack_pop( TRUE );

	if ( stackTop ) {
		sceneList_t * const newTop = stackTop->previous;

		Object_Release( stackTop->scene );
		Memory_Free( stackTop );

		stackTop = newTop;
	}
}

void SceneManager_Goto( xiSceneBase_t * const scene ) {
	window_stack_pop_all( TRUE );

	Object_Retain( scene );
	
	while ( stackTop ) {
		sceneList_t * const newTop = stackTop->previous;

		Object_Release( stackTop->scene );
		Memory_Free( stackTop );

		stackTop = newTop;
	}
	
	stackTop = Memory_Alloc( sizeof( sceneList_t ) );
	stackTop->scene = scene;
	stackTop->previous = NULLPTR;
}

void SceneManager_Call( xiSceneBase_t * const scene ) {
	window_stack_push( ( Window * )scene->pebble.native, TRUE );

	Object_Retain( scene );

	sceneList_t * const newTop = Memory_Alloc( sizeof( sceneList_t ) );
	newTop->scene = scene;
	newTop->previous = stackTop;

	stackTop = newTop;
}

void SceneManager_Exit() {
	window_stack_pop_all( FALSE );

	while ( stackTop ) {
		sceneList_t * const newTop = stackTop->previous;

		Object_Release( stackTop->scene );
		Memory_Free( stackTop );

		stackTop = newTop;
	}
}

xiSceneBase_t * SceneManager_Scene() {
	return stackTop->scene;
}
