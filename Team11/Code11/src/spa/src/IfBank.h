#ifndef AUTOTESTER_IFBANK_H
#define AUTOTESTER_IFBANK_H

#include "Bank.h"

class IfBank
{
public:
    /**
     * Insert If relationship to IfBank.
     * @param stmt stmt# of statement.
     * @param control_vars vector of control variables.
     * @return true if the insert process is successful.
     */
    bool insert_if(int stmt, std::vector<std::string> control_vars);
    /**
     * Get all stmt# of IF statement that control expression contains the variable.
     * @param variable.
     * @return vector of stmt# that IF statements that fulfill the requirements.
     */
    std::vector<int> all_contains(std::string variable);
    /**
     * Get all if statements and their control variable pairing.
     * @return unordered_map of stmt# and vector of control variables
     */
    std::unordered_map<int, std::vector<std::string>> get_all_if_and_control_variables_map();
private:
    Bank<int, std::string> if_bank;
};
#endif
