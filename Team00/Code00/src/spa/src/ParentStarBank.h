#ifndef AUTOTESTER_PARENTSTARBANK_H
#define AUTOTESTER_PARENTSTARBANK_H

#include "Bank.h"

class ParentStarBank
{

public:
    bool is_parent_star(int stmt1, int stmt2);
    bool insert_parent_star(int stmt1, int stmt2);
    std::vector<int> get_parent_star(int stmt);
    std::vector<int> get_children_star(int stmt);
    std::unordered_map<int, std::vector<int>> get_all_parent_star_relationship();
    bool does_parent_star_exist();
    std::vector<int> get_all_parent_star();
    std::vector<int> get_all_children_star();

private:
    Bank<int, int> parent_star_bank;
};

#endif //AUTOTESTER_PARENTSTARBANK_H
