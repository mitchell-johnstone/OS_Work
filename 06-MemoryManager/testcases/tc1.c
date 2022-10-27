#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100

int main()
{
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("TC1: Single allocate with mymalloc_ff\n");
	printf("1 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	
	// Allocate 10 bytes
	//   shouldn't fail
	char* ptr1 = mymalloc_ff(10);
	if(ptr1 == NULL) {
		printf("ptr1 - mymalloc_ff(10) failed\n");
		exit(EXIT_FAILURE);
	}
	strncpy(ptr1, "HELLO", 10);
	printf("ptr1 is %s\n", ptr1);
	
	printf("2 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());

	myfree(ptr1);
	printf("Total successful mallocs: %d\n", get_mymalloc_count());
	mmDestroy();

	return 0;
}
