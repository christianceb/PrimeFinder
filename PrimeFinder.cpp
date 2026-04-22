// PrimeFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <future>
#include <functional>
#include "Utils/Console.h"
#include <fstream>
#include "Utils/Temporal.h"
#include "Classes/PrimalityTest.h"
#include "Classes/PrimeFile.h"
#include "Classes/EratosthenesSieve.h"

using namespace std;

int main()
{
    //constexpr size_t mersenne_19digits{ 2305843009213693951 };
    //constexpr size_t isthisprime{ 541 };

    //int64_t x = btsFindGtIndexInList(3, { 3, 5, 7, 11, 13, 19 });

    //cout << to_string(UINT64_MAX);

    //cout << "# PrimeFinder\n";
    //cout << "Hello CSP3341! - SN 10673966\n";

    // SieveOfEratosthenes(1000); // From 1000000, adding three more zeroes will bring your computer to its knees (upwards to 10GB memory usage and 440+ threads simultaneously)

    EratosthenesSieve(1000);

    //PrimalityTest::Test(UINT64_MAX);
    //if (primality_test(UINT64_MAX)) {
    //    cout << "Yes";
    //}
    //else {
    //    cout << "Naur";
    //}
}
