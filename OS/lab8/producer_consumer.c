#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, empty, full;
pthread_t producer_thread, consumer_thread;

void *producer(void *arg) {
    int *max= (int *) arg;
    int item;
    for (int i = 0; i < *max; i++) {
        item = i+1 ; // Produce a random item -> rand()

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Producer produced item %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int *max= (int *) arg;
    int item;
    for (int i = 0; i < *max; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

void initialize_semaphores()
{
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
}

void destroy_semaphores()
{
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}



int main() {

    initialize_semaphores();

    int max;
    printf("Enter the maximum number of items: ");
    scanf("%d", &max);
    pthread_create(&producer_thread, NULL, producer, &max);
    pthread_create(&consumer_thread, NULL, consumer, &max);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    destroy_semaphores();
    
    return 0;
}
