#include "IfBank.h"

bool IfBank::insert_if(int stmt, std::string control)
{
    if (stmt <= 0 )
    {
        return false;
    }
    if_bank.put(stmt, control);
    return true;
}


std::vector<int> IfBank::all_matches(std::string pattern)
{
    return if_bank.get_reverse(pattern);
}

std::vector<int> IfBank::all_contains(std::string pattern)
{
    std::vector<std::string> controls = if_bank.get_all_values();
    std::vector<int> result;
    for (std::string control : controls)
    {
        if (control.find(pattern) != std::string::npos)
        {
            for (int stmt : if_bank.get_reverse(control))
            {
                result.push_back(stmt);
            }
        }
    }
    return result;
}
