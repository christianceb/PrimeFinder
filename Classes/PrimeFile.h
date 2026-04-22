#pragma once
#include <fstream>
#include <string>

using namespace std;

class PrimeFile
{
public:
    PrimeFile();
    void Write(string line, bool lineBreak = true);
    void Close();
    string filename() const { return _filename; };

private:
    string _filename;
    void createNewPrimeNumbersFile();
    ofstream primeNumberFileStream;
};
