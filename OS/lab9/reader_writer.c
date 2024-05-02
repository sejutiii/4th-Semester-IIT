#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 2
#define MAX_WRITERS 5

sem_t mutex, rw_mutex;
int read_count = 0;

void *reader(void *arg) {
    usleep(100000);
    int id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); 
        }
       
        sem_post(&mutex); 
        printf("Reader %d is reading...\n", id);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); 
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&rw_mutex);
        printf("Writer %d is writing...\n", id);
        sem_post(&rw_mutex);
    }
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
    }
    pthread_create(&readers[0], NULL, reader, &reader_ids[0]);

    for (int i = 0; i < MAX_READERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    pthread_create(&readers[1], NULL, reader, &reader_ids[1]);

    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
