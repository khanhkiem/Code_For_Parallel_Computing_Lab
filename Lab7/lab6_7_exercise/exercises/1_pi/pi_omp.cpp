#include "pi.h"
#include <omp.h>

#define SIZE 100l
double *rect, *midPt, *area;

int compute(long int num_steps)
{
    double pi;
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
#pragma omp parallel for private(i) reduction(+:pi)
    for (i = 0; i < num_steps; ++i)
    {
        //std::cout << "Thread " << omp_get_thread_num() << std::endl;
        pi += area[i] * 2.0;
        //std::cout << "\t pi = " << pi << std::endl;
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
    if (Error = prepare(Count) != 0)
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
