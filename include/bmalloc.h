
#ifndef MEM_INIT
#define MEM_INIT

#include "helpers/memory_helpers.h"
#include "utils/common_libs.h"
#include "utils/errors/handle_err.h"


void allocate_memory(void** var_ptr, size_t size);
void deallocate_all();
void initial_heap_memory(size_t total_size);
void deallocate_memory(void** var_ptr);
void destroy();

#endif
