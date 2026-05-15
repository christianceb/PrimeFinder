#pragma once
#include <string>

/**
 * @brief Utility methods to get and localise time
 * 
 */
class Temporal
{
public:
    /**
     * @brief Gets the epoch (unix timestamp) as an integer
     * 
     * @return __int64 Unix Timestamp, in seconds
     */
    static __int64 timestampNow();

    /**
     * @brief Convert a unix timestamp into a human-readable string
     * 
     * @param seconds Unix Timestamp, in seconds
     * 
     * @return string Localised date/time
     */
    static string secondsToLocalisedHms(__int64 seconds);
};
