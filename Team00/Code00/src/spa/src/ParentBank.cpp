#include "ParentBank.h"
bool ParentBank::is_parent(int stmt1, int stmt2)
{
    return parent_bank.check_relationship(stmt1, stmt2);
}

bool ParentBank::insert_parent(int stmt1, int stmt2)
{
    std::vector<int> children = parent_bank.get(stmt1);
    for (int child : children)
    {
        if (child == stmt2)
        {
            return false;
        }
    }
    parent_bank.put(stmt1, stmt2);
    return true;
}

std::unordered_map<int, std::vector<int>> ParentBank::get_all_parent_relationship()
{
    return parent_bank.copy();
}

std::vector<int> ParentBank::get_all_parent()
{
    return parent_bank.get_all_keys();
}

std::vector<int> ParentBank::get_all_children()
{
    return parent_bank.get_all_values();
}

int ParentBank::get_parent(int stmt)
{
    std::vector<int> result = parent_bank.get_reverse(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

std::vector<int> ParentBank::get_children(int stmt)
{
    return parent_bank.get(stmt);
}

bool ParentBank::does_parent_exist()
{
    return !parent_bank.empty();
}