#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "intdef.h"

typedef void ( * dealloc_t )( const xiObject_t * const self );

typedef struct xiObject_s	xiObject_t;
typedef struct xiObject_s {
	int8_t	retainCount;

	struct {
		dealloc_t	Dealloc_f;
	} __vtable;
} xiObject_t;

xiObject_t *	Object_Alloc();
void			Object_Dealloc( const xiObject_t * const self );
xiObject_t *	Object_Init( xiObject_t * const self );
void			Object_Retain( const void * const self );
void			Object_Release( const void * const self );

#endif