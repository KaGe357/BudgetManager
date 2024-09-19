#ifndef EXPENSEFILE_H
#define EXPENSEFILE_H

#include <iostream>
#include <vector>
#include "Markup.h"
#include "Operation.h"

#include "DateMethods.h"

using namespace std ;

class ExpenseFile
{
    const string EXPENSE_FILENAME;

    bool isFileEmpty(const string& fileName);
    vector<Operation> expenses;

    DateMethods dm;

public:
    ExpenseFile(string expenseDataFilename) : EXPENSE_FILENAME(expenseDataFilename) {};
    void addExpenseToFile(Operation operation);
    vector <Operation> loadExpensesFromFile(int loggedUserId);
    int getNewOperationId();

};

#endif
