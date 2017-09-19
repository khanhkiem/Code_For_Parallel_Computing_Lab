#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
  int i, id, num_process, N;
  int tag = 1;
  double x, y, end_time, start_time, spend_time;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  MPI_Comm_size(MPI_COMM_WORLD, &num_process);

  if (argc != 2)
  {
    if (id == 0)
    {
      fprintf(stderr, "Incorrect NARGIN\n");
      fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  sscanf(argv[1], "%d", &N);
  start_time = MPI_Wtime();

  // To random different value at the same time
  // Each process must have different seed -> id
  // Each run must have different random value -> time(0)
  srand((unsigned)(time(0)) + id);

  int lN = N / num_process;
  int process_hit = 0;

  for (i = 0; i < lN; i++)
  {
    // Random x: 0 <= x <= 1
    x = ((double)rand()) / ((double)RAND_MAX);
    y = ((double)rand()) / ((double)RAND_MAX);
    if ((pow(x, 2) + pow(y, 2)) <= 1)
    {
      process_hit++;
    }
  }
  printf("Process %d hit: %d time(s).\n", id, process_hit);

  int hit = 0;

  int in_message;

  hit = process_hit;
  for (int source = 1; source < num_process; source++)
  {
    MPI_Status Stat;
    MPI_Recv(&in_message, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
    hit += in_message;
  }

  double estimated_pi;
  estimated_pi = (double)hit / N * 4;
  end_time = MPI_Wtime();
  spend_time = fabs(end_time - start_time);

  printf("Number of Points Used:      %d\n", N);
  printf("Estimate of Pi:         %.15f\n", estimated_pi);
  printf("Elapsed Wall time:      %5.3e\n", spend_time);

  MPI_Finalize();
  return 0;
}