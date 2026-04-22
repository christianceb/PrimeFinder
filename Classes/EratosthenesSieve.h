#pragma once

#include <vector>

using namespace std;

struct FindNextGtInBusResult {
    size_t value;
    size_t index;
};

struct FindNextGtIndexResult {
    bool found = false;
    size_t busIndex;
    FindNextGtInBusResult inBusFindResult;
};

class EratosthenesSieve
{
public:
    EratosthenesSieve(size_t upToInclusive);

    bool isNumberDivisibleByNumbersLt(size_t number, vector<size_t>& bus);

private:
    size_t nearestNext(size_t number, size_t next);

    vector<vector<size_t>> sievePrep(size_t upToInclusive);

    vector<size_t> sieve(vector<size_t> bus, size_t divisor);
    
    void sieveThreadedPointer(vector<size_t>& bus, size_t divisor);

    int64_t linearFindGtIndexInList(size_t number, vector<size_t> bus);

    int64_t btsFindGtIndexInList(
        size_t number,
        vector<size_t> bus,
        int64_t leftMostIndex = -1,
        int64_t rightMostIndex = -1
    );

    int64_t findGtIndexInList(
        size_t number,
        vector<size_t> bus,
        bool useLinear = false
    );

    FindNextGtIndexResult findNextGt(size_t number, vector<vector<size_t>> buses, size_t upToInclusive);

    bool threadedIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses);

    bool isFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses);

    bool linearIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses);

private:
    const int STARTING_PRIMALITY_TEST_NUMBER = 2;
    const size_t MIN_BUS_SIZE = 10000;
};
