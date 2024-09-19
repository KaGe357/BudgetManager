#include "BudgetMainApp.h"

#include "BudgetMainApp.h"
#include <iostream>

BudgetMainApp::BudgetMainApp(const string& usersFile, const string& incomesFile, const string& expensesFile)
    : userManager(usersFile), budgetManager(nullptr), loggedUserId(0) {}

BudgetMainApp::~BudgetMainApp() {
    if (budgetManager != nullptr) {
        delete budgetManager;
    }
}

void BudgetMainApp::run() {
    char choice;

    while (!userManager.isAUserLogged()) {
        choice = userManager.chooseOptionAtMainMenu();

        switch (choice) {
        case '1':
            userManager.registerNewUser();
            break;
        case '2':
            loggedUserId = userManager.loginUser();
            if (loggedUserId > 0) {
                budgetManager = new BudgetManager("users.xml", "income.xml", "expense.xml", loggedUserId);
                handleLoggedInUser();
            }
            break;
        case '9':
            exit(0);
            break;
        default:
            cout << "\nNie ma takiej opcji w menu.\n\n";
            system("pause");
            break;
        }
    }
}

void BudgetMainApp::handleLoggedInUser() {
    char choice;

    while (userManager.isAUserLogged()) {
        choice = budgetManager->chooseOptionAtOperationMenu();

        switch (choice) {
        case '1':
            budgetManager->addIncome();
            break;
        case '2':
            budgetManager->addExpense();
            break;
        case '3':
            budgetManager->calculateBalanceForTheCurrentMonth();
            break;
        case '4':
            budgetManager->calculateBalanceForThePreviousMonth();
            break;
        case '5':
            {
            string startDate, endDate;
            cout << "Podaj datê pocz¹tkow¹ (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Podaj datê koñcow¹ (YYYY-MM-DD): ";
            cin >> endDate;
            budgetManager->calculateBalanceForDateRange(startDate, endDate);
            break;
            }
        case '6':
            budgetManager->changePassword(userManager.loggedUserId);
            break;
        case '7':
            userManager.logoutUser();
            delete budgetManager;
            budgetManager = nullptr;
            loggedUserId = 0;
            break;
        default:
            cout << "\nNie ma takiej opcji w menu.\n\n";
            system("pause");
            break;
        }
    }
}

