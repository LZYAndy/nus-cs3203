#include "ParentStarBank.h"
bool ParentStarBank::is_parent_star(int stmt1, int stmt2)
{
    return parent_star_bank.check_relationship(stmt1, stmt2);
}

bool ParentStarBank::insert_parent_star(int stmt1, int stmt2)
{
    parent_star_bank.put(stmt1, stmt2);
    return true;
}

std::vector<int> ParentStarBank::get_parent_star(int stmt)
{
    return parent_star_bank.get(stmt);
}

std::vector<int> ParentStarBank::get_children_star(int stmt)
{
    return parent_star_bank.get_reverse(stmt);
}

std::unordered_map<int, std::vector<int>> ParentStarBank::get_all_parent_star_relationship()
{
    return parent_star_bank.copy();
}

bool ParentStarBank::does_parent_star_exist()
{
    return !parent_star_bank.empty();
}

std::vector<int> ParentStarBank::get_all_parent_star()
{
    return parent_star_bank.get_all_keys();
}

std::vector<int> ParentStarBank::get_all_children_star()
{
    return parent_star_bank.get_all_values();

}
