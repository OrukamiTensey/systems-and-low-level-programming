#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

//base: ewter_ewrweuo_iewu
//input: reuwoeu_ewoiuewo
void CipherPrint(string array, int* count, bool argument)  
{
	if (*count == array.length())
	{
		*count = 0;
		cout << "_";
	}
	else if (array[*count] == '_') (*count)++; 

	for (int i = *count; array[i] != '_' && i < array.length(); i++) 
	{
		if (argument) 
		{
			cout << array[i];
		}
		(*count)++; 
	}

	if (argument && *count < array.length())
	{
		cout << "_";
	}
}

int WordCounter(string array)
{
	int NumOfWords = 0; 
	for (int i = 0; i < array.length(); i++)
	{
		if (array[i] == '_') NumOfWords++;
	}
	return NumOfWords + 1;
}

bool CheckInput(string array)
{
	bool hasUnderscore = false; 
	bool hasLowerCase = false; 
	for (int i = 0; i < array.length(); i++)   
	{
		if (array[i] == '_') 
		{
			hasUnderscore = true; 
		}
		else if (!isupper(array[i]))   
		{ 
			hasLowerCase = true; 
			cout << "Type Error: " << "\"" << array[i] << "\"" << " ";
			break;
		}
	}
	if (!hasUnderscore) cout << "Error: Input must contain underscores between words.\n";

	if (hasLowerCase) cout << "Error: Input must be in UPPERcase.\n";

	return hasUnderscore && !hasLowerCase; 
}

int main()
{
	string input;
	cout << "Enter you sentence with UPPERcase and underscores between words\nExample: \"HELLO_WORLD\"\n"; cin >> input;
	if (CheckInput(input))
	{
		cout << "Input is correct.\n";
	}
	else return 1;

	cout << "Cipher: ";

	string base = "EVERY_SUNRISE_FOR_SOMETHING_ABOUT_ME_WHATEVER_IT_TAKES_NO_REASON";
	
	int NumOfWords = WordCounter(input);

	int countBase = 0, countInput = 0;
	for (int i = 0; i < NumOfWords; i++) 
	{
		CipherPrint(base, &countBase, true); 
		CipherPrint(base, &countBase, true); 
		CipherPrint(input, &countInput, true);  
	}

	cout << "\n\nEnter your ciphered sentence to decode:\n"; cin >> input; 
	cout << "\nDecoded: ";
	if (!CheckInput(input)) 
	{
		return 1;
	}

	NumOfWords = WordCounter(input);

	countInput = 0;   
	for (int i = 0; i < NumOfWords/3; i++) 
	{ 
		CipherPrint(input, &countInput, false); 
		CipherPrint(input, &countInput, false);  
		CipherPrint(input, &countInput, true); 
	}

	cout << "\n";
	return 0;
}
		