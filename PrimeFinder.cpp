#include "Classes/EratosthenesSieve.h"
#include "Utils/Temporal.h"
#include "Utils/Console.h"
#include "Classes/PrimalityTest.h"

using namespace std;

void application() {

    bool exit = false;

    size_t number;
    size_t busSize = 10000;
    int threads = 8;

    string choice;

    bool validNumberforPrimality = false;

    while (!exit) {
        validNumberforPrimality = false;
        Console::Print("---\n");

        Console::Print("What do you want to do?\n");

        Console::Print("[1] Check if a number is a prime or not");
        Console::Print("[2] Run the sieve of eratosthenes up to a certain number");
        Console::Print("[3] Exit\n");
        
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
                numericInputAsString = Console::Read("Up to what number should we find a prime number? (default=100000): ");

                if (numericInputAsString == "") {
                    upToNumber == 100000;
                    break;
                }

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
                numericInputAsString = Console::Read("How many numbers should be there in a thread? (default=10000): ");

                if (numericInputAsString == "") {
                    numbersPerThread == 10000;
                    break;
                }

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
                numericInputAsString = Console::Read("How many threads should there be running at a time? (default=8)");

                if (numericInputAsString == "") {
                    threadCount == 10000;
                    break;
                }

                threadCount = stoull(numericInputAsString);

                // Force the loop to start over if we did not get a good threadCount
                if ((threadCount > 0) == false) {
                    numericInputAsString = "";
                }
            }

            // We finally start

            __int64 timeStart = Temporal::timestampNow();

            EratosthenesSieve(upToNumber, numbersPerThread, threadCount, true);

            Console::Print("Operation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));

            Console::ReadLine("\nPress any key to continue...");

            continue;
        }
        else if (choice == "3") {
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
