#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 100

int shared_data = 0;

pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int readers_count = 0;

void* readerWithoutSync(void* arg) {
    int id = *((int*)arg);
    printf("[Reader %d] reads shared_data: %d\n", id, shared_data);
    usleep(100000);
    return NULL;
}

void* writerWithoutSync(void* arg) {
    int id = *((int*)arg);
    shared_data++;
    printf("[Writer %d] modifies shared_data to: %d\n", id, shared_data);
    usleep(100000);
    return NULL;
}

void* readerWithSync(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&read_mutex);
    readers_count++;
    if (readers_count == 1) pthread_mutex_lock(&rw_mutex);
    pthread_mutex_unlock(&read_mutex);

    printf("[Reader %d] reads shared_data: %d\n", id, shared_data);
    usleep(100000);

    pthread_mutex_lock(&read_mutex);
    readers_count--;
    if (readers_count == 0) pthread_mutex_unlock(&rw_mutex);
    pthread_mutex_unlock(&read_mutex);

    return NULL;
}

void* writerWithSync(void* arg) {
    int id = *((int*)arg);
    pthread_mutex_lock(&rw_mutex);
    shared_data++;
    printf("[Writer %d] modifies shared_data to: %d\n", id, shared_data);
    usleep(100000);
    pthread_mutex_unlock(&rw_mutex);
    return NULL;
}

void executeReadersWriters(int readers, int writers, int sync) {
    pthread_t readerThreads[MAX_THREADS];
    pthread_t writerThreads[MAX_THREADS];
    int ids[MAX_THREADS];

    for (int i = 0; i < (readers > writers ? readers : writers); i++) {
        ids[i] = i + 1;
    }

    for (int i = 0; i < readers; i++) {
        if (sync)
            pthread_create(&readerThreads[i], NULL, readerWithSync, &ids[i]);
        else
            pthread_create(&readerThreads[i], NULL, readerWithoutSync, &ids[i]);
    }

    for (int i = 0; i < writers; i++) {
        if (sync)
            pthread_create(&writerThreads[i], NULL, writerWithSync, &ids[i]);
        else
            pthread_create(&writerThreads[i], NULL, writerWithoutSync, &ids[i]);
    }

    for (int i = 0; i < readers; i++) pthread_join(readerThreads[i], NULL);
    for (int i = 0; i < writers; i++) pthread_join(writerThreads[i], NULL);
}

int main() {
    int choice, readers, writers;

    do {
        printf("\nReader-Writer Synchronization Menu:\n");
        printf("1. Execute without synchronization (Race Condition)\n");
        printf("2. Execute with synchronization (Safe Access)\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("Enter number of Readers: ");
            scanf("%d", &readers);
            printf("Enter number of Writers: ");
            scanf("%d", &writers);
            executeReadersWriters(readers, writers, choice == 2);
        }

    } while (choice != 3);

    pthread_mutex_destroy(&rw_mutex);
    pthread_mutex_destroy(&read_mutex);
    pthread_cond_destroy(&cond);

    printf("Program Terminated.\n");
    return 0;
}
