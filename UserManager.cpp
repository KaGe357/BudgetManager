#include "UserManager.h"
#include "AdditionalMethods.h"



void UserManager::registerNewUser()
{
    User user = giveNewUserData();

    users.push_back(user);
    userFile.appendUserToFile(user);

    cout << endl << "Konto zalozono pomyslnie" << endl << endl;
    system("pause");
}
int UserManager::loginUser()
{
    User user;
    int id;
    string login = "", password = "";

    cout << endl << "Podaj login: ";
    getline(cin,login);

    for(int i=0; i<users.size(); i++)
    {
        if(users[i].getLogin() == login)
        {
            for (int tries = 3; tries > 0; tries--)
            {
                cout << "Podaj haslo. Pozostalo prob: " << tries << ": ";
                getline(cin,password);

                if (users[i].getPassword() == password)
                {
                    cout << endl << "Zalogowales sie." << endl << endl;
                    //system("pause");
                    loggedUserId = users[i].getId();
                    cout << "Wcisnij enter by przejsc dalej" <<endl;
                    return loggedUserId;
                }
            }
            cout << "Wprowadzono 3 razy bledne haslo." << endl;
            system("pause");
            return 0;
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl << endl;
    system("pause");
    return 0;
}

User UserManager::giveNewUserData()
{
    User user;

    user.setId(getNewUserId());
    string name;
    string lastName;
    string login;
    string password;
    do
    {
        cout << "Podaj imie: ";
        cin >> name;
        user.setName(name);

        cout << "Podaj nazwisko: ";
        cin >> lastName;
        user.setLastName(lastName);

        cout << "Podaj login: ";
        cin >> login;
        user.setLogin(login);
    }
    while (isThereALogin(user.getLogin()) == true);

    cout << "Podaj haslo: ";
    cin >> password;
    user.setPassword(password);

    return user;
}

int UserManager::getNewUserId()
{
    int newId = (users.empty()) ? 1 : users.back().getId() + 1;
    cout << "Nowe ID: " << newId << endl; // debug
    return newId;
}


bool UserManager::isThereALogin(string login)
{
    for(int i=0; i<users.size(); i++)
    {
        if(users[i].getLogin()==login)
        {
            cout << endl << "Istnieje uzytkownik o takim loginie." << endl;
            return true;
        }
    }
}
void UserManager::printAllUsers()
{
    for(int i=0; i<users.size(); i++)
    {
        cout << users[i].getId() << endl;
        cout << users[i].getName() << endl;
        cout << users[i].getLastName()<<endl;
        cout << users[i].getLogin() << endl;
        cout << users[i].getPassword() << endl;
    }
}



int UserManager::getLoggedUserId()
{
    return loggedUserId;
}

bool UserManager::isAUserLogged()
{
    if(getLoggedUserId()>0)
        return true;
    else
        return false;
}
void UserManager::logoutUser()
{
    loggedUserId=0;
}


char UserManager::chooseOptionAtMainMenu()
{
    char choice;

    system("cls");
    cout << "    >>> MAIN MENU <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz" << endl;
    cout << "---------------------------" << endl;
    cout << "Twoj wybor: ";
    choice = AdditionalMethods::loadCharacter();

    return choice;
}
void UserManager::updateUserPassword(int userId, const string &newPassword) {
    CMarkup xml;
    xml.Load("users.xml");

    if (xml.FindElem("Users")) {
        xml.IntoElem();
        while (xml.FindElem("User")) {
            xml.FindChildElem("Id");
            int id = stoi(xml.GetChildData());
            if (id == userId) {
                xml.FindChildElem("Password");
                xml.SetChildData(newPassword);
                break;
            }
        }
        xml.OutOfElem();
    }

    xml.Save("users.xml");
}
