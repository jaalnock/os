#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readerCount = 0;
int sharedVar = 0;
sem_t writerSem;
pthread_mutex_t lock;

void *reader(void *num)
{
  int id = *(int *)num;
  while (1)
  {
    pthread_mutex_lock(&lock);
    readerCount++;
    if (readerCount == 1)
    {
      sem_wait(&writerSem);
    }
    pthread_mutex_unlock(&lock);

    printf("Reader %d is read sharedVar %d\n", id, sharedVar);
    sleep(1);

    pthread_mutex_lock(&lock);
    readerCount--;
    if (readerCount == 0)
    {
      sem_post(&writerSem);
    }
    pthread_mutex_unlock(&lock);

    sleep(1);
  }
}

void *writer(void *num)
{
  int id = *(int *)num;
  while (1)
  {
    sem_wait(&writerSem);

    sharedVar++;
    printf("Writer %d updated shareVar to %d\n", id, sharedVar);
    sleep(1);

    sem_post(&writerSem);
    sleep(1);
  }
}

int main()
{
  int nR, nW;

  sem_init(&writerSem, 0, 1);
  pthread_mutex_init(&lock, NULL);

  printf("Enter no. of readers : ");
  scanf("%d", &nR);
  printf("Enter no. of readers : ");
  scanf("%d", &nW);

  pthread_t readers[nR], writers[nW];
  for (int i = 0; i < nR; i++)
  {
    pthread_create(&readers[i], NULL, reader, (void *)&i);
    printf("THread for reader %d is created\n", i);
  }

  for (int i = 0; i < nW; i++)
  {
    pthread_create(&writers[i], NULL, writer, (void *)&i);
    printf("THread for writer %d is created\n", i);
  }

  for (int i = 0; i < nR; i++)
  {
    pthread_join(readers[i], NULL);
  }
  for (int i = 0; i < nW; i++)
  {
    pthread_join(writers[i], NULL);
  }

  sem_destroy(&writerSem);
  pthread_mutex_destroy(&lock);
}
