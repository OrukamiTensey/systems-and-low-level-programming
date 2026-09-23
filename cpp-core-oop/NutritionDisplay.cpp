#include "NutritionDisplay.h"

void NutritionDisplay::update()
{
    Nutrients consumed = calorieCounting->getConsumedNutrients();
    Nutrients norm = calorieCounting->nutrientsNorm();
    std::cout << "Updated Nutrient Statistics:\n";
    std::cout << "Calories: " << consumed.calories << "/" << norm.calories << "\n";
    std::cout << "Protein: " << consumed.protein << "/" << norm.protein <<  " g\n";
    std::cout << "Fat: " << consumed.fat << "/" << norm.fat << " g\n";
    std::cout << "Carbohydrates: " << consumed.carb << "/" << norm.carb << " g\n";
}

NutritionDisplay::~NutritionDisplay() noexcept
{
    calorieCounting->removeObserver(this);
}
