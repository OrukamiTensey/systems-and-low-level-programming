#ifndef HEALTH_APP_NUTRITIONDISPLAY_H
#define HEALTH_APP_NUTRITIONDISPLAY_H

#include "Subject.h"
#include "Nutrients.h"
#include "CalorieCounting.h"
#include <iostream>

class NutritionDisplay : public Observer {
private:
    CalorieCounting* calorieCounting;

public:
    explicit NutritionDisplay(CalorieCounting* cc) : calorieCounting(cc) {
        calorieCounting->addObserver(this);
    }

    ~NutritionDisplay() override;
    void update() override;
};

#endif
