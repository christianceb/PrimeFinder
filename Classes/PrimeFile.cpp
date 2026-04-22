#include "PrimeFile.h"
#include "../Utils/Temporal.h"

PrimeFile::PrimeFile()
{
    createNewPrimeNumbersFile();
}

void PrimeFile::Write(string line, bool lineBreak)
{
    if (primeNumberFileStream.is_open()) {
        primeNumberFileStream << line + (lineBreak ? "\n" : "");
    }
}

void PrimeFile::Close()
{
    if (primeNumberFileStream.is_open()) {
        primeNumberFileStream.close();
    }
}

void PrimeFile::createNewPrimeNumbersFile()
{
    _filename = "PRIMES_GENERATED_" + to_string(Temporal::timestampNow()) + ".txt";

    primeNumberFileStream.open(_filename);
}
