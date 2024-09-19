#include "BudgetManager.h"
#include "UserManager.h"
#include "AdditionalMethods.h"
#include "Operation.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>

void BudgetManager::loadIncomeOperations()
{
    incomeFile.loadIncomesFromFile(LOGGED_USER_ID);
}

void BudgetManager::loadExpenseOperations()
{
    expenseFile.loadExpensesFromFile(LOGGED_USER_ID);
}

char BudgetManager::chooseOptionAtOperationMenu()
{
    cin.ignore();
    char choice;

    system("cls");

    cout << "---------------------------" << endl;
    cout << " >>>     USER MENU      <<<" << endl;
    cout << "---------------------------" << endl;
    cout << "Twoje id: " << LOGGED_USER_ID << endl;
    cout << "---------------------------" <<endl;
    cout << "1. Dodaj przychod" << endl;
    cout << "2. Dodaj wydatek" << endl;
    cout << "3. Bilans obecnego miesiaca" << endl;
    cout << "4. Bilans poprzedniego miesiaca" << endl;
    cout << "5. Bilans z okresu" << endl;
    cout << "---------------------------" << endl;
    cout << "6. Zmiana hasla" << endl;
    cout << "7. Wyloguj" << endl;
    cout << "---------------------------" << endl;
    cout << "Twoj wybor: ";
    choice = AdditionalMethods::loadCharacter();

    return choice;
}

void BudgetManager::addIncome()
{
    Operation newIncome;
    newIncome.id=incomeFile.getNewOperationId();
    newIncome.userId=LOGGED_USER_ID;

    cout << "Podaj date przychodu (YYYY-MM-DD): ";
    string date;
    cin >> date;
    while(date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        cout << "Podaj poprawna date przychodu (YYYY-MM-DD): ";
       cin >> date;
    }
    while(!dm.isDateValidInCurrentMonth(dm.convertStringDateWithDashesToInt(date)))
    {
        cout << "Data nie moze przekraczac pierwszego/ostatniego dnia obecnego miesiaca. Wprowadz ponownie"<<endl;
        cin >> date;
    }
    newIncome.date=dm.convertStringDateWithDashesToInt(date);

    cout << "Podaj przedmiot przychodu: ";
    string description;
    cin.ignore();
    getline(cin, description);
    newIncome.item=description ;

    cout << "Podaj kwote przychodu: ";
    double amount;
    cin >> amount;
    newIncome.amount=amount;

    cout << "Czy zapisac przychod ? T/N " << endl;
    cout << "------------------------"<<endl;
    char choice;
    cin >> choice;
    if(choice=='T' || choice == 't')
    {
        incomeFile.addIncomeToFile(newIncome);

    cout << "Przychod dodany pomyslnie!" << endl;
    system("pause");
    }

}
void BudgetManager::addExpense()
{
    Operation newExpense;
    newExpense.id=expenseFile.getNewOperationId();
    newExpense.userId=LOGGED_USER_ID;

    cout << "Podaj date wydatku (YYYY-MM-DD): ";
    string date;
    cin >> date;
    while(date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        cout << "Podaj poprawna date przychodu (YYYY-MM-DD): ";
       cin >> date;

    }
    while(!dm.isDateValidInCurrentMonth(dm.convertStringDateWithDashesToInt(date)))
    {
        cout << "Data nie moze przekraczac pierwszego/ostatniego dnia obecnego miesiaca. Wprowadz ponownie"<<endl;
        cin >> date;
    }
    newExpense.date=dm.convertStringDateWithDashesToInt(date);

    cout << "Podaj opis wydatku: ";
    string description;
    cin.ignore();
    getline(cin, description);
    newExpense.item=description;

    cout << "Podaj kwote wydatku: ";
    double amount;
    cin >> amount;
    newExpense.amount=amount;


    cout << "Czy zapisac wydatek ? T/N " << endl;
    cout << "------------------------"<<endl;
    char choice;
    cin >> choice;
    if(choice=='T' || choice == 't')
    {
    expenseFile.addExpenseToFile(newExpense);

    cout << "Wydatek dodany pomyslnie!" << endl;
    system("pause");
    }

}

void BudgetManager::getPreviousMonthDetails(int& year, int& month) {
    DateMethods dm;
    int currentYear = dm.getCurrentYear();
    int currentMonth = dm.getCurrentMonth();

    month = currentMonth - 1;
    year = currentYear;

    if (month == 0) {
        month = 12;
        year--;
    }
}

vector<Operation> BudgetManager::filterOperationsByMonth(const vector<Operation>& operations, int year, int month) {
    vector<Operation> filteredOperations;
    for (const auto& operation : operations) {
        int opYear = operation.date / 10000;
        int opMonth = (operation.date % 10000) / 100;

        if (opYear == year && opMonth == month) {
            filteredOperations.push_back(operation);
        }
    }
    return filteredOperations;
}

