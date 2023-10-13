#include "CustomRollingHash.h"
#include <sstream>
#include <cmath>

const int PRIME = 101;

CustomRollingHash::CustomRollingHash() {}

std::string CustomRollingHash::computeHash(const std::string& input) {
    unsigned long long hash = 0;
    int windowSize = input.size();

    for (int i = 0; i < windowSize; ++i) {
        hash = (hash * PRIME + input[i]) % UINT_MAX;
    }

    for (int i = windowSize; i < input.size(); ++i) {
        hash = (hash * PRIME + input[i]) % UINT_MAX;
        hash = (hash + UINT_MAX - (input[i - windowSize] * static_cast<unsigned long long>(pow(PRIME, windowSize)) % UINT_MAX)) % UINT_MAX;
    }

    std::stringstream ss;
    ss << hash;
    return ss.str();
}