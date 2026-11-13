#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "../include/producer_consumer.h"
#include <string.h>
SharedBuffer shared;

#define TOTAL_ITEMS 10
void write_log(const char *message, int item)
{
    FILE *fp = fopen("logs/producer_consumer.log", "a");

    if(fp == NULL)
    {
        perror("Unable to open log file");
        return;
    }

    time_t now = time(NULL);

    char *timestamp = ctime(&now);
timestamp[strcspn(timestamp, "\n")] = '\0';

fprintf(fp, "[%s] %s: %d\n",
        timestamp, message, item);

    fclose(fp);
}
// Producer thread
void *producer(void *arg)
{
    (void)arg;

    for(int i = 1; i <= TOTAL_ITEMS; i++)
    {
        pthread_mutex_lock(&shared.mutex);

        // Wait if buffer is full
        while(shared.count == BUFFER_SIZE)
        {
            pthread_cond_wait(&shared.not_full, &shared.mutex);
        }

        // Insert item
        shared.buffer[shared.in] = i;
        write_log("Producer produced", i);

        printf("Producer produced: %d\n", i);

        shared.in = (shared.in + 1) % BUFFER_SIZE;
        shared.count++;

        pthread_cond_signal(&shared.not_empty);

        pthread_mutex_unlock(&shared.mutex);

        sleep(1);
    }

    return NULL;
}

// Consumer thread
void *consumer(void *arg)
{
    (void)arg;

    for(int i = 1; i <= TOTAL_ITEMS; i++)
    {
        pthread_mutex_lock(&shared.mutex);

        // Wait if buffer is empty
        while(shared.count == 0)
        {
            pthread_cond_wait(&shared.not_empty, &shared.mutex);
        }

        // Remove item
        int item = shared.buffer[shared.out];

        printf("Consumer consumed: %d\n", item);
        write_log("Consumer consumed", item);
        shared.out = (shared.out + 1) % BUFFER_SIZE;
        shared.count--;

        pthread_cond_signal(&shared.not_full);

        pthread_mutex_unlock(&shared.mutex);

        sleep(2);
    }

    return NULL;
}
void run_producer_consumer(void)
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    // Initialize shared buffer
    shared.in = 0;
    shared.out = 0;
    shared.count = 0;

    // Initialize synchronization objects
    pthread_mutex_init(&shared.mutex, NULL);
    pthread_cond_init(&shared.not_full, NULL);
    pthread_cond_init(&shared.not_empty, NULL);

    printf("\n========== PRODUCER CONSUMER ==========\n");

    // Create producer thread
    pthread_create(&producer_thread, NULL, producer, NULL);

    // Create consumer thread
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy synchronization objects
    pthread_mutex_destroy(&shared.mutex);
    pthread_cond_destroy(&shared.not_full);
    pthread_cond_destroy(&shared.not_empty);

    printf("\nProducer and Consumer completed successfully!\n");
}
