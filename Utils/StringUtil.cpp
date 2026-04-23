#include "StringUtil.h"
#include <vector>

using namespace std;

string StringUtil::Join(vector<string> strings, string delimeter)
{
    string result = "";

    int listSize = strings.size();

    for (size_t i = 0; i < listSize; i++)
    {
        result += strings[i];

        if ((i + 1) < listSize) {
            result += delimeter;
        }
    }

    return result;
}
