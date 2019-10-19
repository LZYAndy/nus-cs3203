#include "CallsBank.h"

bool CallsBank::insert_calls(int stmt, std::string caller, std::string callee)
{
    if (caller == callee) // no recursion allowed
    {
        return false; 
    }
    calls_proc_bank.put(caller, callee);
    calls_stmt_bank.put(stmt, callee);
    return true;
}

bool CallsBank::does_calls_exist()
{
    return !calls_proc_bank.empty() && !calls_stmt_bank.empty();
}

bool CallsBank::is_calls(std::string proc1, std::string proc2)
{
    return calls_proc_bank.check_relationship(proc1, proc2);
}

std::vector<std::string> CallsBank::get_all_procedures_calls()
{
    return calls_proc_bank.get_all_values();
}

std::vector<std::string> CallsBank::get_all_procedures_called()
{
    return calls_proc_bank.get_all_keys();
}

std::vector<std::string> CallsBank::get_procedures_calls(std::string proc)
{
    return calls_proc_bank.get_reverse(proc);
}

std::vector<std::string> CallsBank::get_procedures_called_by(std::string proc)
{
    return calls_proc_bank.get(proc);
}

std::unordered_map<std::string, std::vector<std::string>> CallsBank::get_all_procedures_calls_relationship()
{
    return calls_proc_bank.copy();
}

std::unordered_map<int, std::vector<std::string>> CallsBank::get_all_statements_calls_relationship()
{
    return calls_stmt_bank.copy();
}
