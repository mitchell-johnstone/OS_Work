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

// Add two given matrices
matrix* add_matrices(matrix* A, matrix* B){
    matrix* result = (matrix*)malloc(sizeof(matrix));
    result->rows = A->rows;
    result->cols = A->cols;
    result->values = (int*) malloc(sizeof(int) * result->rows * result->cols);
    for(int i = 0; i < A->rows; i++){
        for(int j = 0; j < A->cols; j++){
            result->values[i*(result->cols)+j] = A->values[i*(A->cols)+j] + B->values[i*(B->cols)+j];
        }
    }
    return result;
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
    // Read the matrices
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

    // Timespec structs to keep the timing of the program
    struct timespec start, finish, delta;

    // start time!
    clock_gettime(CLOCK_REALTIME, &start);

    // add
    matrix* C = add_matrices(A, B);

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
