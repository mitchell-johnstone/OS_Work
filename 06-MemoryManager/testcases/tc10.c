#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 4096
#define MUL_COUNT 100

int* heap_multiply(int a, int b)
{
	int* result = mymalloc_ff(sizeof(int));
	if(result == NULL) {
		printf("COULD NOT mymalloc_ff an int\n");
		exit(EXIT_FAILURE);
	}
	*result = a * b;
	return result;
}

int main()
{
	int* results[MUL_COUNT];
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("TC10: allocate multiple integers and perform multiplications\n");

	for(int i = 0; i < MUL_COUNT; i++) {
		printf("%d -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", i, get_remaining_space(), get_allocated_space(), get_fragment_count());
		results[i] = heap_multiply(i, i + 2);
	}
	
	for(int i = 0; i < MUL_COUNT; i++) {
		printf("%d * %d = %d\n", i, i+2, *results[i]);
	}

	for(int i = 0; i < MUL_COUNT; i++) {
		myfree(results[i]);
	}

	printf("Total successful mallocs: %d\n", get_mymalloc_count());
	mmDestroy();

	return 0;
}
