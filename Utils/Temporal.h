#pragma once
#include <string>

class Temporal
{
public:
    static __int64 timestampNow();

    static string secondsToLocalisedHms(__int64 seconds);
};
