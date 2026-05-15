#pragma once

#include <vector>

using namespace std;

// Simple abstract data type to contain the value and the index of a possible prime when
// a number greater than a given prime in the sieve is found. Part of FindNextGtIndexResult
struct FindNextGtInBusResult {
    size_t value;
    size_t index;
};

// Simple abstract data type containing the result of FindNextGtIndexResult, the index of the
// bus, and whether a number following a given prime is found.
struct FindNextGtIndexResult {
    bool found = false;
    size_t busIndex;
    FindNextGtInBusResult inBusFindResult;
};

/**
 * @brief Eratosthenes Sieve, threaded
 * 
 */
class EratosthenesSieve
{
public:
    /**
     * @brief Construct a new Eratosthenes Sieve object
     * 
     * @param upToInclusive Populate the sieve with numbers up to this value
     * @param busSize The numbers in the sieve are going to be divided by a bus size (e.g.: busSize=10 when upToInclusive=1000 will result in 100 buses)
     * @param threadCount How many threads should be running simultaneously when we are sieving. Only one bus will be processed per thread at a time
     * @param debug Debug flag; not in use.
     */
    EratosthenesSieve(size_t upToInclusive, int busSize, int threadCount, bool debug = false);

private:
    /**
     * @brief Prepare the sieve by generating numbers into array of arrays. Arrays are split by busSize
     * 
     * @param upToInclusive Generate all numbers from STARTING_PRIMALITY_TEST_NUMBER=2 up to including this number
     * @return vector<vector<size_t>>  Vector of numbers split into busSize
     */
    vector<vector<size_t>> sievePrep(size_t upToInclusive);

    /**
     * @brief Given a number, find the nearest multiple (e.g.: if number=1777 and multiple=1000, return 2000)
     * 
     * @param number Number to find the nearest multiple
     * @param multiple The multiple to be used
     * @return size_t Nearest multiple
     */
    size_t nearestMultiple(size_t number, size_t multiple);

    /**
     * @brief Run modulo with the divisor on each number in the bus
     * 
     * @param bus Vector of [sieved] numbers
     * @param divisor The number to use when doing modulo operation against a number
     * @return vector<size_t> Result of sieved numbers
     */
    vector<size_t> sieve(vector<size_t> bus, size_t divisor);
    
    /**
     * @brief Wraps the sieve() method so that it can be called as a threaded object
     * 
     * @param bus Vector of [sieved] numbers
     * @param divisor The number to use when doing modulo operation against a number
     */
    void sieveThreadedPointer(vector<size_t>& bus, size_t divisor);

    /**
     * @brief Given an array of numbers, find the index of a number greater than the given number. Uses linear search (O^n)
     * 
     * @param number The given number
     * @param bus Array of numbers, usually sieved
     * @return int64_t Returns zero or a positive integer of the index of the number in the bus. Returns -1 if not found.
     */
    int64_t linearFindIndexOfNumGtThanGivenNumInList(size_t number, vector<size_t> bus);

    /**
     * @brief From the sieved numbers, find a number greater (Gt) than the given number
     * 
     * @param number The number that will be based on to find a number greater than it in the sieve
     * @param buses Array of sieved numbers
     * @param upToInclusive The biggest number on the sieve before it was sieved
     * @return FindNextGtIndexResult Basic struct that contains information about the operation
     */
    FindNextGtIndexResult findNumGtThanGivenNum(size_t number, vector<vector<size_t>> buses, size_t upToInclusive);

    /**
     * @brief Given an array^2 of numbers, iterate through it and check if a given number is divisible by it.
     * 
     * @param result A struct which is the result of `linearFindIndexOfNumGtThanGivenNumInList` that contains information on how to find the given number in the array of arrays
     * @param buses array^2 of numbers
     * @return true The given number has been found to be divisible by numbers lesser than it
     * @return false The given number is NOT divisible by the numbers lesser than it (likely a prime)
     */
    bool linearIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses);

private:
    const int STARTING_PRIMALITY_TEST_NUMBER = 2;
    
    size_t busSize;
    
    int threadCount;

    bool debug = false;
};
