#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
  int i, rank, num_process, N;
  int tag = 1;
  double x, y, end_time, start_time;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_process);

  if (num_process != 2)
  {
    if (rank == 0)
    {
      fprintf(stderr, "Please! Run 2 process and 1 process per host\n");
      fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  if (argc != 2)
  {
    if (rank == 0)
    {
      fprintf(stderr, "Please! Specify packet size (in KB) argument\n");
      fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int packet_size_in_byte = atoi(argv[1]) * 1024;
  printf("%d\n", packet_size_in_byte);
  int dest = 1 - rank;
  int source = 1 - rank;

  // Prepare packet
  char *out_packet = (char *)malloc(packet_size_in_byte * sizeof(char));
  char *in_packet = (char *)malloc(packet_size_in_byte * sizeof(char));

  start_time = MPI_Wtime();
  MPI_Send(out_packet, packet_size_in_byte, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
  MPI_Recv(in_packet, packet_size_in_byte, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
  end_time = MPI_Wtime();
  printf("Process %d: %f\n", rank, end_time - start_time);
  free(out_packet);
  free(in_packet);

  MPI_Finalize();

  return 0;
}