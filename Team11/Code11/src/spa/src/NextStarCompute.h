#ifndef AUTOTESTER_NEXTSTARCOMPUTE_H
#define AUTOTESTER_NEXTSTARCOMPUTE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "NextBank.h"

class NextStarCompute {
public:
    std::vector<int> get_statements_previous_star(int next, NextBank& next_bank);   //e.g. Next*(n, 2)
    std::vector<int> get_statements_next_star(int previous, NextBank& next_bank);  //e.g. Next*(1, n)
    bool is_next_star(int previous, int next, NextBank& next_bank); //e.g. Next*(1, 2)
    //std::unordered_map<int, std::vector<int>> get_all_next_star_relationship(NextBank& next_bank);  //e.g. Next*(n1, n2)
    std::unordered_map<int, std::vector<int>> get_all_next_star_relationship(int last_stmt_num, NextBank& next_bank);  //e.g. Next*(n1, n2)

private:
    //std::unordered_map<int, std::unordered_set<int>> DFS_for_CFG(int target_stmt, std::unordered_map<int, std::vector<int>> cfg);
    std::vector<int> DFS_for_CFG(int target_stmt, std::unordered_map<int, std::vector<int>> cfg);
};


#endif //AUTOTESTER_NEXTSTARCOMPUTE_H
