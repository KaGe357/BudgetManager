#ifndef ADDITIONALMETHODS_H
#define ADDITIONALMETHODS_H
#include <iostream>
#include <sstream>

using namespace std;

class AdditionalMethods
{
public:
    static string loadLine();
    static char loadCharacter();
    static int conversionStringToInt(string integer);
    static string converionIntToString(int integer);
    static string converionFloatToString( float number);
};
#endif
