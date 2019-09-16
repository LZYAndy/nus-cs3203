#pragma once
#ifndef AUTOTESTER_FOLLOWSBANK_H
#define AUTOTESTER_FOLLOWSBANK_H

#include "Bank.h"

#include <algorithm>

class FollowsBank
{
public:
    bool is_follows(int stmt1, int stmt2);
    bool insert_follows(int stmt1, int stmt2);
    bool does_follows_exists();
    std::unordered_map<int, std::vector<int>> get_all_follows_relationship();
    std::vector<int> get_all_follows();
    std::vector<int> get_all_followed();
    int get_followed_by(int stmt);
    int get_follows(int stmt);

private:
    Bank<int, int> follows_bank;
};

#endif //AUTOTESTER_FOLLOWSBANK_H
