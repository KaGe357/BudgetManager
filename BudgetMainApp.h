#ifndef BUDGETMAINAPP_H
#define BUDGETMAINAPP_H

#include "UserManager.h"
#include "BudgetManager.h"

using namespace std;

class BudgetMainApp {
private:
    UserManager userManager;
    BudgetManager* budgetManager;
    int loggedUserId;

public:
    BudgetMainApp(const string& usersFile, const string& incomesFile, const string& expensesFile);
    ~BudgetMainApp();

    void run();  // Uruchomienie apki
    void handleLoggedInUser();  // Obs³uga zalogowanego usera
};
#endif // BUDGETMAINAPP_H
