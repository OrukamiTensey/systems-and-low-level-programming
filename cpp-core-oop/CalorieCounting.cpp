#include "CalorieCounting.h"
#include <iostream>
#include <cmath>

// Function to calculate Basal Metabolic Rate (BMR) based on weight, height, age, and sex
int CalorieCounting::calculateBMR() const
{
    int baseBMR = (10 * weight) + (6.25 * height) - (5 * age);
    return (sex == 'M') ? baseBMR + 5 : baseBMR - 164;
}

// Constructor
CalorieCounting::CalorieCounting (User* user, Sex sex, int height, int weight, int age, float physicalActivity, Goal goal) :
        user(user),
        sex(sex),
        height(height),
        weight(weight),
        age(age),
        physicalActivity(physicalActivity),
        goal(goal),
        consumedNutrients(new Nutrients(0, 0, 0, 0)),
        normNutrients(new Nutrients(0, 0, 0, 0)) {
    // Create GoalMode based on the current goal
    switch (goal) {
        case Goal::Lose:
            goalMode = new LoseMode();
            break;
        case Goal::Gain:
            goalMode = new GainMode();
            break;
        default:
            goalMode = new MaintenanceMode();
            break;
    }
    int calorie = calculateCalories();
    float protein = calculateProtein();
    float fat = calculateFat();
    float carb = calculateCarb();
    normNutrients = new Nutrients(calorie, protein, fat, carb);
}

// Function to calculate daily calories based on the BMR and activity level
int CalorieCounting::calculateCalories()
{
    int bmr = calculateBMR();
    int maintenanceCalories = goalMode->calculateCalories(bmr, physicalActivity);

    normNutrients->calories = maintenanceCalories;
    return maintenanceCalories;
}

// Helper function to calculate a specific nutrient (protein, fat, carbs) based on a percentage of total calories
float CalorieCounting::calculateNutrient(float percentage, int divisor) const
{
    float nutrient = (normNutrients->calories * percentage) / divisor;
    nutrient = round(nutrient * 10) / 10;
    return nutrient;
}

// Calculate the daily protein requirement
float CalorieCounting::calculateProtein() const
{
    return calculateNutrient(0.3, 4);
}

// Calculate the daily fat requirement
float CalorieCounting::calculateFat() const
{
    return calculateNutrient(0.3, 9);
}

// Calculate the daily carbohydrate requirement
float CalorieCounting::calculateCarb() const
{
    return calculateNutrient(0.4, 4);
}

// Function that returns the calculated daily nutrient requirements
Nutrients CalorieCounting::nutrientsNorm() const
{
    return *normNutrients;
}

// Update the calorie and nutrient calculations after changes in properties
void CalorieCounting::updateFunction()
{
    int totalCalories = calculateCalories();
    float protein = calculateProtein();
    float fat = calculateFat();
    float carbs = calculateCarb();

    delete normNutrients;
    normNutrients = new Nutrients(totalCalories, protein, fat, carbs);

    // Adjust nutrients
    goalMode->adjustNutrients(*normNutrients);
}

void CalorieCounting::setSex(Sex nSex)
{
    sex = nSex;
    updateFunction();
}

void CalorieCounting::setHeight(int nHeight)
{
    height = nHeight;
    updateFunction();
}

void CalorieCounting::setAge(int nAge)
{
    age = nAge;
    updateFunction();
}

void CalorieCounting::setWeight(int nWeight)
{
    weight = nWeight;
    updateFunction();
}

void CalorieCounting::setPhysicalActivity(float nPhysicalActivity)
{
    physicalActivity = nPhysicalActivity;
    updateFunction();
}

void CalorieCounting::setGoal(Goal nGoal)
{
    // Delete previous mode
    delete goalMode;

    // Create new mode
    goal = nGoal;
    switch (goal) {
        case Lose:
            goalMode = new LoseMode();
            break;
        case Maintenance:
            goalMode = new MaintenanceMode();
            break;
        case Gain:
            goalMode = new GainMode();
            break;
    }

    updateFunction();
}

