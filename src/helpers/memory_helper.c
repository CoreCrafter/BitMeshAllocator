#include "../../include/helpers/memory_helpers.h"

static Memory *mem_pool_m_data = NULL;
static unsigned short _def_flag = 1;
static size_t mem_obj_size = 0;
static size_t _meta_size = 0;
static MemObject* first_live_obj_ptr = NULL;
static MemObject* last_live_obj_ptr = NULL;
static void* __f_hole_addr = NULL;
static MemObject* ___live_temp = NULL;


#define _ALLOC_LARGE_MEM(x) \
do { \
    size_t _size_of_meta = sizeof(Memory); \
    mem_pool_m_data = (Memory *)gen_allocate(_size_of_meta, MEMORY_ERR_MSG); \
    void* _pool = (void*)gen_allocate(x, MEMORY_ARR_ERR_MSG);\
    _set_mem_pool(mem_pool_m_data, _pool); \
    _set_mem_size(mem_pool_m_data,x); \
    _set_mem_used(mem_pool_m_data, 0); \
    _set_mem_meta_size(mem_pool_m_data, _size_of_meta);\
    _set_mem_next_addr(mem_pool_m_data, (uintptr_t)_pool); \
} while (0)

#define _RESET_MEM() \
    _set_mem_next_addr(mem_pool_m_data, \
        (uintptr_t)_get_mem_pool(mem_pool_m_data))

#define _REMOVE_FROM_LIVE_LIST(x) \
do { \
    if (!__f_hole_addr || (__f_hole_addr && (uintptr_t)x < (uintptr_t)__f_hole_addr)){ \
        __f_hole_addr = (void*)x; \
        ___live_temp = _get_mem_obj_next(x); \
    } \
    if (first_live_obj_ptr == last_live_obj_ptr){ \
        first_live_obj_ptr = NULL; \
        last_live_obj_ptr = NULL;\
        _RESET_MEM();\
    }\
    else if (x == first_live_obj_ptr){ \
        first_live_obj_ptr = _get_mem_obj_next(first_live_obj_ptr);\
        _set_mem_obj_prev(first_live_obj_ptr, NULL);\
        _set_mem_obj_next(x, NULL);\
    }\
    else if(x == last_live_obj_ptr){\
        last_live_obj_ptr = _get_mem_obj_prev(last_live_obj_ptr);\
        _set_mem_obj_next(last_live_obj_ptr, NULL);\
        _set_mem_obj_prev(x, NULL);\
        _set_mem_next_addr(mem_pool_m_data, (uintptr_t)_size_pack(last_live_obj_ptr)); \
    }\
    else {\
        MemObject* __prev = _get_mem_obj_prev(x);\
        MemObject* __next = _get_mem_obj_next(x);\
        _set_mem_obj_next(__prev, __next);\
        _set_mem_obj_prev(__next, __prev);\
    }\
} while(0)


#define _END_ADDR() \
     (uintptr_t)(_get_mem_pool(mem_pool_m_data)) + _get_mem_size(mem_pool_m_data)


#define _START_DEF() do { \
    _set_mem_next_addr(mem_pool_m_data, (uintptr_t)__f_hole_addr); \
    while (___live_temp){ \
        MemObject* ___live_temp_next = _get_mem_obj_next(___live_temp);\
        MemObject* ___live_temp_prev = _get_mem_obj_prev(___live_temp);\
        void** var_ptr = _get_mem_obj_assoc_var_ptr(___live_temp); \
        void* _meta_dest = _write_data((void*)___live_temp, (void*)_get_mem_next_addr(mem_pool_m_data), mem_obj_size);\
        MemObject* _current = (MemObject*)_meta_dest;\
        _set_mem_obj_prev(_current, ___live_temp_prev);\
        _set_mem_obj_next(_current, ___live_temp_next);\
        _set_mem_obj_assoc_var_ptr(_current, var_ptr); \
        if (___live_temp_prev){ \
            _set_mem_obj_next(___live_temp_prev, _current);\
        }\
        if (___live_temp_next){\
            _set_mem_obj_prev(___live_temp_next, _current);\
        }\
        _pool_addr_move_forward(mem_obj_size); \
        size_t obj_s = _get_mem_obj_size(_current); \
        void* _data_dest = _write_safe((void*)*var_ptr, (void*)_get_mem_next_addr(mem_pool_m_data), obj_s);\
        *var_ptr = _data_dest; \
        _pool_addr_move_forward(obj_s); \
        if (___live_temp == first_live_obj_ptr){\
            first_live_obj_ptr = _current;\
        }\
        if (___live_temp == last_live_obj_ptr){\
            last_live_obj_ptr = _current;\
        }\
        ___live_temp = ___live_temp_next; \
    } \
    _def_flag = 1; \
    __f_hole_addr = NULL; \
    ___live_temp = NULL; \
} while(0)

