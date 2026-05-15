#pragma once
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Class to handle saving prime numbers into a file.
 * 
 */
class PrimeFile
{
public:
    /**
     * @brief Construct a new Prime File object
     * 
     * When instantiated, a file stream is opened. The file name is generated using createNewPrimeNumbersFile()
     * 
     * The file is only saved when Close() is called
     */
    PrimeFile();

    /**
     * @brief Write a given string into the file
     * 
     * @param line The string content to put into the file
     * @param lineBreak Whether to add a linebreak at the end of the file or not
     */
    void Write(string line, bool lineBreak = true);

    /**
     * @brief Closes the filestream open on this object
     */
    void Close();

    /**
     * @brief Get the filename of the file when this object was instantiated
     * 
     * @return string Filename of file in file stream
     */
    string filename() const { return _filename; };

private:
    string _filename;

    /**
     * @brief Create a New Prime Numbers File object only accessible in the class
     */
    void createNewPrimeNumbersFile();

    ofstream primeNumberFileStream;
};
