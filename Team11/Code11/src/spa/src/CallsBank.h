#ifndef AUTOTESTER_CALLBANKS_H
#define AUTOTESTER_CALLBANKS_H

#include "Bank.h"

class CallsBank
{
public:

    /**
     * Insert Calls relationship into CallsBank.
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls
     * @return true if the insert process is successful.
     */
    bool insert_calls(std::string proc1, std::string proc2);
    /**
     * Check if there exist at least one Calls relationship stored in CallsBank.
     * @return true if there is at least one Calls relationship store in CallsBank.
     */
    bool does_calls_exist();
    /**
     * Check if the procedure calls another procedure.
     * In other words, Calls(proc1,proc2).
     * @param proc1 procedure to be called
     * @param proc2 procedure to Calls
     * @return true if proc1 Calls proc2. In other words, Calls(proc1, proc2).
     */
    bool is_calls(std::string proc1, std::string proc2);
    /**
     * Get all procedures that have been Calls.
     * @return vector of procedure name that have been Calls.
     */
    std::vector<std::string> get_all_procedures_calls();
    /**
     * Get all procedures that have been Called.
     * @return vector of procedure name that have been Called.
     */
    std::vector<std::string> get_all_procedures_called();
    /**
     * Get all procedures that the queried procedure Calls.
     * @param proc queried procedure
     * @return vector of procedure name that the queried procedure Calls.
     */
    std::vector<std::string> get_procedures_calls(std::string proc);
    /**
     * Get all procedures that Called by the queried procedure .
     * @param proc queried procedure
     * @return vector of procedure name that Called by the queried procedure.
     */
    std::vector<std::string> get_procedures_called_by(std::string proc);
    /**
     * Get all Calls relationship that exists in CallsBank.
     * @return unordered_map containing all Calls relationship that exists in CallsBank with
     * the Calls as key and all Called stored in a vector as value.
     */
    std::unordered_map<std::string, std::vector<std::string>> get_all_procedures_calls_relationship();

private:
    Bank<std::string, std::string> calls_bank;
};

#endif
