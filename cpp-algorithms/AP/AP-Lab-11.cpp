#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Struct
{
    string word; 
    int length; 
};

Struct findLongestWord(string line)
{
    Struct longestWord; 
    longestWord.length = 0;

    int start = 0; 
    string word;
    while (start < line.length())
    {
        int i = start;
        while (line[i] != ' ' && i < line.length()) i++;

        int end = i;

        word = line.substr(start, end - start); 

        if (word.length() > longestWord.length)  
        {
            longestWord.length = word.length(); 
            longestWord.word = word; 
        }
        start = end + 1;
    }
    return longestWord;
}

int main()
{
    string inFilename;
    cout << "Enter the name of input file: "; 
    cin >> inFilename;
    cin.ignore(); 
    ofstream inputFile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\TEST\\" + inFilename);
    if (!inputFile)
    {
        cerr << "Could not create input file." << endl;
        return 1;
    }

    cout << "Enter the text (to complete enter 'END'):" << endl; 
    string line; int i = 1;
    while (true) 
    {
        cout << i << ". ";
        getline(cin, line);
        if (line == "END") break;
        inputFile << line << endl;
        i++;
    }

    inputFile.close();

    ifstream outputFile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\TEST\\" + inFilename);
    if (!inputFile)
    {
        cerr << "Could not open input file." << endl;
        return 1;
    }

    string resFilename; 
    cout << "Enter the name of result file: "; cin >> resFilename; 
    ofstream resultFile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\TEST\\" + resFilename);
    if (!outputFile)
    {
        cerr << "Could not create result file." << endl;
        return 1;
    }

    Struct LongestWord; i = 1;
    while (getline(outputFile, line))  
    {
        LongestWord = findLongestWord(line);
        resultFile << i << ". Word: " << LongestWord.word << ", Length: " << LongestWord.length << endl;
        i++;
    }

    cout << "New file \"" << resFilename << "\" is ready"; 

    outputFile.close(); 
    resultFile.close(); 

    return 0;
}


    
