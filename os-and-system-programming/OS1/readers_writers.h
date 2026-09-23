#ifndef READERS_WRITERS_H
#define READERS_WRITERS_H

#include <pthread.h>
#include <iostream>

class ReadersWriters {
private:
    int readersCount;
    pthread_mutex_t resourceMutex;
    pthread_mutex_t readCountMutex;
    pthread_cond_t canRead;
    pthread_cond_t canWrite;

public:
    ReadersWriters();
    ~ReadersWriters();

    void reader(int readerID);
    void writer(int writerID);
    static void* readerThread(void* arg);
    static void* writerThread(void* arg);
};

#endif // READERS_WRITERS_H
