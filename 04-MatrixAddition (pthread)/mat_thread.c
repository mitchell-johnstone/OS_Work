#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/** Timing work! **/
void sub_time(struct timespec s, struct timespec f, struct timespec *d){
    d->tv_sec = f.tv_sec - s.tv_sec;
    d->tv_nsec = f.tv_nsec - s.tv_nsec;
    if(d->tv_sec > 0 && d->tv_nsec){
        d->tv_sec--;
        d->tv_nsec += (int)1e9;
    }
}

/** Matrix work! **/
typedef struct {
    FILE* file;
    int rows;
    int cols;
    int* values;
} matrix;

// Read the matrix from the file
matrix* read_matrix(matrix* mat, char* filename){
    mat->file = fopen(filename, "r");
    fscanf(mat->file, "%d", &(mat->rows));
    fscanf(mat->file, "%d", &(mat->cols));
    mat->values = (int*) malloc(sizeof(int) * mat->rows * mat->cols);
    for(int i = 0; i < mat->rows; i++)
        for(int j = 0; j < mat->cols; j++)
            fscanf(mat->file, "%d", mat->values+i*(mat->cols)+j);
    return mat;
}

matrix *A ,*B, *C;

// Add matrices through threads!
void *thread_routine(void *args)
{
    int *vals = (int *)args;
    for(int i = 0; i < vals[0]; i++){
        C->values[i+vals[1]] = A->values[i+vals[1]] + B->values[i+vals[1]];
    }
    return NULL;
}

// Print the matrix in correct orientation
void print_matrix(matrix* mat){
    for(int i = 0; i < mat->rows; i++){
        for(int j = 0; j < mat->cols; j++){
            printf("%d ", mat->values[i * (mat->cols) + j]);
        }
        printf("\n");
    }
}

// Free the memory for the matrix
void close_matrix(matrix* mat){
    if(mat->values) free(mat->values);
    if(mat->file) fclose(mat->file);
    free(mat);
}

int main(int argc, char* argv[])
{
    // Only should have 3 args; program, A and B
    if(argc != 3){
        printf("Only the 2 matrices to add should be used as command line arguments.\n");
        return -1;
    }
    A = (matrix*)malloc(sizeof(matrix));
    B = (matrix*)malloc(sizeof(matrix));
    C = (matrix*)malloc(sizeof(matrix));

    // Read the matrices
    read_matrix(A, argv[1]);
    read_matrix(B, argv[2]);

    // check dimensions match
    if(A->rows != B->rows){
        printf("Matrices row count don't match");
        return -1;
    }
    if(A->cols != B->cols){
        printf("Matrices row count don't match");
        return -1;
    }

    int total = A->rows *  A->cols;
    // Set up C
    C->rows = A->rows;
    C->cols = A->cols;
    C->values = (int*) malloc(sizeof(int) * total);

    // Set up the thread amounts
    //  pairs of values {counts, start}
    int num_threads = total < 8 ? total : 8;
    int arr[14];
    int per_thread = total/num_threads;
    for(int i = 0; i < num_threads-1; i++){
        arr[2*i] = per_thread;
        arr[2*i+1] = per_thread * i;
    }


    // Timespec structs to keep the timing of the program
    struct timespec start, finish, delta;


    // start time!
    clock_gettime(CLOCK_REALTIME, &start);

    // add in each thread
    pthread_t thr[7];
    for (int i = 0; i < num_threads-1; i++)
    {
        // NOTE: there is a single memory location for val which is passed to all threads
        if (pthread_create(&thr[i], NULL, thread_routine, (void *)(arr+i*2)) == -1)
        {
            printf("COULD NOT CREATE A THREAD\n");
            exit(EXIT_FAILURE);
        }
    }

    // main thread's adding, taking remaining
    for(int i = per_thread*(num_threads-1); i < total; i++){
        C->values[i] = A->values[i] + B->values[i];
    }

    // wait for threads
    for (int i = 0; i < num_threads-1; i++)
    {
        pthread_join(thr[i], NULL);
    }

    // end time!
    clock_gettime(CLOCK_REALTIME, &finish);
    sub_time(start, finish, &delta);


    // print results
    printf("addition took %d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);
    printf("Matrix A\n");
    print_matrix(A);
    printf("\nMatrix B\n");
    print_matrix(B);
    printf("\nMatrix C\n");
    print_matrix(C);

    // close
    close_matrix(A);
    close_matrix(B);
    close_matrix(C);
}
