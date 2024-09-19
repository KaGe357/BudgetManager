#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <iostream>
#include <vector>
#include "Operation.h"
#include "IncomeFile.h"
#include "ExpenseFile.h"
#include "UserManager.h"
#include "UserFile.h"
#include "DateMethods.h"


using namespace std;

class BudgetManager
{

    int LOGGED_USER_ID;

    IncomeFile incomeFile;
    ExpenseFile expenseFile;
    UserFile userFile;



    vector<Operation> incomes;
    vector<Operation> expenses;

    Operation addOperationDetails();
    double calculateBalance(int startDate, int endDate);


    DateMethods dm;

public:

    BudgetManager(string userFilename, string incomeFilename, string expenseFilename, int LOGGED_USER_ID)
        :userFile(userFilename), incomeFile(incomeFilename), expenseFile(expenseFilename), LOGGED_USER_ID(LOGGED_USER_ID) {}

    void loadIncomeOperations();
    void loadExpenseOperations();
    char chooseOptionAtMainMenu();
    char chooseOptionAtOperationMenu();
    void registerNewUser();
    void loginUser();
    void addIncome();
    void addExpense();
    void getPreviousMonthDetails(int& year, int& month);
    vector<Operation>filterOperationsByMonth(const vector<Operation>& operations, int year, int month);
    void sortOperationsByDate(vector<Operation>& operations);
    void printOperations(const vector<Operation>& operations, const string& type);
    double calculateTotal(const vector<Operation>& operations);
    void calculateBalanceForTheCurrentMonth();
    void calculateBalanceForThePreviousMonth();
    void calculateBalanceForDateRange(const string& startDateStr, const string& endDateStr);
    void changePassword(int loggedUserId);


};
#endif
