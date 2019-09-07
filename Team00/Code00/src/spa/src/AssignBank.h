#ifndef AUTOTESTER_ASSIGNBANK_H
#define AUTOTESTER_ASSIGNBANK_H

#include "Bank.h"

class AssignBank : public Bank<int, std::string>
{
public:
    std::vector<int> matches(std::string var, std::string pattern);
    std::vector<int> contains(std::string var, std::string pattern);
    std::vector<int> all_matches(std::string pattern);
    std::vector<int> all_contains(std::string pattern);
};

#endif //AUTOTESTER_ASSIGNBANK_H
