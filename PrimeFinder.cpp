// PrimeFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <future>
#include <functional>
#include "Utils/Console.h"
#include <chrono>
#include <fstream>
#include "Utils/Temporal.h"
#include "Classes/PrimalityTest.h"

using namespace std;

const int STARTING_PRIMALITY_TEST_NUMBER = 2;
const size_t MIN_BUS_SIZE = 10000;

size_t nearestNext(size_t number, size_t next) {
    if (number == 0) {
        return 0;
    }

    size_t distanceToNext = number % next;

    if (distanceToNext == 0) {
        return number;
    }
    else {
        return (number + next) - distanceToNext;
    }
}

// TODO it might be good to receive an address to a bus so we don't create a new one here
vector<vector<size_t>> sievePrep(size_t upToInclusive) {
    vector<vector<size_t>> buses;

    const size_t BUS_COUNT = (upToInclusive + MIN_BUS_SIZE - 1) / MIN_BUS_SIZE;
    const size_t BUS_SIZE = MIN_BUS_SIZE;

    size_t primalityTestNumber = STARTING_PRIMALITY_TEST_NUMBER;

    for (size_t busIndex = 0; busIndex < BUS_COUNT; busIndex++)
    {
        vector<size_t> bus;

        size_t maxPrimalityTestNumber = nearestNext(primalityTestNumber, MIN_BUS_SIZE);

        if (maxPrimalityTestNumber == primalityTestNumber) {
            maxPrimalityTestNumber += MIN_BUS_SIZE;
        }

        while (primalityTestNumber <= maxPrimalityTestNumber) {
            bus.push_back(primalityTestNumber);

            primalityTestNumber++;
        }

        buses.push_back(bus);
    }

    return buses;
}

vector<size_t> sieve(vector<size_t> bus, size_t divisor)
{
    vector<size_t> sieved;

    for (size_t i = 0; i < bus.size(); i++)
    {
        if (bus[i] == divisor || bus[i] % divisor != 0) {
            sieved.push_back(bus[i]);
        }
    }

    return sieved;
}

void sieveThreadedPointer(vector<size_t>& bus, size_t divisor) {
    bus = sieve(bus, divisor);
}

int64_t linearFindGtIndexInList(size_t number, vector<size_t> bus)
{
    for (size_t i = 0; i < bus.size(); i++)
    {
        if (bus[i] > number) {
            return i;
        }
    }

    return -1;
}

int64_t btsFindGtIndexInList(
    size_t number,
    vector<size_t> bus,
    int64_t leftMostIndex = -1,
    int64_t rightMostIndex = -1
) {
    // Avoid silly halvings (they do happen, seems just a bad bound check when btsFindGtIndexInList is recursive called, but this'll do)
    if (leftMostIndex > rightMostIndex) {
        return -1;

        //throw invalid_argument("Left-most index of btsFindGtIndexInList bigger than rightMostIndex (what?!)");
    }

    if (leftMostIndex == -1 && rightMostIndex == -1) {
        leftMostIndex = 0;
        rightMostIndex = bus.size() - 1;
    }

    size_t middleIndex = leftMostIndex + (rightMostIndex - leftMostIndex) / 2; // These divisions floor by default https://stackoverflow.com/a/21271883
    size_t middle = bus[middleIndex];

    /**
     * Ideas on how to make this work:
     * 
     * - Either find exactly the index of the number
     * - find a pair of indices where {x1 < number} and {x2 > number} by 1 index
     * - or if the number is "cornered" such as that {number < left-most} or {number > right-most}, return -1 (is this really necessary?)
     */

    // nextNumberNoOverflow - if the number next to the middle index is not an overflow relative to rightMostIndex
    // middleMatch - If the middle is equal number
    // numberIsSandwiched - If middle is less than number, but the next number (provided not an overflow) is greater than number (1 < 2 > 3)
    bool nextNumberNoOverflow = middleIndex + 1 <= rightMostIndex,
        middleMatch = middle == number,
        numberIsSandwiched = middle < number && bus[middleIndex] > number;

    // If the middle matches the number and the next number is not an overflow, we return the next number. If there is an overflow, we immediately return false.
    if (middle == number || numberIsSandwiched) {
        return nextNumberNoOverflow ? middleIndex + 1 : -1;
    }

    int64_t leftMostSearch = -1, rightMostSearch = -1;

    if (number < middle) {
        leftMostSearch = btsFindGtIndexInList(number, bus, leftMostIndex, middleIndex - 1);
    }
    else {
        rightMostSearch = btsFindGtIndexInList(number, bus, middleIndex + 1, rightMostIndex);
    }

    if (leftMostSearch != -1) {
        return leftMostSearch;
    }
    else if (rightMostSearch != -1) {
        return rightMostSearch;
    }

    return -1;
}

int64_t findGtIndexInList(
    size_t number,
    vector<size_t> bus,
    bool useLinear = false
) {
    if (useLinear) {
        // Slow O(n)
        return linearFindGtIndexInList(number, bus);
    }

    // Fast O(log n) if it's working.
    return btsFindGtIndexInList(number, bus);
}

struct FindNextGtInBusResult {
    size_t value;
    size_t index;
};

struct FindNextGtIndexResult {
    bool found = false;
    size_t busIndex;
    FindNextGtInBusResult inBusFindResult;
};

