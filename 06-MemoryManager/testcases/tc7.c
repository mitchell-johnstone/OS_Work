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
	
	printf("TC7: Test interleaved allocations FF\n");
	printf("1 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	
	void* ptr1 = mymalloc_ff(20);
	printf("2 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	void* ptr2 = mymalloc_ff(10);
	printf("3 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	void* ptr3 = mymalloc_ff(10);
	printf("4 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	
	if(ptr1 == NULL) {
		printf("Unable to allocate ptr1\n");
	} else {
		myfree(ptr1);
	}
	if(ptr3 == NULL) {
		printf("Unable to allocate ptr3\n");
	} else {
		myfree(ptr3);
	}
	printf("5 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());

	void* ptr4 = mymalloc_ff(10);
	printf("6 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	void* ptr5 = mymalloc_ff(20);
	printf("7 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	if(ptr4 == NULL) {
		printf("Unable to allocate ptr1\n");
	} else {
		myfree(ptr4);
	}

	if(ptr2 == NULL) {
		printf("Unable to allocate ptr2\n");
	} else {
		myfree(ptr2);
	}
	if(ptr5 == NULL) {
		printf("Unable to allocate ptr5\n");
	} else {
		myfree(ptr5);
	}

	printf("Total successful mallocs: %d\n", get_mymalloc_count());
	mmDestroy();

	return 0;
}
