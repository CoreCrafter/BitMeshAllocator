
#include "c_alloc.h"

int main(){
    initial_heap_memory(160);
	char* a;
	allocate_memory((void**)&a, sizeof(char) * 20);
	a[0] = 'm';
	a[1] = 'o';
	a[2] = '\0';
	
/*	char* b;
	allocate_memory((void**)&b, sizeof(char) * 18);
	b[0] = 'a';
	b[1] = 'b';
	b[2] = '\0';
	
	
	char* c;
	allocate_memory((void**)&c, sizeof(char) * 2);
	c[0] = 'w';
	c[1] = '\0';*/
	printf("Before def : \n");
	printf("\nstring1 : %s\nsize: %zu bytes\nstarting pointer : %p\n",a, strlen(a), (void*)a);
	/*printf("\nstring2 : %s\nsize: %zu bytes\nstarting pointer : %p\n",b, strlen(b), (void*)b);
	printf("\nstring3 : %s\nsize: %zu bytes\nstarting pointer : %p\n",c,strlen(c), (void*)c);*/
	printf("\ndealloc c\n");
	deallocate_memory((void**)&a);
	printf("dealloc done \n");
	printf("alloc 2 bytes again \n");
	allocate_memory((void**)&a, sizeof(char) * 2);
	a[0] = 'j';
	a[1] = '\0';
	printf("\nafter allocate 2 again : \n");
	printf("\nstring1 : %s\nsize: %zu bytes\nstarting pointer : %p\n",a, strlen(a), (void*)a);
/*	printf("\nstring2 : %s\nsize: %zu bytes\nstarting pointer : %p\n",b, strlen(b), (void*)b);
	printf("\nstring3 : %s\nsize: %zu bytes\nstarting pointer : %p\n",c,strlen(c), (void*)c);*/
	printf("done\n\n");
	destroy();
    return 0;
}
