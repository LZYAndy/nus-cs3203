#include "NextStarCompute.h"

std::vector<int> NextStarCompute::get_statements_previous_star(int next, NextBank& next_bank) {
    return DFS_for_CFG(next, next_bank.get_all_previous_relationship());
}

std::vector<int> NextStarCompute::get_statements_next_star(int previous, NextBank& next_bank) {
    return DFS_for_CFG(previous, next_bank.get_all_next_relationship());
}

bool NextStarCompute::is_next_star(int previous, int next, NextBank& next_bank) {
    std::vector<int> result = DFS_for_CFG(previous, next_bank.get_all_previous_relationship());
    if (find(result.begin(), result.end(), next) != result.end()) {
        return true;
    }
    else
    {
        return false;
    }
}

std::unordered_map<int, std::vector<int>> NextStarCompute::get_all_next_star_relationship(int last_stmt_num, NextBank& next_bank) {
    std::unordered_map<int, std::vector<int>> pairs;
    std::vector<int> result;
    for(int i = 1; i <= last_stmt_num; i++)
    {
        result = DFS_for_CFG(i, next_bank.get_all_next_relationship());
        pairs.emplace(i, result);
    }
    return pairs;
}

std::vector<int> NextStarCompute::DFS_for_CFG(int stmt, std::unordered_map<int, std::vector<int>> cfg) {
    std::vector<int> result;
    std::vector<int> visited;
    std::vector<int> next_stmts;
    visited.push_back(stmt);
    if (cfg.find(stmt) != cfg.end())
    {
        next_stmts = cfg.at(stmt);
    }
    else
    {
        return result;
    }
    while(!next_stmts.empty())
    {
        int target = next_stmts.back();
        next_stmts.pop_back();
        if (find(visited.begin(), visited.end(), target) == visited.end())
        {
            visited.push_back(target);
        }
        else
        {
            continue;
        }
        if (find(result.begin(), result.end(), target) == result.end())
        {
            result.push_back(target);
        }
        if (cfg.find(target) != cfg.end())
        {
            for (int i: cfg.at(target))
            {
                next_stmts.push_back(i);
            }
        }
    }
    return result;
}
