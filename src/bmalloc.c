

#include "../include/c_alloc.h"

static unsigned short __init__ = 0;

void allocate_memory(void** var_ptr, size_t size){
    if (size < 1){
        throwErr(OBJ_MEM_SIZE_ERR);
    }
    if (!__init__){
    	throwErr(MEM_INIT_ERR);
    }
    __alloc_mem(var_ptr, size);
}

void deallocate_all() {
    __Dealloc_ALL();
}

void destroy() {
    __Destroy_ALL();
    __init__ = 0;
}


void initial_heap_memory(size_t total_size){
    if (total_size < 1){
        throwErr(MEM_SIZE_ERR);
    }
    __init__ = 1;
    __Initial_memory(total_size);
    
}

void deallocate_memory(void** var_ptr) {
    __Dealloc(var_ptr);
}



