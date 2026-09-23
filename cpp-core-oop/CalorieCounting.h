#ifndef HEALTH_APP_CALORIECOUNTING_H
#define HEALTH_APP_CALORIECOUNTING_H

#include "Nutrition.h"
#include "ActivityH.h" 
#include "Nutrients.h"
#include "GoalMode.h"
#include <map>
#include "enum.h"
#include "Subject.h"
#include "Product.h"

using namespace std;

// Class for managing calorie counting
class CalorieCounting : public Subject {
private:
    // Mode
    GoalMode *goalMode;
    User* user;

    Sex sex;
    int height;
    int age;
    int weight;
    float physicalActivity;     // Physical activity factor (1.2, 1.375, 1.55, 1.725 or 1.9)
    Goal goal;

    Nutrients* normNutrients;           // Daily nutrients requirement
    Nutrients* consumedNutrients;       //Object storing current consumed nutrient values

    multimap<int, Nutrition> nutrition_map;     //int for sorting by time of adding (lunch, dinner ect.)
    multimap<int, User_activity> activity_map;

    [[nodiscard]] int calculateBMR() const;             // Calculate the Basal Metabolic Rate
    [[nodiscard]] float calculateNutrient(float percentage, int divisor) const;     // Calculate specific nutrient (protein/fat/carb)
    int calculateCalories();                            // Calculate total daily calories based on physical activity and goal
    [[nodiscard]] float calculateProtein() const;       // Calculate daily protein requirement
    [[nodiscard]] float calculateFat() const;           // Calculate daily fat requirement
    [[nodiscard]] float calculateCarb() const;          // Calculate daily carbohydrate requirement
    void updateFunction();                              // Update after changes in properties


public:
    // Function to update consumed nutrients (+ if action = 1 and - if action = -1)
    void updateConsumeCalories(int consumedCalories, float consumedProtein, float consumedFat, float consumedCarb, int action);
    CalorieCounting(User* user, Sex sex, int height, int weight, int age, float physicalActivity, Goal goal);
    void setSex(Sex nSex);
    void setHeight(int nHeight);
    void setAge(int nAge);
    void setWeight(int nWeight);
    void setPhysicalActivity(float nPhysicalActivity);
    void setGoal(Goal nGoal);
    [[nodiscard]] Nutrients nutrientsNorm() const;              // Returns the calculated nutrient requirements based on current state
    [[nodiscard]] Nutrients getConsumedNutrients() const;       // Get the currently consumed nutrient values
    void addActivityCalorieClass(int time, User_activity activity);         // Function to subtract calories after burning them from exercise
    void removeActivityCalorieClass(int time, User_activity activityToRemove);
    void addNutrition();          // Adding gained nutrient
    void removeNutrition(int time, Nutrition nutritionToRemove);
    void menu();
    ~CalorieCounting();
    
};

#endif 
