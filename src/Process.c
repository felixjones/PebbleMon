#include "Process.h"

#include "Memory.h"

static void Process_Dealloc( xiProcess_t * const self ) {
	// Cleanup

	Object_Dealloc( ( xiObject_t * )self );
}

xiProcess_t * Process_Alloc() {
	return Memory_Alloc( sizeof( xiProcess_t ) );
}

xiProcess_t * Process_Init( xiProcess_t * const self ) {
	Object_Init( ( xiObject_t * )self );

	self->super.__vtable.Dealloc_f = &Process_Dealloc;

	// Startup
}
