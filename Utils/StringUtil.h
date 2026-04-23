#pragma once
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Container class for static methods related to transforming and manipulating strings
 *
 * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
 * @date 2025-05-13
 */
class StringUtil
{
public:
    /**
     * @brief Given a list of strings, join then as a string with a delimeter (reference) https://stackoverflow.com/a/5689061
     * @public
     *
     * @param vector<string> The list of strings to combine
     * @param delimeter What character to join the list of strings with.
     * @return string The combined list of strings.
     *
     * @author REDACTED_AUTHOR_DUE_TO_PUBLIC_PUBLISHING (10673966) <REDACTED@REDACTED>
     * @date 2026-04-23
     */
    static string Join(vector<string> strings, string delimeter = ",");

};
