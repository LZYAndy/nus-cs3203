#ifndef AUTOTESTER_CALLBANKS_H
#define AUTOTESTER_CALLBANKS_H

#include "Bank.h"

class CallsBank
{
public:

    /**
     * Insert Calls relationship into CallsBank.
     * @param stmt Call statement number
     * @param caller caller procedure
     * @param callee callee procedure
     * @return true if the insert process is successful.
     */
    bool insert_calls(int stmt, std::string caller, std::string callee);
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
    /**
     * Get all Calls statements and its callee pairing that exists in CallsBank.
     * @return unordered_map containing all Calls statements and its callee pairing that exists in CallsBank 
     */
    std::unordered_map<int, std::vector<std::string>> get_all_statements_calls_relationship();
    /**
     * Get statement number of all call statements that Calls.
     * @return vector of statement number of call statemetn that Calls.
     */
    std::vector<std::string> get_all_statements_calls();
private:
    Bank<std::string, std::string> calls_proc_bank;
    Bank<int, std::string> calls_stmt_bank;
};

#endif
