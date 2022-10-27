#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h> // needed for pid_t
#include <sys/wait.h>  // needed for wait system call
#include <fcntl.h>     // needed for parameter values for shm_open
#include <unistd.h>    // needed for fork, getpid, getppid, kill system calls
#include <stdlib.h>    // needed for exit
#include <signal.h>    // needed for signal system call
#include <stdio.h>     // needed for printf, perror
#include <sys/mman.h>  // needed for mmap, munmap, shm system calls

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
matrix* read_matrix(char* filename){
    matrix* mat = (matrix*)malloc(sizeof(matrix));
    mat->file = fopen(filename, "r");
    fscanf(mat->file, "%d", &(mat->rows));
    fscanf(mat->file, "%d", &(mat->cols));
    mat->values = (int*) malloc(sizeof(int) * mat->rows * mat->cols);
    for(int i = 0; i < mat->rows; i++)
        for(int j = 0; j < mat->cols; j++)
            fscanf(mat->file, "%d", mat->values+i*(mat->cols)+j);
    return mat;
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

// Print the matrix in shared memory
void print_shared_mem(int* mat, int rows, int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ", mat[i * cols + j]);
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
    if(argc != 3){
        printf("Only the 2 matrices to add should be used as command line arguments.\n");
        return -1;
    }
    matrix* A = read_matrix(argv[1]);
    matrix* B = read_matrix(argv[2]);
    
    // check dimensions match
    if(A->rows != B->rows){
        printf("Matrices row count don't match");
        return -1;
    }
    if(A->cols != B->cols){
        printf("Matrices row count don't match");
        return -1;
    }

    //set up shared memory
    int shmfd = shm_open("/CS3841MEMORY", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(shmfd == -1) {
        printf("COULD NOT OPEN SHARED MEMORY SEGMENT\n");
        exit(EXIT_FAILURE);
    }
    size_t mapped_size = sizeof(int)*A->cols*A->rows;

    // Set the size of the shared memory segment
    ftruncate(shmfd, mapped_size);

    // Map the segment into the processes address space
    //    NOTE: protection is set to allow reading and writing with a shared mapping
    int* mapped_space = (int*)mmap(NULL, mapped_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if(mapped_space == MAP_FAILED) {
        printf("COULD NOT MMAP\n");
        exit(EXIT_FAILURE);
    }
    

    // Timespec structs to keep the timing of the program
    struct timespec start, finish, delta;
    // start time!
    clock_gettime(CLOCK_REALTIME, &start);

    // add each row in a new fork
    for(int i = 0; i < A->rows; i++){
        pid_t pid = fork();  // fork into 2 processes
        if(pid < 0) // error
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(pid == 0) // child
        {
            // Child adds given row
            for(int j = 0; j < A->cols; j++)
                mapped_space[i*A->cols + j] = A->values[i*A->cols + j] + B->values[i*A->cols + j];

            // close matrices
            close_matrix(A);
            close_matrix(B);

            // Unmap the shared memory in the child
            munmap(mapped_space, mapped_size);

            // Close the shared memory segment for the child
            close(shmfd);

            return 0; // Return success
        }
    }

    // wait for how many children were generated
    for(int i = 0; i < A->rows; i++) wait(0);

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
    print_shared_mem(mapped_space, A->rows, A->cols);

    // close matrices
    close_matrix(A);
    close_matrix(B);

    // Unmap the shared memory
    munmap(mapped_space, mapped_size);
    // Close the shared memory segment
    close(shmfd);
    // Unlink the shared memory
    shm_unlink("/CS3841MEMORY");
}
