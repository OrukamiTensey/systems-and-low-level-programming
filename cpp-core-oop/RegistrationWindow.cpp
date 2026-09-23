#include "RegistrationWindow.h"
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <iomanip>

void RegistrationWindow::LoginUser(User& user) 
{
    string email;
    while (true)
    {
        cout << "Enter user email (or type 'EXIT' to cancel): ";
        getline(cin, email);

        if (email == "EXIT")
        {
            cout << "Returning back to menu...\n";
            return;
        }

        if (email.find('@') != string::npos && email.find('.') != string::npos)
        {
            user.setUserEmail(email);
            break;
        }

        cerr << "Invalid input: Email must be in a valid format.\n";
    }

    quitAccount(user);
    CommonUser newUser;

    ifstream inFile("users.db");
    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open user database file.\n";
        return;
    }

    string line;
    bool userFound = false;

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string fileEmail;
        getline(ss, fileEmail, ','); 

        if (fileEmail == email) 
        {
            quitAccount(user); 
            CommonUser newUser; 

            userFound = true;

            newUser.setUserEmail(fileEmail);

            string name, token;
            int day, month, year, weight, height;
            float activity; 

            getline(ss, name, ',');
            newUser.setUserName(name);

            getline(ss, token, ',');
            day = stoi(token);
            getline(ss, token, ',');
            month = stoi(token);
            getline(ss, token, ',');
            year = stoi(token);
            newUser.setBirthDate(day, month, year);

            getline(ss, token, ',');
            weight = stoi(token);
            newUser.setUserWeight(weight);

            getline(ss, token, ',');
            height = stoi(token);
            newUser.setUserHeight(height);

            getline(ss, token, ','); 
            newUser.setSex((token == "Male") ? Sex::Male : Sex::Female); 

            getline(ss, token, ',');
            if (token == "Lose")
                user.setGoal(Goal::Lose);
            else if (token == "Maintenance")
                user.setGoal(Goal::Maintenance);
            else
                user.setGoal(Goal::Gain);

            getline(ss, token, ','); 
            activity = stof(token); 
            user.setPhysicalActivity(activity); 

            cout << "Login successful! Welcome, " << newUser.getUserName() << ".\n";  
            saveToFile(newUser);
            break;
        }
    }

    if (!userFound)
    {
        cout << "User with this email does not exist!\n";
    }

    inFile.close();
}

void RegistrationWindow::LoginAdmin(User& user)
{

}

void RegistrationWindow::quitAccount(User& user) 
{
    
    ofstream outFile("user_data.txt", ios::trunc); 
    if (outFile.is_open())
    {
        outFile.close();
        cout << "User data cleared successfully.\n";
    }
    else
    {
        cerr << "Failed to clear user data file.\n";
    }
    user = User(); 

    cout << "Account logged out. Returning to registration menu.\n";
}

User RegistrationWindow::registerNewUser()
{
    CommonUser newUser; 
    cout << "-------- User Registration --------" << "\n";

    inputUserData(newUser);

    if (validateUserData(newUser)) cout << "Registration successful!" << "\n";
    else cout << "Invalid data. Registration failed!" << "\n";

    return newUser;  
}

bool RegistrationWindow::validateUserData(const User& user)
{
    if (user.getUserEmail().find('@') == string::npos || user.getUserEmail().find('.') == string::npos) {
        cout << "Invalid email format!" << "\n";
        return false;
    }
    if (user.getAge() < 12)
    {
        cout << "User must be at least 12 years old!" << "\n";
        return false;
    }
    if (user.getUserWeight() <= 0)
    {
        cout << "Weight must be positive!" << "\n";
        return false;
    }
    if (user.getUserHeight() <= 0)
    {
        cout << "Height must be positive!" << "\n";
        return false;
    }
    if (user.getSex() != Male && user.getSex() != Female)
    {
        cout << "Invalid sex! Must be 'M' or 'F'." << "\n";
        return false;
    }
    if (user.getGoal() != Gain && user.getGoal() != Lose && user.getGoal() != Maintenance)
    {
        cout << "Invalid goal! Must be 'G', 'L', or 'M'." << "\n";
        return false;
    }

    return true;
}

