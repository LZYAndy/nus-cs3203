#ifndef AUTOTESTER_ASSIGNBANK_H
#define AUTOTESTER_ASSIGNBANK_H

#include "Bank.h"

class AssignBank
{
public:
    void put(int stmt, std::string var, std::string assignment);
    std::vector<int> matches(std::string var, std::string pattern);
    std::vector<int> contains(std::string var, std::string pattern);
    std::vector<int> all_matches(std::string pattern);
    std::vector<int> all_contains(std::string pattern);
    std::string get_variable_from_statement(int stmt);
    int get_statement_from_variable(std::string var);
private:
    Bank<int, std::string> var_bank; // Internal variable bank.
    Bank<int, std::string> assignment_bank;
    Bank<std::string, std::string> var_assignment_bank;
};

#endif //AUTOTESTER_ASSIGNBANK_H
