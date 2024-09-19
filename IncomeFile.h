#ifndef INCOMEFILE_H
#define INCOMEFILE_H

#include <iostream>
#include <vector>
#include "Markup.h"
#include "Operation.h"

#include "DateMethods.h"

using namespace std ;

class IncomeFile
{
    const string INCOME_FILENAME;

    bool isFileEmpty(const string& fileName);
    vector<Operation> incomes;

    DateMethods dm;

public:
    IncomeFile(string incomeDataFilename) : INCOME_FILENAME(incomeDataFilename) {};
    void addIncomeToFile(Operation operation);
    vector <Operation> loadIncomesFromFile(int loggedUserId);
    int getNewOperationId();


};

#endif
