#include "philosophers.h"
#include "readers_writers.h"
#include <pthread.h>

int main()
{
    // Philosophers task
    pthread_mutex_t forks[NUM_PHILOSOPHERS];
    Philosopher *philosophers[NUM_PHILOSOPHERS];
    pthread_t threads[NUM_PHILOSOPHERS];

    // Initialize the forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_mutex_init(&forks[i], nullptr);
    }

    // Create philosophers
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i] = new Philosopher(i, &forks[i], &forks[(i + 1) % NUM_PHILOSOPHERS]);
        pthread_create(&threads[i], nullptr, Philosopher::start, philosophers[i]);
    }

    // Wait for threads to finish (never happens in this case)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        pthread_join(threads[i], nullptr);
    }

    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        delete philosophers[i];
        pthread_mutex_destroy(&forks[i]);
    }

    // Readers/Writers task
    ReadersWriters rw;
    pthread_t readerThreads[3];
    pthread_t writerThreads[2];

    for (int i = 0; i < 3; ++i)
    {
        pthread_create(&readerThreads[i], nullptr, ReadersWriters::readerThread, &rw);
    }

    for (int i = 0; i < 2; ++i)
    {
        pthread_create(&writerThreads[i], nullptr, ReadersWriters::writerThread, &rw);
    }

    for (int i = 0; i < 3; ++i)
    {
        pthread_join(readerThreads[i], nullptr);
    }

    for (int i = 0; i < 2; ++i)
    {
        pthread_join(writerThreads[i], nullptr);
    }

    return 0;
}