void BudgetManager::sortOperationsByDate(vector<Operation>& operations) {
    sort(operations.begin(), operations.end(), [](const Operation& a, const Operation& b) {
        return a.date < b.date;
    });
}

void BudgetManager::printOperations(const vector<Operation>& operations, const string& type) {
    DateMethods dm;
    cout << type << endl << endl;
    for (const auto& operation : operations) {
        cout << "Data: " << dm.convertDateToStringWithDashes(operation.date)
             << ", Opis: " << operation.item
             << ", Kwota: " << fixed << setprecision(2) << operation.amount
             << endl
             << "-------------------------------------------------------"
             << endl << endl;
    }
}

double BudgetManager::calculateTotal(const vector<Operation> &operations) {
    return accumulate(operations.begin(), operations.end(), 0.0,
        [](double sum, const Operation& operation) {
            return sum + operation.amount;
        });
}

void BudgetManager::calculateBalanceForThePreviousMonth() {
    DateMethods dm;
    int previousYear, previousMonth;
    getPreviousMonthDetails(previousYear, previousMonth);

    vector<Operation> incomes = incomeFile.loadIncomesFromFile(LOGGED_USER_ID);
    vector<Operation> expenses = expenseFile.loadExpensesFromFile(LOGGED_USER_ID);

    vector<Operation> previousMonthIncomes = filterOperationsByMonth(incomes, previousYear, previousMonth);
    vector<Operation> previousMonthExpenses = filterOperationsByMonth(expenses, previousYear, previousMonth);

    sortOperationsByDate(previousMonthIncomes);
    sortOperationsByDate(previousMonthExpenses);

    printOperations(previousMonthIncomes, "Przychody za poprzedni miesiac:");
    printOperations(previousMonthExpenses, "Wydatki za poprzedni miesiac:");

    double totalIncome = calculateTotal(previousMonthIncomes);
    double totalExpense = calculateTotal(previousMonthExpenses);

    double balance = totalIncome - totalExpense;

    cout << ">>> Bilans za poprzedni miesiac: " << fixed << setprecision(2) << balance << " <<<" << endl;
}

void BudgetManager::calculateBalanceForTheCurrentMonth() {
    DateMethods dm;
    int currentYear = dm.getCurrentYear();
    int currentMonth = dm.getCurrentMonth();

    vector<Operation> incomes = incomeFile.loadIncomesFromFile(LOGGED_USER_ID);
    vector<Operation> expenses = expenseFile.loadExpensesFromFile(LOGGED_USER_ID);

    vector<Operation> currentMonthIncomes = filterOperationsByMonth(incomes, currentYear, currentMonth);
    vector<Operation> currentMonthExpenses = filterOperationsByMonth(expenses, currentYear, currentMonth);

    sortOperationsByDate(currentMonthIncomes);
    sortOperationsByDate(currentMonthExpenses);

    printOperations(currentMonthIncomes, "Przychody za obecny miesiac:");
    printOperations(currentMonthExpenses, "Wydatki za obecny miesiac:");

    double totalIncome = calculateTotal(currentMonthIncomes);
    double totalExpense = calculateTotal(currentMonthExpenses);

    double balance = totalIncome - totalExpense;

    cout << ">>> Bilans za obecny miesiac: " << fixed << setprecision(2) << balance << " <<<" << endl;
}

void BudgetManager::calculateBalanceForDateRange(const string& startDateStr, const string& endDateStr) {
    DateMethods dm;

    int startDate = dm.convertStringDateWithDashesToInt(startDateStr);
    int endDate = dm.convertStringDateWithDashesToInt(endDateStr);

    vector<Operation> incomes = incomeFile.loadIncomesFromFile(LOGGED_USER_ID);
    vector<Operation> expenses = expenseFile.loadExpensesFromFile(LOGGED_USER_ID);

    vector<Operation> filteredIncomes, filteredExpenses;
    for (const auto& income : incomes) {
        if (income.date >= startDate && income.date <= endDate) {
            filteredIncomes.push_back(income);
        }
    }

    for (const auto& expense : expenses) {
        if (expense.date >= startDate && expense.date <= endDate) {
            filteredExpenses.push_back(expense);
        }
    }

    sortOperationsByDate(filteredIncomes);
    sortOperationsByDate(filteredExpenses);

    printOperations(filteredIncomes, "Przychody:");
    printOperations(filteredExpenses, "Wydatki:");

    double totalIncome = calculateTotal(filteredIncomes);
    double totalExpense = calculateTotal(filteredExpenses);


    double balance = totalIncome - totalExpense;


    cout << ">>> Bilans od " << startDateStr << " do " << endDateStr << ": "
         << fixed << setprecision(2) << balance << " <<<" << endl;
}


void BudgetManager::changePassword(int loggedUserId){
    UserManager userManager("users.xml");
    string oldPassword;
    string newPassword;

    cout << "Podaj nowe haslo: ";
    cin >> newPassword;
    userManager.updateUserPassword(loggedUserId,newPassword);

}
