#include "Classes/EratosthenesSieve.h"
#include "Utils/Temporal.h"
#include "Utils/Console.h"

using namespace std;

int main()
{
    bool exit = false;

    size_t number = 100000;
    size_t busSize = 10000;
    int threads = 8;

    string choice;

    bool validNumberforPrimality = false;

    while (!exit) {
        validNumberforPrimality = false;

        Console::Print("What do you want to do?\n");

        Console::Print("[1] Check if a number is a prime or not");
        Console::Print("[2] Run the sieve of eratosthenes up to a certain number");
        Console::Print("[3] Exit");

        
        choice = Console::Read("Choice: ");

        if (choice == "1") {
            while (!validNumberforPrimality) {
                choice = Console::Read("What number should be tested for primality?: ");

                // Test if input is a valid number. Prompt again if input is not.
                if (stoull(choice) > 0) {
                    validNumberforPrimality = true;
                    number = stoull(choice);
                }
            }

            // Do primality check
        }
        else if (choice == "2") {
            Console::Read("Up to what number should we find a prime number? (default=100000)");

            Console::Read("How many numbers should be there in a thread? (default=10000)");

            Console::Read("How many threads should there be running at a time? (default=8)");

            // Process
        }
        else if (choice == "3") {
            exit = true;
        }
    }

    __int64 timeStart = Temporal::timestampNow();

    EratosthenesSieve(100000, true);

    Console::Print("Operation ended in " + Temporal::secondsToLocalisedHms(Temporal::timestampNow() - timeStart));
}
