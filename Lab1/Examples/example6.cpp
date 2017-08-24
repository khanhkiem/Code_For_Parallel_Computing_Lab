#include <omp.h>
#include <stdio.h>

#define N 1000
#define CHUNKSIZE 100
#define OMP_NUM_THREADS 10
#define MAX_THREADS 48

int count[MAX_THREADS];

int main(int argc, char **argv)
{
  int i, chunk;
  float a[N], b[N], c[N];

  for (i = 0; i < N; i++)
  {
    //i * 1.0 convert i's type from integer to float
    a[i] = b[i] = i * 1.0;
  }

  //Compiler will init as 0, no need to init ourself
  for (i = 0; i < OMP_NUM_THREADS; i++)
  {
    count[i] = 0;
  }

  chunk = CHUNKSIZE;

#pragma omp parallel shared(a, b, c, chunk) private(i)
  {
    omp_set_num_threads(OMP_NUM_THREADS);
#pragma omp for schedule(dynamic, chunk) nowait
    for (i = 0; i < N; i++)
    {
      int tid = omp_get_thread_num();
      printf("Iter %d running from thread %d\n", i, tid);
      c[i] = a[i] + b[i];

      count[tid]++;
    }
  }

  printf("Vector c: \n");
  for (i = 0; i < 10; i++)
  {
    printf("%f \n", c[i]);
  }
  printf("...\n");

  printf("Num of iter with thread:\n");
  for (i = 0; i < MAX_THREADS; i++)
  {
    if (count[i] != 0)
    {
      printf("\tThread %d run %d iter.\n", i, count[i]);
    }
  }
  return 0;
}