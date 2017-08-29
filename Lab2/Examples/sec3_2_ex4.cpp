#include <omp.h>
#include <stdio.h>

#define N 1000
#define CHUNKSIZE 10
#define MAX_THREADS 48
#define NUM_THREADS 4

int count[MAX_THREADS];
int a, b, i, tid;
float x;

int main(int argc, char **argv)
{
  omp_set_dynamic(0);
  omp_set_num_threads(NUM_THREADS);

  printf("1st Parallel Region:\n");
#pragma omp parallel private(b, tid)
  {
    tid = omp_get_thread_num();
  }
}