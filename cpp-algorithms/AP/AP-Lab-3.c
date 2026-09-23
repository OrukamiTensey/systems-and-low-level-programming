#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	time_t t;
	srand((unsigned)time(&t)); // Запуск генератора випадкових послідовностей

	int n, left, right , x , maxNumber = 0; // Введення змінних
	printf("n = ");
	scanf_s("%i", &n);
	printf("left boarder = ");
	scanf_s("%i", &left);
	printf("right boarder = ");
	scanf_s("%i", &right);

	for (int i = 0; i < n; i++)
	{
		x = left + rand() % (right - left + 1); // Генерація випадкового числа
		printf("x = %d\n", x);
		if (abs(x) > abs(maxNumber)) // Порівняння для знаходження найбільшого числа
		{
			maxNumber = x;
			printf("Max number = %d\n", maxNumber);
		}
	}
	printf(" The maximum number from a randomly generated sequence: %d", maxNumber);
}