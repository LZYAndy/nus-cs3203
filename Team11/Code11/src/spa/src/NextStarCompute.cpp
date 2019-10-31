#include "NextStarCompute.h"

/*
std::vector<int> NextStarCompute::get_statements_previous_star(int next, NextBank& next_bank)
{
    std::vector<int> result;
    std::unordered_map<int, std::unordered_set<int>> temp_map = DFS_for_CFG(next, next_bank.get_all_previous_relationship());
    std::unordered_set<int> temp;
    if (!temp_map.empty())
    {
        temp = temp_map.at(next);
    }
    for(int i: temp)
    {
        result.push_back(i);
    }
    return result;
}

std::vector<int> NextStarCompute::get_statements_next_star(int previous, NextBank& next_bank)
{
    std::vector<int> result;
    std::unordered_map<int, std::unordered_set<int>> temp_map = DFS_for_CFG(previous, next_bank.get_all_next_relationship());
    std::unordered_set<int> temp;
    if (!temp_map.empty())
    {
        temp = temp_map.at(previous);
    }
    for(int i: temp)
    {
        result.push_back(i);
    }
    return result;
}

bool NextStarCompute::is_next_star(int previous, int next, NextBank& next_bank)
{
    std::unordered_set<int> result = DFS_for_CFG(previous, next_bank.get_all_previous_relationship()).at(previous);
    return find(result.begin(), result.end(), next) != result.end();
}

std::unordered_map<int, std::vector<int>> NextStarCompute::get_all_next_star_relationship(NextBank& next_bank)
{
    int stmt;
    std::unordered_map<int, std::vector<int>> result;
    std::vector<int> vec;
    std::unordered_set<int> set;
    std::unordered_map<int, std::unordered_set<int>> temp;
    temp = DFS_for_CFG(1, next_bank.get_all_next_relationship());
    for(std::pair<int, std::unordered_set<int>> i: temp)
    {
        stmt = i.first;
        set = i.second;
        for(int j: set)
        {
            vec.push_back(j);
        }
        result.emplace(stmt, vec);
    }
    return result;
}

std::unordered_map<int, std::unordered_set<int>> NextStarCompute::dfs_for_cfg(int stmt, std::unordered_map<int, std::vector<int>> cfg)
{
    std::unordered_map<int, std::unordered_set<int>> result;
    std::vector<int> visited;
    std::vector<int> next_stmts;
    std::vector<int> route;
    std::vector<int> junction;
    //std::unordered_set<int> vec;
    route.push_back(stmt);

    if (cfg.find(stmt) != cfg.end())
    {
        next_stmts = cfg.at(stmt);
        if (next_stmts.size() > 1)
        {
            junction.push_back(stmt);
        }
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
        route.push_back(target);

        if (cfg.find(target) != cfg.end())
        {
            if (cfg.at(target).size() > 1)
            {
                junction.push_back(target);
            }

            for (int i: cfg.at(target))
            {
                next_stmts.push_back(i);
            }
        }
        else
        {
            for (int i = 0; i < route.size(); i++)
            {
                for (int j = i + 1; j < route.size(); j++)
                {
                    if(result.find(route[i]) != result.end())
                    {
                        result.at(route[i]).emplace(route[j]);
                    }
                    else
                    {
                        result.emplace(route[i], route[j]);
                    }
                }
            }
            //reduce route to node
            if(!junction.empty())
            {
                int junction_node = junction.back();
                junction.pop_back();
                while (route.back() != junction_node)
                {
                    route.pop_back();
                }
            }
        }
    }
    return result;
}*/

std::vector<int> NextStarCompute::get_statements_previous_star(int next, NextBank& next_bank)
{
    return dfs_for_cfg(next, next_bank.get_all_previous_relationship());
}

std::vector<int> NextStarCompute::get_statements_next_star(int previous, NextBank& next_bank)
{
    return dfs_for_cfg(previous, next_bank.get_all_next_relationship());
}

bool NextStarCompute::is_next_star(int previous, int next, NextBank& next_bank)
{
    std::vector<int> vec = dfs_for_cfg(previous, next_bank.get_all_next_relationship());
    return find(vec.begin(), vec.end(), next) != vec.end();
}

std::unordered_map<int, std::vector<int>> NextStarCompute::get_all_next_star_relationship(int last_stmt_num, NextBank& next_bank)
{
    std::unordered_map<int, std::vector<int>> result;
    std::unordered_map<int, std::vector<int>> cfg = next_bank.get_all_next_relationship();
    std::vector<int> next_star_stmts;
    for(int i = 1; i <= last_stmt_num; i++)
    {
        next_star_stmts = dfs_for_cfg(i, cfg);
        if (!next_star_stmts.empty())
        {
            result.emplace(i, next_star_stmts);
        }
    }
    return result;
}

std::vector<int> NextStarCompute::dfs_for_cfg(int target_stmt, std::unordered_map<int, std::vector<int>> cfg)
{
    std::vector<int> result;
    std::vector<int> visited;
    std::vector<int> next_stmts;
    if (cfg.find(target_stmt) != cfg.end())
    {
        next_stmts = cfg.at(target_stmt);
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
