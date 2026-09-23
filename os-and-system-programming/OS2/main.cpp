#include <iostream>
#include <windows.h>

// Прототипи функцій запуску
void runProducerConsumer();
void runSleepingBarber();

int main() 
{
    int choice;
    std::cout << "1. Producer/Consumer\n2. Sleeping Barber\nChoose task to run: ";
    std::cin >> choice;

    if (choice == 1) runProducerConsumer();
    else if (choice == 2) runSleepingBarber();
    else std::cout << "Invalid option.\n";

    // Не завершувати main, щоб потоки працювали
    while (true) Sleep(1000); 

    return 0;
}