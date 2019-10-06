#include "CallsStarBank.h"

bool CallsStarBank::insert_calls_star(std::string proc1, std::string proc2)
{
    if (proc1 == proc2) // no recursion allowed
    {
        return false; 
    }
    calls_star_bank.put(proc1, proc2);
    return true;
}

bool CallsStarBank::does_calls_star_exist()
{
    return !calls_star_bank.empty();
}

bool CallsStarBank::is_calls_star(std::string proc1, std::string proc2)
{
    return calls_star_bank.check_relationship(proc1, proc2);
}

std::vector<std::string> CallsStarBank::get_all_procedures_calls_star()
{
    return calls_star_bank.get_all_values();
}

std::vector<std::string> CallsStarBank::get_all_procedures_called_star()
{
    return calls_star_bank.get_all_keys();
}

std::vector<std::string> CallsStarBank::get_procedures_calls_star(std::string proc)
{
    return calls_star_bank.get_reverse(proc);
}

std::vector<std::string> CallsStarBank::get_procedures_called_by_star(std::string proc)
{
    return calls_star_bank.get(proc);
}

std::unordered_map<std::string, std::vector<std::string>> CallsStarBank::get_all_procedures_calls_star_relationship()
{
    return calls_star_bank.copy();
}
