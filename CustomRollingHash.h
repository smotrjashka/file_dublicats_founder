#ifndef CUSTOMROLLINGHASH_H
#define CUSTOMROLLINGHASH_H

#include <string>

class CustomRollingHash {
public:
    CustomRollingHash();
    std::string computeHash(const std::string& input);
};

#endif