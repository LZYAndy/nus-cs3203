#ifndef AUTOTESTER_FOLLOWSSTARBANK_H
#define AUTOTESTER_FOLLOWSSTARBANK_H

#include "Bank.h"
#include <algorithm>

class FollowsStarBank
{
public:
    bool is_follows_star(int stmt1, int stmt2);
    bool insert_follows_star(int stmt1, int stmt2);
    std::vector<int> get_follows_star(int stmt);
    std::vector<int> get_followed_star_by(int stmt);
    std::unordered_map<int, std::vector<int>> get_all_follows_star_relationship();
    bool does_follows_star_exist();
    std::vector<int> get_all_follows_star();
    std::vector<int> get_all_followed_star();

private:
    Bank<int, int> follows_star_bank;
};

#endif //AUTOTESTER_FOLLOWSSTARBANK_H
