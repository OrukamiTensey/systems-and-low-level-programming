#ifndef NUTRITION_H_INCLUDED
#define NUTRITION_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Nutrients.h"
#include "DB_control.h"
#include "User.h"

using namespace std;

class Nutrition
{
private:
	DB_control myDB;
	const char* directory = R"(Products.db)";

	Goal goal;

	bool isNewDish = false, isExit = false, isDishNumber = true, isArray = false;

	int calories_gained = 0, product_calories = 0, grams_gained = 0, dishNumber = 0;
	float protein_gained = 0, fat_gained = 0, carb_gained = 0, product_proteins = 0, product_fats = 0, product_carbs = 0;

	bool addProduct(string product_name, int product_grams);
	bool removeProduct(string product_name);

protected:
	User* user_values;

public:
	void Menu(User& user);
	void showMenu();

	bool addProduct();
	bool removeProduct();

	int getCalories();
	float getProtein();
	float getFat();
	float getCarb();
	int getGrams();

	virtual void revealList(int userNumber, vector<Product>& array) {};

	Nutrients returnNutrientsOfList();
	void calculateNutrientsOfProduct(string nameOfProduct, float weightOfConsumedProduct);
};

class Nutrition_athlete : public Nutrition
{
public:
	void revealList(int userNumber, vector<Product>& array) override;
};

class Nutrition_weightlossing : public Nutrition
{
public:
	void revealList(int userNumber, vector<Product>& array) override;
};

class Nutrition_weightKeeping : public Nutrition
{
public:
	void revealList(int userNumber, vector<Product>& array) override;
};

#endif // NUTRITION_H