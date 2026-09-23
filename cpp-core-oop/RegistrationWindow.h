#ifndef REGISTRATIONWINDOW_H_INCLUDED
#define REGISTRATIONWINDOW_H_INCLUDED

#include <iostream>
#include "User.h"  // Connecting Class User to work with user

using namespace std;

class RegistrationWindow //Simplified console version of the registration window
{
public:
    User registerNewUser();
    void LoginUser(User& user);  
    void LoginAdmin(User& user);     
    void quitAccount(User& user);
    void saveToFile(const User& user); 
    void saveChangedDataToFile(const User& user);

    void showMenu(User& user);
private:
    // Validation of data
    bool validateUserData(const User& user); 
    void inputUserData(User& user);

    
};

#endif // REGISTRATIONWINDOW_H

