#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *user_def_func(void *threadID)
{
  long TID;
  TID = (long)threadID;
  printf("Hello World! from thread %ld\n", TID);
  pthread_exit(NULL);
}

//MyClass: create class to test autocomplete
class MyClass
{
public:
  int myAttrA;
  void myFuncA(void)
  {
  }
};
MyClass insA;

int main(int argc, char **argv)
{
  MyClass *insB = new MyClass();
  insB->myAttrA = 0;

  pthread_t threads[NUM_THREADS];
  int create_flag;
  long i;

  for (i = 0; i < NUM_THREADS; i++)
  {
    create_flag = pthread_create(&threads[i], NULL, user_def_func, (void *)i);
    printf("In main: creating thread %ld\n", i);
    if (create_flag)
    {
      printf("ERROR: retun code from pthread_create() is %d\n", create_flag);
      exit(-1);
    }
  }

  pthread_exit(NULL);
  return 0;
}