#include "StringUtil.h"
#include "Temporal.h"
#include <chrono>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

__int64 Temporal::timestampNow()
{
    const auto now = chrono::system_clock::now();

    return chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
}

string Temporal::secondsToLocalisedHms(__int64 seconds)
{
    __int64 hours = floor(seconds / 60 / 60);
    __int64 flooredHoursInSeconds = hours * 60 * 60;

    __int64 remainingSecondsForMinutes = seconds - flooredHoursInSeconds;
    __int64 minutes = floor(remainingSecondsForMinutes / 60);

    __int64 remainingSeconds = remainingSecondsForMinutes - (minutes * 60);

    vector<string> stringFragments;
    string localised = "";

    if (hours > 0) {
        stringFragments.push_back(to_string(hours) + " hour" + (hours > 1 ? "s" : ""));
    }

    if (minutes > 0) {
        stringFragments.push_back(to_string(minutes) + " minute" + (minutes > 1 ? "s" : ""));
    }
    
    if (seconds > 0) {
        stringFragments.push_back(to_string(seconds) + " second" + (seconds > 1 ? "s" : ""));
    }

    return StringUtil::Join(stringFragments, ", ");
}