static inline size_t _size_pack(MemObject* x) {
   return ((uintptr_t)x + mem_obj_size + _get_mem_obj_size(x));
}

static inline void _inc_meta_used(size_t size) {
    _set_mem_meta_size(mem_pool_m_data, _get_mem_meta_size(mem_pool_m_data) + size);
}

static inline void _dec_meta_used(size_t size) {
    _set_mem_meta_size(mem_pool_m_data, _get_mem_meta_size(mem_pool_m_data) - size); 
}

static inline void _dec_used(size_t size) {
    _set_mem_used(mem_pool_m_data, _get_mem_used(mem_pool_m_data) - size);
}

static inline void _inc_used(size_t size) {
    _set_mem_used(mem_pool_m_data, _get_mem_used(mem_pool_m_data) + size);
}

static inline void _pool_addr_move_forward(size_t size) {
    _set_mem_next_addr(mem_pool_m_data, (uintptr_t)(_get_mem_next_addr(mem_pool_m_data) + size));
}

static inline void _pool_addr_move_backward(size_t size) {
    _set_mem_next_addr(mem_pool_m_data, (uintptr_t)(_get_mem_next_addr(mem_pool_m_data) - size));
}

static inline unsigned short _is_available(size_t size){
    return (_get_mem_next_addr(mem_pool_m_data)) + size + mem_obj_size <= (_END_ADDR());
}


static MemObject* _create_meta(){
    MemObject* meta = (MemObject*)_get_mem_next_addr(mem_pool_m_data);
    _inc_meta_used(mem_obj_size);
    _pool_addr_move_forward(mem_obj_size);
    return meta;
}


static void _add_to_list(MemObject* _obj){
    if (first_live_obj_ptr == NULL){
        first_live_obj_ptr = _obj;
    }
    if (last_live_obj_ptr){
        _set_mem_obj_next(last_live_obj_ptr, _obj); 
    }
    _set_mem_obj_prev(_obj, last_live_obj_ptr);  
    last_live_obj_ptr = _obj;
}

static void compact_allocate(void** var_ptr, size_t object_size) {
    MemObject* _new_obj = _create_meta();
    _set_mem_obj_size(_new_obj, object_size);
    _set_mem_obj_free_status(_new_obj, 0);
    _set_mem_obj_assoc_var_ptr(_new_obj, var_ptr);
    void* next_addr = (void*)_get_mem_next_addr(mem_pool_m_data); 
    *var_ptr = next_addr;
    _pool_addr_move_forward(object_size); 
    _inc_used(object_size);
    _add_to_list(_new_obj);
}

void __Destroy_ALL() {
    if (mem_pool_m_data){
        void* ___pool = (void*)_get_mem_pool(mem_pool_m_data);
        if (___pool){
            gen_free(___pool);
            _set_mem_pool(mem_pool_m_data, NULL);
            gen_free((void*)mem_pool_m_data);
            mem_pool_m_data = NULL;
        }
    }      
}

void __Dealloc_ALL(){
    MemObject* __temp = first_live_obj_ptr;
    while(__temp){
        __Dealloc(_get_mem_obj_assoc_var_ptr(__temp));
        __temp = _get_mem_obj_next(__temp);
    }
}

void __alloc_mem(void** var_ptr, size_t size){
    if (_is_available(size)){
        compact_allocate(var_ptr, size);
    }
    else if (_def_flag){
        throwErr(MEM_LIMIT);
    }
    else {
        _START_DEF();
        if (_is_available(size)){ 
            compact_allocate(var_ptr, size); 
        } 
        else { 
            throwErr(MEM_LIMIT); 
        }
    }
}


void __Initial_memory(size_t total_size) {
    _ALLOC_LARGE_MEM(total_size);
    _meta_size = _get_mem_obj_meta_size();
    mem_obj_size = _get_mem_obj_meta_size();
    first_live_obj_ptr = NULL;
}
void __Dealloc(void** var_ptr){
    if (var_ptr == NULL || *var_ptr == NULL ){
        throwErr(NULL_VAR);
    }
    uintptr_t _data_addr = (uintptr_t)(*var_ptr);
    MemObject* obj = (MemObject*)(_data_addr - mem_obj_size);
    if (_get_mem_obj_free_status(obj) == 1){
        throwErr(DEALLOC_FAILURE_ERR_FREED);
    }
    size_t _obj_size = _get_mem_obj_size(obj);
    _set_mem_obj_free_status(obj, 1);
    _set_mem_obj_size(obj, 0);
    _set_mem_obj_assoc_var_ptr(obj, NULL);
    _dec_used(_obj_size);
    _REMOVE_FROM_LIVE_LIST(obj);
    _dec_meta_used(_meta_size);
    if (__f_hole_addr){
        _def_flag = 0;
    }
    *var_ptr = NULL;
}

