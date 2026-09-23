
#include <iostream>
#include <ctime>

using namespace std;

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    if (number <= 3) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
int main()
{
    // ================================= Task 1 ==================================

    clock_t startTime = clock();

    for (int t = 0; t < 100000; t++) // Обгортка програми для заміру часу
    {
        int S = 0;
        for (int i = 10; i <= 99; i++) // Проходимо по кожному двохзначному числу
        {
            if (isPrime(i)) // Додавання простих чисел до суми
            {
                S += i;
            }
        }
        if (t == 0)
        {
            cout << "The sum of all two-digit prime numbers in Task 1: " << S << endl;
        }

    }
    clock_t endTime = clock();
    double seconds = (double(endTime - startTime)) / CLOCKS_PER_SEC;

    cout << "Time of the optimal solution: " << seconds << " seconds" << endl; // Виведення часу виконання 1-ого завдання

    // ================================= Task 2 ==================================

    clock_t startTime2 = clock();

    for (int t = 0; t < 100000; t++) // Обгортка програми для заміру часу
    {
        const int N = 101; 
        int primeNumbers[N]{};

        for (int i = 1; i < N; i++) // Присвоєння індексам циклу значень від 0 до 100
        {
            primeNumbers[i] = i;
        }
        primeNumbers[0] = 0;
        primeNumbers[1] = 0;

        for (int i = 2; i * i < N; i++) // Знаходження простих чисел за допомогою решета Ератосфена
        {
            if (primeNumbers[i] > 0)
            {
                for (int r = i * i; r <= N; r += i)
                {
                    primeNumbers[r] = 0;
                }

            }
        }

        int S = 0;

        for (int i = 10; i < N; i++) // Знаходження суми всіх простих двоцифрових чисел
        {
            S += primeNumbers[i];
        }
        if (t == 0)
        {
            cout << "The sum of all two-digit prime numbers in Task 2: " << S << endl;
        }
        
    }
    clock_t endTime2 = clock();
    seconds = (double(endTime2 - startTime2)) / CLOCKS_PER_SEC;
    
    cout << "Time of the optimal solution: " << seconds << " seconds" << endl; // Виведення часу виконання 2-ого завдання

    return 0;
}

