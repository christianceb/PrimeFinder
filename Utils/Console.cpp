#include <iostream>
#include <string>
#include "Console.h"

using namespace std;

void Console::Print(string message, bool lineBreak)
{
    cout << message + (lineBreak ? "\n" : "");
}

string Console::Read(string message)
{
    string input;

    Print(message, false);

    cin >> input;

    return input;
}

string Console::ReadLine(string message)
{
    string input;

    Print(message, false);

    cin.ignore(); // Why? User "Mitsakos" explains: https://cplusplus.com/forum/beginner/3001/
    getline(cin, input);

    return input;
}
