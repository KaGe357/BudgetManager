#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User
{
    int id;
    string name,lastName,login,password;



public:
    int getId();
    string getName() const;
    string getLastName() const;
    string getLogin() const;
    string getPassword() const;

    void setId(const int& newId);
    void setName(const string& newName);
    void setLastName(const string& newLastName);
    void setLogin(const string& newLogin);
    void setPassword(const string& newPassword);
};

#endif
