#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 4
#define NUM_LOOPS 1000000

void *userDefFunc(void *threadID)
{
  long TID;
  TID = (long)threadID;
  int i;
  double result = 0.0;
  printf("Thread %ld starting...\n", TID);
  for (i = 0; i < NUM_LOOPS; i++)
  {
    result = result + sin(i) + tan(i);
  }
  printf("Thread %ld done, Result = %e\n", TID, result);
  pthread_exit((void *)threadID);
}

int main()
{
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  int creationFlag, joinFlag;
  long i;
  void *status;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (i = 0; i < NUM_THREADS; i++)
  {
    printf("In main: creating thread %ld\n", i);
    creationFlag = pthread_create(&threads[i], &attr, userDefFunc, (void *)i);
    if (creationFlag)
    {
      printf("ERROR: return code from pthread_create() is %d\n", creationFlag);
      exit(-1);
    }
  }

  pthread_attr_destroy(&attr);
  for (i = 0; i < NUM_THREADS; i++)
  {
    joinFlag = pthread_join(threads[i], &status);
    if (joinFlag)
    {
      printf("ERROR: return code from pthread_join() is %d\n", joinFlag);
      exit(-1);
    }
    printf("Main: completed join with thread %ld having a status of %ld\n", i, (long)status);
  }

  printf("Main: program completed. Exiting.\n");
  pthread_exit(NULL);
  return 0;
}