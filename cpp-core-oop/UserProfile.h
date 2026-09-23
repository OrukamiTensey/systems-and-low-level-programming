#ifndef USERPROFILE_H_INCLUDED
#define USERPROFILE_H_INCLUDED

#include "User.h"

using namespace std;

class UserProfile
{
private:
    void changeEmail(User& user);
    void changeName(User& user);           
    void changeBirthDate(User& user);            
    void changeWeight(User& user);            
    void changeHeight(User& user);            
    void changeSex(User& user);            
    void changeGoal(User& user);           
    void changePhysicalActivity(User& user);           
    void changeAllData(User& user);
public:
	void Menu(User& user);
	void subMenu(User& user);
	void showMenu();
	void showSubMenu();
};

#endif
