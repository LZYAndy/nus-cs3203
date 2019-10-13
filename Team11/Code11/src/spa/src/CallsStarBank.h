#ifndef AUTOTESTER_CALLSSTARBANK_H
#define AUTOTESTER_CALLSSTARBANK_H

#include "Bank.h"

class CallsStarBank
{
public:

    /**
     * Insert Calls* relationship into CallsStarBank.
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls*
     * @return true if the insert process is successful.
     */
    bool insert_calls_star(std::string proc1, std::string proc2);
    /**
     * Check if there exist at least one Calls* relationship stored in CallsStarBank.
     * @return true if there is at least one Calls* relationship store in CallsStarBank.
     */
    bool does_calls_star_exist();
    /**
     * Check if the procedure calls* another procedure.
     * In other words, Calls*(proc1,proc2).
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls*
     * @return true if proc1 Calls* proc2. In other words, Calls*(proc1, proc2).
     */
    bool is_calls_star(std::string proc1, std::string proc2);
    /**
     * Get all procedures that have been Calls directly or indirectly.
     * @return vector of procedure name that have been Calls directly or indirectly.
     */
    std::vector<std::string> get_all_procedures_calls_star();
    /**
     * Get all procedures that have been Called directly or indirectly.
     * @return vector of procedure name that have been Called directly or indirectly.
     */
    std::vector<std::string> get_all_procedures_called_star();
    /**
     * Get all procedures that the queried procedure Calls directly or indirectly.
     * @param proc queried procedure
     * @return vector of procedure name that the queried procedure Calls directly or indirectly.
     */
    std::vector<std::string> get_procedures_calls_star(std::string proc);
    /**
     * Get all procedures that Called by the queried procedure directly or indirectly.
     * @param proc queried procedure
     * @return vector of procedure name that Called by the queried procedure directly or indirectly.
     */
    std::vector<std::string> get_procedures_called_by_star(std::string proc);
    /**
     * Get all Calls* relationship that exists in CallsStarBank.
     * @return unordered_map containing all Calls* relationship that exists in CallsStarBank with
     * the Calls as key and all Called stored in a vector as value.
     */
    std::unordered_map<std::string, std::vector<std::string>> get_all_procedures_calls_star_relationship();

private:
    Bank<std::string, std::string> calls_star_bank;
};

#endif
