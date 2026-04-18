#include "PrimalityTest.h"
#include <vector>
#include <cmath>

using namespace std;

bool PrimalityTest::Test(size_t number)
{
    size_t sqrtOf = sqrt(number);

    // Set starting primeFactors that are very common divisors to composite numbers
    vector<size_t> primeFactors = { 2, 3 };

    // Composite numbers are highly likely to fail this test
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    // We start the probableFactor at 5 because we already have tested 2 and 3, and we know that 4 is composite of 2
    for (
        size_t probableFactor = 5;
        probableFactor <= sqrtOf;
        probableFactor++
    )
    {
        // By default, we assume that probableFactor is usable
        bool skipProbableFactor = false;

        // Iterate through the existing primeFactors
        for (size_t primeFactor : primeFactors)
        {
            /**
             * Here, we test the probableFactor which is the result of the for-loop if it is divisible by any of the
             * existing primeFactors we know. If it is, no point trying this number and move on to the next one.
             */
            if (primeFactor % probableFactor == 0) {
                // Signal outer loop to skip this probableFactor
                skipProbableFactor = true;

                break;
            }
        }

        // Check if the signal from the previous loop has been set
        if (skipProbableFactor) {
            // Skip
            continue;
        }
        
        // The probableFactor we had is a prime and can be tested against our number
        primeFactors.push_back(probableFactor);

        while (number % probableFactor == 0) {
            // A composite
            return false;
        }
    }

    // It's a prime
    return true;
}
