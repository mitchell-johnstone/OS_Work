#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include "memory_manager.h"
#include <pthread.h>
#include <semaphore.h>

/* 
 * Using static causes the compiler to
 * limit visibility of the variables to this file only
 * This can be used to simulate 'private' variables in c
 */
static int allocation_count = 0;
static int space_allocated = 0;
static int fragment_count = 0;
static int total_size = 0;
static int initialized = 0;
static int destroyed = 0;

// Mutexes: Used for keeping our structure thread safe
pthread_mutex_t mem_access;

struct block {
    int free;
    void* start;
    int num_bytes;
    struct block* next_block;
    struct block* prev_block;
};

struct block* head = NULL;

/* mmInit()
 *     Initialize the memory manager to "manage" the given location
 *     in memory with the specified size.
 *         Parameters: start - the start of the memory to manage
 *                     size - the size of the memory to manage
 *         Returns: void
 */ 
void mmInit(void* start, int size) 
{
	allocation_count = 0;
    space_allocated = 0;
    fragment_count = 0;
    total_size = size;
    
    initialized = 1;
    destroyed = 0;

    head = (struct block*) malloc(sizeof(struct block));
    head->free = 1;
    head->start = start;
    head->num_bytes = size;
    head->next_block = NULL;
    head->prev_block = NULL;
}

/* mmDestroy()
 *     Cleans up any storage used by the memory manager
 *     After a call to mmDestroy:
 *         all allocated spaces become invalid
 *         future allocation attempts fail
 *         future frees result in segmentation faults
 *     NOTE: after a call to mmDestroy a call to mmInit
 *           reinitializes the memory manager to allow allocations
 *           and frees
 *         Parameters: None
 *         Returns: void
 */ 
void blockDestroy(struct block* b){
    if(b->next_block != NULL){
        blockDestroy(b->next_block);
    }
    free(b);
}

void mmDestroy()
{
    initialized = 0;
    destroyed = 1;

	allocation_count = 0;
    space_allocated = 0;
    fragment_count = 0;
    total_size = 0;

    blockDestroy(head);
}


/* mymalloc_ff()
 *     Requests a block of memory be allocated using 
 *         first fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void* mymalloc_ff(int nbytes)
{
    // lock!
    pthread_mutex_lock(&mem_access);

    struct block* cur = head;
    void* start = NULL;
    while(cur != NULL){
        // check if current location has free space
        if(cur->free && cur->num_bytes >= nbytes){
            // insert here!
            // create new block, to represent free space after this block!
            struct block* new = (struct block*) malloc(sizeof(struct block));
            new->free = 1;
            new->start = cur->start + nbytes;
            new->num_bytes = cur->num_bytes - nbytes;
            new->next_block = cur->next_block;
            new->prev_block = cur;

            // update our current block to be allocated with the given number
            // of bytes
            cur->free = 0;
            cur->num_bytes = nbytes;

            // update new block status
            if(new->num_bytes == 0){
                // if we have no allocated blocks, just free the block
                free(new);
            } else {
                // otherwise, new block has some free space!
                // add the connecteds between cur and cur->next_block
                if(cur->next_block != NULL){
                    cur->next_block->prev_block = new;
                }
                cur->next_block = new;
                fragment_count++;
            }

            // We allocated, so update!
            allocation_count++;
            space_allocated+=nbytes;

            // record the start address of the current block
            start = cur->start;
            break;
        }
        // loop, update
        cur = cur->next_block;
    }

    // unlock!
    pthread_mutex_unlock(&mem_access);

	return start;
}

/* mymalloc_wf()
 *     Requests a block of memory be allocated using 
 *         worst fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void* mymalloc_wf(int nbytes)
{
    // lock!
    pthread_mutex_lock(&mem_access);

    struct block* worst = NULL;
    struct block* cur = head;
    while(cur != NULL){
        // check if the current spot has right number of free bytes
        if(cur->free && cur->num_bytes >= nbytes){
            // check if current spot is worse than worst spot
            if(worst == NULL || worst->num_bytes < cur->num_bytes){
                // update worst
                worst = cur;
            }
        }
        cur = cur->next_block;
    }
    // now we have worst!
    
    // void* for return val
    void* start = NULL;
    // does it exist?
    if(worst != NULL){
        // update! Insert!
        struct block* new = (struct block*) malloc(sizeof(struct block));
        new->free = 1;
        new->start = worst->start + nbytes;
        new->num_bytes = worst->num_bytes - nbytes;
        new->next_block = worst->next_block;
        new->prev_block = worst;

        // update our current block to be allocated with the given number
        // of bytes
        worst->free = 0;
        worst->num_bytes = nbytes;

        // update new block status
        if(new->num_bytes == 0){
            // if we have no allocated blocks, just free the block
            free(new);
        } else {
            // otherwise, new block has some free space!
            // add the connecteds between cur and cur->next_block
            if(worst->next_block != NULL){
                worst->next_block->prev_block = new;
            }
            worst->next_block = new;
            fragment_count++;
        }

        // We allocated, so update!
        allocation_count++;
        space_allocated += nbytes;

        // record the start address of the current block
        start = worst->start;
    }

    // unlock!
    pthread_mutex_unlock(&mem_access);

	return start;
}

/* mymalloc_bf()
 *     Requests a block of memory be allocated using 
 *         best fit placement algorithm
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: nbytes - the number of bytes in the requested memory
 *         Returns: void* - a pointer to the start of the allocated space
 */
