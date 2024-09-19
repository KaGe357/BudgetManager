#include "BudgetMainApp.h"

int main() {
    BudgetMainApp app("users.xml", "income.xml", "expense.xml");
    app.run();

}
