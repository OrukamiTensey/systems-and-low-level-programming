#ifndef HEALTH_APP_GOALMODE_H
#define HEALTH_APP_GOALMODE_H
#include "Nutrients.h"

class GoalMode {
public:
    // Virtual function to calculate calories based on BMR and physical activity level
    virtual int calculateCalories(int bmr, float physicalActivity) const = 0;

    // Virtual function to adjust the proportions of nutrients
    virtual void adjustNutrients(Nutrients& nutrients) const = 0;
};

// Class for weight loss mode
class LoseMode : public GoalMode {
public:
    int calculateCalories(int bmr, float physicalActivity) const override;

    void adjustNutrients(Nutrients& nutrients) const override;
};

// Class for maintenance mode
class MaintenanceMode : public GoalMode {
public:
    int calculateCalories(int bmr, float physicalActivity) const override;

    void adjustNutrients(Nutrients& nutrients) const override;
};

// Class for weight gain mode
class GainMode : public GoalMode {
public:
    int calculateCalories(int bmr, float physicalActivity) const override;

    void adjustNutrients(Nutrients& nutrients) const override;
};

#endif