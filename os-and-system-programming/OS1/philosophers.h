#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <iostream>

#define NUM_PHILOSOPHERS 5

class Philosopher {
private:
    int id;
    pthread_mutex_t* leftFork;
    pthread_mutex_t* rightFork;

public:
    Philosopher(int id, pthread_mutex_t* leftFork, pthread_mutex_t* rightFork);
    void think();
    void eat();
    static void* start(void* arg);
};

#endif // PHILOSOPHERS_H
