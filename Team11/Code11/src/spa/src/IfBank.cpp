#include "IfBank.h"

bool IfBank::insert_if(int stmt, std::vector<std::string> control_vars)
{
    if (stmt <= 0 )
    {
        return false;
    }
    for (std::string control : control_vars)
    {
        if_bank.put(stmt, control);
    }
    return true;
}

std::vector<int> IfBank::all_contains(std::string variable)
{
    return if_bank.get_reverse(variable);
}

std::unordered_map<int, std::vector<std::string>> IfBank::get_all_if_and_control_variables_map()
{
    return if_bank.copy();
}