// Update the consumed nutrients (add or subtract depending on the action parameter)
void CalorieCounting::updateConsumeCalories(int consumedCalories, float consumedProtein, float consumedFat, float consumedCarb, int action)
{
    consumedNutrients->calories += action * consumedCalories;
    consumedNutrients->protein += action * consumedProtein;
    consumedNutrients->fat += action * consumedFat;
    consumedNutrients->carb += action * consumedCarb;

    // Check for invalid nutrient or exceeds
    if (consumedNutrients->calories < 0)
    {
        cout << "Calories cannot be less than zero" << endl;
        consumedNutrients->calories = 0;
    } else if (consumedNutrients->calories > normNutrients->calories)
    {
        cout << "Calories exceed daily norm" << endl;
    }

    if (consumedNutrients->protein < 0)
    {
        cout << "Protein cannot be less than zero" << endl;
        consumedNutrients->protein = 0;
    } else if (consumedNutrients->protein > normNutrients->protein)
    {
        cout << "Protein exceed daily norm" << endl;
    }

    if (consumedNutrients->fat < 0)
    {
        cout << "Fat cannot be less than zero" << endl;
        consumedNutrients->fat = 0;
    } else if (consumedNutrients->fat > normNutrients->fat)
    {
        cout << "Fat exceed daily norm" << endl;
    }

    if (consumedNutrients->carb < 0)
    {
        cout << "Carb cannot be less than zero" << endl;
        consumedNutrients->carb = 0;
    } else if (consumedNutrients->carb > normNutrients->carb)
    {
        cout << "Carb exceed daily norm" << endl;
    }
}

// Returns the current consumed nutrients
Nutrients CalorieCounting::getConsumedNutrients() const
{
    return *consumedNutrients;
}

// Subtract burned calories
void CalorieCounting::addActivityCalorieClass(int time, User_activity activity)
{
    consumedNutrients->calories -= activity.getDayResult();
    activity_map.insert({time, activity});
}

void CalorieCounting::removeActivityCalorieClass(int time, User_activity activityToRemove)
{
    consumedNutrients->calories += activityToRemove.getDayResult(); 
    auto range = activity_map.equal_range(time); 
    for (auto it = range.first; it != range.second; ++it)
    {
        if (&it->second == &activityToRemove)
        { 
            activity_map.erase(it); 
            break;
        }
    }
}

CalorieCounting:: ~CalorieCounting()
{
    delete consumedNutrients;
    delete normNutrients;
}

void CalorieCounting::addNutrition()
{
    const auto& matrix = user->superProductMatrix;
    for (const auto& meal : matrix) {
        for (const auto& product : meal) {
            updateConsumeCalories(product.product_calories, product.product_proteins, product.product_fats, product.product_carbs, 1);
        }
        cout << endl;
    }

    notifyObservers();
}

void CalorieCounting::removeNutrition(int time, Nutrition nutritionToRemove)
{
    Nutrients gainedNutrients = nutritionToRemove.returnNutrientsOfList();
    updateConsumeCalories(gainedNutrients.calories, gainedNutrients.protein, gainedNutrients.fat, gainedNutrients.carb, -1);
    auto range = nutrition_map.equal_range(time);
    for (auto it = range.first; it != range.second; ++it) {
        if (&it->second == &nutritionToRemove) {
            nutrition_map.erase(it);
            break;
        }
    }
}

void CalorieCounting:: menu()
{
    int choice;
    do {
        cout << "=============================" << endl;
        cout << "     Calorie Tracker Menu    " << endl;
        cout << "=============================" << endl;
        cout << "1. View daily nutrient norm" << endl;
        cout << "2. Update consumed nutrients" << endl;
        cout << "3. View consumed nutrients" << endl;
        cout << "4. Add activity calories" << endl;
        cout << "5. Remove activity calories" << endl;
        cout << "6. Exit" << endl;
        cout << "=============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                Nutrients norm = nutrientsNorm();
                cout << "Daily Nutrient Norm:" << endl;
                cout << "Calories: " << norm.calories << " kcal" << endl;
                cout << "Protein: " << norm.protein << " g" << endl;
                cout << "Fat: " << norm.fat << " g" << endl;
                cout << "Carbs: " << norm.carb << " g" << endl;
                break;
            }
            case 2:
            {
                addNutrition();
                break;
            }
            case 3:
            {
                Nutrients consumed = getConsumedNutrients();
                cout << "Consumed Nutrients:" << endl;
                cout << "Calories: " << consumed.calories << " kcal" << endl;
                cout << "Protein: " << consumed.protein << " g" << endl;
                cout << "Fat: " << consumed.fat << " g" << endl;
                cout << "Carbs: " << consumed.carb << " g" << endl;
                break;
            }
            case 4:
            {
                //
                break;
            }
            case 5:
            {
                //
                break;
            }
            case 6:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 6);
}