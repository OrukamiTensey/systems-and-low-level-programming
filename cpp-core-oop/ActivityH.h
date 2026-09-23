#ifndef ACTIVITYH_H_INCLUDED
#define ACTIVITYH_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class User_activity {
private:
    string user_name; // Store the user's name
    int acquired_calories; // Store the calories acquired
    int calories_burned; // Store the calories burned
    int weight_burned; // Store the weight burned
    int number_of_activities; // Store the number of activities
    float physical_activity; // Store the physical activity level
    double calculatePhysicalActivity; // All user physical_activity
    float fat_percentage; // Store the body fat percentage
    vector<pair<string, int>> activities; // Store list of activities

    class Result_user_activity {
    public:
        string goal; // Store the overall fitness goal
        int day_goal; // Store the daily goal
        int month_goal; // Store the monthly goal
        int weight_burned; // Store the best weight loss result
    };

    Result_user_activity user_result; // Store the user's results

public:
    void set_user_goals(string goal, int day_goal, int month_goal) {
        // Validate input to ensure reasonable goals
        if (day_goal <= 0 || month_goal <= 0)
        {
            cout << "Invalid goal values. Please enter positive values." << endl;
            return;
        }

        user_result.goal = goal;
        user_result.day_goal = day_goal;
        user_result.month_goal = month_goal;
    }

    void update_user_activity();
    void addActivity(const string& activityName, int caloriesBurned);
    void displayUserData() const;
    void saveUserDataToFile();
    int getDayResult() const;
};

class Swimmer_activity : public User_activity
{
public:
    virtual const char* getName() { return "Swimmer_activity"; }
    double m_desired_distance;
    float m_km;

    Swimmer_activity(double desired_distance = 0.0, float km = 0.0)
        : User_activity(), m_desired_distance(desired_distance), m_km(km)
    {
    }
};

#endif