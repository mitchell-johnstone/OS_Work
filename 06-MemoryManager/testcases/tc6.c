#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 4096
#define ALLOC_COUNT 100
#define ALLOC_SIZE 10

int main()
{
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	void* ptr[ALLOC_COUNT];
	
	printf("TC6: Heap size: %d: allocation count: %d, allocation size: %d - Lots of small allocations with interleaved frees\n", MY_HEAP_SIZE, ALLOC_COUNT, ALLOC_SIZE);

	for(int i = 0 ; i < ALLOC_COUNT; i++) {

		printf("%d - 1 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", i, get_remaining_space(), get_allocated_space(), get_fragment_count());
		
		ptr[i] = mymalloc_ff(ALLOC_SIZE);
		if(ptr[i] == NULL) {
			printf("ptr[%d] - mymalloc_ff(%d) failed\n", i, ALLOC_SIZE);
			exit(EXIT_FAILURE);
		}
		
		printf("%d 2 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", i, get_remaining_space(), get_allocated_space(), get_fragment_count());
	}
	for(int i = 0; i < ALLOC_COUNT; i += 2) {
		printf("Freeing ptr[%d], Fragment Count: %d\n", i, get_fragment_count());
		myfree(ptr[i]);
	}
	for(int i = 1; i < ALLOC_COUNT; i += 2) {
		myfree(ptr[i]);
		printf("Freeing ptr[%d], Fragment Count: %d\n", i, get_fragment_count());
	}

	printf("Total successful mallocs: %d\n", get_mymalloc_count());
	mmDestroy();

	return 0;
}
