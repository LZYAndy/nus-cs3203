#include "NextBipBank.h"

bool NextBipBank::insert_next_bip(int previous_prog, int next_prog)
{
    next_bip_bank.put(previous_prog, next_prog);
    return true;
}

bool NextBipBank::insert_call_ingress(int caller_prog, int callee_prog)
{
    ingress_table.insert({caller_prog, callee_prog});
    return true;
}

bool NextBipBank::is_next_bip(int previous_prog, int next_prog)
{
    auto next_result = next_bip_bank.get(previous_prog);
    if (next_result.empty())
    {
        return false;
    }
    else
    {
        for (int next : next_result)
        {
            if (next_prog == next) 
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<int> NextBipBank::get_next_bip(int prog_line)
{
    std::vector<int> next_result = next_bip_bank.get(prog_line);
    return next_result;
}

std::vector<int> NextBipBank::get_previous_bip(int prog_line)
{
    std::vector<int> previous_result = next_bip_bank.get_reverse(prog_line);
    return previous_result;
}

std::vector<int> NextBipBank::get_all_previous_bip()
{
    std::vector<int> previous_result = next_bip_bank.get_all_keys();
    return previous_result;
}

std::vector<int> NextBipBank::get_all_next_bip()
{
    std::vector<int> next_result = next_bip_bank.get_all_values();
    return next_result;
}

bool NextBipBank::does_next_bip_exists()
{
    return !next_bip_bank.empty();
}

std::unordered_map<int, std::vector<int>> NextBipBank::get_all_next_bip_relationship()
{
    return next_bip_bank.copy();
}
