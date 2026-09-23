#include "ActivityH.h"
#include <string> 
#include <sstream> 

void User_activity::update_user_activity() 
{
    // Update the user's activity data
    ifstream dataFile("user_activity_data.csv"); // Open the file with activity data
    if (dataFile.is_open()) 
    { // Check if the file opened successfully
        string line;
        while (getline(dataFile, line)) 
        { // Read the file line by line
            stringstream ss(line);  // Use stringstream to split the line   
            string activityName;
            int caloriesBurned;

            getline(ss, activityName, ',');  // Read activity name 
            ss >> caloriesBurned;            // Read calories burned

            // Add activity to the list and update the total burned calories
            addActivity(activityName, caloriesBurned);
        }
        dataFile.close(); // Close the file
    }
    else {
        cerr << "Error opening data file" << endl; // Print an error message
    }

    // Calculate the total physical activity
    physical_activity = calculatePhysicalActivity;

    // Check and update the weight loss record
    if (weight_burned > user_result.weight_burned)
    {
        user_result.weight_burned = weight_burned;
    }
}

void User_activity::saveUserDataToFile() {
    ofstream dataFile("user_data.txt"); // Open the file for writing
    if (dataFile.is_open()) {
        dataFile << "User name: " << user_name << endl;
        dataFile << "Calories burned: " << calories_burned << endl;
        dataFile << "Physical Activity: " << physical_activity << endl;
        dataFile << "Fat Percentage: " << fat_percentage << "%" << endl;
        dataFile << "Number of Activities: " << number_of_activities << endl;
        dataFile.close(); // Close the file
    }
    else
    {
        cerr << "Error opening data file for writing" << endl;
    }
}

void User_activity::displayUserData() const {
    // Display user information on the screen
    cout << "User name: " << user_name << endl;
    cout << "Calories burned: " << calories_burned << endl;
    cout << "Physical Activity: " << physical_activity << endl;
    cout << "Fat Percentage: " << fat_percentage << "%" << endl;
    cout << "Number of Activities: " << number_of_activities << endl;
}

// Additional methods for working with data
void User_activity::addActivity(const string& activityName, int caloriesBurned)
{
    activities.push_back({ activityName, caloriesBurned });
    calories_burned += caloriesBurned;
    number_of_activities++;
}

int User_activity::getDayResult() const
{
    return calories_burned; 
}