#include "EratosthenesSieve.h"
#include "../Utils/Console.h"
#include <future>
#include <thread>
#include "PrimeFile.h"
#include <cmath>
#include <functional>

using namespace std;

EratosthenesSieve::EratosthenesSieve(size_t upToInclusive, int busSize, int threadCount, bool debug)
{
    this->debug = debug;
    this->busSize = busSize;
    this->threadCount = threadCount;

    // Prepare the numbers to be sieved into "buses"
    vector<vector<size_t>> buses = sievePrep(upToInclusive);
    std::vector<std::thread> threads;

    size_t divisor = STARTING_PRIMALITY_TEST_NUMBER;

    size_t fleetSize = buses.size();

    // The sieve starts testing each number based on the current divisor we are
    // testing each number for primality
    while (divisor <= upToInclusive) {
        // Reset bus indices to go through
        size_t busIndex = 0;

        // Reset the bus index tracked to put into a thread. This is a key component
        // in ensure only n=threadCount threads will be running at a time
        size_t batchMaxBusIndex = 0;

        if (debug) {
            Console::Print("Testing divisor " + to_string(divisor));
        }

        // Iterate through the buses. Each loop is a batch of threads/buses to run
        while (busIndex < fleetSize) {
            // Clear list of finished threads from last batch
            threads.clear();

            // As each bus is put into a thread for processing, this sets the maximum
            // bus index to process on this btach
            batchMaxBusIndex += threadCount;

            // Prevent batchMaxBusIndex from overflowing the fleet size (big bad!)
            if (batchMaxBusIndex >= fleetSize) {
                batchMaxBusIndex = fleetSize;
            }

            // Iterate through the current bus index to process up to batchMaxBusIndex
            while (busIndex < batchMaxBusIndex) {
                if (debug) {
                    Console::Print("Running bus index " + to_string(busIndex + 1) + " out of " + to_string(fleetSize) + "; Divisor " + to_string(divisor) + " out of " + to_string(upToInclusive));
                }

                // Put task into threads to run in parallel
                threads.push_back(thread(&EratosthenesSieve::sieveThreadedPointer, this, ref(buses[busIndex]), divisor));

                busIndex++;
            }

            // Wait for all threads to finish
            for (thread& t : threads) {
                t.join();
            }
        }

        // The sieve for this divisor is done. Now we try and find a new divisor

        // Prep variables for finding the next divisor
        bool canUseResultAsNextDivisor = false;
        FindNextGtIndexResult candidateDivisor;

        // Iterate until we find the next divisor or until we have exhausted all numbers
        while (!canUseResultAsNextDivisor) {
            // Find the next divisor from the buses
            candidateDivisor = findNumGtThanGivenNum(divisor, buses, upToInclusive);

            // If a candidate divisor can't be found, it's likely because we have exhausted all the numbers up to upToInclusive
            if (!candidateDivisor.found) {
                // Setting the divisor higher than upToInclusive will terminate all loops.
                divisor = upToInclusive + 1;

                break;
            }

            // Check if the candidateDivisor is divisible by the numbers less than the ones sieved
            canUseResultAsNextDivisor = linearIsFindResultDivisibleByLtNumbersInBuses(candidateDivisor, buses);

            // If the number found in the result is usable, set it as our divisor
            if (canUseResultAsNextDivisor) {
                divisor = candidateDivisor.inBusFindResult.value;
            }
        }
    }

    // When the sieve is finished, save all sieved numbers into a file.
    PrimeFile file = PrimeFile();

    // Iterate through buses
    for (size_t busIndex = 0; busIndex < fleetSize; busIndex++)
    {
        // Iterate through numbers in array
        for (size_t numberIndex = 0; numberIndex < buses[busIndex].size(); numberIndex++) {
            // Write to file
            file.Write(to_string(buses[busIndex][numberIndex]));
        }
    }

    Console::Print("\nResult of Sieve of Eratosthenes can be found at " + file.filename());

    // Close file
    file.Close();
}

size_t EratosthenesSieve::nearestMultiple(size_t number, size_t multiple)
{
    if (number == 0) {
        return 0;
    }

    size_t distanceToNext = number % multiple;

    if (distanceToNext == 0) {
        return number;
    }
    else {
        return (number + multiple) - distanceToNext;
    }
}

