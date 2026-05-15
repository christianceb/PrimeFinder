#pragma once

/**
 * @brief Utility class to test primality of a number
 * 
 */
class PrimalityTest
{
public:
    /**
     * @brief Tests whether a given number is a prime or not. Uses Trial Division.
     *
     * @param number The number to test
     *
     * @return bool
     */
    static bool Test(size_t number);
};
