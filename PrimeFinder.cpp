#include "Classes/EratosthenesSieve.h"
#include "Utils/Temporal.h"
#include "Utils/Console.h"
#include "Classes/PrimalityTest.h"

using namespace std;

void application() {

    bool exit = false;

    string choice;

    bool validNumberforPrimality = false;

    while (!exit) {
        validNumberforPrimality = false;
        Console::Print("---\n");

        Console::Print("What do you want to do?\n");

        Console::Print("[1] Check if a number is a prime or not");
        Console::Print("[2] Run a custom parameter Sieve of Eratosthenes");
        Console::Print("[3] Run a Sieve of Eratosthenes basic preset (up to 10000, 1000 numbers per thread, 8 threads)");
        Console::Print("[4] Run a Sieve of Eratosthenes advanced preset (up to 1000000, 250000 numbers per thread, 16 threads)");
        Console::Print("[0] Exit\n");
        
        choice = Console::Read("Choice: ");

        if (choice == "1") {
            size_t numberToTestForPrimality = 0;

            while (!validNumberforPrimality) {
                choice = Console::Read("\nWhat number should be tested for primality?: ");

                // Test if input is a valid number. Prompt again if input is not.
                if (stoull(choice) > 0) {
                    validNumberforPrimality = true;
                    numberToTestForPrimality = stoull(choice);
                }
            }

            // Do primality check and output "<NUMBER> is [not] a prime."
            Console::Print(
                "\n"
                + to_string(numberToTestForPrimality)
                + " is "
                + (PrimalityTest::Test(numberToTestForPrimality) ? "" : "not ")
                + "a prime."
            );

            Console::ReadLine("\nPress any key to continue...");

            continue;
        }
        else if (choice == "2") {
            string numericInputAsString = "";
            size_t upToNumber = 0;
            int numbersPerThread = 0;
            int threadCount = 0;

            // Try and get an upToNumber
            while (numericInputAsString == "") {
                numericInputAsString = Console::Read("Up to what number should we find a prime number? (try 10000): ");

                upToNumber = stoull(numericInputAsString);

                // Force the loop to start over if we did not get a good upToNumber
                if ((upToNumber > 0) == false) {
                    numericInputAsString = "";
                }
            }

            // Reset placeholder input var
            numericInputAsString = "";

            // Try and get a numbers per thread
            while (numericInputAsString == "") {
                numericInputAsString = Console::Read("How many numbers should be there in a thread? (try 1000): ");

                numbersPerThread = stoull(numericInputAsString);

                // Force the loop to start over if we did not get a good numbersPerThread
                if ((numbersPerThread > 0) == false) {
                    numericInputAsString = "";
                }
            }

            // Reset placeholder input var
            numericInputAsString = "";

            // Try and get a thread count
            while (numericInputAsString == "") {
                numericInputAsString = Console::Read("How many threads should there be running at a time? (try 8): ");

                threadCount = stoull(numericInputAsString);

                // Force the loop to start over if we did not get a good threadCount
                if ((threadCount > 0) == false) {
                    numericInputAsString = "";
                }
            }

            // We finally start

            __int64 timeStart = Temporal::timestampNow();

            EratosthenesSieve(upToNumber, numbersPerThread, threadCount, true);

            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");

            continue;
        }
        else if (choice == "3") {
            __int64 timeStart = Temporal::timestampNow();

            EratosthenesSieve(10000, 1000, 8, true);

            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");
        }
        else if (choice == "4") {
            __int64 timeStart = Temporal::timestampNow();

            EratosthenesSieve(1000000, 250000, 16, true);

            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");
        }
        else if (choice == "0") {
            exit = true;

            Console::Print("Bye!");
        }
    }
}

int main()
{
    try {
        application();
    }
    catch (...) {
        Console::Print("Either user wanted to exit (CTRL+C) or a fatal error occurred");
    }
}
