#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t t;
    srand(time(&t)); // Запуск генератора нових послідовностей

    int* array; // Вказівник на масив
    int n; // Змінна , що буде визначати розмір масиву
          
    printf("Enter size of the Array: ");
    scanf_s("%d", &n);
 
    array = (int*)malloc(n * sizeof(int)); // Виділення пам'яті для масиву з розміром n
    if (array == NULL) {
        printf("Could not allocate memory for array.\n");
        return 1;
    }
    printf("Generated array:\n");
    
    for (int i = 0; i < n; i++) // Заповнення масиву випадковими числами в діапазоні від 1 до 100
    {
        array[i] = rand() % 100 + 1 - 50;
        printf("%d  ", array[i]); //Виведення всіх елементів масиву
    }
    int Max = array[0]; 
    int Index = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > Max) //Знаходження найбільшого числа зі згенерованих 
        {
            Max = array[i];
            Index = i;
        }
    }
    printf("Max number = %d\n\n", Max); 
    printf("New array:\n");
    for (int i = 0; i < Index; i++)
    {
        if (i % 2 == 0) //Домноження кожного числа під парним індексом на Max
        {
            array[i] *= Max;
        }
        printf("%d  ", array[i]); //Виведення всіх елементів нового масиву
    }
    printf("\n");

    free(array); // Вивільнення пам'яті для масиву

    return 0;
}