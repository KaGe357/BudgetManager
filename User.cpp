#include "User.h"


int User::getId()
{
    return id;
}

void  User::setId(const int& newId)
{
    id=newId;
}


string  User::getName() const
{
    return name;
}

void  User::setName(const string& newName)
{
    name = newName;
}


string  User::getLastName() const
{
    return lastName;
}

void  User::setLastName(const string& newLastName)
{
    lastName = newLastName;
}


string  User::getLogin() const
{
    return login;
}

void  User::setLogin(const string& newLogin)
{
    login = newLogin;
}


string  User::getPassword() const
{
    return password;
}

void  User::setPassword(const string& newPassword)
{
    password = newPassword;
}
