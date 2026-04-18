#include "Temporal.h"

#include <chrono>

using namespace std;

__int64 Temporal::timestampNow()
{
    const auto now = chrono::system_clock::now();

    return chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();
}
