#include <iostream>
#include "UserManager.h"


using namespace std;

int main()
{

   UserManager userManager("Testy.xml");

   //userManager.loginUser();

   userManager.registerNewUser();
   userManager.printAllUsers();
}
