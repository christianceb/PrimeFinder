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
    
    for (int x = 0; threads[0].size; ) {

    }
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

    sieve_bucketer(2);

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
