#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Define buffer size

// Global buffer variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int item = 1; // Item counter

// Semaphores and mutex for synchronization
sem_t filled, empty;
pthread_mutex_t lock;

// Function declarations
void init();
void *producer(void *num);
void *consumer(void *num);

int main()
{
  int np, nc;

  printf("Enter the number of Producers: ");
  scanf("%d", &np);
  printf("Enter the number of Consumers: ");
  scanf("%d", &nc);

  init(); // Initialize semaphores and mutex

  pthread_t producers[np], consumers[nc];

  // Create producer threads
  for (int i = 0; i < np; i++)
  {
    pthread_create(&producers[i], NULL, producer, (void *)&i);
    printf("Producer thread %d created.\n", i);
  }

  // Create consumer threads
  for (int i = 0; i < nc; i++)
  {
    pthread_create(&consumers[i], NULL, consumer, (void *)&i);
    printf("Consumer thread %d created.\n", i);
  }

  // Wait for all threads to finish (optional in an infinite loop model)
  for (int i = 0; i < np; i++)
  {
    pthread_join(producers[i], NULL);
  }
  for (int i = 0; i < nc; i++)
  {
    pthread_join(consumers[i], NULL);
  }

  pthread_mutex_destroy(&lock);
  sem_destroy(&filled);
  sem_destroy(&empty);

  return 0;
}

// Initialize buffer, semaphores, and mutex
void init()
{
  sem_init(&empty, 0, BUFFER_SIZE); // Buffer empty slots
  sem_init(&filled, 0, 0);          // Buffer filled slots
  pthread_mutex_init(&lock, NULL);  // Initialize mutex
}

// Producer function
void *producer(void *num)
{
  int id = *(int *)num;
  while (1)
  {
    int sleep_time = rand() % 10 + 1;
    sleep(sleep_time); // Simulate production time

    sem_wait(&empty);          // Wait for empty slot
    pthread_mutex_lock(&lock); // Enter critical section

    // Produce an item
    buffer[in] = item++;
    printf("Producer %d produced item %d\n", id, buffer[in]);
    in = (in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&lock); // Leave critical section
    sem_post(&filled);           // Signal that buffer has new item
  }
}

// Consumer function
void *consumer(void *num)
{
  int id = *(int *)num;
  while (1)
  {
    int sleep_time = rand() % 10 + 1;
    sleep(sleep_time); // Simulate consumption time

    sem_wait(&filled);         // Wait for filled slot
    pthread_mutex_lock(&lock); // Enter critical section

    // Consume an item
    int consumed_item = buffer[out];
    printf("Consumer %d consumed item %d\n", id, consumed_item);
    out = (out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&lock); // Leave critical section
    sem_post(&empty);            // Signal that buffer has an empty slot
  }
}

// gcc prod_cons.c -o pc -lpthread