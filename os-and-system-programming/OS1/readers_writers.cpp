#include "readers_writers.h"
#include <unistd.h>
#include <pthread.h>

ReadersWriters::ReadersWriters() {
    readersCount = 0;
    pthread_mutex_init(&resourceMutex, nullptr);
    pthread_mutex_init(&readCountMutex, nullptr);
    pthread_cond_init(&canRead, nullptr);
    pthread_cond_init(&canWrite, nullptr);
}

ReadersWriters::~ReadersWriters() {
    pthread_mutex_destroy(&resourceMutex);
    pthread_mutex_destroy(&readCountMutex);
    pthread_cond_destroy(&canRead);
    pthread_cond_destroy(&canWrite);
}

void ReadersWriters::reader(int readerID) {
    pthread_mutex_lock(&readCountMutex);
    readersCount++;
    if (readersCount == 1) {
        pthread_mutex_lock(&resourceMutex);  // First reader locks the resource
    }
    pthread_mutex_unlock(&readCountMutex);

    std::cout << "Reader " << readerID << " is reading the resource." << std::endl;
    usleep(1000000);  // Reading for 1 second

    pthread_mutex_lock(&readCountMutex);
    readersCount--;
    if (readersCount == 0) {
        pthread_mutex_unlock(&resourceMutex);  // Last reader releases the resource
    }
    pthread_mutex_unlock(&readCountMutex);
}

void ReadersWriters::writer(int writerID) {
    pthread_mutex_lock(&resourceMutex);

    std::cout << "Writer " << writerID << " is writing the resource." << std::endl;
    usleep(1000000);  // Writing for 1 second

    pthread_mutex_unlock(&resourceMutex);
}

void* ReadersWriters::readerThread(void* arg) {
    ReadersWriters* rw = static_cast<ReadersWriters*>(arg);
    rw->reader(1);  // Reader ID
    return nullptr;
}

void* ReadersWriters::writerThread(void* arg) {
    ReadersWriters* rw = static_cast<ReadersWriters*>(arg);
    rw->writer(1);  // Writer ID
    return nullptr;
}
