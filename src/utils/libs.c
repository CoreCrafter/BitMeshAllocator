
#include "../../include/api/alloc_api/libs.h"


void *gen_allocate(size_t size, const char *err_msg){
    void* mem = (void*)(malloc(size));
    if (!mem){
        throwErr(err_msg);
    }
    return mem;
}

void gen_free(void* sys_ptr){
    free(sys_ptr);
}

void* _write_safe(void* source, void* destination, size_t size){
    return memmove(destination, source, size);
}

void* _write_data(void* source, void* destination, size_t size){
    return memcpy(destination, source, size);
}