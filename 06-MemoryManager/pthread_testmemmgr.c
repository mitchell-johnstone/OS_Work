#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "memory_manager.h"

#define MY_HEAP_SIZE 4096
#define ALLOC_SIZE   1024
#define THREAD_COUNT 10

void* thread_routine(void* args)
{
	for(int i = 0; i < 25; i++) {
		char* myptr = mymalloc_ff(ALLOC_SIZE);
		usleep(20);
		if(myptr != NULL) {
			printf("Thread %lu allocated %d byte(s): %p\n", pthread_self(), ALLOC_SIZE, myptr);
			*myptr = 'a' + i;
			printf("Thread %lu write %c\n", pthread_self(), *myptr);
			myfree(myptr);
			printf("Thread %lu freed %p\n", pthread_self(), myptr);
		} else {
			printf("Thread %lu could not allocate %d byte(s)\n", pthread_self(), ALLOC_SIZE);
		}
	}

	return NULL;
}

int main()
{
	pthread_t mythreads[THREAD_COUNT];

	char my_heap[MY_HEAP_SIZE];
	mmInit(my_heap, MY_HEAP_SIZE);

	for(int i = 0; i < THREAD_COUNT; i++) {
		if(pthread_create(&mythreads[i], NULL, thread_routine, NULL) == -1) {
			printf("COULD NOT CREATE A THREAD\n");
			exit(EXIT_FAILURE);
		}
	}

	for(int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(mythreads[i], NULL);
	}

	mmDestroy();
	
	return 0;
}
