#pragma once
#include <string>

using namespace std;

/**
 * Utility class with static methods to assist command-line interface interactions.
 *
 * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
 * @date 2025-03-30
 */
class Console
{
public:
    /**
     * @brief Prints a message to the console with an optional line break. Makes it much easier to
     *   read the code rather than see cout everywhere
     *
     * @param message The message to print
     * @param lineBreak `true` by default where a line break will be added to the end of the message.
         If false, no line break will be added.
     * @return void
     *
     * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
     * @date 2025-03-30
     */
    static void Print(string message = "", bool lineBreak = true);

    /**
     * @brief Utility function to prompt user for input (Read-input). It takes a message as an
     *  argument and returns the input as a string.
     *
     * @param message Prompt message to show the user. Default is empty string.
     * @return string The user input
     *
     * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
     * @date 2025-04-01
     */
    static string Read(string message = "");

    /**
     * @brief Utility function to prompt user for input (Read-line). It takes a message as an
     *  argument and returns the input as a string. Difference with Read() is that it doens't just collect
     *  tokens but it includes the whole string given, including spaces.
     *
     * @param message Prompt message to show the user. Default is empty string.
     * @return string The user input
     *
     * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
     * @date 2025-04-01
     */
    static string ReadLine(string message = "");
};
