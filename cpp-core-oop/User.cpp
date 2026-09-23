#include "User.h"
#include "enum.h"
#include <cstdlib>

using namespace std;

string User::getUserName() const
{
    return user_name;
}

string User::getUserEmail() const
{
    return user_email;
}

int User::getBirthDay() const
{
    return birth_day;
}
int User::getBirthMonth() const
{
    return birth_month; 
}
int User::getBirthYear() const 
{
    return birth_year;
}

float User::getPhysicalActivity() const 
{ 
    return physicalActivity; 
}

void User::setUserEmail(const string& newEmail)
{
    if (newEmail.find('@') == string::npos || newEmail.find('.') == string::npos)
    {
        throw invalid_argument("Invalid email format!");
    }
    user_email = newEmail;
}

void User::setBirthDate(int day, int month, int year)  
{
    if (day < 1 || day > 31 || month < 1 || month > 12)
    {
        throw invalid_argument("Invalid birth date!");
    }
    birth_day = day;
    birth_month = month;
    birth_year = year;
}

int User::getAge() const
{
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    int current_year = now.tm_year + 1900;
    int current_month = now.tm_mon + 1;
    int current_day = now.tm_mday;

    int age = current_year - birth_year;

    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day))
    {
        age--;
    }

    return age;
}

void User::setUserName(string newName) 
{
    user_name = newName; 
}

Goal User::getGoal() const
{
    return goal; 
}

Sex User::getSex() const
{
    return sex;
}

int User::getUserWeight() const
{
    return user_weight;
}

int User::getUserHeight() const
{
    return user_height;
}

void User::setGoal(Goal newGoal)
{
    goal = newGoal; 
}

void User::setSex(Sex newSex)
{
    sex = newSex; 
}

void User::setUserWeight(int new_weight)
{
    if (new_weight > 0)
    { 
        user_weight = new_weight;
    }
    else
    {
        throw invalid_argument("Weight must be positive!");
    }
}

void User::setUserHeight(int new_height)
{
    if (new_height > 0)
    { 
        user_height = new_height;
    }
    else
    {
        throw invalid_argument("Height must be positive!");
    }
}

void User::setPhysicalActivity(float activity) 
{
    if (activity >= 1.2 && activity <= 1.9) 
    {
        physicalActivity = activity;
    }
    else
    {
        cerr << "Invalid activity coefficient. Must be between 1.2 and 1.9.\n";
    }
}
