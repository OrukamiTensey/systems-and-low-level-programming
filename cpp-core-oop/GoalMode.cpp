#include "GoalMode.h"

int LoseMode::calculateCalories(int bmr, float physicalActivity) const
{
    return (bmr * physicalActivity * 0.85); // Reduce calories by 15%
}

void LoseMode::adjustNutrients(Nutrients &nutrients) const
{
    nutrients.adjustNutrients(0.85f); // Proportional reduction of nutrients
}

int MaintenanceMode::calculateCalories(int bmr, float physicalActivity) const
{
    return (bmr * physicalActivity); // Maintain base calorie
}

void MaintenanceMode::adjustNutrients(Nutrients &nutrients) const
{
    nutrients.adjustNutrients(1.0f); // No change in nutrient proportions
}

int GainMode::calculateCalories(int bmr, float physicalActivity) const
{
    return (bmr * physicalActivity * 1.25); // Increase calories by 25%
}

void GainMode::adjustNutrients(Nutrients &nutrients) const
{
    nutrients.adjustNutrients(1.25f); // Proportional increase of nutrients
}