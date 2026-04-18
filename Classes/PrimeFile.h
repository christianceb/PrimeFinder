#pragma once
#include <fstream>
#include <string>

using namespace std;

class PrimeFile
{
public:
    PrimeFile();
    void Write(string line);

private:
    ofstream createNewPrimeNumbersFile();
    ofstream primeNumberFileStream;
};
