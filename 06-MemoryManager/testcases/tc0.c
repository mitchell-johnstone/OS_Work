#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 100

int main()
{
	printf("TC0: init and destroy\n");

	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("1 -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", get_remaining_space(), get_allocated_space(), get_fragment_count());
	printf("Total successful mallocs: %d\n", get_mymalloc_count());
	
	mmDestroy();
	
	return 0;
}