void* mymalloc_bf(int nbytes)
{
    // lock!
    pthread_mutex_lock(&mem_access);

    struct block* best = NULL;
    struct block* cur = head;
    while(cur != NULL){
        // check if the current spot has right number of free bytes
        if(cur->free && cur->num_bytes >= nbytes){
            // check if current spot is better than best spot
            if(best == NULL || best->num_bytes > cur->num_bytes){
                // update best
                best = cur;
            }
        }
        cur = cur->next_block;
    }
    // now we have best!
    
    // void* for return val
    void* start = NULL;
    // does it exist?
    if(best != NULL){
        // update! Insert!
        struct block* new = (struct block*) malloc(sizeof(struct block));
        new->free = 1;
        new->start = best->start + nbytes;
        new->num_bytes = best->num_bytes - nbytes;
        new->next_block = best->next_block;
        new->prev_block = best;

        // update our current block to be allocated with the given number
        // of bytes
        best->free = 0;
        best->num_bytes = nbytes;

        // update new block status
        if(new->num_bytes == 0){
            // if we have no allocated blocks, just free the block
            free(new);
        } else {
            // otherwise, new block has some free space!
            // add the connecteds between cur and cur->next_block
            if(best->next_block != NULL){
                best->next_block->prev_block = new;
            }
            best->next_block = new;
            fragment_count++; 
        }

        // We allocated, so update!
        allocation_count++;
        space_allocated += nbytes;

        // record the start address of the current block
        start = best->start;
    }

    // unlock!
    pthread_mutex_unlock(&mem_access);

	return start;
}

/* myfree()
 *     Requests a block of memory be freed and the storage made
 *         available for future allocations
 *     The memory manager must be initialized (mmInit)
 *         for this call to succeed
 *         Parameters: ptr - a pointer to the start of the space to be freed
 *         Returns: void
 *         Signals a SIGSEGV if a free is not valid
 *             - memory manager is not initialized
 *             - memory manager has been destroyed
 *             - ptr is not allocated (e.g. double free)
 */
void myfree(void* ptr)
{
    // lock!
    pthread_mutex_lock(&mem_access);

    // if not initialized
    if(initialized == 0) kill(0,SIGSEGV);
    // if not destroyed
    if(destroyed == 1) kill(0,SIGSEGV);

    struct block* cur = head;
    // loop until we find the ptr!
    while(cur != NULL && (cur->free || cur->start != ptr)){
        cur = cur->next_block;
    }

    // trying to free memory we don't have, so kill, double free
    if(cur == NULL) kill(0,SIGSEGV);

    // otherwise, free it!
    cur->free = 1;
    space_allocated -= cur->num_bytes;

    // now, clean up!
    // check left
    while(cur->prev_block != NULL && cur->prev_block->free){
        fragment_count--;
        struct block* prev = cur->prev_block;

        // if the previous was the head, update head
        if(prev == head) head = cur;
        // update previous connections
        if(prev->prev_block != NULL){
            prev->prev_block->next_block = cur;
        }
        cur->prev_block = prev->prev_block;
        free(prev);
    }
    // check right 
    while(cur->next_block != NULL && cur->next_block->free){
        fragment_count--;
        struct block* next = cur->next_block;

        // update next connections
        if(next->next_block != NULL){
            next->next_block->prev_block = cur;
        }
        cur->next_block = next->next_block;
        free(next);
    }

    // unlock!
    pthread_mutex_unlock(&mem_access);
}

/* get_allocated_space()
 *     Retrieve the current amount of space allocated by the memory manager (in bytes)
 *         Parameters: None
 *         Returns: int - the current number of allocated bytes 
 */
int get_allocated_space()
{
	return space_allocated;
}

/* get_remaining_space()
 *     Retrieve the current amount of available space in the memory manager (in bytes)
 *         (e.g. sum of all free blocks)
 *         Parameters: None
 *         Returns: int - the current number of free bytes 
 */
int get_remaining_space()
{
	return total_size - space_allocated;
}

/* get_fragment_count()
 *     Retrieve the current amount of free blocks (i.e. the count of all the block, not the size)
 *         Parameters: None
 *         Returns: int - the current number of free blocks
 */
int get_fragment_count()
{
	return fragment_count;
}

/* get_mymalloc_count()
 *     Retrieve the number of successful malloc calls (for all placement types)
 *         Parameters: None
 *         Returns: int - the total number of successful mallocs
 */
int get_mymalloc_count()
{
	return allocation_count;
}
