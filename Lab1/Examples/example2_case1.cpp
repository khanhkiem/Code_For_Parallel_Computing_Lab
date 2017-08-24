#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

long taskIds[NUM_THREADS];

void *userDefFunc(void *param)
{
  long TID = (long)param;
  printf("Hello World! from thread #%ld\n", TID);
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  pthread_t threads[NUM_THREADS];
  int createFlag;
  long i;

  for (i = 0; i < NUM_THREADS; i++)
  {
    taskIds[i] = i;
    printf("In main: creating thread #%ld\n", taskIds[i]);
    createFlag = pthread_create(&threads[i], NULL, userDefFunc, (void *)taskIds[i]);
    if (createFlag)
    {
      printf("ERROR: return code from pthread_create() is %d\n", createFlag);
      exit(-1);
    }
  }

  pthread_exit(NULL);
  return 0;
}
