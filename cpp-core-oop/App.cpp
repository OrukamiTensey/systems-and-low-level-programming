#include "App.h"
#include "App.h"
#include <iostream>
#include <string>

using namespace std;

void App::start()
{
    loadUserData(user);  

    if (user.getUserEmail() == "unknown")
    {
        std::cout << "No saved data found. Please register a new user or log in" << endl;
        handleRegistration(user); 
        if (user.getUserEmail() == " ") exit(0);
    }
    else 
    {
        user.displayUserInfo(); // Temp
    }
    initializeCalorieCounting();
    int choice;
    do 
    {
        showMainMenu();
        cin >> choice;

        switch (choice) 
        {
        case 1:
            system("cls"); 
            handleRegistration(user);  
            break;
        case 2:
            system("cls");
            handleNutrition(user);
            break;
        case 3:
            system("cls");
            handleCalCount(user);
            break;
        case 4:
            system("cls");
            handleActivity(user);
        case 5:
            system("cls");
            handleUserProfile(user);
        case 0:
            Reg_W.saveChangedDataToFile(user);  
            cout << "Exiting program.\n";
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
}

void App::showMainMenu() // Console version 
{
    cout << "------ Main Menu ------\n";
    cout << "1. User Registration\n";
    cout << "2. Nutrition Management\n";
    cout << "3. Calorie Counting\n";
    cout << "4. Activity\n";
    cout << "5. Profile\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void App::handleRegistration(User& user)
{
    int choice;
    string userEmail;
    do 
    {
        Reg_W.showMenu(user);   
        cin >> choice; 

        switch (choice) 
        {
        case 1:
            system("cls"); 
            Reg_W.LoginUser(user);   
            loadUserData(user); 
            break;
        case 2:
            system("cls"); 
            user = Reg_W.registerNewUser(); 
            Reg_W.saveToFile(user);  
            choice = 0;
            system("cls");
            break;
        case 3:
            system("cls"); 
            Reg_W.LoginAdmin(user);    
            break;
        case 4:
            system("cls"); 
            Reg_W.quitAccount(user);
            handleRegistration(user);
            break;
        case 0:
            cout << "Exiting.\n";
            if (user.getUserEmail() == "unknown") exit(0);
            system("cls"); 
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
}

void App::loadUserData(User& user)
{
    ifstream inFile("user_data.txt");
    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string token;

            try
            {
                getline(ss, token, ',');
                user.setUserName(token);

                getline(ss, token, ',');
                user.setUserEmail(token);

                getline(ss, token, ',');
                int day = stoi(token);
                getline(ss, token, ',');
                int month = stoi(token);
                getline(ss, token, ',');
                int year = stoi(token);
                user.setBirthDate(day, month, year);

                getline(ss, token, ',');
                user.setUserWeight(stoi(token));
                getline(ss, token, ',');
                user.setUserHeight(stoi(token)); 

                getline(ss, token, ',');
                user.setSex((token == "Male") ? Sex::Male : Sex::Female);

                getline(ss, token, ',');
                if (token == "Lose")
                    user.setGoal(Goal::Lose); 
                else if (token == "Maintenance")
                    user.setGoal(Goal::Maintenance);
                else
                    user.setGoal(Goal::Gain); 

                getline(ss, token, ',');
                user.setPhysicalActivity(stof(token));
            }
            catch (const invalid_argument& e)
            {
                cerr << "Invalid data format in user_data.txt: " << e.what() << endl;
                continue; 
            }
            catch (const out_of_range& e)
            {
                cerr << "Data out of range in user_data.txt: " << e.what() << endl;
                continue;
            }
        }
        inFile.close();
    }
    else
    {
        cerr << "Unable to open file for loading user data." << endl;
    }
}

void App::handleUserProfile(User& user)
{
    Profile_W.Menu(user);
}


void App::handleNutrition(User& user)
{
    Nutrition_W.Menu(user);    
}

void App::handleCalCount(User& user)  
{
    CalCount_W.menu();    
}

void App::handleActivity(User& user)
{
    //Activity_W.Menu(user);
}

void App::initializeCalorieCounting()
{
    Sex sex = user.getSex();    
    int height = user.getUserHeight();
    int weight = user.getUserWeight();
    int age = user.getAge();
    float physicalActivity = user.getPhysicalActivity();   
    Goal goal = user.getGoal();  

    CalCount_W = CalorieCounting(&user, sex, height, weight, age, physicalActivity, goal); 
}