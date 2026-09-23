#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Movie
{
	string name;
	string type;
	int duration;
};

string WordFromFile(string filename)
{
	ifstream file(filename); 

	if (!file.is_open()) { 
		cout << "Error opening file: " << filename << "\n"; 
		return "";  // Повертаємо пустий рядок у випадку помилки  
	}

	vector <string> words; 
	string word; 
	 
	while (file >> word) { 
		words.push_back(word); 
	}
	file.close(); 
	int randIndex = rand() % words.size(); 
	return words[randIndex];
}

Movie RandMovie()  
{
	Movie movie; 

	string filename = "C:\\Users\\PC\\OneDrive\\Рабочий стол\\Movie_names.txt"; 
	movie.name = WordFromFile(filename);

	filename = "C:\\Users\\PC\\OneDrive\\Рабочий стол\\Movie_types.txt";
	movie.type = WordFromFile(filename);

	movie.duration = 90 + rand() % 210;

	return movie;
}

int main()
{
	srand(time(NULL)); 
	Movie film = RandMovie();

	cout << film.name << " " << film.type << " " << film.duration << "\n";
}