#ifndef USERFILE_H
#define USERFILE_H

#include <iostream>
#include <vector>
#include "Markup.h"
#include "User.h"
//#include "AdditionalMethods.h"

using namespace std ;

class UserFile
{
    const string USER_DATA_FILENAME;

    bool isFileEmpty(const string& fileName);
    string convertUserDataToSeparatedForFileSaves(User user);
    User getUserData(string userDataSeparatedWithVerticalLine);
    string convertIntToStr(int number);

public:
    UserFile(string userDataFilename) : USER_DATA_FILENAME(userDataFilename){};
    void appendUserToFile(User user);
    vector <User> loadUsersFromFileToVector();


};

#endif
