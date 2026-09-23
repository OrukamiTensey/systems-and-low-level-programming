#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	time_t t; // Запуск генератора випадкових послідовностей
	srand(time(&t));
	
	int M, N;
	printf("Enter for M: "); scanf_s("%d", &M);
	printf("Enter for N: "); scanf_s("%d", &N);

	// Виділення динамічної пам'яті для одновимірного масиву
	int* array = (int*)malloc((M * N) * sizeof(int));
	if (array == NULL)
	{
		printf("Could not allocate memory for array!!!\n");
		return 1;
	}

	// Виділення динамічної пам'яті для матриці
	int** matrix = (int**)malloc(M * sizeof(int*)); 
	for (int i = 0; i < M; i++)
	{
		matrix[i] = (int*)malloc(N * sizeof(int));
	} 

	int left, right, size = M * N; 
	printf("Enter for left limit: "); scanf_s("%d", &left); 
	printf("Enter for right limit: "); scanf_s("%d", &right); 

	int option;
	printf("Enter \"1\" if you want to enter your values for the matrix\n");
	printf("or any other number for random values: "); scanf_s("%d", &option);
	if (option == 1)
	{
		int a;
		for (int i = 0; i < M; i++) 
		{
			printf("Row with index %d:\n", i); 
			for (int r = 0; r < N; r++) 
			{
				printf("N[%d] = ", r); 
				scanf_s("%d", &a); array[i * N + r] = a;
			}
		}
	}
	else
	{
		for (int i = 0; i < size; i++) // Заповнення одновимірного масиву
		{ 
			array[i] = left + rand() % (right - left + 1);  
		}
	}
	

	// Знаходження максимальних та мінімальних чисел та індексів в масиві
	int MaxNum = array[0], MinNum = array[0], maxIndex = 0, minIndex = 0;
	for (int i = 1; i < size; i++)   
	{ 
		if (array[i] > MaxNum) 
		{
			MaxNum = array[i]; 
			maxIndex = i; 
		}
		else if (array[i] < MinNum) 
		{
			MinNum = array[i]; 
			minIndex = i;
		}
	}

	// Забезпечення унікальності максимального та мінімального значення в масиві
	for (int i = 0; i < size; i++) 
	{
		if (maxIndex != i && array[i] == MaxNum) 
		{
			while (array[i] >= MaxNum)
			{
				array[i] = left + rand() % (right - left + 1); 
			}
		}
		else if (minIndex != i && array[i] == MinNum)
		{
			while (array[i] <= MinNum)  
			{
				array[i] = left + rand() % (right - left + 1); 
			}
		}
	}

	// Заповнення матриці значеннями з одновимірного масиву
	for (int i = 0; i < M; i++)   
	{
		for (int r = 0; r < N; r++)
		{
			matrix[i][r] = array[i * N + r];
			
		}
	}

	// Виведення матриці в консоль
	printf("\nMatrix with unique max and min numbers:\n"); 
	for (int i = 0; i < M; i++) 
	{
		printf("%d| ", i);  
		for (int r = 0; r < N; r++) 
		{
			printf("%4d ", matrix[i][r]); 
		}
		printf("\n"); 
	}
	printf("\nMax Number = %d , Min Number = %d", MaxNum, MinNum);

	int Element;
	int MaxRowIndex = maxIndex / N;
	int MinRowIndex = minIndex / N;
	if (MaxRowIndex == MinRowIndex)
	{
		printf("\nThe maximum and the minimum are on the same row: %d\n", MaxRowIndex); 
		return 0;
	}
	else
	{
		// Зміна рядків з максимальним та мінімальним значенням місцями
		for (int i = 0; i < N; i++)
		{
			Element = matrix[MaxRowIndex][i];
			matrix[MaxRowIndex][i] = matrix[MinRowIndex][i];
			matrix[MinRowIndex][i] = Element;
		}
		
		// Виведення нової матриці
		printf("\n\nNew matrix:\n");
		for (int i = 0; i < M; i++) 
		{
			printf("%d| ", i);
			for (int r = 0; r < N; r++) 
			{
				printf("%4d ", matrix[i][r]); 
			}
			printf("\n"); 
		}
		printf("\nRows that were replaced: %d , %d\n", MaxRowIndex, MinRowIndex);
		return 1;
	}
	// Вивільнення пам'яті для масивів
	free(array); 
	for (int i = 0; i < M; i++) { 
		free(matrix[i]);
	}
}
