#include "IncomeFile.h"
#include "AdditionalMethods.h"


vector <Operation> IncomeFile::loadIncomesFromFile(int loggedUserId)
{
    vector<Operation> incomes;
    CMarkup xml;
    bool fileLoaded = xml.Load(INCOME_FILENAME);

    if (fileLoaded) {
        xml.FindElem("Incomes");
        xml.IntoElem();

        while (xml.FindElem("Income")) {
            Operation income;
            xml.FindChildElem("Id");
            income.id = stoi(xml.GetChildData());
            xml.FindChildElem("UserId");
            income.userId = stoi(xml.GetChildData());
            xml.FindChildElem("Date");
            income.date = stoi(xml.GetChildData());
            xml.FindChildElem("Item");
            income.item = xml.GetChildData();
            xml.FindChildElem("Amount");
            income.amount = stod(xml.GetChildData());

            incomes.push_back(income);
        }
    }
    return incomes;

}
int IncomeFile::getNewOperationId()
{
    CMarkup xml;
    int lastOperationId = 0;


    bool fileLoaded = xml.Load(INCOME_FILENAME);
    if (!fileLoaded)
    {
        cout << "Nie mozna otworzyc pliku XML: " << INCOME_FILENAME << endl;
        return 1;
    }

    xml.FindElem("Incomes");
    xml.IntoElem();

    while (xml.FindElem("Income"))
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
void IncomeFile::addIncomeToFile(Operation operation)
{
    CMarkup xml;

    bool fileExists = xml.Load(INCOME_FILENAME);

    if (!fileExists)
    {

        xml.AddElem("Incomes");
    }


    xml.FindElem("Incomes");
    xml.IntoElem();

    xml.AddElem("Income");
    xml.IntoElem();
    xml.AddElem("Id", operation.id);
    xml.AddElem("UserId", operation.userId);
    xml.AddElem("Date", operation.date);
    xml.AddElem("Item", operation.item);
    xml.AddElem("Amount", operation.amount);
    xml.OutOfElem();


    xml.Save(INCOME_FILENAME);
}
