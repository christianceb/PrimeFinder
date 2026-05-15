#include "Classes/EratosthenesSieve.h"
#include "Utils/Temporal.h"
#include "Utils/Console.h"
#include "Classes/PrimalityTest.h"

using namespace std;

void application() {
    bool exit = false;

    string choice;

    bool validNumberforPrimality = false;

    // Begin application loop. Only ends when exit condition is met (user intentionally exits)
    while (!exit) {
        Console::Print("---\n");

        Console::Print("What do you want to do?\n");

        Console::Print("[1] Check if a number is a prime or not");
        Console::Print("[2] Run a custom parameter Sieve of Eratosthenes");
        Console::Print("[3] Run a Sieve of Eratosthenes basic preset (up to 10000, 1000 numbers per thread, 8 threads)");
        Console::Print("[4] Run a Sieve of Eratosthenes advanced preset (up to 1000000, 10000 numbers per thread, 16 threads)");
        Console::Print("[0] Exit\n");
        
        choice = Console::Read("Choice: ");

        // Erase any (0..n) history of a valid number used in the app
        validNumberforPrimality = false;

        if (choice == "1") {
            // Primality Check

            size_t numberToTestForPrimality = 0;

            // Prompt user over and over again until a valid number is provided
            while (!validNumberforPrimality) {
                choice = Console::Read("\nWhat number should be tested for primality?: ");

                // Test if input is a valid number. Prompt again if input is not
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
            // Run a user-defined Sieve of Eratosthenes

            string numericInputAsString = "";
            size_t upToNumber = 0;

            // Each thread will be provided a number range to work on. If the sieve hasn't been run
            // yet, how many number should be there?
            int numbersPerThread = 0;

            // How many parallel processes should the sieve be running?
            int threadCount = 0;

            // Try and get an upToNumber: up to what numbers from 0 should the sieve be running?
            while (numericInputAsString == "") {
                numericInputAsString = Console::Read("Up to what number should we find a prime number? (try 10000): ");

                // Try and parse string into an integer
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

                // Try and parse string into an integer
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

                // Try and parse string into an integer
                threadCount = stoull(numericInputAsString);

                // Force the loop to start over if we did not get a good threadCount
                if ((threadCount > 0) == false) {
                    numericInputAsString = "";
                }
            }

            // We finally start
            // Record start time so we can measure how long it takes for the sieve to finish
            __int64 timeStart = Temporal::timestampNow();

            // Run the sieve
            EratosthenesSieve(upToNumber, numbersPerThread, threadCount, true);

            // Print time elapsed results
            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");

            continue;
        }
        else if (choice == "3") {
            // Run a basic macro of Sieve of Eratosthenes

            // Record start time so we can measure how long it takes for the sieve to finish
            __int64 timeStart = Temporal::timestampNow();

            // Run the sieve
            EratosthenesSieve(10000, 1000, 8, true);

            // Print time elapsed results
            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");
        }
        else if (choice == "4") {
            // Run an advanced macro of Sieve of Eratosthenes

            __int64 timeStart = Temporal::timestampNow();

            // Run the sieve
            EratosthenesSieve(1000000, 10000, 16, true);

            // Print time elapsed results
            Console::Print("\nOperation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");
        }
        else if (choice == "0") {
            // Exit application

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
