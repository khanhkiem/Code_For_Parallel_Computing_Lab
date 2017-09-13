#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int main(int argc, char **argv)
{
  int numtasks, taskid, len, partner, message;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  if (numtasks % 2 != 0)
  {
    if (taskid == MASTER)
    {
      printf("Quitting, need an even number of tasks: numtasks = %d\n", numtasks);
    }
  }
  else
  {
    if (taskid == MASTER)
    {
      printf("MASTER: number of MPI task is %d\n", numtasks);
    }

    MPI_Get_processor_name(hostname, &len);
    printf("Hello from task %d on %s!\n", taskid, hostname);

    if (taskid < numtasks / 2)
    {
      partner = numtasks / 2 + taskid;
      MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
      MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
    }
    else if (taskid >= numtasks / 2)
    {
      partner = taskid - numtasks / 2;
      MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
      MPI_Send(&taskid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
    }
    printf("Task %d is partner with %d\n", taskid, message);
  }

  MPI_Finalize();
}