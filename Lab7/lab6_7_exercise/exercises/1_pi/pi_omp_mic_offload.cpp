#include "pi.h"
#include <omp.h>

#define SIZE 100l

__declspec(target(mic)) double *rect, *midPt, *area;

int compute(long int num_steps)
{
    double pi = 0;
/* TODO */
/* use #pragma offload target(__) to offload this block to MIC devices */
/* please do not forget the direction and size of: pi, num_step, ... */

#pragma offload target(mic : 0) out(pi) in(num_steps) \
    nocopy(rect : length(num_steps))                  \
        nocopy(midPt : length(num_steps))             \
            nocopy(area : length(num_steps))
    {
        int i;
        double width = 2. / num_steps;
        pi = 0.;
#pragma omp parallel for private(i)
        for (i = 0; i < num_steps; ++i)
        {
            rect[i] = (double)i;
            midPt[i] = (i + 0.5) * width - 1.0;
        }
#pragma omp parallel for private(i)
        for (i = 0; i < num_steps; ++i)
        {
            area[i] = sqrt(1.0 - midPt[i] * midPt[i]) * width;
        }

#pragma omp parallel for private(i) reduction(+ : pi)
        for (i = 0; i < num_steps; ++i)
        {
            pi += area[i] * 2.0;
        }
    }

    std::cout << "PI:" << pi << std::endl;

    return (0);
}

int prepare(long int Count)
{
    int i, j, n = Count;
    rect = new double[Count];
    midPt = new double[Count];
    area = new double[Count];
    std::cout << "allocated 3 times " << sizeof(double[Count]) / (1024. * 1024.) << " MBs" << std::endl;

    return (0);
}

int cleanup(long int N)
{
    delete rect;
    delete midPt;
    delete area;
    return (0);
}

int main(int argc, char *argv[])
{
    long int Count = SIZE;
    int Error;

    if (argc > 1)
    {
        Count = std::atoi(argv[1]);
        if (Count <= 0)
        {
            std::cerr << "Invalid argument" << std::endl;
            std::cerr << "Usage: " << argv[0] << "N" << std::endl;
            std::cerr << "       N = size" << std::endl;
            return 1;
        }
    }

    std::cout << "counts:" << Count << std::endl;
    std::cout << "preparation starting" << std::endl;
    unsigned long long s_pre = omp_get_wtime();
    if (Error = prepare(Count) != 0)
        return Error;
    unsigned long long e_pre = omp_get_wtime();
    printf("\tTime for allocating memory=%.6f s\n", (e_pre - s_pre));
    std::cout << "preparation done" << std::endl;

    std::cout << "========= Check offload time =========" << std::endl;
    std::cout << "\t size of data = " << sizeof(double[Count]) * 3 << " bytes" << std::endl;
    unsigned long long start_offload = omp_get_wtime();
#pragma offload_transfer target(mic : 0) in(Count) in(rect : length(Count) free_if(0)) in(midPt : length(Count) free_if(0)) in(area : length(Count) free_if(0))

    unsigned long long end_offload = omp_get_wtime();
    printf("\tThe offload latency=%.6f s, bandwidth=%.3f GB/s", (end_offload - start_offload), 1e-9 * sizeof(double[Count]) * 3 / (end_offload - start_offload));
    std::cout << "======================================" << std::endl;

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
