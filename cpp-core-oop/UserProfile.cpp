#include "UserProfile.h"
#include "iostream"

using namespace std;

void UserProfile::Menu(User& user)
{
    int choice;
    do
    {
        showMenu(); 
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            user.displayUserInfo();
            break;
        case 2:
            system("cls");
            subMenu(user);
            break;
        case 3:
            // showing user statistic
            break;
        case 0:
            cout << "Returning to main menu....\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
}

void UserProfile::subMenu(User& user) 
{
    int choice;
    do
    {
        showSubMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            system("cls");
            changeEmail(user);
            break;
        case 2:
            system("cls");
            changeName(user);
            break;
        case 3:
            system("cls");
            changeBirthDate(user);
            break;
        case 4:
            system("cls");
            changeWeight(user);
            break;
        case 5:
            system("cls");
            changeHeight(user);
            break;
        case 6:
            system("cls");
            changeSex(user);
            break;
        case 7:
            system("cls");
            changeGoal(user);
            break;
        case 8:
            system("cls");
            changePhysicalActivity(user);
            break;
        case 9:
            system("cls"); 
            changeAllData(user);
            break;
        case 0:
            cout << "Returning to Profile...\n";
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 0);
}

void UserProfile::showMenu()
{
    cout << "------ Profile Menu ------\n";
    cout << "1. Diaplay User Info\n";
    cout << "2. Change User Data\n";
    cout << "3. Show Statistics\n";
    cout << "0. Exit to main menu\n";
    cout << "Choose an option: ";
}

void UserProfile::showSubMenu()
{
    cout << "------ Change User Data ------\n";
    cout << "1. Email\n";
    cout << "2. Name\n";
    cout << "3. Date of Birth\n";
    cout << "4. Weight\n";
    cout << "5. Height\n";
    cout << "6. Sex\n";
    cout << "7. Goal\n";
    cout << "8. PhysicalActivity\n";
    cout << "9. Change ALL Data\n";
    cout << "0. Return to Profile\n";
    cout << "Choose an option: ";
}

void UserProfile::changeEmail(User& user)
{
    string input;
    while (true)
    {
        cout << "Enter new email (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input.find('@') != string::npos && input.find('.') != string::npos)
        {
            user.setUserEmail(input);
            cout << "Email updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Email must be in a valid format.\n";
    }
}

void UserProfile::changeName(User& user) 
{
    string input;
    while (true)
    {
        cout << "Enter new name (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (!input.empty()) 
        {
            user.setUserName(input);
            cout << "Name updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Name cannot be empty.\n";
    }
}

void UserProfile::changeBirthDate(User& user) 
{
    string input;
    while (true) 
    {
        cout << "Enter new birth date (DD MM YYYY) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        int day, month, year;
        if (sscanf_s(input.c_str(), "%d %d %d", &day, &month, &year) == 3 && day > 0 && month > 0 && year > 0) {
            user.setBirthDate(day, month, year);
            cout << "Birth date updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Please enter a valid date in format DD MM YYYY.\n";
    }
}

void UserProfile::changeWeight(User& user)
{
    string input;
    while (true) 
    {
        cout << "Enter new weight (kg) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        try {
            int weight = stoi(input);
            if (weight > 0) 
            {
                user.setUserWeight(weight);
                cout << "Weight updated successfully.\n";
                return;
            }
        }
        catch (...) {}
        cerr << "Invalid input: Weight must be a positive number.\n";
    }
}

void UserProfile::changeHeight(User& user)
{
    string input;
    while (true)
    {
        cout << "Enter new height (cm) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        try {
            int height = stoi(input);
            if (height > 0) 
            {
                user.setUserHeight(height);
                cout << "Height updated successfully.\n";
                return;
            }
        }
        catch (...) {}
        cerr << "Invalid input: Height must be a positive number.\n";
    }
}

void UserProfile::changeSex(User& user)
{
    string input;
    while (true)
    {
        cout << "Enter new sex (M/F) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "M" || input == "F")
        {
            user.setSex(input == "M" ? Male : Female);
            cout << "Sex updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Sex must be 'M' or 'F'.\n";
    }
}

void UserProfile::changeGoal(User& user)
{
    string input;
    while (true)
    {
        cout << "Enter new goal (G - Gain, L - Lose, M - Maintain) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "G" || input == "L" || input == "M") 
        {
            user.setGoal(input == "G" ? Gain : (input == "L" ? Lose : Maintenance));
            cout << "Goal updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Goal must be 'G', 'L', or 'M'.\n";
    }
}

void UserProfile::changePhysicalActivity(User& user)
{
    string input;
    while (true)
    {
        cout << "Enter new physical activity factor (1.2, 1.375, 1.55, 1.725, 1.9) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        try 
        {
            float activity = stof(input);
            if (activity == 1.2f || activity == 1.375f || activity == 1.55f || activity == 1.725f || activity == 1.9f) {
                user.setPhysicalActivity(activity);
                cout << "Physical activity updated successfully.\n";
                return;
            }
        }
        catch (...) {}
        cerr << "Invalid input: Physical activity must be one of the predefined values.\n";
    }
}

void UserProfile::changeAllData(User& user)
{
    string input;

    cout << "You are now changing all user data. Type 'EXIT' to cancel or 'SKIP' to skip a specific field.\n";

    // «м≥на ≥мен≥
    while (true)
    {
        cout << "Enter user name (or type 'EXIT' to cancel, 'SKIP' to skip): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        if (!input.empty())
        {
            user.setUserName(input);
            break;
        }
        cerr << "Invalid input: Name cannot be empty.\n";
    }

    // «м≥на email
    while (true)
    {
        cout << "Enter user email (or type 'EXIT' to cancel, 'SKIP' to skip): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        if (input.find('@') != string::npos && input.find('.') != string::npos)
        {
            user.setUserEmail(input);
            break;
        }
        cerr << "Invalid input: Email must be in a valid format.\n";
    }

    // «м≥на дати народженн€
    while (true)
    {
        cout << "Enter birth date (DD MM YYYY) (or type 'EXIT' to cancel, 'SKIP' to skip): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        int day, month, year;
        if (sscanf_s(input.c_str(), "%d %d %d", &day, &month, &year) == 3 && day > 0 && month > 0 && year > 0)
        {
            user.setBirthDate(day, month, year);
            break;
        }
        cerr << "Invalid input: Please enter a valid date in format DD MM YYYY.\n";
    }

    // «м≥на ваги
    while (true)
    {
        cout << "Enter user weight (kg) (or type 'EXIT' to cancel, 'SKIP' to skip): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        try
        {
            int weight = stoi(input);
            if (weight > 0)
            {
                user.setUserWeight(weight);
                break;
            }
            cerr << "Invalid input: Weight must be a positive number.\n";
        }
        catch (const invalid_argument&)
        {
            cerr << "Invalid input: Expected a numeric value.\n";
        }
    }

    // «м≥на зросту
    while (true)
    {
        cout << "Enter user height (cm) (or type 'EXIT' to cancel, 'SKIP' to skip): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        try
        {
            int height = stoi(input);
            if (height > 0)
            {
                user.setUserHeight(height);
                break;
            }
            cerr << "Invalid input: Height must be a positive number.\n";
        }
        catch (const invalid_argument&)
        {
            cerr << "Invalid input: Expected a numeric value.\n";
        }
    }

    // «м≥на стат≥
    while (true) {
        cout << "Enter new sex (M/F) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        if (input == "M" || input == "F") {
            user.setSex(input == "M" ? Male : Female);
            cout << "Sex updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Sex must be 'M' or 'F'.\n";
    }

    // «м≥на мети
    while (true)
    {
        cout << "Enter new goal (G - Gain, L - Lose, M - Maintain) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        if (input == "G" || input == "L" || input == "M") 
        {
            user.setGoal(input == "G" ? Gain : (input == "L" ? Lose : Maintenance));
            cout << "Goal updated successfully.\n";
            return;
        }
        cerr << "Invalid input: Goal must be 'G', 'L', or 'M'.\n";
    }

    cout << "All selected user data has been updated.\n";

    while (true)
    {
        cout << "Enter new physical activity factor (1.2, 1.375, 1.55, 1.725, 1.9) (or type 'EXIT' to cancel): ";
        getline(cin, input);
        if (input == "EXIT") return;
        if (input == "SKIP") break;
        try 
        {
            float activity = stof(input);
            if (activity == 1.2f || activity == 1.375f || activity == 1.55f || activity == 1.725f || activity == 1.9f) {
                user.setPhysicalActivity(activity);
                cout << "Physical activity updated successfully.\n";
                return;
            }
        }
        catch (...) {}
        cerr << "Invalid input: Physical activity must be one of the predefined values.\n";
    }
}