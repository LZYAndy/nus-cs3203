#ifndef AUTOTESTER_IFBANK_H
#define AUTOTESTER_IFBANK_H

#include "Bank.h"

class IfBank
{
public:
    /**
     * Insert If relationship to IfBank.
     * @param stmt stmt# of statement.
     * @param control control expression.
     * @return true if the insert process is successful.
     */
    bool insert_if(int stmt, std::string control);
    /**
     * Get all stmt# of IF statement that control expression matches the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that IF statements that fulfill the requirements.
     */
    std::vector<int> all_matches(std::string pattern);
    /**
     * Get all stmt# of IF statement that control expression contains the pattern.
     * @param the pattern to match.
     * @return vector of stmt# that IF statements that fulfill the requirements.
     */
    std::vector<int> all_contains(std::string pattern);
private:
    Bank<int, std::string> if_bank;
};
#endif