FindNextGtIndexResult findNextGt(size_t number, vector<vector<size_t>> buses, size_t upToInclusive) {
    const size_t BUS_COUNT = buses.size();
    const size_t BUS_SIZE = MIN_BUS_SIZE;
    
    /**
     * TODO we should not be guessing this. Based on the bus size and index, we should be able to know the upper and lower bound of the bus and return the correct index.
     * We can even pass the hint of the upper/lower bounds of the bus
     */
    size_t guessNumberBusIndex = floor(number/BUS_SIZE);
    size_t nextGtIndex;
    bool nextGtFound = false;

    while (guessNumberBusIndex < BUS_COUNT) {
        int64_t busSearchResult = findGtIndexInList(number, buses[guessNumberBusIndex], true);

        if (busSearchResult >= 0) {
            nextGtIndex = busSearchResult;
            nextGtFound = true;
            break;
        }

        guessNumberBusIndex++;
    }

    FindNextGtIndexResult result;

    if (nextGtFound) {
        result.found = true;
        result.busIndex = guessNumberBusIndex;

        result.inBusFindResult.index = nextGtIndex;
        result.inBusFindResult.value = buses[result.busIndex][result.inBusFindResult.index];
    }

    return result;
}

bool isNumberDivisibleByNumbersLt(size_t number, vector<size_t>& bus) {
    size_t busSize = bus.size();

    for (size_t j = 0; j < busSize; j++) {
        Console::Print(to_string(bus[j]));

        // Terminate as soon as number is bigger than result
        if (bus[j] > number) {
            return false;
        }

        if (number % bus[j] == 0) {
            return true;
        }
    }

    // Unlikely to end up here but just in case.
    return false;
}

bool threadedIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses) {
    std::vector<thread> threads;

    for (size_t busIndex = 0; busIndex <= result.busIndex; busIndex++)
    {
        threads.push_back(thread(isNumberDivisibleByNumbersLt, result.inBusFindResult.value, ref(buses[busIndex])));
    }

    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    return false;
}

bool isFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses) {
    std::vector<future<bool>> futures;

    for (size_t busIndex = 0; busIndex <= result.busIndex; busIndex++)
    {
        futures.push_back(async(isNumberDivisibleByNumbersLt, result.inBusFindResult.value, ref(buses[busIndex])));
    }

    for (size_t i = 0; i < futures.size(); i++)
    {
        bool hasDivisible = futures[i].get();
        
        Console::Print("Future=" + to_string(i));

        if (hasDivisible) {
            return true;
        }
    }

    return false;
}

bool linearIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses) {
    for (size_t i = 0; i <= result.busIndex; i++)
    {
        size_t busSize = buses[i].size();

        for (size_t j = 0; j < busSize; j++) {
            Console::Print("linearIsFindResultDivisibleByLtNumbersInBuses=" + to_string(buses[i][j]));

            // Terminate as soon as number is bigger than result
            if (buses[i][j] > result.inBusFindResult.value) {
                return false;
            }

            if (result.inBusFindResult.value % buses[i][j] == 0) {
                return true;
            }
        }
    }

    return false;
}

ofstream createNewPrimeNumbersFile() {
    string filename = "PRIMES_GENERATED_" + to_string(Temporal::timestampNow()) + ".txt";

    ofstream fileStream;

    fileStream.open(filename);

    return fileStream;
}

void SieveOfEratosthenes(const size_t upToInclusive)
{
    vector<vector<size_t>> buses = sievePrep(upToInclusive);
    std::vector<std::thread> threads;
    
    size_t divisor = STARTING_PRIMALITY_TEST_NUMBER;

    while (divisor <= upToInclusive) {
        threads.clear();

        for (size_t busIndex = 0; busIndex < buses.size(); busIndex++)
        {
            threads.push_back(thread(sieveThreadedPointer, ref(buses[busIndex]), divisor));
        }

        // Wait for all threads
        for (thread& t : threads) {
            t.join();
        }

        bool canUseResultAsNextDivisor = false;
        FindNextGtIndexResult candidateDivisor;

        while (!canUseResultAsNextDivisor) {
            // Find the next divisor 
            candidateDivisor = findNextGt(divisor, buses, upToInclusive);

            // If a candidate divisor can't be found, it's likely because we have exhausted all the numbers up to upToInclusive
            if (!candidateDivisor.found) {
                // Setting the divisor higher than upToInclusive will terminate all loops.
                divisor = upToInclusive + 1;

                break;
            }

            // Check if the candidateDivisor is divisible by the numbers less than the ones sieved    
            canUseResultAsNextDivisor = linearIsFindResultDivisibleByLtNumbersInBuses(candidateDivisor, buses);
            //canUseResultAsNextDivisor = threadedIsFindResultDivisibleByLtNumbersInBuses(candidateDivisor, buses);

            if (canUseResultAsNextDivisor) {
                divisor = candidateDivisor.inBusFindResult.value;
            }
        }
    }

    // Open stream
    ofstream file = createNewPrimeNumbersFile();

    for (size_t busIndex = 0; busIndex < buses.size(); busIndex++)
    {
        for (size_t numberIndex = 0; numberIndex < buses[busIndex].size(); numberIndex++) {
            file << to_string(buses[busIndex][numberIndex]) + "\n";
        }
    }

    file.close();
}

int main()
{
    constexpr size_t mersenne_19digits{ 2305843009213693951 };
    constexpr size_t isthisprime{ 541 };

    //int64_t x = btsFindGtIndexInList(3, { 3, 5, 7, 11, 13, 19 });

    //cout << to_string(UINT64_MAX);

    //cout << "# PrimeFinder\n";
    //cout << "Hello CSP3341! - SN 10673966\n";

    SieveOfEratosthenes(1000); // From 1000000, adding three more zeroes will bring your computer to its knees (upwards to 10GB memory usage and 440+ threads simultaneously)
    //PrimalityTest::Test(UINT64_MAX);
    //if (primality_test(UINT64_MAX)) {
    //    cout << "Yes";
    //}
    //else {
    //    cout << "Naur";
    //}
}
