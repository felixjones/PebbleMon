#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stdint.h>

typedef struct xiObject_s {
	int8_t	retainCount;
} xiObject_t;

xiObject_t *	Object_Alloc();
void			Object_Dealloc( const xiObject_t * const self );
xiObject_t *	Object_Init( xiObject_t * const self );
void			Object_Retain( const xiObject_t * const self );
void			Object_Release( const xiObject_t * const self );

#endif