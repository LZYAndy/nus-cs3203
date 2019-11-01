#ifndef AUTOTESTER_NEXTSTARCOMPUTE_H
#define AUTOTESTER_NEXTSTARCOMPUTE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "NextBank.h"

class NextStarCompute
{
public:
    /**
     * Get all statement numbers that are in the previous position
     * in the Next* relationship with the input statement.
     * @param next
     * @param next_bank
     * @return a vector of statement numbers that are in the previous position
     * in the Next* relationship with the input statement.
     */
    std::vector<int> get_statements_previous_star(int next, NextBank& next_bank);   //e.g. Next*(n, 2)
    /**
     * Get all statement numbers that are in the next position
     * in the Next* relationship with the input statement.
     * @param previous
     * @param next_bank
     * @return a vector of statement numbers that are in the next position
     * in the Next* relationship with the input statement.
     */
    std::vector<int> get_statements_next_star(int previous, NextBank& next_bank);  //e.g. Next*(1, n)
    /**
     * Check if stmt1 and stmt2 have a Next* relationship
     * @param previous
     * @param next
     * @param next_bank
     * @return return true if they have a Next* relationship
     */
    bool is_next_star(int previous, int next, NextBank& next_bank); //e.g. Next*(1, 2)
    //std::unordered_map<int, std::vector<int>> get_all_next_star_relationship(NextBank& next_bank);  //e.g. Next*(n1, n2)
    /**
     * Get all Next* relationship of this program
     * @param last_stmt_num
     * @param next_bank
     * @return an unordered_map containing all Next* relationship in the program with statement number as key and
     * a vector of statement numbers which means they are in the next position in the Next* relationship with the key.
     */
    std::unordered_map<int, std::vector<int>> get_all_next_star_relationship(int last_stmt_num, NextBank& next_bank);  //e.g. Next*(n1, n2)

private:
    //std::unordered_map<int, std::unordered_set<int>> dfs_for_cfg(int target_stmt, std::unordered_map<int, std::vector<int>> cfg);
    /**
     * DFS algorithm
     * @param target_stmt
     * @param cfg
     * @return return a vector of statement numbers
     */
    std::vector<int> dfs_for_cfg(int target_stmt, std::unordered_map<int, std::vector<int>> cfg);
};


#endif //AUTOTESTER_NEXTSTARCOMPUTE_H
