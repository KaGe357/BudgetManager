#ifndef DATEMETHODS_H
#define DATEMETHODS_H

#include <string>
#include <ctime>

using namespace std;

class DateMethods
{
    int isYearLeap(int year);


public:


    int getCurrentDate();
    bool validateDate(string &date);
    int convertStringDateWithDashesToInt(const string &dateAsString);
    string convertDateToStringWithDashes(int dateAsInt);
    int getCurrentYear();
    int getCurrentMonth();
    int getDaysInMonth(int year, int month);
    bool isDateValidInCurrentMonth(int date);

};




#endif
