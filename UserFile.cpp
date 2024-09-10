#include "UserFile.h"
#include <fstream>



vector <User> UserFile::loadUsersFromFileToVector()
{
    CMarkup xml;
    User user;
    vector<User> users;


    xml.Load(USER_DATA_FILENAME);

    if (xml.FindElem("Users")) {
        xml.IntoElem();

        while (xml.FindElem("User")) {
            xml.IntoElem();
            if (xml.FindElem("Id"))
            {
                int id = stoi(xml.GetData());
                user.setId(id);
            }
            if (xml.FindElem("Name")) user.setName(xml.GetData());
            if (xml.FindElem("LastName")) user.setLastName(xml.GetData());
            if (xml.FindElem("Login")) user.setLogin(xml.GetData());
            if (xml.FindElem("Password")) user.setPassword(xml.GetData());

            users.push_back(user);

            xml.OutOfElem();
        }
    }

    return users;
}


void UserFile::appendUserToFile(User user)
{
    CMarkup xml;
    xml.Load(USER_DATA_FILENAME.c_str());
    if(isFileEmpty(USER_DATA_FILENAME))
    {
    xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    xml.AddElem("Users");
    } else
    {
        xml.FindElem("Users");
    }



    xml.IntoElem();
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("Id", user.getId());
    xml.AddElem("Name", user.getName());
    xml.AddElem("LastName", user.getLastName());
    xml.AddElem("Login", user.getLogin());
    xml.AddElem("Password", user.getPassword());
    xml.OutOfElem();

    xml.Save(USER_DATA_FILENAME.c_str());
}


bool UserFile::isFileEmpty(const string& fileName) {
    ifstream file(fileName);
    return file.peek() == ifstream::traits_type::eof();
}
