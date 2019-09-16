#pragma once
#ifndef AUTOTESTER_PARENTBANK_H
#define AUTOTESTER_PARENTBANK_H

#include "Bank.h"
#include <algorithm>

class ParentBank
{
public:
    bool is_parent(int stmt1, int stmt2);
    bool insert_parent(int stmt1, int stmt2);
    std::unordered_map<int, std::vector<int>> get_all_parent_relationship();
    int get_parent(int stmt);
    std::vector<int> get_children(int stmt);
    std::vector<int> get_all_children();
    std::vector<int> get_all_parent();
    bool does_parent_exist();

private:
    Bank<int, int> parent_bank;
};

#endif //AUTOTESTER_PARENTBANK_H
