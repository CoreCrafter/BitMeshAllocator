#ifndef MEM_ALLOC_PROC
#define MEM_ALLOC_PROC

#include "meta/memory_met.h"
#include "meta/memory_obj_met.h"
#include "../utils/errors/handle_err.h"
#include "../utils/common_libs.h"
#include "../api/alloc_api/libs.h"

static void compact_allocate(void** var_ptr, size_t object_size);
static void _add_to_list(MemObject* _obj);
static MemObject* _create_meta();
void __Dealloc(void** var_ptr);
void __Initial_memory(size_t total_size);
void __alloc_mem(void** var_ptr, size_t size);
void __Dealloc_ALL();
void __Destroy_ALL();

#endif
