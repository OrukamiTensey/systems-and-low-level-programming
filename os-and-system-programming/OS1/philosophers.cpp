#include "philosophers.h"
#include <unistd.h>
#include <pthread.h>

Philosopher::Philosopher(int id, pthread_mutex_t* leftFork, pthread_mutex_t* rightFork) 
    : id(id), leftFork(leftFork), rightFork(rightFork) {}

void Philosopher::think() {
    std::cout << "Philosopher " << id << " is thinking.
";
    usleep(1000000);  // Thinking for 1 second
}

void Philosopher::eat() {
    std::cout << "Philosopher " << id << " is eating.
";
    usleep(1000000);  // Eating for 1 second
}

void* Philosopher::start(void* arg) {
    Philosopher* philosopher = static_cast<Philosopher*>(arg);

    while (true) {
        philosopher->think();

        // Try to pick up forks
        pthread_mutex_lock(philosopher->leftFork);
        pthread_mutex_lock(philosopher->rightFork);

        philosopher->eat();

        // Put down forks
        pthread_mutex_unlock(philosopher->rightFork);
        pthread_mutex_unlock(philosopher->leftFork);
    }

    return nullptr;
}
