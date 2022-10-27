#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 4096
#define MUL_COUNT 100

int* results[MUL_COUNT];
int ids[MUL_COUNT];

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

void* thread_function(void* args)
{
	int* localId = mymalloc_ff(sizeof(int));
	if(localId == NULL) {
		printf("%lu could not allocate space for local ID\n", pthread_self());
		exit(EXIT_FAILURE);
	}
	*localId = *(int*)args;
	printf("%d -- Available Memory: %d, Alloc Memory: %d, Fragment Count: %d\n", *localId, get_remaining_space(), get_allocated_space(), get_fragment_count());
	results[*localId] = heap_multiply(*localId, *localId + 2);
	myfree(localId);
	return NULL;
}

int main()
{
	pthread_t mythreads[MUL_COUNT];
	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);
	
	printf("TC11: pthreads allocate multiple integers and perform multiplications\n");

	for(int i = 0; i < MUL_COUNT; i++) {
		ids[i] = i;
		if(pthread_create(&mythreads[i], NULL, thread_function, (void*)&ids[i]) == -1) {
			printf("Could not create thread %d\n", i);
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < MUL_COUNT; i++) {
		pthread_join(mythreads[i], NULL);
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
