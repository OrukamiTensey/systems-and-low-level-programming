#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "RegistrationWindow.h"
#include "User.h"
#include "Nutrition.h"
#include "CalorieCounting.h"
#include "ActivityH.h"
#include "UserProfile.h"

#include <iostream>
#include <fstream>
#include <sstream>

class App
{
public:
	User user;

	RegistrationWindow Reg_W; 
	Nutrition Nutrition_W;
	CalorieCounting CalCount_W; 
	User_activity Activity_W;
	UserProfile Profile_W;

	App() : 
		Reg_W(), 
		Nutrition_W(), 
		CalCount_W(&user, user.getSex(), 0, 0, 0, 1.2, user.getGoal()),   
		Activity_W(),
		Profile_W() {};  
	 
	void start();

private:
	void showMainMenu();
	void handleRegistration(User &user);
	void handleNutrition(User& user); 
	void handleCalCount(User& user);
	void handleActivity(User& user);
	void handleUserProfile(User& user); 
	void loadUserData(User& user);
	void initializeCalorieCounting();
};

#endif // APP_H