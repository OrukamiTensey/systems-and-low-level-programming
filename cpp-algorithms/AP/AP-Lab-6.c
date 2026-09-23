#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CreateArray(int** array, int size, int left, int right) 
{
	*array = (int*)malloc(size * sizeof(int));
	if (*array == NULL)
	{
		printf("Could not allocate memory for array");
		return;
	}
	for (int i = 0; i < size; i++) 
	{
		(*array)[i] = left + rand() % (right - left + 1);
	}
}

void PrintTheArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);   
	}
	printf("\n");
}

void FindMax(int* array, int size, int* MaxNumber) 
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] > *MaxNumber)
		{
			*MaxNumber = array[i];
		}
	}
	printf("Max Number of array \"A\": %d\n", *MaxNumber); 
}

void FindMin(int* array, int size, int* MinNumber) 
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] < *MinNumber)
		{
			*MinNumber = array[i];
		}
	}
	printf("Min Number of array \"B\": %d\n", *MinNumber);
}

void Function(int MaxNumber, int MinNumber, double* result)
{
	*result = (MaxNumber + MinNumber) / 3.0;
}

int main()
{
	time_t t;
	srand(time(&t));   
	
	int left, right, size;
	printf("Enter for left limit: "); scanf_s("%d", &left);
	printf("Enter for right limit: "); scanf_s("%d", &right); 

	int* arrayA, *arrayB;  
	// Створення масиву А
	printf("Enter size of the array \"A\": "); scanf_s("%d", &size); 
	CreateArray(&arrayA, size, left, right);  
	PrintTheArray(arrayA, size);

	//ф-ція знаходження макс
	int MaxNumber = arrayA[0];
	FindMax(arrayA, size, &MaxNumber); 

	// Створення масиву Б
	printf("\nEnter size of the array \"B\": "); scanf_s("%d", &size); 
	CreateArray(&arrayB, size, left, right);   
	PrintTheArray(arrayB, size);

	//ф-ція знаходження мін
	int MinNumber = arrayB[0];
	FindMin(arrayB, size, &MinNumber);    

	//ф-ція обчислення формули
	double result = 0;
	Function(MaxNumber, MinNumber, &result);   
	printf("\nResult of function: %lg\n", result);

	free(arrayA);
	free(arrayB);
	return 0;
}