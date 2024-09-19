#include "DateMethods.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <string>
#include <algorithm>

int DateMethods::getCurrentDate()
{

    time_t t = time(nullptr);
    tm* now = localtime(&t);


    int dateAsInt = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;

    return dateAsInt;
}


int DateMethods::convertStringDateWithDashesToInt(const string &date)
{

    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        cout << "Niepoprawny format daty. Oczekiwano formatu YYYY-MM-DD." << endl;
        return -1;
    }


    string dateWithoutDashes = date;
    dateWithoutDashes.erase(remove(dateWithoutDashes.begin(), dateWithoutDashes.end(), '-'), dateWithoutDashes.end());


    for (char c : dateWithoutDashes)
    {
        if (!isdigit(c))
        {
            cout << "Niepoprawne znaki w dacie. Dozwolone s¹ tylko cyfry." << endl;
            return -1;
        }
    }


    int dateAsInt = stoi(dateWithoutDashes);
    return dateAsInt;
}

string DateMethods::convertDateToStringWithDashes(int dateAsInt)
{
    int year = dateAsInt / 10000;
    int month = (dateAsInt % 10000) / 100;
    int day = dateAsInt % 100;

    ostringstream oss;
    oss << setw(4) << setfill('0') << year << '-'
        << setw(2) << setfill('0') << month << '-'
        << setw(2) << setfill('0') << day;

    return oss.str();
}
int DateMethods::getCurrentYear()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

int DateMethods::getCurrentMonth()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1 + ltm->tm_mon;
}

int DateMethods::getDaysInMonth(int year, int month)
{

    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else
    {
        return 31;
    }
}

bool DateMethods::isDateValidInCurrentMonth(int date) {
    int year = date / 10000;
    int month = (date % 10000) / 100;
    int day = date % 100;

    int currentYear = getCurrentYear();
    int currentMonth = getCurrentMonth();

    if (year != currentYear || month != currentMonth) {
        return false;
    }


    int lastDayOfMonth = getDaysInMonth(currentYear, currentMonth);


    if (day > lastDayOfMonth) {
        return false;
    }

    return true;
}
