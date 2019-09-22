#include "FollowsBank.h"
bool FollowsBank::is_follows(int stmt1, int stmt2)
{
   return follows_bank.check_relationship(stmt1, stmt2);
}

bool FollowsBank::insert_follows(int stmt1, int stmt2)
{
    // do not insert if already exist in bank
    if (follows_bank.get(stmt1).empty())
    {
        follows_bank.put(stmt1, stmt2);
        return true;
    }
    return false;
}

std::unordered_map<int, std::vector<int>> FollowsBank::get_all_follows_relationship()
{
    return follows_bank.copy();
}

std::vector<int> FollowsBank::get_all_follows()
{
    return follows_bank.get_all_values();
}

std::vector<int> FollowsBank::get_all_followed()
{
    return follows_bank.get_all_keys();
}

int FollowsBank::get_followed_by(int stmt)
{
    std::vector<int> result = follows_bank.get_reverse(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

int FollowsBank::get_follows(int stmt)
{
    std::vector<int> result = follows_bank.get(stmt);
    if (result.empty())
    {
        return -1;
    }
    return result.back();
}

bool FollowsBank::does_follows_exists()
{
    return !follows_bank.empty();
}