void RegistrationWindow::inputUserData(User& user)
{
    try
    {
        string input;
        while (true)
        {
            getchar(); 
            cout << "Enter user name (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            if (!input.empty())
            {
                user.setUserName(input); 
                break;
            }
            cerr << "Invalid input: Name cannot be empty.\n";
        }

        while (true)
        {
            cout << "Enter user email (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            if (input.find('@') != string::npos && input.find('.') != string::npos)
            {
                user.setUserEmail(input); 
                break;
            }
            cerr << "Invalid input: Email must be in a valid format.\n";
        }

        while (true)
        {
            cout << "Enter birth date (DD MM YYYY) (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            int day, month, year;
            if (sscanf_s(input.c_str(), "%d %d %d", &day, &month, &year) == 3 && day > 0 && month > 0 && year > 0) {
                user.setBirthDate(day, month, year); 
                break;
            }
            cerr << "Invalid input: Please enter a valid date in format DD MM YYYY.\n";
        }

        while (true)
        {
            cout << "Enter user weight (kg) (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            int weight = stoi(input);
            if (weight > 0)
            {
                user.setUserWeight(weight); 
                break;
            }
            cerr << "Invalid input: Weight must be a positive number.\n";
        }

        while (true)
        {
            cout << "Enter user height (cm) (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            int height = stoi(input);
            if (height > 0)
            {
                user.setUserHeight(height); 
                break;
            }
            cerr << "Invalid input: Height must be a positive number.\n";
        }

        while (true)
        {
            cout << "Enter sex (M/F) (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            if (input == "M")
            {
                user.setSex(Male); 
                break;
            }
            else if (input == "F")
            {
                user.setSex(Female); 
                break;
            }
            cerr << "Invalid input: Sex must be 'M' or 'F'.\n";
        }

        while (true)
        {
            cout << "Enter goal (G - Gain, L - Lose, M - Maintain) (or type 'EXIT' to cancel): ";
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            if (input == "G")
            {
                user.setGoal(Gain); 
                break;
            }
            else if (input == "L")
            {
                user.setGoal(Lose); 
                break;
            }
            else if (input == "M")
            {
                user.setGoal(Maintenance); 
                break;
            }
            cerr << "Invalid input: Goal must be 'G', 'L', or 'M'.\n";
        }

        while (true)
        {
            cout << "Enter physical activity factor (1.2, 1.375, 1.55, 1.725, 1.9) (or type 'EXIT' to cancel): ";
            string input;
            getline(cin, input);
            if (input == "EXIT")
            {
                cout << "Exiting program...\n";
                exit(0);
            }
            float activity = stof(input);
            if (activity == 1.2 || activity == 1.375 || activity == 1.55 || activity == 1.725 || activity == 1.9)
            {
                user.setPhysicalActivity(activity); // Додано збереження рівня активності
                break;
            }
            cerr << "Invalid input: Activity must be one of the predefined values.\n";
        }
    }
    catch (const invalid_argument&)
    {
        cerr << "Invalid input: Expected a numeric value.\n";
    }
    catch (...)
    {
        cerr << "An unexpected error occurred during registration.\n";
    }
}

void RegistrationWindow::saveToFile(const User& user)
{
    ofstream outFile("user_data.txt", ios::app);
    if (outFile.is_open())
    {
        outFile
            << user.getUserName() << "," 
            << user.getUserEmail() << "," 
            << user.getBirthDay() << "," 
            << user.getBirthMonth() << "," 
            << user.getBirthYear() << "," 
            << user.getUserWeight() << "," 
            << user.getUserHeight() << "," 
            << (user.getSex() == Male ? "Male" : "Female") << "," 
            << (user.getGoal() == Lose ? "Lose" :
                user.getGoal() == Maintenance ? "Maintenance" : "Gain") << ","
            << user.getPhysicalActivity() 
            << endl;

        outFile.close();
    }
    else
    {
        cerr << "Unable to open file for saving user data." << endl;
    }
}

void RegistrationWindow::saveChangedDataToFile(const User& user) 
{
    std::ifstream inFile("user_data.txt");
    std::string currentData;

    if (inFile)
    {
        // Зчитуємо існуючі дані
        std::getline(inFile, currentData, '\0');
        inFile.close();
    }

    // Формуємо нові дані користувача для порівняння
    std::string newData = user.getUserName() + "," +
        user.getUserEmail() + "," +
        std::to_string(user.getBirthDay()) + "," +
        std::to_string(user.getBirthMonth()) + "," +
        std::to_string(user.getBirthYear()) + "," +
        std::to_string(user.getUserWeight()) + "," +
        std::to_string(user.getUserHeight()) + "," +
        (user.getSex() == Male ? "Male" : "Female") + "," +
        (user.getGoal() == Lose ? "Lose" :
            user.getGoal() == Maintenance ? "Maintenance" : "Gain") + "," +
        to_string(user.getPhysicalActivity());

    // Якщо дані змінилися, перезаписуємо файл
    if (currentData != newData)
    {
        std::ofstream outFile("user_data.txt", std::ios::trunc);
        if (outFile)
        {
            outFile << newData;
            outFile.close();
            std::cout << "User data updated in file." << std::endl;
        }
        else 
        {
            std::cerr << "Error opening file for writing!" << std::endl;
        }
    }
    else 
    {
        std::cout << "No changes detected in user data." << std::endl;
    }
}



void RegistrationWindow::showMenu(User& user)
{
    cout << "------ Registration ------\n";
    cout << "1. Log In\n";
    cout << "2. Register New Account\n";
    cout << "3. Log In as Admin\n";
    if (user.getUserEmail() == "unknown") cout << "0. Exit\n";
    else
    {
        cout << "4. Quit Account\n";
        cout << "0. Exit to main menu\n";
    }
    cout << "Choose an option: ";
}