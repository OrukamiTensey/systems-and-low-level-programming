#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100
#define S 20

int Continue()
{
	char input[S];  
	printf("(1) continue\n(0) exit\n"); 
	fgets(input, sizeof(input), stdin); 

	if (strcmp(input, "1\n") == 0) return 1;
	else if (strcmp(input, "0\n") == 0) return 0;
	else 
	{
		printf("Invalid input. Please enter 1 to continue or 0 to exit.\n");
		return Continue(); 
	} 
}

void PullOutCycle(char* in, char* from, int* i)
{
	int j = 0;
	if (from[*i] == ' ') (*i)++;
	while (from[*i] != '\0' && from[*i] != ' ' && from[*i] != '\n') 
	{
		in[j++] = from[*i];
		(*i)++;
	}
	in[j] = '\0';
}

void FindThePhoneNumber(char studentInfo[], FILE* F, char *in)
{
	char nameFromInput[S] = { 0 }; 
	char initialsFromInput[S] = { 0 }; 

	int i = 0;
	PullOutCycle(nameFromInput, studentInfo, &i);   
	PullOutCycle(initialsFromInput, studentInfo, &i);   

	char line[N];
	rewind(F);
	
	while (fgets(line, sizeof(line), F) != NULL)
	{ 
		char nameFromList[S] = { 0 }; 
		char initialsFromList[S] = { 0 };  
		
		i = 0;
		PullOutCycle(nameFromList, line, &i);  
		PullOutCycle(initialsFromList, line, &i);    

		if (strcmp(nameFromList, nameFromInput) == 0) 
		{
			if (strcmp(initialsFromList, initialsFromInput) == 0)
			{
				PullOutCycle(in, line, &i); 
				return;
			}
		}
	}
	printf("There is no such student in the list OR input is incorrect.");  
}

int main()
{
	FILE *F; 
	char filepath[N] = "C:\\Users\\PC\\OneDrive\\Рабочий стол\\StudentList.txt"; 
	errno_t err;
	err = fopen_s(&F, filepath, "r");  
	if (err != 0 || F == NULL)   
	{ 
		perror("Could not open the file");
		return 1;
	}

	do
	{
		char studentName[N]; 
		printf("Enter the surname and initials (Example: Ivanov I.I.):\n"); 
		fgets(studentName, N, stdin); 
		studentName[strcspn(studentName, "\n")] = 0;

		char phoneNumber[N] = { 0 }; 
		FindThePhoneNumber(studentName, F, phoneNumber); 
		printf("%s\n", phoneNumber); 
	} 
	while (Continue());
	
	fclose(F); 

	return 0;
}