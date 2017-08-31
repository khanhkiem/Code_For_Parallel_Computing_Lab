#include "sgemm.h"
#include "omp.h"
#define SIZE 100l
float *A, *B, *C; /* Matrices */
int num_threads;

float compute(long int Count)
{
    int N = (int)Count;

    /* TODO */
    /* Modify this function to implement a parallel version with openmp */

    return (0.);
}

int prepare(long int Count)
{
    int i, j;

    int Matrix_elements = Count * Count;
    int Matrix_bytes = sizeof(float) * Matrix_elements;

    std::cout << "allocating 3 times " << Matrix_bytes / (1.0 * 1024 * 1024) << "MB" << std::endl;

    /* Allocate the matrices */
    A = (float *)malloc(Matrix_bytes);
    if (A == NULL)
    {
        std::cout << "Could not allocate matrix A" << Count << std::endl;
        return -1;
    }

    B = (float *)malloc(Matrix_bytes);
    if (B == NULL)
    {
        std::cout << "Could not allocate matrix B" << Count << std::endl;
        return -1;
    }

    C = (float *)malloc(Matrix_bytes);
    if (C == NULL)
    {
        std::cout << "Could not allocate matrix C" << Count << std::endl;
        return -1;
    }

    /* Initialize the matrices */
    for (i = 0; i < Matrix_elements; i++)
    {
        A[i] = 1.0;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    return (0);
}

int cleanup(long int N)
{
    int i, j;
    float Standard;
    /* Check the result */
    Standard = C[0];
    std::cout << "Standard Element: " << Standard << std::endl;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            if (C[j + i * N] != Standard)
            {
                std::cout << "  " << i << " " << j << " : " << C[j +
                                                                 i *
                                                                     N]
                          << std::endl;
            }
    }

    /* Free the matrices */
    free(A);
    free(B);
    free(C);
    return (0);
}

int main(int argc, char *argv[])
{
    long int Count = SIZE;
    int Error;

    if (argc < 3)
    {
        std::cerr << "Invalid argument" << std::endl;
        std::cerr << "Usage: " << argv[0] << "N T" << std::endl;
        std::cerr << "       N = size" << std::endl;
        std::cerr << "       T = Num thread" << std::endl;
        return 1;
    }
    Count = std::atoi(argv[1]);
    num_threads = std::atoi(argv[2]);

    std::cout << "counts:" << Count << std::endl;
    std::cout << "preparation starting" << std::endl;
    if ((Error = prepare(Count)) != 0)
        return Error;
    std::cout << "preparation done" << std::endl;
    unsigned long long start_ticks = my_getticks();
    Error = compute(Count);
    unsigned long long end_ticks = my_getticks();
    unsigned long long ticks = end_ticks - start_ticks;

    if (Error == 0)
        std::cout << "succeeded in ";
    else
        std::cout << "failed in ";
    std::cout << my_ticks_to_seconds(ticks) << " seconds." << std::endl;
    std::cout << "starting cleanup" << std::endl;
    return cleanup(Count);
}