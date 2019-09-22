#ifndef AUTOTESTER_ASSIGNBANK_H
#define AUTOTESTER_ASSIGNBANK_H

#include <unordered_set>

#include "Bank.h"

class AssignBank
{
public:
    /**
     * Insert Assign relationship to AssignBank.
     * @param stmt1 stmt# of statement.
     * @param var variable name.
     * @param assignment RHS expression to be assigned to the variable.
     * @return true if the insert process is successful.
     */
    void put(int stmt, std::string var, std::string assignment);
    /**
     * Get all stmt# of ASSIGN statement containing the variable and its RHS expression exact matches the pattern.
     * @param var variable name in the ASSIGN statement.
     * @param pattern the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    std::vector<int> matches(std::string var, std::string pattern);
    /** 
     * Get all stmt# of ASSIGN statement that containing the variable and its RHS expression contains the pattern.
     * @param var variable name in the ASSIGN statement.
     * @param pattern the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    std::vector<int> contains(std::string var, std::string pattern);
    /**
     * get all stmt# of ASSIGN statement that its RHS expression exact matches the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    std::vector<int> all_matches(std::string pattern);
    /**
     * Get all stmt# of ASSIGN statement that its RHS expression contains the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that ASSIGN statements that fulfill the requirements.
     */
    std::vector<int> all_contains(std::string pattern);
    /**
     * Get name of variable modified in ASSIGN statement.
     * @param assign stmt# of ASSIGN statement.
     * @return name of variable modified in ASSIGN statement.
     */
    std::string get_variable_from_statement(int stmt);

private:
    Bank<int, std::string> var_bank; // Internal variable bank.
    Bank<int, std::string> assignment_bank;
    Bank<std::string, std::string> var_assignment_bank;
};

#endif //AUTOTESTER_ASSIGNBANK_H
