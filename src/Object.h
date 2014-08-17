#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "intdef.h"

typedef struct xiObject_s	xiObject_t;
typedef struct xiObject_s {
	int8_t	retainCount;

	struct {
		void	( * Dealloc_f )( const xiObject_t * const self );
	} __vtable;
} xiObject_t;

xiObject_t *	Object_Alloc();
void			Object_Dealloc( const xiObject_t * const self );
xiObject_t *	Object_Init( xiObject_t * const self );
void			Object_Retain( const xiObject_t * const self );
void			Object_Release( const xiObject_t * const self );

#pragma No_Strict_Aliasing( xiObject_t )

#endif