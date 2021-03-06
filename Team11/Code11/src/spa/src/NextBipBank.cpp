#include "NextBipBank.h"

bool NextBipBank::insert_next_bip(int previous_prog, int next_prog)
{
    next_bip_bank.put(previous_prog, next_prog);
    return true;
}

bool NextBipBank::insert_call_ingress_egress(int ingress_prog, int egress_prog)
{
    ingress_egress_bank.put(ingress_prog, egress_prog);
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

std::vector<int> NextBipBank::get_egress(int ingress_prog)
{
    return ingress_egress_bank.get(ingress_prog);

} 

std::vector<int> NextBipBank::get_ingress(int egress_prog)
{
    return ingress_egress_bank.get_reverse(egress_prog);
    auto result = ingress_egress_bank.get_reverse(egress_prog);
    if (!result.empty())
    {
        return result;
    }
    return std::vector<int>({-1});
} 
