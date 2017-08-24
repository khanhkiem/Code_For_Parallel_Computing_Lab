#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 8
#define VECLEN 100000
pthread_mutex_t sumMutex;
int *a;
int *b;
long sum = 0.0;

void *dotProd(void *arg)
{
  int i, start, end, offset, len;
  long tid;
  tid = (long)arg;
  offset = tid;
  len = VECLEN;
  start = offset * len;
  end = start + len;

  printf("thread: %ld starting, start=%d end=%d\n", tid, start, end);
  for (i = start; i < end; i++)
  {
    pthread_mutex_lock(&sumMutex);
    sum += (a[i] + b[i]);
    pthread_mutex_unlock(&sumMutex);
  }
  printf("thead: %ld done. Global sum now is=%li\n", tid, sum);
  pthread_exit((void *)0);
}

int main(int argc, char *argv[])
{
  long i;
  void *status;
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;

  a = (int *)malloc(NUM_THREADS * VECLEN * sizeof(int));
  b = (int *)malloc(NUM_THREADS * VECLEN * sizeof(int));

  for (i = 0; i < VECLEN * NUM_THREADS; i++)
  {
    a[i] = b[i] = 1;
  }

  pthread_mutex_init(&sumMutex, NULL);

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  for (i = 0; i < NUM_THREADS; i++)
  {
    pthread_create(&threads[i], &attr, dotProd, (void *)i);
  }
  pthread_attr_destroy(&attr);

  for (i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], &status);
    printf("status: %d\n", status);
  }

  printf("Final Global Sum = %li\n", sum);
  free(a);
  free(b);
  pthread_mutex_destroy(&sumMutex);
  pthread_exit(NULL);
}