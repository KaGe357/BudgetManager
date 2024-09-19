#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include "User.h"
#include "UserFile.h"

using namespace std;

class UserManager
{


    vector<User>users;

    bool isThereALogin(string login);
    UserFile userFile;
    User giveNewUserData();
    int getNewUserId();

public:
    int loggedUserId;
    UserManager(string userDataFilename)
        : userFile(userDataFilename), loggedUserId(0) //
    {
        users = userFile.loadUsersFromFileToVector();
    }

    // UserManager() : loggedUserId(0) {}
    void registerNewUser();
    void printAllUsers();
    int loginUser();
    bool isAUserLogged();
    int getLoggedUserId();
    void logoutUser();
    char chooseOptionAtMainMenu();
    void updateUserPassword(int userId, const string &newPassword);

};
#endif
