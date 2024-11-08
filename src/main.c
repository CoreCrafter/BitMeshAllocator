
#include "bmalloc.h"

int main(){
	
    initial_heap_memory(160);
	char* a;
	allocate_memory((void**)&a, sizeof(char) * 20);
	a[0] = 'm';
	a[1] = 'o';
	a[2] = '\0';

	deallocate_memory((void**)&a);

	allocate_memory((void**)&a, sizeof(char) * 2);
	a[0] = 'j';
	a[1] = '\0';

	destroy();
    return 0;
}
