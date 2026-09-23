#include "Nutrition.h"


void Nutrition::Menu(User& user)
{
	int choice;
	user_values = &user;
	do
	{
		showMenu();
		cin >> choice;

		goal = user_values->getGoal();


		switch (choice)
		{
		case 1:
			cout << endl;

			if (!isArray)
			{
				user_values->superProductMatrix.push_back(vector<Product>());
				isArray = true;
			}
			
			if (!user_values->superProductMatrix[dishNumber].empty())
			{
				cout << "If you have completed your dish, do you want to create next one?\n0 - no, I will add ingredient to current dish; 1 - yes, I want to create new one to add ingredient there: ";
				cin >> isNewDish;
			}

			if (isNewDish)
			{
				dishNumber++;

				user_values->superProductMatrix.push_back(vector<Product>());

				user_values->product_gainedNutrition.push_back({ "dish" + dishNumber, calories_gained, protein_gained, fat_gained, carb_gained, grams_gained });
				
				calories_gained = 0;
				protein_gained = 0;
				fat_gained = 0;
				carb_gained = 0;
				grams_gained = 0;

				isNewDish = 0;
			}

			do
			{
				if (addProduct())
				{
					cout << "Ingredient was added to your dish successfully!\n\n";
				}
				else
				{
					cout << "Product adding error!\n\n";
					break;
				}
				
				cout << "Have you finished adding ingredients to your dish? Do you want to exit? 0 - no, 1 - yes: ";
				cin >> isExit; cout << endl;
			} while (!isExit);

			isExit = false;

			break;
		case 2:
			cout << endl;

			if (!user_values->superProductMatrix.size() || !user_values->superProductMatrix[dishNumber].size())
			{
				cout << "No added products!\n\n";
				break;
			}
			
			do
			{
				if (removeProduct())
				{
					cout << "Ingredient was removed from your dish successfully!\n";
				}
				else
				{
					cout << "Product removing error!\n\n";
					break;
				}

				cout << "Have you finished removing ingredients from your dish? Do you want to exit? 0 - no, 1 - yes: ";
				cin >> isExit; cout << endl;
			} while (!isExit);

			isExit = false;
				
			break;
		case 3:
		{
			cout << endl;

			if (!user_values->superProductMatrix.size() || !user_values->superProductMatrix[dishNumber].size())
			{
				cout << "No added products!\n\n";
				break;
			}
			int userNumber = -1;
			do
			{
				cout << "Which dish do you want to look at? Enter number of dish: ";
				
				cin >> userNumber;

				if (userNumber < 0 || userNumber > user_values->superProductMatrix.size() - 1)
				{
					isDishNumber = 0;
					cout << "There's no dish with this index! Try again.\n\n";
				}
				else
				{
					isDishNumber = 1;
				}
			} while (!isDishNumber);

			switch (goal)

			{
				case(Lose):
				{
					Nutrition* loseMode = new Nutrition_weightlossing();

					loseMode->revealList(userNumber, user_values->superProductMatrix[userNumber]);
					break;
				}

				case(Gain):
				{
					Nutrition* gainMode = new Nutrition_athlete();

					gainMode->revealList(userNumber, user_values->superProductMatrix[userNumber]);

					break;
				}

				case(Maintenance):
				{
					Nutrition* keepMode = new Nutrition_weightKeeping();

					keepMode->revealList(userNumber, user_values->superProductMatrix[userNumber]);
					break;
				}

				default: cout << "Goal wasn't set!\n"; return;
			}

			cout << endl;
			break;
		}
		case 4:
		{
			bool isData = 1;
			string text;

			getchar();
			
			do
			{
				if (!isData) cout << "There's no such data. Try again!\n\n";

				cout << "Enter a name of product you want to add to your dish: ";
				getline(cin, text);

				isData = myDB.dataExists(directory, "*", "Nutrition", "product = \'" + text + "\'");
			} while (!isData);

			int weight = 0;
			cout << "Enter weight of your product (grams): ";
			cin >> weight; cout << endl;

			calculateNutrientsOfProduct(text, weight);
			break;
		}
		case 0:
			cout << "Returning to main menu...\n";
			system("cls");
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (choice != 0);
}

void Nutrition::showMenu()
{
	cout << "------ Nutrition ------\n";
	cout << "1. Add Product\n";
	cout << "2. Remove Product\n";
	cout << "3. Reveal List\n";
	cout << "4. Information about specific product\n";
	cout << "0. Exit to main menu\n";
	cout << "Choose an option: ";
}

bool Nutrition::addProduct()
{
	bool isData = 1;
	string text;
	
	getchar();

	do
	{
		if (!isData) cout << "There's no such data. Try again!\n\n";

		cout << "Enter a name of product you want to add to your dish: ";
		getline(cin, text);

		isData = myDB.dataExists(directory, "*", "Nutrition", "product = \'" + text + "\'");
	} while (!isData);

	int weight = 0;
	cout << "Enter weight of your product (grams): ";
	cin >> weight;
	
	if (addProduct(text, weight))
	{
		return 1;
	} else return 0;
}

bool Nutrition::addProduct(string product_name, int product_grams)
{
	product_calories = myDB.getValue<int>(directory, "kcal", "nutrition", "product", product_name);
	product_proteins = myDB.getValue<double>(directory, "proteins", "nutrition", "product", product_name);
	product_fats = myDB.getValue<double>(directory, "fats", "nutrition", "product", product_name);
	product_carbs = myDB.getValue<double>(directory, "carbohydrates", "nutrition", "product", product_name);

	float coefficient = (float)product_grams / 100;
	
	user_values->superProductMatrix[dishNumber].push_back({ product_name, (int)(product_calories * coefficient), product_proteins * coefficient, product_fats * coefficient, product_carbs * coefficient, product_grams });
	
	calories_gained += product_calories * coefficient;
	protein_gained += product_proteins * coefficient;
	fat_gained += product_fats * coefficient;
	carb_gained += product_carbs * coefficient;
	grams_gained += product_grams;

	return 1;
}

bool Nutrition::removeProduct()
{
	bool isData = 1;
	string text;

	getchar();
	
	do
	{
		if (!isData) cout << "There's no such data. Try again!\n\n";

		cout << "Enter a name of product you want to remove from your dish: ";
		getline(cin, text);

		isData = removeProduct(text);
	} while (!isData);

	return 1;
}

bool Nutrition::removeProduct(string product_name)
{
	auto it = std::find_if(user_values->superProductMatrix[dishNumber].begin(), user_values->superProductMatrix[dishNumber].end(), [&product_name](const Product& item)
		{
			return item.product_name == product_name;
		}
	);

	if (it == user_values->superProductMatrix[dishNumber].end()) return 0;

	calories_gained -= it->product_calories;
	protein_gained -= it->product_proteins;
	fat_gained -= it->product_fats;
	carb_gained -= it->product_carbs;
	grams_gained -= it->product_grams;

	user_values->superProductMatrix[dishNumber].erase(it);

	return 1;
}

int Nutrition::getCalories()
{
	return calories_gained;
}

float Nutrition::getProtein()
{
	return protein_gained;
}

float Nutrition::getFat()
{
	return fat_gained;
}

float Nutrition::getCarb()
{
	return carb_gained;
}

int Nutrition::getGrams()
{
	return grams_gained;
}

Nutrients Nutrition::returnNutrientsOfList()
{

	Nutrients nutrients_gained = { calories_gained, protein_gained, fat_gained, carb_gained };

	return nutrients_gained;
}

void Nutrition::calculateNutrientsOfProduct(string nameOfProduct, float weightOfConsumedProduct)
{
	float coefficient = weightOfConsumedProduct / 100;
	
	cout << "Here is specifications of your product:\n" << "Name: " << nameOfProduct << endl
														<< "Calories: " << myDB.getValue<int>(directory, "kcal", "nutrition", "product", nameOfProduct) * coefficient << " g\n"
														<< "Proteins: " << myDB.getValue<double>(directory, "proteins", "nutrition", "product", nameOfProduct) * coefficient << " g\n"
														<< "Fats: " << myDB.getValue<double>(directory, "fats", "nutrition", "product", nameOfProduct) * coefficient << " g\n"
														<< "Carbs: " << myDB.getValue<double>(directory, "carbohydrates", "nutrition", "product", nameOfProduct) * coefficient << " g\n"
														<< "Grams: " << weightOfConsumedProduct << " g\n\n";
}

void Nutrition_athlete::revealList(int userNumber, vector<Product>& array)
{
	if (getProtein() < 10)
	{
		cout << "ATTENTION! You should consume more protein. You've consumed protein: " << getProtein() << " g\n\nLet's have a look which ingredients were in your dish:\n\nName | Calories | Proteins | Fats | Carbs | Grams\n";
	}

	for (int i = 0; i < array.size(); i++)
	{
		cout << i + 1 << ". " << array[i].product_name << " | "
							  << array[i].product_calories << " | "
							  << array[i].product_proteins << " | "
							  << array[i].product_fats << " | "
							  << array[i].product_carbs << " | "
							  << array[i].product_grams << endl;
	}
}

void Nutrition_weightlossing::revealList(int userNumber, vector<Product>& array)
{
	if (getFat() > 10)
	{
		cout << "ATTENTION! You should consume less fat. You've consumed fat: " << getFat() << " g\n\nLet's have a look which ingredients were in your dish:\n\n";
	}

	for (int i = 0; i < array.size(); i++)
	{
		cout << i + 1 << ". " << array[i].product_name << " | "
							  << array[i].product_calories << " | "
							  << array[i].product_proteins << " | "
							  << array[i].product_fats << " | "
							  << array[i].product_carbs << " | "
							  << array[i].product_grams << endl;
	}
}

void Nutrition_weightKeeping::revealList(int userNumber, vector<Product>& array)
{
	for (int i = 0; i < array.size(); i++)
	{
		cout << i + 1 << ". " << array[i].product_name << " | "
							  << array[i].product_calories << " | "
							  << array[i].product_proteins << " | "
							  << array[i].product_fats << " | "
							  << array[i].product_carbs << " | "
							  << array[i].product_grams << endl;
	}
}