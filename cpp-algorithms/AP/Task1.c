#include <stdio.h>
#include <stdlib.h>


int CheckTheWord(char array[], int start, int end)
{
	char alphabet[26] = { 0 };
	int unicLetter = 0;

	for (int i = start; i < end; i++)
	{
		if (alphabet[array[i] - 'a'] == 0)
		{
			unicLetter++;
		}
		alphabet[array[i] - 'a']++;
	}
	if (unicLetter >= 3) return 1;
	return 0;
}

int main()
{
	int N;
	printf("Enter N: "); scanf_s("%d", N);
	char* input = (char*)malloc((N + 2) * sizeof(char));
	printf("Enter the sentence with lower case and underscores between words,\nExample: \"hello_world\"\n");
	fgets(input, N + 2, stdin);

	int hasUnderscore = 0;
	for (int i = 0; input[i] != '\0' && i < N - 1; i++)
	{
		if (input[i] == '_')
		{
			hasUnderscore = 1;
		}
		else if (input[i] >= '0' && input[i] <= '9')
		{
			printf("Type Error: \"%c\" ", input[i]);
			printf("Error: Input must only contain letters.\n"); return 1;
		}
		else if (isupper(input[i]))  
		{ 
			printf("Type Error: \"%c\" ", input[i]); 
			printf("Error: Input must be in lower case.\n"); return 1;
		}
	}

	if (!hasUnderscore)
	{
		printf("Error: Input must contain underscores between words.\n"); return 1;
	}

	printf("Filtered: ");
	int start = 0;
	while (input[start] != '\0' && start < N - 1)
	{
		int i = start;
		while (input[i] != '_' && input[i] != '\0') i++;

		int end = i;
		if (CheckTheWord(input, start, end))
		{
			for (int i = start; i < end; i++)
			{
				printf("%c", input[i]);
			}
			if (end + 1 != '\0') printf("_");

		}
		start = end + 1;
	}

	return 0;
}