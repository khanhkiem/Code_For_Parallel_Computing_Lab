#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

struct ThreadArg
{
  long id;
  int data;
};

ThreadArg taskArg[NUM_THREADS];

void *userDefFunc(void *param)
{
  ThreadArg threadArg = (ThreadArg) * ((ThreadArg *)param);
  long threadId;
  threadId = threadArg.id;
  //TID = ((ThreadArg *)param)->id;
  printf("Hello World! from thread #%ld\n", threadId);
  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  pthread_t threads[NUM_THREADS];
  int createFlag;
  long i;

  for (i = 0; i < NUM_THREADS; i++)
  {
    taskArg[i].id = i;
    printf("In main: creating thread #%ld\n", taskArg[i].id);
    createFlag = pthread_create(&threads[i], NULL, userDefFunc, (void *)&taskArg[i]);
    if (createFlag)
    {
      printf("ERROR: return code from pthread_create() is %d\n", createFlag);
      exit(-1);
    }
  }

  pthread_exit(NULL);
  return 0;
}
