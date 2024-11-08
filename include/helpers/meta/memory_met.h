

#ifndef MEM_METADATA
#define MEM_METADATA

#include "../../utils/common_libs.h"


typedef struct {
    uintptr_t __next_addr;
    size_t __used;  // using to dump memory status
    size_t __size;
    size_t __meta_size;
    void *__pool;
} Memory;


inline void _set_mem_size(Memory* mem_m_obj, size_t size){
    mem_m_obj->__size = size;
}
inline void _set_mem_used(Memory* mem_m_obj, size_t size){
    mem_m_obj->__used = size;
}
inline void _set_mem_next_addr(Memory* mem_m_obj, uintptr_t addr){
    mem_m_obj->__next_addr = addr;
}
inline void _set_mem_pool(Memory* mem_m_obj, void* pool){
    mem_m_obj->__pool = pool;
}
inline void _set_mem_meta_size(Memory* mem_m_obj, size_t size){
    mem_m_obj->__meta_size = size;
}

inline size_t _get_mem_size(Memory* mem_m_obj){
    return mem_m_obj->__size;
}
inline size_t _get_mem_used(Memory* mem_m_obj){
    return mem_m_obj->__used;
}
inline size_t _get_mem_meta_size(Memory* mem_m_obj){
    return mem_m_obj->__meta_size;
}

inline uintptr_t _get_mem_next_addr(Memory* mem_m_obj){
    return mem_m_obj->__next_addr;
}
inline void* _get_mem_pool(Memory* mem_m_obj){
    return mem_m_obj->__pool;
}


#endif
