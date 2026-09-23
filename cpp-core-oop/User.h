#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include "enum.h"
#include "Product.h"

using namespace std;

class User 
{
protected:
    string user_email;
    int birth_day, birth_month, birth_year;

private:
    string user_name;
    int user_weight;
    int user_height;
    Sex sex;
    Goal goal;
    float physicalActivity;

public:
    vector<vector<Product>> superProductMatrix;
    vector<Product> product_gainedNutrition;

    User() : user_email("unknown"), user_weight(0), user_height(0) {} 
    virtual ~User() = default; 

    string getUserEmail() const;
    int getBirthDay() const;
    int getBirthMonth() const;
    int getBirthYear() const;
    int getAge() const;
    Goal getGoal() const;
    Sex getSex() const;
    int getUserWeight() const;
    int getUserHeight() const; 
    string getUserName() const;
    float getPhysicalActivity() const;

    void displayUserInfo() const {
        cout << "Name: " << user_name << "\n";
        cout << "Email: " << user_email << "\n";
        cout << "Birth date: " << birth_day << "/" << birth_month << "/" << birth_year << "\n";
        cout << "Weight: " << user_weight << " kg\n";
        cout << "Height: " << user_height << " cm\n";
        cout << "Sex: " << (sex == Male ? "Male" : "Female") << "\n";
        cout << "Goal: ";
        switch (goal) {
        case Lose:
            cout << "Lose weight";
            break;
        case Maintenance:
            cout << "Maintenance";
            break;
        case Gain:
            cout << "Gain weight";
            break;
        }
        cout << "\n";
        cout << "Physical Activity: " << physicalActivity << "\n";
    }

    void setUserName(string newName); 
    void setUserEmail(const string& newEmail);
    void setBirthDate(int day, int month, int year);
    void setGoal(Goal newGoal);
    void setSex(Sex newSex);
    void setUserWeight(int new_weight);
    void setUserHeight(int new_height); 
    void setPhysicalActivity(float newCoef);
};

// Клас звичайного користувача
class CommonUser : public User
{
public:
    CommonUser() = default;
    ~CommonUser() override = default;
};

// Клас адміністратора
class Admin : public User 
{
private:
    string admin_id; 
    string admin_rights; // NONE , LIMITED , FULL

public:
    Admin() : admin_id("unknown"), admin_rights("none") {}
    Admin(const string& id, const string& rights) : admin_id(id), admin_rights(rights) {}

    void setAdminRights(const string& rights) { admin_rights = rights; } 

};

#endif // USER_H