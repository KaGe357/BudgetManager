#include "ExpenseFile.h"


vector <Operation> ExpenseFile::loadExpensesFromFile(int loggedUserId)
{
  vector<Operation> expenses;
    CMarkup xml;
    bool fileLoaded = xml.Load(EXPENSE_FILENAME);

    if (fileLoaded) {
        xml.FindElem("Expenses");
        xml.IntoElem();

        while (xml.FindElem("Expense")) {
            Operation expense;
            xml.FindChildElem("Id");
            expense.id = stoi(xml.GetChildData());
            xml.FindChildElem("UserId");
            expense.userId = stoi(xml.GetChildData());
            xml.FindChildElem("Date");
            expense.date = stoi(xml.GetChildData());
            xml.FindChildElem("Item");
            expense.item = xml.GetChildData();
            xml.FindChildElem("Amount");
            expense.amount = stod(xml.GetChildData());

            expenses.push_back(expense);
        }
    } else {
        throw runtime_error("Nie uda³o siê za³adowaæ pliku z wydatkami.");
    }

    return expenses;
}
int ExpenseFile::getNewOperationId()
{
    CMarkup xml;
    int lastOperationId = 0;


    bool fileLoaded = xml.Load(EXPENSE_FILENAME);
    if (!fileLoaded)
    {
        cout << "Nie mozna otworzyc pliku XML: " << EXPENSE_FILENAME << endl;
        return 1;
    }

    xml.FindElem("Expenses");
    xml.IntoElem();

    while (xml.FindElem("Expense"))
    {
        xml.IntoElem();
        if (xml.FindElem("Id"))
        {
            int currentId = stoi(xml.GetData());
            if (currentId > lastOperationId)
            {
                lastOperationId = currentId;
            }
        }
        xml.OutOfElem();
    }

    return lastOperationId + 1;
}
void ExpenseFile::addExpenseToFile(Operation operation)
{
    CMarkup xml;

    bool fileExists = xml.Load(EXPENSE_FILENAME);

    if (!fileExists)
    {

        xml.AddElem("Expenses");
    }


    xml.FindElem("Expenses");
    xml.IntoElem();

    xml.AddElem("Expense");
    xml.IntoElem();
    xml.AddElem("Id", operation.id);
    xml.AddElem("UserId", operation.userId);
    xml.AddElem("Date", operation.date);
    xml.AddElem("Item", operation.item);
    xml.AddElem("Amount", operation.amount);
    xml.OutOfElem();


    xml.Save(EXPENSE_FILENAME);
}
