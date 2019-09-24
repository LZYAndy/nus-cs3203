#include "FollowsStarBank.h"
bool FollowsStarBank::is_follows_star(int stmt1, int stmt2)
{
    return follows_star_bank.check_relationship(stmt1, stmt2);
}

bool FollowsStarBank::insert_follows_star(int stmt1, int stmt2)
{
    if (stmt1 == stmt2)
    {
        return false;
    }
    follows_star_bank.put(stmt1, stmt2);
    return true;
}

std::vector<int> FollowsStarBank::get_follows_star(int stmt)
{
    return follows_star_bank.get(stmt);
}

std::vector<int> FollowsStarBank::get_followed_star_by(int stmt)
{
    return follows_star_bank.get_reverse(stmt);
}

std::unordered_map<int, std::vector<int>> FollowsStarBank::get_all_follows_star_relationship()
{
    return follows_star_bank.copy();
}

bool FollowsStarBank::does_follows_star_exist()
{
    return !follows_star_bank.empty();
}

std::vector<int> FollowsStarBank::get_all_follows_star()
{
    return follows_star_bank.get_all_values();
}

std::vector<int> FollowsStarBank::get_all_followed_star()
{
    return follows_star_bank.get_all_keys();

}
