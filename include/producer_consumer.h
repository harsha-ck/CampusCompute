#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include <pthread.h>

#define BUFFER_SIZE 5

typedef struct
{
    int buffer[BUFFER_SIZE];

    int in;
    int out;
    int count;

    pthread_mutex_t mutex;

    pthread_cond_t not_full;
    pthread_cond_t not_empty;

} SharedBuffer;

void run_producer_consumer(void);

#endif
