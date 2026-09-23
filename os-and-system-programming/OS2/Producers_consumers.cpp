#include <windows.h>
#include <iostream>
#include <thread>
#include "Queue.h"

using namespace std;

Queue<int> buffer;
const int MAX_BUFFER = 5;

HANDLE bufferMutex;
HANDLE itemsAvailable;
HANDLE spaceAvailable;

void producer(int id)
{
    while (true)
    {
        Sleep(rand() % 2000 + 500);
        int item = rand() % 100;

        WaitForSingleObject(spaceAvailable, INFINITE);
        WaitForSingleObject(bufferMutex, INFINITE);

        buffer.enqueue(item);
        cout << "[Producer " << id << "] Produced: " << item << endl;

        ReleaseMutex(bufferMutex);
        ReleaseSemaphore(itemsAvailable, 1, NULL);
    }
}

void consumer(int id) 
{
    while (true) 
    {
        Sleep(rand() % 2500 + 800);

        WaitForSingleObject(itemsAvailable, INFINITE);
        WaitForSingleObject(bufferMutex, INFINITE);

        int item = buffer.dequeue();
        cout << "[Consumer " << id << "] Consumed: " << item << endl;

        ReleaseMutex(bufferMutex);
        ReleaseSemaphore(spaceAvailable, 1, NULL);
    }
}

void runProducerConsumer() 
{
    bufferMutex = CreateMutex(NULL, FALSE, NULL);
    itemsAvailable = CreateSemaphore(NULL, 0, MAX_BUFFER, NULL);
    spaceAvailable = CreateSemaphore(NULL, MAX_BUFFER, MAX_BUFFER, NULL);

    for (int i = 0; i < 2; ++i)
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, (LPVOID)(intptr_t)i, 0, NULL);

    for (int i = 0; i < 2; ++i)
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, (LPVOID)(intptr_t)i, 0, NULL);
}