vector<vector<size_t>> EratosthenesSieve::sievePrep(size_t upToInclusive)
{
    vector<vector<size_t>> buses;

    // Determine how many buses we need based on upToInclusive and busSize
    const size_t BUS_COUNT = (upToInclusive + busSize - 1) / busSize;
    const size_t BUS_SIZE = busSize;

    size_t primalityTestNumber = STARTING_PRIMALITY_TEST_NUMBER;

    // Iterate through buses and fill them with numbers
    for (size_t busIndex = 0; busIndex < BUS_COUNT; busIndex++)
    {
        vector<size_t> bus;

        size_t maxPrimalityTestNumber = nearestMultiple(primalityTestNumber, busSize);

        // If the maxPrimalityTestNumber is equal to the current number, we increase
        // the ceiling on this bus by the bus size.
        if (maxPrimalityTestNumber == primalityTestNumber) {
            maxPrimalityTestNumber += busSize;
        }

        // Iterate through the current number to primality test all the way
        // to the ceiling we determined earlier and put them into the bus
        while (primalityTestNumber <= maxPrimalityTestNumber) {
            bus.push_back(primalityTestNumber);

            primalityTestNumber++;
        }

        buses.push_back(bus);
    }

    return buses;
}

vector<size_t> EratosthenesSieve::sieve(vector<size_t> bus, size_t divisor)
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

void EratosthenesSieve::sieveThreadedPointer(vector<size_t>& bus, size_t divisor)
{
    bus = sieve(bus, divisor);
}

int64_t EratosthenesSieve::linearFindIndexOfNumGtThanGivenNumInList(size_t number, vector<size_t> bus)
{
    // Iterate through numbers in the list
    for (size_t i = 0; i < bus.size(); i++)
    {
        if (bus[i] > number) {
            // Return index of the number greater than the given number
            return i;
        }
    }

    // Found nothing
    return -1;
}

FindNextGtIndexResult EratosthenesSieve::findNumGtThanGivenNum(size_t number, vector<vector<size_t>> buses, size_t upToInclusive)
{
    const size_t BUS_COUNT = buses.size();
    const size_t BUS_SIZE = busSize;

    /**
     * Guess which bus index does the given number belong to
     * 
     * TODO we should not be guessing this. Based on the bus size and index, we should be able to know the upper and lower bound of the bus and return the correct index.
     * We can even pass the hint of the upper/lower bounds of the bus
     */
    size_t guessNumberBusIndex = size_t(floor(number / BUS_SIZE));

    // next [number] greater "Gt" [than the current]
    size_t nextNumGtThanGivenNumIndex;
    bool nextGtThanNumFound = false;

    // From the guessed number bus index, iterate through the rest of the buses
    while (guessNumberBusIndex < BUS_COUNT) {
        // On this bus of numbers, find a number bigger than the given number
        int64_t busSearchResult = linearFindIndexOfNumGtThanGivenNumInList(number, buses[guessNumberBusIndex]);

        // Have we found our number?
        if (busSearchResult >= 0) {
            // Fill flags and location of the number
            nextNumGtThanGivenNumIndex = busSearchResult;
            nextGtThanNumFound = true;
            break;
        }

        guessNumberBusIndex++;
    }

    FindNextGtIndexResult result;

    // If the next greater than number
    if (nextGtThanNumFound) {
        result.found = true;
        result.busIndex = guessNumberBusIndex;

        result.inBusFindResult.index = nextNumGtThanGivenNumIndex;
        result.inBusFindResult.value = buses[result.busIndex][result.inBusFindResult.index];
    }

    return result;
}

bool EratosthenesSieve::linearIsFindResultDivisibleByLtNumbersInBuses(FindNextGtIndexResult result, vector<vector<size_t>> buses)
{
    // Iterate through buses all the way to the bus where the number was found
    for (size_t i = 0; i <= result.busIndex; i++) {
        size_t busSize = buses[i].size();

        // Iterate through the numbers in the bus
        for (size_t j = 0; j < busSize; j++) {
            // Terminate as soon as number is bigger than result
            if (buses[i][j] > result.inBusFindResult.value) {
                return false;
            }

            // Number is divisible by a number smaller than it
            if (result.inBusFindResult.value % buses[i][j] == 0) {
                return true;
            }
        }
    }

    // Not divisible by numbers smaller than it.
    return false;
}
