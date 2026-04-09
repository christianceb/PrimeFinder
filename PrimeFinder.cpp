// PrimeFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <future>

using namespace std;



vector<int> megaIterator(int inclusiveFrom, int exclusiveTo) {
    vector<int> result;

    for (int i = inclusiveFrom; i < exclusiveTo; i++) {
        cout << to_string(i) + "\n";
        result.push_back(i);
    }

    return result;
}

uint64_t nearestNext(uint64_t number, uint64_t next) {
    if (number == 0) {
        return 0;
    }

    uint64_t distanceToNext = number % next;

    if (distanceToNext == 0) {
        return number;
    }
    else {
        return (number + next) - distanceToNext;
    }
}

void SieveOfEratosthenes(uint64_t upToInclusive)
{
    vector<uint64_t> _;
    vector<vector<uint64_t>> buses;

    // TODO MAX_BUS_SIZE is probably not int and not returning a value (it's currently -1)
    const int MAX_BUS_SIZE = _.max_size(), MIN_BUS_SIZE = 1000;
    const int BUS_COUNT = ceil(upToInclusive / MIN_BUS_SIZE), BUS_SIZE = MIN_BUS_SIZE;

    uint64_t primalityTestNumber = 2;

    for (size_t busIndex = 0; busIndex < BUS_COUNT; busIndex++)
    {
        vector<uint64_t> bus;

        uint64_t maxPrimalityTestNumber = nearestNext(primalityTestNumber, MIN_BUS_SIZE);

        if (maxPrimalityTestNumber == primalityTestNumber) {
            maxPrimalityTestNumber += MIN_BUS_SIZE;
        }

        while (primalityTestNumber <= maxPrimalityTestNumber) {
            bus.push_back(primalityTestNumber);

            primalityTestNumber++;
        }

        buses.push_back(bus);
    }


    // OK - Determine bus size (BS) and how many buses (BC) we need for this operation

    // OK - Iterate through BC, fill list with size BS with numbers up to upToInclusive

    // Set counter to 2

    // Go through buses as threads and run the sieve with counter against it. Maybe pass as reference?

    // Once completed, find on which bucket <counter + 1> is. Find the first number greater than counter

    // From the bus where <counter+1> was found, iterate backwards and see if modulo by it returns 0. If it is, go back on the last step to find another number <counter + n>

    // Repeat the threaded task until upToInclusive is hit
}

void sieve_bucketer(int buckets = 2) {
    std::vector<std::thread> threads;

    //for (int i = 0; i < buckets; i++)
    //{
    //    threads.emplace_back(thread(iterator, )
    //}
    threads.emplace_back(thread(megaIterator, 0, 1000));
    threads.emplace_back(thread(megaIterator, 1000, 2000));

    for (auto& thread : threads) {
        thread.join();
    }
    
    //for (int x = 0; threads[0].size; ) {

    //}
}

vector<uint64_t> sieve(vector<uint64_t> bucket, uint64_t divisor)
{
    vector<uint64_t> sieved;

    for (uint64_t i = 0; i < bucket.size(); i++)
    {
        if (bucket[i] % divisor == 0) {
            sieved.push_back(bucket[i]);
        }
    }

    return sieved;
}

bool primality_test(uint64_t number) {
    uint64_t sqrtOf = sqrt(number);
    vector<uint64_t> primeFactors = {2, 3};
    
    //cout << to_string(UINT64_MAX/primeFactors.max_size()); // 8
    //cout << to_string(primeFactors.max_size()); // 2305843009213693951

    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    for (
        uint64_t probableFactor = 2;
        probableFactor <= sqrtOf;
        probableFactor++
    )
    {
        bool skipPrimeFactor = false;

        for (uint64_t primeFactor: primeFactors)
        {
            if (primeFactor % probableFactor == 0) {
                skipPrimeFactor = true;

                break;
            }
        }

        if (skipPrimeFactor) {
            continue;
        }

        while (number % probableFactor == 0) {
            return false;
        }
    }

    return true;
}

int main()
{
    constexpr uint64_t mersenne_19digits{ 2305843009213693951 };
    constexpr uint64_t isthisprime{ 541 };

    //cout << to_string(UINT64_MAX);

    //cout << "# PrimeFinder\n";
    //cout << "Hello CSP3341! - SN 10673966\n";

    //sieve_bucketer(2);

    SieveOfEratosthenes(100000);

    //if (primality_test(UINT64_MAX)) {
    //    cout << "Yes";
    //}
    //else {
    //    cout << "Naur";
    //}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
