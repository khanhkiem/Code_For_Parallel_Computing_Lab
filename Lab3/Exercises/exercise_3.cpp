#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
  int i, id, np, N;
  double x, y, double_N, end_time, start_time, spend_time;
  int lhit;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if (argc != 2)
  {
    if (id == 0)
    {
      fprintf(stderr, "Incorrect NARGIN\n");
      fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  sscanf(argv[1], "%lf", &double_N);
  N = lround(double_N);
  MPI_Barrier(MPI_COMM_WORLD);
  start_time = MPI_Wtime();
  lhit = 0;

  // To random different value at the same time
  // Each process must have different seed -> id
  // Each run must have different random value -> time(0)
  srand((unsigned)(time(0)) + id);
  int lN = N / np;

  for (i = 0; i < lN; i++)
  {
    // Random x: 0 <= x <= 1
    x = ((double)rand()) / ((double)RAND_MAX);
    y = ((double)rand()) / ((double)RAND_MAX);
    if ((pow(x, 2) + pow(y, 2)) <= 1)
    {
      lhit++;
    }
  }
  printf("Process %d hit: %d time(s).\n", id, lhit);

  int hit = 0;

  // Reduce sum all lhit -> hit
  // No need to specify root process id
  // Then broadcast to all
  MPI_Allreduce(&lhit, &hit, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  double estimated_pi;
  estimated_pi = (hit * 4) / double_N;
  MPI_Barrier(MPI_COMM_WORLD);
  end_time = MPI_Wtime();
  spend_time = fabs(end_time - start_time);

  if (id == 0)
  {
    printf("Number of Points Used:      %d\n", N);
    printf("Estimate of Pi:         %24.16f\n", estimated_pi);
    printf("Elapsed Wall time:      %5.3e\n", spend_time);
  }

  MPI_Finalize();
  return 0;
}