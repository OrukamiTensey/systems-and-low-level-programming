//
// Created by valal on 26.10.2024.
//
#ifndef HEALTH_APP_NUTRIENTS_H
#define HEALTH_APP_NUTRIENTS_H
#include <random>
// Struct to represent nutrients and their amounts (calories, protein, fat, carbohydrates)
struct Nutrients
{
    int calories;
    float protein;
    float fat;
    float carb;

    Nutrients(int cal, float prot, float f, float c) :
            calories(cal),
            protein(prot),
            fat(f),
            carb(c) {}

    bool operator<(const Nutrients& other) const 
    {
        if (calories != other.calories) return calories < other.calories;
        if (protein != other.protein) return protein < other.protein;
        if (fat != other.fat) return fat < other.fat;
        return carb < other.carb;
    }

    bool operator>(const Nutrients& other) const  {
        return other < *this;
    }

    bool operator<=(const Nutrients& other) const {
        return calories <= other.calories;
    }

    bool operator>=(const Nutrients& other) const {
        return calories >= other.calories;
    }

    bool operator==(const Nutrients& other) const {
        return calories == other.calories &&
               protein == other.protein &&
               fat == other.fat &&
               carb == other.carb;
    }

    bool operator!=(const Nutrients& other) const {
        return !(*this == other);
    }

    void adjustNutrients(float factor) {
        calories = round(calories * factor);
        protein = round(protein * factor * 10) / 10;
        fat = round(fat * factor * 10) / 10;
        carb = round(carb * factor * 10) / 10;
    }
};

#endif //HEALTH_APP_NUTRIENTS_H