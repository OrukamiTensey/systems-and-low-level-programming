#include <windows.h>
#include <iostream>
#include <thread>
#include "Queue.h"

using namespace std;

const int MAX_CHAIRS = 3;
int nextCustomerId = 1;

Queue<int> customerQueue;

HANDLE barberReady;
HANDLE customerReady;
HANDLE queueMutex;

void haircut(int customerId)
{
    cout << "[Barber] Cutting hair of customer " << customerId << "..." << endl;
    Sleep(2000);
    cout << "[Barber] Finished haircut of customer " << customerId << endl;
}

DWORD WINAPI Barber(LPVOID)
{
    while (true)
    {
        WaitForSingleObject(customerReady, INFINITE);
        WaitForSingleObject(queueMutex, INFINITE);

        if (!customerQueue.isEmpty())
        {
            int customerId = customerQueue.dequeue();
            ReleaseMutex(queueMutex);
            ReleaseSemaphore(barberReady, 1, NULL);
            haircut(customerId);
        }
        else
        {
            ReleaseMutex(queueMutex);
        }
    }
    return 0;
}

DWORD WINAPI Customer(LPVOID param) 
{
    int customerId = (int)(intptr_t)param;

    WaitForSingleObject(queueMutex, INFINITE);
    if (customerQueue.size() < MAX_CHAIRS) 
    {
        customerQueue.enqueue(customerId);
        cout << "[Customer " << customerId << "] Sitting in waiting room." << endl;
        ReleaseMutex(queueMutex);

        ReleaseSemaphore(customerReady, 1, NULL);
        WaitForSingleObject(barberReady, INFINITE);

        cout << "[Customer " << customerId << "] Getting haircut." << endl;
    }
    else {
        cout << "[Customer " << customerId << "] No space, leaving." << endl;
        ReleaseMutex(queueMutex);
    }

    return 0;
}

void runSleepingBarber()
{
    barberReady = CreateSemaphore(NULL, 0, 1, NULL);
    customerReady = CreateSemaphore(NULL, 0, MAX_CHAIRS, NULL);
    queueMutex = CreateMutex(NULL, FALSE, NULL);

    CreateThread(NULL, 0, Barber, NULL, 0, NULL);

    while (true)
    {
        Sleep(rand() % 3000 + 1000);
        CreateThread(NULL, 0, Customer, (LPVOID)(intptr_t)nextCustomerId++, 0, NULL);
    }
}