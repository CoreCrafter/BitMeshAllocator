
#ifndef API_ALLOC
#define API_ALLOC

#include "../../utils/common_libs.h"
#include "../../utils/errors/handle_err.h"

void *gen_allocate(size_t size, const char *err_msg);
void gen_free(void* sys_ptr);
void* _write_safe(void* source, void* destination, size_t size);
void* _write_data(void* source, void* destination, size_t size);

#endif
