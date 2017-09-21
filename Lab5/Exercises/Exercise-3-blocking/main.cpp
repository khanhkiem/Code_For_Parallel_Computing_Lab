#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ROOT_RANK (0)

// Size in B
#define START_SIZE (128 * 1024)
#define END_SIZE (1024 * 1024)

// size increase by multiply INCREMENT
#define INCREMENT (2)

// number of measurement per packet size
#define NUM_MEASUREMENT (5)

int main(int argc, char *argv[])
{
  int rank, num_process;
  int tag = 1;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_process);

  char my_name[MPI_MAX_PROCESSOR_NAME];
  int my_name_length;
  MPI_Get_processor_name(my_name, &my_name_length);
  printf("I'm %s\n", my_name);

  if (num_process != 2)
  {
    if (rank == 0)
    {
      fprintf(stderr, "Please! Run 2 process and 1 process per host\n");
      fflush(stderr);
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int dest = 1 - rank;
  int source = 1 - rank;

  // Prepare packet
  char *transmit_buffer = (char *)malloc(END_SIZE * sizeof(char));

  for (int packet_size_in_B = START_SIZE; packet_size_in_B <= END_SIZE; packet_size_in_B *= 2)
  {
    double sum_bandwidth_in_MBps = 0;
    for (int measure_count = 0; measure_count < NUM_MEASUREMENT; measure_count++)
    {
      if (rank == ROOT_RANK)
      {
        for (int idx = 0; idx < packet_size_in_B; idx++)
        {
          transmit_buffer[idx] = (packet_size_in_B / START_SIZE) * 10 + measure_count;
        }

        double start_time = MPI_Wtime();
        MPI_Send(transmit_buffer, packet_size_in_B, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(transmit_buffer, packet_size_in_B, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
        double end_time = MPI_Wtime();

        for (int idx = 0; idx < packet_size_in_B; idx++)
        {
          if (transmit_buffer[idx] != (packet_size_in_B / START_SIZE) * 10 + measure_count)
          {
            fprintf(stderr, "Received data is not ntegrity\n");
            fflush(stderr);
            MPI_Abort(MPI_COMM_WORLD, 1);
          }
        }

        sum_bandwidth_in_MBps += packet_size_in_B * 2 / (end_time - start_time) / (1024 * 1024);
      }
      else
      {
        MPI_Recv(transmit_buffer, packet_size_in_B, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
        MPI_Send(transmit_buffer, packet_size_in_B, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
      }
    }

    if (rank == ROOT_RANK)
    {
      printf("Packet size: %d KB\n", packet_size_in_B / 1024);
      printf("Average bandwidth: %f MBps\n", sum_bandwidth_in_MBps / NUM_MEASUREMENT);
    }
  }

  free(transmit_buffer);

  MPI_Finalize();

  return 0;
}