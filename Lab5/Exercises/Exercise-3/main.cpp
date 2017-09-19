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

  MPI_Finalize();
  return 0;
}