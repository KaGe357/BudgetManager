#ifndef OPERATIONMANAGER_H
#define OPERATIONMANAGER_H

#include <iostream>
#include <vector>
#include "Operation.h"
#include "IncomeFile.h"
#include "ExpenseFile.h"
#include "UserManager.h"
#include "DateMethods.h"

using namespace std;

class OperationManager
{
    DateMethods dm;
    // UserManager userManager;
    IncomeFile incomeFile;
    ExpenseFile expenseFile;



    int loggedUserId;

public:
    OperationManager(string incomeDataFilename, string expenseDataFilename, int loggedUserId) : incomeFile(incomeDataFilename), expenseFile(expenseDataFilename)
    {
        // loggedUserId=userManager.getLoggedUserId();
        incomeFile.loadIncomesFromFile(loggedUserId);
        expenseFile.loadExpensesFromFile(loggedUserId);

    }
    void addIncome();
    void addExpense();


};
#endif
