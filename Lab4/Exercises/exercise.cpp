#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int num_proc, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

  const int sendbuf = rank + 1;
  int recvbuf;
  const int root_rank = 0;
  MPI_Reduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {
    printf("MASTER: ");
    int result = recvbuf;
    if (result == (num_proc * (num_proc + 1) / 2))
    {
      printf("1 + 2 + ... + np = %d\n", result);
    }
    else
    {
      printf("Internal program error\r");
    }
  }

  MPI_Finalize();

  return 0;
}