#include "AdditionalMethods.h"


string AdditionalMethods::loadLine()
{
    string in = "";
    getline(cin, in);
    return in;
}
char AdditionalMethods::loadCharacter()
{
    string in = "";
    char character  = {0};

    while (true)
    {
        getline(cin, in);

        if (in.length() == 1)
        {
            character = in[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return character;
}
int AdditionalMethods::conversionStringToInt(string integer)
{
    int number;
    istringstream iss(integer);
    iss >> number;

    return number;
}
string AdditionalMethods::converionIntToString(int integer)
{
    ostringstream ss;
    ss << integer;
    string str = ss.str();
    return str;
}
string AdditionalMethods::converionFloatToString( float number )
{
    stringstream FloatToStr;
    string str;

    FloatToStr << number;
    FloatToStr >> str;
    FloatToStr.clear();

    return str;
}
