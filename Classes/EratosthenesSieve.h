#pragma once

#include <vector>

using namespace std;

class EratosthenesSieve
{
public:
    EratosthenesSieve(size_t number);

private:
    size_t nearestNext(size_t number, size_t next);

    vector<vector<size_t>> sievePrep(size_t upToInclusive);

    vector<size_t> sieve(vector<size_t> bus, size_t divisor);
    
    void sieveThreadedPointer(vector<size_t>& bus, size_t divisor);
};
